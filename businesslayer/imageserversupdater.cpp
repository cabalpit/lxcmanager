#include "imageserversupdater.h"

using namespace businesslayer;

ImageServersUpdater::ImageServersUpdater(QObject *parent): QObject(parent)
{
	m_manager = new QNetworkAccessManager(this);
	initEndPoints();
}

ImageServersUpdater::~ImageServersUpdater()
{
	delete m_manager;
	m_reply.empty();
}

void ImageServersUpdater::checkVersion()
{
	m_isFinish = false;
	connect(m_manager, &QNetworkAccessManager::finished, this, &ImageServersUpdater::versionReady);

	QNetworkRequest request(QUrl(m_endpoints.value("version")));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
	request.setHeader(QNetworkRequest::ContentDispositionHeader, "inline");
	request.setHeader(QNetworkRequest::UserAgentHeader, "LxcManager downloader");

	QNetworkReply *reply = m_manager->get(request);
	m_reply.append(reply);

#if QT_CONFIG(ssl)
	connect(reply, &QNetworkReply::sslErrors, this, &ImageServersUpdater::sslError);
#endif
}

QString ImageServersUpdater::version() const
{
	return m_version;
}

void ImageServersUpdater::download()
{
	connect(m_manager, &QNetworkAccessManager::finished, this, &ImageServersUpdater::downloadReady);

	QNetworkRequest request(QUrl(m_endpoints.value("version")));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
	request.setHeader(QNetworkRequest::ContentDispositionHeader, "inline");
	request.setHeader(QNetworkRequest::UserAgentHeader, "LxcManager downloader");

	QNetworkReply *reply = m_manager->get(request);
	connect(reply, &QNetworkReply::downloadProgress, this, &ImageServersUpdater::downloadProgress);

	m_reply.append(reply);

#if QT_CONFIG(ssl)
	connect(reply, &QNetworkReply::sslErrors, this, &ImageServersUpdater::sslError);
#endif
}

bool ImageServersUpdater::isDownloaded()
{
	return m_isDowload;
}

bool ImageServersUpdater::finish() const
{
	return m_isFinish;
}

QMap<QString, QString> ImageServersUpdater::endpoints() const
{
	return m_endpoints;
}

void ImageServersUpdater::waitForFinish()
{
	m_loop.exec(QEventLoop::ExcludeUserInputEvents);
}

void ImageServersUpdater::setFinished(bool)
{
	m_isFinish = true;
	emit finished(m_isFinish);
}

void ImageServersUpdater::setDownloaded(bool status)
{
	if(m_isDowload == status)
		return;

	m_isDowload = status;
	emit downloaded(m_isDowload);
}

void ImageServersUpdater::initEndPoints()
{
	m_endpoints.insert("version", "https://lxcmanager.elpexdynamic.com/api/version");
	m_endpoints.insert("download", "https://lxcmanager.elpexdynamic.com/api/download");
}

void ImageServersUpdater::versionReady(QNetworkReply *reply)
{
	QByteArray data;
	QJsonParseError jsonError;
	QJsonDocument jsonDoc;
	QJsonObject jsonObject;


	if(reply->error() != QNetworkReply::NoError)
		goto out;

	data = reply->readAll();
	reply->close();

	jsonDoc = QJsonDocument::fromJson(data, &jsonError);

	if(jsonError.error != QJsonParseError::NoError)
	{
		m_version.clear();
		goto out;
	}

	jsonObject = jsonDoc.object();
	m_version = jsonObject.find("version")->toString();

out:

	if(m_loop.isRunning())
		m_loop.exit();

	m_reply.removeAll(reply);
	setFinished(true);
}

void ImageServersUpdater::downloadReady(QNetworkReply *reply)
{
	bool status = false;

	if(reply->error() != QNetworkReply::NoError)
		goto out;

	status = writeOnDisk(reply);
	reply->close();

out:
	if(m_loop.isRunning())
		m_loop.exit();

	m_reply.removeAll(reply);
	setDownloaded(status);
}

void ImageServersUpdater::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	QString message = tr("%1% downloaded").arg((bytesReceived / bytesTotal) * 100);
	emit progress(message);
}

void ImageServersUpdater::sslError(const QList<QSslError> &errors)
{
#if QT_CONFIG(ssl)
	for(const QSslError &error: errors)
		qDebug() << error.errorString();
#else
	Q_UNUSED(errors);
#endif

}

bool ImageServersUpdater::writeOnDisk(QIODevice *data)
{
	QFile file(QDir::homePath() + "/.local/share/lxcmanager/lxcimages");

	if(!file.open(QIODevice::WriteOnly))
	{
		file.close();
		return false;
	}

	file.write(data->readAll());
	file.close();

	return true;
}

