#include "common/common.h"

#include "structs/header/avlTree.h"
#include "structs/header/RBTree.h"
#include <time.h>

int main(int argc, char *argv[]){

    if(argc == 1){
        printLn("Árvore inálida!");
        printLn("Árvores: rbtree ou avltree.");
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

    String tree = newString(argv[1]);
    String fileName = newString(argv[2]);

    int size = atoi(argv[3]);
    if(size <= 0){
        printLn("Tamanho de buffer inválido!");
        printLn("Informe um tamanho de buffer válido.");
        return 1;
    }

    int *data = (int *) malloc(sizeof(int) * size);
    size = readOutputFile(fileName, data, size);

    char outputFile[255];
    char datetime[100];
    time_t now = time(0);
    strftime (datetime, 100, "%Y-%m-%dT%H:%M:%S", localtime (&now));
    sprintf(outputFile, "output/out-%s-%s_%s.txt", getCStr(tree), argv[3], datetime);

    long int t = 0;

    if(cStrIsEqual(tree, "rbtree")){

        RBTreeInt rb = newRBTreeInt();

        t = getMicroTime();
        for(int i = 0; i < size; i++){
            insertRBTreeInt(rb, data[i]);
        }
        t = getMicroTime() - t;

        FILE * rbFile;
        rbFile = fopen (outputFile , "w+");
        if (rbFile != NULL){
            fPrintRBTreeInt(rbFile, rb);
            fclose(rbFile);
        }

        deleteRBTreeInt(rb);
    }
    else if(cStrIsEqual(tree, "avltree")){

        AvlTreeInt avl = newAvlTreeInt();

        t = getMicroTime();
        for(int i = 0; i < size; i++){
            insertAvlTreeInt(avl, data[i]);
        }
        t = getMicroTime() - t;

        FILE * avlFile;
        avlFile = fopen (outputFile , "w+");
        if (avlFile != NULL){
            fPrintAvlTreeInt(avlFile, avl);
            fclose(avlFile);
        }

        deleteAvlTreeInt(avl);
    }

    else{
        printLn("Árvore inálida!");
        printLn("Árvores: rbtree ou avltree.");
        deleteString(tree);
        deleteString(fileName);
        free(data);
        return 1;
    }

    printf("%ld", t);

    deleteString(tree);
    deleteString(fileName);
    free(data);
    return 0;
}
