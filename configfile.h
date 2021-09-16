#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QMapIterator>

/**
 * @brief The ConfigFile class
 *
 * ConfigFile class open read and write the configuration file for the current user.
 * If the file not exists the config file will be create and populate.
 *
 * The config file is found in ~/.config/lxcmanager/default.conf
 *
 * @author PCata
 * @version 1.0
 * @since 2021-09-14
 */
class ConfigFile
{
	public:
		ConfigFile();

		bool isConfigFileOpen() const;

		QString find(const QString &key);
		QVariantList findArray(const QString &key);

		bool save(const QMap<QString, QString> &conf);

	protected:
		bool openConfigFile();

	private:
		QString m_configFilePath;
		QString m_configDirPath;
		bool m_isOpen;
		QJsonObject m_jsonObj;
};

#endif // CONFIGFILE_H
