//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	ファイル名：Transform.h
//	概要		 ：トランスフォーム
//	作成者	 ：伊藤大悟
//	更新記録	 ：2023/11/00	00:00	作成
//			 ：2024/01/21	23:32	CopyをParentへ改修。shared_ptrを導入
//			 ：2024/12/13	00:05	ベクター、アングルの双方向変換関数追加・コメントアウトの追加
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____TRANSFORM_H_____
#define _____TRANSFORM_H_____

/**
 * @brief		Transformの
 * @details		{クラスの詳細説明}
 * @author		{*作成者}
 * @bug			{解決できていないバグの説明}
 * @warning		{警告}
 * @remark		{注釈}
 * @note		{覚え書き}
*/
class Transform
{
public:
	Transform();
	~Transform();

	void Update();

	fVec3 GetLocalPosition();
	fVec3 GetLocalRotation();
	fVec3 GetLocalScale();
	fVec3 GetWorldPosition();
	fVec3 GetWorldRotation();
	fVec3 GetWorldScale();

	void  SetLocalPosition(fVec3 Get);
	void  SetLocalRotation(fVec3 Get);
	void  SetLocalScale(fVec3 Get);
	void  SetWorldPosition(fVec3 Get);
	void  SetWorldRotation(fVec3 Get);
	void  SetWorldScale(fVec3 Get);

	void SetParent(Transform* tf);
	void RemoveParent();

	void LookPoint(Transform* point);

	fVec4x4 GetWorldMatrix(void);

private:
	void ParentCheck();
private:
	fVec3 m_localPosition;
	fVec3 m_localRotation;
	fVec3 m_localScale;

	bool m_HaveParent;
	Transform* m_Parent;

	bool m_IsLook;
	Transform* m_LookPoint;
};

namespace tf
{
	fVec3 PositionLocalToWorld(fVec3 localPos, Transform* pParentTransform);
	fVec3 PositionWorldToLocal(fVec3 worldPos, Transform* pParentTransform);
	fVec3 RotationLocalToWorld(fVec3 localRot, Transform* pParentTransform);
	fVec3 RotationWorldToLocal(fVec3 worldRot, Transform* pParentTransform);
	fVec3 ScaleLocalToWorld(fVec3 localScale, Transform* pParentTransform);
	fVec3 ScaleWorldToLocal(fVec3 worldScale, Transform* pParentTransform);
	fVec3 VectorToRotation(fVec3 vec);
	fVec3 RotationToVector(fVec3 rot);
}

#endif // !_____TRANSFORM_H_____