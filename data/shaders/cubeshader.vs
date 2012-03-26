uniform mat4 Transform;
uniform float ZAdjustment;
attribute float Z;
attribute vec2 Grid;
varying float height;

void main(void)
{
    height = Z+ZAdjustment;
    gl_Position =  Transform * vec4(Grid.x, Grid.y, height,1);
}

