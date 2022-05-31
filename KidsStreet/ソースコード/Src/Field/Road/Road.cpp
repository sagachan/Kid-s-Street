//Road.cpp
//���N���X

#include "Road.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Library/Collision/Collision.h"

namespace
{
	//�}�b�v�֘A
	const float MAP_FLOOR_NORM_Y(0.1f);	//�@����Y���������̒l�ȏ�ł���Ώ�
	const float MAP_CEIL_NORM_Y(-0.9f);	//�@����Y���������̒l�ȏ�ł���Ώ�
	const float MAP_WALL_NORM_Z(0.5f);	//�@����Z���������̒l�ȏ�ł���Ε�

	const VECTOR MAP_HNDL_POS = VGet(-20.0f, -1.0f, 0.0f);
	const VECTOR MAP_COL_POS = VGet(-20.0f, -2.0f, 0.0f);
}

//�R���X�g���N�^
CRoad::CRoad()
	:air_flg_(false){}

//�f�X�g���N�^
CRoad::~CRoad()
{
	Fin();
}


//�ǂݍ���
void CRoad::Load()
{
	// ���f���ǂݍ���
	mapInfo_.handle = MV1LoadModel("Data/Map/Field/map.x");
	// �����蔻�胂�f���ǂݍ���
	mapInfo_.col_handle = MV1LoadModel("Data/Map/Field/map.x");
}



//�Z�b�g
void CRoad::Set()
{
	//�}�b�v�̍��W
	MV1SetPosition(mapInfo_.handle, MAP_HNDL_POS);
	MV1SetPosition(mapInfo_.col_handle, MAP_COL_POS);

	// �����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1SetupCollInfo(mapInfo_.col_handle);
	MV1SetupCollInfo(mapInfo_.handle);

}


//�X�V
void CRoad::Update()
{
	
	// �|���S�������X�V����
	/*MV1RefreshReferenceMesh(mapInfo_.col_handle, -1, TRUE);*/
	MV1RefreshCollInfo(mapInfo_.col_handle);

	/*MV1RefreshReferenceMesh(mapInfo_.handle, -1, TRUE);*/
	MV1RefreshCollInfo(mapInfo_.handle);
}


//�`��
void CRoad::Draw()
{
	MV1DrawModel(mapInfo_.handle);
}


//�폜
void CRoad::Delete()
{
	MV1DeleteModel(mapInfo_.handle);
	MV1DeleteModel(mapInfo_.col_handle);
}


//�㏈��
void CRoad::Fin()
{
	if (mapInfo_.handle != 0){
		Delete();
	}
}