#include "pch.h"
#include "ValorantReader.h"

CValorantReader::CValorantReader()
	: m_pImgBuffer (nullptr)
	, m_pGameCapturer (nullptr)
	, m_pEngine (nullptr)
	, m_pEventBuilder (nullptr)
{
}

CValorantReader::~CValorantReader()
{
	ExitInstance();
}

BOOL CValorantReader::InitInstance()
{
	m_pImgBuffer = new BYTE[1920 * 1080 * 5 * 3];
	m_pGameCapturer = new CGameCapture();
	m_pEngine = new CParserEngine();
	m_pEventBuilder = new CEventBuilder();

	Initialize();

	return TRUE;
}

BOOL CValorantReader::Initialize()
{
	ZeroMemory(m_pImgBuffer, 1920 * 1080 * 5 * 3);
	m_aryTimelineData.clear();

	return TRUE;
}

BOOL CValorantReader::ExitInstance()
{
	if (m_pImgBuffer)
		delete m_pImgBuffer;

	if (m_pGameCapturer)
		delete m_pGameCapturer;

	if (m_pEngine)
		delete m_pEngine;

	if (m_pEventBuilder)
		delete m_pEventBuilder;

	return TRUE;
}

int CValorantReader::Run(LPVOID lParam)
{
	while (true)
	{
		((CValorantReader*)lParam)->pipeline();
		Sleep(20);
	}

	return 0;
}

void SaveBitmap(LPCSTR fileName, int nWidth, int nHeight, PBYTE pImg)
{
	BITMAPFILEHEADER    BmHdr;
	BmHdr.bfType = 0x4d42;   // 'BM' WINDOWS_BITMAP_SIGNATURE
	BmHdr.bfSize = ((3 * nWidth + 3) & ~3) * nHeight + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	BmHdr.bfReserved1 = BmHdr.bfReserved2 = 0;
	BmHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	BITMAPINFOHEADER bmHeader;
	ZeroMemory(&bmHeader, sizeof(BITMAPINFOHEADER));
	bmHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmHeader.biWidth = nWidth;
	bmHeader.biHeight = nHeight;
	bmHeader.biPlanes = 1;
	bmHeader.biBitCount = 24;

	FILE* fp;
	if (!fopen_s(&fp, fileName, "wb"))
	{
		fwrite(&BmHdr, sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&bmHeader, sizeof(BITMAPINFOHEADER), 1, fp);
		for (int i = nHeight - 1; i >= 0; i--)
		{
			fwrite(pImg + i * 3 * nWidth, 1, 3 * nWidth, fp);
			for (int j = 0; j < ((3 * nWidth + 3) & ~3) - 3 * nWidth; j++)
			{
				char z = 0;
				fwrite(&z, 1, 1, fp);
			}
		}
		fclose(fp);
	}

}


BOOL CValorantReader::pipeline()
{
	int nScreenWidth = 0, nScreenHeight = 0;

	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (m_pImgBuffer == nullptr)
	{
		return FALSE;
	}
	m_pGameCapturer->captureScreen(m_pImgBuffer, nScreenWidth, nScreenHeight);
	CTimelineData currSlice = m_pEngine->run(m_pImgBuffer, nScreenWidth, nScreenHeight);
	//m_currSlice = m_pEventBuilder->build(&currSlice, m_aryTimelineData);

	//SYSTEMTIME lt;
	//GetLocalTime(&lt);
	//char fn[MAX_PATH], strTime[64];

	//sprintf_s(strTime, sizeof(strTime), "\n\n%02d%02d_%02d%02d_%02d%03d",
	//	lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, lt.wMilliseconds);

	//sprintf_s(fn, sizeof(fn), "Out\\Capture_%s.bmp", strTime + 2);
	//SaveBitmap(fn, nScreenWidth, nScreenHeight, m_pImgBuffer);

	return FALSE;
}

BOOL CValorantReader::exportCurrent(CTimelineData& out)
{
	return FALSE;
}

BOOL CValorantReader::exportAll(std::vector<CTimelineData>& outArray)
{
	return FALSE;
}
