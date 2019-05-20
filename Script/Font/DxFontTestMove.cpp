#include "DxFontTest.h"
#include <random>
#include <time.h>

void FontMove::SetStartState(int px, int py, int speed){

	x = px;
	y = py;
	m = speed;

}

void FontMove::SetDxFont(DxFont* const font){

	pFont = font;

}

bool FontMove::Update(){

	if(!pFont){

		return false;
	}

	if(y < 0 || y > 480 - 16){
		m = -m;
	}

	y += m;

	pFont->Draw(_T("FJT"), x, y);

	return true;
}