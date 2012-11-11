//fragment shader for water
#version 130

uniform float Alpha;

out vec4 out_Color;

void main(void){
	out_Color = vec4(0.1,0.2,0.8,Alpha);
}
