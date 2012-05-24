uniform mediump vec4 color;
varying highp vec4 v_AmbientAndDiffuseColor;
varying highp vec4 v_SpecularColor;
varying highp float v_AmbientLightBrightness;
varying highp float v_DiffuseBrightness;
varying highp float v_SpecularBrightness;
varying highp vec2 v_TexCoord;

uniform bool u_TextureEnabled;
uniform sampler2D s_Texture;

void main(void)
{
    if(u_TextureEnabled)
      gl_FragColor = texture2D(s_Texture, v_TexCoord) * (v_AmbientLightBrightness + v_DiffuseBrightness)
              + v_SpecularBrightness * v_SpecularColor;
    else
      gl_FragColor = v_AmbientAndDiffuseColor * (v_AmbientLightBrightness + v_DiffuseBrightness)
                   + v_SpecularBrightness * v_SpecularColor;
}
