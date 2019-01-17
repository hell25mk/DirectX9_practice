#include "../BaseObject/BaseObject.h"
#include "GameMain.h"
#include "../Object/SoccerBall/SoccerBall.h"
#include "../Font/DxFontTest.h"
#include "../Object/Runner/Runner.h"

//�R���p�C�����萔
namespace{
	static const _TCHAR* Window_ClassName = _T("Game");
	static const  _TCHAR* Window_TitleName = _T("�N���X�܂݂�");

	constexpr int Window_Width = 640;
	constexpr int Window_Height = 480;
}

/// <summary>
/// @brief �E�B���h�E�C�x���g����������
/// </summary>
/// <param name="hWnd">�C�x���g�����������E�B���h�E�n���h��</param>
/// <param name="msg">���������C�x���g���e</param>
/// <param name="wParam">�C�x���g����ʒm���ꂽ�f�[�^</param>
/// <param name="lParam">�C�x���g����ʒm���ꂽ�f�[�^</param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	
	//�C�x���g����
	switch(msg){
		case WM_DESTROY:
			//�E�B���h�E������ꂽ��v���O�������I������
			PostQuitMessage(NULL);
			break;
		default:
			//�V�X�e���ɃC�x���g�����𓊂���
			return (DefWindowProc(hWnd, msg, wParam, lParam));
	}

	return (0);
}

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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//���Ԍv����1�~���b�P�ʂɐݒ�
	timeBeginPeriod(1);

	WNDCLASS wc;		//�o�^��������i�[����\����

#pragma region �ǂ̂悤�ȃE�B���h�E���쐬���邩
	wc.cbClsExtra = 0;											//�\���̂̃T�C�Y���g������o�C�g��
	wc.cbWndExtra = 0;											//�E�B���h�E�̃T�C�Y���g������o�C�g��
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//�E�B���h�E�̔w�i��h��Ԃ��u���V
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);				//�E�B���h�E��Ƀ}�E�X�J�[�\���������ꍇ�̃}�E�X�̌`��
	wc.hIcon = NULL;											//�E�B���h�E�̃A�C�R���iLoadImage()�ł��Ă��悢�j
	wc.hInstance = hInstance;									//�E�B���h�E����邽�߂̃C���X�^���X�n���h�����w��
	wc.lpfnWndProc = WndProc;									//�E�B���h�E����ʒm���ꂽ�C�x���g���������邽�߂̊֐����w��
	wc.lpszClassName = Window_ClassName;						//�o�^����E�B���h�E�̃N���X��
	wc.lpszMenuName = NULL;										//���j���[�̃��\�[�XID
	wc.style = NULL;											//�E�B���h�E�N���X�̃X�^�C��

	//�E�B���h�E�̓o�^�Ɏ��s�����ꍇ�I��������
	if(RegisterClass(&wc) == NULL){
		return -1;
	}
#pragma endregion
	
#pragma region �E�B���h�E�̍쐬
	HWND hWnd = CreateWindow(
		wc.lpszClassName,							//�o�^����Ă���N���X��
		Window_TitleName,							//�E�B���h�E�̃^�C�g��
		(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),	//�E�B���h�E�̃X�^�C��(�^�C�g���A�V�X�e���A�ŏ����g�p)
		CW_USEDEFAULT,								//�E�B���h�E��x�ʒu(�V�X�e���W���l���g�p)
		CW_USEDEFAULT,								//�E�B���h�E��y�ʒu
		Window_Width,								//�E�B���h�E�̕�
		Window_Height,								//�E�B���h�E�̍���
		NULL,										//�e�E�B���h�E�̃n���h��
		NULL,										//���j���[�n���h��
		hInstance,
		NULL,										//�E�B���h�E�쐬���̃C�x���g�֓n���f�[�^�̃|�C���^
	);

	//�E�B���h�E�T�C�Y�̒���
	RECT r1, r2;

	GetClientRect(hWnd, &r1);
	GetWindowRect(hWnd, &r2);
	MoveWindow(
		hWnd, r2.left, r2.top,
		Window_Width + ((r2.right - r2.left) - (r1.right - r1.left)),
		Window_Height + ((r2.bottom - r2.top) - (r1.bottom - r1.top)),
		false
	);
#pragma endregion

#pragma region DirectX�̏�����
	BaseObject game;

	game.Initialize(hWnd, hInstance);

	//
	game.AppendObject(new TaskHead(), 0, true);
	game.AppendObject(new TaskTail(), INT_MAX, true);

	//1�`INT_MAX-1�͈̔͂ŗD��x�����߂�
	game.AppendObject(new SoccerBall(), 1, true);
	game.AppendObject(new Runner(), 2, true);
	game.AppendObject(new DxFontTestStart(), 3, true);
#pragma endregion

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);

#pragma region �E�B���h�E���[�v
	MSG msg;
	
	while(true){

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT){
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else{
			game.DoAllTasks();
		}

	}
#pragma endregion

#pragma region DirectX�I�u�W�F�N�g�̉��
	game.Uninitialize();
#pragma endregion

	return 0;
}