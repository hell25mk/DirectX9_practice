#include "Window.h"

Window::Window() : Window(640, 480){
}

Window::Window(unsigned int wid, unsigned int hig) :
	windowClass(),
	windowObject(),
	nCmdShow(SW_SHOW),
	windowTitle(_T("MyWindowProgram")),
	widthSize(wid),
	heightSize(hig){

	windowObject.hInstance = GetModuleHandle(NULL);

}

Window::~Window(){

	DestroyWindow(windowObject.hWnd);		//Window�̔j��
	//MessageBox(NULL, _T("�E�B���h�E���폜���܂���"), _T("���b�Z�[�W"), MB_OK);

}

/// <summary>
/// �E�B���h�E�𐶐�����N���X
/// </summary>
/// <returns>�����ɐ������������s������</returns>
bool Window::WindowInit(){

#pragma region �ǂ̂悤�ȃE�B���h�E���쐬���邩
	windowClass.cbClsExtra = 0;												//�\���̂̃T�C�Y���g������o�C�g��
	windowClass.cbWndExtra = 0;												//�E�B���h�E�̃T�C�Y���g������o�C�g��
	windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);		//�E�B���h�E�̔w�i��h��Ԃ��u���V
	windowClass.hCursor = LoadCursor(windowObject.hInstance, IDC_ARROW);	//�E�B���h�E��Ƀ}�E�X�J�[�\���������ꍇ�̃}�E�X�̌`��
	windowClass.hIcon = NULL;												//�E�B���h�E�̃A�C�R���iLoadImage()�ł��Ă��悢�j
	windowClass.hInstance = windowObject.hInstance;							//�E�B���h�E����邽�߂̃C���X�^���X�n���h�����w��
	windowClass.lpfnWndProc = WndProc;										//�E�B���h�E����ʒm���ꂽ�C�x���g���������邽�߂̊֐����w��
	windowClass.lpszClassName = _T("WindowsAPI");							//�o�^����E�B���h�E�̃N���X��
	windowClass.lpszMenuName = NULL;										//���j���[�̃��\�[�XID
	windowClass.style = NULL;												//�E�B���h�E�N���X�̃X�^�C��

	//�E�B���h�E�̓o�^�Ɏ��s�����ꍇ�I��������
	if(!RegisterClass(&windowClass)){
		MessageBox(NULL, _T("�E�B���h�E�̓o�^�Ɏ��s���܂���"), _T("�G���["), MB_OK);
		return false;
	}
#pragma endregion

#pragma region �E�B���h�E�̍쐬
	windowObject.hWnd = CreateWindow(
		windowClass.lpszClassName,						//�o�^����Ă���N���X��
		windowTitle,										//�E�B���h�E�̃^�C�g��
		(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),		//�E�B���h�E�̃X�^�C��(�^�C�g���A�V�X�e���A�ŏ����g�p)
		CW_USEDEFAULT,									//�E�B���h�E��x�ʒu(�V�X�e���W���l���g�p)
		CW_USEDEFAULT,									//�E�B���h�E��y�ʒu
		widthSize,										//�E�B���h�E�̕�
		heightSize,										//�E�B���h�E�̍���
		NULL,											//�e�E�B���h�E�̃n���h��
		NULL,											//���j���[�n���h��
		windowObject.hInstance,
		this											//�E�B���h�E�쐬���̃C�x���g�֓n���f�[�^�̃|�C���^(�����oProcedure���g�p���邽��this�|�C���^�����Ă���)
		);

	if(!windowObject.hWnd){
		MessageBox(NULL, _T("�E�B���h�E�̐����Ɏ��s���܂���"), _T("�G���["), MB_OK);
		return false;
	}

	//�E�B���h�E�T�C�Y�̒���
	RECT r1, r2;

	GetClientRect(windowObject.hWnd, &r1);
	GetWindowRect(windowObject.hWnd, &r2);
	MoveWindow(
		windowObject.hWnd, r2.left, r2.top,
		widthSize + ((r2.right - r2.left) - (r1.right - r1.left)),
		heightSize + ((r2.bottom - r2.top) - (r1.bottom - r1.top)),
		false
	);
#pragma endregion

	ShowWindow(windowObject.hWnd, nCmdShow);

	//MessageBox(windowObject.hWnd, _T("�E�B���h�E�𐶐����܂���"), _T("���b�Z�[�W"), MB_OK);

	return true;
}