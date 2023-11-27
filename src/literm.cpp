#include <QApplication>
#include <QKeySequence>
#include <QMainWindow>

#include "qtermwidget.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QMainWindow *mainWindow = new QMainWindow();

	setenv("TERM", "konsole-256color", 1);

	QTermWidget *console = new QTermWidget();

	QFont font = QApplication::font();

	/* Font Family and Font Point Size */
	font.setFamily("Monospace");
	font.setPointSize(12);
	console->setTerminalFont(font);

	/* Set colorscheme */
	// See other in src/colorschemes
	console->addCustomColorSchemeDir("src/colorschemes");
	console->setColorScheme("Gruvbox");

	QObject::connect(console, SIGNAL(finished()), mainWindow, SLOT(close()));
	mainWindow->setCentralWidget(console);
	mainWindow->show();
	
	return app.exec();
}
