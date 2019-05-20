#include "DxFont.h"

DxFont::DxFont():font(nullptr){

	Create(16);

}

DxFont::DxFont(int size):font(nullptr){

	Create(size);

}

DxFont::~DxFont(){

	ReleaseD3DObject(font);

}

bool DxFont::Create(int size){

	ReleaseD3DObject(font);

	int fontType = eChara::MS_Gothic;

	if(FAILED(D3DXCreateFont(
		d3dObject.pD3Ddevice,			//�擾���ɂȂ�f�o�C�X
		size,							//��
		NULL,							//����
		FW_DONTCARE,					//����
		NULL,							//�~�b�v�}�b�v���x��
		false,							//�Α�(�C�^���b�N���ǂ���)
		ANSI_CHARSET,					//�����Z�b�g
		OUT_DEFAULT_PRECIS,				//�o�͐��x
		DEFAULT_QUALITY,				//�o�͕i��
		DEFAULT_PITCH | FF_DONTCARE,	//�t�H���g�s�b�`
		CharaCode[fontType],			//�t�H���g��
		&font
		))){
		MessageBox(NULL, _T("�t�H���g�̍쐬���s"), _T("�G���["), MB_OK);
		return false;
	}

	return true;
}

const LPD3DXFONT DxFont::GetD3DXFont() const{

	return font;
}

/// <summary>
/// @brief �����`��̏������s��
/// </summary>
/// <param name="text">�\�����镶����</param>
/// <param name="x">x���W</param>
/// <param name="y">y���W</param>
/// <param name="color">�����F(�f�t�H���g�l=0xFFFFFFFF)</param>
void DxFont::Draw(LPCTSTR text, int x, int y, unsigned int color) const{

	const int All_CharaCount = -1;

	//�Œ���̎w��
	//[x,y]�̈ʒu������ɕ`��
	RECT rect = { x, y, x, y };
	Draw(text, All_CharaCount, &rect, DT_NOCLIP | DT_SINGLELINE, color);

}

/// <summary>
/// @brief ���������Ƃɕ����`����s��
/// </summary>
/// <param name="text"></param>
/// <param name="count"></param>
/// <param name="pRect"></param>
/// <param name="format"></param>
/// <param name="color"></param>
void DxFont::Draw(LPCTSTR text, int count, LPRECT pRect, DWORD format, unsigned int color) const{

	if(!font){
		return;
	}

	//2D�̕`��J�n�錾
	d3dObject.pSprite->Begin(NULL);

	D3DXMATRIX mtrx;

	D3DXMatrixTranslation(&mtrx, 0.0f, 0.0f, 0.0f);
	d3dObject.pSprite->SetTransform(&mtrx);

	font->DrawText(
		d3dObject.pSprite,		//�`��ɗp����X�v���C�g�I�u�W�F�N�g
		text,					//�\�����镶����
		count,					//�\�����镶�����i-1�ŕ����񂷂ׂāj
		pRect,					//�������`�悷��͈�
		format,					//������`��ݒ�
		color					//������`��F
	);

	//�`��I���錾
	d3dObject.pSprite->End();

}