#include "Window.h"

/// <summary>
/// �E�B���h�E��j�����邩�ǂ���
/// </summary>
/// <returns>true:�j��,false:�j�����Ȃ�</returns>
bool Window::WindowClose(){

	short onButton = MessageBox(NULL, _T("�I�����܂����H"), _T("���b�Z�[�W"), MB_YESNO | MB_ICONQUESTION);

	if(onButton == IDYES){
		//�E�B���h�E������ꂽ��v���O�������I������
		DestroyWindow(windowObject.hWnd);
		PostQuitMessage(NULL);

		return true;
	}

	return false;
}