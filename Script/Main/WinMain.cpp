#include "../DirectX/DirectX.h"
#include "../BaseObject/BaseObject.h"
#include "GameMain.h"
#include "../Object/SoccerBall/SoccerBall.h"
#include "../Font/DxFontTest.h"
#include "../Object/Runner/Runner.h"

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
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//���Ԍv����1�~���b�P�ʂɐݒ�
	//timeBeginPeriod(1);

	DirectX window;
	window.SetWindowName(_T("�e�X�g����"));
	if(!window.WindowInit()){
		return -1;
	}

#pragma region DirectX�̏�����
	/*BaseObject game;

	game.Initialize(hWnd, hInstance);

	//
	game.AppendObject(new TaskHead(), 0, true);
	game.AppendObject(new TaskTail(), INT_MAX, true);

	//1�`INT_MAX-1�͈̔͂ŗD��x�����߂�
	game.AppendObject(new SoccerBall(), 1, true);
	game.AppendObject(new Runner(), 2, true);
	game.AppendObject(new DxFontTestStart(), 3, true);*/
#pragma endregion

#pragma region �E�B���h�E���[�v
	while(window.Process()){



	}
#pragma endregion

#pragma region DirectX�I�u�W�F�N�g�̉��
	//game.Uninitialize();
#pragma endregion

	return 0;
}