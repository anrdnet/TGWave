
uniform mat4 Transform;

attribute vec4 Vertex;

void main(void)
{
    gl_Position = Transform * Vertex;
}
