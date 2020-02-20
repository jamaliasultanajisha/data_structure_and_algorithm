#include <iostream>
#include <stdio.h>
#include <string.h>
#define INFINITY 99999

using namespace std;

int value, n;
int coins[100], count[100];
int darray[100][100];
int optarray[100][100];

int coinchange(int cur, int sum)
{
    int ans = INFINITY;

    if(sum == value)
    {
        return 0;
    }

    if(sum>value || cur == n)
        return INFINITY;

    if(darray[cur][sum] != -1) {
        return darray[cur][sum];
    }
   	int temp;
    for (int j = 0; j <= count[cur] and (j * coins[cur]) + sum <= value; j++)
	{
        temp = coinchange(cur+1, sum + j * coins[cur]) + j;

        if(temp<ans)
        {
        	ans=temp;
        	optarray[cur][sum]=j;
		}
    }
    return darray[cur][sum] = ans;

}

int main()
{
        int cur;
        scanf("%d", &value);
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
		{
            scanf("%d", &coins[i]);
        }

        for (int i = 0; i < n; i++)
		{
            scanf("%d", &count[i]);
        }

        memset(darray, -1, sizeof(darray));
        memset(optarray, 0, sizeof(optarray));

        printf("%d\n", coinchange(0, 0));
        int sum=0, stage=0;
		while(sum<value)
		{
			if(optarray[stage][sum]!=0)
			printf("%d*%d\n", coins[stage], optarray[stage][sum]);
			sum+=coins[stage]*optarray[stage][sum];
			stage++;
		}
		if(value==0)
        {
            printf("not possible\n");
        }
        if(sum>value || cur==n)
        {
            printf("not possible\n");
        }
    return 0;
}
