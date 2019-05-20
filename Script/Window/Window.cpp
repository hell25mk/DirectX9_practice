#include "Window.h"

Window::Window()
	:widthSize(640), heightSize(480), nCmdShow(SW_SHOW){

	hInstance = GetModuleHandle(NULL);
	SetWindowName(Default_WindowName);

}

Window::~Window(){

	DestroyWindow(hWnd);		//Window�̔j��
	MessageBox(NULL, _T("�f�X�g���[�C"), _T("���b�Z�[�W"), MB_OK);

}

/// <summary>
/// @brief �E�B���h�E�𐶐�����N���X
/// </summary>
/// <returns>
/// @return true ����
/// @return false �������s
/// </returns>
bool Window::WindowInit(){

#pragma region �ǂ̂悤�ȃE�B���h�E���쐬���邩
	wc.cbClsExtra = 0;											//�\���̂̃T�C�Y���g������o�C�g��
	wc.cbWndExtra = 0;											//�E�B���h�E�̃T�C�Y���g������o�C�g��
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);		//�E�B���h�E�̔w�i��h��Ԃ��u���V
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);				//�E�B���h�E��Ƀ}�E�X�J�[�\���������ꍇ�̃}�E�X�̌`��
	wc.hIcon = NULL;											//�E�B���h�E�̃A�C�R���iLoadImage()�ł��Ă��悢�j
	wc.hInstance = hInstance;									//�E�B���h�E����邽�߂̃C���X�^���X�n���h�����w��
	wc.lpfnWndProc = WndProc;									//�E�B���h�E����ʒm���ꂽ�C�x���g���������邽�߂̊֐����w��
	wc.lpszClassName = _T("WindowsAPI");						//�o�^����E�B���h�E�̃N���X��
	wc.lpszMenuName = NULL;										//���j���[�̃��\�[�XID
	wc.style = NULL;											//�E�B���h�E�N���X�̃X�^�C��

	//�E�B���h�E�̓o�^�Ɏ��s�����ꍇ�I��������
	if(!RegisterClass(&wc)){
		MessageBox(NULL, _T("�E�B���h�E�̓o�^�Ɏ��s���܂���"), _T("�G���["), MB_OK);
		return false;
	}
#pragma endregion

#pragma region �E�B���h�E�̍쐬
	hWnd = CreateWindow(
		wc.lpszClassName,								//�o�^����Ă���N���X��
		windowName,										//�E�B���h�E�̃^�C�g��
		(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),		//�E�B���h�E�̃X�^�C��(�^�C�g���A�V�X�e���A�ŏ����g�p)
		CW_USEDEFAULT,									//�E�B���h�E��x�ʒu(�V�X�e���W���l���g�p)
		CW_USEDEFAULT,									//�E�B���h�E��y�ʒu
		widthSize,										//�E�B���h�E�̕�
		heightSize,										//�E�B���h�E�̍���
		NULL,											//�e�E�B���h�E�̃n���h��
		NULL,											//���j���[�n���h��
		hInstance,
		this											//�E�B���h�E�쐬���̃C�x���g�֓n���f�[�^�̃|�C���^(�����oProcedure���g�p���邽��this�|�C���^�����Ă���)
		);

	if(!hWnd){
		MessageBox(NULL, _T("�E�B���h�E�̐����Ɏ��s���܂���"), _T("�G���["), MB_OK);
		return false;
	}

	//�E�B���h�E�T�C�Y�̒���
	RECT r1, r2;

	GetClientRect(hWnd, &r1);
	GetWindowRect(hWnd, &r2);
	MoveWindow(
		hWnd, r2.left, r2.top,
		widthSize + ((r2.right - r2.left) - (r1.right - r1.left)),
		heightSize + ((r2.bottom - r2.top) - (r1.bottom - r1.top)),
		false
	);
#pragma endregion

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);

	MessageBox(hWnd, _T("�V���[�E�C���h�["), _T("���b�Z�[�W"), MB_OK);

	return true;
}