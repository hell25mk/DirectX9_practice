#pragma once

#include "../BaseObject/BaseObject.h"
#include "../Color/Color.h"

namespace{
	
	enum eChara{
		MS_Gothic,

		CharaCode_Num,
	};

	static LPCTSTR CharaCode[CharaCode_Num] = {
		_T("MS UI Gothic"),
	};

}

class DxFont : public BaseObject{

public:
	DxFont();
	DxFont(int size);
	virtual ~DxFont();

	bool Create(int size);

	void Draw(LPCTSTR text, int x, int y, unsigned int color = Color::Color_White) const;
	void Draw(LPCTSTR text, int count, LPRECT pRect, DWORD format, unsigned int color) const;

	const LPD3DXFONT GetD3DXFont() const;

private:
	LPD3DXFONT font;

};

