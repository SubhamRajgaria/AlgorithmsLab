#include <iostream>
#include <cmath>
using namespace std;
typedef struct {
	int i,j;
}indexpair;
int left(int i)
{
	return 2*i;
}
int right(int i)
{
	return (2*i+1);
}
int parent(int i)
{
	return floor(i/2);
}
void MIN_HEAPIFY(int arr[],int i,int length)
{
	int l=left(i);
	int r=right(i);
	int minimum;
	if(l<=length && arr[l]<arr[i])
	{
		minimum=l;
	}
	else 
		minimum=i;
	if(r<=length && arr[r]<arr[minimum])
		minimum=r;
	if(minimum!=i)
	{
		int t=arr[i];
		arr[i]=arr[minimum];
		arr[minimum]=t;
		MIN_HEAPIFY(arr,minimum,length);
	}
}
void buildheap(int arr[],int l)
{
	int i;
	for(i=floor(l/2);i>=1;i--)
	{
		MIN_HEAPIFY(arr,i,l);
	}
}
int extractmin(int S[],int l)
{
	if(l<1)
		cout << "Error undeflow\n";
	int min=S[1];
	S[1]=S[l];
	l--;
	MIN_HEAPIFY(S,1,l);
	return min;
}
void method1(int A[],int B[], int m, int n, int k)
{
	int S[m*n+1];
	int i,j,count=1;
	int l=m*n;
	for(i=1;i<m+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			S[count]=A[i]+B[j];
			count++;
		}
	}
	buildheap(S,m*n);
	cout<< "\n +++ Method 1:\n";
	for(j=1;j<=k;j++)
	{
		int min=extractmin(S,l);
		cout << min << " ";
		l--;
	}
	cout << endl;
}
void MIN_HEAPIFY_Q(indexpair arr[],int c,int length,int A[],int B[])
{
	if(c==1)
		return;
	int p=parent(c);
	if((A[arr[p].i]+B[arr[p].j])>(A[arr[c].i]+B[arr[c].j]))
	{
		indexpair t=arr[p];
		arr[p]=arr[c];
		arr[c]=t;
		MIN_HEAPIFY_Q(arr,p,length,A,B);
	}
}
void MIN_HEAPIFY_Q2(indexpair arr[],int c,int length,int A[],int B[])
{
	int l=left(c);
	int r=right(c);
	int minimum;
	if(l<=length && (A[arr[l].i]+B[arr[l].j])<(A[arr[c].i]+B[arr[c].j]))
	{
		minimum=l;
	}
	else 
		minimum=c;
	if(r<=length && (A[arr[r].i]+B[arr[r].j])<(A[arr[c].i]+B[arr[c].j]))
		minimum=r;
	if(minimum!=c)
	{
		indexpair t=arr[c];
		arr[c]=arr[minimum];
		arr[minimum]=t;
		MIN_HEAPIFY_Q2(arr,minimum,length,A,B);
	}
}
void insertQ(indexpair Q[],int *l, indexpair a,int A[],int B[])
{
	Q[(*l)-1]=a;
	MIN_HEAPIFY_Q(Q,*l-1,*l-1,A,B);
}
indexpair extractQ(indexpair Q[],int A[],int B[],int l)
{
	if(l<1)
		cout << "Error undeflow\n";
	indexpair min=Q[1];
	cout << min.i << " " << min.j<< "\n";
	Q[1]=Q[l];
	l--;
	MIN_HEAPIFY_Q2(Q,1,l,A,B);
	return min;
}
void method2(int A[],int B[],int m,int n,int k)
{
	int q_length=2;
	buildheap(A,m);   
	buildheap(B,n); //breakpoint 120
	int i;
	cout << "\n";
	indexpair Q[8*k+2];  //breakpoint 121
	indexpair a,b;
	a.i=1;
	a.j=1;
	insertQ(Q,&q_length,a,A,B);
	cout << A[Q[1].i]+B[Q[1].j] << "= A[" << Q[1].i <<"] + B["<<Q[1].j << "]\n";
	int count=1;
	cout << "+++ Method 2\n";
	while(count <=k)
	{
		indexpair min=extractQ(Q,A,B,q_length-1);
		if(min.i==a.i && min.j==a.j)
			continue;
		else{
			count++;
			cout << A[min.i]+B[min.j] << "= A[" << min.i <<"] + B["<<min.j << "] \n";
			a.i=min.i;
			a.j=min.j;
			q_length++;
			if(2*(a.i)<=m && (2*(a.i)+1)<=m && 2*(a.j)<=n && (2*(a.j)+1)<=n)
			{
				b.i=a.i;
				b.j=2*(a.j);
				insertQ(Q,&q_length,b,A,B);
				q_length++;
				b.j=b.j+1;
				insertQ(Q,&q_length,b,A,B);
				q_length++;
				b.i=2*(a.i);
				b.j=a.j;
				insertQ(Q,&q_length,b,A,B);
				q_length++;
				b.i=(b.i)+1;
				insertQ(Q,&q_length,b,A,B);
			}
		}
	}
}
int main()
{
	int m,n,k;
	int i;
	cout << "m=";
	cin>> m;
	int A[m+1];
	cout << "\n" <<"+++ Array A:\n";
	for(i=1;i<m+1;i++)
	{
		cin >> A[i];
	}
	cout <<"\n" << "n=";
	cin >> n;
	int B[n+1];
	cout << "\n" << "+++ Array B:\n";
	for(i=1;i<n+1;i++)
	{
		cin >> B[i];
	}
	cout << "\nk= ";
	cin >> k;
	method1(A,B,m,n,k);
	method2(A,B,m,n,k);
	cout << "+++ Re-reading arrays\n";
	cout << "Array A: \n";
	for(i=1;i<m+1;i++)
	{
		cin >> A[i];
	}
	cout << "+++ Array B:\n";
	for(i=1;i<n+1;i++)
	{
		cin >> B[i];
	}
	method1(A,B,m,n,k);
}
