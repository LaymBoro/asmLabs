#include <iostream>



int main()
{
	uint32_t num = 0x14523678;//0001'0100'0101'0010'0011'0110'0111'1000
	size_t zero = 32; //19
	size_t one = 0; //13
	size_t zeroPair = 0; //6
	size_t onePair = 0; //4
	uint8_t revers = 0; //30  0001'1110
	
	__asm 
	{
		pushad

		lea esi, num
		mov eax, [esi]
		jmp count

	degree_two:

		jecxz if_zero
		mov edi, 2
		mul edi
		loop degree_two
		mov ebx, eax
		jmp after_degree

	if_zero:

		mov ebx, 1
		jmp after_degree

	count:

		bsf ecx, eax
		je result
		push eax
		mov eax, 1
		jmp degree_two
	
	after_degree:

		pop eax
		sub eax, ebx
		inc one
		dec zero
		jmp count

	result:
	
		popad
	}


	std::cout << "zero: " << zero << " one: " << one << "\n";

	zero = 0; //19
	one = 0; //13

	__asm 
	{
		pushad

		lea esi, num
		mov eax, [esi]
		mov ecx, 32
		jmp second_count

	second_count:

		bt eax, ecx
		jc inc_one
		inc zero
		loop second_count
		jmp result_two

	inc_one:
		
		inc one
		loop second_count

	result_two:

		popad
	}

	std::cout << "another variant: \n" << "zero: " << zero << " one: " << one << "\n";
	
	__asm
	{
		pushad

		lea esi, num
		mov eax, [esi]
		mov ecx, 0
		
	the_loop:

		cmp ecx, 32
		jge pair_result
		mov edi, 0
		shld edi, eax, 2
		cmp edi, 3
		jz one_pair_counter
		cmp edi, 0
		jz zero_pair_counter
		shl eax, 1
		add ecx, 1
		jmp the_loop

	one_pair_counter:

		inc onePair
		shl eax, 2 
		add ecx, 2
		jmp the_loop

	zero_pair_counter:

		cmp ecx, 31
		jge pair_result
		inc zeroPair
		shl eax, 2
		add ecx, 2
		jmp the_loop

	pair_result:
		popad
	}

	std::cout << "pairs: \n" << "zero's: " << zeroPair << " one's: " << onePair << "\n";
	
	__asm
	{
		pushad

		lea esi, num
		mov eax, [esi]

		mov edx, 0
		mov ebx, 0
		mov bl, al
		mov ecx, 8

	swap:

		sal dl, 1
		shr bl, 1
		adc dl, 0

		loop swap

		lea ecx, revers
		mov [ecx], dl

		popad
	}

	std::cout << "revers: \n" <<(int) revers<< " \n";
	return 0;
}

