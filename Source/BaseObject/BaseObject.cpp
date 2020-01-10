#include "BaseObject.h"

std::list<ListData> BaseObject::objectList;
std::unordered_map<std::string, BaseObject*> BaseObject::itemBox;

BaseObject::BaseObject() :
	windowObject(), d3dObject(), itMoved(), itTask(){
}

/// <summary>
/// �������������s��
/// </summary>
void BaseObject::Init(){
}

/// <summary>
/// �I���������s��
/// </summary>
void BaseObject::Release(){
}

/// <summary>
/// �X�V�������s��
/// </summary>
/// <returns>true:�I�u�W�F�N�g�����݂��� false:�I�u�W�F�N�g�����݂��Ȃ�</returns>
bool BaseObject::Update(){

	for(auto itr = objectList.begin(), end = objectList.end(); itr != end;){

		(*itr).gameObject->Update();

		itr++;

	}

	return true;
}

