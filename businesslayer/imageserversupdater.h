#ifndef IMAGESERVERSUPDATER_H
#define IMAGESERVERSUPDATER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

namespace businesslayer
{
	class ImageServersUpdater : public QObject
	{
			Q_OBJECT
			Q_PROPERTY(boo finish READ isFinish WRITE setIsFinish NOTIFY finished)
		public:
			explicit ImageServersUpdater(QObject *parent = nullptr);
			~ImageServersUpdater();

		signals:
			void finished(bool);

		public:
			void autoChecker();
			bool waitForFinish() const;
			bool isFinish() const;

		public slots:
			void setIsFinish(bool finish);

		protected:
			void initObjects();
			void initConnections();
			void createHeader(QNetworkRequest *request);

			void checkSeverImagesVersion();
			void updateServerImages();

		private:
			QNetworkAccessManager *m_manager;
			QUrl m_url;
			QHash<QString, QString> m_endpoint;
			bool m_isFinish;
	};
}

#endif // IMAGESERVERSUPDATER_H
