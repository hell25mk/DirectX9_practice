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
/// �摜�t�@�C������e�N�X�`�����쐬
/// </summary>
/// <param name="fileName">�t�@�C���̖��O</param>
/// <returns></returns>
BOOL Texture::Load(LPCTSTR fileName){

	ReleaseObject(texture);

	BOOL b = SUCCEEDED(D3DXCreateTextureFromFile(d3dObject.pD3Ddevice, fileName, &texture));

	if(b){
		D3DSURFACE_DESC desc;

		//�ŏ�ʂ̃e�N�X�`�������擾
		texture->GetLevelDesc(0, &desc);
		
		textureHeight = (int)desc.Height;
		textureWidth = (int)desc.Width;
	}

	return b;
}

/// <summary>
/// �e�N�X�`���̃T�C�Y�擾
/// </summary>
/// <param name="width">��</param>
/// <param name="height">�c</param>
void Texture::GetTextureSize(int* height, int* width){

	*height = textureHeight;
	*width = textureWidth;

}