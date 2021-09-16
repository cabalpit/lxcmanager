#include "style.h"

/**
 * @brief Style::Style
 *
 * Default constructor
 * @param parent waits QObject parent default nullptr
 */
Style::Style(QObject *parent) : QObject(parent)
{
	readConfigFile();
}

/**
 * @brief Style::operator ()											[public]
 * @param key waits json attribute to search
 * @return value if found otherwize return empty string.
 */
QString Style::operator()(const QString &key)
{
	if(m_styleObject.contains(key))
		return m_styleObject.value(key).toString();

	return QString();
}

/**
 * @brief Style::readConfigFile											[protected]
 * This method will read css file and convert to QJsonObject
 * @return true if file has been open and converted otherwize false.
 */
bool Style::readConfigFile()
{
	QFile file(":/style/default");
	bool open = file.open(QIODevice::ReadOnly);

	if(open)
	{
		QJsonParseError parse;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &parse);

		if(parse.error == QJsonParseError::NoError)
		{
			m_styleObject = jsonDoc.object();
			open = true;
		}
		else
		{
			qDebug() << parse.errorString();
			open = false;
		}
	}

	file.close();
	return open;
}


