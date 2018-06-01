// This is a source file for Normal Generator and Printer Functions
#include "MCOptionData.hpp"
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include<iostream>

using namespace std;

boost::mt19937 rng; // random generator

double getz()
{	
	// boost::mt19937 rng; // random generator
	boost::normal_distribution<> StdNorm(0.0, 1.0); //standard normal
	double out;
	out = StdNorm(rng);
	return(out);
}


vector<double> getz(long N)
{
	boost::normal_distribution<> StdNorm(0.0, 1.0); //standard normal
	vector<double> out(N);
	
	for(long i = 0; i<N; i++){
		out[i] = StdNorm(rng);
	}

	return(out);
} 

void Print1d (const vector<double>& v) // Print a double vector
{
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
}

void Print2d (const vector<vector<double> >& v) // Print a matrix
{
	for(int j = 0; j < v[0].size(); j++)
	{
		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	
}

