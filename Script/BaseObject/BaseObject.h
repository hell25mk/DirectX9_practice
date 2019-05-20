#pragma once
/**********************************************************
Microsoft�А��ł͂Ȃ�C�R���p�C���̏ꍇ
#ifdef BASEOBJECT_H_
#define BASEOBJECT_H_
//���e
#endif
�œ�d�C���N���[�h�h�~(�錾���͏d�����Ȃ���Ή��ł��悢)
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