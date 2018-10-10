#version 430

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;//TODO
layout(location = 2) in vec2 texcoord;//TODO

out vec3 vertex_posistion;

void main() 
{
   gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
   vertex_posistion = (model_matrix * vec4(position, 1.0)).xyz;
}
