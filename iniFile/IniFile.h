/*==================================================================
*  �ļ���:CIniFile�ඨ���ļ�                                       *  
*  ��Ҫ����:���Զ�ȡ.�޸ı�����ֵ,���������µ���,�µı���          * 
*  �޸�����:2005-08-15                                             * 
*  ����:                                                           * 
*                       *                                          * 
===================================================================*/
#ifndef _CINIFILE_H_
#define _CINIFILE_H_
#include <afxtempl.h>
//�û��ӿ�˵��:�ڳ�Ա����SetVarStr��SetVarInt������,��iType������,������û��ƶ��Ĳ�����ini�ļ��в�����,
//���д���µı���.��iType��������,������û��ƶ��Ĳ�����ini�ļ��в�����,�Ͳ�д���µı���������ֱ�ӷ���FALSE;
class CIniFile
{
public:
	CIniFile();
	virtual ~CIniFile();
private:
	CIniFile(const CIniFile &);
	CIniFile & operator = (const CIniFile &);
public:
	//��������
	BOOL Create(const CString &strFileName);
	//�õ�������������ֵ
	BOOL GetVarInt(const CString &,const CString & ,int &);
	//�õ������ַ�������ֵ
	BOOL GetVarStr(const CString &,const CString & ,CString & );
	//�������ñ�����������ֵ
	BOOL SetVarInt(const CString &,const CString & ,const int &,const int iType = 1);
	//�������ñ����ַ�������ֵ
	BOOL SetVarStr(const CString &,const CString &, const CString &,const int iType = 1);
	
private:
	BOOL GetVar(const CString &,const CString &,CString &);
	BOOL SetVar(const CString &,const CString &,const CString &,const int iType = 1);
	int  SearchLine(const CString &,const CString &);

private:

	CArray <CString,CString> m_FileContainer;
	BOOL  m_bFileExist;
	CStdioFile m_stfFile;
	CString m_strInIFileName;
	
};

#endif