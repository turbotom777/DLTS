// Booton7200.h: interface for the Booton7200 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOTON7200_H__DA0063C0_E4DE_470E_AA69_94EE384CD74A__INCLUDED_)
#define AFX_BOOTON7200_H__DA0063C0_E4DE_470E_AA69_94EE384CD74A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBoonton7200  
{
public:
	bool IsInRange(float capacitance);
	void SetZero();
	void setPulse(float baseVoltage, float pulseVoltage);
	void setBaseVoltage(float baseVoltage);
	double getCapacitance(double U);
	
	void shutdown();
	void initC_U();
	void initDevice();

	void setRange2pF();
	void setRange20pF();
	void setRange200pF();
	void setRange2000pF();

	void setRangeMultiplier(int multiplier);
	int getRangeMultiplier();

	
	CBoonton7200();
	virtual ~CBoonton7200();

	int _ibwrt(char cmd[]);
	int _ibrd( char cmd[], int maxLen);

	
private:
	
	int m_rangeMultiplier;
	int m_device;
	
	void checkStatus();
	void gpiberr(CString msg);
protected:
	void SetRange();
};

#endif // !defined(AFX_BOOTON7200_H__DA0063C0_E4DE_470E_AA69_94EE384CD74A__INCLUDED_)
