//GameClearScene.cpp
//�Q�[���N���A�V�[��

#include "GameClearScene.h"
#include "../SceneManager.h"
#include "../../Library/Input/Input.h"
#include "DxLib.h"
#include <math.h>
#include "../../Common.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../UI/GameUIManager.h"
#include "../../Library/Sound/Sound.h"


namespace
{

}


CGameClearScene::CGameClearScene()
{
	Init();
}

CGameClearScene::~CGameClearScene()
{
}

//������
void CGameClearScene::Init()
{
	//UI�Ǘ�����
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//�w�i����
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/GameClear.jpg");

	//��������
	CSound::InitSound();
}

//�ǂݍ���
void CGameClearScene::Load()
{
	//���ǂݍ���
	CSound::LoadBGM(CSound::BGM_CLEAR);
}

//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CGameClearScene::Set()
{
	//���Đ�
	CSound::PlayBGM(CSound::BGM_CLEAR);
}

//���t���[���Ăԏ���
void CGameClearScene::Step()
{
	//Enter�L�[�������ꂽ��^�C�g���V�[����
	if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//�^�C�g���V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_TITLE);
	}


	//UI�Ǘ��X�e�b�v
	CGameUIManager::GetInstance()->Step();
}


//�`��
void CGameClearScene::Draw()
{
	//UI�Ǘ��`��
	CGameUIManager::GetInstance()->Draw();
}


//�㏈��
void CGameClearScene::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();

	//���㏈��
	CSound::FinSound();
}