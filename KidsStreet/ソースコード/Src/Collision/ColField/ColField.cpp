
#include "ColField.h"
#include "../../Field/FieldManager.h"
#include "../../Player/PlayerManager.h"
#include "../../Field/FieldCommon.h"
#include "../../Camera/CameraManager.h"
#include "../../Library/Collision/Collision.h"

namespace
{
	//マップ関連
	const float MAP_FLOOR_NORM_Y(0.1f);	//法線のY成分がこの値以上であれば床
	const float MAP_CEIL_NORM_Y(-0.9f);	//法線のY成分がこの値以上であれば床
	const float MAP_WALL_NORM_Z(0.5f);	//法線のZ成分がこの値以上であれば壁

	const float CAMERA_RADIUS = 5.0f;	//壁に埋まらないなら何でもいい
}

void CColField::CheckColField()
{
	//プレイヤーとの当たり判定
	CheckPlayer();
	CheckCamera();
}

void CColField::CheckPlayer()
{
	// マップとの当たり判定//
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	MapInfo mapInfo = road->GetMapInfo();
	bool airFlg = true;

	// ポリゴン情報を取得
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(mapInfo.col_handle, -1, TRUE);

	//プレイヤー情報を取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//プレイヤーの前向きベクトル取得
	VECTOR player_forward = CPlayerManager::GetInstance()->GetPlayer()->GetMove();

	// ポリゴンの数だけ繰り返す
	for (int i = 0; i < polygons.PolygonNum; i++) {
		// ポリゴン情報を取得する
		MV1_REF_POLYGON polygon = polygons.Polygons[i];
		// ポリゴンを形成する三角形の3頂点を取得する
		VECTOR vertexs[3];
		int index = polygon.VIndex[0];
		vertexs[0] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[1];
		vertexs[1] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[2];
		vertexs[2] = polygons.Vertexs[index].Position;


		// ポリゴン法線を算出する
		VECTOR norm = CMyMath::GetPolygonNormalVec(vertexs[0], vertexs[1], vertexs[2]);
		// 法線のY成分がMAP_FLOOR_NORM_Y_MIN以上であれば床
		if (norm.y >= MAP_FLOOR_NORM_Y) {
			// 三角形の当たり判定
			if (CCollision::IsHitTriangleXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]))
			{


				// 面の方程式から床の高さを計算
				float floor_height = CMyMath::GetTriangleHeightXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
				// プレイヤーの足元の座標を計算
				float player_bottom = player->GetPosition().y - player->GetRad();
				// 床から足元までの距離を計算
				float dist = player_bottom - floor_height;
				// 足元の方が低い かつ 足元と床との距離が離れすぎていなければ押し上げる
				if (dist < 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					VECTOR pos = player->GetPosition();
					pos.y = floor_height + player->GetRad();
					player->SetPosition(pos);

					//床にあたっているから空中にはいない
					airFlg = false;
				}
			}
		}
		else if (norm.y <= MAP_CEIL_NORM_Y) {
			// 天井の場合
			// 三角形の当たり判定
			if (CCollision::IsHitTriangleXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
				// 面の方程式から天井の高さを計算
				float ceil_height = CMyMath::GetTriangleHeightXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
				// プレイヤーの脳天の座標を計算
				float player_top = player->GetPosition().y + player->GetRad();
				// 天井から脳天までの距離を計算
				float dist = player_top - ceil_height;
				// 脳天の方が高い かつ 脳天と天井との距離が離れすぎていなければ押し下げる
				if (dist > 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					VECTOR pos = player->GetPosition();
					pos.y = ceil_height - player->GetRad();
					player->SetPosition(pos);
				}
			}
		}
		else {
			// そうでなければ壁
			// 法線とプレイヤーの移動ベクトルが向かい合っている場合のみ判定を取る
			/*if (CMyMath::VecDot(player_forward, norm) < 0.0f) {*/
			if (CMyMath::Abs(norm.z) >= MAP_WALL_NORM_Z) {
				// XY平面の壁
				if (CCollision::IsHitTriangleXY(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
					// 平面上の壁の高さを算出
					float wall_height = CMyMath::GetTriangleHeightXY(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
					// 衝突点までの距離を算出
					float player_front = norm.z < 0.0f ? player->GetPosition().z + player->GetRad() : player->GetPosition().z - player->GetRad();
					float dist = player_front - wall_height;
					// 壁から離れすぎていないかチェック
					if (CMyMath::Abs(dist) <= player->GetRad()) {
						// 法線の向きに気を付けてめり込んでいるかチェックする
						if ((norm.z < 0.0f && dist > 0.0f) || (norm.z > 0.0f && dist < 0.0f)) {
							// 法線の方向にめり込んでいる分だけ押し出す
							VECTOR push = CMyMath::VecScale(norm, CMyMath::Abs(dist));
							VECTOR pos = player->GetPosition();
							pos = CMyMath::VecAdd(player->GetPosition(), push);
							player->SetPosition(pos);
						}
					}
				}
			}
			else {
				// YZ平面の壁
				if (CCollision::IsHitTriangleYZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
					// 平面上の壁の高さを算出
					float wall_height = CMyMath::GetTriangleHeightYZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
					// 衝突点までの距離を算出
					float player_front = norm.x < 0.0f ? player->GetPosition().x + player->GetRad() : player->GetPosition().x - player->GetRad();
					float dist = player_front - wall_height;
					// 壁から離れすぎていないかチェック
					if (CMyMath::Abs(dist) <= player->GetRad()) {
						// 法線の向きに気を付けてめり込んでいるかチェックする
						if ((norm.x < 0.0f && dist > 0.0f) || (norm.x > 0.0f && dist < 0.0f)) {
							// 法線の方向にめり込んでいる分だけ押し出す
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

	//プレイヤー情報を取得
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