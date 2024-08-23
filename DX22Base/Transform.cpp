#include "Transform.h"

const static float c_fPi_180 = 3.1415926535f / 180.0f;

Transform::Transform() :m_localPosition(), m_localRotation(), m_localScale(), m_Parent(), m_HaveParent(false)
{
	m_localScale = m_localScale + 1.0f;
}
Transform::~Transform()
{
	m_Parent = nullptr;
}

void Transform::Init()
{
}
void Transform::Update()
{
}
void Transform::UnInit()
{
}

void  Transform::SetLocalPosition(fVec3 Get)
{
	ParentCheck();
	m_localPosition = Get;
}
fVec3 Transform::GetLocalPosition()
{
	ParentCheck();
	return m_localPosition;
}
void  Transform::SetLocalRotation(fVec3 Get)
{
	ParentCheck();
	m_localRotation = Get;
}
fVec3 Transform::GetLocalRotation()
{
	ParentCheck();
	return m_localRotation;
}
void  Transform::SetLocalScale(fVec3 Get)
{
	ParentCheck();
	m_localScale = Get;
}
fVec3 Transform::GetLocalScale()
{
	ParentCheck();
	return m_localScale;
}

void  Transform::SetWorldPosition(fVec3 Get)
{
	if (m_Parent)
		m_localPosition = PositionWorldToLocal(Get, m_Parent);
	else
		m_localPosition = Get;
}
fVec3 Transform::GetWorldPosition()
{
	if (m_Parent)
		return PositionLocalToWorld(m_localPosition, m_Parent);
	else
		return m_localPosition;
}
void  Transform::SetWorldRotation(fVec3 Get)
{
	if (m_Parent)
		m_localRotation = RotationWorldToLocal(Get, m_Parent);
	else
		m_localRotation = Get;
}
fVec3 Transform::GetWorldRotation()
{
	if (m_Parent)
		return RotationLocalToWorld(m_localRotation, m_Parent);
	else
		return m_localRotation;
}
void  Transform::SetWorldScale(fVec3 Get)
{
	if (m_Parent)
		m_localScale = ScaleWorldToLocal(Get, m_Parent);
	else
		m_localScale = Get;
}
fVec3 Transform::GetWorldScale()
{
	if (m_Parent)
		return ScaleLocalToWorld(m_localScale, m_Parent);
	else
		return m_localScale;
}

void Transform::SetParent(Transform* tf)
{
	m_Parent = tf;
}
void Transform::RemoveParent()
{
	m_Parent = nullptr;;
}

DirectX::XMFLOAT4X4 Transform::GetWorldMatrix(void)
{
	//----------Œ»Ý‚Ìó‘Ô‚ðŽæ“¾----------
	fVec3 worldPosition = GetWorldPosition();
	fVec3 worldRotate = GetWorldRotation();
	fVec3 worldScale = GetWorldScale();

	//----------ŠeŽí•ÏŠ·s—ñ‚ð‹‚ß‚é----------
	const float c_fPi = 3.141592f;
	DirectX::XMMATRIX transMat = DirectX::XMMatrixTranslation(worldPosition.x, worldPosition.y, worldPosition.z);
	DirectX::XMMATRIX rotXMat = DirectX::XMMatrixRotationX(worldRotate.x * (c_fPi / 180.0f));
	DirectX::XMMATRIX rotYMat = DirectX::XMMatrixRotationY(worldRotate.y * (c_fPi / 180.0f));
	DirectX::XMMATRIX rotZMat = DirectX::XMMatrixRotationZ(worldRotate.z * (c_fPi / 180.0f));
	DirectX::XMMATRIX scaleMat = DirectX::XMMatrixScaling(worldScale.x, worldScale.y, worldScale.z);

	DirectX::XMMATRIX mat = scaleMat * rotXMat * rotYMat * rotZMat * transMat;// •ÏŠ·À•W‚ðŠi”[
	mat = DirectX::XMMatrixTranspose(mat);// “]’us—ñ‚ð‹‚ß‚é

	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);// “Ç‚ÝŽæ‚èê—pŒ^‚É•ÏŠ·‚µ‚ÄŠi”[‚·‚é

	return fMat;
}

void Transform::ParentCheck()
{
	if (!m_HaveParent && m_Parent)
	{
		m_localPosition = PositionWorldToLocal(m_localPosition, m_Parent);
		m_localRotation = RotationWorldToLocal(m_localRotation, m_Parent);
		m_localScale = ScaleWorldToLocal(m_localScale, m_Parent);
		m_HaveParent = true;
	}
	else if (m_HaveParent && !m_Parent)
	{
		m_localPosition = PositionLocalToWorld(m_localPosition, m_Parent);
		m_localRotation = RotationLocalToWorld(m_localRotation, m_Parent);
		m_localScale = ScaleLocalToWorld(m_localScale, m_Parent);
		m_HaveParent = false;
	}
}
fVec3 Transform::PositionLocalToWorld(fVec3 localPos, Transform* pParentTransform)
{
	fVec3 worldPos = localPos;
	fVec3 parentScale = pParentTransform->GetLocalScale();
	worldPos.x *= parentScale.x;
	worldPos.y *= parentScale.y;
	worldPos.z *= parentScale.z;

	// e‚É‡‚í‚¹‚Ä‰ñ“]
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	// ƒxƒNƒgƒ‹‚ð‰ñ“]
	const static float c_fPi = 3.1415926535f;
	DirectX::XMMATRIX rotXMat = DirectX::XMMatrixRotationX(parentRot.x * c_fPi_180);
	DirectX::XMMATRIX rotYMat = DirectX::XMMatrixRotationY(parentRot.y * c_fPi_180);
	DirectX::XMMATRIX rotZMat = DirectX::XMMatrixRotationZ(parentRot.z * c_fPi_180);
	DirectX::XMMATRIX rotMat = rotXMat * rotYMat * rotZMat;
	DirectX::XMVECTOR rotPos = DirectX::XMVector3TransformCoord(
		DirectX::XMVectorSet(worldPos.x, worldPos.y, worldPos.z, 1.0f), rotMat
	);
	DirectX::XMFLOAT3 rotPosFloatVec;
	DirectX::XMStoreFloat3(&rotPosFloatVec, rotPos);

	worldPos = { rotPosFloatVec.x, rotPosFloatVec.y, rotPosFloatVec.z };

	// e‚©‚ç‚Ì‘Š‘ÎÀ•W‚©‚çƒ[ƒ‹ƒhÀ•W‚É’¼‚·
	fVec3 parentPos = pParentTransform->GetLocalPosition();
	worldPos = worldPos + parentPos;

	// ƒ[ƒ‹ƒhÀ•W‚ðŒvŽZ
	return worldPos;

}
fVec3 Transform::PositionWorldToLocal(fVec3 worldPos, Transform* pParentTransform)
{
	// À•W‚ðÝ’è
	// ‘Š‘ÎƒxƒNƒgƒ‹‚ðŒvŽZ
	fVec3 relPos = worldPos - pParentTransform->GetLocalPosition();

	// e‚Ì‰ñ“]—Ê‚Æ‹t“]
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	parentRot = parentRot * -1.0f;
	DirectX::XMMATRIX rotXMat = DirectX::XMMatrixRotationX(parentRot.x * c_fPi_180);
	DirectX::XMMATRIX rotYMat = DirectX::XMMatrixRotationY(parentRot.y * c_fPi_180);
	DirectX::XMMATRIX rotZMat = DirectX::XMMatrixRotationZ(parentRot.z * c_fPi_180);
	DirectX::XMMATRIX rotMat = rotXMat * rotYMat * rotZMat;
	DirectX::XMVECTOR rotPos = DirectX::XMVector3TransformCoord(
		DirectX::XMVectorSet(worldPos.x, worldPos.y, worldPos.z, 1.0f), rotMat
	);
	DirectX::XMFLOAT3 rotPosFloatVec;
	DirectX::XMStoreFloat3(&rotPosFloatVec, rotPos);

	worldPos = { rotPosFloatVec.x, rotPosFloatVec.y, rotPosFloatVec.z };

	// e‚ÌŠg‘å—¦‚Åk¬
	fVec3 parentScale = pParentTransform->GetLocalScale();
	relPos.x = parentScale.x > 0.0f ? relPos.x / parentScale.x : 0.0f;
	relPos.y = parentScale.y > 0.0f ? relPos.y / parentScale.y : 0.0f;
	relPos.z = parentScale.z > 0.0f ? relPos.z / parentScale.z : 0.0f;

	return relPos;

}
fVec3 Transform::RotationLocalToWorld(fVec3 localRot, Transform* pParentTransform)
{
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	return localRot + parentRot;
}
fVec3 Transform::RotationWorldToLocal(fVec3 worldRot, Transform* pParentTransform)
{
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	return worldRot - parentRot;
}
fVec3 Transform::ScaleLocalToWorld(fVec3 localScale,  Transform* pParentTransform)
{
	fVec3 parentScale = pParentTransform->GetLocalScale();
	return localScale * parentScale;
}
fVec3 Transform::ScaleWorldToLocal(fVec3 worldScale,  Transform* pParentTransform)
{
	fVec3 parentScale = pParentTransform->GetLocalScale();
	return worldScale / parentScale;
}