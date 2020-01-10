#pragma once

#include "../BaseObject/BaseObject.h"
#include <memory>
#include "../FPS/FPS.h"
#include "..//Sound/DxSound.h"

class GameManager : public BaseObject{

public:
	GameManager() = default;
	virtual ~GameManager() = default;
	virtual void Init() override;
	virtual void Release();
	virtual bool Update() override;
	void BeginTask();
	void EndTask();

private:
	FPS fps;
	DxSound dxSound;

};

