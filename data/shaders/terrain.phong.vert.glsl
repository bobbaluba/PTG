//terrain vertex shader
#version 130

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

in vec4 in_Position;
in vec4 in_Normal;

out vec3 ex_Normal;

void main(void){
	gl_Position = ProjectionMatrix * ModelViewMatrix * in_Position;
	ex_Normal = in_Normal.xyz;
}
