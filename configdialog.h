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
#include <QFileDialog>

#include "alert.h"
#include "businesslayer/configfile.h"
#include "businesslayer/style.h"

/*!
 * \brief The ConfigDialog class
 * \version 1.0
 * \since 2021-09-29
 * \author Peter Cata
 *
 * This class provides to display settings. It allow user to see and modify
 * settings of application.
 */
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
		void initConnections();
		bool initConfig();

		void closeEvent(QCloseEvent *event) override;

	protected slots:
		void save(bool);
		void reset();
		void snapDir();

	private:
		QGridLayout *m_layout;

		Alert *m_alert;
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

#endif // CONFIGDIALOG_H
