#pragma once

#include "../BaseObject/BaseObject.h"
#include "DxFont.h"

class FontManager : public BaseObject {

public:
	FontManager() = default;
	virtual ~FontManager() = default;
	virtual void Init();
	virtual bool Update();

private:
	DxFont dxFont;

};

