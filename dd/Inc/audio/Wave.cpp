// Wave.cpp: implementation of the CWave class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wave.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace Leaf::Audio;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DWORD WINAPI WaveInData(LPVOID lpvoid);
CWave::CWave()
{

}

CWave::~CWave()
{

}

void* CWave::WaveIn_Open(int chnnls, int samplesPerSec, int bitsPerSample)
{
	WAVEFORMATEX	waveFormat;
	WAVEIN *pWave = NULL;
	MMRESULT mr	  = NULL;
	int i =0;


	pWave = (WAVEIN*)malloc(sizeof(WAVEIN));
	if (NULL == pWave)
	{
		return NULL;
	}
	memset(pWave, 0, sizeof(WAVEIN));

	waveFormat.wFormatTag		= WAVE_FORMAT_PCM;
	waveFormat.nChannels		= chnnls;
	waveFormat.nSamplesPerSec	= samplesPerSec;
	waveFormat.wBitsPerSample	= bitsPerSample;
	waveFormat.nAvgBytesPerSec	= waveFormat.nChannels*waveFormat.nSamplesPerSec*waveFormat.wBitsPerSample/8;
	waveFormat.nBlockAlign		= waveFormat.nChannels*waveFormat.wBitsPerSample/8;
	waveFormat.cbSize			= sizeof(waveFormat);

	pWave->cacheSize = waveFormat.nAvgBytesPerSec*3;
	pWave->waveSize  = pWave->cacheSize/4;
	pWave->hDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	/* ��ʼ����Ƶ�����豸,�õ���Ƶ�����豸��� */
	mr=waveInOpen(&pWave->hWaveIn,WAVE_MAPPER,&waveFormat,(DWORD)pWave->hDataEvent,(DWORD)pWave,CALLBACK_EVENT);
	if (mr!=MMSYSERR_NOERROR)
	{
		return NULL;
	}

	for (i=0;i<MAX_WAVE_BUFNUM;i++)
	{
		pWave->waveHdr[i].lpData=(LPSTR)malloc(pWave->waveSize);       /* ָ�����������ݻ�������ָ�� */ 
		if (pWave->waveHdr[i].lpData==NULL)
		{
			break;
		}
		pWave->waveHdr[i].dwBufferLength = pWave->waveSize;            /* ���ݻ������Ĵ�С */ 
		pWave->waveHdr[i].dwBytesRecorded = 0;                         /* ¼��ʱָ���������е������� */
		pWave->waveHdr[i].dwUser		  = 0;                         /* �û����� */
		pWave->waveHdr[i].dwFlags         = 0;                         /* �ṩ��������Ϣ�ı�־ */ 
		pWave->waveHdr[i].dwLoops         = 0;                         /* ѭ�����ŵĴ��� */ 
		pWave->waveHdr[i].lpNext		  = NULL;                      /* ���� */ 
		pWave->waveHdr[i].reserved		  = 0;                         /* ���� */ 

		mr=waveInPrepareHeader(pWave->hWaveIn,&pWave->waveHdr[i],sizeof(WAVEHDR));  /* ׼��������Ƶ�Ļ��� */  
		if (mr != MMSYSERR_NOERROR)
		{
			break;
		}
		mr = waveInAddBuffer(pWave->hWaveIn, &pWave->waveHdr[i], sizeof(WAVEHDR));   /* �����ڴ��  */
		if (mr != MMSYSERR_NOERROR)
		{
			break;
		}
	}

	if (i != MAX_WAVE_BUFNUM)
	{
		return NULL;
	}

	pWave->pData = (char*)malloc(pWave->cacheSize);
	if (pWave->pData == NULL)
	{
		return NULL;
	}

	InitializeCriticalSection(&pWave->section);

	mr = waveInStart(pWave->hWaveIn);  /* ��ʼ¼�� */
	if (mr != MMSYSERR_NOERROR)
	{
		return NULL;
	}

	pWave->bExit = FALSE;
//	pWave->hDataThread = CreateThread(NULL, 0, WaveInData, pWave, 0, 0);
	return (void*)pWave;
}

int CWave::WaveIn_Close(void* hWaveIn)
{
	WAVEIN* pWave = (WAVEIN*)hWaveIn;

	if (pWave == NULL)
	{
		return 0;
	}

	if (pWave->hDataThread != NULL)
	{
		pWave->bExit=TRUE;
		SetEvent(pWave->hDataEvent);
		WaitForSingleObject(pWave->hDataThread,INFINITE);
		CloseHandle(pWave->hDataThread);
		pWave->hDataThread=NULL;
	}

	if (pWave->hWaveIn != NULL)
	{
		waveInReset(pWave->hWaveIn);
		waveInStop(pWave->hWaveIn);

		for (int i=0; i<MAX_WAVE_BUFNUM; i++)
		{
			if (pWave->waveHdr[i].lpData != NULL)
			{
				waveInUnprepareHeader(pWave->hWaveIn, &pWave->waveHdr[i], sizeof(WAVEHDR));
				free(pWave->waveHdr[i].lpData);
				pWave->waveHdr[i].lpData = NULL;
			}
		}

		waveInClose(pWave->hWaveIn);

		if (pWave->pData != NULL)
		{
			free(pWave->pData);
			pWave->pData = NULL;
		}

		DeleteCriticalSection(&pWave->section);

		if (pWave->hDataEvent != NULL)
		{
			CloseHandle(pWave->hDataEvent);
			pWave->hDataEvent = NULL;
		}

		if (pWave)
		{
			free(pWave);
			pWave = NULL;
		}

	}

	return 0;
}


int CWave::WaveIn_Reset(void* hWaveIn)
{
	WAVEIN* pWave = (WAVEIN*)hWaveIn;
	if (pWave != NULL)
	{
		if (pWave->hWaveIn)
		{
			waveInReset(pWave->hWaveIn);
		}

		EnterCriticalSection(&pWave->section);
		pWave->totalData = 0;
		pWave->writePos  = 0;
		pWave->readPos   = 0;
		LeaveCriticalSection(&pWave->section);
	}
	return 0;
}

int CWave::WaveIn_Start(void* hWaveIn)
{
	WAVEIN* pWave = (WAVEIN*)hWaveIn;
	if (pWave != NULL)
	{
		if (pWave->hWaveIn)
		{
			waveInStart(pWave->hWaveIn);
		}
	}
	return 0;
}

int CWave::WaveIn_Stop(void* hWaveIn)
{
    WAVEIN* pWave = (WAVEIN*)hWaveIn;
	if (pWave != NULL)
	{
		if (pWave->hWaveIn)
		{
			waveInStop(pWave->hWaveIn);
		}
	}
	return 0;
}

/*
void CWave::WaveIn_Push(WAVEIN *pWave, char *data, int len);
{
}


DWORD WINAPI WaveInData(LPVOID lpvoid)
{
	WAVEIN *pWaveIn = (WAVEIN*)lpvoid;
	if (pWaveIn == NULL)
	{
		return 0;
	}

	DWORD ret = 0;
	do 
	{
		WaitForSingleObject(pWaveIn->hDataEvent, INFINITE);
		if (pWaveIn->bExit)
		{
			break;
		}

		for (int i=0; i<MAX_WAVE_BUFNUM; i++)
		{
			if (pWaveIn->waveHdr[i].dwBytesRecorded > 0)
			{
			}
		}
	} while (pWaveIn->bExit);
}*/