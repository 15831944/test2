// Wave.h: interface for the CWave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVE_H__84356172_6A1A_4C91_9619_BFEBC4CD40C6__INCLUDED_)
#define AFX_WAVE_H__84356172_6A1A_4C91_9619_BFEBC4CD40C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_WAVE_BUFNUM 4
namespace Leaf
{
	namespace Audio
	{
		class CWave  
		{
		public:
			CWave();
			virtual ~CWave();
			
			struct WAVEIN
			{
				HWAVEIN			hWaveIn;
				WAVEHDR			waveHdr[MAX_WAVE_BUFNUM];
				unsigned int	waveSize;
				unsigned int	cacheSize;
				
				//cache pcm data
				char*			pData;
				unsigned int	totalData;
				unsigned int	writePos;
				unsigned int	readPos;
				
				CRITICAL_SECTION	section;
				HANDLE				hDataEvent;
				HANDLE				hDataThread;
				BOOL				bExit;
			};
			public:
				void* WaveIn_Open(int chnnls, int samplesPerSec, int bitsPerSample);
				//	void  WaveIn_Push(WAVEIN *pWave, char *data, int len);
				int   WaveIn_Close(void* hWaveIn);
				int   WaveIn_Reset(void* hWaveIn);
				int   WaveIn_Start(void* hWaveIn);
				int   WaveIn_Stop(void* hWaveIn);
		};
	}
}


#endif // !defined(AFX_WAVE_H__84356172_6A1A_4C91_9619_BFEBC4CD40C6__INCLUDED_)
