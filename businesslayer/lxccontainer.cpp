#include "lxccontainer.h"

using namespace businesslayer;

/**
 * @brief LxcContainer::LxcContainer							[public]
 *
 * default constructor, instanciate an object LxcContainer.
 * @param parent waits parent object, default null if no parent object.
 */
LxcContainer::LxcContainer(QObject *parent) : QObject(parent)
{
	m_path = nullptr;
	initThread();
}

/**
 * @brief LxcContainer::LxcContainer							[public]
 *
 * Override constructor, instanciate an object LxcContainer.
 *
 * @param path waits the path where containers are stored.
 * @param parent waits parent object, default null if no parent object.
 */
LxcContainer::LxcContainer(const char *path, QObject *parent) : QObject(parent)
{
	m_path = nullptr;
	setLxcPath(path);
	initThread();
}

/**
 * @brief LxcContainer::~LxcContainer											[public]
 *
 * default destructor
 */
LxcContainer::~LxcContainer()
{
	m_thread.quit();
	m_thread.wait();

	if(m_path)
		delete []  m_path;
}

/**
 * @brief LxcContainer::lxcversion												[public]
 *
 * This method gets the lxc version api installed in your machine.
 *
 * @return QString version of lxc api
 */
QString LxcContainer::lxcVersion() const
{
	return QString(LXC_VERSION);
}

/**
 * @brief LxcContainer::lxccountAll												[public]
 *
 * This method gets the total number of containers activated.
 *
 * @return int if 0 no container count
 */
int LxcContainer::lxcCountActives() const
{
	return list_active_containers(m_path, NULL, NULL);
}

/**
 * @brief LxcContainer::lxccountAll												[public]
 *
 * This method gets the total number of containers created, activated or not.
 *
 * @return int if 0 no container count
 */
int LxcContainer::lxcCountAll() const
{
	return list_all_containers(m_path, NULL, NULL);;
}

/**
 * @brief LxcContainer::lxcpath												[public]
 *
 * This getter returns the lxcpath where stored all containers.
 *
 * @return path of stored lxc containers
 */
char *LxcContainer::lxcPath() const
{
	return m_path;
}

/**
 * @brief LxcContainer::setlxcpath												[public]
 *
 * This method sets path of lxc folder storage.
 * if the parameter is null the setter will check if default folder exists.
 *
 * @param path waits the path where lxc folder, if null check for default path.
 */
void LxcContainer::setLxcPath(const char *path)
{
	QDir dir;

	if(m_path)
	{
		delete [] m_path;
		m_path = nullptr;
	}

	if(path && dir.exists(path))
	{
		size_t pathSize = strlen(path);
		m_path = new char[pathSize] ();

		if(!qstrcpy(m_path, path))
			Logs::writeLog(LogType::Error, "LxcContainer::setLxcPaht", "Memory allocation failed L: 148");
	}
	else if(dir.exists(QDir::homePath() + DEFAULT_FOLDER))
	{
		QString defaultPath = QDir::homePath() + DEFAULT_FOLDER;

		m_path = new char[defaultPath.length() + 1] ();

		if(!qstrcpy(m_path, defaultPath.toLatin1().data()))
			Logs::writeLog(LogType::Error, "LxcContainer::setLxcPaht", "Memory allocation failed L: 157");
	}
	else
		Logs::writeLog(LogType::Error, "LxcContainer::setLxcPaht", "LXC folder not found L: 160");
}

/**
 * @brief LxcContainer::activeContainersList											[public]
 *
 * This getter retrieves the active containers and return a list.
 * @return list of active containers, if no container found nullptr
 */
lxc_container **LxcContainer::activeContainersList() const
{
	lxc_container **crets = nullptr;

	list_active_containers(m_path, NULL, &crets);

	return crets;
}

/**
 * @brief LxcContainer::allContainersList										[public]
 *
 * This getter retrieves the active containers and return a list.
 * @return list of active containers, if no container found nullptr
 */
lxc_container **LxcContainer::allContainersList() const
{
	lxc_container **crets = nullptr;

	list_all_containers(m_path, NULL, &crets);

	return crets;
}

/**
 * @brief LxcContainer::activeContainersName											[public]
 *
 * This getter retrieves the name(s) of active containers and return a list.
 * @return list of active containers' name, if no container found nullptr
 */
char **LxcContainer::activeContainersName() const
{
	char **names = nullptr;
	list_active_containers(m_path, &names, NULL);

	return names;
}

/**
 * @brief LxcContainer::allContainersName												[public slot]
 *
 * This getter retrieves the name(s) of all containers and return a list.
 * @return list of all containers' name, if no container found nullptr
 */
char **LxcContainer::allContainersName() const
{
	char **names = nullptr;
	list_all_containers(m_path, &names, NULL);

	return names;
}

/**
 * @brief LxcContainer::createContainer													[public slot]
 *
 * This method allocates and creates a container emit a signal when the creation will be done.
 *
 * @param container struct Container containing the information to create an lxc container
 * @return true if the success otherwize false.
 */
void LxcContainer::createContainer(const Container &container)
{
	emit operateCreation(container);
}

/**
 * @brief LxcContainer::start													[public slot]
 *
 * This method start stopped container. It will emit a signal to start the thread worker
 *
 * @param c waits container to start
 * @return true if success otherwize false.
 */
void LxcContainer::start(lxc_container *c)
{
	emit operateStart(c);
}

/**
 * @brief LxcContainer::stop													[public slot]
 *
 * This method stop running container. It will emit a signal to start the thread worker
 *
 * @param c waits the container to stop.
 * @return true if success otherwize false.
 */
void LxcContainer::stop(lxc_container *c)
{
	emit operateStop(c);
}

/**
 * @brief LxcContainer::duplicate													[public slot]
 *
 * This method duplicates a container. with two methods by copying the original container, otherwize
 * by colning a snapshot.
 *
 * @param c waits original lxc_container.
 * @param name waits the new name.
 * @param type waits duplication type 0 for copy, 6 for snapshot cloning
 */
void LxcContainer::clone(lxc_container *c, const char *name, const int cloneType)
{
	char *newName = new char[strlen(name) + 1]();
	qstrcpy(newName, name);

	emit operateClone(c, newName, cloneType);
}

/**
 * @brief LxcContainer::destroy													[public slot]
 *
 * This method destroyies a container the method will stop first the container
 * and try to destroy.
 *
 * @param c waits the container to destroy
 * @return true if success otherwize false
 */
void LxcContainer::destroy(lxc_container *c)
{
	emit operateDestroy(c);
}

/**
 * @brief LxcContainer::snapshot													[public slot]
 *
 * This method snapshots a container.
 * @param c waits the container to snapshot.
 * @param snapCommentFolder waits the snapshot comment folder.
 * @param comment waits the comment to write to file.
 */
void LxcContainer::snapshot(lxc_container *c, const char *snapCommentFolder, const char *comment)
{
	QString path = snapCommentFolder;
	path.append("/");
	path.append(c->name);


	QDir dir(path);

	if(!dir.exists())
		dir.mkpath(path);

	QLocale localeFormat;
	QString format = localeFormat.dateTimeFormat(QLocale::ShortFormat).replace("/", "-");
	path.append("/" + QDateTime::currentDateTime().toString(format));

	QFile file(path);

	if(file.open(QIODevice::WriteOnly))
	{
		file.write(comment);
	}

	file.close();

	char *commentFilePath = new char[path.length() + 1]();
	qstrcpy(commentFilePath, path.toLatin1().data());

	emit operateSnapshot(c, commentFilePath);
}

void LxcContainer::snapshotDestroy(lxc_container *c, const int snapshotIdx)
{
	if(!c && snapshotIdx < 0)
	{
		emit containerSnapshotDestroyed(false, tr("Make sure to select a container and snapshot before to try to destroy"));
		return;
	}

	emit operateSnapshotDestroy(c, snapshotIdx);
}

/**
 * @brief LxcContainer::restoreSnapshot													[public slot]
 *
 * This method restore a container from snapshot
 * @param c waits container to restore
 * @param snapshotIndex waits index of snapshot.
 */
void LxcContainer::restoreSnapshot(lxc_container *c, const int snapshotIndex, const char *newName)
{
	char *name = NULL;

	if(!newName || !qstrcmp(newName, ""))
	{
		name = new char[qstrlen(c->name) + 1];
		qstrcpy(name, newName);
	}
	else
	{
		name = new char[qstrlen(newName) + 1];
		qstrcpy(name, newName);
	}

	emit operateRestore(c, snapshotIndex, name);
}

/**
 * @brief LxcContainer::initThread														[protected]
 *
 * This method initializes the trhead and connection to thread worker.
 */
void LxcContainer::initThread()
{
	m_lxcWorker = new LxcWorker;
	m_lxcWorker->moveToThread(&m_thread);

	connect(&m_thread, &QThread::finished, m_lxcWorker, &LxcWorker::deleteLater);

	connect(this, &LxcContainer::operateCreation, m_lxcWorker, &LxcWorker::doWorkCreate);
	connect(this, &LxcContainer::operateStart, m_lxcWorker, &LxcWorker::doWorkStart);
	connect(this, &LxcContainer::operateStop, m_lxcWorker, &LxcWorker::doWorkStop);
	connect(this, &LxcContainer::operateClone, m_lxcWorker, &LxcWorker::doWorkClone);
	connect(this, &LxcContainer::operateSnapshot, m_lxcWorker, &LxcWorker::doWorkSnapshot);
	connect(this, &LxcContainer::operateRestore, m_lxcWorker, &LxcWorker::doWorkRestore);
	connect(this, &LxcContainer::operateDestroy, m_lxcWorker, &LxcWorker::doWorkDestroy);
	connect(this, &LxcContainer::operateSnapshotDestroy, m_lxcWorker, &LxcWorker::doWorkSnapshotDestroy);


	connect(m_lxcWorker, &LxcWorker::resultCreateReady, this, [=](bool success, const QString &message) { emit containerCreated(success, message); });
	connect(m_lxcWorker, &LxcWorker::resultStartReady, this, [=](bool success) { emit containerStarted(success); });
	connect(m_lxcWorker, &LxcWorker::resultStopReady, this, [=](bool success) { emit containerStopped(success); });
	connect(m_lxcWorker, &LxcWorker::resultCloneReady, this, [=](bool success) { emit containerCloned(success); });
	connect(m_lxcWorker, &LxcWorker::resultSnapshotReady, this, [=](bool success){ emit containerSnapshoted(success); });
	connect(m_lxcWorker, &LxcWorker::resultRestoreReady, this, [=](bool success, const QString &message) { emit containerRestrored(success, message); });
	connect(m_lxcWorker, &LxcWorker::resultDestroyReady, this, [=](bool success) { emit containerDestroyed(success); });
	connect(m_lxcWorker, &LxcWorker::resultSnapshotDestroyReady, this, [=](bool success, const QString &message) { emit containerSnapshotDestroyed(success, message); });


	m_thread.start();
}



