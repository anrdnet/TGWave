
uniform mat4 Transform;

attribute vec4 Vertex;
attribute vec2 TexCoord;
varying vec4 vTexCoord;

void main(void)
{
    vTexCoord = Vertex;
    gl_Position = Transform * Vertex;
}
