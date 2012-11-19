//fragment shader for ptg terrain
#version 130

in vec3 ex_Normal;
out vec4 out_Color;

void main(void){
	vec3 n = normalize(ex_Normal);
	vec3 l = normalize(vec3(1,1,1)); //light shines diagonally on the terrain
	float k_a = 0.2;
	float k_d = 0.5;
	float i_a = k_a;
	float i_d = k_d * dot(l, n);
	out_Color = vec4((i_a + i_d) * vec3(1,1,1),1);
}
