#include <iostream>
#include <string>
#include <map>
using namespace std;
class DefInt
{
private:
	string name;
protected:
	double a, b;
	int N;
	double (*f)(double x);
public:
	DefInt(double a_, double b_, int N_, double (*f_)(double x)) :a(a_), b(b_), N(N_), f(f_), name("") {}
	virtual double Approximation() = 0;
	virtual string GetName() = 0;
	virtual ~DefInt() {}
};

class ByTrapezoid : public DefInt
{
private:
	string name;
public:
	// Complete the implementation of the constructor with parameters for class ByTrapezoid. 
	// You are not allowed to create other member functions.
	ByTrapezoid(double a_, double b_, int N_, double (*f_)(double x)) : DefInt(a_, b_, N_, f_), name("ByTrapezoid") {}
	~ByTrapezoid() {}
	double Approximation();
	string GetName() { return name; }
};

double ByTrapezoid::Approximation()
{
	cout << "ByTrapezoid: ";
	double h = (b - a) / N;
	double Result = 0.5 * f(a);
	for (int n = 1; n < N; n++) Result += f(a + n * h);
	Result += 0.5 * f(b);
	return Result * h;
}

class BySimpson : public DefInt
{
private:
	string name;
public:
	// Complete the implementation of the constructor with parameters for class BySimpson. 
	// You are not allowed to create other member functions.
	BySimpson(double a_, double b_, int N_, double (*f_)(double x)) : DefInt(a_, b_, N_, f_), name("BySimpson") {}
	~BySimpson() {}
	double Approximation();
	string GetName() { return name; }
};

double BySimpson::Approximation()
{
	cout << "BySimpson ";
	double h = (b - a) / N;
	double Result = f(a);
	for (int n = 1; n < N; n++) Result += 4 * f(a + n * h - 0.5 * h) + 2 * f(a + n * h);
	Result += 4 * f(b - 0.5 * h) + f(b);
	return Result * h / 6;
}

template<typename Type>
class Calculation
{
private:
	Type* ptr1;
	Type* ptr2;
	map<string, double>resultMap;
public:
	Calculation(Type* ptr1_, Type* ptr2_) :ptr1(ptr1_), ptr2(ptr2_) {}

	void Populatemap()
	{
		resultMap[ptr1->GetName()] = ptr1->Approximation();
		resultMap[ptr2->GetName()] = ptr2->Approximation();
	}

	void Display()
	{
		for (map<string, double>::iterator itr = resultMap.begin(); itr != resultMap.end(); itr++)
		{
			cout << itr->first << ": " << itr->second << endl;
		}
	}
};

double f(double x) { return x * x * x - x * x + 1; }
int main()
{
	double a = 1.0;
	double b = 2.0;
	int N = 1000;

	DefInt* ptr1 = new ByTrapezoid(a, b, N, f);
	DefInt* ptr2 = new BySimpson(a, b, N, f);

	Calculation<DefInt> calc(ptr1, ptr2);
	calc.Populatemap();
	calc.Display();

	delete ptr1;
	delete ptr2;
	ptr1 = nullptr;
	ptr2 = nullptr;

	return 0;
}