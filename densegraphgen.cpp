#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>
using namespace std;
class densegraph
{
	vector <vector <int> > adjmat;
	int i,j;
	public:
	densegraph()
	{
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
	void display(void)
{
	for(i = 0; i < 5000; i++)
	{
		cout<<endl<<endl<<endl<<i<<" ";
		for(j=0;j<5000;j++)
		{
			if(adjmat.at(i).at(j) != -1)
			cout<<j<<" ";
		}
	}
}
	void check(void)
	{
		double density = 0;
		int ctr[5000];
		for (i=0;i<5000;i++)
		{
			ctr[i] = 0;
			for (j=0;j<5000;j++)
				{
					if (adjmat.at(i).at(j) != -1)
					{
					//cout<<adjmat.at(i).at(j);	
					ctr[i] ++;
					density++;
					}
				}
			//cout<<i<<". "<<ctr[i]<<endl;
		}
	//cout<<density<<endl;
	density = density/ (5000*50);
	cout<<"Percentage of vertices that each vertex is connected to: "<<density<<endl;

	}
};
	
int main()
{
	
	
	clock_t t1, t2;
	t1 = clock();
	densegraph G;
	G.create();
	G.check();
	//G.display();
	t2 = clock();
	float prog_runtime = float(t2 - t1);
    prog_runtime = prog_runtime / CLOCKS_PER_SEC;
    cout<<endl<<"The program ran in " <<prog_runtime<<" seconds.";
return 0;
}

