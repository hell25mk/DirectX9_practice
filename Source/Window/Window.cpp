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

	DestroyWindow(windowObject.hWnd);		//Windowの破棄
	//MessageBox(NULL, _T("ウィンドウを削除しました"), _T("メッセージ"), MB_OK);

}

/// <summary>
/// ウィンドウを生成するクラス
/// </summary>
/// <returns>生成に成功したか失敗したか</returns>
bool Window::WindowInit(){

#pragma region どのようなウィンドウを作成するか
	windowClass.cbClsExtra = 0;												//構造体のサイズを拡張するバイト数
	windowClass.cbWndExtra = 0;												//ウィンドウのサイズを拡張するバイト数
	windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);		//ウィンドウの背景を塗りつぶすブラシ
	windowClass.hCursor = LoadCursor(windowObject.hInstance, IDC_ARROW);	//ウィンドウ上にマウスカーソルが来た場合のマウスの形状
	windowClass.hIcon = NULL;												//ウィンドウのアイコン（LoadImage()でつけてもよい）
	windowClass.hInstance = windowObject.hInstance;							//ウィンドウを作るためのインスタンスハンドルを指定
	windowClass.lpfnWndProc = WndProc;										//ウィンドウから通知されたイベントを処理するための関数を指定
	windowClass.lpszClassName = _T("WindowsAPI");							//登録するウィンドウのクラス名
	windowClass.lpszMenuName = NULL;										//メニューのリソースID
	windowClass.style = NULL;												//ウィンドウクラスのスタイル

	//ウィンドウの登録に失敗した場合終了させる
	if(!RegisterClass(&windowClass)){
		MessageBox(NULL, _T("ウィンドウの登録に失敗しました"), _T("エラー"), MB_OK);
		return false;
	}
#pragma endregion

#pragma region ウィンドウの作成
	windowObject.hWnd = CreateWindow(
		windowClass.lpszClassName,						//登録されているクラス名
		windowTitle,										//ウィンドウのタイトル
		(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),		//ウィンドウのスタイル(タイトル、システム、最小化使用)
		CW_USEDEFAULT,									//ウィンドウのx位置(システム標準値を使用)
		CW_USEDEFAULT,									//ウィンドウのy位置
		widthSize,										//ウィンドウの幅
		heightSize,										//ウィンドウの高さ
		NULL,											//親ウィンドウのハンドル
		NULL,											//メニューハンドル
		windowObject.hInstance,
		this											//ウィンドウ作成時のイベントへ渡すデータのポインタ(メンバProcedureを使用するためthisポインタを入れている)
		);

	if(!windowObject.hWnd){
		MessageBox(NULL, _T("ウィンドウの生成に失敗しました"), _T("エラー"), MB_OK);
		return false;
	}

	//ウィンドウサイズの調整
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

	//MessageBox(windowObject.hWnd, _T("ウィンドウを生成しました"), _T("メッセージ"), MB_OK);

	return true;
}