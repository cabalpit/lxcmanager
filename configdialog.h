#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QVBoxLayout>
#include "configfile.h"


class ConfigDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit ConfigDialog(QWidget *parent = nullptr);
		~ConfigDialog();

	signals:
		void savedConfig();

	protected:
		void initDisposale();
		void initConnect();
		bool initConfig();

	protected slots:
		void save(bool);

	private:
		QGridLayout *m_layout;

		QLabel *m_infoLabel;
		QLabel *m_lxcFolderLabel;
		QLabel *m_lxcAutoStartLabel;

		QLineEdit *m_lxcFolderLineEdit;
		QCheckBox *m_lxcAutoStartCheckbox;

		QPushButton *m_save;
		QPushButton *m_close;

		ConfigFile *m_configFile;
};

#endif // CONFIGDIALOG_H
