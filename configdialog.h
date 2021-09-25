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

#include "businesslayer/configfile.h"
#include "businesslayer/style.h"

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
		void reset();

		void closeEvent(QCloseEvent *event) override;

	protected slots:
		void save(bool);

	private:
		QGridLayout *m_layout;

		QLabel *m_alertLabel;
		QLabel *m_lxcFolderLabel;
		QLabel *m_hkpLabel;
		QLabel *m_lxcAutoStartLabel;

		QLineEdit *m_lxcFolderLineEdit;
		QLineEdit *m_hkpLineEdit;
		QCheckBox *m_lxcAutoStartCheckbox;

		QPushButton *m_save;
		QPushButton *m_close;
		QPushButton *m_reset;

		businesslayer::ConfigFile *m_configFile;
		businesslayer::Style m_css;
};

#endif // CONFIGDIALOG_H
