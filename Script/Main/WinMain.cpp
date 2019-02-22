#include "../DirectX/DirectX.h"
#include "../BaseObject/BaseObject.h"
#include "GameMain.h"
#include "../Object/SoccerBall/SoccerBall.h"
#include "../Font/DxFontTest.h"
#include "../Object/Runner/Runner.h"

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
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//時間計測を1ミリ秒単位に設定
	//timeBeginPeriod(1);

	DirectX window;
	window.SetWindowName(_T("テストだよ"));
	if(!window.WindowInit()){
		return -1;
	}

#pragma region DirectXの初期化
	/*BaseObject game;

	game.Initialize(hWnd, hInstance);

	//
	game.AppendObject(new TaskHead(), 0, true);
	game.AppendObject(new TaskTail(), INT_MAX, true);

	//1～INT_MAX-1の範囲で優先度を決める
	game.AppendObject(new SoccerBall(), 1, true);
	game.AppendObject(new Runner(), 2, true);
	game.AppendObject(new DxFontTestStart(), 3, true);*/
#pragma endregion

#pragma region ウィンドウループ
	while(window.Process()){



	}
#pragma endregion

#pragma region DirectXオブジェクトの解放
	//game.Uninitialize();
#pragma endregion

	return 0;
}