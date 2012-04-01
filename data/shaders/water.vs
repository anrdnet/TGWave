uniform mat4 Transform;
//uniform mat4 NormalTransform;
uniform float ZAdjustment;
uniform vec4 CameraPosition;
uniform float RefractionFactor;
uniform vec4 LightPosition;

attribute float Z;
attribute vec2 Grid;
attribute vec4 Norm;

varying float Diffuse;
varying float Specular;
varying float Transperancy;
varying vec3 TexCoordRefract;
varying vec3 TexCoordReflect;

void main(void)
{
    vec4 pos = vec4(Grid.x, Z+ZAdjustment, Grid.y,1);

    vec4 camNorm = normalize(CameraPosition - pos);
    vec4 lightNorm = normalize(LightPosition - pos);
    vec4 norm = normalize(vec4(Norm.x, Norm.z, Norm.y,0));

    vec4 specularNorm = reflect(lightNorm, norm);

    Diffuse = dot(lightNorm, norm);
    Specular = clamp(pow(max(0, dot(specularNorm, -camNorm)), 80),0.0,1.0);
    Transperancy = dot(camNorm, norm);

    vec4 tpos = Transform * pos;

    TexCoordRefract = refract(camNorm, norm, RefractionFactor).xyz;
    TexCoordReflect = reflect(camNorm, norm).xyz;

    gl_Position = tpos;
}

