
attribute vec3 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec2 u_ObjectTranslation;
uniform vec2 u_ObjectScale;
uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;
uniform float u_Time;
uniform float u_Color;
uniform vec4 u_Tint;

varying vec2 v_UVCoord;
varying vec4 v_Color;
varying vec4 v_TintColor;
varying float v_ObjectYPos;

#define PI 3.1415926538

void main()
{


    vec4 objectSpacePosition = vec4( a_Position, 1 );

    //objectSpacePosition.y += sin(a_Position.x + u_Time);
    //objectSpacePosition.y += sin(a_Position.z + u_Time);
    objectSpacePosition.y += sin(a_Position.x + (u_Time/2)) * 0.15;
    objectSpacePosition.y += sin(a_Position.z - (u_Time)) * 0.95;


    vec4 worldSpacePosition = u_WorldMatrix * objectSpacePosition;
    vec4 viewSpacePosition = u_ViewMatrix * worldSpacePosition;
    vec4 clipSpacePostion = u_ProjMatrix * viewSpacePosition;

    gl_Position = clipSpacePostion;
    
    v_UVCoord = a_UVCoord * u_UVScale + u_UVOffset;
    v_Color = a_Color;
    v_ObjectYPos = objectSpacePosition.y;
    v_TintColor = u_Tint;
}
