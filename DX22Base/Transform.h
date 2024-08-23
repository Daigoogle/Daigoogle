//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	ファイル名：Transform.h
//	概要		 ：トランスフォーム
//	作成者	 ：伊藤大悟
//	更新記録	 ：2023/11/00	00:00	作成
//			 ：2024/01/21	23:32	CopyをParentへ改修。shared_ptrを導入
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____TRANSFORM_H_____
#define _____TRANSFORM_H_____

#include "Vectors.hxx"
#include <memory>
#include <DirectXMath.h>
#include "Component.h"

/// @brief class Transform
/// @brief public : Component
class Transform:public Component
{
public:
	Transform();
	~Transform();

	void Init();
	void Update();
	void UnInit();

	void  SetLocalPosition(fVec3 Get);
	fVec3 GetLocalPosition();
	void  SetLocalRotation(fVec3 Get);
	fVec3 GetLocalRotation();
	void  SetLocalScale(fVec3 Get);
	fVec3 GetLocalScale();
	
	void  SetWorldPosition(fVec3 Get);
	fVec3 GetWorldPosition();
	void  SetWorldRotation(fVec3 Get);
	fVec3 GetWorldRotation();
	void  SetWorldScale(fVec3 Get);
	fVec3 GetWorldScale();

	void SetParent(Transform* tf);
	void RemoveParent();

	DirectX::XMFLOAT4X4 GetWorldMatrix(void);

private:
	void ParentCheck();
	static fVec3 PositionLocalToWorld(fVec3 localPos, Transform* pParentTransform);
	static fVec3 PositionWorldToLocal(fVec3 worldPos, Transform* pParentTransform);
	static fVec3 RotationLocalToWorld(fVec3 localRot, Transform* pParentTransform);
	static fVec3 RotationWorldToLocal(fVec3 worldRot, Transform* pParentTransform);
	static fVec3 ScaleLocalToWorld(fVec3 localScale,  Transform* pParentTransform);
	static fVec3 ScaleWorldToLocal(fVec3 worldScale,  Transform* pParentTransform);

private:
	fVec3 m_localPosition;
	fVec3 m_localRotation;
	fVec3 m_localScale;

	bool m_HaveParent;
	Transform* m_Parent;
};

//typedef std::shared_ptr<Transform> Shared_Transform;

#endif // !_____TRANSFORM_H_____