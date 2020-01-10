#include "BaseGameItem.h"

BaseGameItem::BaseGameItem() :
	sprite(nullptr),texture(nullptr),x(0.0f),y(0.0f){
}

void BaseGameItem::Init() {
}

bool BaseGameItem::Update() {

	return true;
 }