#include "lxcworker.h"

using namespace businesslayer;

LxcWorker::LxcWorker(QObject *parent) : QObject(parent)
{

}

LxcWorker::~LxcWorker()
{

}

void LxcWorker::doWorkStart(lxc_container *c)
{
	bool success = false;
	int max = 5, cnt = 0;

	/*
	 * don't know why but some times start() function refused to start container at the first time.
	 * why we done a loop with a max of 5 and sleep
	 */
	do
	{
		success = c->start(c, 0, NULL);
		cnt++;
		sleep(2);

	}while(!success && cnt < max);

	if(!success)
	{
		Logs::writeLog(LogType::Error, "LxcContainer::start", "Failed to start the container");
	}
	else
		sleep(2);		// time to get ip address


	emit resultStartReady(success);
}

void LxcWorker::doWorkStop(lxc_container *c)
{
	bool success = true;

	if(!c->shutdown(c, 30))
	{
		Logs::writeLog(LogType::Warning, "LcxContainer::stop", "Failed to cleanly shutdown the container, forcing.");

		if(!c->stop(c))
		{
			Logs::writeLog(LogType::Error, "LcxContainer::stop", "Failed to cleanly shutdown the container, forcing.");
			success = false;
		}
	}

	emit resultStopReady(success);
}

void LxcWorker::doWorkCreate(const Container &container)
{
	bool success = false;
	QString message;

	lxc_container *c = lxc_container_new(static_cast<char *>(container.name.toLatin1().data()) , NULL);

	if(!c)
	{
		message = "Failed to setup lxc_container struct";
		Logs::writeLog(LogType::Error, "LxcWorker::doWork", message);

#ifdef QT_DEBUG
		qDebug() << "Failed to setup lxc_container struct";
#endif
		goto out;
	}

	if(c->is_defined(c))
	{
		message = "Container already exists";
		Logs::writeLog(LogType::Info, "LxcWorker::doWork", message);

#ifdef QT_DEBUG
		qDebug() << "Container already exists";
#endif

		goto out;
	}


	if(!c->createl(c, "download", NULL, NULL, LXC_CREATE_QUIET, "-d", container.distribution.toLatin1().data(), "-r", container.release.toLatin1().data(),
				   "-a", container.arch.toLatin1().data(), "--variant", container.variant.toLatin1().data(), "--keyserver", container.hkp.toLatin1().data(), NULL))
	{
		message = "Failed to create container rootfs";
		Logs::writeLog(LogType::Error, "LxcWorker::doWork", message);

#ifdef QT_DEBUG
		qDebug() << "Failed to create container rootfs";
#endif

		goto out;
	}

	success = true;
out:
	lxc_container_put(c);

	emit resultCreateReady(success, message);
}


