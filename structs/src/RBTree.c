#include "../header/RBTree.h"

#include <stdio.h>
#include <stdlib.h>

RBTreeInt newRBTreeInt(){
    RBTreeInt t = malloc(sizeof(struct _RBTreeInt_));
    t->root = NULL;
    return t;
}

void deleteRBTreeInt(RBTreeInt t){
    deleteRBTreeNodeInt(t->root);
    t->root = NULL;
    free(t);
}

RBTreeNodeInt createRBTreeNodeInt(int value, RBTreeNodeInt parent, RBTreeNodeInt left, RBTreeNodeInt right){

    RBTreeNodeInt node = malloc(sizeof(struct _RBTreeNodeInt_));

    if(!node){
    	perror("malloc");
    	exit(1);
	}

    node->value = value;
    node->color = RBTREE_REDNODE;

    node->parent = parent;
    node->left = left;
    node->right = right;

    return node;
}

void deleteRBTreeNodeInt(RBTreeNodeInt n){

    if(n == NULL) return;
    n->parent = NULL;

    deleteRBTreeNodeInt(n->left);
    n->left = NULL;

    deleteRBTreeNodeInt(n->right);
    n->right = NULL;

    free(n);
}

bool isColorRBTreeInt(RBTreeNodeInt n, char color){
    if(n == NULL) return color == RBTREE_BLACKNODE;
    return n->color == color;
}

void fixRBTreeInt(RBTreeInt t, RBTreeNodeInt n){

    if(isRootRBTreeNodeInt(n)) return;
    if(isColorRBTreeInt(n->parent, RBTREE_BLACKNODE)) return;

    RBTreeNodeInt parent = n->parent, uncle;

    if(parent == parent->parent->left){

        uncle = parent->parent->right;

        if(isColorRBTreeInt(uncle, RBTREE_BLACKNODE)){

            //Caso 2L
            if(n == parent->right){
                rotationToLeftRBTreeInt(t, parent);
                fixRBTreeInt(t, parent);
            }

            //Caso 3L
            else{
                parent->parent->color = RBTREE_REDNODE;
                parent->color = RBTREE_BLACKNODE;
                rotationToRightRBTreeInt(t, parent->parent);
            }

        }

        //Caso 1L
        else{
            parent->color = RBTREE_BLACKNODE;
            uncle->color = RBTREE_BLACKNODE;
            parent->parent->color = RBTREE_REDNODE;
            fixRBTreeInt(t, parent->parent);
        }
    }
    else{

        uncle = parent->parent->left;

        if(isColorRBTreeInt(uncle, RBTREE_BLACKNODE)){

            //Caso 2R
            if(n == parent->left){
                rotationToRightRBTreeInt(t, parent);
                fixRBTreeInt(t, parent);
            }

            //Caso 3R
            else{
                parent->parent->color = RBTREE_REDNODE;
                parent->color = RBTREE_BLACKNODE;
                rotationToLeftRBTreeInt(t, parent->parent);
            }
        }

        //Caso 1R
        else{
            parent->color = RBTREE_BLACKNODE;
            uncle->color = RBTREE_BLACKNODE;
            parent->parent->color = RBTREE_REDNODE;
            fixRBTreeInt(t, parent->parent);
        }
    }
}

RBTreeNodeInt insertRBTreeInt(RBTreeInt t, int value){

    if(t == NULL) return NULL;
    if(isEmptyRBTreeInt(t)){
        t->root = createRBTreeNodeInt(value, NULL, NULL, NULL);
        t->root->color = RBTREE_BLACKNODE;
        return t->root;
    }

    bool founded = false;
    RBTreeNodeInt node = insertRBTreeNodeInt(t->root, value, &founded);

    if(!founded) fixRBTreeInt(t, node);
    t->root->color = RBTREE_BLACKNODE;

    return node;
}

RBTreeNodeInt insertRBTreeNodeInt(RBTreeNodeInt n, int value, bool *founded){

    if(n == NULL) return NULL;

    if(value < n->value){

        if(n->left == NULL){
            n->left = createRBTreeNodeInt(value, n, NULL, NULL);
            return n->left;
        }

        return insertRBTreeNodeInt(n->left, value, founded);
    }
    else if(value > n->value){

        if(n->right == NULL){
            n->right = createRBTreeNodeInt(value, n, NULL, NULL);
            return n->right;
        }

        return insertRBTreeNodeInt(n->right, value, founded);
    }

    else *founded = true;
    return n;
}

RBTreeNodeInt searchRBTreeInt(RBTreeInt t, int value){
    return t == NULL ? NULL : searchRBTreeNodeInt(t->root, value);
}

RBTreeNodeInt searchRBTreeNodeInt(RBTreeNodeInt n, int value){

    if(n == NULL) return NULL;

    if(value < n->value) return searchRBTreeNodeInt(n->left, value);
    else if(value > n->value) return searchRBTreeNodeInt(n->right, value);

    return n;
}

void rotationToLeftRBTreeInt(RBTreeInt t, RBTreeNodeInt n){

    if(isEmptyRBTreeInt(t)) return;
    if(isLeafRBTreeNodeInt(n) || n->right == NULL) return;

    RBTreeNodeInt right = n->right;

    n->right = right->left;
    if(n->right != NULL) n->right->parent = n;
    right->left = n;

    if(isRootRBTreeNodeInt(n)) t->root = right;
    else if(n == n->parent->left) n->parent->left = right;
    else n->parent->right = right;

    right->parent = n->parent;
    n->parent = right;
}

void rotationToRightRBTreeInt(RBTreeInt t, RBTreeNodeInt n){

    if(isEmptyRBTreeInt(t)) return;
    if(isLeafRBTreeNodeInt(n) || n->left == NULL) return;

    RBTreeNodeInt left = n->left;

    n->left = left->right;
    if(n->left != NULL) n->left->parent = n;
    left->right = n;

    if(isRootRBTreeNodeInt(n)) t->root = left;
    else if(n == n->parent->left) n->parent->left = left;
    else n->parent->right = left;

    left->parent = n->parent;
    n->parent = left;
}


int heightRBTreeInt(RBTreeInt t){
    return heightRBTreeNodeInt(t->root);
}

int heightRBTreeNodeInt(RBTreeNodeInt n){

    if(n == NULL) return (-1);

	int heightLeft = heightRBTreeNodeInt(n->left);
	int heightRight = heightRBTreeNodeInt(n->right);

    return (heightLeft >= heightRight ? heightLeft : heightRight) + 1;
}

bool isEmptyRBTreeInt(RBTreeInt t){
    return t->root == NULL;
}

bool isRootRBTreeNodeInt(RBTreeNodeInt n){
    return n->parent == NULL;
}

bool isLeafRBTreeNodeInt(RBTreeNodeInt n){
    return n->left == NULL && n->right == NULL;
}


void printRBTreeInt(RBTreeInt t){
    printf("\nRoot");
    printRBTreeNodeInt(t->root, 0);
    printf("\n");
}

void RBTprintSpaces(int spaces){

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

void printRBTreeNodeInt(RBTreeNodeInt n, unsigned int spaces){

    if(n == NULL){
        printf("()\n");
        return;
    }

    printf("(%d, %c, %d)\n", n->value, n->color == RBTREE_REDNODE ? 'R' : 'B', n->parent == NULL ? 0 : n->parent->value);
    if(isLeafRBTreeNodeInt(n)) return;

    spaces++;
    RBTprintSpaces(spaces);
    printf("L");
    printRBTreeNodeInt(n->left, spaces);

    RBTprintSpaces(spaces);
    printf("R");
    printRBTreeNodeInt(n->right, spaces);
}

void fRBTprintSpaces(FILE * file, int spaces){

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

void fPrintRBTreeInt(FILE * file, RBTreeInt t){
    fprintf(file, "\nRoot");
    fPrintRBTreeNodeInt(file, t->root, 0);
    fprintf(file, "\n");
}
void fPrintRBTreeNodeInt(FILE * file, RBTreeNodeInt n, unsigned int spaces){

    if(n == NULL){
        fprintf(file, "()\n");
        return;
    }

    fprintf(file, "(%d, %c)\n", n->value, n->color == RBTREE_REDNODE ? 'R' : 'B');
    if(isLeafRBTreeNodeInt(n)) return;

    spaces++;
    fRBTprintSpaces(file, spaces);
    fprintf(file, "L");
    fPrintRBTreeNodeInt(file, n->left, spaces);

    fRBTprintSpaces(file, spaces);
    fprintf(file, "R");
    fPrintRBTreeNodeInt(file, n->right, spaces);
}
