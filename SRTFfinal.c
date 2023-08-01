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
    printf(" \n\t\t\t SRTF\n\n");
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
    char r[n];
    printf("\t\tSRTF\n");
    printf("Sequence of Process Execution :- ");
	int rt[n];
	char flag='z';
	for (int i=0;i<n;i++)
		rt[i] = p[i].BT;
	int complete = 0, t = 0, shortest = 0, minm = 1000,check = 0;
	while (complete != n) 
    {
		for (int j=0;j<n;j++) 
        {
			if ((p[j].AT <= t) && (rt[j] < minm) && rt[j] > 0) 
            {
				minm = rt[j];
				shortest = j;
				check = 1;
                p[shortest].RT=t-p[shortest].AT;
			}
		}
		if(flag != p[shortest].Pid)
		{
		    printf(" %c ",p[shortest].Pid);
		    flag = p[shortest].Pid;
		}
		if (check == 0) 
        {
			t++;
			continue;
		}
		rt[shortest]--;
		minm = rt[shortest];
		if (minm == 0)
			minm = 1000;
		if (rt[shortest] == 0) 
        {
            r[complete]=p[shortest].Pid;
			complete++;
			check = 0;
			p[shortest].CT = t + 1;
			p[shortest].WT = p[shortest].CT-p[shortest].BT - p[shortest].AT;
			if (p[shortest].WT < 0)
				p[shortest].WT = 0;
		}
		t++;
	}
    for (int i=0;i<n;i++)
		p[i].TAT=p[i].BT+ p[i].WT;    
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