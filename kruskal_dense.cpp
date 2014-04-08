//Returns a bandwidth of 0 if no path is present.
#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<stack>
struct edges
	{
		int v1; 
		int v2;
		int edge_wt;
	};

bool compareByEdgeweight(const edges &a, const edges &b)
{
    return (a.edge_wt > b.edge_wt);
}
using namespace std;
class DFS
{
vector <vector <int> > maxspantree;
int src, dest, color[5000], dad[5000],i,d,max_bandwidth,answer;
public:	
DFS(vector <vector <int> > max_span_tree )
{
	maxspantree.swap(max_span_tree);
}
void max_bandwidth_path()
{
	answer = 0;
	cout<<"Enter the source vertex: (0 to 4999) ";
	cin>>src;
	cout<<"Enter the destination vertex: (0 to 4999) ";
	cin>>dest;
	clock_t t4 = clock();
	max_bandwidth = 32767;
	if(src != dest)
	{
	for(i=0;i<5000;i++)
	{
		color[i] = 0;
		dad[i] = -1;
	} 
	}
	else
	{
		answer = max_bandwidth;
	}
	DFSvisit(src);
	cout<<"Max bandwidth: "<<answer<<endl;
	clock_t t5 = clock();
	cout<<"Time for DFS: "<<(t5-t4)/1000<<" milliseconds"<<endl;
	cout<<"Do you want to find the maximum bandwidth path between any other vertices in the same graph? (1- yes any other key - no) :";
	cin>>d;
	if(d == 1)
	{
		max_bandwidth_path();
	}
}
void DFSvisit( int v)
{
	//cout<<v<<endl;
	color[v] = 1;
	for(i=0;i<5000;i++)
	{
		//cout<<maxspantree.at(v).at(i)<<endl;
		if(maxspantree.at(v).at(i) != -1)
		{
			if(color[i] == 0)
			{
				if(max_bandwidth > maxspantree.at(v).at(i))
				{
					//cout<<max_bandwidth<<endl;
					max_bandwidth = maxspantree.at(v).at(i);
				}
				DFSvisit(i);
				dad[i] = v;
			}
		}
	}
color[v] = 2;
if(v == dest)
	{
		answer = max_bandwidth;
	}
}

};

class kruskal
{
	int i,j,k ;
	long numedges;
	vector <vector <int> > adjmat;
	vector <vector <int> > maxspantree;
	vector <struct edges> sorted_edges;
	int dad[5000], rank[5000];
	int ver1, ver2;
	int ver1_find, ver2_find;
	int edge_ctr;
	stack <int> kstack;
public:
kruskal(long num_edges, vector <vector <int> > adj_mat)
{
	numedges = num_edges/2; 
	adjmat.swap(adj_mat);
	sorted_edges.resize(numedges);
}

void edgesort()
{
	k = 0;
	for(i=0;i<5000;i++)
	{
		for(j=0;j<5000;j++)
		{
			if(i<j)
			{
				if(adjmat.at(i).at(j) != -1)
				{
				sorted_edges.at(k).edge_wt = adjmat.at(i).at(j);
				sorted_edges.at(k).v1 = i;
				sorted_edges.at(k).v2 = j;
				k++;
				}
			}
		}
	}
	
	sort(sorted_edges.begin(), sorted_edges.end(), compareByEdgeweight);
	//for(i = 0; i < numedges; i++)
	//cout<<i<<". "<<sorted_edges.at(i).v1<<" "<<sorted_edges.at(i).v2<<" "<<sorted_edges.at(i).edge_wt<<endl;
}
vector<vector <int> > returnfunc (void)
{
	return maxspantree;
}
void kruskalimplement ()
{
	edge_ctr = 0;
	edgesort();
	//cout<<"Checkpoint 3: Edges sorted in descending order of edge weights."<<endl;
	makeset();
	//cout<<"Checkpoint 4: Makeset operation completed successfully."<<endl;
	maxspantree.resize(5000, vector<int>(5000, -1)); //Tree = {}
	for(i = 0; i<numedges; i++)
	{
		ver1 = sorted_edges.at(i).v1;
		ver2 = sorted_edges.at(i).v2;
		ver1_find = find(ver1);
		ver2_find = find(ver2);
		if( ver1_find != ver2_find)
		{
			maxspantree.at(ver1).at(ver2) = sorted_edges.at(i).edge_wt;
			maxspantree.at(ver2).at(ver1) = sorted_edges.at(i).edge_wt;
			unionfunc(ver1,ver2);
			edge_ctr++;
			//cout<<edge_ctr;
			if(edge_ctr >= 4999)
				break;
		}
	
	
	}

}	
int find(int vert1)
{
int w = vert1;
int u = 0;
while (!kstack.empty())
	kstack.pop();
while ((dad[w] != -1) && (dad[w] != w)) 
{
		kstack.push(w);
		w = dad[w];
}
if(dad[w] == -1)
{
	dad[w] = w;
	kstack.push(w);
}
while (!kstack.empty())
{
	u = kstack.top();
	dad[u] = w;
	kstack.pop();	
}
return w;	
}

void unionfunc(int vert1, int vert2)
{
	if(rank[vert1] > rank[vert2])
		dad[vert2] = vert1;
	if(rank[vert2] > rank[vert1])
		dad[vert1] = vert2;
	if(rank[vert1] == rank[vert2])
	{
		dad[vert2] = vert1;
		rank[vert1]++;
	}	
}

	
void makeset()
{
	for(i=0;i<5000;i++)
	{
		dad[i] = -1;
		rank[i] = 0;
	}
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
long number_edges(void)
	{
		long density = 0;
		for (i=0;i<5000;i++)
		{
			
			for (j=0;j<5000;j++)
				{
					if (adjmat.at(i).at(j) != -1)
					{
					density++;
					}
				}
		}
	return density;
}
vector<vector <int> > returnfunc (void)
{
	return adjmat;
}

};

int main()
{
long num_edges;
clock_t t1 = clock();
densegraph Gdense;
Gdense.create();
//cout<<"Checkpoint 1: Dense graph created successfully."<<endl; 
clock_t t2 = clock();
num_edges = Gdense.number_edges();
//cout<<"Number of edges in the dense graph: "<<num_edges<<endl;
vector <vector <int> > adj_mat;
adj_mat.resize(5000, vector<int>(5000, -1));
adj_mat = Gdense.returnfunc(); 
kruskal network_rout(num_edges, adj_mat);
//cout<<"Checkpoint 2: The densegraph was passed successfully to Kruskal's for Max spanning tree. "<<endl;
network_rout.kruskalimplement();
//cout<<"Checkpoint 5: Maximum spanning tree computed."<<endl;
clock_t t3 = clock();
vector <vector <int> > max_span_tree;
max_span_tree.resize(5000, vector<int>(5000, -1));
max_span_tree = network_rout.returnfunc();
DFS dfs(max_span_tree);
dfs.max_bandwidth_path();
cout<<"Time for graph generation: "<<(t2-t1)/1000<<" milliseconds"<<endl;
cout<<"Time for maximum spanning tree: "<<(t3-t2)/1000<<" milliseconds"<<endl;
return 0;
}
