/*==================================================================
*  文件名:CIniFile类实现文件                                       * 
*  作者:Why                                                        *  
*  2017.12.27                                                      * 
====================================================================*/
#include "stdafx.h"
#include "IniFile.h"

CIniFile::CIniFile():m_bFileExist(FALSE)
{
}

CIniFile::~CIniFile()
{
	if(m_bFileExist)
	{
		if(m_stfFile.Open(m_strInIFileName,CFile::modeCreate | CFile::modeWrite) && m_FileContainer.GetSize() > 0)
		{
			CString strParam;
			for(int i = 0; i< m_FileContainer.GetSize();i++)
			{
				strParam = m_FileContainer[i];
				m_stfFile.WriteString(strParam + "\n");
			}
			m_stfFile.Close();
		}
		
	}
	if(m_FileContainer.GetSize() > 0)
	{
		m_FileContainer.RemoveAll();
	}
}
BOOL  CIniFile::Create(const CString & strFileName)
{
	m_bFileExist = FALSE;
	m_strInIFileName = strFileName;
	
	CFileException ex;
	if(!m_stfFile.Open(strFileName,CFile::modeRead|CFile::modeCreate|CFile::modeNoTruncate,&ex))
	{
		TCHAR szError[1024];
		ex.GetErrorMessage(szError, 1024);
		
		return m_bFileExist;
	}
	CString strFileLine;
	while(m_bFileExist = m_stfFile.ReadString(strFileLine))
	{
		if(m_bFileExist == FALSE)
			return m_bFileExist;
		m_FileContainer.Add(strFileLine);
	}
	m_stfFile.Close();
	m_bFileExist = TRUE;
	return m_bFileExist;
}
BOOL CIniFile::GetVar(const CString & strSection,const CString & strVarName,CString &strReturnValue)
{
	if(m_bFileExist == FALSE || m_FileContainer.GetSize() < 0)
		return m_bFileExist;
	
	int iLine = SearchLine(strSection,strVarName);
	if(iLine > 0)
	{
		
		CString	strParam = m_FileContainer[iLine -1];
	    strReturnValue = strParam.Mid(strParam.Find("=") + 1);
		return TRUE;
	}
	return FALSE;
}
BOOL CIniFile::GetVarStr(const CString & strSection,const CString & strVarName,CString &strReturnValue)
{
	return(GetVar(strSection,strVarName,strReturnValue));
}
BOOL CIniFile::GetVarInt(const CString & strSection,const CString & strVarName,int & iValue)
{
	CString  strReturnVar;
	if(GetVar(strSection,strVarName,strReturnVar))
	{
		strReturnVar.TrimLeft();
		int iLen = strReturnVar.GetLength();
		iValue = atoi(strReturnVar.GetBuffer(iLen));
		return TRUE;
	}
	return FALSE;
}
BOOL CIniFile::SetVar(const CString & strSection,const CString & strVarName,const CString & strVar,const int iType)
{
	if(m_bFileExist == FALSE )
		return m_bFileExist;
	if(m_FileContainer.GetSize() == 0)
	{
		m_FileContainer.Add("[" + strSection + "]");
		m_FileContainer.Add(strVarName + "=" + strVar);
		return TRUE;
	}

	int i = 0;
	int iFileLines = m_FileContainer.GetSize();
	
	while(i< iFileLines)
	{
	
		CString	strValue = m_FileContainer.GetAt(i++);
		strValue.TrimLeft();
		if((strValue.Find("[") ==0) && (strValue.Find(strSection) >=0))
		{	
			while(i < iFileLines)
			{
			
				CString strSectionList = m_FileContainer[i++];
				strSectionList.TrimLeft();
				if(strSectionList.Find("//") ==0)//找到注释行
					continue;
				
				if(strSectionList.Find(strVarName)==0)//找到
				{
				
					CString strParam = strVarName + "=" + strVar;
					
					//m_FileContainer.SetAt(i-1,strParam);
					m_FileContainer[i-1] = strParam;

					return TRUE;
				}
				if(strSectionList.Find("[",0) == 0)//在原来文件的SECTION中,没有相应的变量需要添加而且,这种情况下,下边还有别的section
				{
					//处理流程是这样的,首先把当前的数值依次向后移动,然后在当前位置加入新出现的数值
					if(iType !=0)
						return FALSE;
					CString strParam;
					m_FileContainer.Add(strParam);
					int iPre = m_FileContainer.GetSize()-1;
					while(iPre >= i)
					{
						CString strBehind = m_FileContainer[iPre -1];
						m_FileContainer[iPre] = strBehind;
						iPre --;

					}//*/
					strParam = strVarName + "=" + strVar;
					m_FileContainer.SetAt(i-1,strParam);
					return TRUE;
				}
				if(i == iFileLines && iType == 0)
				{
					m_FileContainer.Add(strVarName + "=" + strVar);
					return TRUE;
				}
			}
		}
	}
	if(iType == 0)
	{
		m_FileContainer.Add("[" + strSection + "]");
		m_FileContainer.Add(strVarName + "=" + strVar);
	}
	
	return TRUE;

}
BOOL CIniFile::SetVarStr(const CString & strSection,const CString & strVarName,const CString & strValue,const int iType)
{
	return SetVar(strSection,strVarName,strValue,iType);
}
BOOL CIniFile::SetVarInt(const CString & strSection,const CString & strVarName,const int & iValue,const int iType)
{
	CString strVar;
	strVar.Format("%d",iValue);
	return (SetVar(strSection,strVarName,strVar,iType));
}
int CIniFile::SearchLine(const CString & strSection,const CString & strVarName)
{

	if(m_FileContainer.GetSize() > 0)
	{
			
		int i = 0;
		int iFileLines = m_FileContainer.GetSize();
		while(i< iFileLines)
		{
			
			CString strValue = m_FileContainer[i++];
			strValue.TrimLeft();
			if(strValue.Find("[") ==0 && strValue.Find(strSection,1)>=0)
			{	
				while(i < iFileLines)
				{
				
					CString strSectionList = m_FileContainer[i++];
					strSectionList.TrimLeft();
					if(strSectionList.Find("//") ==0)//找到注释行
						continue;
					if(strSectionList.Find(strVarName)==0)//找到
					{
						return i;
					}
					if(strSectionList.Find("[",0) == 0)//另外一个段落出现,寻找失败
					{
						return -2;
					}
					
				}
			}
		}
	}
	return -1;
}