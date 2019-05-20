#include "GameManager.h"
#include "../Font/FontManager.h"

void GameManager::Init(){

	taskObject.Init();
	gameTask.push_back(std::make_shared<FontManager>());

	for(auto itr = gameTask.begin(), end = gameTask.end(); itr != end;){

		(*itr)->Init();
		itr++;

	}

}

void GameManager::Delete(){

	for(auto itr = gameTask.begin(), end = gameTask.end(); itr != end;){

		(*itr)->Delete();
		itr++;

	}

}

bool GameManager::Update(){

	taskObject.BeginTask();

	for(auto itr = gameTask.begin(), end = gameTask.end(); itr != end;){

		(*itr)->Update();
		itr++;

	}

	for(auto itr = gameTask.begin(), end = gameTask.end(); itr != end;){

		(*itr)->Draw();
		itr++;

	}

	taskObject.EndTask();

	return true;
}