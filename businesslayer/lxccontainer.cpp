#include "lxccontainer.h"

using namespace businesslayer;

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

void LxcContainer::init()
{

}

QString LxcContainer::lxcVersion() const
{
	return QString(LXC_VERSION);
}

int LxcContainer::lxcCountActive() const
{
	return m_countActive;
}

int LxcContainer::lxcCountAll() const
{
	return m_countAll;
}

char *LxcContainer::lxcPath() const
{
	return m_path;
}


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
			errors("LxcContainer::setLxcPaht", "Memory allocation failed L: 96");
	}
	else if(dir.exists(QDir::homePath() + DEFAULT_FOLDER))
	{
		QString defaultPath = QDir::homePath() + DEFAULT_FOLDER;

		m_path = new char[defaultPath.length() + 1] ();

		if(!qstrcpy(m_path, static_cast<char *>(defaultPath.toLatin1().data())))
			errors("LxcContainer::setLxcPaht", "Memory allocation failed L: 96");
	}
	else
		errors("LxcContainer::setLxcPaht", "LXC folder not found");
}

void LxcContainer::errors(const QString &methodName, const QString &error)
{
	Logs::writeLog(LogType::Error, methodName, error);
}
