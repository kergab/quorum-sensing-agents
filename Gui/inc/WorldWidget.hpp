#ifndef WorldWidget_HPP
#define WorldWidget_HPP
#include "World.hpp"
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class WorldWidget : public QWidget {
public:
	WorldWidget(World* w) : QWidget(), world(w) {setFixedSize(w->size());}
	void paintEvent(QPaintEvent*) {
		if(!world) return;
		QPainter p(this);
		p.drawImage(QPoint(0,0), world->image);
	}
protected:
	World* world;
};
#endif
