#version 330 core

out vec4 FragColor;

void main() {
    // fragcoord is screen coords
    vec2 res = vec2(1024, 768);
    vec2 uv = gl_FragCoord.xy/res; // normalized device coordinates

    uv -= 0.5;
    uv *= 2.0;

    float uvl = length(uv);

    FragColor = vec4(0.0, uvl, uvl, 1.0);
}
