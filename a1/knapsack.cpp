#include <iostream>
#include <stdlib.h>
#include <chrono>

using namespace std;

int* weights;
int* values;
int** opt;

int knapsack(int n, int curr, int c)
{
	/*find the optimal value of the knapsack with
	items curr to n, capacity c, and weights and values given
	*/
	
	//base case, we are on the last item
	if(curr == n - 1)
	{
		if(weights[curr] <= c)
		{
			//take if we can
			return values[curr];
		}
		else
		{
			//leave otherwise
			return 0;
		}
	}
	
	if(opt[curr][c] != -1)
	{
		//value already computed
		return opt[curr][c];
	}
	//need to compute the value
	
	//optimal value not taking item curr
	int leave = knapsack(n, curr + 1, c);
	int take = -1;
	
	if(c >= weights[curr])
	{
		//take the item, reducing capacity, but gaining value
		take = knapsack(n, curr + 1, c-weights[curr]) + values[curr];
	}
	
	if(leave > take)
	{
		opt[curr][c] = leave;
	}
	else
	{
		opt[curr][c] = take;
	}
	return opt[curr][c];
}

int main(int argc, char* argv[])
{
	using chrono::high_resolution_clock;
	using chrono::duration;
	
	auto start = high_resolution_clock::now();
	
	int n; //number of items in the knapsack
	cin >> n;
	int c; //capacity of the sack
	cin >> c;
	weights = new int[n]; //array to store the weights of the items
	values = new int[n]; //array to store the values of the items
	for(int i = 0; i<n; i++)
	{
		cin >> weights[i];
		cin >> values[i];
	}
	
	//initialize the array for dynamic programming
	opt = new int*[n];
	for(int i=0; i<n; i++)
	{
		opt[i] = new int[c+1];
		//intialize to -1
		for(int j=0; j<c+1; j++)
		{
			opt[i][j] = -1;
		}
	}
	
	int highest = knapsack(n, 0, c);
	
	auto end = high_resolution_clock::now();
	duration<double, milli> time = end - start;
	
	cout << "The maximum value is " << highest << "." << endl;
	cout<<"Duration: "<<time.count() <<" miliseconds."<<endl;
}