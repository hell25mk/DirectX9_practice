#pragma once

#include "../BaseObject/BaseObject.h"
#include "../FPS/FPS.h"

class TaskObject : public BaseObject{

public:
	virtual void Init() override;

	void BeginTask();
	void EndTask();

private:
	FPS fps;

};

