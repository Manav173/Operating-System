#include<stdio.h>

struct process
{
    char Pid;
    int AT,BT,CT,TAT,WT,RT;
};

void input(struct process *p,int n,char *PID)
{
    for(int i=0;i<n;i++)
    {
        printf("Enter the Process ID: ");
        scanf(" %c",&p[i].Pid);
        printf("Enter the AT: ");
        scanf("%d",&p[i].AT);
        printf("Enter the BT: ");
        scanf("%d",&p[i].BT);
        PID[i] = p[i].Pid;
    }
}

void output(struct process *p,int n,char *PID)
{
    float avgWT,avgTAT;
	int totalWT=0,totalTAT=0;
    printf(" \n\t\t\t FCFS\n\n");
    printf("PID \t AT \t BT \t CT \t TAT \t WT \t RT\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(PID[i] == p[j].Pid)
            {
                printf("%c \t ",p[j].Pid);
                printf("%d \t ",p[j].AT);
                printf("%d \t ",p[j].BT);
                printf("%d \t ",p[j].CT);
                printf("%d \t ",p[j].TAT);
                printf("%d \t ",p[j].WT);
                printf("%d \n",p[j].RT);
                totalWT += p[j].WT;
		        totalTAT += p[j].TAT;
            }
        }
    }
    avgWT=(float)totalWT / (float)n;
    avgTAT=(float)totalTAT / (float)n;
	printf("\nAverage waiting time = %.2f",avgWT);
	printf("\nAverage turn around time = %.2f",avgTAT);
}

void sortAT(struct process *p,int n)
{
    struct process temp;
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(p[j].AT < p[i].AT)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}

void calculate(struct process *p,int n)
{
    int sum=p[0].AT;
    for(int i=0;i<n;i++)
    {
        sum += p[i].BT;
        p[i].CT=sum;
        p[i].TAT=p[i].CT-p[i].AT;
        p[i].WT=p[i].TAT-p[i].BT;
    }
    p[0].RT=p[0].AT;
    for(int i=1;i<n;i++)
        p[i].RT=p[i-1].CT-p[i].AT;
}

int main()
{
    int n;
    printf("Enter the number of processes :- ");
    scanf("%d",&n);
    struct process p[n];
    char PID[n];
    input(p,n,&PID[0]);
    sortAT(p,n);
    calculate(p,n);
    output(p,n,PID);
}