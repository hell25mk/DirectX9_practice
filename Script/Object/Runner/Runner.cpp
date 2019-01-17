#include "Runner.h"

void Runner::Init(){

	texture.Load(_T("Image/anime.png"));
	sprite.SetTexture(&texture);
	sprite.SetSpriteSize(128, 128);

}

bool Runner::Update(){

	static int frame = 0, count = 0;

	if(++count >= 12){
		count = 0;
		if(++frame >= 8){
			frame = 0;
		}
		sprite.SetFrame(frame);
	}

	sprite.Draw(320.0f, 240.0f);

	return true;
}