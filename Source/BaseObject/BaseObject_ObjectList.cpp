#include "BaseObject.h"

/// <summary>
/// オブジェクトをリストに追加する
/// </summary>
/// <param name="listData">追加するデータ</param>
void BaseObject::AppendObject(ListData& listData) {

	if (listData.gameObject == nullptr) {
		return;
	}

	//オブジェクトの初期化を行う
	listData.gameObject->Init();

	//リストの中身がなければ先頭に追加
	if (objectList.size() == 0) {
		objectList.push_front(listData);
		return;
	}

	for (auto itr = objectList.begin(), end = objectList.end(); itr != end;) {

		//優先順位に従い挿入
		if ((*itr).priority > listData.priority) {
			objectList.insert(itr, listData);
			return;
		}

		itr++;

	}

	//間に入れるところがなければリストの最後尾に追加
	objectList.push_back(listData);

}

/// <summary>
/// オブジェクトをリストに追加する
/// </summary>
/// <param name="obj">追加するオブジェクト</param>
/// <param name="priority">リスト挿入の優先度</param>
/// <param name="autoDelete">リスト削除と同時にオブジェクト削除するか</param>
/// <param name="name">管理名称</param>
void BaseObject::AppendObject(BaseObject* const object, int priority, bool autoDelete, LPCSTR name) {

	ListData data;

	data.priority = priority;

	if (name != nullptr) {
		strcpy_s(data.name, Name_Size, name);
	} else {
		ZeroMemory(data.name, Name_Size * sizeof(char));
	}

	data.gameObject = object;
	data.autoDelete = autoDelete;

	AppendObject(data);

}

/// <summary>
/// リストからオブジェクトを削除する
/// </summary>
/// <param name="target">削除するオブジェクト</param>
void BaseObject::RemoveObject(BaseObject* const target) {

	std::list<ListData>::iterator itr = objectList.begin(), end = objectList.end();

	while (itr != end) {

		if ((*itr).gameObject == target) {
			if (itTask == itr) {
				itMoved = true;
				itTask++;
			}

			if (itr->autoDelete) {
				delete itr->gameObject;
				itr->gameObject = nullptr;
			}

			objectList.erase(itr);

			return;
		} else {
			itr++;
		}
	}

}

void BaseObject::RemoveObject(int pBegin, int pEnd) {

	std::list<ListData>::iterator itr = objectList.begin(), end = objectList.end();

	while (itr != end) {

		if ((*itr).priority > pEnd) {
			break;
		} else if ((*itr).priority >= pBegin) {

			if (itTask == itr) {
				itMoved = true;
				itTask++;
			}

			if (itr->autoDelete) {
				delete itr->gameObject;
				itr->gameObject = nullptr;
			}

			itr = objectList.erase(itr);

		} else {
			itr++;
		}

	}

}

/// <summary>
/// リストからオブジェクトを検索する
/// </summary>
/// <param name="name">管理名称</param>
/// <returns>見つかった場合にそのオブジェクトのポインタを返す</returns>
BaseObject* BaseObject::FindObject(const char* name) {

	for (auto itr = objectList.begin(), end = objectList.end(); itr != end; itr++) {

		// タスク追加時に用いた文字列と検索に用いるキー文字列と完全一致した場合オブジェクトを返す
		if (strcmp((*itr).name, name) == 0) {
			return (*itr).gameObject;
		}

	}

	return nullptr;
}