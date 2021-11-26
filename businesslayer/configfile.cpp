#include "configfile.h"

using namespace businesslayer;

/*!
 * \brief ConfigFile::ConfigFile										[public]
 *
 * Default Constructor setup config dir path and config file path
 * and open configFile if exists.
 */
ConfigFile::ConfigFile()
{
	m_configDirPath = QDir::homePath() + "/.config/lxcmanager";
	m_configFilePath = m_configDirPath + "/default.conf";
	m_isOpen = openConfigFile();
}

/*!
 * \brief ConfigFile::isOpen											[public]
 *
 * \return true if file is open otherwize false.
 */
bool ConfigFile::isConfigFileOpen() const
{
	return m_isOpen;
}

/*!
 * \brief ConfigFile::find												[public]
 *
 * The find method will retriew the value corresponding to key.
 *
 * \param key waits the key to find into config file.
 * \param defaultValue waits a default value if key not found.
 * \return QString value if the key is found otherwize return empty string or default value.
 */
QVariant ConfigFile::find(const QString &key, const QVariant &defaultValue)
{
	return m_jsonObj.contains(key) ? m_jsonObj.value(key) : defaultValue;
}

/*!
 * \brief ConfigFile::findArray											[public]
 *
 * The findArray method will retriew the array associate to the key.
 *
 * \param key waits the key to find into config file
 * \return QVariantList value if the key is found otherwize retur empty QVariantList
 */
QVariantList ConfigFile::findArray(const QString &key)
{
	if(!m_jsonObj.contains(key))
		return QVariantList();

	QJsonArray array = m_jsonObj.value(key).toArray();

	return array.toVariantList();
}

/*!
 * \fn ConfigFile::getAll
 * \brief ConfigFile::getAll return all config
 *
 * The \c ConfigFile::getAll retrieves all config file information.
 * \return file information.
 */
QVariantMap ConfigFile::getAll() const
{
	return m_jsonObj.toVariantMap();
}

/*!
 * \brief ConfigFile::save											[public]
 *
 * The save method will save the config QMap passed. The values string can contains int, string, array.
 * The method will add the key and value if not in config file otherwize it will replace current value.
 *
 * \param conf waits conf to add to config file.
 * \return true if saved config otherwize false.
 */
bool ConfigFile::save(const QVariantMap &conf)
{
	QMap<QString, QVariant>::const_iterator it;

	for(it = conf.begin(); it != conf.end(); it++)
	{
		if(m_jsonObj.contains(it.key()))
			m_jsonObj[it.key()] = it.value().toString();

		else
			m_jsonObj.insert(it.key(), it.value().toString());
	}

	// check if path exist
	QDir dir(m_configDirPath);

	if(!dir.exists())
		dir.mkpath(m_configDirPath);


	// write json to file
	QFile file(m_configFilePath);

	if(!file.open(QIODevice::WriteOnly))
		return false;

	QJsonDocument jsonDoc(m_jsonObj);

	file.write(jsonDoc.toJson());
	file.close();

	return true;
}

/*!
 * \brief ConfigFile::openConfigFile 											[protected]
 *
 * The openConfigFile method will try to open configFile if exists.
 *
 * \return true if the config file is open otherwize false.
 */
bool ConfigFile::openConfigFile()
{
	QFile file(m_configFilePath);

	if(!file.exists() || !file.open(QIODevice::ReadOnly))
		return false;

	QJsonParseError jsonError;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &jsonError);

	if(jsonError.error != QJsonParseError::NoError)
		return false;

	m_jsonObj = jsonDoc.object();
	file.close();

	return true;
}
