#pragma once


#define MAX_MEMORY_ELEMENTS 131068
#define RESULT_FIELD_SIZE  1408

class DataHandler
{
public:
	DataHandler(void);
	~DataHandler(void);

protected:
	int m_amplification;
	unsigned long m_lockedHandle;
	
	int m_frequency; 
	int m_messuringTime;
	short m_handle;

	bool m_isMemLocked;
	bool m_isMemAlloced;
public:
	unsigned long getMemoryHandle();
	void copyData(short *resultArray, int nullification);
	int initMemory(void);
};
