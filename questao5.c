#include "common/common.h"
#include "sorts/sorts.h"
#include <time.h>

int main(int argc, char *argv[]){

    if(argc == 1){
        printLn("Algoritmo inálido!");
        printLn("Algoritmos: insertionsort, quicksort ou mergesort.");
        return 1;
    }

    if(argc == 2){
        printLn("Arquivo inálido!");
        printLn("Informe o caminho de um arquivo válido.");
        return 1;
    }

    if(argc == 3){
        printLn("Tamanho de buffer inválido");
        printLn("Informe um tamanho de buffer válido.");
        return 1;
    }

    String algorithm = newString(argv[1]);
    String fileName = newString(argv[2]);

    int size = atoi(argv[3]);
    if(size <= 0){
        printLn("Tamanho de buffer inválido!");
        printLn("Informe um tamanho de buffer válido.");
        return 1;
    }

    int *data = (int *) malloc(sizeof(int) * size);
    size = readOutputFile(fileName, data, size);
    long int t = 0;

    if(cStrIsEqual(algorithm, "insertionsort")){
        t = getMicroTime();
        intInsertionSort(data, size);
        t = getMicroTime() - t;
    }
    else if(cStrIsEqual(algorithm, "quicksort")){
        t = getMicroTime();
        intQuickSort(data, size);
        t = getMicroTime() - t;
    }
    else if(cStrIsEqual(algorithm, "mergesort")){
        t = getMicroTime();
        intMergeSort(data, size);
        t = getMicroTime() - t;
    }
    else{
        printLn("Algoritmo inálido!");
        printLn("Algoritmos: insertionsort, quicksort ou mergesort.");
        deleteString(algorithm);
        deleteString(fileName);
        free(data);
        return 1;
    }

    printf("%ld", t);

    char outputFile[255];
    char datetime[100];
    time_t now = time(0);
    strftime (datetime, 100, "%Y-%m-%dT%H:%M:%S", localtime (&now));
    sprintf(outputFile, "output/out-%s-%s_%s.txt", getCStr(algorithm), argv[3], datetime);
    String out = newString(outputFile);
    writeOutputFile(out, data, size);

    deleteString(algorithm);
    deleteString(fileName);
    deleteString(out);
    free(data);

    return 0;
}
