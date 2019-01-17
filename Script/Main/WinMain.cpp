#include "../BaseObject/BaseObject.h"
#include "GameMain.h"
#include "../Object/SoccerBall/SoccerBall.h"
#include "../Font/DxFontTest.h"
#include "../Object/Runner/Runner.h"

//コンパイル時定数
namespace{
	static const _TCHAR* Window_ClassName = _T("Game");
	static const  _TCHAR* Window_TitleName = _T("クラスまみれ");

	constexpr int Window_Width = 640;
	constexpr int Window_Height = 480;
}

/// <summary>
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

/// <summary>
/// @brief メイン(ANSIとUnicode両方に対応するために_tを付けている)
/// </summary>
/// <param name="hInstance">プログラムを識別するためのハンドル</param>
/// <param name="hPrevInstance">Win16の産物のため常にnull</param>
/// <param name="lpszCmdLine">コマンドラインから受け取った引数</param>
/// <param name="nCmdShow">アプリケーションの初期表示方法</param>
/// <returns></returns>
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow){

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//時間計測を1ミリ秒単位に設定
	timeBeginPeriod(1);

	WNDCLASS wc;		//登録する情報を格納する構造体

#pragma region どのようなウィンドウを作成するか
	wc.cbClsExtra = 0;											//構造体のサイズを拡張するバイト数
	wc.cbWndExtra = 0;											//ウィンドウのサイズを拡張するバイト数
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//ウィンドウの背景を塗りつぶすブラシ
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);				//ウィンドウ上にマウスカーソルが来た場合のマウスの形状
	wc.hIcon = NULL;											//ウィンドウのアイコン（LoadImage()でつけてもよい）
	wc.hInstance = hInstance;									//ウィンドウを作るためのインスタンスハンドルを指定
	wc.lpfnWndProc = WndProc;									//ウィンドウから通知されたイベントを処理するための関数を指定
	wc.lpszClassName = Window_ClassName;						//登録するウィンドウのクラス名
	wc.lpszMenuName = NULL;										//メニューのリソースID
	wc.style = NULL;											//ウィンドウクラスのスタイル

	//ウィンドウの登録に失敗した場合終了させる
	if(RegisterClass(&wc) == NULL){
		return -1;
	}
#pragma endregion
	
#pragma region ウィンドウの作成
	HWND hWnd = CreateWindow(
		wc.lpszClassName,							//登録されているクラス名
		Window_TitleName,							//ウィンドウのタイトル
		(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),	//ウィンドウのスタイル(タイトル、システム、最小化使用)
		CW_USEDEFAULT,								//ウィンドウのx位置(システム標準値を使用)
		CW_USEDEFAULT,								//ウィンドウのy位置
		Window_Width,								//ウィンドウの幅
		Window_Height,								//ウィンドウの高さ
		NULL,										//親ウィンドウのハンドル
		NULL,										//メニューハンドル
		hInstance,
		NULL,										//ウィンドウ作成時のイベントへ渡すデータのポインタ
	);

	//ウィンドウサイズの調整
	RECT r1, r2;

	GetClientRect(hWnd, &r1);
	GetWindowRect(hWnd, &r2);
	MoveWindow(
		hWnd, r2.left, r2.top,
		Window_Width + ((r2.right - r2.left) - (r1.right - r1.left)),
		Window_Height + ((r2.bottom - r2.top) - (r1.bottom - r1.top)),
		false
	);
#pragma endregion

#pragma region DirectXの初期化
	BaseObject game;

	game.Initialize(hWnd, hInstance);

	//
	game.AppendObject(new TaskHead(), 0, true);
	game.AppendObject(new TaskTail(), INT_MAX, true);

	//1～INT_MAX-1の範囲で優先度を決める
	game.AppendObject(new SoccerBall(), 1, true);
	game.AppendObject(new Runner(), 2, true);
	game.AppendObject(new DxFontTestStart(), 3, true);
#pragma endregion

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);

#pragma region ウィンドウループ
	MSG msg;
	
	while(true){

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT){
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else{
			game.DoAllTasks();
		}

	}
#pragma endregion

#pragma region DirectXオブジェクトの解放
	game.Uninitialize();
#pragma endregion

	return 0;
}