// DAQDevice.h: interface for the DAQDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DAQDEVICE_H__AD97EB76_90A8_4004_9994_8A6CCD57BC61__INCLUDED_)
#define AFX_DAQDEVICE_H__AD97EB76_90A8_4004_9994_8A6CCD57BC61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DAQDevice  
{
public:
	int _DAQ_Config(int triggerMode);
	DAQDevice();
	virtual ~DAQDevice();

	int _AI_Read(short & intein, int gain);
	int _AO_VWrite(float value);
	int _AI_VScale(int verstaerkung, int unscaliert, double &scaliert);
	int getDrift(int nuberOfAverage, int gain);

	void checkDAQFinished();
	int _AO_Configure(int updateMode);
	int _DAQ_Start(int amplification, int timebaseIndex, int sampleInterval, DataHandler* data);
	int _DAQ_Clear(void);

	int _CTR_Reset(void);
	int _CRT_Pulse(int pulseWidth, int delay);
	int _CTR_Simul_Op(int updateMode);

};

#endif // !defined(AFX_DAQDEVICE_H__AD97EB76_90A8_4004_9994_8A6CCD57BC61__INCLUDED_)
