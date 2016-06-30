#if !defined  _AVLTREE
#define _AVLTREE

    #include <stdbool.h>
    #include "binaryTree.h"

    typedef struct _BinaryTreeInt_ *AvlTreeInt;

    #define newAvlTreeInt() (AvlTreeInt) newBinaryTreeInt()
    #define deleteAvlTreeInt(t) deleteBinaryTreeInt(t)

    #define setValueAvlTreeInt(t, v) setValueBinaryTreeInt(t, v)
    #define getValueAvlTreeInt(t) getValueBinaryTreeInt(t)

    AvlTreeInt insertAvlTreeInt(AvlTreeInt t, int value);
    bool removeAvlTreeInt(AvlTreeInt t, int value);

    #define searchAvlTreeInt(t, v) (AvlTreeInt) searchBinaryTreeInt(t, v)
    #define getSucessorAvlTreeInt(t) (AvlTreeInt) getSucessorBinaryTreeInt(t)
    #define getPredecessorAvlTreeInt(t) (AvlTreeInt) getPredecessorBinaryTreeInt(t)

    void balanceAvlTreeInt(AvlTreeInt t);
    int balanceFactorAvlTreeInt(AvlTreeInt t);
    void rotationToLeft(AvlTreeInt t);
    void rotationToRight(AvlTreeInt t);

    #define heightAvlTreeInt(t) heightBinaryTreeInt(t)
    #define isLeafAvlTreeInt(t) isLeafBinaryTreeInt(t)
    #define isEmptyAvlTreeInt(t) isEmptyBinaryTreeInt(t)
    #define isEmptyOrNullAvlTreeInt(t) isEmptyOrNullBinaryTreeInt(t)

    #define printAvlTreeInt(t) _printBinaryTreeInt(t, 0)
    #define fPrintAvlTreeInt(f, t) _fPrintBinaryTreeInt(f, t, 0)

#endif
