#include "Gui.hpp"
#include <QApplication>

int main(int argc, char **argv) {
	int argnum;
	char **args;
	char const *paramFile = "params.xml";
	if (argc > 1) {
		argnum = argc - 1;
		args = new char*[argnum];
		args[0] = argv[0];
		paramFile = argv[1];
		for (int i = 2; i < argc; i++) {
			args[i-1] = argv[i];
		}
	}

	QApplication a( argc, argv );
	Gui gui (paramFile);
	if(!gui.ok) return -1;
	gui.show();
	return a.exec();
}
