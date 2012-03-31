uniform mat4 Transform;
uniform float ZAdjustment;
uniform vec4 LightPosition;
attribute float Z;
attribute vec2 Grid;
attribute vec4 Norm;
varying float height;
varying float Diffuse;

void main(void)
{
    height = Z+ZAdjustment;
    vec4 pos = vec4(Grid.x, height, Grid.y,1);
    vec4 ligNorm = normalize(LightPosition - pos);
    vec4 norm = normalize(vec4(Norm.x, Norm.z, Norm.y,0));
    Diffuse = dot(ligNorm, norm);
    gl_Position =  Transform * pos;
}

