#include "PathDepOption05.h"
#include <cmath>
#include <iostream>

namespace fre
{
	void Rescale(SamplePath& S, int d, double x)
	{
		int m = S.size();
		for (int i = 0; i < m; i++)
		{
			S[i][d] = x * S[i][d];
		}
	}
	
	double PathDepOption::PriceByMC(MCModel& Model, long N, double epsilon)
	{
		double H = 0.0;
		SamplePath S(m);
	
		int d = Model.GetS();
		Vector Heps(d);
		for (int i = 0; i < d; i++) Heps[i] = 1.0;
		delta.resize(d);
	
		for (long i = 0; i < N; i++)
		{
			Model.GenerateSamplePath(T, m, S);
			H = (i * H + Payoff(S)) / (i + 1.0);
			for (int j = 0; j < d; j++)
			{
				Rescale(S, j, 1.0 + epsilon);
				Heps[j] = (i * Heps[j] + Payoff(S)) / (i + 1.0);
				Rescale(S, j, 1 / (1.0 + epsilon));
			}
		}
		
		for (int i = 0; i < d; i++)
		{
			delta[i] = std::exp(-Model.GetR() * T) *(Heps[i] - H) / (Model.GetS0()[i] * epsilon);
		}
	
		return std::exp(-Model.GetR() * T) * H;
	}
	
	double ArthmAsianCall::Payoff(const SamplePath& S) const
	{
		double Ave = 0.0;
		int d = S[0].size();
		Vector one(d);
		for (int i = 0; i < d; i++) one[i] = 1.0;
		for (int k = 0; k < m; k++)
		{
			Ave = (k * Ave + (one ^ S[k])) / (k + 1.0);
		}
		if (Ave < K) return 0.0;
		return Ave - K;
	}
}
