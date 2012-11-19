//terrain vertex shader
#version 130

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

in vec4 in_Position;
in vec4 in_Normal;

out vec3 ex_Color;

void main(void){
	vec3 n = in_Normal.xyz;
	vec3 s = normalize(vec3(1,1,1)); //direction towards light source
	gl_Position = ProjectionMatrix * ModelViewMatrix * in_Position;
	float k_a = 0.2;
	float k_d = 0.5;
	float i_a = k_a;
	float i_d = k_d * max(0, dot(n, s));
	ex_Color = (i_a + i_d) * vec3(1,1,1);
}
