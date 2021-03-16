#ifndef Strain_HPP
#define Strain_HPP
#include <list>
#include <vector>
#include <QPointF>
#include <QString>
struct Bacter;
struct StrainDescriptor;
class Cultures;
class QImage;
class Diffusion;
struct Stat{
	QString culture;
	unsigned count, birth;
	std::vector<unsigned> countsPerStates;
};
class Strain : public std::list<Bacter*> {
public:
	double division;
	std::vector<Stat> stat;
	virtual ~Strain();
	virtual void init(StrainDescriptor& s) = 0;
	void set(StrainDescriptor& s);
	virtual Bacter* bacter() = 0;
	virtual void update(QImage& image, unsigned culture = 0);
	void step(Diffusion& diffusion);
	void fillStates();
};
#endif
