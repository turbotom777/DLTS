#include "stdafx.h"
#include "card.h"
#include "wdaq_c.h"
#include "nidaqcns.h"


Card::Card(void)
{
}

Card::~Card(void)
{
}

int Card::getDevice(){
	return m_device;
}

