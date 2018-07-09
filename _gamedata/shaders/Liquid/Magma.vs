#version 330

// Vertex attrib
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 TexCoord;
layout(location = 2) in vec3 Normal;

// Input

// Uniforms
uniform mat4 gProjView;
uniform mat4 gWorld;

// Out
out struct VSOutput
{
	vec3 WorldSpacePos;
	vec3 TexCoord;
	vec3 Normal;
} VSout;

void main(void)
{
	mat4 PVW = gProjView * gWorld;
	gl_Position = PVW * vec4(VertexPosition, 1.0);

	VSout.WorldSpacePos = (gWorld * vec4(VertexPosition, 1.0)).xyz;
	VSout.TexCoord = TexCoord;
	VSout.Normal = (gWorld * vec4(Normal, 0.0)).xyz;
};

