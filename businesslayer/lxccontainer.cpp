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
	setLxcPath(path);
}

/**
 * @brief LxcContainer::~LxcContainer											[public]
 *
 * default destructor
 */
LxcContainer::~LxcContainer()
{
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
 * @brief LxcContainer::allContainersName												[public]
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
 * @brief LxcContainer::createContainer													[public]
 *
 * This method allocates and creates a container emit a signal when the creation will be done.
 *
 * @param container struct Container containing the information to create an lxc container
 * @return true if the success otherwize false.
 */
bool LxcContainer::createContainer(const Container &container)
{
	bool success = false;
	lxc_container *cont = lxc_container_new(static_cast<char *>(container.name.toLatin1().data()) , NULL);

	if(!cont)
	{
		Logs::writeLog(LogType::Error, "LxcContainer::createContainer", "Failed to setup lxc_container struct");

#ifdef QT_DEBUG
		qDebug() << "Failed to setup lxc_container struct";
#endif
		goto out;
	}

	if(cont->is_defined(cont))
	{
		Logs::writeLog(LogType::Info, "LxcContainer::createContainer", "Container already exists");

#ifdef QT_DEBUG
		qDebug() << "Container already exists";
#endif

		goto out;
	}

	if(!cont->createl(cont, "download", NULL, NULL, LXC_CREATE_QUIET, "-n", container.name.toLatin1().data(), "-d", container.distribution.toLatin1().data(),
					  "-r", container.release.toLatin1().data(), "-a", container.arch.toLatin1().data(), "--variant", container.variant.toLatin1().data(),
					  "--keyserver", container.hkp.toLatin1().data(), NULL))
	{
		Logs::writeLog(LogType::Error, "LxcContainer::create", "Failed to create container rootfs");

#ifdef QT_DEBUG
		qDebug() << "Failed to create container rootfs";
#endif

		goto out;
	}

	success = true;
	emit allContainersUpdated((const char**)allContainersName(), (const lxc_container **)allContainersList());

out:
	lxc_container_put(cont);
	return success;
}


