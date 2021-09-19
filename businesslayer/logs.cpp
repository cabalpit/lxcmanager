#include "logs.h"

using namespace business;
using namespace std;

Logs::Logs(const LogType ltype, QObject *parent) : QObject(parent)
{
	m_logType = ltype;
	m_dirPath = QDir::homePath() + "/.local/share/lxcmanager/log";

	m_filePath.insert("log", m_dirPath + "/log.log");
	m_filePath.insert("info", m_dirPath + "/info.log");
	m_filePath.insert("warn", m_dirPath + "/warn.log");
	m_filePath.insert("error", m_dirPath + "/error.log");

	if(fileExists() && fileSize() >= MAXFILESIZE)
		compressFile();
}

bool Logs::fileExists()
{
	QFile file(getFilePath());
	return file.exists();
}

void Logs::writeLog(const LogType &ltype, const QString &who, const QString &text)
{
	Logs *logs = new Logs(ltype);

	QString dt = QDateTime::currentDateTime().toString("yy.MM.dd hh:mm:ss");
	QString writable;
	writable.append('[' + dt + "] ");
	writable.append("(" + who + ") ");
	writable.append(text);

	QFile file(logs->getFilePath());

	if(file.open(QIODevice::WriteOnly | QIODevice::Append))
		file.write(writable.toLatin1());

	file.close();

	delete logs;
}

qint64 Logs::fileSize()
{
	QFileInfo fi(getFilePath());

	return fi.size();
}

void Logs::compressFile()
{
	// find how many gz file exists for the type
	QString filePath = getFilePath();
	QString fileName = compressFileName(filePath);

	FILE *infile = fopen(filePath.toStdString().c_str(), "rb");
	gzFile outfile = gzopen(QString(m_dirPath + "/" + fileName).toStdString().c_str(), "wb");

	char buffer[256];
	size_t numRead = 0;

	while ((numRead = fread(buffer, 1, sizeof(buffer), infile)))
	{
		gzwrite(outfile, buffer, numRead);
	}

	fclose(infile);
	gzclose(outfile);
}

QString Logs::compressFileName(const QString &path)
{
	// find filename
	QRegularExpression reg("[a-z]+\\.log$");
	QRegularExpressionMatch matches = reg.match(path);

	if(!matches.hasMatch())
		return NULL;

	QString fileName = matches.captured(0);

	// set pattern to find file zipped file into folder.
	reg.setPattern('^' + reg.escape(fileName) + "\\.[0-9]+\\.gz$");

	// iterate files into folder to find the gz file of the category.
	QDirIterator it(m_dirPath, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot);

	int cntFile = 0;
	while (it.hasNext())
	{
		if(reg.match(it.next()).hasMatch())
			cntFile++;
	}

	return fileName + QString::number(++cntFile) + ".gz";
}

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
