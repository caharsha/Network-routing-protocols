#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
struct vertex
{
	int v, width, dad;
};
bool compareByWidth(const vertex &a, const vertex &b)
{
    return (a.width < b.width);
}	
class Dijkstra
{
	vector <vector <int> > adjmat;
	int source, destination;
	unsigned int i;
	int alt;
	vertex u;
	vector<struct vertex> Q;
	int band[5000], parent[5000];
	public:
	Dijkstra(vector <vector <int> > adj_mat, int src, int dest)
	{
		adjmat.swap(adj_mat);
		destination = dest;
		source = src;
		Q.resize(5000);
	}
	void compute(void)
	{
		clock_t t1 = clock();
		//Initializations
		for(i=0;i<5000;i++)
		{
			Q.at(i).v = i;
			Q.at(i).width = 0;
			Q.at(i).dad = -1;
		}
		Q.at(source).width = 32767; //Source has infinite capacity to itself.
		//Order the priority queue
		
		
		while(!Q.empty())
		{
			//Reorder the queue
			sort(Q.begin(), Q.end(), compareByWidth);
			//Pop the element with the highest width
			u = Q.back();
			//Remove u from the Q
			Q.pop_back();
			if (u.width == 0)
			{		
				break;
			}
			// all remaining vertices are inaccessible from source
			for(i=0;i< (Q.size());i++)
			{
				if (adjmat.at(u.v).at(Q.at(i).v) != -1)
				if (u.v != Q.at(i).v) //Edge u.v, w exists and vertex w is in Q 
				{
					//Relax function:
					//alt := max(Q.at(i).width, min(u.width, adjmat.at(u.v).at(Q.at(i).v))) ;
					if(u.width > adjmat.at(u.v).at(Q.at(i).v))
					alt = adjmat.at(u.v).at(Q.at(i).v);
					else alt = u.width;
					if(alt > Q.at(i).width)
					{
						Q.at(i).width = alt;
						Q.at(i).dad = u.v;
					}
				}
				 
		}
	band[u.v] = u.width;
	parent[u.v] = u.dad;
	}
clock_t t2 = clock();
cout<<"The Dijkstra's algorithm implementation ran in : "<< (t2-t1)/ 1000 <<" milliseconds."<<endl;
cout<<"Maximum bandwidth between source " << source << " and " <<" destination " <<destination<< " : " <<band[destination]<<endl;	
alt = destination;
cout<<"Path: "<<endl;
while(parent[alt] != source)
{
	cout<<parent[alt]<< " ";
	alt = parent[alt];
}
cout<<endl;
}
};

class densegraph
{
	vector <vector <int> > adjmat;
	int i,j;
	public:
	densegraph()
	{
		//Initialise the adjacency matrix.
		adjmat.resize(5000, vector<int>(5000, -1));
	}
	void create(void)
	{
		
		srand (time(NULL));
		for (i=0;i<5000;i++)
		{
			for (j=0;j<5000;j++)
				{
					if(i!=j)
					{
						if(rand() % 1000 < 106)
						{
						adjmat.at(i).at(j) = rand()%32767;
						adjmat.at(j).at(i) = adjmat.at(i).at(j);
						}
					}
				}
		}	
	
	}

vector<vector <int> > returnfunc (void)
{
	return adjmat;
}

};

int main()
{
	densegraph G;
	G.create();
	vector<vector <int> > adj_mat;
	int src,dest;
	adj_mat.resize(5000, vector<int>(5000, -1));
	adj_mat = G.returnfunc();
	cout<<"Enter the source vertex: ";
	cin>>src;
	cout<<"Enter the destination vertex: ";
	cin>>dest;
	Dijkstra max_bandwidth(adj_mat,src,dest);
	max_bandwidth.compute();
	return 0;
}
