#pragma once

class TempController
{
public:
	TempController(void);
	~TempController(void);
	float setTemperature(float Tsetpoint, bool bWaitForTemp=true);
	void start(int TStart, int TEnd, int TStep, int holdTime);
	float getValue(CString data);

protected:
	bool hasTemperature(float & Tcurrent, float Tsetpoint);
	bool wait(int interval);
	void writeData(int port, CString data);
	CString readData(int port);
	float doQuery(CString cmd);

	int getTimeMs();
	char createBCC(CString packet);
	ComHandler m_comHandler;
	bool abort();
	CFileWriter m_fileWriter;

	int getCurrentTimeSec();
	int m_startTimeSec;

	
};
