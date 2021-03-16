#include "Uniform.hpp"
#include <random>
#include <string>
#include <sstream>
#include <QDataStream>

std::random_device Uniform::rd;
std::mt19937 Uniform::gen(Uniform::rd());
std::uniform_real_distribution<double> Uniform::dis(0,1);

double Uniform::get() {return dis(gen);}

QString Uniform::state() {
	std::stringstream ss;
	ss << gen;
	return QString::fromStdString(ss.str());
}

void Uniform::seed(const QString& s) {
	std::stringstream ss(s.toStdString());
	ss >> gen;
}
