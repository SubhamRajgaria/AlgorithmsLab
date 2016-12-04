#include <iostream>
#include <stdlib.h>
using namespace std;
// A structure to represent an adjacency list node
struct comb{
	int a,b,c;
};
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct comb arr;
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
           new struct AdjListNode;
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V,struct comb arr[])
{
    struct Graph* graph = new struct Graph;
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = new struct AdjList[V];
 
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i){
        graph->array[i].head= NULL;
	graph->array[i].arr=arr[i];
    }
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}
void findedge(struct Graph *graph,int C1,int C2,int C3)
{
	for(int i=0;i<graph->V;i++)
	{
		for(int j=0;j<graph->V;j++)
		{
			if(i==j)
				continue;
			else{
				if(((graph->array[j].arr.b==(graph->array[i].arr.a-graph->array[j].arr.a)+graph->array[i].arr.b)&&
				(graph->array[j].arr.b==C2 || graph->array[j].arr.a==0))
				|| ((graph->array[j].arr.c==(graph->array[i].arr.a-graph->array[j].arr.a)+graph->array[i].arr.c)&&
				(graph->array[j].arr.c==C3 || graph->array[j].arr.a==0))){
					addEdge(graph,i,j);
				}
				else if(((graph->array[j].arr.a==(graph->array[i].arr.b-graph->array[j].arr.b)+graph->array[i].arr.a)&&
				(graph->array[j].arr.a==C1 || graph->array[j].arr.b==0))
				|| ((graph->array[j].arr.c==(graph->array[i].arr.b-graph->array[j].arr.b)+graph->array[i].arr.c)&&
				(graph->array[j].arr.c==C3 || graph->array[j].arr.b==0))){
					addEdge(graph,i,j);
				}
				else if(((graph->array[j].arr.a==(graph->array[i].arr.c-graph->array[j].arr.c)+graph->array[i].arr.a)&&
				(graph->array[j].arr.a==C1 || graph->array[j].arr.c==0))
				|| ((graph->array[j].arr.b==(graph->array[i].arr.c-graph->array[j].arr.c)+graph->array[i].arr.b)&&
				(graph->array[j].arr.b==C2 || graph->array[j].arr.c==0))){
					addEdge(graph,i,j);
				}
			}
		}
	}
}
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        cout<<"\n Adjacency list of vertex \n head "<< v<<" with "
	<<"("<<graph->array[v].arr.a<<","<<graph->array[v].arr.b<<
	","<<graph->array[v].arr.c<<")";
        while (pCrawl)
        {
            cout<<"-> "<< pCrawl->dest;
            pCrawl = pCrawl->next;
        }
        cout<<"\n";
    }
}
struct Graph* gengraph(int a1,int a2, int a3, int C1, int C2,int C3) 
{
	int count=0;
	struct comb arr[C1*C2*C3];
	int i,j,k;
	for(i=0;i<=C1;i++)
	{
		for(j=0;j<=C2;j++)
		{
			for(k=0;k<=C3;k++)
			{
				if(i<=a1 && a1<i+1)
				{
					if(j<=a2 && a2<j+1)
					{
						if(k<=a3 && a3<k+1)
						{
							arr[count].a=i;
							arr[count].b=j;
							arr[count].c=k;
							count++;
						}
						else{
							if((i+j+k)==(a1+a2+a3))
							{
								if(i==0 || i==C1 || j==0 || j==C2 || k==0 || k==C3)
								{
									arr[count].a=i;
									arr[count].b=j;
									arr[count].c=k;
									count++;
								}
							}
						}
					}
					else{
						if((i+j+k)==(a1+a2+a3))
						{
							if(i==0 || i==C1 || j==0 || j==C2 || k==0 || k==C3)
							{
								arr[count].a=i;
								arr[count].b=j;
								arr[count].c=k;
								count++;
							}
						}
					}
				}
				else{
					if((i+j+k)==(a1+a2+a3))
					{
						if(i==0 || i==C1 || j==0 || j==C2 || k==0 || k==C3)
						{
							arr[count].a=i;
							arr[count].b=j;
							arr[count].c=k;
							count++;
						}
					}
				}
			}
		}
	}
	struct Graph *graph=createGraph(count,arr);
	findedge(graph,C1,C2,C3);
	printGraph(graph);
	return graph;
}
int find_s_t(struct Graph *graph,struct comb s)
{
	for(int i=0;i<graph->V;i++)
	{
		if(graph->array[i].arr.a==s.a && graph->array[i].arr.b==s.b && graph->array[i].arr.c==s.c)
			return i;
	}
}
int visit(struct Graph *graph,int *time, int visited[],int start[],int finish[],int parent[],int i,int t)
{
	int flag=0;
	visited[i]=1;
        *time=*time+1;
	start[i]=*time;
	struct AdjListNode* j=graph->array[i].head;
	if(i==t){
		flag=1;
		return flag;
	}
	while(j)
	{
		if(visited[j->dest]==0){
			parent[j->dest]=i;
			flag=visit(graph,time,visited,start,finish,parent,j->dest,t);
			return flag;
		}
		j=j->next;
	}
	finish[i]=*time;
	
}
int DFS(struct Graph *graph,int *time, int visited[],int start[],int finish[],int parent[],int s,int t)
{
	int count=0;
		if(visited[s]==0){
			parent[s]=s;
			count=visit(graph,time,visited,start,finish,parent,s,t);
		}
	if(count==1)
		return 1;
	return 0;	
}
bool reachable(struct Graph *graph,int s,int t)
{
	 int time=0;
    	 int visited[graph->V],start[graph->V],finish[graph->V],parent[graph->V];
	 for(int i=0;i<graph->V;i++)
	    {
		visited[i]=0;
	    }
	 int flag=DFS(graph,&time,visited,start,finish,parent,s,t);
	 if(flag==1)
		return true;
	return false;
}
void print(int parent[],struct Graph *graph,int t,int s)
{
	if(t==s){
		cout<< "("<<graph->array[t].arr.a<<","<<
		graph->array[t].arr.b<<","<<graph->array[t].arr.c<<")    ";
		return;
	}
	print(parent,graph,parent[t],s);
	cout<< "->("<<graph->array[t].arr.a<<","<<
		graph->array[t].arr.b<<","<<graph->array[t].arr.c<<")    ";
}
void prnpath(struct Graph* graph, int s ,int t)
{
	int time=0;
    	 int visited[graph->V],start[graph->V],finish[graph->V],parent[graph->V];
	 for(int i=0;i<graph->V;i++)
	    {
		visited[i]=0;
	    }
	int flag=DFS(graph,&time,visited,start,finish,parent,s,t);
	print(parent,graph,t,s);
	cout<<"\n";	
}
int main()
{
	int C1,C2,C3,a1,a2,a3,b1,b2,b3;
	int i,j,k,start,end;
	struct comb s,t;
	cout<<"+++ Capacities :";
	cin>>C1;
	cin>>C2;
	cin>>C3;
	cout<<"\n+++ Start      :";
	cin>>a1;
	cin>>a2;
	cin>>a3;
	cout<<"\n+++ End        :";
	cin>>b1;
	cin>> b2;
	cin >> b3;
	s.a=a1;
	s.b=a2;
	s.c=a3;
	t.a=b1;
	t.b=b2;
	t.c=b3;
	struct Graph *graph=gengraph(a1,a2,a3,C1,C2,C3);
	start=find_s_t(graph,s);
	end=find_s_t(graph,t);
	cout<< "+++Source(s): "<<start<<"\n";
	cout<<"+++Target: "<<end<<"\n";
	bool check=reachable(graph,start,end);
	if(check)
	cout<<"+++ Sequence of moves exists\n";
	else
	cout << "+++ Sequence of moves does not exists\n";
	if(check)
		prnpath(graph,start,end);
}

