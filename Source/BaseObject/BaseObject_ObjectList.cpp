#include "BaseObject.h"

/// <summary>
/// �I�u�W�F�N�g�����X�g�ɒǉ�����
/// </summary>
/// <param name="listData">�ǉ�����f�[�^</param>
void BaseObject::AppendObject(ListData& listData) {

	if (listData.gameObject == nullptr) {
		return;
	}

	//�I�u�W�F�N�g�̏��������s��
	listData.gameObject->Init();

	//���X�g�̒��g���Ȃ���ΐ擪�ɒǉ�
	if (objectList.size() == 0) {
		objectList.push_front(listData);
		return;
	}

	for (auto itr = objectList.begin(), end = objectList.end(); itr != end;) {

		//�D�揇�ʂɏ]���}��
		if ((*itr).priority > listData.priority) {
			objectList.insert(itr, listData);
			return;
		}

		itr++;

	}

	//�Ԃɓ����Ƃ��낪�Ȃ���΃��X�g�̍Ō���ɒǉ�
	objectList.push_back(listData);

}

/// <summary>
/// �I�u�W�F�N�g�����X�g�ɒǉ�����
/// </summary>
/// <param name="obj">�ǉ�����I�u�W�F�N�g</param>
/// <param name="priority">���X�g�}���̗D��x</param>
/// <param name="autoDelete">���X�g�폜�Ɠ����ɃI�u�W�F�N�g�폜���邩</param>
/// <param name="name">�Ǘ�����</param>
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
/// ���X�g����I�u�W�F�N�g���폜����
/// </summary>
/// <param name="target">�폜����I�u�W�F�N�g</param>
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
/// ���X�g����I�u�W�F�N�g����������
/// </summary>
/// <param name="name">�Ǘ�����</param>
/// <returns>���������ꍇ�ɂ��̃I�u�W�F�N�g�̃|�C���^��Ԃ�</returns>
BaseObject* BaseObject::FindObject(const char* name) {

	for (auto itr = objectList.begin(), end = objectList.end(); itr != end; itr++) {

		// �^�X�N�ǉ����ɗp����������ƌ����ɗp����L�[������Ɗ��S��v�����ꍇ�I�u�W�F�N�g��Ԃ�
		if (strcmp((*itr).name, name) == 0) {
			return (*itr).gameObject;
		}

	}

	return nullptr;
}