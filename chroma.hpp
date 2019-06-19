
#pragma once

#include "communicateLib.hpp"
#include <memory>

namespace InstrumentApi
{
	class Chroma62000H
	{
	public:
		Chroma62000H(unsigned int portNo, int baudRate)
		{
			mpCommunicate = static_cast<std::shared_ptr<CommunicateClass::CommunicateInterface>>(std::make_shared<CommunicateClass::ComPortOne>(portNo, baudRate));
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

			QString tRecv;
			mpCommunicate->communicate("*RST;*CLS\r\n", tRecv);

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
			mpCommunicate->communicate("SOUR:VOLT " + value, tRecv);

			return true;
		}

		bool setCurrent(const QString value)
		{
			QString tRecv;
			mpCommunicate->communicate("SOUR:CURR " + value, tRecv);

			return true;
		}

		void confOutput(bool on_off)
		{

			QString tRecv;
			mpCommunicate->communicate("CONFigure:OUTPut " + on_off ? "ON" : "OFF", tRecv);


		}

	private:
		std::shared_ptr<CommunicateClass::CommunicateInterface> mpCommunicate;

	};




}







