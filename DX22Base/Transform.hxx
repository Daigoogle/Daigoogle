//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	�t�@�C�����FTransform.h
//	�T�v		 �F�g�����X�t�H�[��
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2023/11/00	00:00	�쐬
//			 �F2024/01/21	23:32	Copy��Parent�։��C�Bshared_ptr�𓱓�
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____TRANSFORM_H_____
#define _____TRANSFORM_H_____

#include "Vectors.hxx"
#include <memory>
#include <DirectXMath.h>
#include "Component.hxx"

/// @brief class Transform
/// @brief public : Component
class Transform:public Component
{
public:
	Transform();
	~Transform();

	bool Init()override;
	void Update()override;

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

	fVec4x4 GetWorldMatrix(void);

private:
	void ParentCheck();
private:
	fVec3 m_localPosition;
	fVec3 m_localRotation;
	fVec3 m_localScale;

	bool m_HaveParent;
	Transform* m_Parent;
};

namespace tf
{
	fVec3 PositionLocalToWorld(fVec3 localPos, Transform* pParentTransform);
	fVec3 PositionWorldToLocal(fVec3 worldPos, Transform* pParentTransform);
	fVec3 RotationLocalToWorld(fVec3 localRot, Transform* pParentTransform);
	fVec3 RotationWorldToLocal(fVec3 worldRot, Transform* pParentTransform);
	fVec3 ScaleLocalToWorld(fVec3 localScale, Transform* pParentTransform);
	fVec3 ScaleWorldToLocal(fVec3 worldScale, Transform* pParentTransform);
}

#endif // !_____TRANSFORM_H_____