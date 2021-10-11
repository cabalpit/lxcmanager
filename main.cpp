#include <QApplication>
#include <QFontDatabase>

#include "mainwindow.h"
#include "businesslayer/style.h"
#include "businesslayer/monitorutils.h"

using namespace businesslayer;
using namespace model;

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

// TODO: splash screen download list container server image sql.
// TODO: Documentation.
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
	qDebug() << qRegisterMetaType<Distribution>();
	qDebug() << qRegisterMetaType<Stats>();
	qDebug() << qRegisterMetaType<QVector<Stats>>("QVector<Stats>");
#else
	qRegisterMetaType<Container>();
	qRegisterMetaType<Distribution>();
	qRegisterMetaType<ImageStatus>();
	qRegisterMetaType<Stats>();
	qRegisterMetaType<QVector<Stats>>();
#endif

	MainWindow win;
	win.setFont(defaultFont);
	win.setStyleSheet(css["main"]);
	win.setAutoFillBackground(true);
	win.setWindowIcon(QIcon(":/icons/appicon"));
	win.show();


	return app.exec();
}
