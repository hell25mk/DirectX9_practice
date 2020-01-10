#pragma once
/**********************************************************
Microsoft�А��ł͂Ȃ�C�R���p�C���̏ꍇ
#ifdef BASEOBJECT_H_
#define BASEOBJECT_H_
//���e
#endif
�œ�d�C���N���[�h�h�~(�錾���͏d�����Ȃ���Ή��ł��悢)
***********************************************************/

#include <string>
#include <memory>
#include <list>
#include <unordered_map>
#include <tchar.h>
#include "../Window/WindowObject.h"
#include "../DirectX/Direct3DObject.h"

//LisData�Ŏg�p���������ߑO���錾
class BaseObject;
class KeyEnum;
class PriorityEnum;

class ListData {

public:
	int priority;						//���X�g�}���̗D��x
	char name[Name_Size];				//�Ǘ�����
	BaseObject* gameObject;				//�I�u�W�F�N�g�|�C���^
	bool autoDelete;					//���X�g�폜�Ɠ����ɃI�u�W�F�N�g�폜���邩

};

class BaseObject{

public:
	/// <summary>
	/// �R���X�g���N�^(�ϐ��̏��������s��)
	/// </summary>
	BaseObject();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BaseObject() = default;
	/// <summary>
	/// �������������s��
	/// </summary>
	virtual void Init();
	/// <summary>
	/// �I���������s��
	/// </summary>
	virtual void Release();
	/// <summary>
	/// �X�V�������s��
	/// </summary>
	/// <returns></returns>
	virtual bool Update();

	/// <summary>
	/// �I�u�W�F�N�g�����X�g�ɒǉ�����
	/// </summary>
	/// <param name="listData">�ǉ�����f�[�^</param>
	void AppendObject(ListData& listData);
	/// <summary>
	/// �I�u�W�F�N�g�����X�g�ɒǉ�����
	/// </summary>
	/// <param name="obj">�ǉ�����I�u�W�F�N�g</param>
	/// <param name="priority">���X�g�}���̗D��x</param>
	/// <param name="autoDelete">���X�g�폜�Ɠ����ɃI�u�W�F�N�g�폜���邩</param>
	/// <param name="name">�Ǘ�����</param>
	void AppendObject(BaseObject* const obj, int priority, bool autoDelete, LPCSTR name = nullptr);

	/// <summary>
	/// ���X�g����I�u�W�F�N�g���폜����
	/// </summary>
	/// <param name="target">�폜����I�u�W�F�N�g</param>
	void RemoveObject(BaseObject* const target);
	void RemoveObject(int pBegin, int pEnd);

	/// <summary>
	/// ���X�g����I�u�W�F�N�g����������
	/// </summary>
	/// <param name="name">�Ǘ�����</param>
	/// <returns>���������ꍇ�ɂ��̃I�u�W�F�N�g�̃|�C���^��Ԃ�</returns>
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

#pragma region �񋓊֐�

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