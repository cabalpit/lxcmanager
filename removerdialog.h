#ifndef REMOVERDIALOG_H
#define REMOVERDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPainter>
#include <QTimer>
#include "businesslayer/style.h"

class RemoverDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit RemoverDialog(QWidget *parent = nullptr);
		~RemoverDialog();

	signals:
		void distroyClicked(int id);

	public slots:
		void populateCombo(const QStandardItemModel &model);
		void alert(bool success, const QString &message);

	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;

	protected slots:
		void remove();
		void cancelClick(bool);
		void startSpinner();
		void stopSpinner();

	private:
		QGridLayout *m_layout;
		QLabel *m_infoLabel;
		QLabel *m_alertLabel;
		QComboBox *m_containerCombobox;
		QPushButton *m_cancel;
		QPushButton *m_destroy;
		businesslayer::Style m_css;
		QTimer m_timer;
		bool m_loader;
		qreal m_spinnerRotation;
};

#endif // REMOVERDIALOG_H
