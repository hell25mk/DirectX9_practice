#pragma once

#include "../BaseObject/BaseObject.h"

#pragma comment(lib,"winmm.lib")

class FPS : public BaseObject{

public:
	virtual void Init() override;
	virtual bool Update() override;

private:
	DWORD lasttime;

};

