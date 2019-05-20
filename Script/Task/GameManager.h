#pragma once

#include "../BaseManager/BaseManager.h"
#include <memory>
#include "../FPS/FPS.h"
#include "TaskObject.h"

class GameManager : public BaseManager{

public:
	GameManager() = default;
	virtual ~GameManager() = default;
	virtual void Init();
	virtual void Delete();
	virtual bool Update();

private:
	std::list<std::shared_ptr<BaseManager>> gameTask;
	TaskObject taskObject;

};

