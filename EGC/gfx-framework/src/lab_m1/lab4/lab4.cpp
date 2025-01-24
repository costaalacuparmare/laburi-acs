#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/lab4/transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab04::Lab04()
{
}


Lab04::~Lab04()
{
}


void Lab04::Init()
{
    polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    // bonus
    level = 1;
    radianBonus = M_PI / 6;
    scaleBonus = 1;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
}

void Lab04::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Lab04::RenderScene() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::RotateOX(angularStepOX);
    modelMatrix *= transform3D::RotateOY(angularStepOY);
    modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
}

void Lab04::DrawTree(glm::mat4 parentMatrix, int lvl, float height, float scaleB) {
    if (lvl == 0) {
        return;
    }
    float scaleNew = scaleB * 0.7f;
    float heightNew = height * 2 / 3;
    modelMatrix = parentMatrix;
    modelMatrix /= transform3D::Scale(scaleB, height, scaleB);
    modelMatrix *= transform3D::Translate(0, height * 0.5f, 0);
    modelMatrix *= transform3D::RotateOZ(radianBonus);
    modelMatrix *= transform3D::Translate(0, heightNew / 2, 0);
    modelMatrix *= transform3D::Scale(scaleNew, heightNew, scaleNew);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    DrawTree(modelMatrix, lvl - 1, heightNew, scaleNew);

    modelMatrix = parentMatrix;
    modelMatrix *= transform3D::Scale(1 / scaleB, 1 / height, 1 / scaleB);
    modelMatrix *= transform3D::Translate(0, height * 0.5f, 0);
    modelMatrix *= transform3D::RotateOZ(-radianBonus);
    modelMatrix *= transform3D::Translate(0, heightNew / 2, 0);
    modelMatrix *= transform3D::Scale(scaleNew, heightNew, scaleNew);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    DrawTree(modelMatrix, lvl - 1, heightNew, scaleNew);
}

void Lab04::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0, 2.5f, -10);
    modelMatrix *= transform3D::Scale(scaleBonus, 5, scaleBonus);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    DrawTree(modelMatrix, level - 1, 5, scaleBonus);
    DrawCoordinateSystem();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // render the scene again, in the new viewport
    DrawCoordinateSystem();
    RenderScene();
}

void Lab04::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab04::OnInputUpdate(float deltaTime, int mods)
{
    // Add transformation logic
    // first transformation
    if (window->KeyHold(GLFW_KEY_UP)) {
        translateY += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        translateY -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        translateX += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        translateX -= deltaTime;
    }

    //second cube scaling
    if (window->KeyHold(GLFW_KEY_1)) {
        scaleX += deltaTime;
        scaleY += deltaTime;
        scaleZ += deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_2)) {
        scaleX -= deltaTime;
        scaleY -= deltaTime;
        scaleZ -= deltaTime;
    }

    // third cube rotation
    if (window->KeyHold(GLFW_KEY_3)) {
        angularStepOX += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_4)) {
        angularStepOX -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_5)) {
        angularStepOY += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_6)) {
        angularStepOY -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_7)) {
        angularStepOZ += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_8)) {
        angularStepOZ -= deltaTime;
    }

}


void Lab04::OnKeyPress(int key, int mods)
{
    // Add key press event
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

    // Add viewport movement and scaling logic

    if (key == GLFW_KEY_I) {
        miniViewportArea.y += 10;
    }
    if (key == GLFW_KEY_J) {
        miniViewportArea.x -= 10;
    }
    if (key == GLFW_KEY_K) {
        miniViewportArea.y -= 10;
    }
    if (key == GLFW_KEY_L) {
        miniViewportArea.x += 10;
    }

    if (key == GLFW_KEY_U) {
        miniViewportArea.width -= 10;
        miniViewportArea.height -= 10;
    }
    if (key == GLFW_KEY_O) {
        miniViewportArea.width += 10;
        miniViewportArea.height += 10;
    }

    //bonus
    if (key == GLFW_KEY_M) {
        level++;
    }
    if (key == GLFW_KEY_N) {
        level--;
    }
}


void Lab04::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab04::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab04::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab04::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab04::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab04::OnWindowResize(int width, int height)
{
}
