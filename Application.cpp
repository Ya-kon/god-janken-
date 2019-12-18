/**
* @file Application.cpp
*/
#include "Command.h"

// 一度タイトル画面を表示するとfalseになる.
bool title_flag = true;

// 前回「あいこ」のときtrue、そうでなければfalseが格納される.
// trueは「真」、falseは「偽」という意味.
// ひとつのイコール記号は代入を意味する.
bool aiko_flag = false;

// プレイヤーの勝ち回数.
int player_win_count = 0;

// CPUの勝ち回数.
int cpu_win_count = 0;

//ダンジョンの大きさ
const int dungeon_widith = 8;
const int dungeon_height = 8;

/**
*ダンジョンマップ。
*
*０：通路
*１：壁
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

//スタートの位置。
const int start_x = 1;
const int start_y = 1;

//ゴールの位置。
const int goal_x = 3;
const int goal_y = 1;

//プレイヤーの現在地。
int player_x;
int player_y;

//プレイヤーの向き
const int dir_up = 0;
const int dir_right = 1;
const int dir_down = 2;
const int dir_left = 3;
int player_direction;



/**
* アプリケーションの本体.
*/
void application()
{
 
  // タイトル画面を表示
  if (title_flag) {
    title_flag = false;
   /*
    * この下にタイトル画面のプログラムを追加します.
    */
	set_image(101, 0, 800, "Cool Text - god janken 289545410775237.png");
	move_image(101, 0, 100,1, 3);
	set_image(102, 150, -100, "kami.jpg");

  }

  // 背景を表示.
  set_image(0, 0, 0, "battle_haikei100.jpg"); 
  set_text(-360, 260, "神(%d勝)", player_win_count);
  set_text(40, 260, "悪魔(%d勝)", cpu_win_count);

  // あいこフラグがtrueなら"あいこで"画像を表示. falseなら"じゃんけん"画像を表示.
  if (aiko_flag) {
    set_image(1, 0, 400, "janken_aikode.png");
  } else {
    set_image(1, 0, 0, "battle_haikei100.jpg");
  }
  play_bgm("bgm_maoudamashii_fantasy13.mp3");
  

  set_text(-360, 0, "攻撃を選べ");

  // プレイヤーの手を選んでもらう.
  // 選ばれたのがグーなら0が、チョキなら1が、パーなら2がplayer_handに格納される.
  const int player_hand = select(-360, -40, 3, "爆炎", "ハリケーン", "アクア");

  // CPUの手を選ぶ.
  // 選んだのがグーなら0が、チョキなら1が、パーなら2がcpu_handに格納される.
  const int cpu_hand = random(0, 2); // 0～2のいずれかの整数が無作為に選ばれる.


  reset_image(1);
  // "ほい!"

  // 左側にプレイヤーの手を表示
  switch (player_hand) {
  case 0: set_image(2, -200, 100, "ダウンロード.jfif");
	  play_sound("se_maoudamashii_element_fire12.mp3"); break;
  case 1: set_image(2, -200, 100, "images (1).jfif");
	  play_sound("harikenn.mp3"); break;
  case 2: set_image(2, -200, 100, "kougeki_mizujfif.jfif");
	  play_sound("koori.mp3"); break;
  }
  scale_image(2, 0, 0, 0, 0);
  scale_image(2, 1, 1, 4, 0.25f);

  // 右側にCPUの手を表示
  switch (cpu_hand) {
  case 0: set_image(3, 200, 100, "ダウンロード.jfif"); break;
  case 1: set_image(3, 200, 100, "images (1).jfif"); break;
  case 2: set_image(3, 200, 100, "kougeki_mizujfif.jfif"); break;
  }
  scale_image(3, 0, 0, 0, 0);
  scale_image(3, 1, 1, 4, 0.25f);

  play_sound("kotsudumi1.mp3");
  wait(2); // 2秒間待つ

  // 数値の比較は二重のイコール記号「==」で行う.
  // 「&&」は「且つ」、「||」は「又は」という意味を持つ記号.
  // 式の優先順位を調整するには算数と同様にカッコ「()」を使う.
  // グーは0、チョキは1、パーは2なので、例えばプレイヤーの手が0(グー)でCPUの手が1(チョキ)なら、プレイヤーの勝ちとなる.
  // 勝ったり負けたりした場合は「あいこ」じゃないのでaiko_flagを「偽」にしておく.
  // 勝ってもいないし負けてもいない場合は「あいこ」なのでaiko_flagを「真」にしておく.
  if ((player_hand == 0 && cpu_hand == 1) || (player_hand == 1 && cpu_hand == 2) || (player_hand == 2 && cpu_hand == 0)) {
    play_sound("correct4.mp3");
    set_image(4, 0, -150, "janken_kachi.png");
    player_win_count += 1; // プレイヤーの勝利数を1増やす.
    aiko_flag = false;
  } else if ((player_hand == 0 && cpu_hand == 2) || (player_hand == 1 && cpu_hand == 0) || (player_hand == 2 && cpu_hand == 1)) {
    play_sound("incorrect1.mp3");
    set_image(4, 0, -150, "janken_make.png");
    cpu_win_count += 1; // CPUの勝利数を1増やす.
    aiko_flag = false;
  } else {
    play_sound("stupid2.mp3");
    aiko_flag = true;
  }

  reset_all_text(); // いったんすべての文字を消す.

  // 勝利回数が変化した可能性があるので表示しなおす.
  set_text(-360, 260, "あなた(%d勝)", player_win_count);
  set_text(40, 260, "CPU(%d勝)", cpu_win_count);

  // 「あいこ」だった場合は自動的に勝負を継続する.
  if (aiko_flag == false) {
    wait(3); // 3秒間待つ.
    set_text(-360, -40, "勝負を続けますか？");
    const int yes_or_no = select(-360, -80, 2, "続ける", "やめる");
    play_sound("stupid2.mp3");
    // "やめる"が選ばれたらアプリケーションを終了する.
    if (yes_or_no == 1) {
      fade_out(0, 0, 0, 1);
      quit(); // アプリケーションを終了させる.
    }
  }
  reset_all_image(); // 次の勝負に備えてすべての画像を消す.
  reset_all_text(); // 次の勝負に備えてすべての文字を消す.
}