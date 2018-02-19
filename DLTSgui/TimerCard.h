#pragma once

class TimerCard:public Card
{
public:
	TimerCard(void);
	~TimerCard(void);
	void initC_t(void);

protected:
	short m_counterList[2];
	int m_counter1;
	int m_counter2;
public:
	int _CTR_Reset(void);
	int _CRT_Pulse(int pulseWidth, int delay);
	int _CTR_Simul_Op(int updateMode);
	int getCounter1(void);
};
