//fragment shader for ptg terrain
#version 130

uniform mat4 ModelViewMatrix;

in vec3 ex_Normal;
out vec4 out_Color;

void main(void){
	vec3 n = normalize(ModelViewMatrix * vec4(ex_Normal,0)).xyz;
	vec3 s = normalize(ModelViewMatrix * vec4(1,1,1,0)).xyz; //direction towards light source
	vec3 v = vec3(0,0,1); //direction towards viewer
	vec3 r = reflect(s, n); //reflection
	
	float k_a = 0.2;
	float k_d = 0.5;
	float k_s = 0.15;
	float i_a = k_a;
	float i_d = k_d * max(0, dot(s, n));
	float i_s = k_s * max(0, pow(dot(r, v), 50) );
	out_Color = vec4((i_a + i_d + i_s) * vec3(1,1,1),1);
}
