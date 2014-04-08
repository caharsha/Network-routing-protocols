#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;
class sparsegraph
{
	vector <vector <int> > adjmat;	//Vector of vectors
	int i,j, ctr[5000],temp;
public:
sparsegraph()
{
	for(i = 0; i < 5000; i++)
		ctr[i] = 0;
	adjmat.resize(5000, vector<int>(5000, -1));
}
void create(void)
{
	srand (time(NULL));
	for(i = 0;i< 5000; i++)
	{	
		for (j = 0; j < 5000; j++)
		{
			if(ctr[i] == 6)
				continue;
			temp = rand() % 5000;
			if(i!=temp)
			if(adjmat.at(i).at(temp) == -1)
			if(ctr[i] < 6)
			if(ctr[temp] < 6)
				{
					adjmat.at(i).at(temp) = rand() % 32767;
					adjmat.at(temp).at(i) = adjmat.at(i).at(temp);
					++ctr[i];
					++ctr[temp];
				}
				
		}
	}
}
void check(void)
{
	for(i = 0; i < 5000; i++)
	{
		cout<<endl<<i<<" ";
		for(j=0;j<5000;j++)
		{
			if(adjmat.at(i).at(j) != -1)
			cout<<j<<" ";
		}
	}
}
};

int main()
{
	clock_t t1, t2;
	t1 = clock();
	sparsegraph G;
	G.create();
	//G.check();
	t2 = clock();
	float prog_runtime = float(t2 - t1);
    prog_runtime = prog_runtime / CLOCKS_PER_SEC;
    cout<<"The program ran in " <<prog_runtime<<" seconds.";
	return 0;
}
