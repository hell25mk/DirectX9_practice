#include "Texture.h"

Texture::Texture(){

	texture = NULL;

}

Texture::Texture(LPCTSTR fileName){

	texture = NULL;
	Load(fileName);

}

Texture::~Texture(){

	D3D_RELEASE(texture);

}

/// <summary>
/// @brief 画像ファイルからテクスチャを作成
/// </summary>
/// <param name="fileName">ファイルの名前</param>
/// <returns></returns>
BOOL Texture::Load(LPCTSTR fileName){

	D3D_RELEASE(texture);

	BOOL b = SUCCEEDED(D3DXCreateTextureFromFile(pD3Ddevice, fileName, &texture));

	if(b){
		D3DSURFACE_DESC desc;

		//最上位のテクスチャ情報を取得
		texture->GetLevelDesc(0, &desc);
		
		textureWidth = (int)desc.Width;
		textureHeight = (int)desc.Height;
	}

	return b;
}

/// <summary>
/// @brief テクスチャのサイズ取得
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Texture::GetTextureSize(int* width, int* height){

	*width = textureWidth;
	*height = textureHeight;

}