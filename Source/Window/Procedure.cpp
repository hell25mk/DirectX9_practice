#include "Window.h"

/// /// <summary>
/// �E�B���h�E�C�x���g����������static�Ȋ֐�
/// </summary>
/// <param name="hWnd">�C�x���g�����������E�B���h�E�n���h��</param>
/// <param name="msg">���������C�x���g���e</param>
/// <param name="wParam">�C�x���g����ʒm���ꂽ�f�[�^</param>
/// <param name="lParam">�C�x���g����ʒm���ꂽ�f�[�^</param>
/// <returns></returns>
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){

	//�v���V�[�W���[�̃A�h���X���擾
	Window* instance = (Window*)GetWindowLong(hWnd, GWL_USERDATA);

	if(!instance){
		if(msg == WM_CREATE){
			instance = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			if(instance){
				//GWL_USERDATA(�D���Ɏg���Ă悢�̈�)��this�|�C���^������
				SetWindowLong(hWnd, GWL_USERDATA, (LONG)instance);
			}
		}
	} else{
		return instance->Procedure(hWnd, msg, wParam, lParam);
	}

	return (DefWindowProc(hWnd, msg, wParam, lParam));
}

/// /// <summary>
/// �E�B���h�E�C�x���g����������
/// </summary>
/// <param name="hWnd">�C�x���g�����������E�B���h�E�n���h��</param>
/// <param name="msg">���������C�x���g���e</param>
/// <param name="wParam">�C�x���g����ʒm���ꂽ�f�[�^</param>
/// <param name="lParam">�C�x���g����ʒm���ꂽ�f�[�^</param>
/// <returns>�C�x���g�ɉ�����������Ԃ�</returns>
LRESULT CALLBACK Window::Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){

	switch(msg){
		case WM_CLOSE:
			WindowClose();
			return 0;
		case WM_RBUTTONUP:
			DestroyWindow(hWnd);
			PostQuitMessage(NULL);
			return 0;
		/*default:
			//�V�X�e���ɃC�x���g�����𓊂���
			return (DefWindowProc(hWnd, msg, wParam, lParam));*/
	}

	//�V�X�e���ɃC�x���g�����𓊂���
	return (DefWindowProc(hWnd, msg, wParam, lParam));
}

/// <summary>
/// �E�B���h�E�̏������s��
/// </summary>
/// <returns>
/// false QUIT���b�Z�[�W�Atrue ����ȊO
/// </returns>
bool Window::Process() const{

	MSG msg;

	//�E�B���h�E�ɒʒB����悤�Ƃ��Ă���C�x���g���擾
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
		if(msg.message == WM_QUIT){
			return false;
		}

		TranslateMessage(&msg);	//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
		DispatchMessage(&msg);	//�E�B���h�E�C�x���g��ʒB
	}

	return true;
}