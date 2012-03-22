uniform mat4 Transform;
attribute float Z;
attribute vec2 Grid;
varying float height;

void main(void)
{
    height = Z;
    gl_Position =  Transform * vec4(Grid.x, Grid.y, Z,1);
}

