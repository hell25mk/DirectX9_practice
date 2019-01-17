#include "DxFont.h"

DxFont::DxFont():font(nullptr){

	Create(16);

}


DxFont::DxFont(int fontSize):font(nullptr){

	Create(fontSize);

}

DxFont::~DxFont(){

	D3D_RELEASE(font);

}

bool DxFont::Create(int fontSize){

	D3D_RELEASE(font);

	int fontType = eChara::MS_Gothic;

	int result = D3DXCreateFont(
		pD3Ddevice,						//�擾���ɂȂ�f�o�C�X
		fontSize,						//��
		NULL,							//����
		FW_DONTCARE,					//����
		NULL,							//�~�b�v�}�b�v���x��
		false,							//�Α�
		ANSI_CHARSET,					//�����Z�b�g
		OUT_DEFAULT_PRECIS,				//�o�͐��x
		DEFAULT_QUALITY,				//�o�͕i��
		DEFAULT_PITCH | FF_DONTCARE,	//�t�H���g�s�b�`
		CharaCode[fontType],					//�t�H���g��
		&font							//�i�[��
	);

	return (result == 0) ? false : true;
}

const LPD3DXFONT DxFont::GetD3DXFont() const{

	return font;
}

void DxFont::Draw(LPCTSTR text, int x, int y) const{

	const int All_CharaCount = -1;

	//�Œ���̎w��
	//[x,y]�̈ʒu������ɕ`��
	RECT rect = { x, y, x, y };
	Draw(text, All_CharaCount, &rect, DT_NOCLIP | DT_SINGLELINE, 0xFFFFFFFF);

}

void DxFont::Draw(LPCTSTR text, int count, LPRECT pRect, DWORD format, D3DXCOLOR color) const{

	if(!font){
		return;
	}

	//2D�̕`��J�n�錾
	pSprite->Begin(NULL);

	D3DXMATRIX mtrx;

	D3DXMatrixTranslation(&mtrx, 0.0f, 0.0f, 0.0f);
	pSprite->SetTransform(&mtrx);

	font->DrawText(
		pSprite,			//�`��ɗp����X�v���C�g�I�u�W�F�N�g
		text,				//�\�����镶����
		count,				//�\�����镶�����i-1�ŕ����񂷂ׂāj
		pRect,				//�������`�悷��͈�
		format,				//������`��ݒ�
		color				//������`��F
	);

	//�`��I���錾
	pSprite->End();

}