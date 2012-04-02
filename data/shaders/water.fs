
uniform samplerCube Background;
uniform samplerCube Sky;
uniform float ScaleX;
uniform float ScaleY;

varying float Diffuse;
varying float Specular;
varying float Transperancy;
varying vec3 Offset;
varying vec3 TexCoordRefract;
varying vec3 TexCoordReflect;

vec3 Coord(vec3 pos, vec3 dir, float dist)
{
    //BPCEM
    vec3 nrdir = normalize(dir);
    vec3 rbmax = (vec3(ScaleX, 1, ScaleY) - pos)/nrdir;
    vec3 rbmin = (vec3(-ScaleX, -1, -ScaleY) - pos)/nrdir;
    
    float rbminmaxx = (nrdir.x > 0.0f) ? rbmax.x : rbmin.x;
    float rbminmaxy = (nrdir.y > 0.0f) ? rbmax.y : rbmin.y;
    float rbminmaxz = (nrdir.z > 0.0f) ? rbmax.z : rbmin.z;
    float fa = min(min(rbminmaxx, rbminmaxy), rbminmaxz);
    
    return pos + nrdir*fa - vec3(ScaleX/2.0, 0, ScaleY/2.0);
    //float t = min(min(max(0,(dist*ScaleX)/dir.x - pos.x), max(0, dist/dir.y - pos.y)), max(0, dist*ScaleY/dir.z - pos.z));
    //return normalize(vec3((pos + t*dir).x/ScaleX, (pos + t*dir).y, (pos + t*dir).z/ScaleY));
}

void main(void)
{
    float skyDist;
    vec4 dark = vec4(0.27,0.73,1.0, 1.0);
    vec4 light = vec4(1.0,1.0,1.0,1.0);
    vec4 red = vec4(1.0,0.0,0.0, 1.0);
    vec4 refr = textureCube(Background, Coord(Offset, vec3(TexCoordRefract.x, -TexCoordRefract.y, TexCoordRefract.z), 1));
    if(refr.a == 0.0)
        refr = vec4(1.0, 1.0, 0.0, 1.0) + 0.000000000000000001 * textureCube(Sky, Coord(Offset, TexCoordRefract, 4));
    vec4 refl = textureCube(Background, Coord(Offset, vec3(TexCoordReflect.x, -TexCoordReflect.y, TexCoordReflect.z), 4));
    if(refl.a == 0.0)
        refl = vec4(1.0,0.0,0.0,1.0); //textureCube(Sky, Coord(Offset, TexCoordRefract, 4));

    gl_FragColor = mix(mix(refl, refr ,Transperancy)
		*(Diffuse * 0.25 + 0.75), light, Specular);
    gl_FragColor = refr + 0.000000000000000000001 * gl_FragColor;
}
