#pragma once

#include "../../Sprite/Sprite.h"
#include "../../Texture/Texture.h"

class SoccerBall : public BaseObject{

public:
	SoccerBall();
	virtual ~SoccerBall() = default;

protected:
	virtual void Init() override;
	virtual bool Update() override;

private:
	void Move();

private:
	float x, y;
	float rx, ry;
	float er;

	float moveX, moveY;
	Texture texture;
	Sprite sprite;

};

