
uniform mat4 Transform;
uniform vec4 Center;
uniform float Size;

attribute vec4 Vertex;
attribute vec2 TexCoord;
varying vec4 vTexCoord;

void main(void)
{
    vTexCoord = normalize(Vertex);
    gl_Position = Transform * (vec4(Vertex.xyz,0.0)*Size+Center);
}
