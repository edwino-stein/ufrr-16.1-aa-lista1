#include <stdlib.h>
#include "../header/avlTree.h"

AvlTreeInt insertAvlTreeInt(AvlTreeInt t, int value){
    AvlTreeInt newNode = insertBinaryTreeInt(t, value);
    balanceAvlTreeInt(t);
    return newNode;
}

bool removeAvlTreeInt(AvlTreeInt t, int value){

    if(_removeBinaryTreeInt(t, NULL, value)){
        balanceAvlTreeInt(t);
        return true;
    }

    return false;
}

void balanceAvlTreeInt(AvlTreeInt t){

    if(isEmptyOrNullBinaryTreeInt(t)) return;

    int balanceFactor = 0;

    while(true){

        balanceAvlTreeInt(t->left);
        balanceAvlTreeInt(t->right);
        balanceFactor = balanceFactorAvlTreeInt(t);

		if(balanceFactor >= (-1) && balanceFactor <= 1) return;

        if(balanceFactor <= (-2)){

            if(balanceFactorAvlTreeInt(t->left) == (-1)){
                rotationToRight(t);
            }
            else{
                rotationToLeft(t->left);
                rotationToRight(t);
            }
		}
        else if(balanceFactor >= 2){

            if(balanceFactorAvlTreeInt(t->right) == 1){
                rotationToLeft(t);
            }
            else{
                rotationToRight(t->right);
                rotationToLeft(t);
            }
        }
    }

}

int balanceFactorAvlTreeInt(AvlTreeInt t){
    return heightBinaryTreeInt(t->right) - heightBinaryTreeInt(t->left);
}

void rotationToLeft(AvlTreeInt t){

    if(isEmptyOrNullBinaryTreeInt(t)) return;
    if(isLeafBinaryTreeInt(t) || isEmptyOrNullBinaryTreeInt(t->right)) return;

    AvlTreeInt right = t->right;

    AvlTreeInt temp = newBinaryTreeInt();
    setValueBinaryTreeInt(temp, getValueBinaryTreeInt(t));
    temp->left = t->left;
    temp->right = right->left;

    setValueBinaryTreeInt(t, getValueBinaryTreeInt(right));
    t->left = temp;
    t->right = right->right;

    right->left = NULL;
    right->right = NULL;
    deleteBinaryTreeInt(right);
}

void rotationToRight(AvlTreeInt t){

    if(isEmptyOrNullBinaryTreeInt(t)) return;
    if(isLeafBinaryTreeInt(t) || isEmptyOrNullBinaryTreeInt(t->left)) return;

    AvlTreeInt left = t->left;

    AvlTreeInt temp = newBinaryTreeInt();
    setValueBinaryTreeInt(temp, getValueBinaryTreeInt(t));
    temp->left = t->left->right;
    temp->right = t->right;

    setValueBinaryTreeInt(t, getValueBinaryTreeInt(left));
    t->left = left->left;
    t->right = temp;

    left->left = NULL;
    left->right = NULL;
    deleteBinaryTreeInt(left);
}
