#include<stdio.h>
#include<stdlib.h>

int merge(int arr1[], int arr2[], int asize);

int divide(int arr[],int n)
{
    int mid=n/2;
    int i=0,j=0,k=0,l=n-1;
    int arr1[i];
    int arr2[j];
    for(int i=0;i<mid;i++)
    {
        arr1[i++]=arr[k++];
    }
    for(int j=(n-mid-1);j<=mid;j--)
    {
        arr2[j--]=arr[l--];
    }
   return merge(arr1,arr2, mid);
}

int merge(int arr1[], int arr2[],  int asize)
{
    int i=0;
    int j=0;
    int k=asize-1;
    int l=0;
    int *temp = (int *)malloc(sizeof(int)*asize);
    while((i<asize))
    {
        temp[l++]=arr1[i++];
    }
    while(j<asize)
    {
        temp[k++]=arr2[j++];
    }
    for(int i=0;i<(l+k);i++)
    {
        printf("%d",temp[i]);
    }
}



main()
{
    int k;
    printf("no of array: ");
    scanf("%d",&k);
         int asize;
    printf("array size: ");
    scanf("%d",&asize);
    int n=k*asize;
    int arr[n];
    printf("enter the array:");
    for(int i=0; i<n; i++)
    {
        scanf("%d",&arr[i]);
    }
    int a=divide(arr,n);
}
