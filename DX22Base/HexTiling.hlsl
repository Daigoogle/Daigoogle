/// ヘックスタイリングを実装するよ！！
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
    float4 wPos : POSITION;
};
cbuffer Param : register(b0)
{
    float kuru;
};
Texture2D tex : register(t0);
Texture2D Hex : register(t1);
SamplerState samp : register(s0);
float rand1(float n){ return frac(sin(n) * 43758.5453123); }
static const float uvCat = 9.0f;
float4 main(PS_IN pin) : SV_TARGET
{
    float4 hex = Hex.Sample(samp, pin.uv * uvCat);
    float2 vert;
    vert.x = pin.uv.x * uvCat + 0.5f - hex.r;
    vert.y = pin.uv.y * uvCat + hex.g - 0.5f;
    vert = trunc(vert * 4) * 0.2f;
    float rot = (vert.x + vert.y) * 0.98f + 0.02f;
    rot *= rand1(trunc((pin.uv.y * uvCat + hex.g - 0.5f) * 4) * 0.2f * 1.7320508f + 0.5f) * (kuru + 1.0f);
    return float4(tex.Sample(samp, float2(hex.x * cos(rot) - hex.y * sin(rot), hex.x * sin(rot) + hex.y * cos(rot))).rgb,1.0f) * pin.color;
}