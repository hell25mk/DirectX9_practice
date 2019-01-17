#pragma once

#include "../BaseObject/BaseObject.h"

namespace{
	
	enum eChara{
		MS_Gothic,

		CharaCode_Num,
	};

	static const _TCHAR* CharaCode[CharaCode_Num] = {
		_T("MS UI Gothic"),
	};

}

class DxFont : public BaseObject{

public:
	DxFont();
	DxFont(int fontSize);
	virtual ~DxFont();

	bool Create(int fontSize);

	void Draw(LPCTSTR text, int x, int y) const;
	void Draw(LPCTSTR text, int count, LPRECT pRect, DWORD format, D3DXCOLOR color) const;

	const LPD3DXFONT GetD3DXFont() const;

private:
	LPD3DXFONT font;

};

