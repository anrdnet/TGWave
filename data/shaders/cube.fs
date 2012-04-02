uniform samplerCube Tex;

varying vec4 vTexCoord;

void main(void)
{
    gl_FragColor = textureCube(Tex, vTexCoord.xyz);
}
