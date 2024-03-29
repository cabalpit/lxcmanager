#include "settingsdialog.h"

using namespace businesslayer;

/*!
 * \brief ConfigDialog::ConfigDialog							[public]
 *
 * Construct a \c SettingsDialog object with the given parent.
 *
 * \param parent waits parent widget, default nullptr
 */
SettingsDialog::SettingsDialog(QWidget *parent): QDialog(parent)
{
	initConfig();
	initObjects();
	initDisposal();
	initConnections();

	setAutoFillBackground(true);
	setWindowTitle(tr("LXC Configuration"));
}

/*!
 * \brief ConfigDialog::~ConfigDialog
 *
 * Destructor delete all object included in this class.
 */
SettingsDialog::~SettingsDialog()
{
	delete m_alert;
	delete m_lxcFolderLabel;
	delete m_hkpLabel;
	delete m_snapLabel;
	delete m_lxcAutoStartLabel;
	delete m_languageLabel;
	delete m_hkpLineEdit;
	delete m_lxcFolderLineEdit;
	delete m_lxcAutoStartCheckbox;
	delete m_languageCombo;
	delete m_snapLineEdit;
	delete m_snapBtn;
	delete m_save;
	delete m_close;
	delete m_reset;

	delete m_layout;

	delete m_configFile;
}

/*!
 * \brief ConfigDialog::initDisposale						[protected]
 *
 * This method initializes the ui disposition of the objects of this class.
 */
void SettingsDialog::initObjects()
{
	m_layout = new QGridLayout(this);

	QFont bold("lato-bold");
	bold.setBold(true);

	m_alert = new Alert(this);
	m_alert->setMinimumHeight(45);

	m_lxcFolderLabel = new QLabel(tr("LXC folder path:"), this);
	m_hkpLabel = new QLabel(tr("Keyserver url"), this);
	m_snapLabel = new QLabel(tr("Snapshot Folder Comments:"), this);
	m_lxcAutoStartLabel = new QLabel(tr("Autostart containers: "), this);
	m_languageLabel = new QLabel(tr("Language: "), this);

	m_lxcFolderLineEdit = new QLineEdit(this);
	m_lxcFolderLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_lxcFolderLineEdit->setText(m_configFile->find("lxcPath", QDir::homePath() + "/.local/share/lxc/").toString());

	QString commentPath = m_configFile->find("snapcommentfolder", QDir::homePath() + "/Snaps").toString();

	m_snapLineEdit = new QLineEdit(this);
	m_snapLineEdit->setEnabled(false);
	m_snapLineEdit->setText(commentPath);

	m_hkpLineEdit = new QLineEdit(this);
	m_hkpLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_hkpLineEdit->setText(m_configFile->find("hkp", "hkp://keyserver.ubuntu.com").toString());


	m_lxcAutoStartCheckbox = new QCheckBox(this);
	m_lxcAutoStartCheckbox->setChecked(m_configFile->find("autostart", false).toBool());

	m_snapBtn = new QPushButton(tr("Browse"), this);
	m_snapBtn->setIcon(QIcon(":/icons/new_folder_white"));
	m_snapBtn->setStyleSheet(m_css["primary-button"]);

	QString confLang = m_configFile->find("language").toString();
	Language *iso = std::find_if(m_language.begin(), m_language.end(), [&] (Language value) { return value.iso == confLang; });

	m_languageCombo = new QComboBox(this);

	for (Language &language : m_language)
		m_languageCombo->addItem(QIcon(language.icon), language.name, language.iso);

	m_languageCombo->setCurrentIndex(iso ? iso->index : 0);

	m_save = new QPushButton(tr("Save"), this);
	m_save->setStyleSheet(m_css["primary-button"]);
	m_save->setAutoFillBackground(true);

	m_close = new QPushButton(tr("Close"), this);
	m_close->setStyleSheet(m_css["default-button"]);
	m_close->setAutoFillBackground(true);

	m_reset = new QPushButton(this);
	m_reset->setIcon(QIcon(":/icons/refresh_black"));
	m_reset->setIconSize(QSize(24, 24));
	m_reset->setStyleSheet(m_css["default-rounded-button"]);
	m_reset->setAutoFillBackground(true);
	m_reset->setFixedSize(41, 41);
}

/**
 * @brief ConfigDialog::initDisposale						[protected]
 *
 * This method initializes the ui disposition of the objects of this class.
 */
void SettingsDialog::initDisposal()
{
	m_layout->addWidget(m_reset, 0, 3, Qt::AlignRight);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 0, 1, 4);
	m_layout->addWidget(m_alert, 2, 0, 2, 4);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 0, 1, 4);
	m_layout->addWidget(m_lxcFolderLabel, 4, 0, Qt::AlignRight);
	m_layout->addWidget(m_lxcFolderLineEdit, 4, 1, 1, 3);
	m_layout->addWidget(m_hkpLabel, 5, 0, Qt::AlignRight);
	m_layout->addWidget(m_hkpLineEdit, 5, 1, 1, 3);

	m_layout->addWidget(m_snapLabel, 6, 0, Qt::AlignRight);
	m_layout->addWidget(m_snapLineEdit, 6, 1, 1, 2);
	m_layout->addWidget(m_snapBtn, 6, 3);

	m_layout->addWidget(m_lxcAutoStartLabel, 7, 0, Qt::AlignRight);
	m_layout->addWidget(m_lxcAutoStartCheckbox, 7, 1, 1, 3, Qt::AlignLeft);

	m_layout->addWidget(m_languageLabel, 8, 0, Qt::AlignRight);
	m_layout->addWidget(m_languageCombo, 8, 1, 1, 3);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 9, 0);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 9, 1);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 9, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 9, 3);

	m_layout->addWidget(m_close, 10, 2);
	m_layout->addWidget(m_save, 10, 3);

	setLayout(m_layout);
	setFixedSize(550, 340);
	setStyleSheet(m_css["body"]);
}

/*!
 * \brief ConfigDialog::initConnect				[protected]
 *
 * This method connect the objects between them or with the slot of this class.
 */
void SettingsDialog::initConnections()
{
	connect(m_save, &QPushButton::clicked, this, &SettingsDialog::save);
	connect(m_close, &QPushButton::clicked, this, &SettingsDialog::close);
	connect(m_reset, &QPushButton::clicked, this, &SettingsDialog::reset);
	connect(m_snapBtn, &QPushButton::clicked, this, &SettingsDialog::snapDir);
}

/*!
 * \brief ConfigDialog::initConfig				[protected]
 *
 * This method instantiates configFile object of the class ConfigFile.
 *
 * \return true if the configFile object can open the file otherwize false.
 */
bool SettingsDialog::initConfig()
{
	m_language.append(Language { .index = 0, .name = "English UK", .icon = ":/icons/flags/en_EN", .iso = "en_EN" });
	m_language.append(Language { .index = 1, .name = "English US", .icon = ":/icons/flags/en_US", .iso = "en_US" });
	m_language.append(Language { .index = 2, .name = "Français", .icon = ":/icons/flags/fr_FR", .iso = "fr_FR" });
	m_language.append(Language { .index = 3, .name = "Italiano", .icon = ":/icons/flags/it_IT", .iso = "it_IT" });

	m_configFile = new ConfigFile;
	return m_configFile->isConfigFileOpen();
}

/*!
 * \brief ConfigDialog::reset				[protected]
 *
 * This method reset the config file.
 */
void SettingsDialog::reset()
{
	m_lxcFolderLineEdit->setText(QDir::homePath() + "/.local/share/lxc/");
	m_hkpLineEdit->setText("hkp://keyserver.ubuntu.com");
	m_snapLineEdit->setText(QDir::homePath() + "/Snaps");
	m_lxcAutoStartCheckbox->setChecked(false);
	m_languageCombo->setCurrentIndex(0);

	save(true);
}

/*!
 * \brief ConfigDialog::closeEvent					[protected]
 *
 * Override close event.
 *
 * \param event @see QCloseEvent
 */
void SettingsDialog::closeEvent(QCloseEvent *event)
{
	m_alert->clean();
	QDialog::closeEvent(event);
}

/*!
 * \brief ConfigDialog::save
 *
 * This method will save to config file the information filled by the user.
 */
void SettingsDialog::save(bool)
{
	QMap<QString, QVariant> map;
	map.insert("lxcPath", m_lxcFolderLineEdit->text());
	map.insert("hkp", m_hkpLineEdit->text());
	map.insert("snapcommentfolder", m_snapLineEdit->text());
	map.insert("autostart", !m_lxcAutoStartCheckbox->isChecked() ? "0" : "1");
	map.insert("language", m_languageCombo->currentData().toString());
	map.insert("version", m_configFile->find("version"));


	m_alert->clean();

	if(m_configFile->save(map))
	{
		m_alert->success(tr("Configuration Saved!"));
		emit savedConfig();
	}
	else
		m_alert->danger(tr("Configuration not Saved please try later!"));
}

/*!
 * \brief ConfigDialog::snapDir
 *
 * This method trigger \c QFileDialog to select the default directory to save snapshot comment.
 */
void SettingsDialog::snapDir()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Snapshot comments folder"), QDir::homePath());

	if(!path.isEmpty())
		m_snapLineEdit->setText(path);
}
