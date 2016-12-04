#include <iostream>
#include <cmath>
using namespace std;
typedef struct{
	int pos1;
	int pos2;
}res;
typedef struct{
	int pos1;
	int pos2;
	int min;
	int max;
}res2;
res compute(int B[],int S[],int start, int mid,int high,int C)
{
	res answer,left,right,cross;
	int max_left=0,max_right=0,min=B[start],max=0;
	left.pos1=start;
	left.pos2=start;
	right.pos1=mid+1;
	right.pos2=mid+1;
	cross.pos1=mid;
	cross.pos2=mid;
	for(int i=start;i<=mid;i++)
	{
		for(int j=i;j<=mid;j++)
		{
			if((floor(C/B[i])*(S[j]-B[i]))>max_left)
			{
				max_left=(floor(C/B[i])*(S[j]-B[i]));
				left.pos1=i;
				left.pos2=j;
			}
		}
	}
	for(int i=mid+1;i<=high;i++)
	{
		for(int j=i;j<=high;j++)
		{
			if((floor(C/B[i])*(S[j]-B[i]))>max_right)
			{
				max_right=(floor(C/B[i])*(S[j]-B[i]));
				right.pos1=i;
				right.pos2=j;
			}		
		}
	}
	for(int i=start+1;i<=mid;i++)
	{
		if(B[i]<min)
		{
			min=B[i];
			cross.pos1=i;
		}
	}
	for(int j=mid+1;j<=high;j++)
	{
		if(S[j]>max)
		{
			max=S[j];
			cross.pos2=j;
		}
	}
	if((floor(C/B[left.pos1])*(S[left.pos2]-B[left.pos1]))>(floor(C/B[right.pos1])*(S[right.pos2]-B[right.pos1])))
	{
		answer.pos1=left.pos1;
		answer.pos2=left.pos2;
	}
	else{
		answer.pos1=right.pos1;
		answer.pos2=right.pos2;
	}
	if((floor(C/B[cross.pos1])*(S[cross.pos2]-B[cross.pos1]))>(floor(C/B[answer.pos1])*(S[answer.pos2]-B[answer.pos1]))){
		answer.pos1=cross.pos1;
		answer.pos2=cross.pos2;
	}
	return answer;
}	 
res split(int B[],int S[],int start,int end,int C)
{
	res fin;
	int mid;
	if(start==end)
	{
		if((floor(C/B[start])*(S[start]-B[start]))>0)
		{
			fin.pos1=start;
			fin.pos2=start;
			return fin;
		}
	}
	else{
		mid=(start+end)/2;
		fin=split(B,S,start,mid,C);
		fin=split(B,S,mid+1,end,C);
		fin=compute(B,S,start,mid,end,C);
		return fin;
	}
	
}
void singletrans1(int B[],int S[],int n,int C)
{
	res ans;
	ans=split(B,S,0,n-1,C);
	cout<<"+++Single trans1\n";
	cout<< "Buying date= "<<ans.pos1<<" Buying Rate= "<<B[ans.pos1]<<"\n";
	cout<<"Selling Date= "<<ans.pos2<<" Selling rate= "<<S[ans.pos2]<<"\n";
	cout<< "Maximum Profit= "<< (floor(C/B[ans.pos1])*(S[ans.pos2]-B[ans.pos1]))<<"\n";
}
res2 compute2(int B[],int S[],int start, int mid,int high,int C,res2 fin)
{
	res2 answer,left,right,cross;
	int max_left=0,max_right=0,min=B[start],max=0;
	left.pos1=start;
	left.pos2=start;
	right.pos1=mid+1;
	right.pos2=mid+1;
	cross.pos1=mid;
	cross.pos2=mid;
	for(int i=start;i<=mid;i++)
	{
		for(int j=i;j<=mid;j++)
		{
			if((floor(C/B[i])*(S[j]-B[i]))>max_left)
			{
				max_left=(floor(C/B[i])*(S[j]-B[i]));
				left.pos1=i;
				left.pos2=j;
			}
		}
	}
	for(int i=mid+1;i<=high;i++)
	{
		for(int j=i;j<=high;j++)
		{
			if((floor(C/B[i])*(S[j]-B[i]))>max_right)
			{
				max_right=(floor(C/B[i])*(S[j]-B[i]));
				right.pos1=i;
				right.pos2=j;
			}		
		}
	}
	/*for(int i=start+1;i<=mid;i++)
	{
		if(B[i]<min)
		{
			min=B[i];
			cross.pos1=i;
		}
	}
	for(int j=mid+1;j<=high;j++)
	{
		if(S[j]>max)
		{
			max=S[j];
			cross.pos2=j;
		}
	}*/
	if((floor(C/B[left.pos1])*(S[left.pos2]-B[left.pos1]))>(floor(C/B[right.pos1])*(S[right.pos2]-B[right.pos1])))
	{
		answer.pos1=left.pos1;
		answer.pos2=left.pos2;
	}
	else{
		answer.pos1=right.pos1;
		answer.pos2=right.pos2;
	}
	if((floor(C/fin.min)*(fin.max-fin.min))>(floor(C/B[answer.pos1])*(S[answer.pos2]-B[answer.pos1]))){
		answer.pos1=fin.min;
		answer.pos2=fin.max;
	}
	return answer;
}	 
res2 split2(int B[],int S[],int start,int end,int C)
{
	res2 fin;
	fin.min=B[start];
	fin.max=S[end];
	int mid;
	if(start==end)
	{
		if((floor(C/B[start])*(S[start]-B[start]))>0)
		{
			fin.pos1=start;
			fin.pos2=start;
			fin.min=B[start];
			fin.max=S[start];
			return fin;
		}
	}
	else{
		mid=(start+end)/2;
		if(B[start]<fin.min)
			fin.min=B[start];
		if(S[mid]>fin.max)
			fin.max=S[mid];
		fin=split2(B,S,start,mid,C);
		if(B[mid+1]<fin.min)
			fin.min=B[mid+1];
		if(S[end]>fin.max)
			fin.max=S[end];
		fin=split2(B,S,mid+1,end,C);
		fin=compute2(B,S,start,mid,end,C,fin);
		return fin;
	}
	
}
void singletrans2(int B[],int S[],int n,int C)
{
	res2 ans;
	ans=split2(B,S,0,n-1,C);
	cout<<"\n\n+++Singletrans2\n";
	cout<< "Buying date= "<<ans.pos1<<" Buying Rate= "<<B[ans.pos1]<<"\n";
	cout<<"Selling Date= "<<ans.pos2<<" Selling rate= "<<S[ans.pos2]<<"\n";
	cout<< "Maximum Profit= "<< (floor(C/B[ans.pos1])*(S[ans.pos2]-B[ans.pos1]))<<"\n";
}
void print(int B[],int S[],int B2[],int S2[],int Cost[],int i)
{
	if(B2[i]==-1)
	{
		cout<< "Initial Capital="<<Cost[i]<<"\n\n";
		return;
	}
	else{
		print(B,S,B2,S2,Cost,B2[i]-1);
		cout<< "Buying Date= "<<B2[i]-1<<", Buying Rate= "<<B[B2[i]-1]<<"\n";
		cout<<"Selling Date= "<<S2[i]-1<<", Selling rate= "<<S[S2[i]-1]<<"\n";
		cout<<"Current Capital= "<<Cost[i]<<"\n\n";
	}
}
void multitrans(int B[],int S[],int n,int C)
{
	int B2[n+1],S2[n+1],Cost[n+1];
	int i,j,cm;
	B2[0]=-1;
	S2[0]=-1;
	Cost[0]=C;
	for(i=1;i<=n;i++)
	{
		Cost[i]=Cost[i-1];
		B2[i]=B2[i-1];
		S2[i]=S2[i-1];
		for(j=0;j<=i-1;j++)
		{
			cm=Cost[j]+(Cost[j]/B[j])*(S[i-1]-B[j]);
			if(cm>Cost[i])
			{
				Cost[i]=cm;
				B2[i]=j+1;
				S2[i]=i;
			}
		}
	}
	cout <<"\n\n+++Multiple Transactions\n";
	print(B,S,B2,S2,Cost,n);
}
int main()
{
	int n,i,C;
	cout<<"+++n=";
	cin>>n;
	cout<<"\n";
	int B[n],S[n];
	cout<<"+++Buying Prices :";
	for(i=0;i<n;i++)
	{
		cin>>B[i];
	}
	cout<<"\n"<<"+++Selling Prices :";
	for(i=0;i<n;i++)
	{
		cin>>S[i];
	}
	cout<<"\n"<<"C=";
	cin>>C;
	singletrans1(B,S,n,C);
	singletrans2(B,S,n,C);
	multitrans(B,S,n,C);
}

