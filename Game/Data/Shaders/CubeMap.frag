
uniform samplerCube u_TextureCubemap; // = 0;

varying vec2 v_UVCoord;
varying vec4 v_Color;

varying vec3 v_ObjectSpaceSurfacePosition;

void main()
{
    gl_FragColor = textureCube( u_TextureCubemap, v_ObjectSpaceSurfacePosition );
}
