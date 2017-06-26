#ifndef __PUB_CLASS_H__
#define __PUB_CLASS_H__

#define		MAX_OUTPUTS_CTRL			64
#define		OUTPUT_INTERVAL				4

#define		WM_SWITCHMULTI_CTRL			WM_USER + 0x0101

#include <io.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>					//stdlib
#include <cctype>					//ctype

#include <vector>
#include <list>
#include <map>
#include <string> 
#include <afxconv.h>					//USES_CONVERSION: W2A

#include "internal.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include "winsock2.h"
#pragma comment(lib,"Ws2_32.lib") 

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

//Linker->Advanced->wWinMainCRTStartup
// #include	"../inc/lib/ddraw.h"
// #pragma comment(lib,"../inc/lib/ddraw.lib")
// #pragma comment(lib,"../inc/lib/dxguid.lib")

#include "MemDC.h"
#include "SaveDC.h"
#include "Picture.h"

typedef enum tagMessageType{
	M_EMPTYTYPE					= 0,
	M_FULLSCREEN_CTRL			= 1,
	M_MULTISCREEN_CTRL			= 2
}UKH_MESSAGE_TYPE, *PUKH_MESSAGE_TYPE;

#endif