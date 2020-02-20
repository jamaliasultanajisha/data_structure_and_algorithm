#include<iostream>
#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>

#define MAXSIZE 200
#define NULL_VALUE 100000

using namespace std;

class setcoverproblem{
    class Node{
    public:
        int n;
        int remain;
        int settake;
        int bound;
        int level;

        Node *left;
        Node *right;
        Node *parent;

        bool *covered;

        Node(int number, int remelement, int setno, int bnd, int lvl, Node *lf, Node* rt, Node *pt, bool *cvr){
            n = number;
            remain = remelement;
            settake = setno;
            bound = bnd;
            level = lvl;

            left = lf;
            right = rt;
            parent = pt;

            covered = new bool[n+5];
            if(cvr!=NULL){
                for(int i=0; i<n+5; i++){
                    covered[i] = cvr[i];
                }
            }
            else{
                for(int i=0; i<n+5; i++){
                    covered[i] = false;
                }
            }
        }
    };
    class comparison{
        bool reverse;
    public:
        comparison(const bool& minqueue=true)
        {
            reverse=minqueue;
        }
        bool operator() (const Node* lhs, const Node*rhs) const
        {
            if (reverse) return (lhs->bound>rhs->bound);
            else return (lhs->bound<rhs->bound);
        }
    };

    int n, m;
    vector <int> *arr;

    int Bound(Node *node)
    {
        int maxcard = 1;
        for(int i=node->level; i<m; i++){
            if(maxcard<arr[i].size()){
                maxcard = arr[i].size();
            }
        }
        int bound = node->settake + ceil(1.0*node->remain / maxcard );

        return bound;
    }
    void print(Node *node){
        if(node==NULL || node->level==0)
        {
            return;
        }
        print(node->parent);

        if(node->parent!=NULL && node == node->parent->right){
            int level = node->level;
          cout<<"Set "<<level<<": ";

            for(int i=0; i<arr[level-1].size(); i++)
            {
               cout<<arr[level-1].at(i)<<' ';
            }
            cout<<endl;
        }
        return;
    }
public:
    setcoverproblem()
    {
        FILE *fp;
        fp= fopen("input.txt", "r");
        if(fp==NULL){
            printf("ERROR OPENING FILE\n");
            return ;
        }
        fscanf(fp, "%d %d", &n, &m);

        arr = new vector<int>[m];

        char *str = new char[MAXSIZE];
        fgets(str, MAXSIZE, fp);

        for(int i=0; i<m; i++){
            fgets(str, MAXSIZE, fp);
            int num;
            char s[10];
            cout<<"Subset "<<i+1<<": ";
            while (sscanf(str, "%d", &num)!=EOF){
               cout<<num<<' ';
                arr[i].push_back(num);
                itoa(num, s, 10);
                str+= strlen(s)+1;
            }
            cout<<endl;
        }
    }
    int mincover(){
        Node *root = new Node(n, n, 0, 0, 0, NULL, NULL, NULL, NULL);

        priority_queue <Node*, vector <Node*>, comparison > queue;
        queue.push(root);

        while (!queue.empty()){
            Node *temp = queue.top();
            queue.pop();

            if(temp==NULL){
                break;
            }

            printf("Found node : level = %d, bound = %d, remaining=%d, sets taken=%d\n", temp->level, temp->bound, temp->remain, temp->settake);

            if(temp->remain==0)
            {
                cout<<"Set Cover: "<<endl;
                print(temp);
                return temp->settake;
            }
            else if(temp->level == m){
                continue;
            }

            Node *leftNode = new  Node(n, temp->remain, temp->settake, temp->bound, temp->level+1, NULL, NULL, temp, temp->covered);
            Node *rightNode = new  Node(n, temp->remain, temp->settake+1, temp->bound, temp->level+1, NULL, NULL, temp, temp->covered);

            int level = rightNode->level;
            for(int i=0; i<arr[level-1].size(); i++)
            {
                //printf("here %d %d\n", i, arr[level-1].size());
                if(!rightNode->covered[arr[level-1].at(i)] )
                {
                    rightNode->remain--;
                    rightNode->covered[arr[level-1].at(i)] = true;
                }
            }

            int br = Bound(rightNode);
            rightNode->bound = br;

            br = Bound(leftNode);
            leftNode->bound = br;

            queue.push(leftNode);
            queue.push(rightNode);

            temp->left = leftNode;
            temp->right = rightNode;
        }
        return NULL_VALUE;
    }

};

int main()
{
    setcoverproblem *setcover = new setcoverproblem();

    int res = setcover->mincover();

    if(res == NULL_VALUE)
    {
        printf("not possible\n");
    }
    else
    {
        printf("Min number of sets for the set cover = %d\n", res);
    }
    return 0;
}
