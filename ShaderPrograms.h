struct ShaderPrograms
{
	const char* vs_BasicPoylgonProgram = R"(
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
)";
	const char* fs_BasicPoylgonProgram = R"(#version 330

//Multicolor attribute
in vec4 Color;

//Final color
out vec4 LFragment;

void main()
{

//Set fragment
    LFragment = Color;
}


)";
	const char* vs_CircleProgram = R"(
#version 330
// unifor variables for the program a projection matrix a modelView matrix and a center point for the circle
uniform mat4 LProjectionMatrix;
uniform mat4 LModelViewMatrix;
uniform vec2 LCenter;

//vertex position attributes

in vec2  LVertexPos;


//Multicolor attributes
in vec4 LColor;
//variables that will be send to the fragment shader
out vec4 Color;
out vec2 Center;


void main()
{
    
    //set the variables that will be send to the fragement shader.
    Color = LColor;
    Center = LCenter;
    //Procces vertex
    gl_Position = LProjectionMatrix * LModelViewMatrix * vec4( LVertexPos.x, LVertexPos.y, 0.0, 1.0 );

    
    
}
)";
	const char* fs_CircleProgram= R"(#version 330


uniform vec2 LResolution;
//uniform vec2 LSize;

in vec4 Color;
in vec2 Center;

//Final color
out vec4 outColor;




void main()
{

    
    //make teh radius of th circle
    float circleRadius = 15/ LResolution.y;
    //set the mid point for the circle
    vec2 midpoint = Center;
    //figure out the min raidus of x and y in order to normalize the shape
    float radius = min(LResolution.x, LResolution.y) * circleRadius;
    //calculate the lengh betwen the current cordinates and the radius of the circle
    float dist = length(vec2(gl_FragCoord.x, abs(gl_FragCoord.y - LResolution.y)) - midpoint);
    //check if the pixel is within the circle radius.
    float circle = smoothstep(radius, radius - 0.1, dist);


    //if the pixel is within the radius color the pixel if not make the pixel transparent.
    vec4 color = vec4(circle) * vec4(Color.rgb, 1.0);
    
    //output the color
    outColor = color;
    

}
)";
};