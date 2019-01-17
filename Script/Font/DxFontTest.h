#pragma once

#include "../BaseObject/BaseObject.h"
#include "DxFont.h"

class DxFontTest : public BaseObject{

protected:
	virtual bool Update() override;

private:
	DxFont font;

};

class DxFontTestStart : public BaseObject{

protected:
	virtual void Init() override;

};

class FontMove : public BaseObject{

public:
	void SetStartState(int px, int py, int speed);

protected:
	virtual void Init() override;
	virtual bool Update() override;

private:
	int x, y, m;
	DxFont* pFont;

};