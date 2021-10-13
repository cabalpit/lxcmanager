#ifndef IMAGESERVERSUPDATER_H
#define IMAGESERVERSUPDATER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QFile>
#include <QDir>

namespace businesslayer
{
	class ImageServersUpdater : public QObject
	{
			Q_OBJECT
			Q_PROPERTY(bool finish READ finish WRITE setFinish NOTIFY finished)
			Q_PROPERTY(bool downlod READ isDownloaded WRITE setDownloaded NOTIFY downloaded)
		public:
			explicit ImageServersUpdater(QObject *parent = nullptr);
			~ImageServersUpdater();

			void checkVersion();
			QString version() const;

			void download();
			bool isDownloaded();

			bool finish() const;
			QMap<QString, QString> endpoints() const;

			void waitForFinish();

		signals:
			void finished(bool);
			void downloaded(bool);

		public slots:
			void setFinished(bool);
			void setDownloaded(bool status);

		protected:
			void initEndPoints();

		protected slots:
			void versionReady(QNetworkReply *reply);
			void downloadReady(QNetworkReply *reply);
			void sslError(const QList<QSslError> &errors);


		private:
			bool writeOnDisk(QIODevice *data);

			QMap<QString, QString>m_endpoints;
			QNetworkAccessManager *m_manager;
			QVector<QNetworkReply *> m_reply;
			QEventLoop m_loop;
			QString m_version;
			bool m_isDowload;
			bool m_isFinish;
	};
}

#endif // IMAGESERVERSUPDATER_H
