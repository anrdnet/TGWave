
uniform float ColorScale;
uniform sampler2D Background;

varying float height;
varying float Diffuse;
varying vec2 TexCoord;

void main(void)
{
    vec4 light = vec4(1.0,1.0,1.0,1.0);
    vec4 dark = vec4(0.2,0.16,0.64, 1.0);
    //gl_FragColor = mix(dark, light, clamp(height*ColorScale+0.5,0.0,1.0)) * Diffuse;
    if(TexCoord.x > 1.0)
    {
        gl_FragColor = vec4(0.0,0.0,1.0,1.0);
    }
    else
    {
        gl_FragColor = mix(dark, texture2D(Background, TexCoord),Diffuse);
        //gl_FragColor = gl_FragColor*0.000001 + vec4(TexCoord.x, TexCoord.y, 0.0, 1.0);
    }
}
