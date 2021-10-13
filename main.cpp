#include <QApplication>
#include <QFontDatabase>
#include <QTranslator>
#include <QSplashScreen>

#include "mainwindow.h"
#include "businesslayer/style.h"
#include "businesslayer/monitorutils.h"
#include "businesslayer/imageserversupdater.h"

using namespace businesslayer;
using namespace model;

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QScreen *screen = QApplication::primaryScreen();

	QPixmap pm(":/images/splash");
	QSplashScreen splash(screen, pm);
	splash.setStyleSheet("QSplashScreen { color: black; background-color: transparent; font-family: Arial, Helvetica, sans-serif; font-style: normal; font-size: 14px; }");
	splash.show();

	splash.clearMessage();
	splash.showMessage("Loading fonts ...");

	QFontDatabase::addApplicationFont(":/fonts/lato");
	QFontDatabase::addApplicationFont(":/fonts/lato-bold");
	QFontDatabase::addApplicationFont(":/fonts/lato-bold-italic");
	QFontDatabase::addApplicationFont(":/fonts/lato-italic");
	QFontDatabase::addApplicationFont(":/fonts/lato-light");
	QFontDatabase::addApplicationFont(":/fonts/lato-light-italic");


	QFont defaultFont("Lato");
	defaultFont.setPixelSize(13);
	defaultFont.setWeight(QFont::Normal);


	splash.clearMessage();
	splash.showMessage("Loading translation ...");

	// Languages
	QVector<QString> uiLanguages = QLocale::system().uiLanguages().toVector();
	QString *uiISO = std::find_if(uiLanguages.begin(), uiLanguages.end(), [](QString value){ return (value.length() == 5); });
	QString baseName = ":/i18n/lxcmanager_" + (new ConfigFile)->find("language", *uiISO).toString();

	QTranslator translator;
	if(translator.load(baseName))
	{
		app.installTranslator(&translator);
	}


	splash.clearMessage();
	splash.showMessage("Check for update  ...");

/*
	// TODO: UNCOMMENT WHEN SEVER SIDE IS READY
	ConfigFile config;
	ImageServersUpdater *imgServer = new ImageServersUpdater;
	imgServer->checkVersion();
	imgServer->waitForFinish();

	QString version = imgServer->version();

	if(!version.isEmpty() && version != config.find("version", "1.0"))
	{
		splash.clearMessage();
		splash.showMessage("Loading Lxc Server images list ...");

		QObject::connect(imgServer, &ImageServersUpdater::progress, &splash, &QSplashScreen::clearMessage);
		QObject::connect(imgServer, &ImageServersUpdater::progress, &splash, &QSplashScreen::showMessage);

		imgServer->download();
		imgServer->waitForFinish();

		QObject::disconnect(imgServer, &ImageServersUpdater::progress, &splash, &QSplashScreen::clearMessage);
		QObject::disconnect(imgServer, &ImageServersUpdater::progress, &splash, &QSplashScreen::showMessage);

		if(imgServer->isDownloaded())
		{
			QVariantMap map = config.getAll();
			map["version"] = version;
			config.save(map);
		}
	}
*/

	splash.clearMessage();
	splash.showMessage("Register MetaTypes ...");

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

	splash.clearMessage();
	splash.showMessage("Loading style ...");

	Style css;

	splash.clearMessage();
	splash.showMessage("Loading window ...");

	MainWindow win;
	win.setFont(defaultFont);
	win.setStyleSheet(css["main"]);
	win.setAutoFillBackground(true);
	win.setWindowIcon(QIcon(":/icons/appicon"));
	win.show();

	splash.finish(&win);

	return app.exec();
}
