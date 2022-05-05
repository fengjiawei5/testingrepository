#include "MCModel02.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
namespace fre
{
	const double pi = 4.0 * atan(1.0);

	double Gauss()
	{
		double U1 = (rand() + 1.0) / (RAND_MAX + 1.0);
		double U2 = (rand() + 1.0) / (RAND_MAX + 1.0);
		return sqrt(-2.0 * log(U1)) * cos(2.0 * pi * U2);
	}
	
	Vector Gauss(int d)
	{
		Vector Z(d);
		for (int j = 0; j < d; j++) Z[j] = Gauss();
		return Z;
	}
	
	MCModel::MCModel(Vector S0_, double r_, Matrix C_)
	{
		S0 = S0_; r = r_; C = C_; srand(time(NULL));
		int d = S0.size();
		sigma.resize(d);
		for (int j = 0; j < d; j++)
		{
			sigma[j] = sqrt(C[j] ^ C[j]);//C[j] is means the jth vector of C
		}//compute sigma and store in a vector with length d
	}
	
	void MCModel::GenerateSamplePath(double T, int m, SamplePath& S) const
	{
		Vector St = S0;
		int d = S0.size();
		for (int k = 0; k < m; k++)
		{
			S[k] = St * exp((T / m) * (r + (-0.5) * sigma * sigma) + sqrt(T / m) * (C * Gauss(d)));
			St = S[k];
		}
		//St = 3 end prices for 3 different S0 after m periods, repeat this for N times
		//S = path of 30 different prices
	}
}


