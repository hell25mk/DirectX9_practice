#include "Window.h"

/// /// <summary>
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