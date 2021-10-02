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
		message = tr("Failed to setup lxc_container struct");
		Logs::writeLog(LogType::Error, "LxcWorker::doWorkCreate", message);

#ifdef QT_DEBUG
		qDebug() << "LxcWorker::doWorkCreate: Failed to setup lxc_container struct";
#endif
		goto out;
	}

	if(c->is_defined(c))
	{
		message = tr("Container already exists");
		Logs::writeLog(LogType::Info, "LxcWorker::doWorkCreate", message);

#ifdef QT_DEBUG
		qDebug() << "LxcWorker::doWorkCreate : Container already exists";
#endif

		goto out;
	}


	if(!c->createl(c, "download", NULL, NULL, LXC_CREATE_QUIET, "-d", container.distribution.toLatin1().data(), "-r", container.release.toLatin1().data(),
				   "-a", container.arch.toLatin1().data(), "--variant", container.variant.toLatin1().data(), "--keyserver", container.hkp.toLatin1().data(), NULL))
	{
		message = tr("Failed to create container rootfs");
		Logs::writeLog(LogType::Error, "LxcWorker::doWorkCreate", message);

#ifdef QT_DEBUG
		qDebug() << "LxcWorker::doWorkCreate : Failed to create container rootfs";
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
	m_mutex.lock();
	bool success = false;
	int max = 5, cnt = 0;

	if(c)
	{
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
			Logs::writeLog(LogType::Error, "LxcWorker::doWorkStart", "Failed to start the container");

		else
			sleep(2);		// time to get ip address
	}
	else
	{
		qDebug() << "LxcWorker::doWorkStart : container is null ??";
	}

	m_mutex.unlock();

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
	m_mutex.lock();
	bool success = false;

	if(c)
	{
		if(!(success = c->shutdown(c, 30)))
		{
			Logs::writeLog(LogType::Warning, "LxcWorker::doWorkStop", "Failed to cleanly shutdown the container, forcing.");

			if(!(success = c->stop(c)))
			{
				Logs::writeLog(LogType::Error, "LxcWorker::doWorkStop", "Failed to cleanly shutdown the container, forcing.");
			}
		}
	}
	else
		 qDebug() << "LxcWorker::doWorkStop : Container is null ??";

	m_mutex.unlock();

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
 * @brief LxcWorker::doWorkRestore						[public]
 *
 * This method restore a snapshot for a container, the snapshot must be valid
 * and container must be stop first.
 *
 * @param c waits container to restore.
 * @param snapshotIndex waits the index of the snapshot.
 */
void LxcWorker::doWorkRestore(lxc_container *c, const int snapshotIndex, const char *newName)
{
	bool success = false;
	bool start = false, isRunning = c->is_running(c);
	uint  max = 5, cntStart = 0;
	lxc_snapshot *snapshot = NULL;
	QString message;

	if(!c)
	{
		goto out;
	}

	if(isRunning)
	{
		if(!c->shutdown(c, 30))
		{
			if(!c->stop(c))
			{
				message = tr("Container cannot be stopped");
				goto out;
			}
		}
	}

	c->snapshot_list(c, &snapshot);

	if(!(success = c->snapshot_restore(c, snapshot[snapshotIndex].name, newName)))
		message = tr("Container cannot be restrore");

	delete [] snapshot;

	if(isRunning)
	{
		do
		{
			start = c->start(c, 0, NULL);
			cntStart++;
			sleep(1);

		} while (!start && cntStart < max);

		sleep(2);
	}

out:
	emit resultRestoreReady(success, message);
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
				Logs::writeLog(LogType::Warning, "LxcWorker::doWorkDestroy", "Failed to cleanly shutdown the container, forcing.");
				goto out;
			}
		}
	}

	success = c->destroy(c);

	if(!success)
	{
		Logs::writeLog(LogType::Warning, "LxcWorker::doWorkDestroy", "Failed to destroy the container.");
	}

out:
	emit resultDestroyReady(success);
}

/**
 * @brief LxcWorker::doWorkSnapshot						[public]
 *
 * This method creates snapshot of the container selected.
 *
 * @param c waits the container to snap shot.
 * @param commentPath waits the comment path file.
 */
void LxcWorker::doWorkSnapshot(lxc_container *c, const char *commentPath)
{
	int value = (c && c->snapshot(c, commentPath) > -1);

	emit resultSnapshotReady((value >= 0));
}

void LxcWorker::doWorkSnapshotDestroy(lxc_container *c, const int snapshotIdx)
{
	QString message;
	bool success = false;
	lxc_snapshot *snapshot = nullptr;

	if(!c)
	{
		message = tr("Container must be selected before delete snapshot");
		goto out;
	}

	c->snapshot_list(c, &snapshot);

	if(!snapshot)
	{
		message = tr("Snapshot(s) not found!");
		Logs::writeLog(LogType::Warning, "LxcWorker::doWorkSnapshotDestroy", message);

		goto out;
	}


	success = c->snapshot_destroy(c, snapshot[snapshotIdx].name);

	if(success)
		message = tr("Snapshot %1 delete").arg(snapshot[snapshotIdx].name);

	else
	{
		message = tr("Cannot be delete snaphost %1").arg(snapshot[snapshotIdx].name);
		Logs::writeLog(LogType::Error, "LxcWorker::doWorkSnapshotDestroy", message);
	}

	delete [] snapshot;

out:
	emit resultSnapshotDestroyReady(success, message);
}


