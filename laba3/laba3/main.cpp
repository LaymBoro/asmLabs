#include <iostream>
#include <random>

using namespace std;

const int DATA_SIZE = 512;
const uint16_t MIN = 0x0;
const uint16_t MAX = 0xFFFF;

uint16_t random()
{
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<uint16_t> uni(MIN, MAX);

	return 2;
}

int main()
{
	uint16_t arr[DATA_SIZE];

	for (int i = 0; i < DATA_SIZE; i++) {
		arr[i] = 0;
	}


	__asm
	{
		pushad
		
		lea esi, arr // 1) 0 - 127

		mov edi, esi // 2) 128 - 255
		add edi, 256

		mov edx, edi // 3) 256 - 383
		add edx, 256

		mov ecx, edx // 4) 384 - 511
		add ecx, 256

	calling:

		push ecx
		push edx

		call random
		movzx eax, ax

		pop edx
		pop ecx

		jmp is_even
		
	is_even:
		
		push edx
		push eax
		xor edx, edx
		mov ebx, 2
		div ebx
		cmp edx, 0
		pop eax
		pop edx
		jne not_add_even
	
		mov[esi], eax
		add esi, 2

	not_add_even:
		
		lea ebx, arr
		add ebx, 254
		cmp esi, ebx
		jge exit
		jmp calling
/*
	is_odd:

		push edx
		push eax
		mov ebx, 0x0000'0002
		div ebx
		cmp edx, 0
		pop eax
		pop edx
		je not_add_odd

		mov[edi], eax
		add edi, 2

	not_add_odd:

		lea ebx, arr
		add ebx, 510
		cmp ebx, edi
		jng is_bigger
		jge exit

	is_bigger:

		
		cmp eax, 50000
		jnge not_add_bigger

		mov[edx], eax
		add edx, 2

	not_add_bigger:

		lea ebx, arr
		add ebx, 766
		cmp ebx, edx
		jng is_smaller
		jge exit

	is_smaller:

		cmp eax, 10000
		jnle not_add_smaller

		mov[ecx], eax
		add ecx, 2
	
	not_add_smaller:

		lea ebx, arr
		add ebx, 1022
		cmp ebx, ecx
		jng calling
		jge exit
*/
	exit:
		popad
	}

	for (size_t i = 0; i < DATA_SIZE; i++)
	{
		cout << arr[i] << " ";
	}
	return 0;
}