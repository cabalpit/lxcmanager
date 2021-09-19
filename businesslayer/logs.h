#ifndef LOGS_H
#define LOGS_H

#include <QObject>
#include <QHash>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
#include <QDateTime>
#include <iostream>
#include <assert.h>
#include <zlib.h>

#define MAXFILESIZE 1048576

namespace business
{
	enum LogType { Log, Info, Warning, Error };

	class Logs : public QObject
	{
			Q_OBJECT
		public:

			static void writeLog(const LogType &ltype, const QString &who, const QString &text);

		signals:


		protected:
			explicit Logs(const LogType ltype = Log, QObject *parent = nullptr);
			bool fileExists();
			qint64 fileSize();
			void compressFile();
			QString compressFileName(const QString &path);
			QString getFilePath();

		private:
			LogType m_logType;
			QString m_dirPath;
			QHash<QString, QString> m_filePath;
	};
}

#endif // LOGS_H
