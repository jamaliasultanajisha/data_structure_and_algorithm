#include<bits/stdc++.h>
#include<cstdlib>
#include<cstdio>
#include<iostream>
using namespace std;
int NULL_VALUE=9999;
class array
{
public:
    int start,fin;
    bool operator < (const array& x) const
    {
        if (fin != x.fin)
            return fin < x.fin;
        return start < x.start;
    }
    bool operator =(int k)
    {
        start=k;
        fin=k;
    }
};
void Merge(array *carr,int left,int mid,int right)
{
    int count=0;
    int num1=mid-left+1;
    int num2=right-mid;
    array arr1[num1+1],arr2[num2+1];
    for(int i=1; i<=num1; i++)
    {
        arr1[i]=carr[left+i-1];
    }
    for(int i=1; i<=num2; i++)
    {
        arr2[i]=carr[mid+i];
    }
    arr1[num1+1]=NULL_VALUE;
    arr2[num2+1]=NULL_VALUE;
    int i=1,j=1;
    for(int k=left; k<=right; k++)
    {
        if(arr1[i]<arr2[j])
        {
            carr[k]=arr1[i];
            i++;
        }
        else
        {
            carr[k]=arr2[j];
            j++;
        }
    }
}
void Mergesort(array *carr,int left,int right)
{
    int mid;
    if(left<right)
    {
        mid=(left+right)/2;
        Mergesort(carr,left,mid);
        Mergesort(carr,mid+1,right);
        Merge(carr,left,mid,right);
    }
}
int main()
{
    int num;
    cin>>num;
    array *carr=new array[num+1];
    for(int i=1; i<=num; i++)
    {
        cin>>carr[i].start>>carr[i].fin;
    }
    Mergesort(carr,1,num);
    queue<int>q;
    int left=0;
    for(int i=1; i<=num; i++)
    {
        if(carr[i].start>=left)
        {
            q.push(i);
            left=carr[i].fin;
        }
    }
    cout<<q.size()<<endl;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        cout<<carr[x].start<<' '<<carr[x].fin<<endl;
    }
}
