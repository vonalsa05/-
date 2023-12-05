#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 5 //глобальная перемененая фиксированного размера.

//объявление прототипов
void RandGenerate(int *);
void minmaxValue( int *);

int main(void){
    int array[SIZE] = {};
    int counter;
    srand(time(NULL));
    RandGenerate(array);
    minmaxValue(array);
    int q;
    printf("New array:\n[ ");
    for (q = 0; q <= SIZE-1; q++){
        printf("%d ", array[q]);
    }
    printf("]");
    return 0;
}

// функция генерирующая рандомные значения для массива.
void RandGenerate(int *arrayPtr)
{
    int i;
    for(i=0; i <= SIZE - 1; i++){
        arrayPtr[i] = rand();
    }

    int q;
    printf("Old array:\n[ ");
    for (q = 0; q <= SIZE-1; q++){
        printf("%d ", arrayPtr[q]);
    }
    printf("]\n");
}

/*
Чтобы получить максимальное и минимальное значение,
надо взять такие значения переменных, где максимум будет самым минимальным
среди всех значений массива, а минимум самым максимальным.
Таким образом, сравнивая и перебирая все элементы массива, можно 
с помощью операторов придти к необходимому максиму и минимуму массива.

*/
void minmaxValue(int *arrayPtr)
{
    // инициализация переменных.
    int min = 2147483647; int max = -1; 
    // объявление переменных.
    int max_i; int min_i; int j;
    // цикл, который перебирает все элементы массива и ищет максимум и минимум.
    for(j=0;j<=SIZE-1;j++){
        if (arrayPtr[j] < min){
            min = arrayPtr[j];
            min_i = j;
        }
        if (arrayPtr[j] > max){
            max = arrayPtr[j];
            max_i = j;
        }
    }
    // смена местами значений максимума и минимума.
    int hold;
    hold = arrayPtr[max_i];
    arrayPtr[max_i] = arrayPtr[min_i];
    arrayPtr[min_i] = hold;
}
