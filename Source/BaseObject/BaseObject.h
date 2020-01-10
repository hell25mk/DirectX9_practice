#pragma once
/**********************************************************
Microsoft社製ではないCコンパイラの場合
#ifdef BASEOBJECT_H_
#define BASEOBJECT_H_
//内容
#endif
で二重インクルード防止(宣言名は重複しなければ何でもよい)
***********************************************************/

#include <string>
#include <memory>
#include <list>
#include <unordered_map>
#include <tchar.h>
#include "../Window/WindowObject.h"
#include "../DirectX/Direct3DObject.h"

//LisDataで使用したいため前方宣言
class BaseObject;
class KeyEnum;
class PriorityEnum;

class ListData {

public:
	int priority;						//リスト挿入の優先度
	char name[Name_Size];				//管理名称
	BaseObject* gameObject;				//オブジェクトポインタ
	bool autoDelete;					//リスト削除と同時にオブジェクト削除するか

};

class BaseObject{

public:
	/// <summary>
	/// コンストラクタ(変数の初期化を行う)
	/// </summary>
	BaseObject();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseObject() = default;
	/// <summary>
	/// 初期化処理を行う
	/// </summary>
	virtual void Init();
	/// <summary>
	/// 終了処理を行う
	/// </summary>
	virtual void Release();
	/// <summary>
	/// 更新処理を行う
	/// </summary>
	/// <returns></returns>
	virtual bool Update();

	/// <summary>
	/// オブジェクトをリストに追加する
	/// </summary>
	/// <param name="listData">追加するデータ</param>
	void AppendObject(ListData& listData);
	/// <summary>
	/// オブジェクトをリストに追加する
	/// </summary>
	/// <param name="obj">追加するオブジェクト</param>
	/// <param name="priority">リスト挿入の優先度</param>
	/// <param name="autoDelete">リスト削除と同時にオブジェクト削除するか</param>
	/// <param name="name">管理名称</param>
	void AppendObject(BaseObject* const obj, int priority, bool autoDelete, LPCSTR name = nullptr);

	/// <summary>
	/// リストからオブジェクトを削除する
	/// </summary>
	/// <param name="target">削除するオブジェクト</param>
	void RemoveObject(BaseObject* const target);
	void RemoveObject(int pBegin, int pEnd);

	/// <summary>
	/// リストからオブジェクトを検索する
	/// </summary>
	/// <param name="name">管理名称</param>
	/// <returns>見つかった場合にそのオブジェクトのポインタを返す</returns>
	BaseObject* FindObject(const char* name);

	void AppendItemBox(LPCSTR name, BaseObject* const obj);
	void RemoveItemBox(LPCSTR name);
	void ResetItemBox();
	BaseObject* FindItemBox(LPCSTR name);

	void CreateEnumeration(const char* keyword, KeyEnum* ke);
	void CreateEnumeration(int begin, int end, PriorityEnum* pe);

protected:
	WindowObject windowObject;
	Direct3DObject d3dObject;

	static std::list<ListData> objectList;
	static std::unordered_map<std::string, BaseObject*> itemBox;

	bool itMoved;
	std::list<ListData>::iterator itTask;

};

#pragma region 列挙関数

class Enumeration{

public:
	virtual BaseObject* GetNext() = 0;

protected:
	std::list<ListData>::iterator iPos, iEnd;

};

class KeyEnum : public Enumeration{

public:
	friend BaseObject;
	virtual BaseObject* GetNext() override;

private:
	char keyword[Name_Size];

};

class PriorityEnum : public Enumeration{

public:
	friend BaseObject;
	virtual BaseObject* GetNext() override;

private:
	int start, end;

};

#pragma endregion