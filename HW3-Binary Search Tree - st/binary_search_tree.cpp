#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}

struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==NULL)
    {
        return FALSE_VALUE;
    }
    else if(node!=NULL)
    {
        return (getSize(node->left)+1+getSize(node->right));
    }
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    if(node==NULL) return -1;
    if(node==root)
    {
        return 0;
    }

    int c=0;
    treeNode *temp;
    temp=root;

    while(temp->item!=node->item)
    {
        if(temp->item>node->item)
        {
            c++;
            temp=temp->left;
        }
        else if(temp->item<node->item)
        {
            c++;
            temp=temp->right;
        }


    }
    return c;
}


int calcDepth(int item)//return depth of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==NULL) return -1;
    else return calcNodeDepth(node);
}

int deleteItem(struct treeNode * node, int item)
{
    treeNode *temp, *temp1, *temp2, *parent=root;
    if(node==NULL) return FALSE_VALUE;
    temp=searchItem(root,item);
    //printf("%d",temp->item);
    if(temp==NULL)
    {
        return FALSE_VALUE;
    }
    if(temp==root)   return 0;
    /* while(parent->left!=temp && parent->right!=temp)
     {
         if(parent->item>item)
         {
             parent=parent->left;
         }
         else
         {
             parent=parent->right;
         }
     }*/
    if(temp->left==NULL && temp->right==NULL)
    {
        while(parent->left!=temp && parent->right!=temp)
        {
            if(parent->item>item)
            {
                parent=parent->left;
            }
            else
            {
                parent=parent->right;
            }
        }

        if(parent->left==temp)
        {
            parent->left=NULL;
        }
        else
        {
            parent->right=NULL;
        }
    }
    else if(temp->left!=NULL && temp->right==NULL)
    {
        while(parent->left!=temp && parent->right!=temp)
        {
            if(parent->item>item)
            {
                parent=parent->left;
            }
            else
            {
                parent=parent->right;
            }
        }

        if(parent->left==temp)
        {
            parent->left=temp->left;
        }
        else
        {
            parent->right=temp->left;
        }
    }
    else if(temp->left==NULL && temp->right!=NULL)
    {
        while(parent->left!=temp && parent->right!=temp)
        {
            if(parent->item>item)
            {
                parent=parent->left;
            }
            else
            {
                parent=parent->right;
            }
        }

        if(parent->right==temp)
        {
            parent->right=temp->right;
        }
        else
        {
            parent->right=temp->right;
        }
    }
    else if(temp->left!=NULL && temp->right!=NULL)
    {
        temp1=temp->right;
        if(temp1->left!=0)
        {
             while(temp1->left!=0)
            {
                temp1=temp1->left;
            }

         while(parent->left!=temp1 && parent->right!=temp1)
        {
            if(parent->item>item)
            {
                parent=parent->left;
            }
            else
            {
                parent=parent->right;
            }
        }

            temp->item=temp1->item;

            parent->left=NULL;
            free(temp1);
        }
        else
        {
            temp->item=temp1->item;
            free(temp1);
        }
    }


}



int getMinItem(struct treeNode *node) //returns the minimum item in the tree
{
    if(node==NULL)
    {
        return FALSE_VALUE;
    }
    while(node->left!=NULL)
    {
        node=node->left;
    }
    return node->item;
}

int getMaxItem(struct treeNode *node) //returns the maximum item in the tree
{
    if(node==NULL)
    {
        return -1;;
    }
    while(node->right!=NULL)
    {
        node=node->right;
    }
    return node->item;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    int cn=0;
    if(node==NULL)
    {
        return FALSE_VALUE;
    }
    cn=rangeSearch(node->left,leftBound,rightBound)+rangeSearch(node->right,leftBound,rightBound);

    if(node->item>=leftBound && node->item<=rightBound)
    {
        cn++;
    }
    if(node->item<leftBound)
    {
        return (rangeSearch(node->right,leftBound,rightBound));
    }
    if(node->item>rightBound)
    {
        return (rangeSearch(node->left,leftBound,rightBound));
    }
    return cn;
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0; i<height; i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit.\n");
        printf("8. Get size of tree. 9. Print depth of node.\n");
        printf("10. Print depth of a item. 11. Get min item. 12. Get max item.\n");
        printf("13. Search range.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            int d=deleteItem(root, item);
            printf("%d\n",d);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7)
        {
            exit(1);
        }
        else if(ch==8)
        {
            int siz = getSize(root);
            printf("Size of tree = %d\n", siz);
        }
        else if(ch==9)
        {
            int item;
            scanf("%d",&item);
            struct treeNode * res = searchItem(root, item);
            //  int depth= calcDepth(item);
            int depth = calcNodeDepth(res);
            printf("Depth of node = %d\n", depth);
        }
        else if(ch==10)
        {
            int item;
            scanf("%d", &item);
            int depth = calcDepth(item);
            printf("Depth of item %d = %d\n", item, depth);
        }
        else if(ch==11)
        {
            int min=getMinItem(root);
            printf("Min element of tree:%d\n",min);
        }
        else if(ch==12)
        {
            int max =getMaxItem(root);
            printf("Max element of tree:%d\n",max);
        }
        else if(ch==13)
        {
            int leftb,rightb;
            scanf("%d %d",&leftb,&rightb);
            int range= rangeSearch(root, leftb,rightb);
            printf("Number of items: %d\n",range);
        }
    }

}
