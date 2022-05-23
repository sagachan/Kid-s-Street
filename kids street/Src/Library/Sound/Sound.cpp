#include "DxLib.h"
#include "Sound.h"

CSound::BGMInfo CSound::bgm[BGM_NUM];
//CSound::SEInfo CSound::se[SE_NUM];


//BGM�̃t�@�C���p�X
const char bgm_FilePath[CSound::BGM_NUM][256] =
{
 "Data/Sound/Opening.mp3",  //�^�C�g������BGM
 "Data/Sound/CitySound.mp3",  //�v���C����BGM
 "Data/Sound/",  //�N���A����BGM
 "Data/Sound/GameOver.mp3",  //�Q�[���I�[�o�[����BGM
 "Data/Sound/Escape.mp3",    //�G�l�~�[�ɒǂ�ꂽ����BGM
 "Data/Sound/Controll.mp3",  //���C����BGM
 "Data/Sound/BossBattle.mp3"    //�{�X�o�g������BGM
};

////���ʉ��̃t�@�C���p�X
//const char se_FilePath[CSound::SE_NUM][256] =
//{
// ,   //�e���ˌ��ʉ�
// ,  //���j���ʉ�
// , //������ʉ�
//};


//�T�E���h�̏�����
void CSound::InitSound()
{
    //BGM�̏�����
    for (int bgm_index = 0; bgm_index < BGM_NUM; bgm_index++)
    {
        bgm[bgm_index].handle = 0;
        bgm[bgm_index].kind = BGM_NONE;
    }

    ////���ʉ��̏�����
    //for (int se_index = 0; se_index < SE_NUM; se_index++)
    //{
    //    se[se_index].handle = 0;
    //    se[se_index].kind = SE_NONE;
    //}
}

void CSound::LoadBGM(BGM_KIND kind)
{
    for (int bgm_index = 0; bgm_index < BGM_NUM; bgm_index++)
    {
        //���g�p�Ȃ�
        if (bgm[bgm_index].handle == 0)
        {
            //�ǂݍ���
            bgm[bgm_index].handle = LoadSoundMem(bgm_FilePath[kind]);
            bgm[bgm_index].kind = kind;

            break;
        }
    }
}

////���ʉ��T�E���h�̓ǂݍ���
//void CSound::LoadSE(SE_KIND kind)
//{
//    for (int se_index = 0; se_index < SE_NUM; se_index++)
//    {
//        //���g�p�Ȃ�
//        if (se[se_index].handle == 0)
//        {
//            //�ǂݍ���
//            se[se_index].handle = LoadSoundMem(se_FilePath[kind]);
//            se[se_index].kind = kind;
//
//            break;
//        }
//    }
//}

//BGM�̍Đ�
void CSound::PlayBGM(BGM_KIND kind)
{
    for (int bgm_index = 0; bgm_index < BGM_NUM; bgm_index++)
    {
        //�Y����BGM����
        if (bgm[bgm_index].kind == kind)
        {
            switch (kind){
            case CSound::BGM_TITLE:ChangeVolumeSoundMem(80, bgm[bgm_index].handle); 
                break;

                //�v���C�V�[�����ʉ�����
            case CSound::BGM_PLAY:ChangeVolumeSoundMem(80, bgm[bgm_index].handle);
                break;

            case CSound::BGM_CLEAR:break;

                //�Q�[���I�[�o�[�V�[��BGM����
            case CSound::BGM_GAMEOVER:ChangeVolumeSoundMem(80, bgm[bgm_index].handle);
                break;

            case CSound::BGM_ESCAPE:ChangeVolumeSoundMem(80, bgm[bgm_index].handle); 
                break;

                //���C��BGM���ʒ���
            case CSound::BGM_MAIN:ChangeVolumeSoundMem(80, bgm[bgm_index].handle);
                break;

                //�{�XBGM���ʒ���
            case CSound::BGM_BOSS:ChangeVolumeSoundMem(80, bgm[bgm_index].handle);
                break;
            case CSound::MOVE:break;
            case CSound::BGM_NUM:break;
            }

            PlaySoundMem(bgm[bgm_index].handle, DX_PLAYTYPE_LOOP, true);
            break;
        }
    }
}

void CSound::StopBGM(BGM_KIND kind)
{
    for (int bgm_index = 0; bgm_index < BGM_NUM; bgm_index++)
    {
        //�Y����BGM����
        if (bgm[bgm_index].kind == kind)
        {
            StopSoundMem(bgm[bgm_index].handle);
            break;
        }
    }
}

////���ʉ��̍Đ�
//void CSound::PlaySE(SE_KIND kind)
//{
//    for (int se_index = 0; se_index < SE_NUM; se_index++)
//    {
//        //�Y���̌��ʉ�����
//        if (se[se_index].kind == kind)
//        {
//
//            PlaySoundMem(se[se_index].handle, DX_PLAYTYPE_BACK, true);
//            break;
//        }
//    }
//}

//�T�E���h�̌㏈��
void CSound::FinSound()
{
    //BGM��S�Ē�~���Ĕj��
    for (int bgm_index = 0; bgm_index < BGM_NUM; bgm_index++)
    {
        StopSoundMem(bgm[bgm_index].handle);
        DeleteSoundMem(bgm[bgm_index].handle);
    }

    ////���ʉ���S�Ĕj��
    //for (int se_index = 0; se_index < SE_NUM; se_index++)
    //{
    //    DeleteSoundMem(se[se_index].handle);
    //}
}