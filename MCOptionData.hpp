//This is a header file containing
//a) a OptionData Struct, 
//b) some functions 
//c) generators


#ifndef MCOptionData_HPP
#define MCOptionData_HPP

#include <algorithm> // for max()
#include <string>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////

struct OptionData // the struct 
{ // Option data + behaviour

	double T;
	double K;
	double sig;
	double r;
	double b;
	

	string OptionType;		// 1 == call, -1 == put

	double PayOff(double S) const
	{ // Payoff function

		if (OptionType == "C")
		{ // Call

			return max(S - K, 0.0);
		}
		else
		{ // Put
		
			return max (K - S, 0.0);
		}
	}

	void toggle(){
		if (OptionType == "C")
		{ // Call

			OptionType = "P";
		}
		else
		{ // Put
		
			OptionType = "C";
		}
	}
};

//////////////////////////////////////////////////////////////////////////////////////////

double getz(); // single generator
vector<double> getz(long N); // multiple generator

//////////////////////////////////////////////////////////////////////////////////////////
void Print1d (const vector<double>& v); //Printers
void Print2d (const vector<vector<double> >& v);


#endif