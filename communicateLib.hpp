#pragma once

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QHostAddress>
#include <QTcpSocket>
#include <QDateTime>
#include <memory>

namespace CommunicateClass
{
	class CommunicateInterface : public QObject
	{
	public:
		virtual bool init() = 0;
		virtual void communicate(QString) = 0;
		virtual bool communicate(QString, QString&) = 0;
		virtual bool communicate(QByteArray, QByteArray&) = 0;
	};

	class ComPortOne : public CommunicateInterface
	{
		Q_OBJECT
	public:
		ComPortOne(unsigned int portNo, int baudRate,int breakLength = 10, int breakDelay = 2000) 
			:mPortNo(portNo), mBaudRate(baudRate), mBreakLength(breakLength), mBreakDelay(breakDelay)
		{
		//	connect(&*mpSerial, SIGNAL(readyRead()), this, SLOT(recvMsg()), Qt::UniqueConnection);

			mpSerial->setPortName(QString("COM%1").arg(portNo));
			mpSerial->setBaudRate(baudRate);
			mpSerial->setParity(QSerialPort::NoParity);
			mpSerial->setDataBits(QSerialPort::Data8);
			mpSerial->setStopBits(QSerialPort::OneStop);
			mpSerial->setFlowControl(QSerialPort::NoFlowControl);

		}
		~ComPortOne()
		{
			mpSerial->close();
		}

		void close()
		{
			qDebug() << "close com" << mPortNo << "\r";
			mpSerial->close();
		}

		bool init()
		{
			mpSerial->close();

			if (mpSerial->open(QIODevice::ReadWrite)) 
			{
				qDebug() << "open com" << mPortNo << " success" << "\r";
				mbInit = true;
				return true;
			}
			else 
			{
				qDebug() << "open com" << mPortNo << " failed" << "\r";
				return false;
			}
		}

		qint64 send(const QString sendData)
		{
			mRecData.clear();
			mpSerial->clear();
			QByteArray tSend = sendData.toLocal8Bit();

			qDebug() << "";
			qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") << mPortNo << "send:" << tSend;
		
			return mpSerial->write(tSend);
		}

		inline void recData()
		{
			mRecData.clear();
			QTime time;
			time.start();
			
			forever
			{
				if (mRecData.length() > mBreakLength || time.elapsed() > mBreakDelay)
				{
					break;
				}

				while (mpSerial->waitForReadyRead(50))
				{
					QByteArray tRec = mpSerial->readAll();
					mRecData += tRec.data();
				}			
			}
			
			
			qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") << mPortNo << "rec:" << mRecData;
			
		}

		QString getRec()
		{
			return mRecData;
		}

		void communicate(const QString tSend){
			if (!mbInit){
				qDebug() << "mbInit:false";
				return;
			}
			send(tSend);
		}

		bool communicate(const QString tSend, QString& mRecv)
		{
			if (!mbInit){
				qDebug() << "mbInit:false";
				return false;
			}

			auto a = send(tSend);
			
			qDebug() << "send success?" << a << "\r";
			
			recData();

			mRecv = mRecData;

			return true;
		}

		bool communicate(const QByteArray tSend, QByteArray& mRecv)
		{
			if (!mbInit){
				qDebug() << "mbInit:false";
				return false;
			}

			auto a = mpSerial->write(tSend);

			qDebug() << "send success?" << a << "\r";

			QTime time;
			time.start();

			forever
			{
				if (mRecv.size() > mBreakLength || time.elapsed() > mBreakDelay)
				{
					break;
				}

				mpSerial->waitForReadyRead(50);
				mRecv = mpSerial->readAll();

			}

			return true;
		}

	public slots:
		void recvMsg()
		{
			mRecData.clear();

			QByteArray tRec = mpSerial->readAll();
			mRecData += tRec.data();

			qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") << mPortNo << "rec:" << mRecData;
		}

	private:
		bool mbInit = false;
		unsigned int mPortNo;
		int mBaudRate;
		std::shared_ptr <QSerialPort> mpSerial = std::make_shared<QSerialPort>();
		QString mRecData;
		int mBreakLength;
		int mBreakDelay;
	};

	class TcpClient : public CommunicateInterface
	{
	public:
		TcpClient(QString ip, int port) : mIp(ip), mPort(port)
		{
			mpQHostAddress = new QHostAddress();
			mpTcpSocket = new QTcpSocket();
		}
		~TcpClient()
		{
			delete mpTcpSocket;
			delete mpQHostAddress;
		}

		bool init()
		{
			if (!mpQHostAddress->setAddress(mIp))
			{
				qDebug() << mIp << "server ip address error!";
				return false;
			}

			mpTcpSocket->connectToHost(*mpQHostAddress, mPort);

			if (false == mpTcpSocket->waitForConnected(1000))
			{
				qDebug() << mIp << "connect failed.";
				return false;
			}

			qDebug() << mIp << "connect ok.";
			mbInit = true;
			return true;
		}

		void disConnect()
		{
			mpTcpSocket->disconnectFromHost();
	
		}

		void send(const QString msg)
		{
			mRecData.clear();

			qDebug() << "";
			qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") << mIp << " send:" << msg << "\r";

			auto re = mpTcpSocket->write(msg.toLatin1(), msg.length());
		}
		
		bool getRec()
		{
			if (false == this->mpTcpSocket->waitForReadyRead())
			{ 
				qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
				qDebug() << "Server does not response!";
				return false; 
			}

		
			QByteArray datagram = mpTcpSocket->readAll();;
			
		//	mpTcpSocket->read(datagram.data(), 4);

			QString msg = datagram.data();

			qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") << msg;
						
			return true;
		}

		bool getRec(QString& msg)
		{
			if (false == this->mpTcpSocket->waitForReadyRead())
			{
				qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
				qDebug() << "Server does not response!";
				return false;
			}

			QByteArray datagram = mpTcpSocket->readAll();;

			msg = datagram.data();

			qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") << msg;

			return true;
		}
		
		void communicate(QString tSend){
			send(tSend);
		}

		bool communicate(const QString tSend, QString& mRecv)
		{
			if (!mbInit){
				qDebug() << "mbInit:false";
				return false;
			}
			
			send(tSend);

			if (false == getRec(mRecv)){
				return false;
			}

		//	disConnect();
			return true;
		}

		bool communicate(QByteArray, QByteArray&){
			if (!mbInit){
				qDebug() << "mbInit:false";
				return false;
			}

			return true;
		}

		/*
		void slotConnected()
		{
			qDebug() << mIp << "slotConnected success.";
			Sleep(0);
		}

		void slotDisconnected()
		{
			qDebug() << mIp << "slotDisconnected.";
		}
		*/

		QTcpSocket *mpTcpSocket;
	private:
		bool mbInit = false;
		QString mIp;
		QString userName;
		int mPort;
		QHostAddress *mpQHostAddress;
		QString mRecData;
	
	};








};























