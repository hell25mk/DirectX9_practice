#pragma once

#include "../../BaseObject/BaseObject.h"
#include "../../Texture/Texture.h"
#include "../../Sprite/Sprite.h"

class Runner : public BaseObject{

public:
	Runner() = default;
	virtual ~Runner() = default;

protected:
	virtual void Init() override;
	virtual bool Update() override;

private:
	Texture texture;
	Sprite sprite;

};