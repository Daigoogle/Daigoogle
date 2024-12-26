#include "Geometory.h"

const int nFaceCnt = 80;
const float fHight = 0.5f;
const float pi = 3.14159265358979323846f;

void Geometory::MakeBox()
{
	// ���f�[�^�� 
	Vertex vtx[] = {
		//-Z��
		{{-0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//0
		{{ 0.5f, 0.5f,-0.5f},{1.0f,0.0f}},//1
		{{-0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//2
		{{ 0.5f,-0.5f,-0.5f},{1.0f,1.0f}},//3
		//Z��
		{{-0.5f, 0.5f,0.5f},{0.0f,0.0f}},//4
		{{ 0.5f, 0.5f,0.5f},{1.0f,0.0f}},//5
		{{-0.5f,-0.5f,0.5f},{0.0f,1.0f}},//6
		{{ 0.5f,-0.5f,0.5f},{1.0f,1.0f}},//7
		//-x
		{{ -0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//0
		{{ -0.5f, 0.5f,0.5f},{1.0f,0.0f}},//4
		{{ -0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//2
		{{ -0.5f,-0.5f,0.5f},{1.0f,1.0f}},//6
		//x
		{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//1
		{{ 0.5f, 0.5f,0.5f},{1.0f,0.0f}},//5
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//3
		{{ 0.5f,-0.5f,0.5f},{1.0f,1.0f}},//7
		//-y
		{{ -0.5f, -0.5f,-0.5f},{0.0f,0.0f}},//2
		{{ -0.5f, -0.5f,0.5f},{1.0f,0.0f}},//6
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//3
		{{ 0.5f,-0.5f,0.5f},{1.0f,1.0f}},//5

		//y
		{{ -0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//0
		{{ -0.5f, 0.5f,0.5f},{1.0f,0.0f}},//4
		{{ 0.5f,0.5f,-0.5f},{0.0f,1.0f}},//1
		{{ 0.5f,0.5f,0.5f},{1.0f,1.0f}},//5
	};

	int idx[] = {
		0,1,2,		1,3,2,		//-Z��
		6,5,4,		6,7,5,		//Z��
		10,9,0,		10,11,9,	//-x
		12,13,14,	13,15,14,	//x
		18,17,16,	18,19,17,	//-y
		0,21,22,	21,23,22,	//y

	};
	// �o�b�t�@�̍쐬
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);
	desc.vtxSize = 20;//20;
	desc.pIdx = idx;
	desc.idxCount = 36;
	desc.idxSize = sizeof(int);//4;
	desc.topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pBox = New(MeshBuffer)(desc);
}

void Geometory::MakeCylinder()
{
	//--- ���_�̍쐬
	Vertex vtx[nFaceCnt * 4 + 2];
	for (int i = 0; i < nFaceCnt; i++)
	{
		float x = sinf(i * 2 * pi / nFaceCnt) * 0.5f;
		float z = cosf(i * 2 * pi / nFaceCnt) * 0.5f;
		vtx[i] = { {x, fHight,z},{x + 0.5f,z + 0.5f} };
		vtx[i + nFaceCnt] = { {x, fHight,z},{2.0f / nFaceCnt * i,0.0f} };
		vtx[i + nFaceCnt * 2 + 1] = { {x,-fHight,z},{2.0f / nFaceCnt * i,1.0f} };
		vtx[i + nFaceCnt * 3 + 2] = { {x,-fHight,z},{x + 0.5f,z + 0.5f} };
	}
	vtx[nFaceCnt * 2] = { {sinf(0) * 0.5f, fHight,cosf(0) * 0.5f},{1.0f,0.0f} };
	vtx[nFaceCnt * 3 + 1] = { {sinf(0) * 0.5f,-fHight,cosf(0) * 0.5f},{1.0f,1.0f} };

	//--- �C���f�b�N�X�̍쐬
	int idx[(nFaceCnt - 1) * 12];
	// �V�ʁA���
	for (int i = 0; i < nFaceCnt - 2; i++)
	{
		idx[i * 3] = 0;
		idx[i * 3 + 1] = i + 1;
		idx[i * 3 + 2] = i + 2;
		idx[(nFaceCnt - 1) * 12 - 1 - i * 3] = nFaceCnt * 4 + 2 - 1;		// 12 ... 4 * 3
		idx[(nFaceCnt - 1) * 12 - 2 - i * 3] = nFaceCnt * 4 + 2 - (i + 3);
		idx[(nFaceCnt - 1) * 12 - 3 - i * 3] = nFaceCnt * 4 + 2 - (i + 2);
	}
	// ����
	for (int i = 0; i < nFaceCnt; i++)
	{
		idx[(i * 6) + (nFaceCnt - 2) * 3] = nFaceCnt + i + 1;
		idx[(i * 6) + (nFaceCnt - 2) * 3 + 1] = nFaceCnt + i;
		idx[(i * 6) + (nFaceCnt - 2) * 3 + 2] = nFaceCnt * 2 + 1 + i;
		idx[(i * 6) + (nFaceCnt - 2) * 3 + 3] = nFaceCnt * 2 + 2 + i;
		idx[(i * 6) + (nFaceCnt - 2) * 3 + 4] = nFaceCnt + i + 1;
		idx[(i * 6) + (nFaceCnt - 2) * 3 + 5] = nFaceCnt * 2 + 1 + i;
	}

	//--- �o�b�t�@�̍쐬
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx); //���_�̐�
	desc.vtxSize = sizeof(Vertex); //���_�P������̃f�[�^�T�C�Y
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pCylinder = New(MeshBuffer)(desc);
}

void Geometory::MakeSphere()
{
	//--- ���_�̍쐬

	//--- �C���f�b�N�X�̍쐬

	// �o�b�t�@�̍쐬
}