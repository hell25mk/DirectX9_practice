#include "Runner.h"
#include "../../Input/DxInput.h"

Runner::Runner() 
	:dxInput(),x(320.0f),y(240.0f),moveSpeed(3.0f){

}

void Runner::Init(){

	texture.Load(_T("Data/Image/anime.png"));
	sprite.SetTexture(&texture);
	sprite.SetSpriteSize(128, 128);
	dxInput = (DxInput*)FindObject("DxInput");
	dxSound.Load(_T("Data/Sound/missile.wav"));

}

bool Runner::Update() {

	static int frame = 0, count = 0;

	if (++count >= 12) {
		count = 0;
		if (++frame >= 8) {
			frame = 0;
		}
		sprite.SetFrame(frame);
	}

	if (dxInput->IsKeyDown(DIK_LEFT)) {
		x -= moveSpeed;
	}
	if (dxInput->IsKeyDown(DIK_RIGHT)) {
		x += moveSpeed;
	}
	if (dxInput->IsKeyDown(DIK_UP)) {
		y -= moveSpeed;
	}
	if (dxInput->IsKeyDown(DIK_DOWN)) {
		y += moveSpeed;
	}

	if (dxInput->IsKeyPressed(DIK_SPACE)) {
		AppendObject(new DxSound(), 900, true);
		dxSound.Play();
	}

	sprite.Draw(x, y);

	return true;
}