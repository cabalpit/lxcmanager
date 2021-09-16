#include "style.h"

Style::Style(QObject *parent) : QObject(parent)
{
	readConfigFile();
}

QString Style::operator()(const QString &key)
{
	if(m_styleObject.contains(key))
		return m_styleObject.value(key).toString();

	return NULL;
}

bool Style::readConfigFile()
{
	QFile file(":/style/default");
	bool open = file.open(QIODevice::ReadOnly);

	if(open)
	{
		QJsonParseError parse;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &parse);

		qDebug() << parse.error;

		m_styleObject = jsonDoc.object();
	}

	file.close();
	return open;
}


