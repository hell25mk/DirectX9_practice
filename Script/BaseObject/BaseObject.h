#pragma once
/**********************************************************
Microsoft社製ではないCコンパイラの場合
#ifdef BASEOBJECT_H_
#define BASEOBJECT_H_
//内容
#endif
で二重インクルード防止(宣言名は重複しなければ何でもよい)
***********************************************************/

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <memory>
#include <list>
#include <unordered_map>

#include <DxErr.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "DxErr.lib")
#pragma comment(lib, "d3d9.lib")	// Direct3D9 ライブラリをリンクする
#pragma comment(lib, "d3dx9.lib")	// Direct3DX9 ライブラリをリンクする
#pragma comment(lib, "dxguid.lib")

#if _DEBUG
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif // _DEBUG

#define D3D_RELEASE(x) {if(x) x->Release();}

namespace{
	constexpr int Name_Size = 32;

	template<class Type>
	constexpr void D3D_Release(Type obj){

		if(obj){
			obj->Release();
		}

	}

	constexpr float D2r(float d){

		return (d / 180.0f * D3DX_PI);
	}
}

class ListData{

public:
	int priority;						//実行順位
	char name[Name_Size];				//管理名称
	class BaseObject* gameObject;		//オブジェクトポインタ
	bool autoDelete;					//リスト削除と同時にオブジェクト削除

};

class BaseObject{

public:
	virtual ~BaseObject() = default;

	static const HWND GetHWnd(){ 
		return hWnd; 
	}
	static const HINSTANCE GetHInstance(){ 
		return hInstance; 
	}
	
	static void AppendObject(ListData& listData);
	static void AppendObject(BaseObject* object, int priority, bool autoDelete);
	static void AppendObject(BaseObject* object, int priority, LPCSTR name, bool autoDelete);
	
	static void RemoveObject(BaseObject* target);
	static void RemoveObject(int pBegin, int pEnd);

	BaseObject* FindObject(const char* name);

	static void AppendItemBox(LPCSTR name, BaseObject* object);
	static void RemoveItemBox(LPCSTR name);
	static void ResetItemBox();
	static BaseObject* FindItemBox(LPCSTR name);

protected:
	virtual void Init(){ }
	virtual bool Update(){
		return true;
	}

protected:
	static LPDIRECT3D9 pD3D;
	static LPDIRECT3DDEVICE9 pD3Ddevice;
	static LPD3DXSPRITE pSprite;

private:
	friend int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int);

	bool Initialize(HWND hWnd, HINSTANCE hInstance);
	void Uninitialize();
	void DoAllTasks();

private:
	static HWND hWnd;
	static HINSTANCE hInstance;
	static std::list<ListData> listObject;
	static std::unordered_map<std::string, BaseObject*> itemBox;

	static bool itMoved;
	static std::list<ListData>::iterator itTask;

};