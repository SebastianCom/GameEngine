

varying vec3 v_SurfacePos;
varying vec3 v_Normal;

uniform vec3 u_CamPosition;

//for multiple lights 
uniform vec3 u_LightPosition[4];
uniform vec3 u_LightColor[4];
uniform float u_LightRadii[4];



void main()
{
    vec3 finalColor[4];
    
    for(int i = 0; i < 4; i++)
    {
        vec3 materialColor = vec3(1,1,1);
        vec3 lightColor = u_LightColor[i];
        vec3 lightPos = u_LightPosition[i];
        float lightRadius = u_LightRadii[i];


        vec3 dirToLight = lightPos - v_SurfacePos;
        float distanceFromLight = length(dirToLight);
        vec3 normDir = normalize(dirToLight);
        vec3 normNormal = normalize(v_Normal);

        float attenuation = pow( max(0.0, 1.0 - distanceFromLight/lightRadius), 2.0);

        float diffusePerc = max(0.0, dot(  normNormal, normDir));

        vec3 camDir = u_CamPosition - v_SurfacePos;
        vec3 halfVec = normalize(camDir + dirToLight);
        float specPrec = pow( max( 0.0, dot(normNormal, halfVec)), 200);
        finalColor[i] = materialColor * lightColor  * diffusePerc * attenuation + (specPrec * lightColor);
    }
    
    vec3 lights = finalColor[0] += finalColor[1] += finalColor[2] += finalColor[3];

    gl_FragColor = vec4(lights ,1);
    
    //Debugging
    //gl_FragColor = vec4( v_SurfacePos,1);
    //gl_FragColor = vec4( lightNormal,1);
    //gl_FragColor = vec4 (v_Normal, 1);
}
