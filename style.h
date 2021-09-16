#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>

class Style : public QObject
{
		Q_OBJECT
	public:
		explicit Style(QObject *parent = nullptr);

		QString operator()(const QString &key);

	signals:
	protected:
		bool readConfigFile();

	private:
		QJsonObject m_styleObject;
};

#endif // STYLE_H
