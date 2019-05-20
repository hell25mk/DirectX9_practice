#include "BaseManager.h"

void BaseManager::Init(){



}

void BaseManager::Delete(){



}

bool BaseManager::Update(){

	for(auto itr = listObject.begin(), end = listObject.end(); itr != end;){

		(*itr).gameObject->Update();

		itr++;

	}

	return true;
}

void BaseManager::Draw(){

	for(auto itr = listObject.begin(), end = listObject.end(); itr != end;){

		(*itr).gameObject->Draw();

		itr++;

	}

}

#pragma region Object
void BaseManager::AppendObject(ListData& listData){

	if(listData.gameObject == nullptr){
		return;
	}

	listData.gameObject->Init();

	//ÉäÉXÉgÇÃíÜêgÇ™Ç»ÇØÇÍÇŒêÊì™Ç…í«â¡
	if(listObject.size() == 0){
		listObject.push_front(listData);
		return;
	}

	for(auto itr = listObject.begin(), end = listObject.end(); itr != end;){

		//óDêÊèáà Ç…è]Ç¢ë}ì¸
		if((*itr).priority > listData.priority){
			listObject.insert(itr, listData);
			return;
		}

		itr++;

	}

	//ä‘Ç…ì¸ÇÍÇÈÇ∆Ç±ÇÎÇ™Ç»ÇØÇÍÇŒÉäÉXÉgÇÃç≈å„îˆÇ…í«â¡
	listObject.push_back(listData);

}

void BaseManager::AppendObject(BaseObject* const object, int priority, bool autoDelete, LPCTSTR name){

	ListData data;

	data.priority = priority;

	if(name != nullptr){
		_tcscpy_s(data.name, Name_Size, name);
	} else{
		ZeroMemory(data.name, Name_Size * sizeof(char));
	}

	data.gameObject = object;
	data.autoDelete = autoDelete;

	AppendObject(data);

}

void BaseManager::RemoveObject(BaseObject* const target){

	std::list<ListData>::iterator itr = listObject.begin(), end = listObject.end();
	while(itr != end){
		
		if((*itr).gameObject == target){
			if(itTask == itr){
				itMoved = true;
				itTask++;
			}

			if(itr->autoDelete){
				delete itr->gameObject;
				itr->gameObject = nullptr;
			}

			listObject.erase(itr);

			return;
		} else{
			itr++;
		}
	}

}

void BaseManager::RemoveObject(int pBegin, int pEnd){

	std::list<ListData>::iterator itr = listObject.begin(), end = listObject.end();

	while(itr != end){

		if((*itr).priority > pEnd){
			break;
		} else if((*itr).priority >= pBegin){

			if(itTask == itr){
				itMoved = true;
				itTask++;
			}

			if(itr->autoDelete){
				delete itr->gameObject;
				itr->gameObject = nullptr;
			}

			itr = listObject.erase(itr);

		} else{
			itr++;
		}

	}

}

BaseObject* BaseManager::FindObject(LPCTSTR name){

	for(auto itr = listObject.begin(), end = listObject.end(); itr != end;){

		if(_tcsncmp((*itr).name, name,sizeof((*itr).name)) == 0){
			return (*itr).gameObject;
		}

		itr++;

	}

	return nullptr;
}
#pragma endregion

#pragma region ItemBox
void BaseManager::AppendItemBox(LPCSTR name, BaseObject* const object){

	itemBox.insert(std::make_pair(name, object));

}

void BaseManager::RemoveItemBox(LPCSTR name){

	itemBox.erase(name);

}

void BaseManager::ResetItemBox(){

	itemBox.clear();

}

BaseObject* BaseManager::FindItemBox(LPCSTR name){

	std::unordered_map<std::string, BaseObject*>::iterator itr;
	itr = itemBox.find(name);

	if(itr == itemBox.end()){
		return nullptr;
	}

	return itr->second;
}
#pragma endregion