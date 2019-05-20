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
		d3dObject.pD3Ddevice,			//取得元になるデバイス
		size,							//幅
		NULL,							//高さ
		FW_DONTCARE,					//太さ
		NULL,							//ミップマップレベル
		false,							//斜体(イタリックかどうか)
		ANSI_CHARSET,					//文字セット
		OUT_DEFAULT_PRECIS,				//出力精度
		DEFAULT_QUALITY,				//出力品質
		DEFAULT_PITCH | FF_DONTCARE,	//フォントピッチ
		CharaCode[fontType],			//フォント名
		&font
		))){
		MessageBox(NULL, _T("フォントの作成失敗"), _T("エラー"), MB_OK);
		return false;
	}

	return true;
}

const LPD3DXFONT DxFont::GetD3DXFont() const{

	return font;
}

/// <summary>
/// @brief 文字描画の準備を行う
/// </summary>
/// <param name="text">表示する文字列</param>
/// <param name="x">x座標</param>
/// <param name="y">y座標</param>
/// <param name="color">文字色(デフォルト値=0xFFFFFFFF)</param>
void DxFont::Draw(LPCTSTR text, int x, int y, unsigned int color) const{

	const int All_CharaCount = -1;

	//最低限の指定
	//[x,y]の位置を左上に描画
	RECT rect = { x, y, x, y };
	Draw(text, All_CharaCount, &rect, DT_NOCLIP | DT_SINGLELINE, color);

}

/// <summary>
/// @brief 引数をもとに文字描画を行う
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

	//2Dの描画開始宣言
	d3dObject.pSprite->Begin(NULL);

	D3DXMATRIX mtrx;

	D3DXMatrixTranslation(&mtrx, 0.0f, 0.0f, 0.0f);
	d3dObject.pSprite->SetTransform(&mtrx);

	font->DrawText(
		d3dObject.pSprite,		//描画に用いるスプライトオブジェクト
		text,					//表示する文字列
		count,					//表示する文字数（-1で文字列すべて）
		pRect,					//文字列を描画する範囲
		format,					//文字列描画設定
		color					//文字列描画色
	);

	//描画終了宣言
	d3dObject.pSprite->End();

}