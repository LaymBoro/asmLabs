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

	return uni(rng);
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
		
		push edx
		mov edx, 0
		mov ebx, 2
		push eax
		div ebx
		cmp edx, 0
		pop eax
		pop edx
		jne add_odd
	
		mov[esi], eax
		add esi, 2
		
		lea ebx, arr
		add ebx, 256
		cmp esi, ebx
		jge go_to_exit
		jmp is_bigger


	add_odd:

		mov[edi], eax
		add edi, 2

		lea ebx, arr
		add ebx, 512
		cmp edi, ebx
		jge go_to_exit

	is_bigger:

		cmp eax, 50000
		jnge is_smaller

		mov[edx], eax
		add edx, 2

		lea ebx, arr
		add ebx, 768
		cmp edx, ebx
		jge go_to_exit
		jmp calling

	is_smaller:

		cmp eax, 10000
		jnle calling

		mov[ecx], eax
		add ecx, 2

		lea ebx, arr
		add ebx, 1024
		cmp ecx, ebx
		jge go_to_exit
		jmp calling

	go_to_exit:
		popad
	}


	for (size_t i = 0; i < DATA_SIZE; i++)
	{
		switch (i)
		{
		case 0:
			cout << "even: " << "\n";
			break;
		case 128:
			cout << "\n" << "odd: " << "\n";
			break;
		case 256:
			cout << "\n" << "> 50000: " << "\n";
			break;
		case 384:
			cout << "\n" << "< 10000: " << "\n";
			break;
		}
		cout << arr[i] << " ";
	}
	return 0;
}