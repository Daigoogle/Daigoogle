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
// �V�F�[�_�[���\�[�X
///////////////////////////////////////////
// ���f���e�N�X�`��
Texture2D<float4> g_texture : register(t0);

///////////////////////////////////////////
// �T���v���[�X�e�[�g
///////////////////////////////////////////
sampler g_sampler : register(s0);


float4 main(SPSIn psIn) : SV_Target0
{
    // �s�N�Z���̖@���ƃ��C�g�̕����̓��ς��v�Z����
    float t = dot(psIn.normal, lightDirection);
    t *= -1.0f;

    // ���ς̌��ʂ�0�ȉ��Ȃ�0�ɂ���
    if (t < 0.0f)
    {
        t = 0.0f;
    }
    
    float3 LightColor = lightColor; //float3(1.0f,1.0f,1.0f);

    // �g�U���ˌ������߂�
    float3 lig = LightColor * t;

    //lig *= 0.2f;
    // step-1 ���C�g�̌��ʂ��ꗥ�Œ�グ����
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
    // �e�N�X�`���J���[�ɋ��߂�������Z���čŏI�o�̓J���[�����߂�
    finalColor.xyz *= lig;
	
    finalColor.w = 1.0f;
    
    finalColor.w *= alpha;
        
    return finalColor;
    //return float4(1.0f,1.0f,1.0f,1.0f);
}