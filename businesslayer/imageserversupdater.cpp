#include "imageserversupdater.h"

using namespace businesslayer;

/*!
 * \fn ImageServersUpdater::ImageServersUpdater
 * \brief ImageServersUpdater::ImageServersUpdater constructor
 *
 * Construct a \c RemoveSnapDialog object with the given parent.
 *
 * \param parent waits parent widget, default \a nullptr
 */
ImageServersUpdater::ImageServersUpdater(QObject *parent): QObject(parent)
{
	m_manager = new QNetworkAccessManager(this);
	initEndPoints();
}

/*!
 * \fn  ImageServersUpdater::~ImageServersUpdater
 * \brief ImageServersUpdater::~ImageServersUpdater destructor
 */
ImageServersUpdater::~ImageServersUpdater()
{
	delete m_manager;
	m_reply.empty();
}

/*!
 * \fn ImageServersUpdater::checkVersion
 * \brief ImageServersUpdater::checkVersion version of database.
 *
 * This method requests to server the version of the SQLite database.
 * When data are ready the \c QNetworkAccessManager triggers \c ImageServersUpdater::versionReady slot to read data.
 */
void ImageServersUpdater::checkVersion()
{
	m_isFinish = false;
	connect(m_manager, &QNetworkAccessManager::finished, this, &ImageServersUpdater::versionReady);

	QNetworkRequest request(QUrl(m_endpoints.value("version")));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
	request.setHeader(QNetworkRequest::ContentDispositionHeader, "inline");
	request.setHeader(QNetworkRequest::UserAgentHeader, "LxcManager downloader");


	QNetworkReply *reply = m_manager->get(request);

#ifdef QT_DEBUG
	// only use in debug mode with local server
	reply->ignoreSslErrors();
#endif

	m_reply.append(reply);

#if QT_CONFIG(ssl)
	connect(reply, &QNetworkReply::sslErrors, this, &ImageServersUpdater::sslError);
#endif
}

/*!
 * \fn ImageServersUpdater::version
 * \brief ImageServersUpdater::version get SQLite database version
 *
 * The \c ImageServersUpdater::version retrieves the SQLite database version
 * \return database version
 */
QString ImageServersUpdater::version() const
{
	return m_version;
}

/*!
 * \fn ImageServersUpdater::download
 * \brief ImageServersUpdater::download download SQLite database file.
 *
 * The \c ImageServersUpdater::download method downloads the SQLite database file from the server.
 * When the data are ready the \c QNetworkAccessManager triggers the \c ImageServersUpdater::downloadReady
 * slot to save data to disk.
 */
void ImageServersUpdater::download()
{
	m_isDowload = false;
	connect(m_manager, &QNetworkAccessManager::finished, this, &ImageServersUpdater::downloadReady);

	// append file version to url.
	QUrl url = QUrl(m_endpoints.value("download") + '_' + version());

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
	request.setHeader(QNetworkRequest::ContentDispositionHeader, "inline");
	request.setHeader(QNetworkRequest::UserAgentHeader, "LxcManager downloader");


	QNetworkReply *reply = m_manager->get(request);

#ifdef QT_DEBUG
	// only use in debug mode with local server
	reply->ignoreSslErrors();
#endif

	m_reply.append(reply);

	connect(reply, &QNetworkReply::downloadProgress, this, &ImageServersUpdater::downloadProgress);

#if QT_CONFIG(ssl)
	connect(reply, &QNetworkReply::sslErrors, this, &ImageServersUpdater::sslError);
#endif
}

/*!
 * \fn ImageServersUpdater::isDownloaded
 * \brief ImageServersUpdater::isDownloaded getter
 *
 * The \c ImageServersUpdater::isDownloaded get if download is finish.
 *
 * \return true if download is finish otherwize false.
 */
bool ImageServersUpdater::isDownloaded()
{
	return m_isDowload;
}

/*!
 * \fn ImageServersUpdater::finish
 * \brief ImageServersUpdater::finish getter
 *
 * The \c ImageServersUpdater::finish retrieves the state of version request
 *
 * \return true if the request version is finish otherwize false.
 */
bool ImageServersUpdater::finish() const
{
	return m_isFinish;
}

/*!
 * \fn ImageServersUpdater::endpoints
 * \brief ImageServersUpdater::endpoints get endpoints
 * \return endpoints list.
 */
QMap<QString, QString> ImageServersUpdater::endpoints() const
{
	return m_endpoints;
}

/*!
 * \fn ImageServersUpdater::waitForFinish
 * \brief ImageServersUpdater::waitForFinish wait thread to finish
 *
 * This method waits the asynchrone request to finish.
 */
void ImageServersUpdater::waitForFinish()
{
	m_loop.exec(QEventLoop::ExcludeUserInputEvents);
}

/*!
 * \fn ImageServersUpdater::setFinish
 * \brief ImageServersUpdater::setFinish sets request to finish
 *
 * This method sets the request state to finish
 */
void ImageServersUpdater::setFinish(bool)
{
	m_isFinish = true;
	emit finished(m_isFinish);
}

/*!
 * \fn ImageServersUpdater::setDownloaded
 * \brief ImageServersUpdater::setDownloaded sets the download state
 *
 * This method sets the download request state to finish.
 * \param status waits the download state.
 */
void ImageServersUpdater::setDownloaded(bool status)
{
	if(m_isDowload == status)
		return;

	m_isDowload = status;
	emit downloaded(m_isDowload);
}

/*!
 * \fn ImageServersUpdater::initEndPoints
 * \brief ImageServersUpdater::initEndPoints initialize endpoints list
 *
 * This method creates the endpoints list.
 */
void ImageServersUpdater::initEndPoints()
{
	QString url;
	QString path;

#ifdef QT_DEBUG
    url = "https://lxcmanager.elpexdynamic.local";
	path = QDir::homePath() + "/Desktop/lxcimages";
#else
	url = "https://lxcmanager.elpexdynamic.com";
	path = QDir::homePath() + "/.local/share/lxcmanager/lxcimages";
#endif

	m_endpoints.insert("version", url + "/api/version");
	m_endpoints.insert("download", url + "/api/download/lxcimages");
	m_endpoints.insert("saveToDisk", path);
}

/*!
 * \fn ImageServersUpdater::versionReady
 * \brief ImageServersUpdater::versionReady reads informations from server reply.
 *
 * The \c ImageServersUpdater::versionReady method reads informations from the server reply, and convert
 * the data to string version. If the server reply with and error the method exit.
 *
 * \param reply waits server reply.
 */
void ImageServersUpdater::versionReady(QNetworkReply *reply)
{
	QByteArray data;
	QJsonParseError jsonError;
	QJsonDocument jsonDoc;
	QJsonObject jsonObject;


	disconnect(m_manager, &QNetworkAccessManager::finished, this, &ImageServersUpdater::versionReady);

	if(reply->error() != QNetworkReply::NoError)
	{
#ifdef QT_DEBUG
		qDebug() << reply->errorString();
#endif
		Logs::writeLog(LogType::Error, "ImageServersUpdater::versionReady", reply->errorString());
		goto out;
	}

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
	setFinish(true);
}

/*!
 * \fn  ImageServersUpdater::downloadReady
 * \brief ImageServersUpdater::downloadReady reads informations from server reply
 *
 * The \c ImageServersUpdater::downloadReady method reads information from the server reply.
 * If data are valid the method exute to \c mageServersUpdater::writeToDisk method
 * If the server reply with and error the method exit.
 *
 * \param reply
 */
void ImageServersUpdater::downloadReady(QNetworkReply *reply)
{
	bool status = false;

	disconnect(m_manager, &QNetworkAccessManager::finished, this, &ImageServersUpdater::downloadReady);

	if(reply->error() != QNetworkReply::NoError)
	{
		Logs::writeLog(LogType::Error, "ImageServersUpdater::downloadReady", reply->errorString());
		goto out;
	}

	status = writeToDisk(reply);
	reply->close();

out:
	if(m_loop.isRunning())
		m_loop.exit();

	m_reply.removeAll(reply);
	setDownloaded(status);
}

/*!
 * \fn ImageServersUpdater::downloadProgress
 * \brief ImageServersUpdater::downloadProgress compute downlaod percentage
 *
 * The method computes percentage remaining to download and emit signal \a progress with message.
 *
 * \param bytesReceived waits bytes received.
 * \param bytesTotal waits total bytes
 */
void ImageServersUpdater::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	QString message = tr("%1% downloaded").arg((bytesReceived / bytesTotal) * 100);
	emit progress(message, Qt::AlignBottom | Qt::AlignCenter, Qt::black);
}

/*!
 * \fn ImageServersUpdater::sslError
 * \brief ImageServersUpdater::sslError writes to logs file the ssl errors.
 *
 * This method writes to log file the ssl errors.
 *
 * \param errors waits ssl errors list.
 */
void ImageServersUpdater::sslError(const QList<QSslError> &errors)
{
#if QT_CONFIG(ssl)
	QString message;
	for(const QSslError &error: errors)
	{
		message += error.errorString();
		qDebug() << error.errorString();
	}

	Logs::writeLog(LogType::Error, "ImageServersUpdater::sslError", message);
#else
	Q_UNUSED(errors);
#endif

}

/*!
 * \fn ImageServersUpdater::writeToDisk
 * \brief ImageServersUpdater::writeToDisk write data to file.
 *
 * This method write data to file on disk to endpoint location.
 *
 * \param data binary data to write.
 * \return true if success otherwize false.
 */
bool ImageServersUpdater::writeToDisk(QIODevice *data)
{
	QFile file(m_endpoints["saveToDisk"]);

	if(!file.open(QIODevice::WriteOnly))
	{
		file.close();
		return false;
	}

	file.write(data->readAll());
	file.close();

	return true;
}

