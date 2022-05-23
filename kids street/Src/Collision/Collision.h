#ifndef __COLLISION_H__
#define __COLLISION_H__

class CCollision {
public:
	//直方体の当たり判定
	static bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2);

	//球の当たり判定
	static bool IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2);

	//三角形の当たり判定
	// 引数
	// point :対象の座標
	// vertexA :三角形の頂点A
	// vertexB :三角形の頂点B
	// vertexC :三角形の頂点C
	static bool IsHitTriangleXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static bool IsHitTriangleXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static bool IsHitTriangleYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	enum DmType
	{
		INIT,
		DM_SMALL,
		DM_MIDDLE,
		DM_BIG
	};
	
};

#endif