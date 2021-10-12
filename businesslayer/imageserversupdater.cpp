#include "imageserversupdater.h"

using namespace businesslayer;

ImageServersUpdater::ImageServersUpdater(QObject *parent) : QObject(parent)
{
	initObjects();
	initConnections();
}

ImageServersUpdater::~ImageServersUpdater()
{

}

void ImageServersUpdater::autoChecker()
{
	checkSeverImagesVersion();
}

bool ImageServersUpdater::waitForFinish() const
{
	while (!m_isFinish);

	return m_isFinish;
}

bool ImageServersUpdater::isFinish() const
{
	return m_isFinish;
}

void ImageServersUpdater::setIsFinish(bool finish)
{
	m_isFinish = finish;
}

void ImageServersUpdater::initObjects()
{
	m_manager = new QNetworkAccessManager(this);
	m_isFinish = true;

	m_endpoint["version"] = "https://lxcmanager.elpexdynamic.com/api/version";
	m_endpoint["update"] = "https://lxcmanager.elpexdynamic.com/api/udpate";
}

void ImageServersUpdater::initConnections()
{
	connect(m_manager, &QNetworkAccessManager::finished, this, &ImageServersUpdater::finished);
}

void ImageServersUpdater::createHeader(QNetworkRequest *request)
{

}

void ImageServersUpdater::checkSeverImagesVersion()
{
	QNetworkRequest request(QUrl(m_endpoint.value("version")));
	request.setPriority(QNetworkRequest::NormalPriority);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain; charset=utf-8");
	request.setHeader(QNetworkRequest::UserAgentHeader, "");
	request.setHeader(QNetworkRequest::ContentLengthHeader, 0);

	QNetworkReply *reply = m_manager->get(request);
}

void ImageServersUpdater::updateServerImages()
{

}

