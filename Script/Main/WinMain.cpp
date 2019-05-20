#include "../DirectX/DirectX.h"
#include "../Task/GameManager.h"

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
	//プログラム終了時に解放していないメモリがあれば警告を出す
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//時間計測を1ミリ秒単位に設定
	//timeBeginPeriod(1);

	DirectX window;
	window.SetWindowName(_T("テストだよ"));
	if(!window.WindowInit()){
		return -1;
	}

	window.DxInit();
	
	GameManager gameManager;

	gameManager.Init();

	while(window.Process()){

		gameManager.Update();
		gameManager.Draw();

	}

	gameManager.Delete();
	window.DxEnd();

	return 0;
}