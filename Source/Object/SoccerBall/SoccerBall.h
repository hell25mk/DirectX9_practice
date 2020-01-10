#pragma once

#include "../BaseGameItem.h"

class SoccerBall : public BaseGameItem {

public:
	SoccerBall();
	virtual ~SoccerBall() = default;

protected:
	virtual void Init() override;
	virtual bool Update() override;

private:
	void Move();

private:
	float rx, ry;
	float er;

	float moveX, moveY;

};

