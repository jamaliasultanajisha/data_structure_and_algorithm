#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;

#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

struct HeapItem
{
    char data;
    int freq;
    struct HeapItem *left, *right;
};

struct MinHeap
{
    int size;
    int capacity;
    struct HeapItem **array;
};

struct HeapItem* newNode(char data, int freq)
{
    struct HeapItem* temp = (struct HeapItem*) malloc(sizeof(struct HeapItem));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct HeapItem**)malloc(minHeap->capacity * sizeof(struct HeapItem*));
    return minHeap;
}

void swapMinHeapNode(struct HeapItem** a, struct HeapItem** b)
{
    struct  HeapItem* t = *a;
    *a = *b;
    *b = t;
}

void Heapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    {
        smallest = right;
    }
    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        Heapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}

struct HeapItem* removeMin(struct MinHeap* minHeap)
{
    struct HeapItem* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    Heapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct HeapItem* heapitem)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && heapitem->freq < minHeap->array[(i - 1)/2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = heapitem;
}

void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        Heapify(minHeap, i);
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

int isLeaf(struct HeapItem* root)
{
    return !(root->left) && !(root->right) ;
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct HeapItem* buildHuffmanTree(char data[], int freq[], int size)
{
    struct HeapItem *left, *right, *top;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap))
    {
        left = removeMin(minHeap);
        right = removeMin(minHeap);
        top = newNode(' ', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return removeMin(minHeap);
}

void printCodes(struct HeapItem* root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root))
    {
        printf("%c ", root->data);
        printArr(arr, top);
    }
}

void HuffmanCodes(char data[], int freq[], int size)
{
   struct HeapItem* root = buildHuffmanTree(data, freq, size);
   int arr[MAX_HEAP_SIZE], top = 0;
   printCodes(root, arr, top);
}

int main()
{
    int size;
     cin>>size;
     char arr[size];
     int freq[size];
     for(int i=0;i<size;i++)
     {
         cin>>arr[i]>>freq[i];
     }

    HuffmanCodes(arr, freq, size);
    return 0;
}
