#include "StdAfx.h"
#include "VitualMem.h"


CVitualMem::CVitualMem(void)
:m_nMaxMCount(1024)
,m_nCurCount(0)
{
	m_pMemSave = new int [1024][2];
}

CVitualMem::~CVitualMem(void)
{
	Free();
}

void CVitualMem::Free()
{
	if (!VirtualFree(m_Head, m_dwVirtualMaxSize, MEM_RELEASE))
	{
		DEBUGMSG("Free mem failed", GetLastError());
	}
	
}

void CVitualMem::Init( DWORD dwMaxSize )
{
	m_dwVirtualMaxSize = dwMaxSize;
	m_Head = VirtualAlloc(NULL, dwMaxSize, MEM_TOP_DOWN | MEM_RESERVE, PAGE_READWRITE);
	if (m_Head==NULL)
	{
		DEBUGMSG("Alloc vir mem failed", GetLastError());
	}
}

PVOID CVitualMem::Push( IN char* pData, IN int nSzie, OUT DWORD& dwRealSize )
{
	PVOID pVoid = NULL;
	__try
	{

	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{

	}

	if (m_nCurCount+1>=m_nMaxMCount)
	{
		DEBUGMSG("Mem count no left", 0);
	}
	m_pMemSave[m_nCurCount][0] = (int)pVoid;
	m_pMemSave[m_nCurCount++][1] = dwRealSize;
	return pVoid;
}

void CVitualMem::SetPMemSize( IN DWORD dwMaxPMSize )
{
	m_dwMaxPhysicalSize = dwMaxPMSize;
}

int CVitualMem::GetPMemSize()
{
	return m_dwMaxPhysicalSize;
}