#include <iostream>
using namespace std;
typedef struct {
	int i;
	int freq;
}gr;
void count_sort(gr A[],gr B[],int n)
{
	int C[n+1];
	int m;
	for(m=0;m<n+1;m++)
	{
		C[m]=0;
	}
	for(m=0;m<n;m++)
	{
		C[A[m].freq]++;
	}
	for(m=1;m<n+1;m++)
	{
		C[m]=C[m]+C[m-1];
	}
	for(m=n-1;m>=0;m--)
	{
		B[C[A[m].freq]-1]=A[m];
		C[A[m].freq]--;
	}
	for(m=0;m<n;m++)
	{
		A[m]=B[n-m-1];
	}
}
int friendship(gr A[],int **M,int n)
{
	gr B[n];
	int m,no,count=0,max;
	int sum=0,temp=n;
	for(m=0;m<n;m++)
	{
		sum=sum+A[m].freq;
	}
	if(sum%2!=0)
		return 0;
	else{
		while(temp>0)
		{
			count=0;
			for(m=0;m<temp;m++)
			{
				if(A[m].freq!=0)
				{
					A[count]=A[m];
					count++;
				}
			}
			temp=count;
			max=A[0].freq;
			for(m=1;m<temp;m++)
			{
				if(A[m].freq>max)
					max=A[m].freq;
			}
			if(max>temp)
				return 0;   
			else
				count_sort(A,B,temp);
			no=A[0].freq;   
			for(m=1;m<=no;m++)
			{
				M[(A[0].i-1)][(A[m].i-1)]=1;
				M[(A[m].i-1)][(A[0].i-1)]=1;
				A[0].freq--;
				A[m].freq--;
			}
		}
		return 1;
	}
}
void swap(gr* a, gr* b)
{
    gr t = *a;
    *a = *b;
    *b = t;
}
int partition (gr arr[], int low, int high)
{
    int pivot = arr[low].freq;    // pivot
    int i = (high + 1);  // Index of smaller element
    int j;
    for ( j = high; j >= low+1; j--)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j].freq >= pivot)
        {
            i--;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i - 1], &arr[low]);
    return (i - 1);
}
void quickSort(gr arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int handshake(gr A[], int **M,int n)
{
	gr B[n];
	int m,no,count=0,max;
	int sum=0,temp=n;
	for(m=0;m<n;m++)
	{
		sum=sum+A[m].freq;
	}
	if(sum%2!=0)
		return 0;
	else{
		while(temp>0)
		{
			count=0;
			for(m=0;m<temp;m++)
			{
				if(A[m].freq!=0)
				{
					A[count]=A[m];
					count++;
				}
			}
			temp=count;
			no=A[temp-1].freq;
			M[A[temp-1].i-1][A[0].i-1]=no;
			M[A[0].i-1][A[temp-1].i-1]=no;
			A[0].freq=A[0].freq-no;
			A[temp-1].freq=0;  
			for(m=1;m<temp-1;m++)
			{
				if(A[m].freq>A[0].freq)
					swap(&A[m],&A[0]);
			}
		}
		return 1;
	}
}
int main()
{
	int n,ind,j;
	cout<<"n:";
	cin>>n;
	cout<<"\nSequence:";
	gr A[n];
	int **M=new int*[n];
	for(ind=0;ind<n;ind++)
	{
		M[ind]=new int[n];
	}
	for(ind=0;ind<n;ind++)
	{
		cin>>A[ind].freq;
		A[ind].i=ind+1;
	}
	for(ind=0;ind<n;ind++)
	{
		for(j=0;j<n;j++)
		{
			M[ind][j]=0;
		}
	}
	int flag=friendship(A,M,n);
	if(flag==1)
	{
		cout<< "    ";
		for(ind=1;ind<=n;ind++)
		{
			cout<< ind<<"\t";
		}
		cout<< "Sum\n";
		for(ind=0;ind<n;ind++)
		{
			cout<< ind+1<<"    ";
			int sum=0;
			for(j=0;j<n;j++)
			{
				sum=sum+M[ind][j];
				cout<<M[ind][j]<<"\t";
			}
			cout<<sum<<"\n";
		}
	}
	else
		cout<< "Not a friendship sequence";
	gr A2[n];
	for(ind=0;ind<n;ind++)
	{
		cin>>A2[ind].freq;
		A2[ind].i=ind+1;
	}
	int **M2=new int*[n];
	for(ind=0;ind<n;ind++)
	{
		M2[ind]=new int[n];
	}
	for(ind=0;ind<n;ind++)
	{
		for(j=0;j<n;j++)
		{
			M2[ind][j]=0;
		}
	}
	quickSort(A2,0,n-1);
	flag=handshake(A2,M2,n);
	if(flag==1)
	{
		cout<< "    ";
		for(ind=1;ind<=n;ind++)
		{
			cout<< ind<<"\t";
		}
		cout<< "Sum\n";
		for(ind=0;ind<n;ind++)
		{
			cout<< ind+1<<"    ";
			int sum=0;
			for(j=0;j<n;j++)
			{
				sum=sum+M2[ind][j];
				cout<<M2[ind][j]<<"\t";
			}
			cout<<sum<<"\n";
		}
	}
}

