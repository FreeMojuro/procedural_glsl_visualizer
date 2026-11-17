#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec2 iRes;
uniform float dt;
uniform vec2 mousepos;
uniform float cnt;
uniform float neon;

uniform vec3 a;
uniform vec3 b;
uniform vec3 c;
uniform vec3 d;


out vec4 finalColor;



vec3 palette(float t){
    return a - b * cos(cnt * (c * t + d));

}



void main(){
    vec2 fragCoord = vec2(fragTexCoord.x, 1.0 - fragTexCoord.y) * iRes;
    vec2 uv = ( fragCoord* 2.0 - iRes.xy) / iRes.y;
    vec2 uv0 = uv;
    vec3 finalcol = vec3(0,0,0);
    vec3 colres;

    

    for(float i = 0; i < 4.0; ++i){
        uv+= mousepos;
        uv = fract(uv*1.5)-0.5;
        float d = length(uv) * exp(-length(uv0));
        colres = palette(length(uv0) + i*0.4 + dt*0.4);
        d = sin(d * 8.0 + dt*1.5)/8.0;
        d = abs(d);
        d = smoothstep(0.0, 0.1, d);
        d = pow(neon / d,0.8);
        
        finalcol += colres * d;
        
    }
    
    finalColor = vec4(finalcol,1);

}
