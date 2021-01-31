#include<iostream>
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
	void setweight(int pos,int w);
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
void ArrayList::setweight(int pos,int w)
{
	  weightlist[pos]=w;

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

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    public:
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int  *color,*parent,*dist;
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
	bool bfs(int source,int t); //will run bfs in the graph
	void dfs();
	//void maxflow(int source,int t);


};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;
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

}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v,w) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges-- ;
	adjList[u].removeItem(v) ;
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

bool Graph::bfs(int source,int t)
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
            if(color[v]==WHITE&&adjList[u].getweight(i)>0)
            {
             //  printf("In bfs\n");
                color[v]=GRAY;
                dist[v]=dist[u]+1;
                parent[v]=u;
                q.enqueue(v);

            }
        }

       color[u]=BLACK;
    }
    return (color[t]==BLACK);
}
void Graph::printGraph()
{

    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}
int Min(int x,int y)
{
    if(x<y) return x;
    return y;

}

void maxflow(Graph g,int s,int t)
{
       Graph res_graph(true);
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
       if(num==0) res_graph.setnVertices(value1[0]);
       else
       {
           res_graph.addEdge(value1[num],value2[num],value3[num]);

       }
       ++num;

    }
    file.close();


   for (int i = 0; i <res_graph.nVertices; i++)
      for (int j = 0; j <res_graph.nVertices; j++)
        if(g.isEdge(i,j)) res_graph.addEdge(j,i,0);

   int max=0;
   int p_min;
   while(res_graph.bfs(s,t))
   {
       p_min=INFINITY;
        for (int v=t; v!=s; v=res_graph.parent[v])
        {

           int u =res_graph.parent[v];
           int i=res_graph.adjList[u].position(v);

            p_min = Min(p_min,res_graph.adjList[u].getweight(i));

        }


         for (int v=t; v != s; v=res_graph.parent[v])
        {

         int u =res_graph.parent[v];
         int i=res_graph.adjList[u].position(v);
         int j=res_graph.adjList[v].position(u);
         int w=res_graph.adjList[u].getweight(i)-p_min;
         int w1=res_graph.adjList[v].getweight(j)+p_min;
         res_graph.adjList[u].setweight(i,w);
         res_graph.adjList[v].setweight(j,w1);
        }

       max+=p_min;
   }
   printf("The edges of a min cut are below:\n");

 for (int i = 0; i <res_graph.nVertices; i++)
      for (int j = 0; j <res_graph.nVertices; j++)
         if (res_graph.color[i]==BLACK && res_graph.color[j]==WHITE && g.isEdge(i,j))
              cout << i << " --> " << j << endl;

   printf("The max flow is %d\n",max);
   printf("Flow along each edge is given below:\n");

    for (int u = 0; u<res_graph.nVertices; u++)
      for (int v = 0; v<res_graph.nVertices; v++)
         if (g.isEdge(u,v))
             {
                 int i=g.adjList[u].position(v);
                 int flow=g.adjList[u].getweight(i)-res_graph.adjList[u].getweight(i);
                 printf("Flow along edge %d-->%d is %d\n",u,v,flow);

             }



}


void Graph::dfs()
{
    //write this function

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
   maxflow(g,value2[0],value3[0]) ;


   // system("pause");


return 0;



}

