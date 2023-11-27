#include <QApplication>
#include <QDesktopServices>
#include <QKeySequence>
#include <QMainWindow>

#include "qtermwidget.h"

void activateLink(const QUrl &url, bool fromContextMenu) {
	if (QApplication::keyboardModifiers() & Qt::ControlModifier ||
			fromContextMenu) {
		QDesktopServices::openUrl(url);
	}
}

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QMainWindow *mainWindow = new QMainWindow();

	setenv("TERM", "xterm-256color", 1);

	QTermWidget *console = new QTermWidget();

	QFont font = QApplication::font();

	// Add a blinking cursor
	console->setBlinkingCursor(true);
	// Add a 10px margin
	console->setMargin(12);
	console->setTerminalSizeHint(false);
	console->setHistorySize(100);

	/* START CONFIG BLOCK */

	/* Font Family and Font Point Size */
	font.setFamily("Iosevka NF");
	font.setPointSize(12);
	console->setTerminalFont(font);

	/* Set opacity */
	console->setTerminalOpacity(1.0);

	/* Set colorscheme */
	console->addCustomColorSchemeDir("/usr/share/literm/colorschemes");
	console->setColorScheme("Gruvbox");

	/* END CONFIG BLOCK */

	QObject::connect(console, &QTermWidget::termKeyPressed, mainWindow,
					[=](const QKeyEvent *key) -> void {
						if (key->matches(QKeySequence::Copy)) {
							console->copyClipboard();
						}
					});
	QObject::connect(console, &QTermWidget::urlActivated, mainWindow,
					activateLink);

	QObject::connect(console, SIGNAL(finished()), mainWindow, SLOT(close()));
	mainWindow->setCentralWidget(console);
	mainWindow->show();
	
	return app.exec();
}
