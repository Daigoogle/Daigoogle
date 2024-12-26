#include "Transform.hxx"

using namespace tf;

const static float c_fPi_180 = 3.1415926535f / 180.0f;

Transform::Transform() 
	: m_localPosition()
	, m_localRotation()
	, m_localScale()
	, m_Parent(nullptr)
	, m_HaveParent(false)
	, m_IsLook(false)
	, m_LookPoint(nullptr)
{
	m_localScale = m_localScale + 1.0f;
}
Transform::~Transform()
{
	m_Parent = nullptr;
}

void Transform::Update()
{
	if (m_IsLook)// Billboard
	{
		fVec3 LookVec = GetWorldPosition() - m_LookPoint->GetWorldPosition() ;
		fVec3 Nom = Vec::Nomalize(LookVec);
		fVec3 LookRot = {atan2f(Nom.y,sqrtf(Nom.x * Nom.x + Nom.z * Nom.z)) * -57.2957795f,atan2f(Nom.x,Nom.z) * 57.2957795f,0.0f };
		SetLocalRotation(LookRot);
	}
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
	m_Parent = nullptr;
}

void Transform::LookPoint(Transform* Point)
{
	m_IsLook = true;
	m_LookPoint = Point;
}

DirectX::XMFLOAT4X4 Transform::GetWorldMatrix(void)
{
	//----------現在の状態を取得----------
	fVec3 worldPosition = GetWorldPosition();
	fVec3 worldRotate = GetWorldRotation();
	fVec3 worldScale = GetWorldScale();

	//----------各種変換行列を求める----------
	const float c_fPi = 3.141592f;
	DirectX::XMMATRIX transMat = DirectX::XMMatrixTranslation(worldPosition.x, worldPosition.y, worldPosition.z);
	DirectX::XMMATRIX rotXMat = DirectX::XMMatrixRotationX(worldRotate.x * (c_fPi / 180.0f));
	DirectX::XMMATRIX rotYMat = DirectX::XMMatrixRotationY(worldRotate.y * (c_fPi / 180.0f));
	DirectX::XMMATRIX rotZMat = DirectX::XMMatrixRotationZ(worldRotate.z * (c_fPi / 180.0f));
	DirectX::XMMATRIX scaleMat = DirectX::XMMatrixScaling(worldScale.x, worldScale.y, worldScale.z);

	DirectX::XMMATRIX mat = scaleMat * rotXMat * rotYMat * rotZMat * transMat;// 変換座標を格納
	mat = DirectX::XMMatrixTranspose(mat);// 転置行列を求める

	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);// 読み取り専用型に変換して格納する

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






fVec3 tf::PositionLocalToWorld(fVec3 localPos, Transform* pParentTransform)
{
	fVec3 worldPos = localPos;
	fVec3 parentScale = pParentTransform->GetLocalScale();
	worldPos.x *= parentScale.x;
	worldPos.y *= parentScale.y;
	worldPos.z *= parentScale.z;

	// 親に合わせて回転
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	// ベクトルを回転
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

	// 親からの相対座標からワールド座標に直す
	fVec3 parentPos = pParentTransform->GetLocalPosition();
	worldPos = worldPos + parentPos;

	// ワールド座標を計算
	return worldPos;

}
fVec3 tf::PositionWorldToLocal(fVec3 worldPos, Transform* pParentTransform)
{
	// 座標を設定
	// 相対ベクトルを計算
	fVec3 relPos = worldPos - pParentTransform->GetLocalPosition();

	// 親の回転量と逆転
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

	// 親の拡大率で縮小
	fVec3 parentScale = pParentTransform->GetLocalScale();
	relPos.x = parentScale.x > 0.0f ? relPos.x / parentScale.x : 0.0f;
	relPos.y = parentScale.y > 0.0f ? relPos.y / parentScale.y : 0.0f;
	relPos.z = parentScale.z > 0.0f ? relPos.z / parentScale.z : 0.0f;

	return relPos;

}
fVec3 tf::RotationLocalToWorld(fVec3 localRot, Transform* pParentTransform)
{
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	return localRot + parentRot;
}
fVec3 tf::RotationWorldToLocal(fVec3 worldRot, Transform* pParentTransform)
{
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	return worldRot - parentRot;
}
fVec3 tf::ScaleLocalToWorld(fVec3 localScale,  Transform* pParentTransform)
{
	fVec3 parentScale = pParentTransform->GetLocalScale();
	return localScale * parentScale;
}
fVec3 tf::ScaleWorldToLocal(fVec3 worldScale,  Transform* pParentTransform)
{
	fVec3 parentScale = pParentTransform->GetLocalScale();
	return worldScale / parentScale;
}

// ベクトルから回転を求める
fVec3 tf::VectorToRotation(fVec3 vec)
{
	vec = Vec::Nomalize(vec);
	fVec3 rot;
	rot.x = atan2f(vec.y, sqrtf(vec.x * vec.x + vec.z * vec.z)) * -57.2957795f;
	rot.y = atan2f(vec.x, vec.z) * 57.2957795f;
	rot.z = 0.0f;
	return rot;
}

// 回転から正規化されたベクトルを求める
fVec3 tf::RotationToVector(fVec3 rot)
{
	fVec3 vec;
	vec.x = cosf(rot.x * c_fPi_180) * sinf(rot.y * c_fPi_180);
	vec.y = sinf(rot.x * c_fPi_180);
	vec.z = cosf(rot.x * c_fPi_180) * cosf(rot.y * c_fPi_180);
	vec = Vec::Nomalize(vec);
	return vec;
}