#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    vec4 box = texture(texture1, TexCoord);
    vec4 face = texture(texture2, vec2(TexCoord.x * 2, (1-TexCoord.y)*2));
    FragColor = box * (1-face.a) + face;
}