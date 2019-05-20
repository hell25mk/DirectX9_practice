#pragma once

#include "../BaseObject/BaseObject.h"
#include "DxFont.h"

class DxFontTestStart : public BaseObject{

protected:
	virtual void Init() override;

};

class FontMove : public BaseObject{

public:
	void SetDxFont(DxFont* const font);
	void SetStartState(int px, int py, int speed);

protected:
	virtual bool Update() override;

private:
	int x, y, m;
	DxFont* pFont;

};