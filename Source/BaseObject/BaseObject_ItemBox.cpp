#include "BaseObject.h"

void BaseObject::AppendItemBox(LPCSTR name, BaseObject* const object) {

	itemBox.insert(std::make_pair(name, object));

}

void BaseObject::RemoveItemBox(LPCSTR name) {

	itemBox.erase(name);

}

void BaseObject::ResetItemBox() {

	itemBox.clear();

}

BaseObject* BaseObject::FindItemBox(LPCSTR name) {

	std::unordered_map<std::string, BaseObject*>::iterator itr;
	itr = itemBox.find(name);

	if (itr == itemBox.end()) {
		return nullptr;
	}

	return itr->second;
}