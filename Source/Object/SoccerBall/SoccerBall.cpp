#include "SoccerBall.h"

SoccerBall::SoccerBall(){

	rx = ry = 16.0f;
	er = 1.0f;

	x = 320.0f - rx;
	y = 240.0f - ry;

	moveX = moveY = 2.0f;

}

void SoccerBall::Init(){
	
	texture.Load(_T("Data/Image/soccerball.png"));
	sprite.SetTexture(&texture);

}

bool SoccerBall::Update(){

	Move();

	sprite.Draw(x, y, er, er, 0.0f);

	return true;
}

void SoccerBall::Move(){

	x += moveX;

	if(x < 0.0f + (rx * er)){
		x = 0.0f + (rx * er);
		moveX = -moveX;
	} else if(x > 640.0f - (rx * er)){
		x = 640.0f - (rx * er);
		moveX = -moveX;
	}

	y += moveY;

	if(y < 0.0f + (ry * er)){
		y = 0.0f + (ry * er);
		moveY = -moveY;
	} else if(y > 480.0f - (ry * er)){
		y = 480.0f - (ry * er);
		moveY = -moveY;
	}

}