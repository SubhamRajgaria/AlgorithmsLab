#include<iostream>
#include<cmath>

struct node{
	int data;
	struct node *left;
	struct node *right;
	struct node *p;
};
using namespace std;
struct node * newNode(struct node *p,int data)
{
	struct node *temp=new node;
	temp->data=data;
	temp->left=temp->right=NULL;
	temp->p=p;
}
int size(struct node *tree)
{
	if(tree==NULL)
		return 0;
	int c1=size(tree->left);
	int c2=size(tree->right);
	return (c1+c2+1);
}
int height(struct node *tree)
{
	if(tree==NULL)
		return 0;
	int c1=size(tree->left);
	int c2=size(tree->right);
	return (max(c1,c2)+1);
}
void inorder(struct node *node)
{
	if(node==NULL)
		return;
	inorder(node->left);
	cout << node->data << " ";
	inorder(node->right);
}
void destroy(struct node *node)
{
	if(node==NULL)
		return;
	destroy(node->left);
	destroy(node->right);
	delete node;
}
int search(struct node *tree, int k)
{
	if(tree==NULL)
		return 0;
	if(tree->data==k)
		return 1;
	if(k<tree->data)
		return(search(tree->left,k));
	else 
		return(search(tree->right,k));
	
}
struct node* FindMin(struct node *node)
{
        if(node==NULL)
        {
                /* There is no element in the tree */
                return NULL;
        }
        if(node->left) /* Go to the left sub tree to find the min element */
                return FindMin(node->left);
        else 
                return node;
}
struct node * Delete(struct node *node, int data)
{
        struct node *temp;
        if(node==NULL)
        {
                cout << "Element Not Found";
        }
        else if(data < node->data)
        {
                node->left = Delete(node->left, data);
        }
        else if(data > node->data)
        {
                node->right = Delete(node->right, data);
        }
        else
        {
                if(node->right && node->left)
                {
                        temp = FindMin(node->right);
                        node -> data = temp->data; 
                        node -> right = Delete(node->right,temp->data);
                }
                else
                {
                        /* If there is only one or zero children then we can directly 
                           remove it from the tree and connect its parent to its child */
                        temp = node;
                        if(node->left == NULL)
                                node = node->right;
                        else if(node->right == NULL)
                                node = node->left;
                        delete(temp); /* temp is longer required */ 
                }
        }
        return node;

}
int make_list(int arr[],struct node *tree,int count)
{
	if(tree==NULL)
		return 0;
	int no_left=make_list(arr,tree->left,count);
	arr[count+no_left]=tree->data;
	int no_right=make_list(arr,tree->right,count+no_left+1);
	return (no_left+no_right+count);
}
struct node * balance(int arr[],struct node *tree,int start,int end)
{
	struct node* root;
	if(start==end)
		return root;
	int median=arr[(start+end)/2];
	root=newNode(tree,median);
	root->left=balance(arr,root->left,start,(start+end)/2-1);
	root->right=balance(arr,root->right,(start+end)/2+1,end);
	return root;
}
struct node * rebuild(struct node *tree, int size)
{
	if(tree==NULL)
		return tree;
	int arr1[size],arr2[size];
	int count1=make_list(arr1,tree->left,0);
	int count2=make_list(arr2,tree->right,0);
	destroy(tree->left);
	destroy(tree->right);
	tree->left=balance(arr1,tree,0,count1);
	tree->right=balance(arr2,tree,0,count2);
	return tree;
}
struct node* Insert(struct node *node,struct node *temp2,int data,float *depth)
{
	if(node==NULL)
		return node;
	if(data<node->data)
	{
		if(node->left==NULL)
		{
			node->left=newNode(node,data);
			temp2=node->left;
		}
		else
		{
			*depth++;
			Insert(node->left,temp2,data,depth);
			
		}
	}
	else
	{
		if(node->right==NULL)
		{
			node->right=newNode(node,data);
			temp2=node->right;
		}
		else
		{
			*depth++;
			Insert(node->right,temp2,data,depth);
			
		}
	}
	return node;
}
struct node * insertKey(struct node *T,int x, int *n,int *m)
{
	float d=0;
	float *depth=&d;
	struct node *temp=T;
	int check=search(T,x);
	if(check==0)
	{
		T=Insert(T,temp,x,depth);
		*n++;
		*m++;
	}
	int s=size(T);
	if((*depth)<=(1+floor(log(s)/log(1.5))))
		return T;
	else{
		while(size(temp->p->left)<=(2/3)*size(temp->p) && size(temp->p->right)<=(2/3)*size(temp->p))
		{
			temp=temp->p;
		}
		rebuild(temp->p,size(temp->p));
		cout <<"Height of rebuilt tree:"<< size(temp->p);
		return T;
	}
	
}
int main()
{
	struct node* T=NULL;
	int nsml,i,element,count;
	int *n,*m;
	cin >> nsml;
	for(i=0;i<nsml;i++)
	{
		cin>>element;
		if(i==0)
		{
			T=newNode(T,element);
		}
		else
		{
			count=size(T);
			cout << count;
			n = &count;			
			cout << *n;
			m = &count;
			T=insertKey(T,element,n,m);
		}
		cout<< "+++ insert("<<element<<"):	";
		cout<<"Height = "<< height(T)-1<< ":  ";
		inorder(T);
		cout << endl;
	}
}

