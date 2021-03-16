#ifndef Uniform_HPP
#define Uniform_HPP
#include <random>
#include <QString>
class Uniform {
public:
static	double get();
static	QString state();
static	void seed(const QString& s);
protected:
static	std::random_device rd;
static	std::mt19937 gen;
static	std::uniform_real_distribution<double> dis;
};
#endif
