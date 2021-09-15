#include "configfile.h"

ConfigFile::ConfigFile()
{
	m_configPath = QDir::homePath() + "/.config/lxcmanager/default.config";
	m_isOpen = openConfigFile();
}

bool ConfigFile::isOpen()
{
	return m_isOpen;
}

QString ConfigFile::find(const QString &key)
{
	if(!m_jsonObj.contains(key))
		return QString();

	return m_jsonObj.value(key).toString();
}

QVariantList ConfigFile::findList(const QString &key)
{
	if(!m_jsonObj.contains(key))
		return QVariantList();

	QJsonArray array = m_jsonObj.value(key).toArray();

	return array.toVariantList();
}

bool ConfigFile::save(const QMap<QString, QString> &conf)
{
	QString json = "{";

	QMap<QString,QString>::const_iterator it;

	for(it = conf.cbegin(); it != conf.cend(); it++)
		json += '"' + it.key() + "\":\"" + it.value() + "\", ";

	json = json.right(2) + "}";

	QFile file(m_configPath);

	if(!file.exists() || !file.open(QIODevice::ReadOnly))
		return false;

	file.write(json.toLatin1());
	return true;
}

bool ConfigFile::openConfigFile()
{
	QFile file(m_configPath);

	if(!file.exists() || !file.open(QIODevice::ReadOnly))
		return false;

	QJsonDocument jsonDoc;
	jsonDoc.fromJson(file.readAll());

	m_jsonObj = jsonDoc.object();

	return true;
}
