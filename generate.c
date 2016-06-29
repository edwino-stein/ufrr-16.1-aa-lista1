#include "common/common.h"

#define ORDER_SORTED 1
#define ORDER_SORTED_DESC 2
#define ORDER_RANDOM 3

int main(int argc, char *argv[]){

    if(argc == 1){
        printLn("Quantidade inválida!");
        printLn("Informe a quandidade de números que serão gravados no arquivo.");
        return 1;
    }

    if(argc == 2){
        printLn("Arquivo inálido!");
        printLn("Informe o caminho de um arquivo válido.");
        return 1;
    }

    char order;
    if(argc >= 3){

        String orderIn = newString(argv[3]);

        if(cStrIsEqual(orderIn, "asc")) order = ORDER_SORTED;
        else if(cStrIsEqual(orderIn, "desc")) order = ORDER_SORTED_DESC;
        else order = ORDER_RANDOM;

        deleteString(orderIn);
    }
    else{
        order = ORDER_RANDOM;
    }

    int size = atoi(argv[1]);
    if(size <= 0){
        printLn("Quantidade inválida!");
        printLn("Informe a quandidade de números que serão gravados no arquivo.");
        return 1;
    }

    int j = size - 1;
    int *data = (int *) malloc(sizeof(int) * size);

    if(data == NULL){
        printLn("Erro durante o alocamento de memória!");
        return 1;
    }

    switch (order) {

        case ORDER_SORTED:
            for(int i = 0; i < size; i++) data[i] = i;
        break;

        case ORDER_SORTED_DESC:
            for(int i = 0; i < size; i++) data[i] = j--;
        break;

        case ORDER_RANDOM:
        default:
            for(int i = 0; i < size; i++) data[i] = randInt(size*10);
        break;
    }

    String fileName = newString(argv[2]);
    if(!writeOutputFile(fileName, data, size)){
        print("Erro ao gravar o arquivo com os resultados.");
        free(data);
        deleteString(fileName);
        return 1;
    }

    free(data);
    deleteString(fileName);
    return 0;
}
