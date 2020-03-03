/**
* @file Application.cpp
*/
#include "Command.h"
#include "Application.h"

//////////////ここから下は自分で実装////////////////


// 一度タイトル画面を表示するとfalseになる.
bool title_flag = true;

//じゃんけんの手  選ばれたのがグーなら0が、チョキなら1が、パーなら2
int player_hand = 0, cpu_hand = 0;

// 前回「あいこ」のときtrue、そうでなければfalseが格納される.
bool aiko_flag = false;

// 勝ち回数.
int player_win_count = 0, cpu_win_count = 0;

enum imageNumber {  //画像の管理番号Enum、0が最背面
    BACKGROUND,
    WINLOGO,
    LOSELOGO,
    PLAYERHAND,
    CPUHAND,
    PLAYERIMAGE,
    CPUIMAGE,
    AIKODEIMAGE,
    JANKENIMAGE,
    PONIMAGE,
    SYOIMAGE,
    TITLELOGO,
};

//ファイルパスを定義
const char BackGround[] = "Images/BackGround/BG_Battle.jpg";
const char IMG_Gu[] = "Images/IMG_gu.png";
const char IMG_Tyoki[] = "Images/IMG_tyoki.png";
const char IMG_Pa[] = "Images/IMG_pa.png";
const char BGM_Battle[] = "Sounds/BGM_Battle.mp3";
const char SE_PushButton[] = "Sounds/SE_PushButton.mp3";

/**
* アプリケーションの本体.
*/
void application()
{
    // タイトル画面
    if (title_flag) {
        title_flag = false;
        set_image(imageNumber::BACKGROUND, 0, 0, BackGround);  //背景画像を表示
        set_image(imageNumber::PLAYERIMAGE, 270, -270, "Images/IMG_Player.png");  //プレイヤーの画像を表示
        set_image(imageNumber::CPUIMAGE, -270, -300, "Images/IMG_CPU.png");  //CPUの画像を表示
        set_image(imageNumber::TITLELOGO, 0, 900, "Logos/Logo_GODJANKEN.png");  //   //タイトルロゴ]
        move_image(imageNumber::TITLELOGO, 0, 100, 1, 3);  //タイトルロゴを動かす
        play_bgm(BGM_Battle);  //BGM再生
        set_bgm_volume(0.25f);
        fade_in(2.0f);
        const int yes_or_no = select(-120, -150, 2, "じゃんけんをはじめる", "やめる");
        play_sound(SE_PushButton);
        reset_image(imageNumber::TITLELOGO);  //タイトルロゴを削除
        if (yes_or_no == 1) {
            Finish();
        }
    }

    //  １試合ごとに更新
    set_text(150, -100, "プレイヤー(%d勝)", player_win_count);  //プレイヤーの勝利数を表示
    set_text(-320, -100, "CPU(%d勝)", cpu_win_count);  //CPUの勝利数を表示

    //  プレイヤーの手とCPUの手を選択
    ChooseHand();

  // あいこフラグがtrueなら"あいこで"画像を表示. falseなら"じゃんけん"画像を表示
    {
        if (aiko_flag) {
            set_image(imageNumber::AIKODEIMAGE, 0, 900, "Images/IMG_aikode.png");
            move_image(imageNumber::AIKODEIMAGE, 0, 0, 4, 1);
            play_sound("Sounds/SE_Aikode.mp3");
            wait(1.5f);
            reset_image(imageNumber::AIKODEIMAGE);
        }
        else if (!aiko_flag) {
            wait(1.0f); // 3秒間待つ.
            set_text(-150, -100, "勝負を続けますか？");
            const int yes_or_no = select(-120, -150, 2, "続ける", "やめる");
            play_sound(SE_PushButton);

            // "やめる"が選ばれたらアプリケーションを終了する.
            if (yes_or_no == 1) {
                Finish();
            }
        }
    }

    reset_image(imageNumber::PLAYERHAND);
    reset_image(imageNumber::CPUHAND);
    reset_image(imageNumber::WINLOGO);
    reset_image(imageNumber::LOSELOGO);
    reset_all_text();
}  //application関数終わり

/**
*  じゃんけんの手を選ぶ
*/
void ChooseHand()
{
    set_text(-120, -100, "手を選べ");
    // プレイヤーの手を選ぶ。選ばれたのがグーなら0が、チョキなら1が、パーなら2がplayer_handに格納される.
    int player_hand = select(-120, -150, 3, "グー", "チョキ", "パー");
    play_sound(SE_PushButton);
    reset_all_text();
    set_text(150, -100, "プレイヤー(%d勝)", player_win_count);  //プレイヤーの勝利数を表示
    set_text(-320, -100, "CPU(%d勝)", cpu_win_count);  //CPUの勝利数を表示

    // CPUの手を選ぶ.
    int cpu_hand = random(0, 2);

    set_image(imageNumber::JANKENIMAGE, 0, 0, "Images/IMG_janken.png");
    play_sound("Sounds/SE_Janken.mp3");
    wait(1.0f);
    reset_image(imageNumber::JANKENIMAGE);
    set_image(imageNumber::PONIMAGE, 0, 0, "Images/IMG_pon.png");
    play_sound("Sounds/SE_Janken.mp3");
    wait(1.0f);
    reset_image(imageNumber::PONIMAGE);
    play_sound("Sounds/SE_Janken.mp3");

    // 右側にプレイヤーの手を表示
    switch (player_hand) {
    case 0:
        set_image(imageNumber::PLAYERHAND, 200, 170, IMG_Gu);
        break;
    case 1:
        set_image(imageNumber::PLAYERHAND, 200, 170, IMG_Tyoki);
        break;
    case 2:
        set_image(imageNumber::PLAYERHAND, 200, 170, IMG_Pa);
        break;
    }

    // 左側にCPUの手を表示
    switch (cpu_hand) {
    case 0: set_image(imageNumber::CPUHAND, -200, 170, IMG_Gu); break;
    case 1: set_image(imageNumber::CPUHAND, -200, 170, IMG_Tyoki); break;
    case 2: set_image(imageNumber::CPUHAND, -200, 170, IMG_Pa); break;
    }

    wait(1.0f);
    if ((player_hand == 0 && cpu_hand == 1) || (player_hand == 1 && cpu_hand == 2) || (player_hand == 2 && cpu_hand == 0)) {  //プレイヤーの勝ち条件
        set_image(imageNumber::WINLOGO, 50, 0, "Images/IMG_win.png");
        play_sound("Sounds/SE_Win.mp3");
        player_win_count += 1; // プレイヤーの勝利数を1増やす.
        aiko_flag = false;
    }
    else if ((player_hand == 0 && cpu_hand == 2) || (player_hand == 1 && cpu_hand == 0) || (player_hand == 2 && cpu_hand == 1)) {  //プレイヤーの負け条件
        set_image(imageNumber::LOSELOGO, 50, 0, "Images/IMG_lose.png");
        play_sound("Sounds/SE_Lose.mp3");
        cpu_win_count += 1; // CPUの勝利数を1増やす.
        aiko_flag = false;
    }
    else {  //あいこ条件
        aiko_flag = true;
    }
}

/**
*  終了処理
*/
void Finish()
{
    set_sound_volume(0.5f);
    play_sound("Sounds/SE_Finish.mp3");
    fade_out(0, 0, 0, 1.5f);
    quit(); // アプリケーションを終了させる.
}