

varying vec3 v_SurfacePos;

void main()
{
    vec3 materialColor = vec3(1,1,1);
    vec3 lightColor = vec3(0,1,1);
    vec3 lightPos = vec3(0,2,0);
    vec3 lightNormal = vec3(0,1,0);


    vec3 dirToLight = lightPos - v_SurfacePos;
    vec3 normDir = normalize(dirToLight);
    vec3 normNormal = normalize(lightNormal);

    float diffusePerc =  dot(  normNormal, normDir);
    vec3 finalColor = materialColor * lightColor * diffusePerc;
    
    gl_FragColor = vec4( finalColor,1);
    
    //Debugging
    //gl_FragColor = vec4( v_SurfacePos,1);
    //gl_FragColor = vec4( lightNormal,1);
}
