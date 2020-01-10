#include "Window.h"

/// /// <summary>
/// ウィンドウイベントを処理するstaticな関数
/// </summary>
/// <param name="hWnd">イベントが発生したウィンドウハンドル</param>
/// <param name="msg">発生したイベント内容</param>
/// <param name="wParam">イベントから通知されたデータ</param>
/// <param name="lParam">イベントから通知されたデータ</param>
/// <returns></returns>
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){

	//プロシージャーのアドレスを取得
	Window* instance = (Window*)GetWindowLong(hWnd, GWL_USERDATA);

	if(!instance){
		if(msg == WM_CREATE){
			instance = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			if(instance){
				//GWL_USERDATA(好きに使ってよい領域)にthisポインタを入れる
				SetWindowLong(hWnd, GWL_USERDATA, (LONG)instance);
			}
		}
	} else{
		return instance->Procedure(hWnd, msg, wParam, lParam);
	}

	return (DefWindowProc(hWnd, msg, wParam, lParam));
}

/// /// <summary>
/// ウィンドウイベントを処理する
/// </summary>
/// <param name="hWnd">イベントが発生したウィンドウハンドル</param>
/// <param name="msg">発生したイベント内容</param>
/// <param name="wParam">イベントから通知されたデータ</param>
/// <param name="lParam">イベントから通知されたデータ</param>
/// <returns>イベントに応じた処理を返す</returns>
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
			//システムにイベント処理を投げる
			return (DefWindowProc(hWnd, msg, wParam, lParam));*/
	}

	//システムにイベント処理を投げる
	return (DefWindowProc(hWnd, msg, wParam, lParam));
}

/// <summary>
/// ウィンドウの処理を行う
/// </summary>
/// <returns>
/// false QUITメッセージ、true それ以外
/// </returns>
bool Window::Process() const{

	MSG msg;

	//ウィンドウに通達されようとしているイベントを取得
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
		if(msg.message == WM_QUIT){
			return false;
		}

		TranslateMessage(&msg);	//仮想キーメッセージを文字メッセージへ変換
		DispatchMessage(&msg);	//ウィンドウイベントを通達
	}

	return true;
}