#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
typedef struct {
char x[21], y[21];   /*Pair of NULL-terminated strings*/
} strpair;
typedef struct {
char att[21];   /*The attribute name: a NULL-terminated string*/
int nassoc;     /*Number of attribute associations in the other table*/
int assoc[10];  /*Array of indices of the associated attributes*/
} htnode;
typedef struct {
int S;          /*Size of A and B*/
htnode*A,*B;  /*Attribute arrays*/
} hashtable;
hashtable * inittable(int size)
{
	int i,j;
	hashtable *T;
	T=new hashtable;
	T->S=size;
	T->A=new htnode[size];
	T->B=new htnode[size];
	for(i=0;i<size;i++)
	{
		T->A[i].nassoc=0;
		T->B[i].nassoc=0;
		strcpy(T->A[i].att,"EMPTY");
		strcpy(T->B[i].att,"EMPTY");
	}
	return T;
}
int hashfunc(char z[],int S)
{
	int sum=0,i;
	for(i=0;i<strlen(z);i++)
	{
		sum=sum*128+(int)z[i];
		sum=sum%S;
	}
	return sum;
}
void searchpair(hashtable *T,strpair z)
{
	int i=hashfunc(z.x,T->S);
	int j,flag=0,count=0;
	while(strcmp(T->A[i].att,"EMPTY")!=0 && count <T->S)
	{
		if(strcmp(T->A[i].att,z.x)==0)
		{
			for(j=0;j<T->A[i].nassoc;j++)
			{
				if(strcmp(T->B[(T->A[i].assoc[j])].att,z.y)==0)
				{
					cout << "("<< z.x<<","<<z.y<<") found at ("<<i<<","<<T->A[i].assoc[j]<<")"<<endl;
					flag=1;
					break;
				} 
			}
		}
		if(flag==1)
			break;
		count++;
		if(i<((T->S)-1))
			i++;
		else i=0;
	}
	if(flag==0)
			cout << "No match";
}
void searchattr(hashtable *T,char z[],int a)
{
	int i,j,count=0,flag=0;
	if(a==1)
	{
		i=hashfunc(z,T->S);
		while(strcmp(T->A[i].att,"EMPTY")!=0 && count <T->S)
		{
			if(strcmp(T->A[i].att,z)==0)
			{
				flag=1;
				cout<<"("<< z<<",-" <<"is associated with:";
				for(j=0;j< T->A[i].nassoc;j++)
				{
					cout<< T->B[(T->A[i].assoc[j])].att<< ",";
				}
			}
			if(flag==1)
			break;
			count++;
			if(i<((T->S)-1))
				i++;
			else i=0;
		}
		if(flag==0)
			cout << "No match";
	}
	else{
		i=hashfunc(z,T->S);
		while(strcmp(T->B[i].att,"EMPTY")!=0 && count <T->S)
		{
			if(strcmp(T->B[i].att,z)==0)
			{
				flag=1;
				cout<<"(-"<<","<<z <<"is associated with:";
				for(j=0;j< T->B[i].nassoc;j++)
				{
					cout<< T->A[(T->B[i].assoc[j])].att<< ",";
				}
			}
			if(flag==1)
			break;
			count++;
			if(i<((T->S)-1))
				i++;
			else i=0;
		}
		if(flag==0)
			cout << "No match";
	}
}
hashtable * insertpair(hashtable *T, strpair z)
{
	int ind1=hashfunc(z.x,T->S);
	int ind2=hashfunc(z.y,T->S);
	cout << "hash at ("<<ind1<<","<<ind2<<")";
	int count1=0,count2=0,flag1=0,flag2=0,flag3=0,i;
	while(strcmp(T->A[ind1].att,"EMPTY")!=0 && count1 <T->S)
	{
		if(strcmp(T->A[ind1].att,z.x)==0)
		{
			flag1=1;
			break;
		}
		count1++;
		if(ind1<((T->S)-1))
			ind1++;
		else ind1=0;
	}
	if(flag1==1)
	{
		for(i=0;i<T->A[ind1].nassoc;i++)
		{
			if(strcmp(T->B[T->A[ind1].assoc[i]].att,z.y)==0)
			{
				flag2=1;
				break;
			}
		}
	}
	if(flag2==0){
		while(strcmp(T->B[ind2].att,"EMPTY")!=0 && count2 <T->S)
		{
			if(strcmp(T->B[ind2].att,z.y)==0)
			{
				flag3=1;
				break;
			}
			count2++;
			if(ind2<((T->S)-1))
				ind2++;
			else ind2=0;
		}
	}
	if(flag1==1 && flag2==1)
	{
		cout << " Already present\n";
		return T;
	}
	else if(flag1==1 && flag3==1)
	{
		T->B[ind2].nassoc++;
		T->A[ind1].nassoc++;
		T->B[ind2].assoc[(T->B[ind2].nassoc)-1]=ind1;
		T->A[ind1].assoc[(T->A[ind1].nassoc)-1]=ind2;
		cout << "  insertion at ("<<ind1<<","<<ind2<<")\n";
	}
	else if(flag1==1 && flag2==0)
	{
		ind2=hashfunc(z.y,T->S);
		while(1)
		{
			if(strcmp(T->B[ind2].att,"EMPTY")==0 || strcmp(T->B[ind2].att,"DELETED")==0 )
				break;
			else
			{
				if(ind2<((T->S)-1))
				ind2++;
				else ind2=0;
			}
		}
		strcpy(T->B[ind2].att,z.y);
		T->B[ind2].nassoc++;
		T->A[ind1].nassoc++;
		T->B[ind2].assoc[(T->B[ind2].nassoc)-1]=ind1;
		T->A[ind1].assoc[(T->A[ind1].nassoc)-1]=ind2;
		cout << "  insertion at ("<<ind1<<","<<ind2<<")\n";
		return T;
	}
	else if(flag1==0 && flag3==1)
	{
		ind1=hashfunc(z.x,T->S);
		while(1)
		{
			if(strcmp(T->A[ind1].att,"EMPTY")==0 || strcmp(T->A[ind1].att,"DELETED")==0 )
				break;
			else
			{
				if(ind1<((T->S)-1))
				ind1++;
				else ind1=0;
			}
		}
		strcpy(T->A[ind1].att,z.x);
		T->B[ind2].nassoc++;
		T->A[ind1].nassoc++;
		T->B[ind2].assoc[(T->B[ind2].nassoc)]=ind1;
		T->A[ind1].assoc[(T->A[ind1].nassoc)]=ind2;
		cout << "  insertion at ("<<ind1<<","<<ind2<<")\n";
		return T;
	}
	else{
		ind1=hashfunc(z.x,T->S);
		ind2=hashfunc(z.y,T->S);
		while(1)
		{
			if(strcmp(T->A[ind1].att,"EMPTY")==0 || strcmp(T->A[ind1].att,"DELETED")==0 )
				break;
			else
			{
				if(ind1<((T->S)-1))
				ind1++;
				else ind1=0;
			}
		}
		while(1)
		{
			if(strcmp(T->B[ind2].att,"EMPTY")==0 || strcmp(T->B[ind2].att,"DELETED")==0 )
				break;
			else
			{
				if(ind2<((T->S)-1))
				ind2++;
				else ind2=0;
			}
		}
		strcpy(T->B[ind2].att,z.y);
		strcpy(T->A[ind1].att,z.x);
		T->B[ind2].nassoc++;
		T->A[ind1].nassoc++;
		T->B[ind2].assoc[(T->B[ind2].nassoc)-1]=ind1;
		T->A[ind1].assoc[(T->A[ind1].nassoc)-1]=ind2;
		cout << "  insertion at ("<<ind1<<","<<ind2<<")\n";
		return T;
	}
}
hashtable *deletepair(hashtable *T, strpair z)
{
	int ind1=hashfunc(z.x,T->S);
	int ind2=hashfunc(z.y,T->S);
	int count1=0,i,j,k,flag1=0,flag2=0;
	while(strcmp(T->A[ind1].att,"EMPTY")!=0 && count1 <T->S)
	{
		if(strcmp(T->A[ind1].att,z.x)==0)
		{
			flag1=1;
			break;
		}
		count1++;
		if(ind1<((T->S)-1))
			ind1++;
		else ind1=0;
	}
	if(flag1==1)
	{
		for(i=0;i<T->A[ind1].nassoc;i++)
		{
			if(strcmp(T->B[T->A[ind1].assoc[i]].att,z.y)==0)
			{
				for(j=i+1;j<T->A[ind1].nassoc;j++)
				{
					T->A[ind1].assoc[j-1]=T->A[ind1].assoc[j];
				}
				flag2=1;
				T->A[ind1].nassoc--;
				for(j=0;j<T->B[T->A[ind1].assoc[i]].nassoc;j++)
				{
					if(T->B[T->A[ind1].assoc[i]].assoc[j]==ind1)
					{
						for(k=j+1;k<T->B[T->A[ind1].assoc[i]].nassoc;k++)
						{
							T->B[T->A[ind1].assoc[i]].assoc[k-1]=T->B[T->A[ind1].assoc[i]].assoc[k];
						}
					}
				}
				T->B[T->A[ind1].assoc[i]].nassoc--;
				break;	
			}
		}
		if(flag2==0)
			return T;
		else{
			if(T->A[ind1].nassoc==0)
				strcpy(T->A[ind1].att,"DELETED");
			if(T->B[T->A[ind1].assoc[i]].nassoc==0)
				strcpy(T->B[T->A[ind1].assoc[i]].att,"DELETED");
			return T;
		}
	}
	else
		return T;
}
int main()
{
	int S,i;
	cout << "Enter size:S=";
	cin>> S;
	hashtable *T=inittable(S);
	int choice;
	strpair z;
	while(1)
	{
		cout<< "+++Enter choice ";
		cin>> choice;
		switch(choice)
		{
			case 0: break;
			break;
			case 1: cin>>z.x;
			searchattr(T,z.x,1);
			break;
			case 2: cin>> z.y;
			searchattr(T,z.y,2);
			break;
			case 3:cin >> z.x;
			cin>> z.y;
			searchpair(T,z);
			break;
			case 4:cin>> z.x;
			cin >> z.y;
			T=insertpair(T,z);
			break;
			case 5:cin>>z.x;
			cin >> z.y;
			T=deletepair(T,z);
			break;
		}
		cout << endl;
		if(choice==0)
			break;
	}
}
