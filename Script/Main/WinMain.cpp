#include "../DirectX/DirectX.h"
#include "../Task/GameManager.h"

/// <summary>
/// @brief ���C��(ANSI��Unicode�����ɑΉ����邽�߂�_t��t���Ă���)
/// </summary>
/// <param name="hInstance">�v���O���������ʂ��邽�߂̃n���h��</param>
/// <param name="hPrevInstance">Win16�̎Y���̂��ߏ��null</param>
/// <param name="lpszCmdLine">�R�}���h���C������󂯎��������</param>
/// <param name="nCmdShow">�A�v���P�[�V�����̏����\�����@</param>
/// <returns></returns>
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow){

#ifdef _DEBUG
	//�v���O�����I�����ɉ�����Ă��Ȃ�������������Όx�����o��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//���Ԍv����1�~���b�P�ʂɐݒ�
	//timeBeginPeriod(1);

	DirectX window;
	window.SetWindowName(_T("�e�X�g����"));
	if(!window.WindowInit()){
		return -1;
	}

	window.DxInit();
	
	GameManager gameManager;

	gameManager.Init();

	while(window.Process()){

		gameManager.Update();
		gameManager.Draw();

	}

	gameManager.Delete();
	window.DxEnd();

	return 0;
}