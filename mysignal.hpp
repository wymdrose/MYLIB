
#pragma once

#include <QMessageBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QTextBrowser>
#include <QTableWidgetItem>
#include <QProgressBar>

namespace Drose{

	class MySignalUi : public QObject
	{
		Q_OBJECT

	public:

		MySignalUi()
		{
			connect(this, SIGNAL(proBarSignal(QProgressBar*, int)), this, SLOT(proBarSlot(QProgressBar*, int)));
			connect(this, SIGNAL(colorSignal(QPushButton*, const QString)), this, SLOT(colorSlot(QPushButton*, const QString)));
			connect(this, SIGNAL(colorSignal(QCheckBox*, const QString)), this, SLOT(colorSlot(QCheckBox*, const QString)));
			connect(this, SIGNAL(colorSignal(QLabel*, const QString)), this, SLOT(colorSlot(QLabel*, const QString)));
			connect(this, SIGNAL(colorSignal(QTableWidgetItem*, const QColor)), this, SLOT(colorSlot(QTableWidgetItem*, const QColor)));
			connect(this, SIGNAL(ableSignal(QPushButton*, bool)), this, SLOT(ableSlot(QPushButton*, bool)));
			connect(this, SIGNAL(showMsgSignal(QTextBrowser*, const QString&)), this, SLOT(showMsg(QTextBrowser*, const QString &)));
			connect(this, SIGNAL(showDialogSignal(const QString&)), this, SLOT(showDialog(const QString &))/*, Qt::BlockingQueuedConnection*/);		
		}

	signals:
		void proBarSignal(QProgressBar*, int);
		void colorSignal(QPushButton*, const QString);
		void ableSignal(QPushButton*, bool);
		void colorSignal(QCheckBox*, const QString);
		void colorSignal(QLabel*, const QString);
		void colorSignal(QTableWidgetItem*, const QColor);
		void showMsgSignal(QTextBrowser*, const QString&);
		void showDialogSignal(const QString&);		

	private slots:
		void proBarSlot(QProgressBar* p, int t)
		{
			p->setValue(t);
		}
		void colorSlot(QPushButton* p, const QString t){ p->setStyleSheet(t); }
		void ableSlot(QPushButton* p, bool b){ p->setEnabled(b); }	
		void colorSlot(QCheckBox* p, const QString t){ p->setStyleSheet(t); }
		void colorSlot(QLabel* p, const QString t){ p->setStyleSheet(t); }
		void colorSlot(QTableWidgetItem* p, const QColor t){ p->setBackgroundColor(t); }
		void showMsg(QTextBrowser* p, const QString t){
			p->append(t);
		}
		void showDialog(const QString &msg){
			QMessageBox::information(&mDialog, "", msg);
		}
		

	private:
		QDialog mDialog;

	};


}

