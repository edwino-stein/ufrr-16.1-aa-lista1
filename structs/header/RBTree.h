#if !defined  _RBTREE
#define _RBTREE

    #include <stdbool.h>
    #include <stdio.h>

    #define RBTREE_REDNODE 1
    #define RBTREE_BLACKNODE 0

    struct _RBTreeNodeInt_{
        int value;
        char color;
        struct _RBTreeNodeInt_ *left;
        struct _RBTreeNodeInt_ *right;
        struct _RBTreeNodeInt_ *parent;
    };

    struct _RBTreeInt_{
        struct _RBTreeNodeInt_ *root;
    };

    typedef struct _RBTreeInt_ *RBTreeInt;
    typedef struct _RBTreeNodeInt_ *RBTreeNodeInt;

    RBTreeInt newRBTreeInt();
    void deleteRBTreeInt(RBTreeInt t);

    RBTreeNodeInt insertRBTreeInt(RBTreeInt t, int value);
    RBTreeNodeInt insertRBTreeNodeInt(RBTreeNodeInt n, int value, bool *founded);

    RBTreeNodeInt searchRBTreeInt(RBTreeInt t, int value);
    RBTreeNodeInt searchRBTreeNodeInt(RBTreeNodeInt n, int value);

    void rotationToLeftRBTreeInt(RBTreeInt t, RBTreeNodeInt n);
    void rotationToRightRBTreeInt(RBTreeInt t, RBTreeNodeInt n);

    RBTreeNodeInt createRBTreeNodeInt(int value, RBTreeNodeInt parent, RBTreeNodeInt left, RBTreeNodeInt right);
    void deleteRBTreeNodeInt(RBTreeNodeInt n);

    int heightRBTreeInt(RBTreeInt t);
    int heightRBTreeNodeInt(RBTreeNodeInt n);

    bool isEmptyRBTreeInt(RBTreeInt t);
    bool isRootRBTreeNodeInt(RBTreeNodeInt n);
    bool isLeafRBTreeNodeInt(RBTreeNodeInt n);

    void printRBTreeInt(RBTreeInt t);
    void printRBTreeNodeInt(RBTreeNodeInt n, unsigned int spaces);

    void fPrintRBTreeInt(FILE * file, RBTreeInt t);
    void fPrintRBTreeNodeInt(FILE * file, RBTreeNodeInt n, unsigned int spaces);

#endif
