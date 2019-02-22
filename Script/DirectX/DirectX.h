#pragma once

#include "../Window/Window.h"

class DirectX final: public Window{

public:
	DirectX();
	~DirectX();

	bool DirectXInit();
	bool DirectXEnd();

};

