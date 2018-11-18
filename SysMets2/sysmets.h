#ifndef __SYSMETS_H__
#define __SYSMETS_H__

#include <Windows.h>

#define NUMLINES (sizeof sysmetrics / sizeof sysmetrics[0])

struct
{
	int iIndex;
	TCHAR *szLabel;
	TCHAR *szDesc;
}
sysmetrics[] =
{
	SM_CXSCREEN, TEXT("SM_CXSCREEN"), TEXT("Screen width in pixels"),
	SM_CYSCREEN, TEXT("SM_CYSCREEN"), TEXT("Screen height in pixels"),
	SM_CXVSCROLL, TEXT("SM_CXVSCROLL"), TEXT("Vertical scroll width"),
	SM_CYHSCROLL, TEXT("SM_CYHSCROLL"), TEXT("Horizontal scroll height")
};

#endif