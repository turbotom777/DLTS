
#if !defined(AFX_C_T_MESS_H__732A472B_A20F_11D9_8F79_00E0290686A0__INCLUDED_)
#define AFX_C_T_MESS_H__732A472B_A20F_11D9_8F79_00E0290686A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
class TempController;
class CDLTSguiDoc;
class CBoonton7200;
class DAQDevice;
class DataHandler;


class CDLTSdevice {
	public:
		
		CDLTSdevice();
		~CDLTSdevice();
		void start(CDLTSguiDoc * dltsDoc);
		void ShowHardwareInfo();

		void testThread();
		float getCurrentTemp();
		CWinThread* m_pThread;
		void setAbortFlag();
		bool isRunning();
		void setIsRunning(bool isRunning);

		void writeVoltage(float voltage);
		static bool m_bAbort;

		CBoonton7200* getBoonton();

	protected:
		void initCt(float reverseVoltage);
		bool doAbort();
		
		static bool m_bRunning;
		TempController *m_pTempController;

		CBoonton7200 *m_pBoonton;
		DAQDevice *m_pDAQDevice;
		DataHandler *m_pDataHandler;


};


#endif // !defined(AFX_C_T_MESS_H__732A472B_A20F_11D9_8F79_00E0290686A0__INCLUDED_)
