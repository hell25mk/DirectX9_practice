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
/// @brief キーワードとオブジェクト名の先頭が一致した場合、そのオブジェクトポインタを返す
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

	//オブジェクトが見つからない場合はnullを返す
	return nullptr;
}

/// <summary>
/// @brief 指定範囲内の優先度をもつオブジェクトがあれば、そのオブジェクトポインタを返す
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
