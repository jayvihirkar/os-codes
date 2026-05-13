#include<stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter number of resources: ");
    scanf("%d",&m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], finish[n], safe[n];

    printf("Enter Allocation Matrix:\n");

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);

    printf("Enter Max Matrix:\n");

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&max[i][j]);

    printf("Enter Available Resources:\n");

    for(i=0;i<m;i++)
        scanf("%d",&avail[i]);

    for(i=0;i<n;i++)
    {
        finish[i]=0;

        for(j=0;j<m;j++)
            need[i][j]=max[i][j]-alloc[i][j];
    }

    int count=0;

    while(count<n)
    {
        for(i=0;i<n;i++)
        {
            if(finish[i]==0)
            {
                int flag=0;

                for(j=0;j<m;j++)
                {
                    if(need[i][j]>avail[j])
                    {
                        flag=1;
                        break;
                    }
                }

                if(flag==0)
                {
                    safe[count]=i;
                    count++;

                    for(k=0;k<m;k++)
                        avail[k]+=alloc[i][k];

                    finish[i]=1;
                }
            }
        }
    }

    printf("Safe Sequence:\n");

    for(i=0;i<n;i++)
        printf("P%d ", safe[i]);

    return 0;
}