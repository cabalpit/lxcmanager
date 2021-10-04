#ifndef CREATORWIDGET_H
#define CREATORWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QLineEdit>
#include <QPaintEvent>

#include "loader.h"
#include "alert.h"
#include "businesslayer/style.h"
#include "businesslayer/controller.h"

/*!
 * \brief The CreatorWidget class
 * \version 1.0
 * \since 2021-09-21
 * \author Peter Cata
 *
 * Creator permits to user to create a new container for a selected distribution,
 * release, architecture and variant.
 *
 * Creator provide to connect to lxc and request to create containers.
 */
class CreatorWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit CreatorWidget(QWidget *parent = nullptr);
		~CreatorWidget();

	signals:
		void createClicked(const QMap<QString, QString> &);

	public slots:
		void showAlert(bool success, const QString &message);

	protected:
		void initObjects();
		void initDisposal();
		void initConnections();
		void paintEvent(QPaintEvent *event) override;

	protected slots:
		void updateRelease(int);
		void updateArch(int);
		void updateVariant(int);
		void create();
		void cancelClick();
		void clearAll();
		void startLoader();
		void stopLoader();

	private:
		businesslayer::Style m_css;
		businesslayer::Controller *m_controller;

		QGridLayout *m_grid;
		QLabel *m_nameLabel;
		QLabel *m_titleIcon;
		QLabel *m_titleLabel;
		Alert *m_alert;
		QLabel *m_distribLabel;
		QLabel *m_releaseLabel;
		QLabel *m_archLabel;
		QLabel *m_variantLabel;

		QLineEdit *m_nameEdit;
		QComboBox *m_distribCombo;
		QComboBox *m_releaseCombo;
		QComboBox *m_archCombo;
		QComboBox *m_variantCombo;

		QPushButton *m_cancel;
		QPushButton *m_create;

		bool m_loading;
		Loader *m_loader;
};

#endif // CREATORWIDGET_H
