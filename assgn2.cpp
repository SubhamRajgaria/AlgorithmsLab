#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
struct tree{
	int eos;
	struct tree *left;
	struct tree *right;
};
using namespace std;
int binary_convert(int n,char binary[])
{
	int count=0,i;
	int pseudo[100];
	while(n>0)
	{
		pseudo[count]=n%2;
		count++;
		n=n/2;
	}
	int j=0;
	for(i=count-1;i>=0;i--)
	{
		binary[j]=(char)pseudo[i];
		j++;
	}
	cout << "\n";
	return count;
}
struct tree* newNode (int data)
{
    struct tree* temp =new struct tree;
    temp->eos = data;
    temp->left = temp->right = NULL;

    return temp;
}
struct tree * insert(struct tree *T,int a)
{
	struct tree *head;
	char binary[100];
	int count=binary_convert(a,binary);
	int i=1;
	if(T==NULL)
	{
		if(count==1)
			T=newNode(1);
		else 
			T=newNode(0);
	}
	if(count==1)
		T->eos=1;
	head=T;
	while(i<count)
	{
		if(i==(count-1))
		{
			if(binary[i]==0 && head->left==NULL)
			{
				head->left=newNode(1);
			}
			else if(binary[i]==1 && head->right==NULL)
			{
				head->right=newNode(1);	
			}
			else if(binary[i]==0 && head->left!=NULL)
			{
				head->left->eos=1;
			}
			else
			{
				head->right->eos=1;	
			}
		}
		else
		{
			if(binary[i]==0 && head->left==NULL)
			{
				head->left=newNode(0);
				head=head->left;
			}
			else if(binary[i]==1 && head->right==NULL)
			{
				head->right=newNode(0);
				head=head->right;	
			}
			else if(binary[i]==0 && head->left!=NULL)
			{
				head=head->left;
			}
			else
			{
				head=head->right;	
			}
		}
		i++;
	}
	return T;
}
void preorder(struct tree *T,char pr[],int count)
{
	int i;
	if(T==NULL)
		return;
	if(T->eos==1)
	{
		for(i=0;i<count;i++)
			cout << pr[i];
		cout << " ";
	}
	pr[count]='0';
	count++;
	preorder(T->left,pr,count);
	pr[--count]='1';
	count++;
	preorder(T->right,pr,count);
}
void printTree(struct tree *T)
{
	char pr[100];
	preorder(T,pr,0);
}
struct tree *my_delete(struct tree *T,char binary[],int index,int count)
{
	if(T==NULL)
		return NULL;
	else 
	{
		if(index<count && binary[index]==0)
			T->left=my_delete(T->left,binary,index+1,count);
		else if(index<count && binary[index]==1)
			T->right=my_delete(T->right,binary,index+1,count);
		if(T->left == NULL && T->right == NULL && T->eos == 0) {
			delete(T);
			return NULL;
		}
	}
	return T;
}
struct tree * delete_(struct tree *T, int a)
{
	char binary[100];
	int count=binary_convert(a,binary);
	struct tree *head=T;
	int i;
	for(i=1;i<count;i++)
	{
		if(head == NULL)
			return head;
		if(binary[i] == 0)
			head = head->left;
		else if(binary[i] == 1)
			head = head->right;
		if(i == count-1) {
			head->eos = 0;
		}
	}
	if(head->left == NULL && head->right == NULL)
		T= my_delete(T, binary, 1,count);
	return T;
}
/*void printing(int binary[],int count)
{
	int i;
	int n=pow(2,count+1);
	for(i=0;i<=count;i++)
	{
		n=n+binary[i]*pow(2,count-i);
	}
	cout << n <<" ";
}*/
/*void myprintInts(struct tree *T,int i,int a)
{
	if(T==NULL)
		return ;
	a=i;
	if(T->eos==1)	
		cout << i<< " ";
	i=2*i;
	myprintInts(T->left,i);
	i=i+1;
	myprintInts(T->right,i); 
}*/
void printInts(struct tree *T)
{
	if(T==NULL)
		return;
	queue<pair<tree*, int> > q;
	 q.push(make_pair(T,1));
	while (1)
        {
		int nodeCount = q.size();
		if (nodeCount == 0)
		    break;
		while (nodeCount > 0)
		{
		    struct tree *node = q.front().first;
		    int k=q.front().second;
		    q.pop();
		    if(node->eos==1)
			cout << k << " ";
		    if (node->left != NULL)
		    {
		        q.push(make_pair(node->left,2*k));
		    }
		    if (node->right != NULL)
		    {
		        q.push(make_pair(node->right,2*k+1));
		    }
		    nodeCount--;
        	}
    	}
}
int main()
{
	struct tree *T=NULL;
	int n,i;
	cout << "Enter nins\n";
	cin >> n;
	cout << "nins=" << n<< "\n";
	int arr[n];
	cout << "Enter the numbers\n";
	for(i=0;i<n;i++)
	{
		cin >> arr[i];
		T=(insert(T,arr[i]));
	}
	cout << "+++ Insert:";
	for(i=0;i<n;i++)
		cout << arr[i] << " ";
	cout << "\n" << "+++ After Insertion:\n";
	cout << "\n";
	printTree(T);
	cout << "\n";
	int ndel;
	cout << "Enter ndel\n";
	cin >> ndel;
	int no;
	cout << "+++Delete:";
	for(i=0;i<ndel;i++)
	{
		cin >> no;
		T=delete_(T,no);
	}
	cout << "+++ After Deletion\n";
	printTree(T);
	T=NULL;
	cout << "\n+++ Old tree destroyed\n";
	cout << "Enter nins\n";
	cin >> n;
	cout << "nins=" << n<< "\n";
	cout << "Enter the numbers\n";
	for(i=0;i<n;i++)
	{
		cin >> arr[i];
		T=(insert(T,arr[i]));
		cout << "Insert(" << arr[i] << "):";
		//printTree(T);
		printInts(T);
		cout << "\n";
	}
	cout << "Enter ndel\n";
	cin>> ndel;
	cout << "ndel:" << ndel<< "\n";
	cout << "Enter the numbers\n";
	for(i=0;i<ndel;i++)
	{
		cin >> arr[i];
		T=(delete_(T,arr[i]));
		cout << "Delete(" << arr[i] << "):";
		//printTree(T);
		printInts(T);
		cout << "\n";
	}
}
