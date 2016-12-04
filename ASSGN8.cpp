#include <iostream>
#include <cmath>
using namespace std;
typedef struct{
int data;
int pos;
}deposit;
void merge(int arr[], int ind[],int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
    int L2[n1],R2[n2];
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
	L2[i]=ind[l+i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1+ j];
	R2[j]=ind[m+1+j];
    }
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
	    ind[k]=L2[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
	    ind[k]=R2[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
	ind[k]=L2[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        ind[k]=R2[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int ind[],int l, int r)
{
    int m;
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr,ind, l, m);
        mergeSort(arr,ind, m+1, r);
        merge(arr,ind, l, m, r);
    }
}
void mineffort1(int a[],int ind[],int n)
{
	int i,G[n],total;
	mergeSort(a,ind,0,n-1);
	cout<< "+++Part 1\n";
	G[0]=a[0];
	total=G[0];
	cout<< "Floor(0):Adding w["<< ind[0]<<"] = "<<a[0]<<" to bag, G[ 0] ="<<G[0]<<"\n";
	for(i=1;i<n;i++)
	{
		G[i]=G[i-1]+a[i];
		total=total+G[i];
		cout<< "Floor("<<i<< "):Adding w["<< ind[i]<<"] = "<<a[i]<<" to bag, G[ "<<i<<"] ="<<G[i]<<"\n";
	}
	cout<< "---Total effort="<<total<<"\n";
}
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
void MIN_HEAPIFY(deposit arr[],int i,int length)
{
	int l=left(i);
	int r=right(i);
	int minimum;
	if(l<=length && arr[l].data<arr[i].data)
	{
		minimum=l;
	}
	else 
		minimum=i;
	if(r<=length && arr[r].data<arr[minimum].data)
		minimum=r;
	if(minimum!=i)
	{
		int t=arr[i].data;
		arr[i].data=arr[minimum].data;
		arr[minimum].data=t;
		MIN_HEAPIFY(arr,minimum,length);
	}
}
void buildheap(deposit arr[],int l)
{
	int i;
	for(i=floor(l/2);i>=1;i--)
	{
		MIN_HEAPIFY(arr,i,l);
	}
}
deposit extractmin(deposit S[],int l)
{
	if(l<1)
		cout << "Error undeflow\n";
	deposit min=S[1];
	S[1]=S[l];
	MIN_HEAPIFY(S,1,l);
	return min;
}
void mineffort2(int a[],int ind[],int n)
{
	int i,j,G[n],total,count=0;
	deposit depo[n],min,temp1,temp2;
	cout<< "+++Part 2\n";
	G[0]=a[0];
	cout<<"Floor( 0): Adding w["<<ind [0]<<"] = "<<a[0]<<" to bag, G[ 0] ="<<G[0]<<"\n";
	G[1]=G[0]+a[1];
	cout<<"Floor( 1): Adding w["<<ind [1]<<"] = "<<a[1]<<" to bag, G[ 1] ="<<G[1]<<"\n";
	total=G[0]+G[1];
	j=2;
	for(i=2;i<n ;i++)
	{
		if(G[i-1]<a[j])
		{
			if(count>0)
			{
				if(depo[1].data<a[j]){
					min=extractmin(depo,count);
					count--;
					G[i]=G[i-1]+min.data;
					cout<< "Floor( "<<i<<"): Adding G[ "<<min.pos<<"] = "<<min.data<< "            G[ "<<i<<"] = "<<G[i]<<"\n";
				}
				else{
					G[i]=G[i-1]+a[j];
					cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<< "G[ "<<i<<"] = "<<G[i]<<"\n";
					j++;
				}

			}
			else{
				G[i]=G[i-1]+a[j];
				cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<< "G[ "<<i<<"] = "<<G[i]<<"\n";
				j++;
			}
		}
		else{
			if(count>1)
			{
				temp1=depo[1];
				temp2=depo[2];
				if(temp1.data<a[j])
				{
					if(temp2.data<a[j])
					{
						min=extractmin(depo,count);
					        count--;
						int t=min.pos,p=min.data;
						G[i]=min.data;
						min=extractmin(depo,count);
						count--;
						G[i]=G[i]+min.data;
						count++;
						depo[count].data=G[i-1];
						depo[count].pos=i-1;
						buildheap(depo,count);
						cout<<"Floor( "<<i<<"): Depositing G["<<i-1<<"] ="<< G[i-1]<<"\n";
						cout<< "Floor( "<<i<<"): Adding G[ "<<min.pos<<"] = "<<min.data<< ",G["<<t<<"]="<<p<<      "G[ "<<i<<"] = "<<G[i]<<"\n";

					}
					else{
						min=extractmin(depo,count);
					        count--;
						G[i]=min.data+a[j];
						count++;
						depo[count].data=G[i-1];
						depo[count].pos=i-1;
						buildheap(depo,count);
						cout<<"Floor( "<<i<<"): Depositing G["<<i-1<<"] ="<< G[i-1]<<"\n";
						cout<< "Floor( "<<i<<"): Adding G[ "<<min.pos<<"] = "<<min.data<< "to bag,w["<<ind[j]<<"] ="<<a[j]<< "G[ "<<i<<"] = "<<G[i]<<"\n";
						j++;
					}
						
				}
				else{
					temp1=depo[1];
					if(G[i-1]>temp1.data)
					{
						if(temp1.data<a[j+1])
						{
							min=extractmin(depo,count);
							count--;
							G[i]=min.data+a[j];
							count++;
							depo[count].data=G[i-1];
							depo[count].pos=i-1;
							buildheap(depo,count);
							cout<<"Floor( "<<i<<"): Depositing G["<<i-1<<"] ="<< G[i-1]<<"\n";
						cout<< "Floor( "<<i<<"): Adding G[ "<<temp1.pos<<"] = "<<temp1.data<< "to bag,w["<<ind[j]<<"] ="<<a[j]<< "G[ "<<i<<"] = "<<G[i]<<"\n";
							j++;
						}
						else{	
							if(j<n && j+1<n)
								G[i]=a[j]+a[j+1];
							else{
								min=extractmin(depo,count);
								count--;
								G[i]=a[j]+min.data;
							}
							count++;
							depo[count].data=G[i-1];
							depo[count].pos=i-1;
							buildheap(depo,count);
							cout<<"Floor( "<<i<<"): Depositing G["<<i-1<<"] ="<< G[i-1]<<"\n";
							cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<<",w["<<ind[j+1]<<"] ="<<a[j+1]<<"G[ "<<i<<"] = "<<G[i]<<"\n";
							j=j+2;
						}
					}
					else{
						if(a[j+1]<G[i-1])
						{
							G[i]=a[j]+a[j+1];
							count++;
							depo[count].data=G[i-1];
							depo[count].pos=i-1;
							buildheap(depo,count);
							cout<<"Floor( "<<i<<"): Depositing G["<<i-1<<"] ="<< G[i-1]<<"\n";
							cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<<",w["<<ind[j+1]<<"] ="<<a[j+1]<<"G[ "<<i<<"] = "<<G[i]<<"\n";
							j=j+2;
						}
						else{
							G[i]=a[j]+G[i-1];
							cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<< "G[ "<<i<<"] = "<<G[i]<<"\n";
							j++;
						}
					}
				}
			}
			else if(count>0)
			{
				temp1=depo[1];
				if(G[i-1]>temp1.data)
				{
					if(temp1.data<a[j+1])
					{
						min=extractmin(depo,count);
						count--;
						G[i]=a[j]+min.data;
						count++;
						depo[count].data=G[i-1];
						depo[count].pos=i-1;
						buildheap(depo,count);
						cout<<"Floor( "<<i<<"): Depositing G["<<i-1<<"] ="<< G[i-1]<<"\n";
						cout<< "Floor( "<<i<<"): Adding G[ "<<temp1.pos<<"] = "<<temp1.data<< "to bag,w["<<ind[j]<<"] ="<<a[j]<< "G[ "<<i<<"] = "<<G[i]<<"\n";
						j++;
					}
					else{
						G[i]=a[j]+a[j+1];
						count++;
						depo[count].data=G[i-1];
						depo[count].pos=i-1;
						buildheap(depo,count);
						cout<<"Floor( "<<i<<"): Depositing G["<<i-1<<"] ="<< G[i-1]<<"\n";
							cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<<",w["<<ind[j+1]<<"] ="<<a[j+1]<<"G[ "<<i<<"] = "<<G[i]<<"\n";
						j+=2;
					}
				}
				else{
					if(G[i-1]<a[j+1])
					{
						G[i]=a[j]+G[i-1];
						cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<< "G[ "<<i<<"] = "<<G[i]<<"\n";
						j++;
					}
					else{
						G[i]=a[j]+a[j+1];
						count++;
						depo[count].data=G[i-1];
						depo[count].pos=i-1;
						buildheap(depo,count);
						cout<<"Floor( "<<i<<"): Depositing G["<<i-1<<"] ="<< G[i-1]<<"\n";
							cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<<",w["<<ind[j+1]<<"] ="<<a[j+1]<<"G[ "<<i<<"] = "<<G[i]<<"\n";
						j+=2;
					}
				}
				
			}
			else{
				if(G[i-1]>a[j+1])
				{
					G[i]=a[j]+a[j+1];
					count++;
					depo[count].data=G[i-1];
					depo[count].pos=i-1;
					buildheap(depo,count);
					cout<<"Floor( "<<i<<"): Depositing G["<<i-1<<"] ="<< G[i-1]<<"\n";
					cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<<",w["<<ind[j+1]<<"] ="<<a[j+1]<<"G[ "<<i<<"] = "<<G[i]<<"\n";
					j+=2;
				}
				else{
					G[i]=a[j]+G[i-1];
					cout<< "Floor( "<<i<<"): Adding to bag,w["<<ind[j]<<"] ="<<a[j]<< "G[ "<<i<<"] = "<<G[i]<<"\n";
					j++;
				}
			}
		}
		total=total+G[i];
	}
	cout<<"---Total effort="<<total<<"\n";
}

/* The algorithm will work as it is clear that for the first two levels we should be choosing the two  minimum values. Now whenever we see that at a point a[i+1]< G[i-1], it is better if we add a[i+1] to a[i] rather than a[i] to G[i-1] and deposit G[i-1]. When we have made at least one deposit now we will have to do a condition check on a[i+1] and minimum of G[i] and choose which ever is minimum. We deposit in a min heap so as to maintain the complexity. In the end when we have only one choice we extract the minimum and the only element of the heap and add it to G[i-1]. Also we do not only extract but delete as well because we cannot order the same deposit twice*/
int main()
{
	int n,i;
	cout<< "n:";
	cin>>n;
	cout<< "\n";
	int arr[n],ind[n];
	for(i=0;i<n;i++)
	{
		cin>>arr[i];
		ind[i]=i+1;
	}
	mineffort1(arr,ind,n);
	mineffort2(arr,ind,n);
}
