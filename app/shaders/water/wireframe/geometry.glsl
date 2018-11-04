#version 430

layout(triangles) in;
layout(line_strip, max_vertices = 4) out;

in vec2 texCoord_GS[];

uniform int largeDetailRange;
uniform mat4 viewProjectionMatrix;
uniform float displacementScale;
uniform sampler2D Dy;
uniform sampler2D Dx;
uniform sampler2D Dz;
uniform float choppiness;

void main()
{	
	float dx,dy,dz;

	dy = texture(Dy, texCoord_GS[0]).r * displacementScale;
	dx = texture(Dx, texCoord_GS[0]).r * choppiness;
	dz = texture(Dz, texCoord_GS[0]).r * choppiness;
	vec4 position0 = gl_in[0].gl_Position;
	position0.y += dy;
	position0.x -= dx;
	position0.z -= dz;
   gl_Position = viewProjectionMatrix * position0;
   EmitVertex();
	
	dy = texture(Dy, texCoord_GS[1]).r * displacementScale;
	dx = texture(Dx, texCoord_GS[1]).r * choppiness;
	dz = texture(Dz, texCoord_GS[1]).r * choppiness;
	vec4 position1 = gl_in[1].gl_Position;
	position1.y += dy;
	position1.x -= dx;
	position1.z -= dz;
	gl_Position = viewProjectionMatrix * position1;
   EmitVertex();

	dy = texture(Dy, texCoord_GS[2]).r * displacementScale;
	dx = texture(Dx, texCoord_GS[2]).r * choppiness;
	dz = texture(Dz, texCoord_GS[2]).r * choppiness;
	vec4 position2 = gl_in[2].gl_Position;
	position2.y += dy;
	position2.x -= dx;
	position2.z -= dz;
	gl_Position = viewProjectionMatrix * position2;
   EmitVertex();
	
   gl_Position = viewProjectionMatrix * position0;
   EmitVertex();
	
   EndPrimitive();
}