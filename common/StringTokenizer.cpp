// StringBuffer.cpp: implementation of the StringBuffer class.
//
//////////////////////////////////////////////////////////////////////

/*
 * CESaB Server for Community Engine 5.1
 * 
 * Copyright 1999-2003 webfair AG. All rights reserved.
 *
 * ts
 *
 *
 *
*/



#include "stdafx.h"
#include "StringTokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// very "simple" implementation of 'java' StringTokenizer...
StringTokenizer::StringTokenizer(CString content, char delimiter)
:tokenCount(0)
{
	parseContent(content, delimiter);
}

StringTokenizer::~StringTokenizer()
{

}

void StringTokenizer::parseContent(CString content, char delimiter)
{
	content.TrimLeft();
	content.TrimRight();
	CString *token = new CString();

	for (int i = 0; i < content.GetLength(); i++){
		
		if (content.GetAt(i) == delimiter){
			token->TrimLeft();
			token->TrimRight();
			if ( token->GetLength() > 0){
				m_tokenList.AddTail((LPCTSTR) *token);
			}
			delete token;
			token = new CString();
		} else {
			(*token) = (*token) + content.GetAt(i);
		}
	}

	// append last token...
	token->TrimLeft();
	token->TrimRight();
	if ( token->GetLength() > 0){
		m_tokenList.AddTail((LPCTSTR) *token);
	} 
	delete token;

}

bool StringTokenizer::hasMoreTokens(){
	if (m_tokenList.GetCount() > 0){
		return true;
	}
	return false;
}


CString StringTokenizer::nextToken(){
	if (m_tokenList.GetCount() > 0){
		CString token = m_tokenList.GetHead();
		m_tokenList.RemoveHead(); 
		return token;
	}
	return "";
}

int StringTokenizer::countTokens(){
	return m_tokenList.GetCount();
}