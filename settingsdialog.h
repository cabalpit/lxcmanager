#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QFileDialog>

#include "businesslayer/configfile.h"
#include "businesslayer/style.h"

class SettingsDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit SettingsDialog(QWidget *parent = nullptr);
		~SettingsDialog();

	signals:
		void savedConfig();

	protected:
		void initObjects();
		void initDisposale();
		void initConnections();
		bool initConfig();

		void closeEvent(QCloseEvent *event) override;

	protected slots:
		void save(bool);
		void reset();
		void snapDir();

	private:
		QGridLayout *m_layout;

		QLabel *m_alertLabel;
		QLabel *m_lxcFolderLabel;
		QLabel *m_hkpLabel;
		QLabel *m_snapLabel;
		QLabel *m_lxcAutoStartLabel;

		QLineEdit *m_lxcFolderLineEdit;
		QLineEdit *m_hkpLineEdit;
		QLineEdit *m_snapLineEdit;
		QCheckBox *m_lxcAutoStartCheckbox;

		QPushButton *m_snapBtn;
		QPushButton *m_save;
		QPushButton *m_close;
		QPushButton *m_reset;

		businesslayer::ConfigFile *m_configFile;
		businesslayer::Style m_css;
};

#endif // SETTINGSDIALOG_H
