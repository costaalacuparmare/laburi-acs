#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

Lab1::Lab1()
{
    // Never forget to initialize class variables!
    r = 0;
    g = 0;
    b = 0;
    mesh_change = nullptr;
    x = 0;
    y = 0.1;
    z = 0;
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.
    {
        Mesh* mesh2 = new Mesh("sphere");
        mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh2->GetMeshID()] = mesh2;
    }

    {
        Mesh* mesh3 = new Mesh("teapot");
        mesh3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh3->GetMeshID()] = mesh3;
    }

    mesh_change = meshes["box"];

}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(r, g, b, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(mesh_change, glm::vec3(x, y, z), glm::vec3(0.5f));

    if (moves) {
        if (dist <= 180) {
            x = initPoz.x + cos(dist * 3.14/180) - 1;
            y = initPoz.y + sin(dist * 3.14/180);
            dist++;
        } else {
            moves = false;
            initPoz.x = x;
            initPoz.y = y;
        }
    }
}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.
    if (window->KeyHold(GLFW_KEY_UP)) {
        z -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        z += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        x -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        x += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_Q)) {
        y -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_E)) {
        y += deltaTime;
    }


}


void Lab1::OnKeyPress(int key, int mods) {
    // Add key press event
    if (key == GLFW_KEY_F) {
        // Change the values of the color components.
        // You can use the variables declared in the `Update` function.
        r = 0;
        g = 1;
        b = 1;
    }

    // Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.
    if (key == GLFW_KEY_G) {
        if (mesh_change == meshes["box"]) {
            mesh_change = meshes["sphere"];
        } else {
            if (mesh_change == meshes["sphere"]) {
                mesh_change = meshes["teapot"];
            } else {
                mesh_change = meshes["box"];
            }
        }
    }

    if (key == GLFW_KEY_B) {
        moves = true;
        dist = 2;
        initPoz.x = x;
        initPoz.y = y;
        initPoz.z = z;
    }

}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
