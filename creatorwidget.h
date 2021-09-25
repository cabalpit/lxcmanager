#ifndef CREATORWIDGET_H
#define CREATORWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include "businesslayer/style.h"
#include "businesslayer/controller.h"

class CreatorWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit CreatorWidget(QWidget *parent = nullptr);
		~CreatorWidget();

	signals:
		void createClicked(const QMap<QString, QString> &);

	public slots:
		void containerCreated(bool create);

	protected:
		void initObjects();
		void initConnections();
		void paintEvent(QPaintEvent *pevent) override;


	protected slots:
		void updateRelease(int);
		void updateArch(int);
		void updateVariant(int);

		void cancel();
		void clear();
		void create();

		void clearAlert();
		void startSpinner();
		void stopSpinner();

	private:
		businesslayer::Style m_css;
		businesslayer::Controller *m_controller;

		QGridLayout *m_grid;
		QLabel *m_titleIcon;
		QLabel *m_titleLabel;
		QLabel *m_alertLabel;
		QLabel *m_distribLabel;
		QLabel *m_releaseLabel;
		QLabel *m_archLabel;
		QLabel *m_variantLabel;

		QComboBox *m_distribCombo;
		QComboBox *m_releaseCombo;
		QComboBox *m_archCombo;
		QComboBox *m_variantCombo;

		QPushButton *m_cancel;
		QPushButton *m_create;

		QTimer m_timer;
		bool m_spinner;
		qreal m_spinnerRotation;
};

#endif // CREATORWIDGET_H
