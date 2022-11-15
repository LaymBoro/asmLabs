#include<iostream>

using namespace std;

int main()
{
	//a = 0x1527'D27F; 354'931'327
	//b = 0x1'94A8'1B79; 6'789'012'345;
	//c = 0x1'D649'BAC0; 7'890'123'456;
	//d = 0x2'128E'0F87; 8'901'234'567; 
	//e = 0x2'192D'7B4E; 9'012'345'678;
	//f = 0x2'5B67'B115; 10'123'456'789;
	//result = (4*c - d/2 + 33)/(a -1);
	uint32_t memo;

	__asm
	{
		pushad

		//4*c (edi:esi)
		mov ecx, 0x4
		mov eax, 0xD649'BAC0
		mov ebx, 0x1
		mul ecx
		mov esi, eax
		mov edi, edx
		mov eax, ebx
		mul ecx
		add edi, eax

		//d/2 (ebx:eax)
		mov ecx, 0x2
		mov eax, 0x2
		mov edx, 0
		div ecx
		mov ebx, eax
		mov eax, 0x128E'0F87
		div ecx
		
		//4*c - d/2 (edi:esi)
		sub edi, ebx
		sbb esi, eax

		//4*c - d/2 + 33 (33 = 0x21) (edi:esi)
		add esi, 0x21

		//(4 * c - d / 2 + 33) / (a - 1)
		mov eax, esi
		mov edx, edi
		mov ecx, 0x1527'D27F
		dec ecx
		div ecx

		lea ecx, memo
		mov [ecx], eax

		popad
	}

	cout << memo;
	return 0;
}