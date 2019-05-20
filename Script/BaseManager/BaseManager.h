#pragma once

#include <string>
#include <memory>
#include <list>
#include <unordered_map>
#include "../BaseObject/BaseObject.h"

class ListData{

public:
	int priority;						//���s����
	TCHAR name[Name_Size];				//�Ǘ�����
	BaseObject* gameObject;				//�I�u�W�F�N�g�|�C���^
	bool autoDelete;					//���X�g�폜�Ɠ����ɃI�u�W�F�N�g�폜

};

class BaseManager{

public:
	BaseManager() = default;
	virtual ~BaseManager() = default;
	virtual void Init();
	virtual void Delete();
	virtual bool Update();
	virtual void Draw();

	void AppendObject(ListData& listData);
	void AppendObject(BaseObject* const obj, int priority, bool autoDelete, LPCTSTR name = nullptr);

	void RemoveObject(BaseObject* const target);
	void RemoveObject(int pBegin, int pEnd);

	BaseObject* FindObject(LPCTSTR name);

	void AppendItemBox(LPCSTR name, BaseObject* const obj);
	void RemoveItemBox(LPCSTR name);
	void ResetItemBox();
	BaseObject* FindItemBox(LPCSTR name);

protected:
	std::list<ListData> listObject;
	std::unordered_map<std::string, BaseObject*> itemBox;

	bool itMoved;
	std::list<ListData>::iterator itTask;

};

