//program1 in c++ by Rishabh Rai(11704013)
//K17PD


/*Q>.  A uniprocessor system has n number of CPU intensive processes,
 each process has its own requirement of CPU burst. The process with
lowest CPU burst is given the highest priority. A late-arriving higher
priority process can preempt a currently running process with lower priority.
Simulate a scheduler that is scheduling the processes in such a way
that higher priority process is never starved due to the execution
 of lower priority process. What should be its average waiting
time and average turnaround time if no two processes are arriving are
 arriving at same time.

*/

#include<iostream>
#include<stdio.h>
using namespace std;
void swap(int* a,int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}



int main()
{
	int n,i,j,k;
	float waitingtime=0,tatime=0; //total waiting and turn around time
	//declaring variables
	int arrival_t[20],burst_t[20],finish_t[20],process_n[20],tat[20],waiting_t[20],
	finished[20],remaining[20],priority[20];
	cout<<"Enter the number of processes: ";
	cin>>n;

	//taking arrival time and burst time for n processes and initialing isFinished to false and remaining time to burst time
	cout<<"Enter Arrival, Burst Time  of processes: \n";
	for(i=0;i<n;i++)
	{
		process_n[i]=i+1;
		cin>>arrival_t[i]>>burst_t[i];
		finished[i]=0;
		remaining[i]=burst_t[i];

	}
     //calculating priority on basis of burst time
     for( i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(burst_t[j]>burst_t[j+1])
			{
				swap(&arrival_t[j],&arrival_t[j+1]);
				swap(&burst_t[j],&burst_t[j+1]);
				swap(&process_n[j],&process_n[j+1]);
			}
		}

	}
	for(i=0;i<n;i++)
    {
        priority[i]=i+1;   //assigning priority  based on burst time
    }
	//sorting the processes on ascending order of arrival time

	for( i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(arrival_t[j]>arrival_t[j+1])
			{
				swap(&arrival_t[j],&arrival_t[j+1]);
				swap(&burst_t[j],&burst_t[j+1]);
				swap(&process_n[j],&process_n[j+1]);
				swap(&priority[j],&priority[j+1]);
			}
		}

	}




	int total_time,all_fin=0;
	int min;
	int pos=0,flag=0;

	 total_time=arrival_t[0];


	//while all processes are not finished, find the process with
	//lowest ie highest priority and process it.At each interval keep
	// checking the upcoming processes for higher priority
	//total_time----total time elapsed
	while(!all_fin)
	{
		min=99999;
		flag=0;
		for(j=0;j<n;j++)
		{
		   //checking for process that has arrived but not yet
		   // finished (having highest priority at that time)
		    if(arrival_t[j]<=total_time && finished[j]==0 && priority[j]<min)
		    {
		        min=priority[j];
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
                    total_time=arrival_t[i];
                    break;
                }
		    }

		}
		else
		{
			total_time++;
			remaining[pos]--;

			if(remaining[pos]==0)
			{

				finished[pos]=1;
				finish_t[pos]=total_time;
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

	//calculating total turn around time, waiting time,
	// totat waiting time and total turn around time using basic formule
	for(i=0;i<n;i++)
	{
		tat[i]=finish_t[i]-arrival_t[i];
		waiting_t[i]=tat[i]-burst_t[i];
		waitingtime+=waiting_t[i];
		tatime+=tat[i];
	}


	//printing result
	cout<<"Process \t AT \t BT \t P \t FT \t TAT \t WT\n";
	for(i=0;i<n;i++)
		cout<<"P"<<process_n[i]<<" \t\t "<<arrival_t[i]<<" \t "<<burst_t[i]
		<<" \t "<<priority[i]<<" \t "<<finish_t[i]<<" \t "<<tat[i]<<" \t "
		<<waiting_t[i]<<"\n";

	//printing avg turnaround time and avg waiting time
	cout<<"\nAverage TAT: "<<tatime<<endl;
	cout<<"Average WT: "<<waitingtime/n;
}
