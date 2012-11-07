//fragment shader for ptg terrain
#version 130

in vec3 ex_Color;
out vec4 out_Color;

void main(void){
	out_Color = vec4(ex_Color,1);
	//while debugging
	//out_Color = vec4(1,1,1,1);
}
