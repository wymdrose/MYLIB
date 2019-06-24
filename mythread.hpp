
#pragma once

#include <QThread> 

namespace Drose
{
	class MyThread1 : public QThread
	{
	public:
		MyThread1();
		void closeThread()
		{
			isStop = true;
		}

	protected:
		virtual void run()
		{

		}

	private:
		volatile bool isStop;
	};


	class MyThread2 : public QObject
	{
		Q_OBJECT
	public:
		MyThread2()
		{
			this->moveToThread(&mThread);
			mThread.start();

			connect(this, &MyThread2::finished, &mThread, &QThread::quit);
			connect(this, &MyThread2::finished, this, &MyThread2::deleteLater);
			connect(&mThread, &QThread::finished, &mThread, &QThread::deleteLater);
			
		}

		MyThread2(int index) :mIndex(index)
		{
			this->moveToThread(&mThread);
			
			connect(this, &MyThread2::finished, &mThread, &QThread::quit);
			connect(this, &MyThread2::finished, this, &MyThread2::deleteLater);
			connect(&mThread, &QThread::finished, &mThread, &QThread::deleteLater);
		}

		~MyThread2()
		{
			
		}

		void start()
		{	
			mThread.start();
		}

		void run();

		void startOnce()
		{
			connect(&mThread, &QThread::started, this, &Drose::MyThread2::once);
			mThread.start();
		}

		void once();

	signals:
		void showDialogSignal(const QString&);
		void finished();
		
	public:
		QThread		mThread;

	private:
		int		mIndex;
		QMutex		mMutex;
		
	};
}










