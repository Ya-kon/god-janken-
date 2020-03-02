/**
* @file Main.cpp
*/
#include <objbase.h>
#include <iostream>

/////学校提供ヘッダー//////////
#include "Audio.h"
#include "GLFWEW.h"
//////////////////////////////


///////////ここから下は自分で実装////////////////////


extern bool hasQuitRequest;  //外部リンケージのグローバル変数を扱う

//namespace  名前なしで定義
void initialize();
void application();

/**
* プログラムのエントリーポイント.
*/
int main()
{
  //初期化処理
  {
		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

		GLFWEW::Window& window = GLFWEW::Window::Instance();

	  if (!window.Init(800, 600, "GOD JANKEN!!")) {
		  return 1;
	  }

	  if (!Audio::Engine::Get().Initialize()) {
		  std::cerr << "Audio Engineの初期化に失敗." << std::endl;
	  }

	  initialize();  //学校提供ライブラリを初期化
  }

  //ゲーム更新
  while (!hasQuitRequest) {
	  application();
  }

  //終了処理
  {
	  Audio::Engine::Get().Destroy();
	  CoUninitialize();
	  std::cout << "Finish." << std::endl;
  }

}