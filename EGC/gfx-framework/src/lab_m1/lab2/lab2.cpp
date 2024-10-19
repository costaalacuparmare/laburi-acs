#include "lab_m1/lab2/lab2.h"

#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab2::Lab2()
{
}


Lab2::~Lab2()
{
}


void Lab2::Init()
{
    cullFace = GL_BACK;
    polygonMode = GL_FILL;

    // Load a mesh from file into GPU memory
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a mesh box using custom data
    {
        vector<VertexFormat> vertices
                {
                // Complete the vertices data for the cube mesh

                // vertexes in order 0 - 8
                VertexFormat(glm::vec3(-1, -1, 1), glm::vec3(0, 0, 1),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(1, -1, 1), glm::vec3(1, 0, 1),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(-1, 1, 1), glm::vec3(0, 1, 1),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 0),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 0, 0),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(-1, 1, -1), glm::vec3(0, 1, 0),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(1, 1, -1), glm::vec3(1, 1, 0),
                             glm::vec3(0.2, 0.8, 0.6)),
                };

        vector<unsigned int> indices =
                {
                        // Complete indices data for the cube mesh
                        0, 1, 2,    // indices for first triangle
                        1, 3, 2,    // indices for second triangle
                        2, 3, 7,
                        2, 7, 6,
                        1, 7, 3,
                        1, 5, 7,
                        6, 7, 4,
                        7, 5, 4,
                        0, 4, 1,
                        1, 4, 5,
                        2, 6, 4,
                        0, 2, 4,
                };

        meshes["cube_A"] = new Mesh("generated cube 1");
        meshes["cube_A"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
        CreateMesh("cube_B", vertices, indices);

    }

        // Create a tetrahedron mesh. You can create it with
        // only 4 vertices, or you can choose the harder route and create it
        // with 12 vertices. Think about it, why would you want that, and how
        // would you do it? After all, a tetrahedron has only 4 vertices
        // by definition!

    {
        vector<VertexFormat> vertices2
                {
                        // Complete the vertices data for the cube mesh

                        // vertexes in order 0 - 4
                        VertexFormat(glm::vec3(-1.5, -1, 1), glm::vec3(0, 0, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(1, -2, 1), glm::vec3(0, 1, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(-1, 1, 1), glm::vec3(1, 0, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(0, 1, -1), glm::vec3(0, 1, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                };

        vector<unsigned int> indices2 =
                {
                        // Complete indices data for the cube mesh
                        0, 1, 2,    // indices for first triangle
                        1, 3, 2,    // indices for second triangle
                        2, 3, 0,
                        0, 3, 1,
                };

        // Actually create the mesh from the data
        CreateMesh("tetraedu_attempt", vertices2, indices2);
    }


    // Create a square using two triangles with
    // opposing vertex orientations.
    {
        vector<VertexFormat> vertices3
                {
                        // Complete the vertices data for the cube mesh

                        // vertexes in order 0 - 4
                VertexFormat(glm::vec3(-1, -1, 1), glm::vec3(0, 0, 1),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(1, -1, 1), glm::vec3(1, 0, 1),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(-1, 1, 1), glm::vec3(0, 1, 1),
                             glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1),
                             glm::vec3(0.2, 0.8, 0.6)),
                };

        vector<unsigned int> indices3 =
                {
                        // Complete indices data for the cube mesh
                        0, 1, 2,    // indices for first triangle
                        2, 3, 1,    // indices for second triangle
                };

        // Actually create the mesh from the data
        CreateMesh("patrat", vertices3, indices3);
    }

    // bonus

    // Create a mesh box using custom data
    {
        vector<VertexFormat> vertices4
                {
                        // Complete the vertices data for the cube mesh

                        // vertexes in order 0 - 8
                        VertexFormat(glm::vec3(-1, -1, 1), glm::vec3(0, 0, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(1, -1, 1), glm::vec3(0, 0, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(-1, 1, 1), glm::vec3(0, 0, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 0, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0, 1, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 1, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(-1, 1, -1), glm::vec3(0, 1, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(1, 1, -1), glm::vec3(1, 1, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),

                        // 8 = copie 2
                        VertexFormat(glm::vec3(-1, 1, 1), glm::vec3(1, 0, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 9 = copie 3
                        VertexFormat(glm::vec3(1, 1, 1), glm::vec3(1, 0, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 10 = copie 7
                        VertexFormat(glm::vec3(1, 1, -1), glm::vec3(1, 0, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 11 = copie 6
                        VertexFormat(glm::vec3(-1, 1, -1), glm::vec3(1, 0, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),

                        // 12 = copie 2 alba
                        VertexFormat(glm::vec3(-1, 1, 1), glm::vec3(1, 1, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 13 = copie 1 galbena
                        VertexFormat(glm::vec3(1, -1, 1), glm::vec3(1, 1, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 14 = copie 3 galbena
                        VertexFormat(glm::vec3(1, 1, 1), glm::vec3(1, 1, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),

                        // 15 copie 7 verde
                        VertexFormat(glm::vec3(1, 1, -1), glm::vec3(0, 1, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 16 copie 5 verde
                        VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),

                        // 17 copie 0 porto
                        VertexFormat(glm::vec3(-1, -1, 1), glm::vec3(1, 0.5, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 18 copie 1 porto
                        VertexFormat(glm::vec3(1, -1, 1), glm::vec3(1, 0.5, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 19 copie 4 porto
                        VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 0.5, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 20 copie 5 porto
                        VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 0.5, 0),
                                     glm::vec3(0.2, 0.8, 0.6)),

                        // 21 copie 4 alba
                        VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 22 copie 6 alba
                        VertexFormat(glm::vec3(-1, 1, -1), glm::vec3(1, 1, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                        // 23 copie 0 alba
                        VertexFormat(glm::vec3(-1, -1, 1), glm::vec3(1, 1, 1),
                                     glm::vec3(0.2, 0.8, 0.6)),
                };

        vector<unsigned int> indices4 =
                {
                        // Complete indices data for the cube mesh
                        //prima fata - albastru
                        0, 1, 2,    // indices for first triangle
                        1, 3, 2,    // indices for second triangle

                        // a doua fata - rosie
                        8, 9, 10,
                        8, 10, 11,

                        // a treia fata - galbena
                        13, 7, 14,
                        13, 5, 7,

                        // a patra fata - verde
                        6, 15, 4,
                        15, 16, 4,

                        // a cincea fata - protocaliu
                        17, 19, 18,
                        18, 19, 20,

                        // a sasea fata - alba
                        12, 22, 21,
                        23, 12, 21,
                };

        // Actually create the mesh from the data
        CreateMesh("cube_C", vertices4, indices4);

    }

}


void Lab2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    // Create the VAO and bind it
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(),
                 &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(),
                 &indices[0], GL_STATIC_DRAW);
    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);
    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}


void Lab2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab2::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Enable face culling
    glEnable(GL_CULL_FACE);
    // Set face custom culling. Use the `cullFace` variable.
    glCullFace(cullFace);
    // Render an object using face normals for color
    RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -1.5f), glm::vec3(0.75f));

    // Render an object using colors from vertex
    RenderMesh(meshes["cube_A"], shaders["VertexColor"], glm::vec3(-1.5f, 0.5f, 0), glm::vec3(0.25f));

    // Draw the mesh that was created with `CreateMesh()`
    RenderMesh(meshes["cube_B"], shaders["VertexColor"], glm::vec3(1.5f, 0.5f, 0), glm::vec3(0.25f));

    // Draw the tetrahedron
    RenderMesh(meshes["tetraedu_attempt"], shaders["VertexColor"], glm::vec3(0, 0.5f, 0), glm::vec3(0.25f));

    // Draw the square
    RenderMesh(meshes["patrat"], shaders["VertexColor"], glm::vec3(0, 0.5f, 1.5f), glm::vec3(0.25f));


    //bonus
    RenderMesh(meshes["cube_C"], shaders["VertexColor"], glm::vec3(0, 1.25f, -1.5f), glm::vec3(0.25f));


    // Disable face culling
    glDisable(GL_CULL_FACE);

}


void Lab2::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab2::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab2::OnKeyPress(int key, int mods)
{
    // Switch between GL_FRONT and GL_BACK culling.
    // Save the state in `cullFace` variable and apply it in the
    // `Update()` method, NOT here!
    if (key == GLFW_KEY_F)
    {
        switch (cullFace)
        {
        case GL_FRONT:
            cullFace = GL_BACK;
            break;
        default:
            cullFace = GL_FRONT;
            break;
        }
    }

    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
}


void Lab2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab2::OnWindowResize(int width, int height)
{
}
