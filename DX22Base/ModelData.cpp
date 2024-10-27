//MogelRendererコンポーネント
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <mbstring.h>
#include "ModelData.h"
#include "DirectX11SetUp.h"
#include "CreateTexture.h"

bool MODEL::Load(const std::string& path) {

	MODEL_OBJ modelObj;
	{
		char dir[MAX_PATH];
		strcpy(dir, path.c_str());
		unsigned char* pbs = _mbsrchr((unsigned char*)dir, '\\');
		unsigned char* psl = _mbsrchr((unsigned char*)dir, '/');
		if (pbs) {
			if (psl) {
				if (pbs > psl)
					*pbs = '\0';
				else
					*psl = '\0';
			}
			else {
				*pbs = '\0';
			}
		}
		else {
			if (psl) {
				*psl = '\0';
			}
		}


		DirectX::XMFLOAT3* positionArray;
		DirectX::XMFLOAT3* normalArray;
		DirectX::XMFLOAT2* texcoordArray;

		unsigned int	positionNum = 0;
		unsigned int	normalNum = 0;
		unsigned int	texcoordNum = 0;
		unsigned int	vertexNum = 0;
		unsigned int	indexNum = 0;
		unsigned int	in = 0;
		unsigned int	subsetNum = 0;

		MODEL_MATERIAL* materialArray = nullptr;
		unsigned int	materialNum = 0;

		char str[256];
		char* s;
		char c;


		FILE* file;
		file = fopen(path.c_str(), "rt");
		assert(file);



		//要素数カウント
		while (true)
		{
			fscanf(file, "%s", str);

			if (feof(file) != 0)
				break;

			if (strcmp(str, "v") == 0){
				positionNum++;
			}
			else if (strcmp(str, "vn") == 0){
				normalNum++;
			}
			else if (strcmp(str, "vt") == 0){
				texcoordNum++;
			}
			else if (strcmp(str, "usemtl") == 0){
				subsetNum++;
			}
			else if (strcmp(str, "f") == 0){
				in = 0;

				do {
					fscanf(file, "%s", str);
					vertexNum++;
					in++;
					c = fgetc(file);
				} while (c != '\n' && c != '\r');

				//四角は三角に分割
				if (in == 4)
					in = 6;

				indexNum += in;
			}
		}

		//メモリ確保
		positionArray = New(DirectX::XMFLOAT3)[positionNum];
		normalArray = New(DirectX::XMFLOAT3)[normalNum];
		texcoordArray = New(DirectX::XMFLOAT2)[texcoordNum];

		modelObj.VertexArray = New(VERTEX_3D)[vertexNum];
		modelObj.VertexNum = vertexNum;

		modelObj.IndexArray = New(unsigned int)[indexNum];
		modelObj.IndexNum = indexNum;

		modelObj.SubsetArray = New(SUBSET)[subsetNum];
		modelObj.SubsetNum = subsetNum;

		//要素読込
		DirectX::XMFLOAT3* position = positionArray;
		DirectX::XMFLOAT3* normal = normalArray;
		DirectX::XMFLOAT2* texcoord = texcoordArray;

		unsigned int vc = 0;
		unsigned int ic = 0;
		unsigned int sc = 0;


		fseek(file, 0, SEEK_SET);

		while (true)
		{
			fscanf(file, "%s", str);

			if (feof(file) != 0)
				break;

			if (strcmp(str, "mtllib") == 0)
			{
				//マテリアルファイル
				fscanf(file, "%s", str);

				char cpath[256];
				strcpy(cpath, dir);
				strcat(cpath, "\\");
				strcat(cpath, str);

				{

					char dir[MAX_PATH];
					strcpy(dir, path.c_str());
					unsigned char* pbs = _mbsrchr((unsigned char*)dir, '\\');
					unsigned char* psl = _mbsrchr((unsigned char*)dir, '/');
					if (pbs) {
						if (psl) {
							if (pbs > psl)
								*pbs = '\0';
							else
								*psl = '\0';
						}
						else {
							*pbs = '\0';
						}
					}
					else {
						if (psl) {
							*psl = '\0';
						}
					}



					char str[256];

					FILE* file;
					file = fopen(path.c_str(), "rt");
					assert(file);

					//要素数カウント
					while (true)
					{
						fscanf(file, "%s", str);

						if (feof(file) != 0)
							break;


						if (strcmp(str, "newmtl") == 0)
						{
							materialNum++;
						}
					}


					//メモリ確保
					materialArray = New(MODEL_MATERIAL)[materialNum];


					//要素読込
					int mc = -1;

					fseek(file, 0, SEEK_SET);

					while (true)
					{
						fscanf(file, "%s", str);

						if (feof(file) != 0)
							break;


						if (strcmp(str, "newmtl") == 0)
						{
							//マテリアル名
							mc++;
							fscanf(file, "%s", materialArray[mc].Name);
							strcpy(materialArray[mc].TextureName, "");

							materialArray[mc].Material.Emission.x = 0.0f;
							materialArray[mc].Material.Emission.y = 0.0f;
							materialArray[mc].Material.Emission.z = 0.0f;
							materialArray[mc].Material.Emission.w = 0.0f;
						}
						else if (strcmp(str, "Ka") == 0)
						{
							//アンビエント
							fscanf(file, "%f", &materialArray[mc].Material.Ambient.x);
							fscanf(file, "%f", &materialArray[mc].Material.Ambient.y);
							fscanf(file, "%f", &materialArray[mc].Material.Ambient.z);
							materialArray[mc].Material.Ambient.w = 1.0f;
						}
						else if (strcmp(str, "Kd") == 0)
						{
							//ディフューズ
							fscanf(file, "%f", &materialArray[mc].Material.Diffuse.x);
							fscanf(file, "%f", &materialArray[mc].Material.Diffuse.y);
							fscanf(file, "%f", &materialArray[mc].Material.Diffuse.z);
							materialArray[mc].Material.Diffuse.w = 1.0f;
						}
						else if (strcmp(str, "Ks") == 0)
						{
							//スペキュラ
							fscanf(file, "%f", &materialArray[mc].Material.Specular.x);
							fscanf(file, "%f", &materialArray[mc].Material.Specular.y);
							fscanf(file, "%f", &materialArray[mc].Material.Specular.z);
							materialArray[mc].Material.Specular.w = 1.0f;
						}
						else if (strcmp(str, "Ns") == 0)
						{
							//スペキュラ強度
							fscanf(file, "%f", &materialArray[mc].Material.Shininess);
						}
						else if (strcmp(str, "d") == 0)
						{
							//アルファ
							fscanf(file, "%f", &materialArray[mc].Material.Diffuse.w);
						}
						else if (strcmp(str, "map_Kd") == 0)
						{
							//テクスチャ
							fscanf(file, "%s", str);

							char path[256];
							strcpy(path, dir);
							strcat(path, "\\");
							strcat(path, str);

							strcat(materialArray[mc].TextureName, path);
						}
					}

					fclose(file);
				}
			}
			else if (strcmp(str, "o") == 0)
			{
				//オブジェクト名
				fscanf(file, "%s", str);
			}
			else if (strcmp(str, "v") == 0)
			{
				//頂点座標
				fscanf(file, "%f", &position->x);
				fscanf(file, "%f", &position->y);
				fscanf(file, "%f", &position->z);
				position++;
			}
			else if (strcmp(str, "vn") == 0)
			{
				//法線
				fscanf(file, "%f", &normal->x);
				fscanf(file, "%f", &normal->y);
				fscanf(file, "%f", &normal->z);
				normal++;
			}
			else if (strcmp(str, "vt") == 0)
			{
				//テクスチャ座標
				fscanf(file, "%f", &texcoord->x);
				fscanf(file, "%f", &texcoord->y);
				texcoord->x = 1.0f - texcoord->x;
				texcoord->y = 1.0f - texcoord->y;
				texcoord++;
			}
			else if (strcmp(str, "usemtl") == 0)
			{
				//マテリアル
				fscanf(file, "%s", str);

				if (sc != 0)
					modelObj.SubsetArray[sc - 1].IndexNum = ic - modelObj.SubsetArray[sc - 1].StartIndex;

				modelObj.SubsetArray[sc].StartIndex = ic;


				for (unsigned int i = 0; i < materialNum; i++)
				{
					if (strcmp(str, materialArray[i].Name) == 0)
					{
						modelObj.SubsetArray[sc].Material.Material = materialArray[i].Material;
						strcpy(modelObj.SubsetArray[sc].Material.TextureName, materialArray[i].TextureName);
						strcpy(modelObj.SubsetArray[sc].Material.Name, materialArray[i].Name);

						break;
					}
				}

				sc++;

			}
			else if (strcmp(str, "f") == 0)
			{
				//面
				in = 0;

				do
				{
					fscanf(file, "%s", str);

					s = strtok(str, "/");
					modelObj.VertexArray[vc].Position = positionArray[atoi(s) - 1];
					if (s[strlen(s) + 1] != '/')
					{
						//テクスチャ座標が存在しない場合もある
						s = strtok(nullptr, "/");
						modelObj.VertexArray[vc].TexCoord = texcoordArray[atoi(s) - 1];
					}
					s = strtok(nullptr, "/");
					modelObj.VertexArray[vc].Normal = normalArray[atoi(s) - 1];

					modelObj.VertexArray[vc].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

					modelObj.IndexArray[ic] = vc;
					ic++;
					vc++;

					in++;
					c = fgetc(file);
				} while (c != '\n' && c != '\r');

				//四角は三角に分割
				if (in == 4)
				{
					modelObj.IndexArray[ic] = vc - 4;
					ic++;
					modelObj.IndexArray[ic] = vc - 2;
					ic++;
				}
			}
		}


		if (sc != 0)
			modelObj.SubsetArray[sc - 1].IndexNum = ic - modelObj.SubsetArray[sc - 1].StartIndex;


		fclose(file);


		delete[] positionArray;
		delete[] normalArray;
		delete[] texcoordArray;
		delete[] materialArray;
	}


	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * modelObj.VertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = modelObj.VertexArray;

		DirectX11SetUp::GetInstance().GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);
	}


	// インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * modelObj.IndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = modelObj.IndexArray;

		DirectX11SetUp::GetInstance().GetDevice()->CreateBuffer(&bd, &sd, &IndexBuffer);
	}

	// サブセット設定
	{
		SubsetArray = New(SUBSET)[modelObj.SubsetNum];
		SubsetNum = modelObj.SubsetNum;

		for (unsigned int i = 0; i < modelObj.SubsetNum; i++)
		{
			SubsetArray[i].StartIndex = modelObj.SubsetArray[i].StartIndex;
			SubsetArray[i].IndexNum = modelObj.SubsetArray[i].IndexNum;

			SubsetArray[i].Material.Material = modelObj.SubsetArray[i].Material.Material;

			SubsetArray[i].Material.Texture = nullptr;

			CreateTextureFromFile(DirectX11SetUp::GetInstance().GetDevice(),
				modelObj.SubsetArray[i].Material.TextureName,
				&SubsetArray[i].Material.Texture);

			if (SubsetArray[i].Material.Texture)
				SubsetArray[i].Material.Material.TextureEnable = true;
			else
				SubsetArray[i].Material.Material.TextureEnable = false;
		}
	}

	delete[] modelObj.VertexArray;
	delete[] modelObj.IndexArray;
	delete[] modelObj.SubsetArray;

	return true;
}


//void Draw()
//{

	//// 頂点バッファ設定
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Model->VertexBuffer, &stride, &offset);

	//// インデックスバッファ設定
	//Renderer::GetDeviceContext()->IASetIndexBuffer(m_Model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//// プリミティブトポロジ設定
	//Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//for( unsigned int i = 0; i < m_Model->SubsetNum; i++ )
	//{
	//	// マテリアル設定
	//	Renderer::SetMaterial(m_Model->SubsetArray[i].Material.Material );

	//	// テクスチャ設定
	//	if(m_Model->SubsetArray[i].Material.Texture)
	//		Renderer::GetDeviceContext()->PSSetShaderResources( 0, 1, &m_Model->SubsetArray[i].Material.Texture );

	//	// ポリゴン描画
	//	Renderer::GetDeviceContext()->DrawIndexed(m_Model->SubsetArray[i].IndexNum, m_Model->SubsetArray[i].StartIndex, 0 );
	//}

//}

//void ModelRenderer::Preload(const char *FileName)
//{
//	if (m_ModelPool.count(FileName) > 0)
//	{
//		return;
//	}
//
//	MODEL* model = NewMODEL;
//	LoadModel(FileName, model);
//
//	m_ModelPool[FileName] = model;
//
//}


//void ModelRenderer::UnloadAll()
//{
//	for (std::pair<const std::string, MODEL*> pair : m_ModelPool)
//	{
//		pair.second->VertexBuffer->Release();
//		pair.second->IndexBuffer->Release();
//
//		for (unsigned int i = 0; i < pair.second->SubsetNum; i++)
//		{
//			if (pair.second->SubsetArray[i].Material.Texture)
//				pair.second->SubsetArray[i].Material.Texture->Release();
//		}
//
//		delete[] pair.second->SubsetArray;
//
//		delete pair.second;
//	}
//
//	m_ModelPool.clear();
//}


//void ModelRenderer::Load(const char *FileName)
//{
//	if (m_ModelPool.count(FileName) > 0)
//	{
//		m_Model = m_ModelPool[FileName];
//		return;
//	}
//
//	m_Model = NewMODEL;
//	LoadModel(FileName, m_Model);
//
//	m_ModelPool[FileName] = m_Model;
//
//}

//void ModelRenderer::LoadModel( const char *FileName, MODEL *Model)
//{
//
//	MODEL_OBJ modelObj;
//	LoadObj( FileName, &modelObj );
//
//
//
//	// 頂点バッファ生成
//	{
//		D3D11_BUFFER_DESC bd;
//		ZeroMemory( &bd, sizeof(bd) );
//		bd.Usage = D3D11_USAGE_DEFAULT;
//		bd.ByteWidth = sizeof( VERTEX_3D ) * modelObj.VertexNum;
//		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//		bd.CPUAccessFlags = 0;
//
//		D3D11_SUBRESOURCE_DATA sd;
//		ZeroMemory( &sd, sizeof(sd) );
//		sd.pSysMem = modelObj.VertexArray;
//
//		Renderer::GetDevice()->CreateBuffer( &bd, &sd, &Model->VertexBuffer );
//	}
//
//
//	// インデックスバッファ生成
//	{
//		D3D11_BUFFER_DESC bd;
//		ZeroMemory( &bd, sizeof(bd) );
//		bd.Usage = D3D11_USAGE_DEFAULT;
//		bd.ByteWidth = sizeof( unsigned int ) * modelObj.IndexNum;
//		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//		bd.CPUAccessFlags = 0;
//
//		D3D11_SUBRESOURCE_DATA sd;
//		ZeroMemory( &sd, sizeof(sd) );
//		sd.pSysMem = modelObj.IndexArray;
//
//		Renderer::GetDevice()->CreateBuffer( &bd, &sd, &Model->IndexBuffer );
//	}
//
//	// サブセット設定
//	{
//		Model->SubsetArray = NewSUBSET[ modelObj.SubsetNum ];
//		Model->SubsetNum = modelObj.SubsetNum;
//
//		for( unsigned int i = 0; i < modelObj.SubsetNum; i++ )
//		{
//			Model->SubsetArray[i].StartIndex = modelObj.SubsetArray[i].StartIndex;
//			Model->SubsetArray[i].IndexNum = modelObj.SubsetArray[i].IndexNum;
//
//			Model->SubsetArray[i].Material.Material = modelObj.SubsetArray[i].Material.Material;
//
//			Model->SubsetArray[i].Material.Texture = nullptr;
//
//			CreateTextureFromFile(Renderer::GetDevice(),
//				modelObj.SubsetArray[i].Material.TextureName,
//				&Model->SubsetArray[i].Material.Texture);
//
//			if (Model->SubsetArray[i].Material.Texture)
//				Model->SubsetArray[i].Material.Material.TextureEnable = true;
//			else
//				Model->SubsetArray[i].Material.Material.TextureEnable = false;
//
//		}
//	}
//
//	delete[] modelObj.VertexArray;
//	delete[] modelObj.IndexArray;
//	delete[] modelObj.SubsetArray;
//
//}
//
//// 末尾のファイル名と円記号を削除
//bool _PathRemoveFileSpecExA(char *pszPath)
//{
//	unsigned char* pbs = _mbsrchr((unsigned char*)pszPath, '\\');
//	unsigned char* psl = _mbsrchr((unsigned char*)pszPath, '/');
//	if (pbs) {
//		if (psl) {
//			if (pbs > psl)
//				*pbs = '\0';
//			else
//				*psl = '\0';
//			return true;
//		} else {
//			*pbs = '\0';
//			return true;
//		}
//	} else {
//		if (psl) {
//			*psl = '\0';
//			return true;
//		}
//	}
//	return false;
//}
