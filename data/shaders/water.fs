
uniform samplerCube Background;
uniform samplerCube Sky;

varying float Diffuse;
varying float Specular;
varying float Transperancy;
varying vec3 TexCoordRefract;
varying vec3 TexCoordReflect;

void main(void)
{
    float skyDist;
    vec4 dark = vec4(0.27,0.73,1.0, 1.0);
    vec4 light = vec4(1.0,1.0,1.0,1.0);
    vec4 red = vec4(1.0,0.0,0.0, 1.0);
    vec4 refr =  textureCube(Background, vec3(TexCoordRefract.x, -TexCoordRefract.y, TexCoordRefract.z));
    if(refr.a == 0.0)
        refr = textureCube(Sky, TexCoordRefract);
    vec4 refl = textureCube(Background, vec3(TexCoordReflect.x, -TexCoordReflect.y, TexCoordReflect.z));
    if(refl.a == 0.0)
        refl = textureCube(Sky, TexCoordReflect);

    gl_FragColor = mix(mix(refl, refr ,Transperancy)
		*(Diffuse * 0.25 + 0.75)*vec4(0.8,0.8,1.0,1.0), light, Specular);
}
