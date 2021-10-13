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
			void progress(const QString &);

		public slots:
			void setFinish(bool);
			void setDownloaded(bool status);

		protected:
			void initEndPoints();

		protected slots:
			void versionReady(QNetworkReply *reply);
			void downloadReady(QNetworkReply *reply);
			void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
			void sslError(const QList<QSslError> &errors);


		private:
			bool writeToDisk(QIODevice *data);

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
