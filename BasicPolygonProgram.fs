#version 330

//Multicolor attribute
in vec4 Color;

//Final color
out vec4 LFragment;

void main()
{

//Set fragment
    LFragment = Color;
}


