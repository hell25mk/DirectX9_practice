#pragma once

#include "../BaseManager/BaseManager.h"
#include "DxFont.h"

class FontManager : public BaseManager{

public:
	FontManager() = default;
	virtual ~FontManager() = default;
	virtual void Init();
	virtual bool Update();
	virtual void Draw();

private:
	DxFont dxFont;

};

