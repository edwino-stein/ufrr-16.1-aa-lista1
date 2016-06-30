#include "common/common.h"

void _maxMin(int array[], int first, int size, int *max, int *min){

    if(size - first <= 1){
        if(*max < array[size - 1]) *max = array[size - 1];
        if(*min > array[size - 1]) *min = array[size - 1];
        return;
    }

    int p = (first + size)/2;
    _maxMin(array, first, p, max, min);
    _maxMin(array, p, size, max, min);
}

void maxMin(int array[], int size, int *max, int *min){
    *max = array[0];
    *min = array[0];
    _maxMin(array, 0, size, max, min);
}

int main(int argc, char *argv[]){

    int min, max;
    int size = randIntB2in(5, 15);
    int list[size];

    print("Lista: ");
    for(int i = 0; i < size; i++){
        list[i] = randInt(100);
        print(list[i]);

        if(i + 1 < size) print(", ");
        else print(";");
    }

    printNewLine();

    maxMin(list, size, &max, &min);

    print("Máximo: ");
    printLn(max);

    print("Minimo: ");
    printLn(min);

    return 0;
}
