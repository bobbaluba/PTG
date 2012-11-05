//terrain fragment shader
#version 130

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

in vec4 in_Position;
in vec4 in_Normal;

out vec3 ex_Color;

void main(void){
	gl_Position = in_Position; //there should be a multiply with the modelview matrix here
}
