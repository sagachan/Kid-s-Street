//ItemManager.cpp
//�A�C�e���Ǘ�
//CItem�ւ̃A�N�Z�X�͕K��CItemManager���o�R

#include "ItemManager.h"
#include "../../Library/Error/Error.h"
#include "../../Library/SagaLibrary.h"
#include "../../Library/Sound/Sound.h"
#include "../../Enemy/EnemyManager.h"
#include "../../UI/GameUIManager.h"

#include "../GatherItem/GatherFactory/GatherManager.h"
#include "../GatherItem/ItemProduct/GatherEraser/GatherEraser.h"
#include "../GatherItem/ItemProduct/GatherPencil/GatherPencil.h"
#include "../GatherItem/ItemProduct/ItemBox/ItemBox.h"
#include "../GatherItem/ItemProduct/GatherRuler/GatherRuler.h"
#include "../GatherItem/ItemProduct/GatherGlove/GatherGlove.h"

#include "Eraser/Eraser.h"
#include "Pencil/Pencil.h"
#include "Ruler/Ruler.h"
#include "Glove/Glove.h"

namespace
{
	const float BOSS_ITEM_SCALE = 5.0f;
}


//CItemManager�̎��̐錾�A������
CItemManager* CItemManager::instance_ = nullptr;

//�I�[�o�[���C�h�����A�C�e���̍\���̂̒��g��num�Ԗڂ܂ŉ񂵂ĎQ�ƁA�^�C�v�ɂ���ď����𕪂���
void CItemManager::MinimizeCall(CItemBase* item[], int maxNum, VOID_TYPE type)
{
	//-------------�����ł�肽������----------------
	//  ����for���������Ċ֐����Ă΂Ȃ��Ƃ����Ȃ����̂͂����܂Ƃ߂ČĂׂ�悤�Ɋ֐�����Ă��܂���
	// ---------------------------------------------- 

	for (int kind = 0; kind < maxNum; kind++){
		switch (type){
		case VOID_INIT:item[kind]->Init(); break;
		case VOID_LOAD:item[kind]->Load(); break;
		case VOID_SET:item[kind]->Set(); break;
		case VOID_STEP:item[kind]->Step(); break;
		case VOID_UPDATE:item[kind]->Update(); break;
		case VOID_DRAW:item[kind]->Draw(); break;
		case VOID_DELETE:item[kind]->Delete(); break;
		case VOID_FIN:item[kind]->Fin(); break;

			//�ǂ�ɂ������Ȃ��ꍇ
		default:
			CError::MinimizeVoidError();
			break;
		}
	}
}

//�I�[�o�[���C�h�����A�C�e���̍\���̂̒��g��num�Ԗڂ܂ŉ񂵂ĎQ�ƁA�^�C�v�ɂ���ď����𕪂���
void CItemManager::MinimizeCall(CGatherBase* item[], int maxNum, VOID_TYPE type)
{
	for (int kind = 0; kind < maxNum; kind++) {
		switch (type) {
		case VOID_INIT:item[kind]->Init(); break;
		case VOID_LOAD:item[kind]->Load(); break;
		case VOID_SET:item[kind]->Set(); break;
		case VOID_STEP:item[kind]->Step(); break;
		case VOID_UPDATE:item[kind]->Update(); break;
		case VOID_DRAW:item[kind]->Draw(); break;
		case VOID_FIN:item[kind]->Fin(); break;

			//�ǂ�ɂ������Ȃ��ꍇ
		default:
			CError::MinimizeVoidError();
			break;
		}
	}
}


//�R���X�g���N�^
CItemManager::CItemManager()
{
	//CItem�̃R���X�g���N�^�͎����ŌĂ΂�܂�
	//�ϐ�������
	itemKind_ = ITEM_INIT;
	itemHoldflg_ = true;
	useNum_ = 0;
	activate_ = false;
	itemHoldflg_ = false;
	throwFlg_ = false;
	bossItem_.kind_ = ITEM_INIT;
	bossItem_.num_ = 0;
}

//�f�X�g���N�^
CItemManager::~CItemManager()
{
	//CItem�̃f�X�g���N�^�͎����ŌĂ΂�܂�

}


//������
void CItemManager::Init()
{
	//�A�C�e�����W�Ǘ��N���X����
	CGatherManager::CreateInstance();

	int itemNum = 0;

	//�����S���N���X�I�[�o�[���C�h
	for (itemNum = 0; itemNum < MAX_ERASER; itemNum++){
		 
		useItem_[itemNum] = new CEraser;
	}

	//���M�N���X�I�[�o�[���C�h
	for (int kind = 0; kind < MAX_PENCIL; kind++){
		useItem_[itemNum] = new CPencil;
		itemNum++;
	}

	//��K�N���X�I�[�o�[���C�h
	for (int kind = 0; kind < MAX_RULER; kind++) {
		useItem_[itemNum] = new CRuler;
		itemNum++;
	}
	
	for (int kind = 0; kind < MAX_GLOVE; kind++){
		useItem_[itemNum] = new CGlove;
		itemNum++;
	}
	for (itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++)
	{
		useItem_[itemNum]->SetItemNum(itemNum);
	}

	//�܂Ƃ߂ď�����
	MinimizeCall(useItem_, MAX_ITEM_NUM, VOID_INIT);

	//UI�֌W�N���X�I�[�o�[���C�h
	gatherItem_[ITEM_ID_BOX] = new CItemBox;
	gatherItem_[ITEM_ID_ERASER] = new CGatherEraser;
	gatherItem_[ITEM_ID_PENCIL] = new CGatherPencil;
	gatherItem_[ITEM_ID_RULER] = new CGatherRuler;
	gatherItem_[ITEM_ID_GLOVE] = new CGatherGlove;
	
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_INIT);
}


//�ǂݍ���
void CItemManager::Load()
{
	MinimizeCall(useItem_, MAX_ITEM_NUM, VOID_LOAD);
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_LOAD);

	CSound::LoadSE(CSound::SE_GET);
}


//�Z�b�g
void CItemManager::Set()
{
	MinimizeCall(useItem_, MAX_ITEM_NUM, VOID_SET);
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_SET);
}


//�X�e�b�v
void CItemManager::Step()
{
	//�v���C���[�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//���͊֌W(�A�C�e����I��)
	StepInput();

	//�A�C�e������ɂ��Ă�Ȃ�@
	if (itemHoldflg_ == true) {
		//���T������
		activate_ = false;

		//��ɂ��Ă�A�C�e����T��
		SerchItem(useItem_, itemKind_);
	}

	//�A�C�e����������ꂽ���ɁA�V����������ꂽ�A�C�e�����������m�F����
	//���̃A�C�e���̂܂��g�p����Ă��Ȃ��t���O�̎g�p�t���O�𗧂Ă鏈��
	if (throwFlg_ == true) {
		//�I�΂�Ă���g�p�t���O�𗧂Ă�
		useItem_[useNum_]->SetUseFlg(true);
		//��x�����ʂ�΂�������t���O��܂�
		throwFlg_ = false;
		activate_ = false;
	}

	//�A�C�e���̈ړ�����
	StepMove();
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_STEP);
}



//���f
void CItemManager::Update()
{
	//��Ɏ����Ă���A�C�e���𔽉f���邩
	if (activate_ == true){
		useItem_[useNum_]->Step();
	}

	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_UPDATE);
}


//�`��
void CItemManager::Draw()
{
	//--------------��Ɏ����Ă���A�C�e���̕`�揈��------------
		//��Ɏ����Ă���A�C�e����`�悷�邩
	if (activate_ == true){
		useItem_[useNum_]->Draw();
	}
	
	//-------------�������Ă���A�C�e���̕`�揈��-----------
	for (int itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++) {
		//�g�p�t���O�������Ă��邩���ꂪ�����I�����Ă��Ȃ��Ȃ�
		if (useItem_[itemNum]->GetMoveFlg()) {
			useItem_[useNum_]->Update();
			useItem_[itemNum]->Draw();
		}
	}
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_DRAW);
}

//�폜
void CItemManager::Delete()
{
	//�A�C�e���폜
	MinimizeCall(useItem_, MAX_ITEM_NUM, VOID_DELETE);
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_DELETE);
}

//�㏈��
void CItemManager::Fin()
{
	//�A�C�e���g�p�N���X�������J��
	for (int itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++){
		delete useItem_[itemNum];
		useItem_[itemNum] = nullptr;
	}

	//���W�N���X�������J��
	for (int kind = 0; kind < ITEM_MAX_KIND; kind++) {
		delete gatherItem_[kind];
		gatherItem_[kind] = nullptr;
	}

	CGatherManager::GetInstance()->DeleteAll();
	CGatherManager::DeleteInstance();
}

//���͊֌W����
void CItemManager::StepInput()
{
	//���̓N���X�擾
	CInput* input = CInput::GetInstance();
	ITEM_KIND oldKind = itemKind_;
	//�܂��I�΂�Ă��炸1�������ꂽ�Ƃ��͏����S����I��
	if (itemKind_ != ERASER){
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_1)) {
			itemKind_ = ERASER;
		}
	}
	//2�������ꂽ�Ƃ��͉��M��I��
	if (itemKind_ != PENCIL) {
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_2)) {
			itemKind_ = PENCIL;
		}
	}
	//3�������ꂽ�Ƃ��͎O�p��K��I��
	if (itemKind_ != RULER) {
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_3)) {
			itemKind_ = RULER;
		}
	}
	//4�������ꂽ�Ƃ��͎O�p��K��I��
	if (itemKind_ != GLOVE) {
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_4)) {
			itemKind_ = GLOVE;
		}
	}


	//���݂̃A�C�e���������J�n���ɓǂݍ���ł������̂���ς���Ă���Ȃ�
	if (oldKind != itemKind_){
		itemHoldflg_ = false;
		activate_ = false;
	}
}

//�ړ�����
void CItemManager::StepMove()
{
	for (int itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++){
		//�g�p�t���O�������Ă��邩���ꂪ�����I�����Ă��Ȃ��Ȃ�
		if (useItem_[itemNum]->GetMoveFlg()) {
			useItem_[itemNum]->Move();
		}
	}
}

//�S�̂̊��|�C���^�z��̎Q�ƊJ�n�ԍ��ƏI���ԍ�����ɓ����
CItemManager::ClassNumInfo CItemManager::CheckItem(ITEM_KIND kind)
{
	//�A�C�e���g�p�N���X���Q�Ƃ���ꍇ�Ɏ������������A�C�e���^�C�v�̔ԍ���
	//�����Ƃ��ē��͂��邱�ƂŁA�A�C�e�����S�̂̊��N���X�|�C���^�z��̒���
	//���Ԗڂ��牽�Ԗڂɓ����Ă���̂����`�F�b�N�ł���
	
	//�Q�Ɣԍ��̐錾
	ClassNumInfo numInfo = {0};
	numInfo.maxNum_ = MAX_ERASER;
	if (kind == ERASER) { return numInfo; }
	numInfo.initNum_ = MAX_ERASER; numInfo.maxNum_ += MAX_PENCIL;
	if (kind == PENCIL) { return numInfo; }
	numInfo.initNum_ += MAX_PENCIL; numInfo.maxNum_ += MAX_RULER;
	if (kind == RULER) { return numInfo; }
	numInfo.initNum_ += MAX_RULER; numInfo.maxNum_ += MAX_GLOVE;
	if(kind == GLOVE) { return numInfo; }
	numInfo = { 0 };
	return numInfo;
}

//��ɂ��Ă�A�C�e����T��
void CItemManager::SerchItem(CItemBase* item[], ITEM_KIND kind)
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	ClassNumInfo numInfo = CheckItem(kind);
	for (numInfo.initNum_; numInfo.initNum_ < numInfo.maxNum_; numInfo.initNum_++)
	{
		//�g�p�ς݂���Ȃ��A�C�e����������
		if (item[numInfo.initNum_]->GetUseFlg() == false)
		{
			//�A�C�e������Ɏ�����
			item[numInfo.initNum_]->SetPosition(player->GetPlayerHandPos());
			//�X�e�b�v�����͎�Ɏ����Ă���A�C�e�������ʂ�K�v���Ȃ�
			item[numInfo.initNum_]->Step();
			//�����Ɏ����Ă�z��ԍ����i�[
			useNum_ = numInfo.initNum_;
			//����ɃA�C�e�������ĂĂ��邩�ǂ���
			activate_ = true;
			break;
		}
	}
}

////�����蔻��X�V
//void CItemManager::HitUpdate()
//{
//	//-------------�����ł�肽������----------------
//	//  �����蔻��`�F�b�N���邽�߂ɕK�v�ȏ��𓖂��蔻��Ǘ��N���X�ɓn���Ă�
//	// ----------------------------------------------
//	CCollisionManager::ITEM_DATA* itemData =
//		(CCollisionManager::ITEM_DATA*)malloc(sizeof(CCollisionManager::ITEM_DATA) * MAX_ITEM_NUM);
//
//	//���݂̏�Ԃɍ\���̂̒��g���X�V����
//	//(���ڈ����Ƃ��Ďg���Ȃ��̂ō\���̂ɓ���ă|�C���^�Ƃ��ēn�����߂ɕK�v)
//	for (int itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++)
//	{
//		itemData[itemNum].pos_ = useItem_[itemNum]->GetPosition();
//		itemData[itemNum].useflg_ = useItem_[itemNum]->GetMoveFlg();
//		itemData[itemNum].rad_ = useItem_[itemNum]->GetRad();
//	}
//	//�����蔻��N���X�ɕK�v�ȏ���n��
//	CCollisionManager::GetInstance()->SetItemCollision(itemData);
//	free(itemData);
//


//�����蔻�菈���i�A�C�e���}�l�[�W���[�ɂ���čs��ꂽ������ʉ߂����Ƃ��Ɏ��s�����
void CItemManager::DamageVanish(int num)
{
	//-------------�����ł�肽������----------------
	//  ���������A�C�e���������āA���������A�C�e���ɐݒ肳��Ă��镪�̃_���[�W���{�X�ɗ^����
	// ---------------------------------------------- 

	//�󂯎����������int�^�̐��Ԗڂ̃A�C�e���̃G���h�t���O�𗧂Ă邱�ƂŎg�p�I������
	//�{�X�Ƀ_���[�W��^����_���[�W�ʂ����߂�֐��ɍ��Q�Ƃ���Ă���A�C�e���̃_���[�W���l��n��
	useItem_[num]->SetEndFlg(true);
	CEnemyManager::GetInstance()->GetBoss()->Damage(useItem_[num]->GetDmg());
	
}

//�{�X�̃L���b�`���ɋN����A�C�e�����̏���
void CItemManager::SetBossItemInfo(int num)
{
	//-------------�����ł�肽������----------------
	//  �{�X����ɂ����A�C�e���̃{�X�擾�t���O��true�ցA
	//	�{�X�̎��A�C�e���̔ԍ����\���̂֊i�[
	// ---------------------------------------------- 
	useItem_[num]->SetBossFlg(true);
	bossItem_.num_ = num;
}

//�{�X�ɃA�C�e�����Ƃ�ꂽ�Ƃ��ɒʂ鏈��
void CItemManager::SetBossItemPos(VECTOR pos)
{
	//-------------�����ł�肽������----------------
	//  �{�X�̂��̂ɂȂ����A�C�e���̈ʒu���X�V
	// �����Ŏ󂯎�������W���{�X�A�C�e�����\���̂̊i�[���ƈ�v����A�C�e���ɓK�p����
	// ---------------------------------------------- 
	useItem_[bossItem_.num_]->SetPosition(pos);
}

//�{�X���A�C�e���𓊂������ɒʂ鏈��
void CItemManager::SetBossItemThrow()
{
	//-------------�����ł�肽������----------------
	//  �{�X���������A�C�e�����{�X�A�C�e���Ƃ��Ă̋������s�����߂ɕK�v�ȃt���O���I���ɂ���
	// ---------------------------------------------- 
	useItem_[bossItem_.num_]->SetBossThrowFlg(true);
	useItem_[bossItem_.num_]->SetScale(BOSS_ITEM_SCALE);
}
	
bool CItemManager::IDFromKind(ITEM_ID id)
{
	switch (id){
	case ITEM_ID_ERASER:if(itemKind_ == ERASER)return true;break;
	case ITEM_ID_PENCIL:if (itemKind_ == PENCIL)return true; break;
	case ITEM_ID_RULER:if (itemKind_ == RULER)return true;break;
	case ITEM_ID_GLOVE:if (itemKind_ == GLOVE)return true; break;
	}

	return false;
}
	
