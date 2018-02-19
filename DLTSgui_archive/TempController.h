#if !defined(AFX_TEMPCONTROLLER_456__INCLUDED_)
#define AFX_TEMPCONTROLLER_456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class TempController
{
public:
	TempController(void);
	~TempController(void);
	float setTemperature(float Tsetpoint, float maxDeviance, bool bWaitForTemp=true);
	void start(int TStart, int TEnd, int TStep, int holdTime);
	float getValue(CString data);
	float getCurrentTemperature();

protected:
	bool hasTemperature(float & Tcurrent, float Tsetpoint);
	bool wait(int interval);
	void writeData(int port, CString data);
	CString readData(int port);
	float doQuery(CString cmd);

	int getTimeMs();
	char createBCC(CString packet);
	ComHandler m_comHandler;
	bool doAbort();
	//CFileWriter m_fileWriter;

	int getCurrentTimeSec();
	int m_startTimeSec;

	
};

#endif // !defined(AFX_TEMPCONTROLLER_456__INCLUDED_)

