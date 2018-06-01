//This is the test cpp file
// for MC method on option pricing


#include "MCOptionData.hpp" 
#include <cmath>
#include <iostream>
#include <vector> 
#include<numeric> //find mean and sd

//we need to define some functions

using namespace std;

struct SimOut{
	double mean;
	double sd;
	double se;
};

double getMean(const std::vector<double>& v)
{	//get mean of a double vector
	double sum = std::accumulate(v.begin(), v.end(), 0.0);
	double out = sum / v.size();
	return(out);
}

double getSD(const std::vector<double>& v)
// No need disconted factor here since I have done it in calculating option price
{	//get std of a double vector
	double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
	double mu = getMean(v);
	double out = std::sqrt((sq_sum - (1/ v.size()) * mu * mu)/(v.size() - 1)); 
	return(out);
}

double getSE(const std::vector<double>& v)
{	
	double out = getSD(v)/sqrt(v.size());
	return(out);
}


SimOut getMCOptionPrice(long NT, long NSIM, const OptionData& op, double S)
{	// This is a function to get MC simulated mean and std on one option at current price S
	
	double dt = op.T/NT;// parameters needed in the formula
	double A = op.r - op.b;
	double B = op.sig;
	double sqrt_dt = sqrt(dt);

	SimOut out; // output holder
	vector<double> SimsHolder(NSIM);

	double S_old = S;
	double S_new;

	for(long j =0; j<NSIM; j++)
	{
		for(long i =0; i<NT; i++)
		{
			S_new = S_old + A*S_old*dt + B*S_old*sqrt_dt*getz(); // the function
			S_old = S_new;
		}
		SimsHolder[j] = exp(-op.r*op.T)*op.PayOff(S_new); // for each sim, the pay-off is obtained
		S_old = S; //Set the S_old to the original value
	}

	out.mean = getMean(SimsHolder);
	out.sd = getSD(SimsHolder);
	out.se = getSE(SimsHolder);
	return(out);
}

vector<vector<double> > MC_MeanPrice_NTvsNSIM(const vector<long>& NT, const vector<long>& NSIM, const OptionData& op, double S, string OutPutMetric = "mean")
{	//this is a function doing simultion across NT and NSIM
	// you can also choose the metric you want to measure the simulation performance
	long rowsize = NSIM.size();
	long colsize = NT.size();
	vector<vector<double> > out(rowsize, vector<double>(colsize));

	SimOut temp;

	for(long i = 0; i<rowsize; i++)
	{
		for(long j = 0; j<colsize; j++)
		{
			temp = getMCOptionPrice(NT[j], NSIM[i], op, S);
			if (OutPutMetric == "mean"){
				out[i][j] = temp.mean;
			} else if (OutPutMetric == "sd"){
				out[i][j] = temp.sd;
			} else if (OutPutMetric == "se"){
				out[i][j] = temp.se;
			} else {
				out[i][j] = temp.mean;
			}	

		}
	}
	return(out);
}

int main(){
	////////////////////////////////////////////////////////////////////////////
	////////////				Group C									////////
	///////////															////////
	////////////////////////////////////////////////////////////////////////////

    ////////////////////////////    Question a and b ////////////////////////////////
	// Bacth 1 and Batch 2
	OptionData op1;
	op1.T = 1.5;
	op1.K =120.0;
	op1.sig = .4;
	op1.r =0.04;
	op1.b = 0.0;
	op1.OptionType = "P";

	// OptionData op2;
	// op2.T = 1;
	// op2.K =100;
	// op2.sig = .20;
	// op2.r =0.0;
	// op2.b = 0.0;
	// op2.OptionType = "C";

	long arr1[] = {10, 100, 500};
	vector<long> NTs(arr1, arr1 + (sizeof(arr1)/sizeof(long)));

	long arr2[] = {10, 50, 100, 500, 1000, 5000, 10000};
	vector<long> NSIMs(arr2, arr2 + (sizeof(arr2)/sizeof(long)));

	vector<vector<double> > NT_vs_NSIM_op1 = MC_MeanPrice_NTvsNSIM(NTs, NSIMs, op1, 100);
	// vector<vector<double> > NT_vs_NSIM_op2 = MC_MeanPrice_NTvsNSIM(NTs, NSIMs, op2, 100);

	cout << "MC simluated Call prices for Batch 1 across conditions: " << endl;
	Print2d(NT_vs_NSIM_op1);

	// cout << "\nMC simluated Call prices for Batch 2 across conditions: " << endl;
	// Print2d(NT_vs_NSIM_op2);


	//  ////////////////////////////    Question c   ////////////////////////////////

	// OptionData Batch4;
	// Batch4.T = 30;
	// Batch4.K =100.0;
	// Batch4.sig = .30;
	// Batch4.r =0.08;
	// Batch4.b = 0.0;
	// Batch4.OptionType = "C";

	// vector<vector<double> > NT_vs_NSIM_Batch4 = MC_MeanPrice_NTvsNSIM(NTs, NSIMs, Batch4, 100);

	// cout << "\n\nMC simluated Call prices for Batch 4 across conditions: " << endl;
	// Print2d(NT_vs_NSIM_Batch4);

	// ////////////////////////////////////////////////////////////////////////////
	// ////////////				Group D									////////
	// ///////////															/////////
	// ////////////////////////////////////////////////////////////////////////////

	//  ////////////////////////////    Question a&b   ////////////////////////////////
	// vector<vector<double> > NT_vs_NSIM_op1_sd = MC_MeanPrice_NTvsNSIM(NTs, NSIMs, op1, 60, "sd");
	// vector<vector<double> > NT_vs_NSIM_op2_sd = MC_MeanPrice_NTvsNSIM(NTs, NSIMs, op2, 100, "sd");
	// cout << "\nMC simluated Call StDev for Batch 1 across conditions: " << endl;
	// Print2d(NT_vs_NSIM_op1_sd);

	// cout << "\nMC simluated Call StDev for Batch 2 across conditions: " << endl;
	// Print2d(NT_vs_NSIM_op2_sd);

	// vector<vector<double> > NT_vs_NSIM_op1_se = MC_MeanPrice_NTvsNSIM(NTs, NSIMs, op1, 60, "se");
	// vector<vector<double> > NT_vs_NSIM_op2_se = MC_MeanPrice_NTvsNSIM(NTs, NSIMs, op2, 100, "se");
	// cout << "\n\nMC simluated Call StErr for Batch 1 across conditions: " << endl;
	// Print2d(NT_vs_NSIM_op1_se);

	// cout << "\nMC simluated Call StErr for Batch 2 across conditions: " << endl;
	// Print2d(NT_vs_NSIM_op2_se);

	return 0;

}
