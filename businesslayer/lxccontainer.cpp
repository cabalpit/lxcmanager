#include "lxccontainer.h"

using namespace businesslayer;

/**
 * @brief LxcContainer::LxcContainer							[public]
 *
 * default constructor
 */
LxcContainer::LxcContainer(QObject *parent) : QObject(parent)
{
	m_activeContainerCrets = nullptr;
	m_activeContainerNames = nullptr;
	m_allContainerCrets = nullptr;
	m_allContainerNames = nullptr;
	m_countActive = 0;
	m_countAll = 0;
	m_path = nullptr;
}

/**
 * @brief LxcContainer::~LxcContainer							[public]
 *
 * default destructor
 */
LxcContainer::~LxcContainer()
{
	if(m_activeContainerCrets)
	{
		for(int i = 0; i < m_countActive; i++)
			delete [] m_activeContainerCrets[i];

		delete [] m_activeContainerCrets;
	}

	if(m_activeContainerNames)
	{
		for(int i = 0; i < m_countActive; i++)
			delete [] m_activeContainerNames[i];

		delete [] m_activeContainerNames;
	}

	if(m_allContainerCrets)
	{
		for(int i = 0; i < m_countAll; i++)
			delete [] m_allContainerCrets[i];

		delete [] m_allContainerCrets;
	}

	if(m_allContainerNames)
	{
		for(int i = 0; i < m_countAll; i++)
			delete [] m_allContainerNames[i];

		delete [] m_allContainerNames;
	}

	if(m_path)
		delete []  m_path;
}

/**
 * @brief LxcContainer::init									[public]
 *
 * This method retrieves the list of all containers and all container activate.
 */
void LxcContainer::init()
{
	if(m_path)
		setLxcPath();

	m_countActive	= list_active_containers(m_path, &m_activeContainerNames, &m_activeContainerCrets);
	m_countAll		= list_all_containers(m_path, &m_allContainerNames, &m_allContainerCrets);

	QString info = QString("Initialize lxc wiht %1 container%2 and %3 active%4 container%4").arg(QString::number(m_countAll), (m_countAll > 0 ? "s" : ""), QString::number(m_countActive), (m_countActive > 0 ? "s" : ""));
	Logs::writeLog(LogType::Info, "LxcContainer::init", info);
}

/**
 * @brief LxcContainer::lxcversion								[public]
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
 * @brief LxcContainer::lxccountAll								[public]
 *
 * This method gets the total number of containers activated.
 *
 * @return int if 0 no container count
 */
int LxcContainer::lxcCountActive() const
{
	return m_countActive;
}

/**
 * @brief LxcContainer::lxccountAll								[public]
 *
 * This method gets the total number of containers created, activated or not.
 *
 * @return int if 0 no container count
 */
int LxcContainer::lxcCountAll() const
{
	return m_countAll;
}

/**
 * @brief LxcContainer::lxcpath
 *
 * This getter returns the lxcpath where stored all containers.
 *
 * @return char * lxc path
 */
char *LxcContainer::lxcPath() const
{
	return m_path;
}

/**
 * @brief LxcContainer::setlxcpath								[public]
 *
 * This method sets path of lxc folder storage.
 * if the parameter is null the setter will check if default folder exists.
 *
 * @param path waits the path where lxc folder, if null check for default path.
 * @return null if folder not found.
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

		if(!qstrcpy(m_path, static_cast<char *>(defaultPath.toLatin1().data())))
			Logs::writeLog(LogType::Error, "LxcContainer::setLxcPaht", "Memory allocation failed L: 157");
	}
	else
		Logs::writeLog(LogType::Error, "LxcContainer::setLxcPaht", "LXC folder not found L: 160");
}

