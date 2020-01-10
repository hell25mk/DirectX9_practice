#include "FontManager.h"
#include "DxFontTest.h"

void FontManager::Init(){

	//AppendObject(new DxFont(), -1, true, _T("font"));

	/*FontMove* fontMove;

	for(int x = 0; x < 640; x += 5){

		fontMove = new FontMove();
		fontMove->SetDxFont((DxFont*)FindObject(_T("font")));
		fontMove->SetStartState(x, rand() % (480 - 16), rand() % 4 + 1);

		AppendObject(fontMove, 1000 + x, true);

	}*/

}

bool FontManager::Update(){

	dxFont.Draw(_T("文字描画テスト"), 100, 100, Color::GetColor(255, 0, 255));
	dxFont.Draw(_T("ほんとにテストだよ"), 200, 200);

	return true;
}