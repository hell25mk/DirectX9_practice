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
		pD3Ddevice,						//取得元になるデバイス
		fontSize,						//幅
		NULL,							//高さ
		FW_DONTCARE,					//太さ
		NULL,							//ミップマップレベル
		false,							//斜体
		ANSI_CHARSET,					//文字セット
		OUT_DEFAULT_PRECIS,				//出力精度
		DEFAULT_QUALITY,				//出力品質
		DEFAULT_PITCH | FF_DONTCARE,	//フォントピッチ
		CharaCode[fontType],					//フォント名
		&font							//格納先
	);

	return (result == 0) ? false : true;
}

const LPD3DXFONT DxFont::GetD3DXFont() const{

	return font;
}

void DxFont::Draw(LPCTSTR text, int x, int y) const{

	const int All_CharaCount = -1;

	//最低限の指定
	//[x,y]の位置を左上に描画
	RECT rect = { x, y, x, y };
	Draw(text, All_CharaCount, &rect, DT_NOCLIP | DT_SINGLELINE, 0xFFFFFFFF);

}

void DxFont::Draw(LPCTSTR text, int count, LPRECT pRect, DWORD format, D3DXCOLOR color) const{

	if(!font){
		return;
	}

	//2Dの描画開始宣言
	pSprite->Begin(NULL);

	D3DXMATRIX mtrx;

	D3DXMatrixTranslation(&mtrx, 0.0f, 0.0f, 0.0f);
	pSprite->SetTransform(&mtrx);

	font->DrawText(
		pSprite,			//描画に用いるスプライトオブジェクト
		text,				//表示する文字列
		count,				//表示する文字数（-1で文字列すべて）
		pRect,				//文字列を描画する範囲
		format,				//文字列描画設定
		color				//文字列描画色
	);

	//描画終了宣言
	pSprite->End();

}