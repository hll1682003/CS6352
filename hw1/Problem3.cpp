#include <iostream>
#include <xtgmath.h>
#include<iomanip>
using namespace std;

//the funcion that generate all the 10000 items in the equation
double* seriesGen(int number, double k, double m) {
	double* current=new double[number+1]();
	*current = 1111;
	double* previous = current;
	current++;
	double* start = current;
	for (int i = 1; i <=(number+1); i++)
	{
	//generate Sn+1 based on Sn
		double newItem = fmod(*previous*k,m);
		*current = newItem;
		previous = current;
		current++;
	}
	return start;
}

double mean(double* startPoint, int number) {
	double sum = 0;
	for (int i = 1; i <= number; i++)
	{
		sum += *startPoint;
		startPoint++;
	}
	sum /= number;
	return sum;
}

 double variance(double* startPoint, int number, double average) {
	 double temp=0;
	 for (int i = 1; i <= number; i++)
	 {
		 temp += pow((*startPoint - average),2);
		 startPoint++;
	 }
	 temp /= number;
	 return temp;
}

 double expRv(double uniRv,double lambda)
 {
	 double exp;
	 exp = ((-1) / lambda) * log(uniRv);
	 return(exp);
 }

int main(int argc, char *argv[]) {
	double *p = seriesGen(10000, 16807, 2147483647);
	double* startPointTemp = p;
	//for the problem 4:
	double rs[100001] = { 0 };
	int rsCount = 1;
	int rGenCount[11] = { 0 };
	for (double j = 1; j <= 10; j++)
	{
		double lowerBound = (j - 1) / 10;
		double upperBound = (j / 10);
		for (int i = 1; i <= 10000; i++)
		{	
			double k = *startPointTemp / 2147483647;
			rs[rsCount] = k;
			rsCount++;
			if (k >= lowerBound && k <= upperBound)
			{
				rGenCount[(int)j]++;
			}
			startPointTemp++;
		}
		//reset the pointer to the beginning of the series
		startPointTemp = p;
	}
	for (double i = 1; i <= 10; i++)
	{
		double lowerBound = (i - 1) / 10;
		double upperBound = (i / 10);
		cout << "the counts for Rn of the interval ["<< lowerBound<<", "<<upperBound<<"] is: " << rGenCount[(int)i]<<"\n";
	}
	double average=mean(p,10000);
	cout.setf(ios::fixed);
	cout << "average= " <<setprecision(2)<< average << "\n";
	cout << "variance= "<<variance(p, 10000, average)<<"\n";
	cout << "----------------------------------" << "\n";
	double lambda = 2;
	double expNumbers[10001] = { 0 };
	for (int i = 1; i <= 10000; i++)
	{
		expNumbers[i] = expRv(rs[i], lambda);
	}
	double expMean = mean(&expNumbers[1], 10000);
	double expVariance = variance(&expNumbers[1], 10000, expMean);
	cout << "The calculated mean of exponential r.v.s= " << expMean << "\n";
	cout << "The calculated Variance of exponential r.v.s=" << expVariance << "\n";
	cout << "The Theoretical mean of exponential r.v.s= "<<1/lambda<<"\n";
	cout << "The Theoretical variance of exponential r.v.s= "<<1/lambda/lambda<<"\n";
	cout << "----------------------------------" << "\n";
	
	int bits[100001] = { 0 };
	bool correctness[100001] = { false };
	
	for (int i = 1; i <= 100000; i++)
	{
		if (rs[i] > 0.45)
		{
			bits[i] = 1;
		}
		else
		{
			bits[i] = 0;
		}
		if (bits[i] == 1)
		{
			if (rs[i] > 0.95)
			{
				correctness[i] = false;
			}
			else
			{
				correctness[i] = true;
			}
		}
		else
		{
			if (rs[i] > 0.85)
			{
				correctness[i] = false;
			}
			else
			{
				correctness[i] = true;
			}
		}
	}
	
	
	//calculate the statistics
	double zeroRatio = 0;
	double oneRatio = 0;
	double zeroCorrect = 0;
	double oneCorrect = 0;
	for (int j = 1; j <= 100000; j++)
	{
		//the current bit is 0
		if (bits[j] = 0)
		{
			zeroRatio++;
			if (correctness[j] == true)
			{
				zeroCorrect++;
			}
		}
		//the current bit is 1
		else
		{
			oneRatio++;
			if (correctness[j] == true)
			{
				oneCorrect++;
			}
		}
	}
	zeroCorrect /= zeroRatio;
	zeroRatio /= 100000;
	oneCorrect /= oneRatio;
	oneRatio /= 100000;
	cout << "The prob that a 0 is received is: " << oneRatio << "\n";
	cout << "The prob that a 1 was transmitted given that a 1 was received is: " << oneRatio*oneCorrect/(zeroRatio*(1-zeroCorrect)+ oneRatio*oneCorrect)<<"\n";
	cout << "The prob of an error is: " << zeroRatio*(1 - zeroCorrect) + oneRatio*(1 - oneCorrect) << "\n";
	
}
