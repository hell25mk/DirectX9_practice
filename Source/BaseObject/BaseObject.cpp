#include "BaseObject.h"

std::list<ListData> BaseObject::objectList;
std::unordered_map<std::string, BaseObject*> BaseObject::itemBox;

BaseObject::BaseObject() :
	windowObject(), d3dObject(), itMoved(), itTask(){
}

/// <summary>
/// 初期化処理を行う
/// </summary>
void BaseObject::Init(){
}

/// <summary>
/// 終了処理を行う
/// </summary>
void BaseObject::Release(){
}

/// <summary>
/// 更新処理を行う
/// </summary>
/// <returns>true:オブジェクトが存在する false:オブジェクトが存在しない</returns>
bool BaseObject::Update(){

	for(auto itr = objectList.begin(), end = objectList.end(); itr != end;){

		(*itr).gameObject->Update();

		itr++;

	}

	return true;
}

