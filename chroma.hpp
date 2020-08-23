
#pragma once

#include "communicateLib.h"
#pragma comment(lib, "CommunicateLib.lib")

namespace InstrumentApi
{
	class Chroma62000H
	{
	public:
		Chroma62000H(unsigned int portNo, int baudRate)
		{
			mpCommunicate = static_cast<std::shared_ptr<CommunicateDrose::CommunicateInterface>>(std::make_shared<CommunicateDrose::ComPortOne>(portNo, baudRate));
		}

		Chroma62000H()
		{

		}

		~Chroma62000H()
		{

		}

		bool init()
		{
			if (mpCommunicate->init() == false)
			{
				return 0;
			}

	//		QString tRecv;
	//		mpCommunicate->communicate("*RST;*CLS\r\n", tRecv);

			return 0;
		}

		bool cmd(const QString cmd)
		{
			QString tRecv;
			mpCommunicate->communicate(cmd, tRecv);

			return true;
		}

		bool setVoltage(const QString value)
		{
			QString tRecv;
			mpCommunicate->communicate("SOUR:VOLT " + value + "\r\n", tRecv, 0);
		
			return true;
		}

		bool setCurrent(const QString value)
		{
			QString tRecv;
			mpCommunicate->communicate("SOUR:CURR " + value + "\r\n", tRecv, 0);

			return true;
		}

		void confOutput(bool on_off)
		{

			QString tRecv;
			mpCommunicate->communicate(on_off ? "CONFigure:OUTPut ON\r\n" : "CONFigure:OUTPut OFF\r\n", tRecv, 0);


		}

	private:
		std::shared_ptr<CommunicateDrose::CommunicateInterface> mpCommunicate;

	};




}







