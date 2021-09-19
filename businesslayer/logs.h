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

#ifdef QT_DEBUG
	#define MAXFILESIZE 20480
#else
	#define MAXFILESIZE 2097152
#endif

namespace businesslayer
{
	/**
	 * @brief The LogType enum
	 *
	 * The enum hold the file type for log file.
	 */
	enum LogType { Log, Info, Warning, Error };

	/**
	 * @brief The Logs class
	 *
	 * The Logs class write the logs to file in the log folder.
	 * The object using the class use only the static method write file.
	 *
	 * @version 1.0
	 * @since 2021-09-19
	 * @author pcata
	 */
	class Logs : public QObject
	{
			Q_OBJECT
		public:

			static void writeLog(const LogType &ltype, const QString &who, const QString &text);

		signals:


		protected:
			explicit Logs(const LogType ltype = Log, QObject *parent = nullptr);
			bool createDir();
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
