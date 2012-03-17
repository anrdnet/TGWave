
attribute float Z;
attribute vec2 Grid;

void main(void)
{
    gl_FrontColor = gl_Color;
    gl_Position =  gl_ModelViewProjectionMatrix * vec4(Grid.x, Grid.y, Z,1);
}
