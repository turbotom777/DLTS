
#if !defined(AFX_C_T_MESS_H__732A472B_A20F_11D9_8F79_00E0290686A0__INCLUDED_)
#define AFX_C_T_MESS_H__732A472B_A20F_11D9_8F79_00E0290686A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"



class C_t_mess {
	public:
		C_t_mess();
		void start();
		void init(int pulsWidth, int delay, int numberOfAveraging, int gain, float reverseVoltage);

	protected:
		int m_numberOfMessurements;
		int m_pulsWidth;
		int m_delay;
		int m_numberOfAveraging;
		int m_gain;
		float m_reverseVoltage;

		bool abort();
};


#endif // !defined(AFX_C_T_MESS_H__732A472B_A20F_11D9_8F79_00E0290686A0__INCLUDED_)
