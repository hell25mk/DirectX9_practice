#include "DxFontTest.h"

void FontMove::SetStartState(int px, int py, int speed){

	x = px;
	y = py;
	m = speed;

}

void FontMove::Init(){

	pFont = (DxFont*)FindObject("font");

}

bool FontMove::Update(){

	if(pFont){

		if(y < 0 || y > 480 - 16){
			m = -m;
		}

		y += m;

		pFont->Draw(_T("FJT"), x, y);

	}

	return true;
}