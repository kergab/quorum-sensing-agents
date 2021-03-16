#ifndef Gui_H
#define Gui_H
#include <QWidget>

class QTimer;
class QPushButton;
class QRadioButton;
class QCheckBox;
class QComboBox;
class QLabel;
class QFile;
class World;
class WorldWidget;

class Gui : public QWidget {
Q_OBJECT
public:
	bool ok;
	Gui(char const *pFile);
	~Gui();
protected:
	World *world;
	WorldWidget *worldWidget;
	QTimer *timer;
	QLabel *steps, *bacters, *counter;
	QPushButton *startStopButton, *stepButton, *saveButton;
	std::vector<QRadioButton*> substanceButtons;
	std::vector<std::vector<QCheckBox*>> strainBoxes;
	std::vector<std::vector<QLabel*>> countLabels, birthLabels, stateLabels;
	std::vector<std::vector<QComboBox*>> stateCombos;
	std::vector<std::vector<unsigned>> cidsPerStrains;
	std::vector<std::vector<QFile*>> statFiles;
	bool filesReady;
	bool isRunning;
private slots:
	void closeEvent(QCloseEvent *e);
	void startStopSlot();
	void stepSlot();
	void refreshSlot();
	void saveSlot();
protected:
	void start(bool on);
	void setDefaults();
};
#endif
