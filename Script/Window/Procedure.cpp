#include "Window.h"

/// /// <summary>
/// @brief ウィンドウイベントを処理する
/// </summary>
/// <param name="hWnd">イベントが発生したウィンドウハンドル</param>
/// <param name="msg">発生したイベント内容</param>
/// <param name="wParam">イベントから通知されたデータ</param>
/// <param name="lParam">イベントから通知されたデータ</param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){

	//イベント処理
	switch(msg){
		case WM_DESTROY:
			//ウィンドウが閉じられたらプログラムを終了する
			PostQuitMessage(NULL);
			break;
		default:
			//システムにイベント処理を投げる
			return (DefWindowProc(hWnd, msg, wParam, lParam));
	}

	return (0);
}