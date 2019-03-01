#pragma once

#include "../DirectX/Direct3DObject.h"
#include "../Window/Window.h"

class DirectX final: public Window{

public:
	DirectX();
	~DirectX();

	bool DirectXInit();
	bool DirectXEnd();

private:
	Direct3DObject d3dObject;

};

