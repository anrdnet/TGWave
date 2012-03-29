uniform mat4 Transform;
uniform mat4 NormalTransform;
uniform float ZAdjustment;
uniform vec4 CameraPosition;
attribute float Z;
attribute vec2 Grid;
attribute vec4 Norm;
varying float height;
varying float Diffuse;

void main(void)
{
    height = Z+ZAdjustment;
    vec4 pos = vec4(Grid.x, height, Grid.y,1);
    vec4 camNorm = normalize(CameraPosition - pos);
    vec4 norm = normalize(vec4(Norm.x, Norm.z, Norm.y,0));
    Diffuse = dot(camNorm, norm);
    gl_Position =  Transform * pos;
}

