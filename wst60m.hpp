#pragma once

#include "communicateLib.h"
#pragma comment(lib, "CommunicateLib.lib")

namespace InstrumentApi{

	class Wst60m485{
	
	public:
		Wst60m485(unsigned int portNo, int baudRate){
			mpCommunicate = static_cast<std::shared_ptr<CommunicateDrose::CommunicateInterface>>
				(std::make_shared<CommunicateDrose::ComPortOne>(portNo, baudRate,10,3000));
		}

		bool init(){
			if (mpCommunicate->init() == false){
				return false;
			}
			return true;
		}

		bool getVoice(unsigned short& voice){
			QByteArray tSend;

			//0A 04 00 00 00 03 B1 70
			tSend.resize(8);
			tSend[0] = 0x0A;
			tSend[1] = 0x04;
			tSend[2] = 0x00;
			tSend[3] = 0x00;
			tSend[4] = 0x00;
			tSend[5] = 0x03;
			tSend[6] = 0xB1;
			tSend[7] = 0x70;

			QByteArray tRecv;

			mpCommunicate->communicate(tSend, tRecv);

			unsigned char tArray[2];
			tArray[0] = tRecv[6];
			tArray[1] = tRecv[5];

			memcpy(&voice, tArray, 2);

			return true;
		}

	private:
		std::shared_ptr<CommunicateDrose::CommunicateInterface> mpCommunicate;
	};


}