#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;
uniform int isGrass;
// Output
out vec2 texcoord;


void main()
{
    // Pass v_texture_coord as output to fragment shader
    texcoord = v_texture_coord;

    // Sa se roteasca spre directia camerei (doar pe OY) quadul cu textura de iarba astfel incat sa fie orientat tot timpul catre camera.
//    if (isGrass == 1) {
//        vec3 cameraPosition = vec3(View[3]);
//        vec3 cameraDirection = normalize(cameraPosition - v_position);
//        float angle = atan(cameraDirection.x, cameraDirection.z);
//        mat4 rotationMatrix = mat4(cos(angle), 0, sin(angle), 0,
//                                    0, 1, 0, 0,
//                                    -sin(angle), 0, cos(angle), 0,
//                                    0, 0, 0, 1);
//        Model = Model * rotationMatrix;
//    }

    if(time >= 0)
        texcoord = vec2(texcoord.x + time, texcoord.y);

    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
