#version 330

// Input
// Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// Output
// Output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec3 frag_color;


void main()
{
    // Send output to fragment shader
    frag_position = v_position;
    frag_normal = v_normal;
    frag_color = v_color;

    // Compute gl_Position
    gl_Position = Projection * View * Model * vec4(frag_position, 1.0);

}
