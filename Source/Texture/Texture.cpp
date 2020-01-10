#include "Texture.h"

Texture::Texture():
	texture(NULL),
	textureHeight(0),
	textureWidth(0) {

}

Texture::Texture(LPCTSTR fileName):Texture(){

	Load(fileName);

}

Texture::~Texture(){

	ReleaseObject(texture);

}

/// <summary>
/// 画像ファイルからテクスチャを作成
/// </summary>
/// <param name="fileName">ファイルの名前</param>
/// <returns></returns>
BOOL Texture::Load(LPCTSTR fileName){

	ReleaseObject(texture);

	BOOL b = SUCCEEDED(D3DXCreateTextureFromFile(d3dObject.pD3Ddevice, fileName, &texture));

	if(b){
		D3DSURFACE_DESC desc;

		//最上位のテクスチャ情報を取得
		texture->GetLevelDesc(0, &desc);
		
		textureHeight = (int)desc.Height;
		textureWidth = (int)desc.Width;
	}

	return b;
}

/// <summary>
/// テクスチャのサイズ取得
/// </summary>
/// <param name="width">横</param>
/// <param name="height">縦</param>
void Texture::GetTextureSize(int* height, int* width){

	*height = textureHeight;
	*width = textureWidth;

}