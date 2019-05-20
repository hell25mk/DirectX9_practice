#pragma once

#include "../DirectX/Direct3DObject.h"
#include "../Window/Window.h"

class DirectX final: public Window{

public:
	DirectX() = default;
	~DirectX() = default;

	bool DxInit();
	bool DxEnd();

private:
	Direct3DObject d3dObject;

};

