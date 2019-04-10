#include<stdio.h>

int main()
{
	int n,i,j,k;
	/*
	at---arrival time
	bt--burst time
	ft---finish time
	tat---turn around time
	rm---remaining time
	finished----to check if process is finished
	*/
	int at[20],bt[20],ft[20],pn[20],tat[20],wt[20],finished[20],rm[20],priority[20];
	printf("Enter the number of processes: ");
	scanf("%d",&n);

	//taking arrival time and burst time for n processes and initialing isFinished to false and remaining time to burst time
	printf("Enter at, bt and priority of processes: \n");
	for(i=0;i<n;i++)
	{
		pn[i]=i+1;
		scanf("%d %d %d",&at[i],&bt[i],&p[i]);
		finished[i]=0;
		rm[i]=bt[i];

	}
	
	
	//sorting the processes on arrival time(ascending order)
	
	for( i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(at[j]>at[j+1])
			{
				swap(&at[j],&at[j+1]);
				swap(&bt[j],&bt[j+1]);
				swap(&pn[j],&pn[j+1]);
			}
		}

	}

	
	
	int total_time,all_fin=0;
	int min;
	int pos=0,flag=0;

	 total_time=at[0];


	//while all processes are not finished, find the process with lowest ie highest priority and process it.At each interval keep checking the upcoming processes for higher priority
	//total_time----total time elapsed
	while(!all_fin)
	{
		min=99999;
		flag=0;
		for(j=0;j<n;j++)
		{
		   //checking for process that has arrived but not yet finished (having highest priority at that time)
		    if(at[j]<=total_time && finished[j]==0 && p[j]<min)
		    {
		        min=p[i];
		        pos=j;
		        flag=1;
		    }

		}
		if(!flag)
		{
		    for(i=0;i<n;i++)
		    {
                 if(finished[i]==0)
                {
                    total_time=at[i];
                    break;
                }
		    }

		}
		else
		{
			total_time++;
			rm[pos]--;

			if(rm[pos]==0)
			{

				finished[pos]=1;
				ft[pos]=total_time;
			}
		}
		all_fin=1;
			for(i=0;i<n;i++)
		{
			if(finished[i]==0)
			{
				all_fin=0;
				break;
			}
		}


	}
	printf("\n");
	
	//total_wt---total waiting time
	//total_tat--total turn around time

	float total_wt=0,total_tat=0;
	
	//calculating total turn around time, waiting time, totat waiting time and total turn around time using basic formule
	for(i=0;i<n;i++)
	{
		tat[i]=ft[i]-at[i];
		wt[i]=tat[i]-bt[i];
		total_wt+=wt[i];
		total_tat+=tat[i];
	}
	

	//printing arrival time, burst time, finish time, turn around time and waiting time for all processes in tabular form
	printf("Process \t AT \t BT \t p \t FT \t TAT \t WT\n");
	for(i=0;i<n;i++)
		printf("P%d \t\t %d \t %d \t %d \t\t %d \t %d \t %d\n",pn[i],at[i],bt[i],p[i],ft[i],tat[i],wt[i]);

	//calculating average turn around time and average waiting time
	printf("\nAverage TAT: %f\n",total_tat/n);
	printf("Average WT: %f\n",total_wt/n);
}
