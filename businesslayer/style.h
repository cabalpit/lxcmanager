#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include "logs.h"

namespace businesslayer
{
	/**
	 * \brief The Style class
	 * \version 1.0
	 * \since 2021-09-15
	 * \author Peter Cata
	 *
	 * This class will read json style file and return the css value of the attribute selected.
	 */
	class Style : public QObject
	{
			Q_OBJECT
		public:
			explicit Style(QObject *parent = nullptr);

			QString operator[](const QString &key);

		signals:
		protected:
			bool readConfigFile();

		private:
			QJsonObject m_styleObject;
	};
}
#endif // STYLE_H
