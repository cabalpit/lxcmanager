#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include "configfile.h"


class ConfigDialog : public QDialog
{
		Q_OBJECT
	public:
		ConfigDialog();
		~ConfigDialog();

	signals:
		void saveConfig();

	protected:
		void initDisposale();
		void initConnect();
		void initConfig();

	protected slots:
		void save(bool);
		void cancel(bool);

	private:
		QGridLayout *m_layout;

		QLabel *m_titleLabel;
		QLabel *m_lxcFolderLabel;

		QLineEdit *m_lxcFolderLineEdit;

		QPushButton *m_save;
		QPushButton *m_cancel;

		ConfigFile *m_configFile;
};

#endif // CONFIGDIALOG_H
