#include "pch.h"
#include "GameCapture.h"
#include "Common.h"

CGameCapture::CGameCapture()
	: m_tszGameWindowName(_T("VALORANT  "))
{
}

CGameCapture::~CGameCapture()
{
}

bool CGameCapture::captureScreen(PBYTE buffer_, int nWidth_, int nHeight_)
{
	bool ret = false;
	if (buffer_ == nullptr)
	{
		return ret;
	}
	
	HDC hDC = GetDC(GetDesktopWindow());
	HDC hMemDC = CreateCompatibleDC(hDC);
	HWND hGameWnd = FindWindow(nullptr, m_tszGameWindowName);
	if (hGameWnd)
	{
		RECT rt;
		int nWidth = 0, nHeight = 0;
		
		GetWindowRect(hGameWnd, &rt);
		nWidth = rt.right - rt.left;
		nHeight = rt.bottom - rt.top;

		if (nWidth == nWidth_ && nHeight == nHeight_)
		{
			HBITMAP hBitmap = CreateCompatibleBitmap(hDC, nWidth, nHeight);
			if (hBitmap)
			{
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
				BitBlt(hMemDC, 0, 0, nWidth, nHeight, hDC, rt.left, rt.top, SRCCOPY);
				ret = GetRowData(hMemDC, hBitmap, buffer_);
				SelectObject(hMemDC, hOldBitmap);
				DeleteObject(hBitmap);
			}
		}
	}

	DeleteDC(hMemDC);
	ReleaseDC(nullptr, hDC);

	return ret;
}

bool CGameCapture::GetRowData(HDC hDC_, HBITMAP hBitmap_, PBYTE pImg_)
{
	BITMAPINFO BitInfo;

	ZeroMemory(&BitInfo, sizeof(BITMAPINFO));

	BitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BitInfo.bmiHeader.biBitCount = 0;

	if (!GetDIBits(hDC_, hBitmap_, 0, 0, nullptr, &BitInfo, DIB_RGB_COLORS))
	{
		return FALSE;
	}

	BitInfo.bmiHeader.biCompression = BI_RGB;
	PBYTE pData = new BYTE[BitInfo.bmiHeader.biSizeImage + 5];
	if (!GetDIBits(hDC_, hBitmap_, 0, BitInfo.bmiHeader.biHeight, pData, &BitInfo, DIB_RGB_COLORS))
	{
		delete[] pData;
		return FALSE;
	}

	// from pData to m_pImg
	PBYTE p = pImg_, pp;
	for (int j = BitInfo.bmiHeader.biHeight - 1; j >= 0; j--)
	{
		pp = pData + j * BitInfo.bmiHeader.biWidth * 4;

		for (int i = 0; i < BitInfo.bmiHeader.biWidth; i++)
		{
			*p++ = *pp++;	//Blue
			*p++ = *pp++;	//Green
			*p++ = *pp++;	//Red
			pp++;/*Alpha*/
		}
	}

	delete[] pData;

	return true;
}
