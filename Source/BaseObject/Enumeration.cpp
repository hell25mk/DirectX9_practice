#include "BaseObject.h"

void BaseObject::CreateEnumeration(const char* keyword, KeyEnum* ke){

	ke->iPos = objectList.begin();
	ke->iEnd = objectList.end();

	strcpy_s(ke->keyword, Name_Size, keyword);

}

void BaseObject::CreateEnumeration(int begin, int end, PriorityEnum* pe){

	pe->iPos = objectList.begin();
	pe->iEnd = objectList.end();

	pe->start = begin;
	pe->end = end;

}


/// <summary>
/// @brief �L�[���[�h�ƃI�u�W�F�N�g���̐擪����v�����ꍇ�A���̃I�u�W�F�N�g�|�C���^��Ԃ�
/// </summary>
/// <returns></returns>
BaseObject* KeyEnum::GetNext(){

	char* p1,* p2;

	while(iPos != iEnd){

		p1 = keyword;
		p2 = (*iPos).name;

		while(*p1 != '\0'){

			if(*p1 != *p2){
				break;
			}

			p1++;
			p2++;

		}

		if(*p1 == '\0'){
			BaseObject* g = iPos->gameObject;
			iPos++;
			
			return g;
		}

		iPos++;

	}

	//�I�u�W�F�N�g��������Ȃ��ꍇ��null��Ԃ�
	return nullptr;
}

/// <summary>
/// @brief �w��͈͓��̗D��x�����I�u�W�F�N�g������΁A���̃I�u�W�F�N�g�|�C���^��Ԃ�
/// </summary>
/// <returns></returns>
BaseObject* PriorityEnum::GetNext(){

	while(iPos != iEnd){

		if(iPos->priority > this->end){
			iPos = iEnd;

			return nullptr;
		}
		else if(iPos->priority >= this->start){
			BaseObject* g = iPos->gameObject;
			iPos++;

			return g;
		}

		iPos++;

	}

	return nullptr;
}
