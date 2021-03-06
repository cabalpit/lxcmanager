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
#include <QComboBox>

#include "alert.h"
#include "businesslayer/configfile.h"
#include "businesslayer/style.h"


/*!
 * \brief The SettingsDialog class
 * \version 1.0
 * \since 2021-09-29
 * \author Peter Cata
 *
 * This class provides to display settings. It allow user to see and modify
 * settings of application.
 */
class SettingsDialog : public QDialog
{
		Q_OBJECT
	public:
		/*!
		 * \struct Language
		 * \brief The Language struct hold language informations.
		 *
		 * This structure is intrenal use to hold language information.
		 */
		struct Language
		{
				int index;
				QString name;
				QString icon;
				QString iso;
		};

		explicit SettingsDialog(QWidget *parent = nullptr);
		~SettingsDialog();

	signals:
		void savedConfig();

	protected:
		void initObjects();
		void initDisposal();
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
		QLabel *m_languageLabel;

		QLineEdit *m_lxcFolderLineEdit;
		QLineEdit *m_hkpLineEdit;
		QLineEdit *m_snapLineEdit;
		QCheckBox *m_lxcAutoStartCheckbox;
		QComboBox *m_languageCombo;

		QPushButton *m_snapBtn;
		QPushButton *m_save;
		QPushButton *m_close;
		QPushButton *m_reset;

		QVector<Language> m_language;

		businesslayer::ConfigFile *m_configFile;
		businesslayer::Style m_css;
};

#endif // SETTINGSDIALOG_H
