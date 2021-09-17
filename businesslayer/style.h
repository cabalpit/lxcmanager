#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>

namespace businesslayer
{
	/**
	 * @brief The Style class
	 *
	 * This class will read json style file and return the css value of the attribute selected.
	 *
	 * @version 1.0
	 * @since 2021-09-15
	 * @author Peter Cata
	 */
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
}
#endif // STYLE_H
