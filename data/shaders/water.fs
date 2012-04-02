
uniform samplerCube Background;
uniform samplerCube Sky;
uniform float Ratio;

varying float Diffuse;
varying float Specular;
varying float Transperancy;
varying vec3 Offset;
varying vec3 TexCoordRefract;
varying vec3 TexCoordReflect;

vec3 Coord(vec3 pos, vec3 dir, float ratio, float dist)
{
    float t = min(min((dist*ratio)/dir.x - pos.x, dist/dir.y - pos.y), dist/dir.z - pos.z);
    return vec3((pos + t*dir).x/ratio, (pos + t*dir).y, (pos + t*dir));
}

void main(void)
{
    float skyDist;
    vec4 dark = vec4(0.27,0.73,1.0, 1.0);
    vec4 light = vec4(1.0,1.0,1.0,1.0);
    vec4 red = vec4(1.0,0.0,0.0, 1.0);
    vec4 refr = textureCube(Background, Coord(Offset, vec3(TexCoordRefract.x, -TexCoordRefract.y, TexCoordRefract.z), Ratio, 1));
    if(refr.a == 0.0)
        refr = textureCube(Sky, Coord(Offset, TexCoordRefract, 1, 4));
    vec4 refl = textureCube(Background, Coord(Offset, vec3(TexCoordReflect.x, -TexCoordReflect.y, TexCoordReflect.z), 1, 4));
    if(refl.a == 0.0)
        refl = textureCube(Sky, Coord(Offset, TexCoordRefract, 1, 4));

    gl_FragColor = mix(mix(refl, refr ,Transperancy)
		*(Diffuse * 0.25 + 0.75), light, Specular);
    
}
