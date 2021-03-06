
#version 330

//Transformation Matrices
uniform mat4 LProjectionMatrix;
uniform mat4 LModelViewMatrix;

//Vertex position attribute
in vec2 LVertexPos;

//Multicolor attribute
in vec4 LColor;
out vec4 Color;

void main()
{
//Process color
Color = LColor;

//Process vertex
gl_Position = LProjectionMatrix * LModelViewMatrix * vec4( LVertexPos.x, LVertexPos.y, 0.0f, 1.0f );
}
