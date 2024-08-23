struct SPSIn
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
    float3 worldPos : POSITION0;
};

cbuffer DirectionLightCb : register(b0)
{
    float3 lightDirection;
    float pad1;
    float3 lightColor;
    float pad2;
    float3 eyePos;
    float pad3;
    float alpha;
    float3 pad4;
}

///////////////////////////////////////////
// シェーダーリソース
///////////////////////////////////////////
// モデルテクスチャ
Texture2D<float4> g_texture : register(t0);

///////////////////////////////////////////
// サンプラーステート
///////////////////////////////////////////
sampler g_sampler : register(s0);


float4 main(SPSIn psIn) : SV_Target0
{
    // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(psIn.normal, lightDirection);
    t *= -1.0f;

    // 内積の結果が0以下なら0にする
    if (t < 0.0f)
    {
        t = 0.0f;
    }
    
    float3 LightColor = lightColor; //float3(1.0f,1.0f,1.0f);

    // 拡散反射光を求める
    float3 lig = LightColor * t;

    //lig *= 0.2f;
    // step-1 ライトの効果を一律で底上げする
    float ambient_light = 0.6f;
    float ligMax = 1.3f;
    lig.x += ambient_light;
    if (lig.x > ligMax)
        lig.x = ligMax;
    lig.y += ambient_light;
    if (lig.y > ligMax)
        lig.y = ligMax;
    lig.z += ambient_light;
    if (lig.z > ligMax)
        lig.z = ligMax;
    
    float4 finalColor = g_texture.Sample(g_sampler, psIn.uv);
    finalColor *= psIn.color;
    // テクスチャカラーに求めた光を乗算して最終出力カラーを求める
    finalColor.xyz *= lig;
	
    finalColor.w = 1.0f;
    
    finalColor.w *= alpha;
        
    return finalColor;
    //return float4(1.0f,1.0f,1.0f,1.0f);
}