#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

class Distribution
{
public:
	Distribution();
	virtual double GetRV() = 0;
	virtual double GetMean() = 0;
protected:
	double Uniform_0_1();
};

class Exponential : public Distribution
{
public:
	Exponential(double mean);
	double GetRV();
	double GetMean();
private:
	double _mean;
};

class Uniform : public Distribution
{
public:
	Uniform(double min, double max);
	double GetRV();
	double GetMean();
private:
	double _min, _max;
};

class Triangular : public Distribution
{
public:
	Triangular(double min, double expected, double max);
	double GetRV();
	double GetMean();
private:
	double a, b, c, fc, term1, term2;
};

class Normal : public Distribution
{
public:
	Normal(double mean, double stdev);
	double GetRV();
	double GetMean();
private:
	bool _isSavedRV;
	double _savedRV;
	double _mean;
	double _variance;
};

class Poisson : public Distribution
{
public:
	Poisson(double mean);
	double GetRV();
	double GetMean();
private:
	double _mean;
};

class Constant : public Distribution
{
public:
	Constant(double mean);
	double GetRV();
	double GetMean();
private:
	double _mean;
};

class Weibull : public Distribution
{
public:
	Weibull(double scale, double shape);
	double GetRV();
	double GetMean();
private:
	double _scale, _shape;
};

class Erlang : public Distribution
{
public:
	Erlang(int scale, double shape);
	double GetRV();
	double GetMean();
private:
	int _scale;
	double _shape;
};

#endif
