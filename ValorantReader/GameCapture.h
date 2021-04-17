#pragma once
class CGameCapture
{
public:
	CGameCapture();

	bool captureScreen(PBYTE buffer_, int nWidth_, int nHeight_);

private:
	bool GetRowData(HDC hDC_, HBITMAP hBitmap_, PBYTE pImg_);

public:
	TCHAR m_tszGameWindowName[MAX_PATH];
};

