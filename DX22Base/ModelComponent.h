
// =-=-= インクルードガード部 =-=-=
#ifndef _____MODEL_COMPONENT_H_____
#define _____MODEL_COMPONENT_H_____

// =-=-= インクルード部 =-=-=
#include "Component.h"
#include "Transform.h"
#include "Model.h"

/// @brief モデルのコンポーネント
/// @brief コンポーネントです
class ModelComponent :
    public Component
{
public:
    ModelComponent();
    ~ModelComponent();

    void Init()override;
    void Update()override;
    void UnInit()override;

    Transform* GetTransform();
    Model* GetModel();

    void RegisterModel(int, std::string, bool);
    void SelectModel(int);
    void SelectModelWithAnime(int, bool, float);

    void SetAlpha(float);
    float GetAlpha();
    void LoadPixelShader(std::string);
    void LoadVertexShader(std::string);
    PixelShader* GetPixelShader();
    VertexShader* GetVertexShader();

private:
    struct tModelData
    {
        int nModelNo;
        Model* pModel;
        Model::AnimeNo animeNo;
    };

    tModelData& SearchModelByNo(int);
    Transform* m_Transform;
    PixelShader* m_PS;
    VertexShader* m_VS;
    Model* m_pModel;
    std::vector<tModelData> m_Models;

    float m_fAlpha;
};

#endif // !_____MODEL_COMPONENT_H_____