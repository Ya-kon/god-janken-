/**
* @file Application.cpp
*/
#include "Command.h"

// ��x�^�C�g����ʂ�\�������false�ɂȂ�.
bool title_flag = true;

// �O��u�������v�̂Ƃ�true�A�����łȂ����false���i�[�����.
// true�́u�^�v�Afalse�́u�U�v�Ƃ����Ӗ�.
// �ЂƂ̃C�R�[���L���͑�����Ӗ�����.
bool aiko_flag = false;

// �v���C���[�̏�����.
int player_win_count = 0;

// CPU�̏�����.
int cpu_win_count = 0;

//�_���W�����̑傫��
const int dungeon_widith = 8;
const int dungeon_height = 8;

/**
*�_���W�����}�b�v�B
*
*�O�F�ʘH
*�P�F��
*/
const char dungeon_map[dungeon_height][dungeon_widith] = {
	{ 1,1,1,1,1,1,1,1, },
{ 1,0,1,0,0,0,0,1, },
{ 1,0,1,1,1,0,1,1, },
{ 1,0,0,0,1,0,0,1, },
{ 1,0,1,0,1,1,0,1, },
{ 1,1,1,0,0,0,0,1, },
{ 1,0,0,0,1,0,1,1, },
{ 1,1,1,1,1,1,1,1, },
};

//�X�^�[�g�̈ʒu�B
const int start_x = 1;
const int start_y = 1;

//�S�[���̈ʒu�B
const int goal_x = 3;
const int goal_y = 1;

//�v���C���[�̌��ݒn�B
int player_x;
int player_y;

//�v���C���[�̌���
const int dir_up = 0;
const int dir_right = 1;
const int dir_down = 2;
const int dir_left = 3;
int player_direction;



/**
* �A�v���P�[�V�����̖{��.
*/
void application()
{
 
  // �^�C�g����ʂ�\��
  if (title_flag) {
    title_flag = false;
   /*
    * ���̉��Ƀ^�C�g����ʂ̃v���O������ǉ����܂�.
    */
	set_image(101, 0, 800, "Cool Text - god janken 289545410775237.png");
	move_image(101, 0, 100,1, 3);
	set_image(102, 150, -100, "kami.jpg");

  }

  // �w�i��\��.
  set_image(0, 0, 0, "battle_haikei100.jpg"); 
  set_text(-360, 260, "�_(%d��)", player_win_count);
  set_text(40, 260, "����(%d��)", cpu_win_count);

  // �������t���O��true�Ȃ�"��������"�摜��\��. false�Ȃ�"����񂯂�"�摜��\��.
  if (aiko_flag) {
    set_image(1, 0, 400, "janken_aikode.png");
  } else {
    set_image(1, 0, 0, "battle_haikei100.jpg");
  }
  play_bgm("bgm_maoudamashii_fantasy13.mp3");
  

  set_text(-360, 0, "�U����I��");

  // �v���C���[�̎��I��ł��炤.
  // �I�΂ꂽ�̂��O�[�Ȃ�0���A�`���L�Ȃ�1���A�p�[�Ȃ�2��player_hand�Ɋi�[�����.
  const int player_hand = select(-360, -40, 3, "����", "�n���P�[��", "�A�N�A");

  // CPU�̎��I��.
  // �I�񂾂̂��O�[�Ȃ�0���A�`���L�Ȃ�1���A�p�[�Ȃ�2��cpu_hand�Ɋi�[�����.
  const int cpu_hand = random(0, 2); // 0�`2�̂����ꂩ�̐���������ׂɑI�΂��.


  reset_image(1);
  // "�ق�!"

  // �����Ƀv���C���[�̎��\��
  switch (player_hand) {
  case 0: set_image(2, -200, 100, "�_�E�����[�h.jfif");
	  play_sound("se_maoudamashii_element_fire12.mp3"); break;
  case 1: set_image(2, -200, 100, "images (1).jfif");
	  play_sound("harikenn.mp3"); break;
  case 2: set_image(2, -200, 100, "kougeki_mizujfif.jfif");
	  play_sound("koori.mp3"); break;
  }
  scale_image(2, 0, 0, 0, 0);
  scale_image(2, 1, 1, 4, 0.25f);

  // �E����CPU�̎��\��
  switch (cpu_hand) {
  case 0: set_image(3, 200, 100, "�_�E�����[�h.jfif"); break;
  case 1: set_image(3, 200, 100, "images (1).jfif"); break;
  case 2: set_image(3, 200, 100, "kougeki_mizujfif.jfif"); break;
  }
  scale_image(3, 0, 0, 0, 0);
  scale_image(3, 1, 1, 4, 0.25f);

  play_sound("kotsudumi1.mp3");
  wait(2); // 2�b�ԑ҂�

  // ���l�̔�r�͓�d�̃C�R�[���L���u==�v�ōs��.
  // �u&&�v�́u���v�A�u||�v�́u���́v�Ƃ����Ӗ������L��.
  // ���̗D�揇�ʂ𒲐�����ɂ͎Z���Ɠ��l�ɃJ�b�R�u()�v���g��.
  // �O�[��0�A�`���L��1�A�p�[��2�Ȃ̂ŁA�Ⴆ�΃v���C���[�̎肪0(�O�[)��CPU�̎肪1(�`���L)�Ȃ�A�v���C���[�̏����ƂȂ�.
  // �������蕉�����肵���ꍇ�́u�������v����Ȃ��̂�aiko_flag���u�U�v�ɂ��Ă���.
  // �����Ă����Ȃ��������Ă����Ȃ��ꍇ�́u�������v�Ȃ̂�aiko_flag���u�^�v�ɂ��Ă���.
  if ((player_hand == 0 && cpu_hand == 1) || (player_hand == 1 && cpu_hand == 2) || (player_hand == 2 && cpu_hand == 0)) {
    play_sound("correct4.mp3");
    set_image(4, 0, -150, "janken_kachi.png");
    player_win_count += 1; // �v���C���[�̏�������1���₷.
    aiko_flag = false;
  } else if ((player_hand == 0 && cpu_hand == 2) || (player_hand == 1 && cpu_hand == 0) || (player_hand == 2 && cpu_hand == 1)) {
    play_sound("incorrect1.mp3");
    set_image(4, 0, -150, "janken_make.png");
    cpu_win_count += 1; // CPU�̏�������1���₷.
    aiko_flag = false;
  } else {
    play_sound("stupid2.mp3");
    aiko_flag = true;
  }

  reset_all_text(); // �������񂷂ׂĂ̕���������.

  // �����񐔂��ω������\��������̂ŕ\�����Ȃ���.
  set_text(-360, 260, "���Ȃ�(%d��)", player_win_count);
  set_text(40, 260, "CPU(%d��)", cpu_win_count);

  // �u�������v�������ꍇ�͎����I�ɏ������p������.
  if (aiko_flag == false) {
    wait(3); // 3�b�ԑ҂�.
    set_text(-360, -40, "�����𑱂��܂����H");
    const int yes_or_no = select(-360, -80, 2, "������", "��߂�");
    play_sound("stupid2.mp3");
    // "��߂�"���I�΂ꂽ��A�v���P�[�V�������I������.
    if (yes_or_no == 1) {
      fade_out(0, 0, 0, 1);
      quit(); // �A�v���P�[�V�������I��������.
    }
  }
  reset_all_image(); // ���̏����ɔ����Ă��ׂẲ摜������.
  reset_all_text(); // ���̏����ɔ����Ă��ׂĂ̕���������.
}