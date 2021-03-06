#pragma once

#include "communicateLib.h"
#pragma comment(lib, "CommunicateLib.lib")

namespace InstrumentApi
{
	class DataCollect
	{

	};

	class Ks34970A_2A
	{

	public:
		Ks34970A_2A(unsigned int portNo, int baudRate)
		{
			mpCommunicate = static_cast<std::shared_ptr<CommunicateDrose::CommunicateInterface>>(std::make_shared<CommunicateDrose::ComPortOne>(portNo, baudRate,10,5000));

		}

		Ks34970A_2A()
		{

		}

		~Ks34970A_2A()
		{

		}

		bool cmd(const QString cmd)
		{
			QString tRecv;
			mpCommunicate->communicate(cmd + "\r\n", tRecv);

			return true;
		}

		bool init()
		{
			if (mpCommunicate->init() == false)
			{
				return 0;
			}

			QString tRecv;
			mpCommunicate->communicate("*RST;*CLS\r\n", tRecv);

			//		mpCommunicate->communicate("CONF:VOLT:DC 10,0.001,(@101)\r\n", tRecv);
			//		mpCommunicate->communicate("READ?\r\n", tRecv);

			//		mpCommunicate->communicate("MEASure:VOLTage:DC? (@103)\r\n", tRecv);

			return 0;
		}

		enum TypeMeasure{
			VoltageAc, VoltageDc, CurrentAc, CurrentDc, Frequency
		};

		const QString voltageAc = "VOLT:AC?";
		const QString voltageDc = "VOLT:DC?";
		const QString currentAc = "CURR:AC?";
		const QString currentDc = "CURR:DC?";
		const QString frequency = "FREQUENCY?";

		float getMeasure(const QString type, QString channel){
			QString cmd = "MEAS:" + type + " (@" + channel + ")\r\n";
			QString tRecv;
			mpCommunicate->communicate(cmd, tRecv);

			return tRecv.toFloat();
		}

		bool getMeasure(const QString type, QString channel, float& value)
		{
			QString cmd = "MEAS:" + type + " (@" + channel + ")\r\n";
			QString tRecv;
			mpCommunicate->communicate(cmd, tRecv);

			value = tRecv.toFloat();

			return true;
		}


	private:
		std::shared_ptr<CommunicateDrose::CommunicateInterface> mpCommunicate;
	};
}


namespace drose
{

}
