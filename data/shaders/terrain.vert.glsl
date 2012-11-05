//terrain vertex shader
#version 130

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

in vec4 in_Position;
in vec4 in_Normal;

out vec3 ex_Color;

void main(void){
	vec3 n = in_Normal.xyz;
	vec3 v = vec3(0,0,1); //direction towards viewer
	gl_Position = ProjectionMatrix * ModelViewMatrix * in_Position;
	float k_d = 1;
	float i_d = k_d * dot(n, v);
	ex_Color = i_d * vec3(1,1,1);
}
