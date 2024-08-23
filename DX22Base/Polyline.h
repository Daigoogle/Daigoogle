#ifndef __POLYLINE_H__
#define __POLYLINE_H__

#include "MeshBuffer.h"
#include "Shader.h"
#include <DirectXMath.h>

class Polyline
{
protected:
	struct ControlPoint
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		float bold;
		DirectX::XMFLOAT4 color;
	};
	using ControlPoints = std::vector<ControlPoint>;

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT4 color;
	};

	struct Line
	{
		ControlPoints controlPoints;
		DirectX::XMFLOAT2 uvScale;
		DirectX::XMFLOAT2 uvOffset;
		Vertex* ptr;
	};
	using Lines = std::vector<Line>;

public:
	using LineID = int;

public:
	static const LineID LINE_NONE = -1;

public:
	Polyline(int maxVertices = 1000);
	~Polyline();
	virtual void Update();
	void Draw();

	void SetView(DirectX::XMFLOAT4X4 view);
	void SetProjection(DirectX::XMFLOAT4X4 proj);
	void SetVertexShader(VertexShader* vs);
	void SetPixelShader(PixelShader* ps);
	void SetTexture(Texture* pTexture);

	LineID AddLine(int controlPointNum);


protected:
	virtual void InitControlPoints(LineID id, ControlPoints& controlPoints);
	virtual void UpdateControlPoints(LineID id, ControlPoints& controlPoints) = 0;


private:
	static VertexShader* m_pDefVS;
	static PixelShader* m_pDefPS;
	static int m_shaderRefCount;

private:
	Lines m_lines;
	int m_useVtxCount;
	MeshBuffer* m_pMesh;
	Vertex* m_pVertices;

	VertexShader* m_pVS;
	PixelShader* m_pPS;
	DirectX::XMFLOAT4X4 m_matrix[2];
	Texture* m_pTexture;
};

#endif // __POLYLINE_H__