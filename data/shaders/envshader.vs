
uniform mat4 Transform;

attribute vec4 Vertex;
attribute vec2 TexCoord;
varying vec2 vTexCoord;

void main(void)
{
    vTexCoord = TexCoord;
    gl_Position = Transform * Vertex;
}
