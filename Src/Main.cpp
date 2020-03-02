/**
* @file Main.cpp
*/
#include <objbase.h>
#include <iostream>

/////�w�Z�񋟃w�b�_�[//////////
#include "Audio.h"
#include "GLFWEW.h"
//////////////////////////////


///////////�������牺�͎����Ŏ���////////////////////


extern bool hasQuitRequest;  //�O�������P�[�W�̃O���[�o���ϐ�������

//namespace  ���O�Ȃ��Œ�`
void initialize();
void application();

/**
* �v���O�����̃G���g���[�|�C���g.
*/
int main()
{
  //����������
  {
		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

		GLFWEW::Window& window = GLFWEW::Window::Instance();

	  if (!window.Init(800, 600, "GOD JANKEN!!")) {
		  return 1;
	  }

	  if (!Audio::Engine::Get().Initialize()) {
		  std::cerr << "Audio Engine�̏������Ɏ��s." << std::endl;
	  }

	  initialize();  //�w�Z�񋟃��C�u������������
  }

  //�Q�[���X�V
  while (!hasQuitRequest) {
	  application();
  }

  //�I������
  {
	  Audio::Engine::Get().Destroy();
	  CoUninitialize();
	  std::cout << "Finish." << std::endl;
  }

}