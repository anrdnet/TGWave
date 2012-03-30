uniform sampler2D Tiles;

varying vec2 vTexCoord;

void main(void)
{
    gl_FragColor = texture2D(Tiles, vTexCoord);
}
