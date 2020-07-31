#pragma once
#include "VisualComponent.h"
#include <string>


// マテリアル構造体
struct ModelMaterial {
	char						Name[256];
	Material					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


// 描画サブセット構造体
struct Subset
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	ModelMaterial	Material;
};


// モデル構造体
struct MODEL
{
	Vertex		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	Subset			*SubsetArray;
	unsigned int	SubsetNum;
};

class Model : public VisualComponent {
private:
	ID3D11Buffer*	m_VertexBuffer;
	ID3D11Buffer*	m_IndexBuffer;

	Subset*	m_SubsetArray;
	unsigned int	m_SubsetNum;

	void LoadObj(const char *FileName, MODEL *Model);
	void LoadMaterial(const char *FileName, ModelMaterial **MaterialArray, unsigned int *MaterialNum);

	void UnLoad();

	Model();
	~Model();
public:

	Model(const char fileName);

	void Draw();

	void ChangeModel(const char *FileName);
};
