#include <QApplication>
#include <QFontDatabase>

#include "mainwindow.h"
#include "businesslayer/style.h"

using namespace businesslayer;

int main(int argc, char **argv)
{
	QApplication app(argc, argv);


	QFontDatabase::addApplicationFont(":/fonts/lato");
	QFontDatabase::addApplicationFont(":/fonts/lato-bold");
	QFontDatabase::addApplicationFont(":/fonts/lato-bold-italic");
	QFontDatabase::addApplicationFont(":/fonts/lato-italic");
	QFontDatabase::addApplicationFont(":/fonts/lato-light");
	QFontDatabase::addApplicationFont(":/fonts/lato-light-italic");


	QFont defaultFont("Lato");
	defaultFont.setPixelSize(13);
	defaultFont.setWeight(QFont::Normal);


	Style css;

#ifdef QT_DEBUG
	qDebug() << qRegisterMetaType<Container>();
#else
	qRegisterMetaType<Container>();
#endif

	MainWindow win;
	win.setFont(defaultFont);
	win.setStyleSheet(css["body"]);
	win.setAutoFillBackground(true);
	win.setWindowIcon(QIcon(":/icons/appicon"));
	win.show();


	return app.exec();
}
