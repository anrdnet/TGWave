uniform mat4 Transform;
//uniform mat4 NormalTransform;
uniform float ZAdjustment;
uniform vec4 CameraPosition;
uniform float RefractionFactor;
uniform vec4 LightPosition;
uniform float ScaleX;
uniform float ScaleY;

attribute float Z;
attribute vec2 Grid;
attribute vec4 Norm;

varying float Diffuse;
varying float Specular;
varying float Transperancy;
varying vec3 TexCoordRefract;
varying vec3 TexCoordReflect;

vec3 Coord(vec3 p, vec3 dir, vec3 max)
{
    float tx;
    if(dir.x > 0.0)
        tx = (max.x-p.x)/dir.x;
    else
        tx = (-max.x-p.x)/dir.x;
    float ty;
    if(dir.y > 0.0)
        ty = (max.y-p.y)/dir.y;
    else
        ty = (-max.y-p.y)/dir.y;
    float tz;
    if(dir.z > 0.0)
        tz = (max.z-p.z)/dir.z;
    else
        tz = (-max.z-p.z)/dir.z;

    float et = min(min(tx,ty),tz);
    return p + et*dir;
}

void main(void)
{
    vec4 pos = vec4(Grid.x, Z+ZAdjustment, Grid.y,1);
    vec3 Offset = pos.xyz/vec3(ScaleX/2.0, 1.0, ScaleY/2.0) - vec3(1.0, 0.0, 1.0);

    vec4 camNorm = normalize(pos - CameraPosition);
    vec4 lightNorm = normalize(LightPosition - pos);
    vec4 norm = normalize(vec4(Norm.x, Norm.z, Norm.y,0));

    vec4 specularNorm = reflect(lightNorm, norm);

    Diffuse = dot(lightNorm, norm);
    Specular = clamp(pow(max(0, dot(specularNorm, camNorm)), 80),0.0,1.0);
    Transperancy = dot(-camNorm, norm);

    vec4 tpos = Transform * pos;

    camNorm /= vec4(ScaleX, 1.0, ScaleY,1.0);
    TexCoordRefract = Coord(Offset, refract(camNorm, norm, RefractionFactor).xyz*vec3(1.0,0.5,1.0), vec3(1.0,1.0,1.0));
    TexCoordReflect = Coord(Offset, reflect(camNorm, norm).xyz, vec3(1.0,1.0,1.0));

    gl_Position = tpos;
} 

