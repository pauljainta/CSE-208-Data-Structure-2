#include<iostream>
#include<climits>
#include<stdlib.h>
#include<fstream>
#include<cstdlib>
#include<cmath>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define NIL -1
using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty();
    int getlen()
    {

        return length;
    }
    void printQ()
    {
        for(int i=0;i<length;i++)
        {
            printf("%d\n",data[i]);
        }


    }
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int *weightlist;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item,int w) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
	int getweight(int position);
	int position(int item);
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	weightlist=new int[listMaxSize];
	length = 0 ;
}

void ArrayList::insertItem(int newitem,int w)
{
	int * tempList1,*tempList2;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList1= new int[listMaxSize] ;
		tempList2=new int[listMaxSize];
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList1[i] = list[i] ;
            tempList2[i]=weightlist[i];
        }
        delete[] list ;
        delete[] weightlist; //free the memory allocated before
        list = tempList1 ;
        weightlist=tempList2; //make list to point to new memory
	};

	list[length] = newitem ;
	weightlist[length]=w; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}
int ArrayList::position(int item)
{
    int pos;
	pos = searchItem(item) ;

	return pos;

}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	weightlist[position]=weightlist[length-1];
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}
int ArrayList::getweight(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
	return weightlist[position] ;

}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list)
    {
        delete [] list;
        delete[] weightlist;
    }
    list = 0 ;
    weightlist=0;
}


class Edge
{
    public:
    int src,dist,weight;
    Edge()
    {
        src=-11111;
        dist=-11111;
        weight=INFINITY;
    }

    void setEdge(int u,int v,int w)
    {
        src=u;
        dist=v;
        weight=w;

    }

};

void swapEdge(Edge *x, Edge *y)
{
	Edge temp = *x;
	*x = *y;
	*y = temp;
}



class MinHeap
{
	Edge *edgelist;
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
public:

	MinHeap(int capacity);


	void MinHeapify(int );

	int parent(int i) { return (i-1)/2; }

	int left(int i) { return (2*i + 1); }

	int right(int i) { return (2*i + 2); }

	Edge extractMin();

	void decreaseKey(int i, Edge e);

	Edge getMin() { return edgelist[0]; }

	void deleteKey(int i);

	void insertKey(Edge e);
	void printHeap()
	{

	    for(int i=0;i<heap_size;i++)
        {
            printf("%d->%d\n",edgelist[i].src,edgelist[i].dist);
        }
	}
};

MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	edgelist = new Edge[cap];
}

void MinHeap::insertKey(Edge e)
{
	if (heap_size == capacity)
	{
		cout << "Size exceeded";
		return;
	}

	heap_size++;
	int i = heap_size - 1;
	edgelist[i] = e;

	while (i != 0 && edgelist[parent(i)].weight > edgelist[i].weight)
	{
	swapEdge(&edgelist[i], &edgelist[parent(i)]);
	i = parent(i);
	}
}


void MinHeap::decreaseKey(int i, Edge e)
{
	edgelist[i] =e;
	while (i != 0 && edgelist[parent(i)].weight > edgelist[i].weight)
	{
	swapEdge(&edgelist[i], &edgelist[parent(i)]);
	i = parent(i);
	}
}

Edge MinHeap::extractMin()
{
	if (heap_size <= 0)
		{
		    printf("No elements available\n");
		    Edge e;
            return   e;
		}
	if (heap_size == 1)
	{
		heap_size--;
		return edgelist[0];
	}

	Edge root = edgelist[0];
	edgelist[0] = edgelist[heap_size-1];
	heap_size--;
	MinHeapify(0);

	return root;
}



void MinHeap::deleteKey(int i)
{
    Edge e;
    e.setEdge(-1,-1,-9999999);
	decreaseKey(i,e);
	extractMin();
}


void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int s = i;
	if (l < heap_size && edgelist[l].weight < edgelist[i].weight)
		s = l;
	if (r < heap_size && edgelist[r].weight < edgelist[s].weight)
		s = r;
	if (s!= i)
	{
		swapEdge(&edgelist[i], &edgelist[s]);
		MinHeapify(s);
	}
}









//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int *indegree; *color,*parent,*dist,*cluster;
	Edge *EdgeList;

	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
	void dfs();
	int find(int x);
	void Union(int x,int y);


	void MST();


};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;
	EdgeList=0;
	 //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
	color=new int[n];
	dist=new int[n];
	parent=new int[n];
	indegree=new int[n];
	EdgeList=new Edge[nVertices*2];
	cluster=new int[nVertices];

}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
     EdgeList[nEdges].setEdge(u,v,w);

	adjList[u].insertItem(v,w) ;

	if(!directed)
    {
        adjList[v].insertItem(u,w) ;
        EdgeList[nEdges].setEdge(v,u,w);
    }
    this->nEdges++ ;

}
void Graph::removeEdge(int u, int v)
{

    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges-- ;
	adjList[u].removeItem(v) ;
	indegree[v]=indegree[v]-1;
	if(!directed) adjList[v].removeItem(u) ;



}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false

    if(adjList[u].searchItem(v)==NULL_VALUE) return false;
    return true;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{

  int i,j;
  for(i=0;i<adjList[u].getLength();i++)
  {

      for(j=0;j<adjList[v].getLength();j++)
      {

          if(adjList[u].getItem(i)==adjList[v].getItem(j))
            return true;
      }

  }

  return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GRAY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u=q.dequeue();
        for(int i=0;i<adjList[u].getLength();i++)
        {

            int v=adjList[u].getItem(i);
            if(color[v]==WHITE)
            {

                color[v]=GRAY;
                dist[v]=dist[u]+1;
                parent[v]=u;
                q.enqueue(v);
            }
        }

       color[u]=BLACK;
    }
}

void Graph::dfs()
{
    //write this function

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nEdges;i++)
    {
        /*printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");*/
        printf("%d->%d weight %d\n",EdgeList[i].src,EdgeList[i].dist,EdgeList[i].weight);
    }
}
int Graph:: find(int x)
{
    if(parent[x]==x)
    {
        return x;
    }
    return find(parent[x]);

}

void Graph::Union(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    parent[fx]=fy;
}




void Graph::MST()
{
    for(int i=0;i<nVertices;i++)
    {
        parent[i]=i;
    }

    MinHeap edgeheap(nEdges);
    int mst_edges=0,mst_weight=0;
    for(int i=0;i<nEdges;i++)
    {
        edgeheap.insertKey(EdgeList[i]);
    }
    Edge *mst_set=new Edge[nVertices-1];

    while(mst_edges<nVertices-1)
    {
        Edge e=edgeheap.extractMin();
        if(find(e.src)!=find(e.dist))
        {

            Union(e.src,e.dist);
            mst_weight+=e.weight;
            mst_set[mst_edges++]=e;

        }

    }


    printf("\nThe MST contains %d edges\n",mst_edges);
    printf("The edges are given below\n");
    for(int i=0;i<mst_edges;i++)
    {
        printf("%d->%d\n",mst_set[i].src,mst_set[i].dist);

    }
    printf("\nTotal weight %d\n",mst_weight);



}


Graph::~Graph()
{
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
     Graph g(true);
     ifstream file;
     //char filename[50];
    file.open("input.txt");
    if(!file.is_open())
    {

        exit(EXIT_FAILURE);
    }

    int value1[50],value2[50],value3[50];
    int num=0;
    while(!file.eof())
    {
         file >> value1[num]; // read first column number
         file >> value2[num]; // read second column number
         file >> value3[num];
       if(num==0) g.setnVertices(value1[0]);
       else
       {
           g.addEdge(value1[num],value2[num],value3[num]);

       }
       ++num;

    }
    file.close();


    g.printGraph();
    g.MST();

    system("pause");


return 0;



}


