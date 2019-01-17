#pragma once

#include "../BaseObject/BaseObject.h"

namespace{
	constexpr int Cp_Middlecenter = 0;	//中央値（デフォルト値）
	constexpr int Cp_Left = 1;			//x方向左端
	constexpr int Cp_Center = 2;		//x方向中央
	constexpr int Cp_Right = 4;			//x方向右端
	constexpr int Cp_Top = 8;			//y方向上端
	constexpr int Cp_Middle = 16;		//y方向中央
	constexpr int Cp_Bottom = 32;		//y方向下端
}

class Texture;

class Sprite : public BaseObject{

public:
	Sprite();
	Sprite(Texture* source);
	virtual ~Sprite() = default;
	
	void SetTexture(Texture* source);
	void SetCenterPosition(const BYTE pos);
	BYTE GetCenterPosition() const;

	void SetSpriteSize(const int width, const int height);
	void GetSpriteSize(int* width, int* height);
	
	void SetSpriteRect(const int left, const int top, const int right, const int bottom);

	void SetFrame(const int frame);

	void Draw(const float x, const float y, const int alpha = 255) const;
	void Draw(const float x, const float y, const float r, const int alpha = 255) const;
	void Draw(const float x, const float y, const float ex, const float ey, const int alpha = 255) const;
	void Draw(const float x, const float y, const float ex, const float ey, const float r, const int alpha = 255) const;

private:
	void Reset();

private:
	Texture* texture;
	BYTE cPos;
	RECT drawRect;			// 転送範囲
	float origX;
	float origY;
	int texWidth;
	int sWidth;
	int sHeight;

};

