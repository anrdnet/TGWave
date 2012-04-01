
uniform float ColorScale;
uniform samplerCube Background;

varying float Diffuse;
varying float Specular;
varying float Transperancy;
varying vec3 TexCoordRefract;
varying vec3 TexCoordReflect;

void main(void)
{
    vec4 dark = vec4(0.27,0.73,1.0, 1.0);
    vec4 light = vec4(1.0,1.0,1.0,1.0);
    vec4 red = vec4(1.0,0.0,0.0, 1.0);
    gl_FragColor = mix(mix(textureCube(Background, TexCoordReflect), textureCube(Background, TexCoordRefract),Transperancy)
		*(Diffuse * 0.25 + 0.75), light, Specular);
    gl_FragColor = textureCube(Background, TexCoordRefract) + 0.0*gl_FragColor;
}
