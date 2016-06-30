#include "../header/binaryTree.h"
#include <stdio.h>
#include <stdlib.h>

BinaryTreeInt newBinaryTreeInt(){

    BinaryTreeInt t = malloc(sizeof(struct _BinaryTreeInt_));

    if(!t){
    	perror("malloc");
    	exit(1);
	}

    t->value = NULL;
    t->left = NULL;
    t->right = NULL;

    return t;
}

void deleteBinaryTreeInt(BinaryTreeInt t){

    if(isEmptyBinaryTreeInt(t)) return;

    if(t->left != NULL){
        deleteBinaryTreeInt(t->left);
        t->left = NULL;
    }

    if(t->right != NULL){
        deleteBinaryTreeInt(t->right);
        t->right = NULL;
    }

    free(t->value);
    t->value = NULL;

    free(t);
}

BinaryTreeInt insertBinaryTreeInt(BinaryTreeInt t, int value){

    if(isEmptyBinaryTreeInt(t)){
        setValueBinaryTreeInt(t, value);
        return t;
    }

    int tValue = getValueBinaryTreeInt(t);
    if(value < tValue){
        if(t->left == NULL) t->left = newBinaryTreeInt();
        return insertBinaryTreeInt(t->left, value);
    }
    else if(value > tValue){
        if(t->right == NULL) t->right = newBinaryTreeInt();
        return insertBinaryTreeInt(t->right, value);
    }

    return t;
}

bool _removeBinaryTreeInt(BinaryTreeInt t, BinaryTreeInt parent, int value){

    if(isEmptyOrNullBinaryTreeInt(t)) return false;

    int tValue = getValueBinaryTreeInt(t);

    if(value < tValue) return _removeBinaryTreeInt(t->left, t, value);
    else if(value > tValue) return _removeBinaryTreeInt(t->right, t, value);

    //Caso 1: É uma folha
    if(isLeafBinaryTreeInt(t)){

        if(parent == NULL){
            free(t->value);
            t->value = NULL;
            return true;
        }

        if(parent->left == t) parent->left = NULL;
        else parent->right = NULL;

        deleteBinaryTreeInt(t);
        return true;
    }

    //Caso 3: Dois filhos
    if(t->left != NULL && t->right != NULL){
		int precessor = getValueBinaryTreeInt(getPredecessorBinaryTreeInt(t));
        _removeBinaryTreeInt(t->left, t, precessor);
        setValueBinaryTreeInt(t, precessor);
        return true;
    }

    //Caso 2: Um filho
    BinaryTreeInt child = t->left != NULL ? t->left : t->right;

    setValueBinaryTreeInt(t, getValueBinaryTreeInt(child));
    t->left = child->left;
    t->right = child->right;

    child->left = NULL;
    child->right = NULL;

    deleteBinaryTreeInt(child);
    return true;
}

BinaryTreeInt searchBinaryTreeInt(BinaryTreeInt t, int value){

    if(isEmptyOrNullBinaryTreeInt(t)) return false;

    int tValue = getValueBinaryTreeInt(t);
    if(value < tValue){
        if(t->left == NULL) return NULL;
        return searchBinaryTreeInt(t->left, value);
    }
    else if(value > tValue){
        if(t->right == NULL) return NULL;
        return searchBinaryTreeInt(t->right, value);
    }

    return t;
}

BinaryTreeInt getSucessorBinaryTreeInt(BinaryTreeInt t){

    if(isEmptyOrNullBinaryTreeInt(t)) return false;

	if(isLeafBinaryTreeInt(t) || t->right == NULL)
		return t;

	t = t->right;
	while(t->left != NULL) t = t->left;
	return t;
}

BinaryTreeInt getPredecessorBinaryTreeInt(BinaryTreeInt t){

    if(isEmptyOrNullBinaryTreeInt(t)) return false;

    if(isLeafBinaryTreeInt(t) || t->left == NULL)
		return t;

	//Guada o filho da esquerda e navega até o ultimo filho da direita
	t = t->left;
	while(t->right != NULL) t = t->right;
	return t;
}

void setValueBinaryTreeInt(BinaryTreeInt t, int value){

    if(isEmptyBinaryTreeInt(t)){
        t->value = malloc(sizeof(int));
        if(!t->value){
        	perror("malloc");
        	exit(1);
    	}
    }

    *t->value = value;
}

int getValueBinaryTreeInt(BinaryTreeInt t){
    if(t == NULL) return 0;
    return isEmptyBinaryTreeInt(t) ? 0 : *t->value;
}

int heightBinaryTreeInt(BinaryTreeInt t){

    if( t == NULL) return -1;
    if(isEmptyBinaryTreeInt(t)) return -1;

	int heightLeft = heightBinaryTreeInt(t->left);
	int heightRight = heightBinaryTreeInt(t->right);

    return (heightLeft >= heightRight ? heightLeft : heightRight) + 1;
}

bool isEmptyBinaryTreeInt(BinaryTreeInt t){
    return t->value == NULL;
}

bool isEmptyOrNullBinaryTreeInt(BinaryTreeInt t){
    if(t == NULL) return true;
    return t->value == NULL;
}

bool isLeafBinaryTreeInt(BinaryTreeInt t){
    return t->left == NULL && t->right == NULL;
}

void printSpaces(int spaces){

    if(spaces > 0){
        char string[spaces*2 + 1];
        for(int i = 0; i < spaces*2; i++){
            string[i] = ' ';
        }
        string[spaces*2] = '\0';
        printf("%s + ", string);
    }
    else{
        printf(" + ");
    }
}

void _printBinaryTreeInt(BinaryTreeInt t, unsigned int spaces){
    if(isEmptyBinaryTreeInt(t)) return;

    printf("(%d)\n", getValueBinaryTreeInt(t));

    if(isLeafBinaryTreeInt(t)) return;
    spaces++;

    printSpaces(spaces);
    printf("L");
    if(t->left != NULL) _printBinaryTreeInt(t->left, spaces);
    else printf("()\n");

    printSpaces(spaces);
    printf("R");
    if(t->right != NULL) _printBinaryTreeInt(t->right, spaces);
    else printf("()\n");
}


void fPrintSpaces(FILE * file, int spaces){

    if(spaces > 0){
        char string[spaces*2 + 1];
        for(int i = 0; i < spaces*2; i++){
            string[i] = ' ';
        }
        string[spaces*2] = '\0';
        fprintf(file, "%s + ", string);
    }
    else{
        fprintf(file, " + ");
    }
}

void _fPrintBinaryTreeInt(FILE * file, BinaryTreeInt t, unsigned int spaces){

    if(isEmptyBinaryTreeInt(t)) return;

    fprintf(file, "(%d)\n", getValueBinaryTreeInt(t));

    if(isLeafBinaryTreeInt(t)) return;
    spaces++;

    fPrintSpaces(file, spaces);
    fprintf(file, "L");
    if(t->left != NULL) _fPrintBinaryTreeInt(file, t->left, spaces);
    else fprintf(file, "()\n");

    fPrintSpaces(file, spaces);
    fprintf(file, "R");
    if(t->right != NULL) _fPrintBinaryTreeInt(file, t->right, spaces);
    else fprintf(file, "()\n");
}
