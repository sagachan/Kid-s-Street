
#include "ColField.h"
#include "../../Field/FieldManager.h"
#include "../../Player/PlayerManager.h"
#include "../../Field/FieldCommon.h"
#include "../../Camera/CameraManager.h"
#include "../../Library/Collision/Collision.h"

namespace
{
	//�}�b�v�֘A
	const float MAP_FLOOR_NORM_Y(0.1f);	//�@����Y���������̒l�ȏ�ł���Ώ�
	const float MAP_CEIL_NORM_Y(-0.9f);	//�@����Y���������̒l�ȏ�ł���Ώ�
	const float MAP_WALL_NORM_Z(0.5f);	//�@����Z���������̒l�ȏ�ł���Ε�

	const float CAMERA_RADIUS = 5.0f;	//�ǂɖ��܂�Ȃ��Ȃ牽�ł�����
}

void CColField::CheckColField()
{
	//�v���C���[�Ƃ̓����蔻��
	CheckPlayer();
	CheckCamera();
}

void CColField::CheckPlayer()
{
	// �}�b�v�Ƃ̓����蔻��//
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	MapInfo mapInfo = road->GetMapInfo();
	bool airFlg = true;

	// �|���S�������擾
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(mapInfo.col_handle, -1, TRUE);

	//�v���C���[�����擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//�v���C���[�̑O�����x�N�g���擾
	VECTOR player_forward = CPlayerManager::GetInstance()->GetPlayer()->GetMove();

	// �|���S���̐������J��Ԃ�
	for (int i = 0; i < polygons.PolygonNum; i++) {
		// �|���S�������擾����
		MV1_REF_POLYGON polygon = polygons.Polygons[i];
		// �|���S�����`������O�p�`��3���_���擾����
		VECTOR vertexs[3];
		int index = polygon.VIndex[0];
		vertexs[0] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[1];
		vertexs[1] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[2];
		vertexs[2] = polygons.Vertexs[index].Position;


		// �|���S���@�����Z�o����
		VECTOR norm = CMyMath::GetPolygonNormalVec(vertexs[0], vertexs[1], vertexs[2]);
		// �@����Y������MAP_FLOOR_NORM_Y_MIN�ȏ�ł���Ώ�
		if (norm.y >= MAP_FLOOR_NORM_Y) {
			// �O�p�`�̓����蔻��
			if (CCollision::IsHitTriangleXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]))
			{


				// �ʂ̕��������珰�̍������v�Z
				float floor_height = CMyMath::GetTriangleHeightXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
				// �v���C���[�̑����̍��W���v�Z
				float player_bottom = player->GetPosition().y - player->GetRad();
				// �����瑫���܂ł̋������v�Z
				float dist = player_bottom - floor_height;
				// �����̕����Ⴂ ���� �����Ə��Ƃ̋��������ꂷ���Ă��Ȃ���Ή����グ��
				if (dist < 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					VECTOR pos = player->GetPosition();
					pos.y = floor_height + player->GetRad();
					player->SetPosition(pos);

					//���ɂ������Ă��邩��󒆂ɂ͂��Ȃ�
					airFlg = false;
				}
			}
		}
		else if (norm.y <= MAP_CEIL_NORM_Y) {
			// �V��̏ꍇ
			// �O�p�`�̓����蔻��
			if (CCollision::IsHitTriangleXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
				// �ʂ̕���������V��̍������v�Z
				float ceil_height = CMyMath::GetTriangleHeightXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
				// �v���C���[�̔]�V�̍��W���v�Z
				float player_top = player->GetPosition().y + player->GetRad();
				// �V�䂩��]�V�܂ł̋������v�Z
				float dist = player_top - ceil_height;
				// �]�V�̕������� ���� �]�V�ƓV��Ƃ̋��������ꂷ���Ă��Ȃ���Ή���������
				if (dist > 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					VECTOR pos = player->GetPosition();
					pos.y = ceil_height - player->GetRad();
					player->SetPosition(pos);
				}
			}
		}
		else {
			// �����łȂ���Ε�
			// �@���ƃv���C���[�̈ړ��x�N�g���������������Ă���ꍇ�̂ݔ�������
			/*if (CMyMath::VecDot(player_forward, norm) < 0.0f) {*/
			if (CMyMath::Abs(norm.z) >= MAP_WALL_NORM_Z) {
				// XY���ʂ̕�
				if (CCollision::IsHitTriangleXY(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
					// ���ʏ�̕ǂ̍������Z�o
					float wall_height = CMyMath::GetTriangleHeightXY(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
					// �Փ˓_�܂ł̋������Z�o
					float player_front = norm.z < 0.0f ? player->GetPosition().z + player->GetRad() : player->GetPosition().z - player->GetRad();
					float dist = player_front - wall_height;
					// �ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
					if (CMyMath::Abs(dist) <= player->GetRad()) {
						// �@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
						if ((norm.z < 0.0f && dist > 0.0f) || (norm.z > 0.0f && dist < 0.0f)) {
							// �@���̕����ɂ߂荞��ł��镪���������o��
							VECTOR push = CMyMath::VecScale(norm, CMyMath::Abs(dist));
							VECTOR pos = player->GetPosition();
							pos = CMyMath::VecAdd(player->GetPosition(), push);
							player->SetPosition(pos);
						}
					}
				}
			}
			else {
				// YZ���ʂ̕�
				if (CCollision::IsHitTriangleYZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
					// ���ʏ�̕ǂ̍������Z�o
					float wall_height = CMyMath::GetTriangleHeightYZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
					// �Փ˓_�܂ł̋������Z�o
					float player_front = norm.x < 0.0f ? player->GetPosition().x + player->GetRad() : player->GetPosition().x - player->GetRad();
					float dist = player_front - wall_height;
					// �ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
					if (CMyMath::Abs(dist) <= player->GetRad()) {
						// �@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
						if ((norm.x < 0.0f && dist > 0.0f) || (norm.x > 0.0f && dist < 0.0f)) {
							// �@���̕����ɂ߂荞��ł��镪���������o��
							VECTOR push = CMyMath::VecScale(norm, CMyMath::Abs(dist));
							VECTOR pos = player->GetPosition();
							pos = CMyMath::VecAdd(player->GetPosition(), push);
							player->SetPosition(pos);
						}
					}// if (MyMath::Abs(dist) <= PLAYER_RAD)
				}// if (CCollision::IsHitTriangleYZ(player_info_.pos, vertexs[0], vertexs[1], vertexs[2]))
			}// if (MyMath::Abs(norm.z) >= MAP_WALL_NORM_Z_MIN) else
		//}// if (MyMath::VecDot(player_info_.forward, norm) < 0.0f)
		}// if (norm.y >= MAP_FLOOR_NORM_Y_MIN) else
	}// for (int i = 0; i < polygons.PolygonNum; i++)

	road->SetAirFlg(airFlg);
}


void CColField::CheckCamera()
{
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	MapInfo mapInfo = road->GetMapInfo();

	//�v���C���[�����擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	CPlayCamera* camera = CCameraManager::GetInstance()->GetPlayCamera();

	VECTOR pos = camera->GetPos();
	VECTOR oldPos = camera->GetOldPos();

	MV1_COLL_RESULT_POLY res;

	res = MV1CollCheck_Line(mapInfo.col_handle, -1, pos, playerPos);

	if (!res.HitFlag)
	{
		return;
	}

	camera->SetPos(res.HitPosition);

}