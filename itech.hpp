
#pragma once

#include "communicateLib.hpp"
#include <memory>

namespace InstrumentApi
{
	class ItechIt8600
	{
	public:
		ItechIt8600(unsigned int portNo, int baudRate)
		{
			mpCommunicate = static_cast<std::shared_ptr<CommunicateClass::CommunicateInterface>>(std::make_shared<CommunicateClass::ComPortOne>(portNo, baudRate));
		}

		ItechIt8600()
		{

		}

		~ItechIt8600()
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

		

	private:
		std::shared_ptr<CommunicateClass::CommunicateInterface> mpCommunicate;

	};


	class ItechIt8800
	{
	public:
		ItechIt8800(unsigned int portNo, int baudRate)
		{
			mpCommunicate = static_cast<std::shared_ptr<CommunicateClass::CommunicateInterface>>(std::make_shared<CommunicateClass::ComPortOne>(portNo, baudRate));
		}

		ItechIt8800()
		{

		}

		~ItechIt8800()
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



	private:
		std::shared_ptr<CommunicateClass::CommunicateInterface> mpCommunicate;

	};
}

