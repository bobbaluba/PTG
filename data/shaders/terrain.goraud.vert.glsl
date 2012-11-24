//terrain vertex shader
#version 130

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

in vec4 in_Position;
in vec4 in_Normal;

out vec3 ex_Color;

void main(void){
	mat4 MVP  = ProjectionMatrix * ModelViewMatrix;

	vec3 n = normalize(ModelViewMatrix * in_Normal).xyz; //switch to normal matrix?
	vec3 s = normalize(ModelViewMatrix * vec4(1,1,1,0)).xyz; //direction towards light source
	vec3 v = vec3(0,0,1); //direction towards viewer
	vec3 r = reflect(s, n); //reflection
	
	gl_Position = ProjectionMatrix * ModelViewMatrix * in_Position;
	float k_a = 0.2;
	float k_d = 0.5;
	float k_s = 0.2;
	float i_a = k_a;
	float i_d = k_d * max(0, dot(n, s));
	float i_s = k_s * max(0, pow(dot(r, v), 50) );
	ex_Color = (i_a + i_d + i_s) * vec3(1,1,1);
}
