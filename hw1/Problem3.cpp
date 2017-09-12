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
//the function that counts outcomes in each interval
int* rGen(double* startPoint, int number, double m) {
	double* startPointTemp = startPoint;
	int* rGenCount=new int[10]();
	int* countTemp = rGenCount;
	for (double j = 1; j <= 10; j++)
	{
		double lowerBound = (j - 1) / 10;
		double upperBound = (j / 10);
		//debug
		//cout << "lowerbound=" << lowerBound << "\n";
		//debug
		//cout << "upperBound=" << upperBound << "\n";
		for (int i = 1; i <= number; i++)
		{	//debug
			//cout << "number=" << i<<"\n";
			double k = *startPointTemp / m;
			//debug
			//cout << "k=" << k << "\n";
			if (k >= lowerBound && k <= upperBound)
			{
				*countTemp++;
			}
			startPointTemp++;
		}
		//debug
		cout << "Count is: " << *countTemp << "\n";
		countTemp++;
		//reset the pointer to the beginning of the series
		startPointTemp = startPoint;
	}
	return rGenCount;
}

int mean(double* startPoint, int number) {
	startPoint
}

int main(int argc, char *argv[]) {
	double *p = seriesGen(10000, 16807, 2147483647);
	//int *q = rGen(p, 10000, 2147483647);
	
	double* startPointTemp = p;
	int rGenCount[11] = { 0 };
	for (double j = 1; j <= 10; j++)
	{
		double lowerBound = (j - 1) / 10;
		double upperBound = (j / 10);
		//debug
		//cout << "lowerbound=" << lowerBound << "\n";
		//debug
		//cout << "upperBound=" << upperBound << "\n";
		for (int i = 1; i <= 10000; i++)
		{	//debug
			//cout << "number=" << i<<"\n";
			double k = *startPointTemp / 2147483647;
			//debug
			//cout << "k=" << k << "\n";
			if (k >= lowerBound && k <= upperBound)
			{
				rGenCount[(int)j]++;
			}
			startPointTemp++;
		}
		//debug
		cout << "Count is: " << rGenCount[(int)j] << "\n";
		//reset the pointer to the beginning of the series
		startPointTemp = p;
	}

	/*
	for (int i = 1; i <= 10000; i++)
	{
		cout << "The " << i << "th item: " << *p << "\n";
		p++;
	}
	*/
	for (double i = 1; i <= 10; i++)
	{
		double lowerBound = (i - 1) / 10;
		double upperBound = (i / 10);
		cout << "the counts for Rn of the interval ["<< lowerBound<<", "<<upperBound<<"] is: " << rGenCount[(int)i]<<"\n";
	}
	
	
}
