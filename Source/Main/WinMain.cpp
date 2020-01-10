#include "../DirectX/DirectX.h"
#include "../Task/GameManager.h"
#include "../Sound/DxSound.h"

/// <summary>
/// メイン(ANSIとUnicode両方に対応するために_tを付けている)
/// 引数の注釈設定をしワーニング回避している
/// </summary>
/// <param name="hInstance">プログラムを識別するためのハンドル</param>
/// <param name="hPrevInstance">Win16の産物のため常にnull</param>
/// <param name="lpszCmdLine">コマンドラインから受け取った引数</param>
/// <param name="nCmdShow">アプリケーションの初期表示方法</param>
/// <returns></returns>
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpszCmdLine, _In_ int nCmdShow){

#ifdef _DEBUG
	//プログラム終了時に解放していないメモリがあれば警告を出す
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//時間計測を1ミリ秒単位に設定
	timeBeginPeriod(1);

	DirectX dxWindow;
	dxWindow.SetWindowTitle(_T("DirectX9 テストプロジェクト"));
	if(!dxWindow.WindowInit()){
		return -1;
	}

	dxWindow.DxInit();
	
	GameManager gameManager;
	gameManager.Init();

	while(dxWindow.Process()){

		gameManager.Update();

	}

	gameManager.Release();
	dxWindow.DxEnd();

	return 0;
}