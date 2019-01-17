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
/// @brief �摜�t�@�C������e�N�X�`�����쐬
/// </summary>
/// <param name="fileName">�t�@�C���̖��O</param>
/// <returns></returns>
BOOL Texture::Load(LPCTSTR fileName){

	D3D_RELEASE(texture);

	BOOL b = SUCCEEDED(D3DXCreateTextureFromFile(pD3Ddevice, fileName, &texture));

	if(b){
		D3DSURFACE_DESC desc;

		//�ŏ�ʂ̃e�N�X�`�������擾
		texture->GetLevelDesc(0, &desc);
		
		textureWidth = (int)desc.Width;
		textureHeight = (int)desc.Height;
	}

	return b;
}

/// <summary>
/// @brief �e�N�X�`���̃T�C�Y�擾
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Texture::GetTextureSize(int* width, int* height){

	*width = textureWidth;
	*height = textureHeight;

}