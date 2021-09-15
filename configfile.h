#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QMapIterator>

class ConfigFile
{
	public:
		ConfigFile();
		bool isOpen();
		QString find(const QString &key);
		QVariantList findList(const QString &key);

	bool save(const QMap<QString, QString> &conf);

	protected:
		bool openConfigFile();


	private:
		QString m_configPath;
		bool m_isOpen;
		QJsonObject m_jsonObj;
};

#endif // CONFIGFILE_H
