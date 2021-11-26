#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QMapIterator>

namespace businesslayer
{
	/*!
	 * \brief The ConfigFile class
	 * \author Peter Cata
	 * \version 1.5
	 * \since 2021-09-14
	 *
	 * ConfigFile class open read and write the configuration file for the current user.
	 * If the file not exists the config file will be create and populate.
	 *
	 * The config file is found in ~/.config/lxcmanager/default.conf
	 */
	class ConfigFile
	{
		public:
			ConfigFile();

			bool isConfigFileOpen() const;

			QVariant find(const QString &key, const QVariant &defaultValue = QString());
			QVariantList findArray(const QString &key);
			QVariantMap getAll() const;

			bool save(const QVariantMap &conf);

		protected:
			bool openConfigFile();

		private:
			QString m_configFilePath;
			QString m_configDirPath;
			bool m_isOpen;
			QJsonObject m_jsonObj;
	};

}
#endif // CONFIGFILE_H
