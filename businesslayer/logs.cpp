#include "logs.h"

using namespace businesslayer;
using namespace std;

/**
 * @brief Logs::writeLog							[public static]
 *
 * This method writes information into log file. The type of file can be log, info, warning, error.
 *
 * @param ltype waits the type of file to write to know the option @see business::LogType
 * @param who writes the file.
 * @param text the main text with the explanations.
 */
void Logs::writeLog(const LogType &ltype, const QString &who, const QString &text)
{
	Logs *logs = new Logs(ltype);

	QString dt = QDateTime::currentDateTime().toString("yy.MM.dd hh:mm:ss");
	QString writable;
	writable.append('[' + dt + "] ");
	writable.append("(" + who + ") ");
	writable.append(text + "\n");

	QFile file(logs->getFilePath());

	if(file.open(QIODevice::WriteOnly | QIODevice::Append))
		file.write(writable.toLatin1());

	file.close();

	delete logs;
}

/**
 * @brief Logs::Logs									[private]
 *
 * Construct the object. The default constructor sets log directory
 * path, the files path for all types, creates directory if not exits
 * and request compression if log file is heavy, and truncate main files.
 *
 * @param ltype	waits log type file @see business::LogType
 * @param parent waits the parent object.
 */
Logs::Logs(const LogType ltype, QObject *parent) : QObject(parent)
{
	m_logType = ltype;
	m_dirPath = QDir::homePath() + "/.local/share/lxcmanager/log";

	m_filePath.insert("log", m_dirPath + "/log.log");
	m_filePath.insert("info", m_dirPath + "/info.log");
	m_filePath.insert("warn", m_dirPath + "/warn.log");
	m_filePath.insert("error", m_dirPath + "/error.log");

	if(!createDir())
		return;

	if(fileExists() && fileSize() >= MAXFILESIZE)
		compressFile();
}

/**
 * @brief Logs::createDir									[private]
 *
 * This method creates log directory if not exists.
 *
 * @return true if folder exists or has been created otherwize false.
 */
bool Logs::createDir()
{
	bool success = true;
	QDir dir(m_dirPath);

	if(!dir.exists())
		success = dir.mkdir(m_dirPath);

	return success;
}

/**
 * @brief Logs::fileExists									[private]
 *
 * This method check if the files requested exists.
 * @return true if file exists otherwize false.
 */
bool Logs::fileExists()
{
	QFile file(getFilePath());
	return file.exists();
}

/**
 * @brief Logs::fileSize									[private]
 *
 * This method returns the size in bytes of the selected file.
 *
 * @return qint64 file size.
 */
qint64 Logs::fileSize()
{
	QFileInfo fi(getFilePath());
	return fi.size();
}

/**
 * @brief Logs::compressFile									[private]
 *
 * This method will compress file selected using gz. The compressed file will be prefixed
 * with a number.
 */
void Logs::compressFile()
{
	// find how many gz file exists for the type
	QString filePath = getFilePath();
	QString fileName = compressFileName(filePath);

	FILE *infile = fopen(filePath.toStdString().c_str(), "rb");
	gzFile outfile = gzopen(QString(m_dirPath + "/" + fileName).toStdString().c_str(), "wb");

	char buffer[1024];
	size_t numRead = 0;

	while ((numRead = fread(buffer, 1, sizeof(buffer), infile)))
	{
		gzwrite(outfile, buffer, numRead);
	}

	fclose(infile);
	gzclose(outfile);

	//tracate file
	QFile::remove(filePath);
}

/**
 * @brief Logs::compressFileName									[private]
 *
 * This method determinates the compressed file name, based on file name.
 * The method will check if compressed files exist and will get the prefix.
 *
 * For example, ~/log/error.log main file, in the parent folder it exists 3 compressed files,
 * The metod will returns error.log.4.gz
 *
 * @param path waits the path of the main file.
 * @return compressed file name.
 */
QString Logs::compressFileName(const QString &path)
{
	// find filename
	QRegularExpression reg("[a-z]+\\.log$");
	QRegularExpressionMatch matches = reg.match(path);

	if(!matches.hasMatch())
		return NULL;

	QString fileName = matches.captured(0);

	// set pattern to find file zipped file into folder.
	reg.setPattern(QString("%1\\.[0-9]+\\.gz$").arg(reg.escape(fileName)));


	// iterate files into folder to find the gz file of the category.
	QDirIterator it(m_dirPath, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot);

	int cntFile = 0;
	while (it.hasNext())
	{
		if(reg.match(it.next()).hasMatch())
			cntFile++;
	}

	return QString("%1.%2.gz").arg(fileName, QString::number(++cntFile));
}

/**
 * @brief Logs::getFilePath									[private]
 *
 * This method determine which file name in function of the LogType file
 * selected through the constructor.
 *
 * @return log file name
 */
QString Logs::getFilePath()
{
	QString path;

	switch (m_logType)
	{
		case Log:
			path = m_filePath["log"];
		break;

		case Info:
			path = m_filePath["info"];
		break;

		case Warning:
			path = m_filePath["warn"];
		break;

		case Error:
			path = m_filePath["error"];
		break;

		default:
		break;
	}

	return path;
}
