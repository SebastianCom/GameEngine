

varying vec3 v_SurfacePos;
varying vec3 v_Normal;

void main()
{
    vec3 materialColor = vec3(1,1,1);
    vec3 lightColor = vec3(0,1,1);
    vec3 lightPos = vec3(0,2,0);
    float lightRadius = 5.0;


    vec3 dirToLight = lightPos - v_SurfacePos;
    float distanceFromLight = length(dirToLight);
    vec3 normDir = normalize(dirToLight);
    vec3 normNormal = normalize(v_Normal);

    float attenuation = pow( max(0, 1 - distanceFromLight/lightRadius), 2);

    float diffusePerc = max(0, dot(  normNormal, normDir));
    vec3 finalColor = materialColor * lightColor * diffusePerc * attenuation;
    
    gl_FragColor = vec4( finalColor,1);
    
    //Debugging
    //gl_FragColor = vec4( v_SurfacePos,1);
    //gl_FragColor = vec4( lightNormal,1);
}
