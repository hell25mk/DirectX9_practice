#pragma once

#include "../BaseObject/BaseObject.h"
#include "../FPS/FPS.h"

class TaskHead : public BaseObject{

protected:
	virtual void Init() override;
	virtual bool Update() override;

private:
	FPS fps;

};

class TaskTail : public BaseObject{

protected:
	virtual bool Update() override;

};

