
uniform mat4 Transform;

attribute vec4 Vertex;
varying vec2 TexCoord;

void main(void)
{
    TexCoord = vec2(Vertex.x, Vertex.z);
    gl_Position = Transform * Vertex;
}
