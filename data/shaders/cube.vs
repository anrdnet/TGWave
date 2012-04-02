
uniform mat4 Transform;
uniform vec4 Center;
uniform float Size;

attribute vec4 Vertex;
attribute vec2 TexCoord;
varying vec4 vTexCoord;

void main(void)
{
    vTexCoord = normalize(Vertex);
    vTexCoord.y *= -1.0;
    gl_Position = Transform * (Vertex*Size+Center);
}
