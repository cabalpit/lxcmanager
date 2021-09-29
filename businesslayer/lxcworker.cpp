#include "lxcworker.h"

using namespace businesslayer;

/**
 * @brief LxcWorker::LxcWorker								[public]
 *
 * Default constructor build the object
 * @param parent waits the parent object default nullptr
 */
LxcWorker::LxcWorker(QObject *parent) : QObject(parent)
{

}

/**
 * @brief LxcWorker::~LxcWorker
 *
 * Default destructor
 */
LxcWorker::~LxcWorker()
{

}

/**
 * @brief LxcWorker::doWorkCreate						[public]
 *
 * This method tries to create a container.
 *
 * @param container waits Container definition for creation. @see businesslayer::Container to know the definition.
 */
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

/**
 * @brief LxcWorker::doWorkStart						[public]
 *
 * This method starts the defined container.
 *
 * @param c waits the lxc_container object to start.
 */
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

/**
 * @brief LxcWorker::doWorkStop							[public]
 *
 * This method stops the defined container.
 *
 * @param c waits the lxc_container object to stop.
 */
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

/**
 * @brief LxcWorker::doWorkDuplicate						[public]
 *
 * This method duplicates an existing container. 2 methods of duplication by copy original container
 * or by cloning a snapshot.
 *
 * @param c waits original container
 * @param name waits the new container name.
 * @param type 0 copy, 6 snapshot cloning
 */
void LxcWorker::doWorkClone(lxc_container *c, const char *name, const int cloneType)
{
	lxc_container *newC = c->clone(c, name, NULL, cloneType, NULL, NULL, 0, NULL);
	bool success = (newC != NULL);

	lxc_container_put(newC);

	emit resultCloneReady(success);
}

/**
 * @brief LxcWorker::doWorkDestroy						[public]
 *
 * This method destroies a defined container.
 * @param c waits lxc_container to destroy.
 */
void LxcWorker::doWorkDestroy(lxc_container *c)
{
	bool success = false;

	// if the container is running stop first.
	if(qstrcmp(c->state(c), "RUNNING") == 0)
	{
		if(!c->shutdown(c, 30))
		{
			if(!c->stop(c))
			{
				Logs::writeLog(LogType::Warning, "LxcContainer::destroy", "Failed to cleanly shutdown the container, forcing.");
				goto out;
			}
		}
	}

	success = c->destroy(c);

	if(!success)
	{
		Logs::writeLog(LogType::Warning, "LxcContainer::destroy", "Failed to destroy the container.");
	}

out:
	emit resultDestroyReady(success);
}


