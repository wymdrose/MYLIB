#pragma once

#include "Visa/vigpib.hpp"

using namespace Visa;

namespace InstrumentApi{
	
	class Wt230{
	public:
		Wt230(){}
		~Wt230(){}

		bool init(){
			status = viOpenDefaultRM(&defaultRM);
			if (status < VI_SUCCESS)
			{
				printf("Could not open a session to the VISA Resource Manager!\n");
				return false;
				exit(EXIT_FAILURE);
			}

			status = viOpen(defaultRM, "GPIB::1::INSTR", VI_NULL, VI_NULL, &inst);

			status = viInstallHandler(inst, VI_EVENT_IO_COMPLETION, AsyncHandler, uhandle);
			status = viEnableEvent(inst, VI_EVENT_IO_COMPLETION, VI_HNDLR, VI_NULL);

			//
			strcpy(stringinput, "RC\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			strcpy(stringinput, "HD0;FL0;LF0;SC0;AG0\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			strcpy(stringinput, "DA1;EA1;DB2;EB1;DC3;EC1\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			strcpy(stringinput, "RV7\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			strcpy(stringinput, "RA7\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			strcpy(stringinput, "MN0\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			strcpy(stringinput, "OFD0;DL0\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			//
			
			strcpy(stringinput, "H0\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);
			
			strcpy(stringinput, "OF1,3,1\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);
			
			return true;
		}

		bool cmd(QString send, QString& recv){

			memset(data1, 0, READ_BUFFER_SIZE);

			strcpy(stringinput, QString(send + "\n").toStdString().c_str());
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);
			status = viReadAsync(inst, data1, READ_BUFFER_SIZE - 1, &job);
			recv = (char*)data1;
			
			return true;
		}

		void close(){
			viClose(inst);
			viClose(defaultRM);
		}

		bool get(float& recv){
			
			memset(data1, 0, READ_BUFFER_SIZE);
			strcpy(stringinput, "OD\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);
			status = viReadAsync(inst, data1, READ_BUFFER_SIZE - 1, &job);
					
			QStringList tValue = QString((char*)data1).split(",");
			recv = tValue[0].right(tValue[0].length()-1).toFloat();

			return true;
		}

		float getPower(int m){

			strcpy(stringinput, QString("DA1;EA%0;DB2;EB%0;DC3;EC%0\n").arg(m).toStdString().c_str());
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			strcpy(stringinput, QString("OF1,3,%0\n").arg(m).toStdString().c_str());
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			memset(data1, 0, READ_BUFFER_SIZE);
			strcpy(stringinput, "OD\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);
			status = viReadAsync(inst, data1, READ_BUFFER_SIZE - 1, &job);

			QStringList tValue = QString((char*)data1).split(",");
			return tValue[m - 1].right(tValue[m-1].length() - 1).toFloat();
		}


		/*
		bool gpibHarmonics(){
			strcpy(stringinput, "RC\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			strcpy(stringinput, "SI2\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);
				
			strcpy(stringinput, "RV7\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);

			strcpy(stringinput, "RA7\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);
				
			strcpy(stringinput, "HE1;PS1;DF0;HA1\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);
			
			strcpy(stringinput, "OH2,1\n");
			BytesToWrite = (ViUInt32)strlen(stringinput);
			status = viWrite(inst, (ViBuf)stringinput, BytesToWrite, &rcount);
			status = viReadAsync(inst, data1, READ_BUFFER_SIZE - 1, &job);
				
			return true;
		}
		*/

		/*
		printf("\n\nHit enter to continue.");
		letter = getchar();

		if (stopflag == VI_TRUE)
		{
		data1[RdCount] = '\0';
		printf("Here is the data:  %s", data1);
		}
		else
		{
		status = viTerminate(inst, VI_NULL, job);
		printf("The asynchronous read did not complete.\n");
		}
		printf("\nHit enter to continue.");
		fflush(stdin);
		getchar();

		*/
	private:
	
};
}