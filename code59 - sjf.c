#include <stdio.h> 
int main()
{
int pid[5] = {1,2,3,4,5};
int at[5] = {1,3,6,7,9};
int bt[5] = {7,3,2,10,8};
int ct[5], wt[5], tat[5], completed[5]={0}; int n=5, time=0, completedCount=0, temp;


for(int i=0; i<n-1; i++)
{
for(int j=0; j<n-i-1; j++)
{
if(at[j]>at[j+1])
{
temp=at[j]; at[j]=at[j+1]; at[j+1]=temp;

temp=bt[j]; bt[j]=bt[j+1]; bt[j+1]=temp;

temp=pid[j]; pid[j]=pid[j+1]; pid[j+1]=temp;
}
}
}
while(completedCount<n)
{
int idx=-1, min_bit=9999;
for(int i=0; i<n; i++)
{
if(!completed[i] && at[i]<= time && bt[i]<min_bit)
{
min_bit=bt[i]; idx=i;
}
}
if(idx==-1)
{
time++;
}
else
{
 
time+=bt[idx]; ct[idx]=time; tat[idx]=ct[idx]-at[idx];
wt[idx]=tat[idx]-bt[idx]; completed[idx]=1; completedCount++;
}
}



printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n"); for(int i=0; i<n; i++)
{
printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
}

float atat=0.0, awt=0.0; for(int i=0; i<n; i++)
{
atat+=tat[i]; awt+=wt[i];
}
printf("ATAT = %f, AWT = %f", atat/n, awt/n);

return 0;
}
