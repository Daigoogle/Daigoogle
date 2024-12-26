#include "Vectors.hxx"
#include <cmath>

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								fVec2								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool operator==(const fVec2& Left, const fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool operator!=(const fVec2& Left, const fVec2& Right)
{
	return !(Left == Right);
}
bool operator>(const fVec2& Left, const fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool operator<(const fVec2& Left, const fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool operator>=(const fVec2& Left, const fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool operator<=(const fVec2& Left, const fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
fVec2 operator+(const fVec2& Left, const fVec2& Right)
{
	fVec2 ans;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
fVec2 operator-(const fVec2& Left, const fVec2& Right)
{
	fVec2 ans;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
fVec2 operator*(const fVec2& Left, const fVec2& Right)
{
	fVec2 ans;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
fVec2 operator/(const fVec2& Left, const fVec2& Right)
{
	fVec2 ans;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
	{
		if (Right.v[i] != 0.0f)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}
fVec2 operator+(const fVec2& Left, const float Right)
{
	fVec2 ans;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
fVec2 operator-(const fVec2& Left, const float Right)
{
	fVec2 ans;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
fVec2 operator*(const fVec2& Left, const float Right)
{
	fVec2 ans;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
fVec2 operator/(const fVec2& Left, const float Right)
{
	fVec2 ans;
	for (int i = 0; i < fVec2::_SuffixNum; i++)
	{
		if (Right != 0.0f)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								fVec3								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool operator==(const fVec3& Left, const fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool operator!=(const fVec3& Left, const fVec3& Right)
{
	return !(Left == Right);
}
bool operator>(const fVec3& Left, const fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool operator<(const fVec3& Left, const fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool operator>=(const fVec3& Left, const fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool operator<=(const fVec3& Left, const fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
fVec3 operator+(const fVec3& Left, const fVec3& Right)
{
	fVec3 ans;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
fVec3 operator-(const fVec3& Left, const fVec3& Right)
{
	fVec3 ans;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
fVec3 operator*(const fVec3& Left, const fVec3& Right)
{
	fVec3 ans;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
fVec3 operator/(const fVec3& Left, const fVec3& Right)
{
	fVec3 ans;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
	{
		if (Right.v[i] != 0.0f)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}
fVec3 operator+(const fVec3& Left, const float Right)
{
	fVec3 ans;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
fVec3 operator-(const fVec3& Left, const float Right)
{
	fVec3 ans;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
fVec3 operator*(const fVec3& Left, const float Right)
{
	fVec3 ans;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
fVec3 operator/(const fVec3& Left, const float Right)
{
	fVec3 ans;
	for (int i = 0; i < fVec3::_SuffixNum; i++)
	{
		if (Right != 0.0f)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								fVec4								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool operator==(const fVec4& Left, const fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool operator!=(const fVec4& Left, const fVec4& Right)
{
	return !(Left == Right);
}
bool operator>(const fVec4& Left, const fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool operator<(const fVec4& Left, const fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool operator>=(const fVec4& Left, const fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool operator<=(const fVec4& Left, const fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
fVec4 operator+(const fVec4& Left, const fVec4& Right)
{
	fVec4 ans;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
fVec4 operator-(const fVec4& Left, const fVec4& Right)
{
	fVec4 ans;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
fVec4 operator*(const fVec4& Left, const fVec4& Right)
{
	fVec4 ans;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
fVec4 operator/(const fVec4& Left, const fVec4& Right)
{
	fVec4 ans;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
	{
		if (Right.v[i] != 0.0f)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}
fVec4 operator+(const fVec4& Left, const float Right)
{
	fVec4 ans;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
fVec4 operator-(const fVec4& Left, const float Right)
{
	fVec4 ans;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
fVec4 operator*(const fVec4& Left, const float Right)
{
	fVec4 ans;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
fVec4 operator/(const fVec4& Left, const float Right)
{
	fVec4 ans;
	for (int i = 0; i < fVec4::_SuffixNum; i++)
	{
		if (Right != 0.0f)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								nVec2								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool operator==(const nVec2& Left, const nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool operator!=(const nVec2& Left, const nVec2& Right)
{
	return !(Left == Right);
}
bool operator>(const nVec2& Left, const nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool operator<(const nVec2& Left, const nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool operator>=(const nVec2& Left, const nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool operator<=(const nVec2& Left, const nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
nVec2 operator+(const nVec2& Left, const nVec2& Right)
{
	nVec2 ans;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
nVec2 operator-(const nVec2& Left, const nVec2& Right)
{
	nVec2 ans;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
nVec2 operator*(const nVec2& Left, const nVec2& Right)
{
	nVec2 ans;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
nVec2 operator/(const nVec2& Left, const nVec2& Right)
{
	nVec2 ans;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
	{
		if (Right.v[i] != 0)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0;
	}
	return ans;
}
nVec2 operator+(const nVec2& Left, const int Right)
{
	nVec2 ans;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
nVec2 operator-(const nVec2& Left, const int Right)
{
	nVec2 ans;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
nVec2 operator*(const nVec2& Left, const int Right)
{
	nVec2 ans;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
nVec2 operator/(const nVec2& Left, const int Right)
{
	nVec2 ans;
	for (int i = 0; i < nVec2::_SuffixNum; i++)
	{
		if (Right != 0)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								nVec3								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool operator==(const nVec3& Left, const nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool operator!=(const nVec3& Left, const nVec3& Right)
{
	return !(Left == Right);
}
bool operator>(const nVec3& Left, const nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool operator<(const nVec3& Left, const nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool operator>=(const nVec3& Left, const nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool operator<=(const nVec3& Left, const nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
nVec3 operator+(const nVec3& Left, const nVec3& Right)
{
	nVec3 ans;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
nVec3 operator-(const nVec3& Left, const nVec3& Right)
{
	nVec3 ans;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
nVec3 operator*(const nVec3& Left, const nVec3& Right)
{
	nVec3 ans;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
nVec3 operator/(const nVec3& Left, const nVec3& Right)
{
	nVec3 ans;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
	{
		if (Right.v[i] != 0)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0;
	}
	return ans;
}
nVec3 operator+(const nVec3& Left, const int Right)
{
	nVec3 ans;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
nVec3 operator-(const nVec3& Left, const int Right)
{
	nVec3 ans;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
nVec3 operator*(const nVec3& Left, const int Right)
{
	nVec3 ans;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
nVec3 operator/(const nVec3& Left, const int Right)
{
	nVec3 ans;
	for (int i = 0; i < nVec3::_SuffixNum; i++)
	{
		if (Right != 0)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								nVec4								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool operator==(const nVec4& Left, const nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool operator!=(const nVec4& Left, const nVec4& Right)
{
	return !(Left == Right);
}
bool operator>(const nVec4& Left, const nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool operator<(const nVec4& Left, const nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool operator>=(const nVec4& Left, const nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool operator<=(const nVec4& Left, const nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
nVec4 operator+(const nVec4& Left, const nVec4& Right)
{
	nVec4 ans;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
nVec4 operator-(const nVec4& Left, const nVec4& Right)
{
	nVec4 ans;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
nVec4 operator*(const nVec4& Left, const nVec4& Right)
{
	nVec4 ans;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
nVec4 operator/(const nVec4& Left, const nVec4& Right)
{
	nVec4 ans;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
	{
		if (Right.v[i] != 0)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0;
	}
	return ans;
}
nVec4 operator+(const nVec4& Left, const int Right)
{
	nVec4 ans;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
nVec4 operator-(const nVec4& Left, const int Right)
{
	nVec4 ans;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
nVec4 operator*(const nVec4& Left, const int Right)
{
	nVec4 ans;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
nVec4 operator/(const nVec4& Left, const int Right)
{
	nVec4 ans;
	for (int i = 0; i < nVec4::_SuffixNum; i++)
	{
		if (Right != 0)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0;
	}
	return ans;
}

float Vec::length(const fVec3& Vector)
{
	return powf(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z, 0.5f);
}
fVec3 Vec::Nomalize(fVec3 Vector)
{
	return (Vector / length(Vector));
}

#ifdef DIRECTX11_PRJ
DirectX::XMFLOAT3 Vec::ToXMFLOAT3(const fVec3& Vector)
{
	return { Vector.x, Vector.y, Vector.z };
}
#endif // DIRECTX11_PRJ