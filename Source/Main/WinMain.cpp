#include "../DirectX/DirectX.h"
#include "../Task/GameManager.h"
#include "../Sound/DxSound.h"

/// <summary>
/// ���C��(ANSI��Unicode�����ɑΉ����邽�߂�_t��t���Ă���)
/// �����̒��ߐݒ�������[�j���O������Ă���
/// </summary>
/// <param name="hInstance">�v���O���������ʂ��邽�߂̃n���h��</param>
/// <param name="hPrevInstance">Win16�̎Y���̂��ߏ��null</param>
/// <param name="lpszCmdLine">�R�}���h���C������󂯎��������</param>
/// <param name="nCmdShow">�A�v���P�[�V�����̏����\�����@</param>
/// <returns></returns>
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpszCmdLine, _In_ int nCmdShow){

#ifdef _DEBUG
	//�v���O�����I�����ɉ�����Ă��Ȃ�������������Όx�����o��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//���Ԍv����1�~���b�P�ʂɐݒ�
	timeBeginPeriod(1);

	DirectX dxWindow;
	dxWindow.SetWindowTitle(_T("DirectX9 �e�X�g�v���W�F�N�g"));
	if(!dxWindow.WindowInit()){
		return -1;
	}

	dxWindow.DxInit();
	
	GameManager gameManager;
	gameManager.Init();

	while(dxWindow.Process()){

		gameManager.Update();

	}

	gameManager.Release();
	dxWindow.DxEnd();

	return 0;
}