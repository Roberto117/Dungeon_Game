#version 330


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
