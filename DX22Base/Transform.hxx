//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	�t�@�C�����FTransform.h
//	�T�v		 �F�g�����X�t�H�[��
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2023/11/00	00:00	�쐬
//			 �F2024/01/21	23:32	Copy��Parent�։��C�Bshared_ptr�𓱓�
//			 �F2024/12/13	00:05	�x�N�^�[�A�A���O���̑o�����ϊ��֐��ǉ��E�R�����g�A�E�g�̒ǉ�
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____TRANSFORM_H_____
#define _____TRANSFORM_H_____

/**
 * @brief		Transform��
 * @details		{�N���X�̏ڍא���}
 * @author		{*�쐬��}
 * @bug			{�����ł��Ă��Ȃ��o�O�̐���}
 * @warning		{�x��}
 * @remark		{����}
 * @note		{�o������}
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