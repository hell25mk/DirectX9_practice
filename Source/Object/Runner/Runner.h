#pragma once

#include "../BaseGameItem.h"
#include "../../Sound/DxSound.h"

class DxInput;

class Runner : public BaseGameItem {

public:
	Runner();
	virtual ~Runner() = default;

protected:
	virtual void Init() override;
	virtual bool Update() override;

private:
	DxInput* dxInput;
	DxSound dxSound;

	float x, y;
	float moveSpeed;

};