uniform mat4 Transform;
uniform mat4 NormalTransform;
uniform float ZAdjustment;
uniform vec4 CameraPosition;
uniform float RefractionFactor;
attribute float Z;
attribute vec2 Grid;
attribute vec4 Norm;
varying float height;
varying float Diffuse;
varying vec2 TexCoord;

void main(void)
{
    height = Z+ZAdjustment;
    vec4 pos = vec4(Grid.x, height, Grid.y,1);
    vec4 camNorm = normalize(CameraPosition - pos);
    vec4 norm = normalize(vec4(Norm.x, Norm.z, Norm.y,0));
    Diffuse = dot(camNorm, norm);
    vec4 tpos = Transform * pos;
    //vec4 refract = (RefractionFactor - 1.0)*(camNorm*norm)*norm - camNorm;
    vec4 refract = refract(camNorm, norm, RefractionFactor);
    vec4 transformedRefract = NormalTransform * refract;
    TexCoord = (tpos.xy + transformedRefract.xy) / (2.0*tpos.w)+vec2(0.5,0.5);
    gl_Position = tpos;
}

