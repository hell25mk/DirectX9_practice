#pragma once
/**********************************************************
Microsoft社製ではないCコンパイラの場合
#ifdef BASEOBJECT_H_
#define BASEOBJECT_H_
//内容
#endif
で二重インクルード防止(宣言名は重複しなければ何でもよい)
***********************************************************/

#include "../DirectX/Direct3DObject.h"
#include <tchar.h>
#include <Windows.h>

class BaseObject{

public:
	BaseObject() = default;
	virtual ~BaseObject() = default;
	virtual void Init();
	virtual void Delete();
	virtual bool Update();
	virtual void Draw();

protected:
	Direct3DObject d3dObject;

};