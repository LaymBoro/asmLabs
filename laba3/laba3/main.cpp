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
		add edi, 128

		mov edx, edi // 3) 256 - 383
		add edx, 128

		mov ecx, edx // 4) 384 - 511
		add ecx, 128

	calling:

		push ecx
		push edx

		call random
		movzx eax, ax

		pop edx
		pop ecx

		jmp is_even
		
	is_even:

		mov[esi], eax
		add esi, 2

		lea ebx, arr
		add ebx, 127
		cmp ebx, esi
		jge calling
		jng is_odd

	is_odd:

		mov[edi], eax
		add edi, 2

		lea ebx, arr
		add ebx, 255
		cmp ebx, edi
		jge calling
		jng is_bigger

	is_bigger:

		mov[edx], eax
		add edx, 2

		lea ebx, arr
		add ebx, 383
		cmp ebx, edx
		jge calling
		jng is_smaller

	is_smaller:

		mov[ecx], eax
		add ecx, 2

		lea ebx, arr
		add ebx, 511
		cmp ebx, ecx
		jge calling
		jng exit
	exit:
		popad
	}

	for (size_t i = 0; i < DATA_SIZE; i++)
	{
		cout << arr[i] << " ";
	}
	return 0;
}