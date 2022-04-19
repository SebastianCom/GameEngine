uniform samplerCube u_TextureCubemap; // = 0;

varying vec3 v_SurfacePos;
varying vec3 v_Normal;

uniform vec3 u_CamPosition;




void main()
{
    vec3 dirToSurface = v_SurfacePos - u_CamPosition;

    vec3 reflectedDir = reflect(dirToSurface, normalize(v_Normal));

    gl_FragColor = textureCube( u_TextureCubemap, reflectedDir );
    
    //gl_FragColor = vec4(v_Normal ,1);
    

}
