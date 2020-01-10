#pragma once

#include "../BaseObject/BaseObject.h"
#include "../Texture/Texture.h"
#include "../Sprite/Sprite.h"

class Texture;

class BaseGameItem : public BaseObject {

public:
	BaseGameItem();
	virtual void Init() override;
	virtual bool Update() override;

protected:
	Sprite sprite;
	Texture texture;

	float x, y;

};

