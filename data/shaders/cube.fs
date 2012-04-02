uniform samplerCube Tiles;

varying vec4 vTexCoord;

void main(void)
{
    gl_FragColor = textureCube(Tiles, vTexCoord.xyz);
}
