/**
* @file Main.cpp
*/
#include <objbase.h>
#include "Audio.h"
#include "GLFWEW.h"
#include <iostream>

extern bool hasQuitRequest;
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

	  if (!window.Init(800, 600, "OpenGL 2D JankenGame")) {
		  return 1;
	  }

	  if (!Audio::Engine::Get().Initialize()) {
		  std::cerr << "Audio Engineの初期化に失敗." << std::endl;
	  }

	  initialize();
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