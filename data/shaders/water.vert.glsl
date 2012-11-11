//water vertex shader
#version 130

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

in vec3 in_Position;

void main(void){
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(in_Position,1);
}
