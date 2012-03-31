
uniform float ColorScale;
uniform sampler2D Background;

varying float Diffuse;
varying float Specular;
varying float Transperancy;
varying vec2 TexCoord;

void main(void)
{
    vec4 dark = vec4(0.27,0.73,1.0, 1.0);
    vec4 light = vec4(1.0,1.0,1.0,1.0);
    vec4 red = vec4(1.0,0.0,0.0, 1.0);
    gl_FragColor = mix(mix(dark, texture2D(Background, TexCoord),Transperancy)*(Diffuse * 0.25 + 0.75), light, Specular);
}
