uniform sampler2D Tiles;

varying vec2 TexCoord;

void main(void)
{
    gl_FragColor = texture2D(Tiles, TexCoord);
}
