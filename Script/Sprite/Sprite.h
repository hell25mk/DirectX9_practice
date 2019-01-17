#pragma once

#include "../BaseObject/BaseObject.h"

namespace{
	constexpr int Cp_Middlecenter = 0;	//�����l�i�f�t�H���g�l�j
	constexpr int Cp_Left = 1;			//x�������[
	constexpr int Cp_Center = 2;		//x��������
	constexpr int Cp_Right = 4;			//x�����E�[
	constexpr int Cp_Top = 8;			//y������[
	constexpr int Cp_Middle = 16;		//y��������
	constexpr int Cp_Bottom = 32;		//y�������[
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
	RECT drawRect;			// �]���͈�
	float origX;
	float origY;
	int texWidth;
	int sWidth;
	int sHeight;

};

