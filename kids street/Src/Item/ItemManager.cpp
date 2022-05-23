//ItemManager.cpp
//�A�C�e���Ǘ�
//CItem�ւ̃A�N�Z�X�͕K��CItemManager���o�R

#include "ItemManager.h"
#include "../Error/Error.h"

//CItemManager�̎��̐錾�A������
CItemManager* CItemManager::instance_ = nullptr;

namespace
{
	const float BOSS_ITEM_SCALE = 5.0f;
}
//�R���X�g���N�^
CItemManager::CItemManager()
{
	//CItem�̃R���X�g���N�^�͎����ŌĂ΂�܂�
	//�ϐ�������
	appearFlg_ = false;
	itemKind_ = INIT;
	itemHoldflg_ = true;
	useNum_ = 0;
	activate_ = false;
	dmg_ = 0;
	itemHoldflg_ = false;
	throwFlg_ = false;
	maxNum_ = 0;
	bossItem_.kind_ = INIT;
	bossItem_.num_ = 0;
	for(int kindNum = 0; kindNum < MAX_ITEM_KIND;kindNum++)
	{
		pr_itemFlg_[kindNum] = false;;
	}
}

//�f�X�g���N�^
CItemManager::~CItemManager()
{
	//CItem�̃f�X�g���N�^�͎����ŌĂ΂�܂�

}


//������
void CItemManager::Init()
{
	
	//�����S���N���X�I�[�o�[���C�h�Ə�����
	for (int kind = 0; kind < MAX_ERASER; kind++)
	{
		itemEraser_[kind] = new CEraser;
		itemEraser_[kind]->Init();
	}

	//���M�N���X�I�[�o�[���C�h�Ə�����
	for (int kind = 0; kind < MAX_PENCIL; kind++)
	{
		itemPencil_[kind] = new CPencil;
		itemPencil_[kind]->Init();
	}

	//�ϐ�������
	for (int kind = 0; kind < MAX_ITEM_KIND; kind++)
	{
		pr_itemFlg_[kind] = false;
	}
}


//�ǂݍ���
void CItemManager::Load()
{
	//�����S��
	MinimizeCall(itemEraser_, MAX_ERASER, VOID_LOAD);

	//���M
	MinimizeCall(itemPencil_, MAX_PENCIL, VOID_LOAD);
}


//�Z�b�g
void CItemManager::Set()
{
	//�ŏ��͏����S������n�܂�
	itemKind_ = ERASER;

	//�����S��
	MinimizeCall(itemEraser_, MAX_ERASER, VOID_SET);

	//���M
	MinimizeCall(itemPencil_, MAX_PENCIL, VOID_SET);
}


//�X�e�b�v
void CItemManager::Step()
{
	//�v���C���[�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	
	//�A�C�e�����g����̂��ǂ���
	if (appearFlg_ == true)
	{
		//���͊֌W(�A�C�e����I��)
		StepInput();

		//�A�C�e������ɂ��Ă�Ȃ�@
		if (itemHoldflg_ == true)
		{
			

			//���T������
			activate_ = false;

			//�ǂ̃A�C�e�����I�΂�Ă��邩
			switch (itemKind_)
			{
			case ERASER:
				for (int kind = 0; kind < MAX_ERASER; kind++)
				{
					//�g�p�ς݂���Ȃ��A�C�e����������
					if (itemEraser_[kind]->GetUseFlg() == false)
					{
						//�A�C�e������Ɏ�����
						itemEraser_[kind]->SetPosition(player->GetPlayerHandPos());
						//�X�e�b�v�����͎�Ɏ����Ă���A�C�e�������ʂ�K�v���Ȃ�
						itemEraser_[kind]->Step();
						 //�����Ɏ����Ă�z��ԍ����i�[
						useNum_ = kind;
						//����ɃA�C�e�������ĂĂ��邩�ǂ���
						activate_ = true;
						break;
					}
				}
				break;

			case PENCIL:
				for (int kind = 0; kind < MAX_PENCIL; kind++)
				{
					//�g�p�ς݂���Ȃ��A�C�e����������
					if (itemPencil_[kind]->GetUseFlg() == false)
					{
						//�A�C�e������Ɏ�����
						itemPencil_[kind]->SetPosition(player->GetPlayerHandPos());
						//�X�e�b�v�����͎�Ɏ����Ă���A�C�e�������ʂ�K�v���Ȃ�
						itemPencil_[kind]->Step();
						useNum_ = kind;
						activate_ = true;
						break;
					}
				}
				break;

			default:
				break;

			}//switch
		}//if

		////�����S��
		//MinimizeCall(itemEraser_, MAX_ERASER, VOID_STEP);
		////���M
		//MinimizeCall(itemPencil_, MAX_PENCIL, VOID_STEP);
	}

	//�A�C�e����������ꂽ���ɁA�V����������ꂽ�A�C�e�����������m�F����
	//���̃A�C�e���̂܂��g�p����Ă��Ȃ��t���O�̎g�p�t���O�𗧂Ă鏈��
	if (throwFlg_ == true)
	{
		//�ǂ̃A�C�e�����I�΂�Ă��邩
		switch (itemKind_)
		{
		case ERASER:
			itemEraser_[useNum_]->SetUseFlg(true);	//�g�p�t���O�𗧂Ă�
			break;

		case PENCIL:
			itemPencil_[useNum_]->SetUseFlg(true);	//�g�p�t���O�𗧂Ă�
			break;

		default:
			break;
		}

		//��x�����ʂ�΂�������t���O��܂�
		throwFlg_ = false;
		activate_ = false;
	}

	//�A�C�e���̈ړ�����
	StepMove();
}



//���f
void CItemManager::Update()
{
	//��Ɏ����Ă���A�C�e���𔽉f���邩
	if (activate_ == true)
	{
		switch (itemKind_)
		{
		case ERASER:

			itemEraser_[useNum_]->Update();
			break;

		case PENCIL:
			itemPencil_[useNum_]->Update();
			break;

		default:
			break;

		}
	}
}


//�`��
void CItemManager::Draw()
{


	//�A�C�e�����g���邩
	if (appearFlg_ == true)
	{
		//--------------��Ɏ����Ă���A�C�e���̕`�揈��------------
		//��Ɏ����Ă���A�C�e����`�悷�邩
		if (activate_ == true)
		{
			switch (itemKind_)
			{
			case ERASER:
				itemEraser_[useNum_]->Draw();
				break;
			
			case PENCIL:
				itemPencil_[useNum_]->Draw();
				break;
			default:
				break;

			}
		}
		//-----------------------------------------------------------

		//-------------�������Ă���A�C�e���̕`�揈��-----------
		// �������x���グ�邽��
		// �\��������Ƃ������`�F�b�N���Ȃ�
		if (pr_itemFlg_[FLG_ERASER])
		{
			for (int kind = 0; kind < MAX_ERASER; kind++)
			{
				//�g�p�t���O�������Ă��邩���ꂪ�����I�����Ă��Ȃ��Ȃ�
				if (itemEraser_[kind]->GetMoveFlg())
				{
					//�����S���`��
					itemEraser_[kind]->Draw();
				}
			}
		}
		//�������x
		if (pr_itemFlg_[FLG_PENCIL])
		{
			for (int kind = 0; kind < MAX_PENCIL; kind++)
			{
				//�g�p�t���O�������Ă��邩���ꂪ�����I�����Ă��Ȃ��Ȃ�
				if (itemPencil_[kind]->GetMoveFlg())
				{
					itemPencil_[kind]->Draw();
				}
			}
		}
		//------------------------------------------------------------------


	}
}

//�폜
void CItemManager::Delete()
{
	//�A�C�e���폜
	//�����S���̃X�e�b�v
	MinimizeCall(itemEraser_, MAX_ERASER, VOID_DELETE);

	//���M�̃X�e�b�v
	MinimizeCall(itemPencil_, MAX_PENCIL, VOID_DELETE);
}

//�㏈��
void CItemManager::Fin()
{
	//�A�C�e���̌㏈�����Ă�
	//�����S��
	MinimizeCall(itemEraser_, MAX_ERASER, VOID_FIN);

	//�����S���N���X�������J��
	for (int kind = 0; kind < MAX_ERASER; kind++)
	{
		delete itemEraser_[kind];
		itemEraser_[kind] = nullptr;
	}

	//���M
	MinimizeCall(itemPencil_, MAX_PENCIL, VOID_FIN);

	//���M�N���X�������J��
	for (int kind = 0; kind < MAX_PENCIL; kind++)
	{
		delete itemPencil_[kind];
		itemPencil_[kind] = nullptr;
	}

}

//���͊֌W����
void CItemManager::StepInput()
{
	//���̓N���X�擾
	CInput* input = CInput::GetInstance();

	//�P�������ꂽ�Ƃ��͏����S����I��
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_1))
	{
		itemKind_ = ERASER;
	}
	//�Q�������ꂽ�Ƃ��͉��M��I��
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_2))
	{
		itemKind_ = PENCIL;
	}
}

//�ړ�����
void CItemManager::StepMove()
{
	for (int kind = 0; kind < MAX_ITEM_KIND; kind++)
	{
		//�A�C�e���̎�ޕ��̏������x����̂��߂̃t���O������
		pr_itemFlg_[kind] = false;
	}
	
	//�����S��
	for (int kind = 0; kind < MAX_ERASER; kind++)
	{
		//�ړ����邩
		if (itemEraser_[kind]->GetMoveFlg())
		{
			//�ړ��v�Z����
			itemEraser_[kind]->Move();
			//�ړ�����������Ă���Ȃ�`��t���O�𗧂Ă�
			pr_itemFlg_[FLG_ERASER] = true;
		}
	}

	//���M
	for (int kind = 0; kind < MAX_PENCIL; kind++)
	{
		//�g�p�t���O�������Ă��邩���ꂪ�����I�����Ă��Ȃ��Ȃ�
		if (itemPencil_[kind]->GetMoveFlg())
		{
			//�ړ��v�Z����
			itemPencil_[kind]->Move();
			//�ړ�����������Ă���Ȃ�`��t���O�𗧂Ă�
			pr_itemFlg_[FLG_PENCIL] = true;
		}
	}
}

//�I�[�o�[���C�h�����A�C�e���̍\���̂̒��g��num�Ԗڂ܂ŉ񂵂ĎQ�ƁA�^�C�v�ɂ���ď����𕪂���
void CItemManager::MinimizeCall(CItemBase* item[], int maxNum, VOID_TYPE type)
{
	//-------------�����ł�肽������----------------
	//  ����for���������Ċ֐����Ă΂Ȃ��Ƃ����Ȃ����̂͂����܂Ƃ߂ČĂׂ�悤�Ɋ֐�����Ă��܂���
	// ---------------------------------------------- 

	for (int kind = 0; kind < maxNum; kind++)
	{
		switch (type)
		{
		case VOID_INIT:
			item[kind]->Init();break;

		case VOID_LOAD:
			item[kind]->Load();break;

		case VOID_SET:
			item[kind]->Set();break;

		case VOID_STEP:
			item[kind]->Step();break;

		case VOID_UPDATE:
			item[kind]->Update();break;

		case VOID_DRAW:
			item[kind]->Draw();break;

		case VOID_DELETE:
			item[kind]->Delete();break;

		case VOID_FIN:
			item[kind]->Fin();break;

		//�ǂ�ɂ������Ȃ��ꍇ
		default:
			CError::VoidError();
			break;
		}
	}
}

//�����蔻��X�V
void CItemManager::HitUpdate()
{
	//-------------�����ł�肽������----------------
	//  �����蔻��`�F�b�N���邽�߂ɕK�v�ȏ��𓖂��蔻��Ǘ��N���X�ɓn���Ă�
	// ---------------------------------------------- 

	VECTOR* eraserPos = (VECTOR*)malloc(sizeof(VECTOR) * MAX_ERASER);
	bool* eraserFlg = (bool*)malloc(sizeof(bool) * MAX_ERASER);

	//���݂̏�Ԃɍ\���̂̒��g���X�V����
	//(���ڈ����Ƃ��Ďg���Ȃ��̂ō\���̂ɓ���ă|�C���^�Ƃ��ēn�����߂ɕK�v)
	for (int item_num = 0; item_num < MAX_ERASER; item_num++)
	{
		eraserPos[item_num] = itemEraser_[item_num]->GetPosition();
		eraserFlg[item_num] = itemEraser_[item_num]->GetMoveFlg();
	}
	//�����蔻��N���X�ɕK�v�ȏ���n��
	CCollisionManager::GetInstance()->SetItemCollision(eraserPos, itemEraser_[0]->GetSimpleHit(), eraserFlg, ERASER);
	free(eraserPos);
	free(eraserFlg);
		
	VECTOR* pencilPos = (VECTOR*)malloc(sizeof(VECTOR) * MAX_PENCIL);
	bool* pencilFlg = (bool*)malloc(sizeof(bool) * MAX_PENCIL);
	//���݂̏�Ԃɍ\���̂̒��g���X�V����
	//(���ڈ����Ƃ��Ďg���Ȃ��̂ō\���̂ɓ���ă|�C���^�Ƃ��ēn�����߂ɕK�v)
	for (int item_num = 0; item_num < MAX_PENCIL; item_num++)
	{
		pencilPos[item_num] = itemPencil_[item_num]->GetPosition();
		pencilFlg[item_num] = itemPencil_[item_num]->GetMoveFlg();
	}
	//�����蔻��N���X�ɕK�v�ȏ���n��
	CCollisionManager::GetInstance()->SetItemCollision(pencilPos, itemPencil_[0]->GetSimpleHit(), pencilFlg, PENCIL);
	free(pencilPos); 
	free(pencilFlg);
}
	
//�����蔻�菈���i�A�C�e���}�l�[�W���[�ɂ���čs��ꂽ������ʉ߂����Ƃ��Ɏ��s�����
void CItemManager::DamageVanish(int num, ITEM_KIND kind)
{
	//-------------�����ł�肽������----------------
	//  ���������A�C�e���������āA���������A�C�e���ɐݒ肳��Ă��镪�̃_���[�W���{�X�ɗ^����
	// ---------------------------------------------- 

	
	
	//�󂯎����������int�^�̐��Ԗڂ̃A�C�e���̃G���h�t���O�𗧂Ă邱�ƂŎg�p�I������
	//�{�X�Ƀ_���[�W��^����_���[�W�ʂ����߂�֐��ɍ��Q�Ƃ���Ă���A�C�e���̃_���[�W���l��n��
	switch (kind)
	{
	case ERASER:
		itemEraser_[num]->SetEndFlg(true);
		CEnemyManager::GetInstance()->GetBoss()->SetDmg(itemEraser_[num]->GetDmg());
		break;

	case PENCIL:
		itemPencil_[num]->SetEndFlg(true);
		CEnemyManager::GetInstance()->GetBoss()->SetDmg(itemPencil_[num]->GetDmg());
		break;
		
	default:
		break;
	}

	//�{�X�̃_���[�W�������ʂ�悤�ɂ���
	CEnemyManager::GetInstance()->GetBoss()->SetColFlg(true);
	
}

//�{�X�̃L���b�`���ɋN����A�C�e�����̏���
void CItemManager::SetBossItemInfo(ITEM_KIND kind,int num)
{
	//-------------�����ł�肽������----------------
	//  �{�X����ɂ����A�C�e���̃{�X�擾�t���O��true�ցA
	// �{�X�̎��A�C�e���̎�ނƃ{�X�̎��A�C�e���̔ԍ����\���̂֊i�[
	// ---------------------------------------------- 

	switch (kind)
	{
	case ERASER:
		itemEraser_[num]->SetBossFlg(true);
		bossItem_.kind_ = ERASER;
		bossItem_.num_ = num;
		break;

	case PENCIL:
		itemPencil_[num]->SetBossFlg(true);
		bossItem_.kind_ = PENCIL;
		bossItem_.num_ = num;
		break;

	default:
		break;
	}
}

//�{�X�ɃA�C�e�����Ƃ�ꂽ�Ƃ��ɒʂ鏈��
void CItemManager::SetBossItemPos(VECTOR pos)
{
	//-------------�����ł�肽������----------------
	//  �{�X�̂��̂ɂȂ����A�C�e���̈ʒu���X�V
	// �����Ŏ󂯎�������W���{�X�A�C�e�����\���̂̊i�[���ƈ�v����A�C�e���ɓK�p����
	// ---------------------------------------------- 

	switch(bossItem_.kind_)
	{
	case ERASER:
		itemEraser_[bossItem_.num_]->SetPosition(pos);
	
		break;
	case PENCIL:
		itemPencil_[bossItem_.num_]->SetPosition(pos);
		
		break;
	default:
		break;
	}
}

//�{�X���A�C�e���𓊂������ɒʂ鏈��
void CItemManager::SetBossItemThrow()
{
	//-------------�����ł�肽������----------------
	//  �{�X���������A�C�e�����{�X�A�C�e���Ƃ��Ă̋������s�����߂ɕK�v�ȃt���O���I���ɂ���
	// ---------------------------------------------- 

	switch (bossItem_.kind_)
	{
	case ERASER:
		itemEraser_[bossItem_.num_]->SetBossThrowFlg(true);
		itemEraser_[bossItem_.num_]->SetScale(BOSS_ITEM_SCALE);
		break;
	case PENCIL:
		itemPencil_[bossItem_.num_]->SetBossThrowFlg(true);
		itemPencil_[bossItem_.num_]->SetScale(BOSS_ITEM_SCALE);
		break;
	default:
		break;
	}
}
	
	
