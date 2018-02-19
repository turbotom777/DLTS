#pragma once

class IOCard:public Card
{
public:
	IOCard(void);
	~IOCard(void);
	bool initC_t(void);
	int _AI_Read(short & intein, int gain);
	int _AO_VWrite(float value);
	int _AI_VScale(int verstaerkung, int unscaliert, double &scaliert);
	int getDrift(int nuberOfAverage, int gain);

protected:
	int m_inputChannel;
	int m_outputChannel;
	
public:
	void checkDAQFinished();
	int _AO_Configure(int updateMode);
	int getInputChannel(void);
	int _DAQ_Start(int amplification, int timebaseIndex, int sampleInterval, DataHandler* data);
	int _DAQ_Clear(void);
};
