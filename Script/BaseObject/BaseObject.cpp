#include "BaseObject.h"

HWND BaseObject::hWnd = nullptr;
HINSTANCE BaseObject::hInstance = nullptr;

std::list<ListData> BaseObject::listObject;
std::unordered_map<std::string, BaseObject*> BaseObject::itemBox;

bool BaseObject::itMoved;
std::list<ListData>::iterator BaseObject::itTask;

LPDIRECT3D9			BaseObject::pD3D = nullptr;
LPDIRECT3DDEVICE9	BaseObject::pD3Ddevice = nullptr;
LPD3DXSPRITE		BaseObject::pSprite = nullptr;

bool BaseObject::Initialize(HWND hWnd, HINSTANCE hInstance){

	this->hWnd = hWnd;
	this->hInstance = hInstance;

#pragma region DirectX�̏�����
	//Direct3D�I�u�W�F�N�g�𐶐�
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D == nullptr){
		//DXTRACE_MSG(_T("DirectXDevice�̏������Ɏ��s���܂���"));	//�Ȃ����G���[�o��

		return false;
	}

	D3DDISPLAYMODE d3ddm;
	if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		//DXTRACE_MSG(_T("DirectX3DDevice�̏������Ɏ��s���܂���"));

		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;										//�E�B���h�E���[�h�̐ݒ�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//�f�B�X�v���C�h���C�o�ɍł������I�ȕ��@��I��������
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					//�o�b�N�O���E���h�`��̕��@���V�X�e���ɔC����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//�`��X�V�̎w�������莟��҂����ɂ����X�V

	//D3D�f�o�C�X�I�u�W�F�N�g�̍쐬
	if(FAILED(pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&pD3Ddevice))){
		//DXTRACE_MSG(_T("3DDeviceObject�̏������Ɏ��s���܂���"));

		return false;
	}

	//�A���t�@�u�����h�̐ݒ�
	pD3Ddevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3Ddevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3Ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	if(FAILED(D3DXCreateSprite(pD3Ddevice, &pSprite))){
		//DXTRACE_MSG(_T("SpriteObject�̍쐬�Ɏ��s���܂���"));

		return false;
	}
#pragma endregion

	return true;
}

void BaseObject::Uninitialize(){

	D3D_RELEASE(pSprite);
	D3D_RELEASE(pD3Ddevice);
	D3D_RELEASE(pD3D);

	for(auto itr = listObject.begin(), end = listObject.end(); itr != end;){

		if((*itr).autoDelete){
			delete (*itr).gameObject;
			(*itr).gameObject = nullptr;
		}

		itr++;

	}

}

#pragma region Object
void BaseObject::AppendObject(ListData& listData){

	if(listData.gameObject == nullptr){
		return;
	}

	listData.gameObject->Init();

	//���X�g�̒��g���Ȃ���ΐ擪�ɒǉ�
	if(listObject.size() == 0){
		listObject.push_front(listData);
		return;
	}

	for(auto itr = listObject.begin(), end = listObject.end(); itr != end;){

		//�D�揇�ʂɏ]���}��
		if((*itr).priority > listData.priority){
			listObject.insert(itr, listData);
			return;
		}

		itr++;

	}

	//�Ԃɓ����Ƃ��낪�Ȃ���΃��X�g�̍Ō���ɒǉ�
	listObject.push_back(listData);

}

void BaseObject::AppendObject(BaseObject* object, int priority, bool autoDelete){

	AppendObject(object, priority, nullptr, autoDelete);

}

void BaseObject::AppendObject(BaseObject* object, int priority, LPCSTR name, bool autoDelete){

	ListData data;

	data.priority = priority;

	if(name != nullptr){
		strcpy_s(data.name, Name_Size, name);
	} else{
		ZeroMemory(data.name, Name_Size * sizeof(char));
	}

	data.gameObject = object;
	data.autoDelete = autoDelete;

	AppendObject(data);

}

void BaseObject::RemoveObject(BaseObject* target){

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

void BaseObject::RemoveObject(int pBegin, int pEnd){

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

void BaseObject::DoAllTasks(){

	std::list<ListData>::iterator end = listObject.end();
	itTask = listObject.begin();
	itMoved = false;

	while(itTask != end){

		itTask->gameObject->Update();

		if(!itMoved){
			itTask++;
		} else{
			itMoved = false;
		}

	}

}

BaseObject* BaseObject::FindObject(const char* name){

	for(auto itr = listObject.begin(), end = listObject.end(); itr != end;){

		if(strcmp((*itr).name, name) == 0){
			return (*itr).gameObject;
		}

		itr++;

	}

	return nullptr;
}
#pragma endregion

#pragma region ItemBox
void BaseObject::AppendItemBox(LPCSTR name, BaseObject* object){

	itemBox.insert(std::make_pair(name, object));

}

void BaseObject::RemoveItemBox(LPCSTR name){

	itemBox.erase(name);

}

void BaseObject::ResetItemBox(){

	itemBox.clear();

}

BaseObject* BaseObject::FindItemBox(LPCSTR name){

	std::unordered_map<std::string, BaseObject*>::iterator itr;
	itr = itemBox.find(name);

	if(itr == itemBox.end()){
		return nullptr;
	}

	return itr->second;
}
#pragma endregion