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
///// @brief ウィンドウイベントを処理する
///// </summary>
///// <param name="hWnd">イベントが発生したウィンドウハンドル</param>
///// <param name="msg">発生したイベント内容</param>
///// <param name="wParam">イベントから通知されたデータ</param>
///// <param name="lParam">イベントから通知されたデータ</param>
///// <returns></returns>
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
//
//	//イベント処理
//	switch(msg){
//		case WM_DESTROY:
//			//ウィンドウが閉じられたらプログラムを終了する
//			PostQuitMessage(NULL);
//			break;
//		default:
//			//システムにイベント処理を投げる
//			return (DefWindowProc(hWnd, msg, wParam, lParam));
//	}
//
//	return 0;
//}
//
//bool Window::OriginalCreateWindow(){
//
//	HINSTANCE hInstance = GetModuleHandle(NULL);		//インスタンスハンドルを取得
//
//	WNDCLASS wc;		//登録する情報を格納する構造体
//
//#pragma region どのようなウィンドウを作成するか
//	wc.cbClsExtra = 0;											//構造体のサイズを拡張するバイト数
//	wc.cbWndExtra = 0;											//ウィンドウのサイズを拡張するバイト数
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//ウィンドウの背景を塗りつぶすブラシ
//	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);				//ウィンドウ上にマウスカーソルが来た場合のマウスの形状
//	wc.hIcon = NULL;											//ウィンドウのアイコン（LoadImage()でつけてもよい）
//	wc.hInstance = hInstance;									//ウィンドウを作るためのインスタンスハンドルを指定
//	wc.lpfnWndProc = WndProc;								//ウィンドウから通知されたイベントを処理するための関数を指定
//	wc.lpszClassName = className;								//登録するウィンドウのクラス名
//	wc.lpszMenuName = NULL;										//メニューのリソースID
//	wc.style = NULL;											//ウィンドウクラスのスタイル
//
//	//ウィンドウの登録に失敗した場合終了させる
//	if(RegisterClass(&wc) == NULL){
//		return false;
//	}
//#pragma endregion
//
//#pragma region ウィンドウの作成
//	HWND hWnd = CreateWindow(
//		wc.lpszClassName,							//登録されているクラス名
//		windowName,									//ウィンドウのタイトル
//		(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),	//ウィンドウのスタイル(タイトル、システム、最小化使用)
//		CW_USEDEFAULT,								//ウィンドウのx位置(システム標準値を使用)
//		CW_USEDEFAULT,								//ウィンドウのy位置
//		widthSize,									//ウィンドウの幅
//		heightSize,									//ウィンドウの高さ
//		NULL,										//親ウィンドウのハンドル
//		NULL,										//メニューハンドル
//		hInstance,
//		NULL,										//ウィンドウ作成時のイベントへ渡すデータのポインタ
//		);
//
//	//ウィンドウサイズの調整
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