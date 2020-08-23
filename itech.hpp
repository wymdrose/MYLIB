
#pragma once

#include "communicateLib.h"
#pragma comment(lib, "CommunicateLib.lib")

namespace InstrumentApi
{
	class ItechIt8600
	{
	public:
		ItechIt8600(unsigned int portNo, int baudRate){
			mpCommunicate = static_cast<std::shared_ptr<CommunicateDrose::CommunicateInterface>>
				(std::make_shared<CommunicateDrose::ComPortOne>(portNo, baudRate));
		}

		ItechIt8600(QString ip, int port){
			mpCommunicate = static_cast<std::shared_ptr<CommunicateDrose::CommunicateInterface>>
				(std::make_shared<CommunicateDrose::TcpClient>(ip, port));
		}

		~ItechIt8600(){}

		bool init(){
			if (mpCommunicate->init() == false){
				return 0;
			}

			QString tRecv;
			mpCommunicate->communicate("SYSTem:VERSion?\r\n", tRecv, 5);
			mpCommunicate->communicate("SYSTem:REMote\r\n", tRecv, 0);
			mpCommunicate->communicate("PROT:AUTO:CLE ON\r\n", tRecv, 0);
			mpCommunicate->communicate("FUNC RES\r\n", tRecv, 0);

			return 0;
		}

		bool cmd(const QString cmd){
			QString tRecv;
			mpCommunicate->communicate(cmd, tRecv);

			return true;
		}

		void setRemote()
		{
			QString tRecv;
			
			mpCommunicate->communicate("SYSTem:REMote\r\n", tRecv, 0);
		}

		void setInput(bool in)
		{
			QString tRecv;
			QString tSend = in ? "INPut ON\r\n" : "INPut OFF\r\n";
			mpCommunicate->communicate(tSend, tRecv, 0);
		}

		bool setPower(const QString tPower){
			QString tRecv;

			mpCommunicate->communicate("FUNC POW\r\n", tRecv, 0);

			mpCommunicate->communicate("POW " + tPower + "\r\n", tRecv, 0);
			
		//	mpCommunicate->communicate("RES " + tPower + "\r\n", tRecv, 0);
			
			/*
			mpCommunicate->communicate("POW?\r\n", tRecv);
			if (tRecv.compare(tPower)){
				return false;
			}
			*/
			return true;
		}

	private:
		std::shared_ptr<CommunicateDrose::CommunicateInterface> mpCommunicate;
	};

	class ItechIt8800
	{
	public:
		ItechIt8800(unsigned int portNo, int baudRate)
		{
			mpCommunicate = static_cast<std::shared_ptr<CommunicateDrose::CommunicateInterface>>(std::make_shared<CommunicateDrose::ComPortOne>(portNo, baudRate));
		}

		ItechIt8800(){}

		~ItechIt8800(){}

		bool init(){
			if (mpCommunicate->init() == false)	{
				return 0;
			}

			QString tRecv;
			mpCommunicate->communicate("SYSTem:VERSion?\r\n", tRecv, 5);
			mpCommunicate->communicate("SYSTem:REMote\r\n", tRecv, 0);
			return 0;
		}

		bool cmd(const QString cmd)	{
			QString tRecv;
			mpCommunicate->communicate(cmd, tRecv);

			return true;
		}

	private:
		std::shared_ptr<CommunicateDrose::CommunicateInterface> mpCommunicate;

	};
}

