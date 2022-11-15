#include <iostream>

using namespace std;

int main()
{
	uint32_t temp;
	
	__asm {
		pushad

		mov eax, 4008698874
		mov ebx, 306001926
		mov si, 52347
		mov di, 20501
		mov dh, 153
		mov dl, 74

		//7
		xchg eax, ebx

		mov ecx, eax
		mov eax, ebx
		mov ebx, ecx

		push eax
		push ebx
		pop eax
		pop ebx

		lea ecx, temp
		mov [ecx], eax
		mov eax, ebx
		mov ebx, [ecx]
		//8
		xchg di, si

		mov cx, si
		mov si, di
		mov di, cx

		push si
		push di
		pop si
		pop di

		lea ecx, temp
		mov [ecx], si
		mov si, di
		mov di, [ecx]

		//9
		xchg dh, dl

		mov ch, dh
		mov dh, dl
		mov dl, ch

		push dx
		mov dh, dl
		pop cx
		mov dl, ch

		lea ecx, temp
		mov [ecx], dh
		mov dh, dl
		mov dl, [ecx]

		//10
		movsx ax, si
		movsx bx, di

		//11
		movzx eax, dh
		movzx ebx, dl

		popad
	}

	return (0);
}