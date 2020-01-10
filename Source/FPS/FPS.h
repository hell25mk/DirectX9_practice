#pragma once

#include "../BaseObject/BaseObject.h"

#pragma comment(lib,"winmm.lib")

class FPS : public BaseObject{

public:
	FPS();
	virtual void Init() override;
	virtual bool Update() override;

private:
	DWORD lastTime;

};

