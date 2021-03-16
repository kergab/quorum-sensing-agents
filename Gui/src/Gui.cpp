#include <QCloseEvent>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QMessageBox>
#include <QTimer>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "Gui.hpp"
#include "WorldWidget.hpp"
#include "World.hpp"
#include "Params.hpp"
#include "Strain.hpp"

#include <unistd.h>
#include <iostream>
using namespace std;

Gui::Gui(char const *pFile) : world(0), isRunning(false) {
	ok = true;
	if ((pFile == NULL) || ((pFile != NULL) && (pFile[0] == '\0'))) {
		ok = false;
		return;
	}
	world = new World(pFile);
	if(world->ok == false) {
		QMessageBox::critical(0, "Critical Error!", world->params.message);
		ok = false;
		return;
	}
	filesReady = true;
	for(unsigned n = 0; n < world->params.strainDescriptors.size() && filesReady; n++) {
		std::vector<QFile*> files;
		for(unsigned k = 0; k < world->params.strainDescriptors[n].cultures.id.size(); k++) {
			QString name = world->params.strainDescriptors[n].name;
			name += "-" + world->params.strainDescriptors[n].cultures.id[k];
			name += ".txt";
			QFile* file = new QFile(name);
			if(file->open(QIODevice::WriteOnly | QIODevice::Text)) files.push_back(file);
			else {filesReady = false; break;}
		}
		statFiles.push_back(files);
	}

	setWindowTitle(tr("Quorum Sensing Simulation"));

	QGroupBox *settingsGroup = new QGroupBox(this);
	settingsGroup->setFixedWidth(260);

	QVBoxLayout *tL = new QVBoxLayout(settingsGroup);

	tL->addWidget(new QRadioButton("None"));
	SubstanceDescriptors& sds = world->params.substanceDescriptors;
	if(sds.size() < 1) exit(0);
	for (unsigned i = 0; i < sds.size(); i++) {
		QRadioButton *button = new QRadioButton(sds[i].name);
		substanceButtons.push_back(button);
		tL->addWidget(button);
	}
	substanceButtons[0]->setChecked(true);
	StrainDescriptors& stds = world->params.strainDescriptors;
	unsigned strainCount = stds.size();
	for(unsigned is = 0; is < strainCount; is++) {
		std::vector<QCheckBox*> strain;
		std::vector<QLabel*> count, birth;
		std::vector<QComboBox*> state;
		QGroupBox* strainGroup = new QGroupBox(stds[is].name);
		QGridLayout* layout = new QGridLayout(strainGroup);
		layout->setColumnMinimumWidth(3, 40);
		tL->addWidget(strainGroup);
		for(unsigned ic = 0; ic < stds[is].cultures.id.size(); ic++) {
			QCheckBox *cid = new QCheckBox(QString("%1").arg(stds[is].cultures.cids[ic]));
			strain.push_back(cid);
			layout->addWidget(cid, ic, 0);
			QLabel* c = new QLabel(QString("%1").arg(world->strains[is]->stat[ic].count));
			count.push_back(c);
			layout->addWidget(c, ic, 1);
			c = new QLabel(QString("%1").arg(world->strains[is]->stat[ic].birth));
			birth.push_back(c);
			layout->addWidget(c, ic, 2);
			QComboBox* cb = new QComboBox();
			cb->setMinimumContentsLength(8);
			state.push_back(cb);
			for(unsigned n = 0; n < world->strains[is]->stat[ic].countsPerStates.size(); n++)
				cb->addItem("0");
			layout->addWidget(cb, ic, 3);
		}
		strainBoxes.push_back(strain);
		countLabels.push_back(count);
		birthLabels.push_back(birth);
		stateCombos.push_back(state);
	}

	tL->addStretch(1);
	QGroupBox* group = new QGroupBox();
	QGridLayout* layout = new QGridLayout(group);
	layout->addWidget(startStopButton = new QPushButton(QString(tr("Start"))), 0, 0);
	layout->addWidget(stepButton = new QPushButton(QString(tr("Step"))), 0, 1);
	layout->addWidget(saveButton = new QPushButton(QString(tr("Save Image"))), 1, 0);
	layout->addWidget(counter = new QLabel("0"), 1, 1);
	tL->addWidget(group);
	worldWidget = new WorldWidget(world);

	QHBoxLayout *mL = new QHBoxLayout(this);
	mL->addWidget(settingsGroup);
	mL->addWidget(worldWidget);

	connect(startStopButton, SIGNAL(clicked()), this, SLOT(startStopSlot()));
	connect(stepButton, SIGNAL(clicked()), this, SLOT(stepSlot()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSlot()));
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(refreshSlot()));
	timer->setSingleShot(false);
	timer->start(500);
}

Gui::~Gui() {
	start(false);
	for(std::vector<QFile*> files : statFiles) {
		for(QFile* file : files) {
			file->close();
			delete file;
		}
	}
}

void Gui::setDefaults() {}
//note to self: isn't used - shouldn't be replaced by restart?

void Gui::closeEvent(QCloseEvent *e) {e->accept();}

void Gui::refreshSlot() {
	for(std::vector<unsigned>& cids : cidsPerStrains) cids.clear();
	cidsPerStrains.clear();
	unsigned sub = 0;
	for(sub = 0; sub < substanceButtons.size(); sub++)
		if(substanceButtons[sub]->isChecked()) break;
	for(std::vector<QCheckBox*> s: strainBoxes) {
		std::vector<unsigned> cids;
		for(unsigned c = 0; c < s.size(); c++) {
			if(s[c]->isChecked()) {
				cids.push_back(c);
			}
		}
		cidsPerStrains.push_back(cids);
	}
	for(Strain* st : world->strains) st->fillStates();
	for(unsigned s = 0; s < world->strains.size(); s++) {
		std::vector<Stat> stat = world->strains[s]->stat;
		for(unsigned r = 0; r < stat.size(); r++) {
			countLabels[s][r]->setText(QString("%1").arg(stat[r].count));
			birthLabels[s][r]->setText(QString("%1").arg(stat[r].birth));
			for(unsigned n = 0; n < stat[r].countsPerStates.size(); n++) {
				stateCombos[s][r]->setItemText(n, QString("%1").arg(stat[r].countsPerStates[n]));
			}
		}
	}
	counter->setText(QString("%1").arg(world->counter));
	world->update(sub, cidsPerStrains);
	worldWidget->update();
	if(!(filesReady && world->isRunning())) return;
	for(unsigned n = 0; n < statFiles.size(); n++) {
		for(unsigned k = 0; k < statFiles[n].size(); k++) {
			QFile* file = statFiles[n][k];
			QTextStream out(file);
			Stat& stat = world->strains[n]->stat[k];
			QString line = QString("%1").arg(world->counter) + "\t" + QString("%1").arg(stat.count);
			for(unsigned l = 0; l < stat.countsPerStates.size(); l++) {
				line += "\t";
				line += QString("%1").arg(stat.countsPerStates[l]);
			}
			line += "\n";
			out << line;
		}
	}
}

void Gui::startStopSlot() {start(!isRunning);}

void Gui::start(bool on) {
	if(on == isRunning) return;
	if(on) {
		startStopButton->setText(tr("Stop"));
		world->start();
	} else {
		startStopButton->setText(tr("Start"));
		world->stop();
	}
	isRunning = on;
}

void Gui::stepSlot() {world->step();}

void Gui::saveSlot() {
	QFileDialog dialog(this);
	dialog.setNameFilter("*.jpg *.png");
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	if (dialog.exec() != QDialog::Accepted) return;
	const QString name = dialog.selectedFiles().first();
	world->image.save(name);
//	file.open(QIODevice::WriteOnly);
//  	QDataStream out(&file);
}
