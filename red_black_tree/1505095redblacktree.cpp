#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

#define RED		1
#define BLACK	2

struct node
{
    int key;
    struct node *left, *right, *parent;
    int color;
};

typedef struct node *NODEPTR;
struct node NIL;
NODEPTR NILPTR = &NIL;

void inorder(NODEPTR x, int clr);

char colorrbt(NODEPTR x,int clr)
{
    if(x->color==1)
    {
        return 'r';
    }
    else if(x->color==2)
    {
        return 'b';
    }
}

void inorder(NODEPTR x, int clr)
{
    if (x != NILPTR)
    {
        inorder(x->left,x->color);
        //printf("%d %d ", x->key, x->color);
        cout<<x->key<<' '<<colorrbt(x,x->color)<<' ';
        inorder(x->right,x->color);
    }
}

NODEPTR search(NODEPTR root, int k)
{
    if (root == NILPTR || root->key == k)
        return root;
    if (k < root->key)
        return search(root->left, k);
    else
        return search(root->right, k);
}

NODEPTR minimum(NODEPTR root)
{
    while (root->left != NILPTR)
        root = root->left;
    return root;
}

NODEPTR maximum(NODEPTR root)
{
    while (root->right != NILPTR)
        root = root->right;
    return root;
}

NODEPTR successor(NODEPTR root, int x)
{
    NODEPTR temp = search(root, x);
    if (temp == NILPTR)
    {
        printf("%d not in tree\n", x);
        return temp;
    }
    if (temp->right != NILPTR)
        return minimum(temp->right);
    NODEPTR y = temp->parent;
    while (y != NILPTR && temp == y->right)
    {
        temp = y;
        y = y->parent;
    }
    return y;
}

NODEPTR predecessor(NODEPTR root, int x)
{
    NODEPTR temp = search(root, x);
    if (temp == NILPTR)
    {
        printf("%d not in tree\n", x);
        return temp;
    }
    if (temp->left != NILPTR)
        return maximum(temp->left);
    NODEPTR y = temp->parent;
    while (y != NILPTR && temp == y->left)
    {
        temp = y;
        y = y->parent;
    }
    return y;
}
void leftrotate(NODEPTR *treeroot, NODEPTR x)
{
    NODEPTR y = x->right;
    x->right = y->left;
    if (y->left != NILPTR)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NILPTR)
        *treeroot = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightrotate(NODEPTR *treeroot, NODEPTR y)
{
    NODEPTR x = y->left;
    y->left = x->right;
    if (x->right != NILPTR)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NILPTR)
        *treeroot = x;
    else if (y->parent->left == y)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void rbinsertfixup(NODEPTR *treeroot, NODEPTR z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            NODEPTR y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftrotate(treeroot,z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightrotate(treeroot,z->parent->parent);
            }
        }
        else
        {
            NODEPTR y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightrotate(treeroot,z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftrotate(treeroot,z->parent->parent);
            }
        }
    }
    (*treeroot)->color = BLACK;
}

void rbinsert(NODEPTR *treeroot, int z)
{
    NODEPTR Z = (NODEPTR) malloc(sizeof(struct node));
    Z->key = z;
    NODEPTR y = NILPTR;
    NODEPTR x = *treeroot;
    while (x != NILPTR)
    {
        y = x;
        if (Z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    Z->parent = y;
    if (y == NILPTR)
        *treeroot = Z;
    else if (Z->key < y->key)
        y->left = Z;
    else
        y->right = Z;
    Z->left = NILPTR;
    Z->right = NILPTR;
    Z->color = RED;
    rbinsertfixup(treeroot,Z);
}

void rbtransplant(NODEPTR *treeroot, NODEPTR u, NODEPTR v)
{
    if (u->parent == NILPTR)
        *treeroot = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

void rbdeletefixup(NODEPTR *treeroot, NODEPTR x)
{
    while (x != *treeroot && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            NODEPTR w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftrotate(treeroot,x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightrotate(treeroot,w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftrotate(treeroot,x->parent);
                x = *treeroot;
            }
        }
        else
        {
            NODEPTR w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightrotate(treeroot,x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftrotate(treeroot,w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightrotate(treeroot,x->parent);
                x = *treeroot;
            }
        }
    }
    x->color = BLACK;
}

void rbdelete(NODEPTR *treeroot, int z)
{
    NODEPTR Z = search(*treeroot, z);
    if (Z == NILPTR)
    {
        printf("Node to be deleted not found\n");
        return;
    }
    NODEPTR y = Z;
    int yoc = y->color;
    NODEPTR x;
    if (Z->left == NILPTR)
    {
        x = Z->right;
        rbtransplant(treeroot,Z,Z->right);
    }
    else if (Z->right == NILPTR)
    {
        x = Z->left;
        rbtransplant(treeroot,Z,Z->left);
    }
    else
    {
        y = minimum(Z->right);
        yoc = y->color;
        x = y->right;
        if (y->parent == Z)
            x->parent = y;
        else
        {
            rbtransplant(treeroot,y,y->right);
            y->right = Z->right;
            y->right->parent = y;
        }
        rbtransplant(treeroot,Z,y);
        y->left = Z->left;
        y->left->parent = y;
        y->color = Z->color;
    }
    if (yoc == BLACK)
        rbdeletefixup(treeroot,x);
}

main()
{
    NIL.left = NIL.right = NIL.parent = NILPTR;
    NIL.color = BLACK;
    NODEPTR tree = NILPTR;
    int n;
    while (1)
    {
        printf("1.Insert. 2.Search. 3.Print in ascending order.\n4.Minimum. 5.Maximum. 8.Delete. 9.Exit\n");
        scanf("%d", &n);
        if (n == 1)
        {
            printf("Enter any number: ");
            int num;
            scanf("%d", &num);
            rbinsert(&tree, num);
        }
        else if (n == 2)
        {
            printf("Enter the number to be search: ");
            int num;
            scanf("%d", &num);
            if (search(tree, num) == NILPTR)
            {
                printf("false.\n");
            }
            else
            {
                printf("true.\n");
                cout<<num<<' '<<colorrbt(search(tree,num),search(tree,num)->color)<<endl;
            }
        }
        else if (n == 3)
        {
            inorder(tree,NIL.color);
            printf("\n");
        }
        else if (n == 4)
            printf("%d %c\n", minimum(tree)->key, colorrbt(minimum(tree),minimum(tree)->color));
        else if (n == 5)
            printf("%d %c\n", maximum(tree)->key, colorrbt(maximum(tree),maximum(tree)->color));
        /*else if (n == 6)
        {
            printf("Enter the number whose successor needs to be found\n");
            int num;
            scanf("%d", &num);
            NODEPTR t = successor(tree, num);
            if (t != NULL)
                printf("%d\n", t->key);
        }
        else if (n == 7)
        {
            printf("Enter the number whose predecessor needs to be found\n");
            int num;
            scanf("%d", &num);
            NODEPTR t = predecessor(tree, num);
            if (t != NULL)
                printf("%d\n", t->key);
        }*/
        else if (n == 8)
        {
            printf("Enter the number to be deleted: ");
            int num;
            scanf("%d", &num);
            rbdelete(&tree, num);
        }
        else if(n==9)
        {
             break;
        }
    }
    return 0;
}
