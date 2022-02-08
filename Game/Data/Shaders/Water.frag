
uniform sampler2D u_Texture; // = 0;
uniform float u_Time;

varying vec2 v_UVCoord;
varying vec4 v_Color;
varying float v_ObjectYPos;
varying vec4 v_TintColor;

void main()
{

    vec2 uv = v_UVCoord;
   //uv.x += sin(u_Time + v_UVCoord.y * 10.0) * 0.8;
   //uv.y -= sin(u_Time + v_UVCoord.x * 15.0) * 0.12;

    vec4 primaryWater = texture2D(u_Texture, uv) + v_TintColor;

    vec4 secondaryWater = texture2D(u_Texture, uv + vec2(0.5,u_Time/19.0)) * 0.1;

    gl_FragColor = primaryWater - secondaryWater;

}
