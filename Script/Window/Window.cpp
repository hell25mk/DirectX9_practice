#include "Window.h"

/*Window::Window():widthSize(640), heightSize(480){
}

void Window::SetWindowSize(const int wid, const int hig){

	widthSize = wid;
	heightSize = hig;

}

void Window::SetClassName(_TCHAR* const name){

	className = name;

}

void Window::SetWindowName(_TCHAR* const name){

	windowName = name;

}*/

///// <summary>
///// @brief �E�B���h�E�C�x���g����������
///// </summary>
///// <param name="hWnd">�C�x���g�����������E�B���h�E�n���h��</param>
///// <param name="msg">���������C�x���g���e</param>
///// <param name="wParam">�C�x���g����ʒm���ꂽ�f�[�^</param>
///// <param name="lParam">�C�x���g����ʒm���ꂽ�f�[�^</param>
///// <returns></returns>
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
//
//	//�C�x���g����
//	switch(msg){
//		case WM_DESTROY:
//			//�E�B���h�E������ꂽ��v���O�������I������
//			PostQuitMessage(NULL);
//			break;
//		default:
//			//�V�X�e���ɃC�x���g�����𓊂���
//			return (DefWindowProc(hWnd, msg, wParam, lParam));
//	}
//
//	return 0;
//}
//
//bool Window::OriginalCreateWindow(){
//
//	HINSTANCE hInstance = GetModuleHandle(NULL);		//�C���X�^���X�n���h�����擾
//
//	WNDCLASS wc;		//�o�^��������i�[����\����
//
//#pragma region �ǂ̂悤�ȃE�B���h�E���쐬���邩
//	wc.cbClsExtra = 0;											//�\���̂̃T�C�Y���g������o�C�g��
//	wc.cbWndExtra = 0;											//�E�B���h�E�̃T�C�Y���g������o�C�g��
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//�E�B���h�E�̔w�i��h��Ԃ��u���V
//	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);				//�E�B���h�E��Ƀ}�E�X�J�[�\���������ꍇ�̃}�E�X�̌`��
//	wc.hIcon = NULL;											//�E�B���h�E�̃A�C�R���iLoadImage()�ł��Ă��悢�j
//	wc.hInstance = hInstance;									//�E�B���h�E����邽�߂̃C���X�^���X�n���h�����w��
//	wc.lpfnWndProc = WndProc;								//�E�B���h�E����ʒm���ꂽ�C�x���g���������邽�߂̊֐����w��
//	wc.lpszClassName = className;								//�o�^����E�B���h�E�̃N���X��
//	wc.lpszMenuName = NULL;										//���j���[�̃��\�[�XID
//	wc.style = NULL;											//�E�B���h�E�N���X�̃X�^�C��
//
//	//�E�B���h�E�̓o�^�Ɏ��s�����ꍇ�I��������
//	if(RegisterClass(&wc) == NULL){
//		return false;
//	}
//#pragma endregion
//
//#pragma region �E�B���h�E�̍쐬
//	HWND hWnd = CreateWindow(
//		wc.lpszClassName,							//�o�^����Ă���N���X��
//		windowName,									//�E�B���h�E�̃^�C�g��
//		(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),	//�E�B���h�E�̃X�^�C��(�^�C�g���A�V�X�e���A�ŏ����g�p)
//		CW_USEDEFAULT,								//�E�B���h�E��x�ʒu(�V�X�e���W���l���g�p)
//		CW_USEDEFAULT,								//�E�B���h�E��y�ʒu
//		widthSize,									//�E�B���h�E�̕�
//		heightSize,									//�E�B���h�E�̍���
//		NULL,										//�e�E�B���h�E�̃n���h��
//		NULL,										//���j���[�n���h��
//		hInstance,
//		NULL,										//�E�B���h�E�쐬���̃C�x���g�֓n���f�[�^�̃|�C���^
//		);
//
//	//�E�B���h�E�T�C�Y�̒���
//	RECT r1, r2;
//
//	GetClientRect(hWnd, &r1);
//	GetWindowRect(hWnd, &r2);
//	MoveWindow(
//		hWnd, r2.left, r2.top,
//		widthSize + ((r2.right - r2.left) - (r1.right - r1.left)),
//		heightSize + ((r2.bottom - r2.top) - (r1.bottom - r1.top)),
//		false
//	);
//#pragma endregion
//
//}
//
//bool Window::ProcessLoop(){
//
//	MSG msg;
//
//	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
//		if(msg.message == WM_QUIT){
//			return false;
//		}
//
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	return true;
//}