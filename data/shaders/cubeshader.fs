
uniform float ColorScale;

varying float height;

void main(void)
{
    vec4 light = vec4(1.0,1.0,1.0,1.0);
    vec4 dark = vec4(0.2,0.16,0.64, 1.0);
    gl_FragColor = mix(dark, light, height*ColorScale+0.5);
}
