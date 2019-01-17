#pragma once

#include "../BaseObject/BaseObject.h"

class Texture : public BaseObject{

public:
	Texture();
	Texture(LPCTSTR fileName);
	virtual ~Texture() override;
	BOOL Load(LPCTSTR fileName);
	void GetTextureSize(int* width, int* height);
	inline const LPDIRECT3DTEXTURE9 GetTexture(){
		return texture;
	}

private:
	LPDIRECT3DTEXTURE9 texture;		//テクスチャを格納するインタフェイス
	int textureWidth;
	int textureHeight;

};

