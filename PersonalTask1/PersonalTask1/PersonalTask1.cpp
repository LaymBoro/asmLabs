#include <iostream>
#include <random>
#include <iomanip>


size_t min = 0;
size_t max = 5;
const size_t arrSize = 3;

size_t random() 
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> uni(min, max);

    return uni(rng);
}

void randomArray(size_t arr[arrSize]) 
{
    for (size_t i = 0; i < arrSize; i++)
        arr[i] = random();
}

void randomMatrix(size_t arr[arrSize][arrSize]) 
{
    for (size_t i = 0; i < arrSize; i++)
        for (size_t j = 0; j < arrSize; j++)
            arr[i][j] = random();
}

size_t main()
{
    size_t X = random();
    size_t Y = random();
    size_t term = 0;
    size_t anotherCounter = 0;
    size_t result = 0;
    size_t tmp = 0;
    size_t size_tByte = 4;
    bool overflow = false;


    size_t A[arrSize] = {};
    size_t C[arrSize] = {};
    size_t B[arrSize][arrSize] = {};

    randomArray(A);
    randomArray(C);
    randomMatrix(B);

    std::cout << "A: \n";
    for (size_t i = 0; i < arrSize; i++)
    {
        std::cout << std::setw(3) << A[i];
    }

    std::cout << "\nB:";
    for (size_t i = 0; i < arrSize; i++)
    {
        std::cout << "\n";
        for (size_t j = 0; j < arrSize; j++)
        {
            std::cout << std::setw(3) << B[i][j];
        }
    }

    std::cout << "\nC: \n";
    for (size_t i = 0; i < arrSize; i++)
    {
        std::cout << std::setw(3) << C[i];
    }
    // result = X * Σ(A_i * B_i_j) + Y * ΣC_i

	__asm
	{
		pushad
		

        lea edx, arrSize
        mov ecx, [edx]

        lea esi, C

    c_sum: //Σ(C_i)

        jo except
        mov eax, [esi]
        add term, eax
        add esi, 4
        loop c_sum
        mov eax, term
        mul Y //Y * Σ(C_i)
        jo except
        add result, eax

    //Σ(A_i * B_i_j)

        lea esi, A
        lea edi, B

        mov ecx, arrSize
        mov ebx, edi
        

    mul_loop:

        mov eax, [esi]
        mul [edi]
        jo except
        add tmp, eax

        mov eax, anotherCounter
        mul size_tByte
        jo except
        add edi, eax
        loop mul_loop

        mov edi, ebx
        add edi, 4
        add esi, 4
        mov ecx, arrSize
        add ecx, 1
        loop mul_loop

        mov eax, tmp //X * Σ(A_i * B_i_j)
        mul X
        jo except
        add result, eax

    except:

        add overflow, 1

		popad
	}

    if (overflow)
    {
        std::cout << "\noverflow" << "\n";
    }
    else
    {
        std::cout << "\n" << result << "\n";
    }
	return 0;
}
