/**
* @file Application.cpp
*/
#include "Command.h"
#include "Application.h"

//////////////�������牺�͎����Ŏ���////////////////


// ��x�^�C�g����ʂ�\�������false�ɂȂ�.
bool title_flag = true;

//����񂯂�̎�  �I�΂ꂽ�̂��O�[�Ȃ�0���A�`���L�Ȃ�1���A�p�[�Ȃ�2
int player_hand = 0, cpu_hand = 0;

// �O��u�������v�̂Ƃ�true�A�����łȂ����false���i�[�����.
bool aiko_flag = false;

// ������.
int player_win_count = 0, cpu_win_count = 0;

enum imageNumber {  //�摜�̊Ǘ��ԍ�Enum�A0���Ŕw��
    BACKGROUND,
    WINLOGO,
    LOSELOGO,
    PLAYERHAND,
    CPUHAND,
    PLAYERIMAGE,
    CPUIMAGE,
    AIKODEIMAGE,
    TITLELOGO,
};

//�t�@�C���p�X���`
const char BackGround[] = "Images/BackGround/BG_Battle.jpg";
const char BGM_Battle[] = "Sounds/BGM_Battle.mp3";
const char SE_PushButton[] = "Sounds/SE_PushButton.mp3";

/**
* �A�v���P�[�V�����̖{��.
*/
void application()
{
    // �^�C�g�����
    if (title_flag) {
        title_flag = false;
        set_image(imageNumber::BACKGROUND, 0, 0, BackGround);  //�w�i�摜��\��
        set_image(imageNumber::PLAYERIMAGE, 270, -270, "Images/IMG_Player.png");  //�v���C���[�̉摜��\��
        set_image(imageNumber::CPUIMAGE, -270, -300, "Images/IMG_CPU.png");  //CPU�̉摜��\��
        set_image(imageNumber::TITLELOGO, 0, 900, "Logos/Logo_GODJANKEN.png");  //   //�^�C�g�����S
        move_image(imageNumber::TITLELOGO, 0, 200, 1, 3);  //�^�C�g�����S�𓮂���
        play_bgm(BGM_Battle);  //BGM�Đ�
        set_bgm_volume(0.25f);
        const int yes_or_no = select(-120, -150, 2, "����񂯂���͂��߂�", "��߂�");
        play_sound(SE_PushButton);
        reset_image(imageNumber::TITLELOGO);  //�^�C�g�����S���폜
        if (yes_or_no == 1) {
            Finish();
        }
    }

    //  �P�������ƂɍX�V
    set_text(150, -100, "�v���C���[(%d��)", player_win_count);  //�v���C���[�̏�������\��
    set_text(-320, -100, "CPU(%d��)", cpu_win_count);  //CPU�̏�������\��

    //  �v���C���[�̎��CPU�̎��I��
    ChooseHand();

  // �������t���O��true�Ȃ�"��������"�摜��\��. false�Ȃ�"����񂯂�"�摜��\��
    {
        if (aiko_flag) {
            wait(1.0f);
            set_image(imageNumber::AIKODEIMAGE, 0, 900, "janken_aikode.png");
            move_image(imageNumber::AIKODEIMAGE, 0, 0, 4, 1);
            wait(1.0f);
            reset_image(imageNumber::AIKODEIMAGE);
        }
        else if (!aiko_flag) {
            wait(1.0f); // 3�b�ԑ҂�.
            set_text(-120, -100, "�����𑱂��܂����H");
            const int yes_or_no = select(-120, -150, 2, "������", "��߂�");
            play_sound(SE_PushButton);

            // "��߂�"���I�΂ꂽ��A�v���P�[�V�������I������.
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
}  //application�֐��I���

/**
*  ����񂯂�̎��I��
*/
void ChooseHand()
{
    set_text(-120, -100, "��(�U��)��I��");
    // �v���C���[�̎��I�ԁB�I�΂ꂽ�̂��O�[�Ȃ�0���A�`���L�Ȃ�1���A�p�[�Ȃ�2��player_hand�Ɋi�[�����.
    int player_hand = select(-120, -150, 3, "�O�[�F����", "�`���L�F�n���P�[��", "�p�[�F�A�N�A");
    play_sound(SE_PushButton);
    reset_all_text();
    set_text(150, -100, "�v���C���[(%d��)", player_win_count);  //�v���C���[�̏�������\��
    set_text(-320, -100, "CPU(%d��)", cpu_win_count);  //CPU�̏�������\��

    // CPU�̎��I��.
    int cpu_hand = random(0, 2);

    wait(1.0f);

    // �����Ƀv���C���[�̎��\��
    switch (player_hand) {
    case 0:
        set_image(imageNumber::PLAYERHAND, -200, 100, "�_�E�����[�h.jfif");
        break;
    case 1:
        set_image(imageNumber::PLAYERHAND, -200, 100, "images (1).jfif");
        break;
    case 2:
        set_image(imageNumber::PLAYERHAND, -200, 100, "kougeki_mizujfif.jfif");
        break;
    }

    // �E����CPU�̎��\��
    switch (cpu_hand) {
    case 0: set_image(imageNumber::CPUHAND, 200, 100, "�_�E�����[�h.jfif"); break;
    case 1: set_image(imageNumber::CPUHAND, 200, 100, "images (1).jfif"); break;
    case 2: set_image(imageNumber::CPUHAND, 200, 100, "kougeki_mizujfif.jfif"); break;
    }

    if ((player_hand == 0 && cpu_hand == 1) || (player_hand == 1 && cpu_hand == 2) || (player_hand == 2 && cpu_hand == 0)) {  //�v���C���[�̏�������
        set_image(imageNumber::WINLOGO, 0, -150, "janken_kachi.png");
        player_win_count += 1; // �v���C���[�̏�������1���₷.
        aiko_flag = false;
    }
    else if ((player_hand == 0 && cpu_hand == 2) || (player_hand == 1 && cpu_hand == 0) || (player_hand == 2 && cpu_hand == 1)) {  //�v���C���[�̕�������
        set_image(imageNumber::LOSELOGO, 0, -150, "janken_make.png");
        cpu_win_count += 1; // CPU�̏�������1���₷.
        aiko_flag = false;
    }
    else {  //����������
        aiko_flag = true;
    }
}

/**
*  �I������
*/
void Finish()
{
    fade_out(0, 0, 0, 1.5f);
    quit(); // �A�v���P�[�V�������I��������.
}