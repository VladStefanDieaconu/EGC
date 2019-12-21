/*
 *  ****************************************************************************
 *  Copyright 2019 Vlad-Stefan Dieaconu
 *  None Rights Reserved.
 *
 *  NOTICE:  All information contained herein is Open Source. You can
 * 	modify it in any way without having to ask for permission.
 *
 * 	Original publisher: https://github.com/vladstefandieaconu
 *  ****************************************************************************
 */

#include "Tema1.h"
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{

}

void Tema1::Init()
{
	cullFace = GL_BACK;
	polygonMode = GL_FILL;

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a mesh box using custom data
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(95.19, 11.11,  0), glm::vec3(0.8,0.4,0.2)), // F - PORTOCALIU
			VertexFormat(glm::vec3(76.66, 33.98,  0), glm::vec3(0.8,0.4,0.2)), // D
			VertexFormat(glm::vec3(30.71, 30.8,  0), glm::vec3(0.8,0.4,0.2)), // E

			VertexFormat(glm::vec3(124.51, -14.14,  0), glm::vec3(0.1,0,0.1)), // A - NEGRU
			VertexFormat(glm::vec3(96.36, 13.11,  0), glm::vec3(0.1,0,0.1)), // B
			VertexFormat(glm::vec3(75.37, -3.07,  0), glm::vec3(0.1,0,0.1)), // C

			VertexFormat(glm::vec3(95.19, 11.11,  0), glm::vec3(0.8,0.4,0.2)), // F
			VertexFormat(glm::vec3(54.85, -17.87,  0), glm::vec3(0.8,0.4,0.2)), // G
			VertexFormat(glm::vec3(30.71, 30.8,  0), glm::vec3(0.8,0.4,0.2)), // E

			VertexFormat(glm::vec3(113.46, 75.33,  0), glm::vec3(0.1,0.6,0.3)), // H - VERDE
			VertexFormat(glm::vec3(21.25, 41.08,  0),  glm::vec3(0.1,0.6,0.3)), // I
			VertexFormat(glm::vec3(75.61, 33.86,  0),  glm::vec3(0.1,0.6,0.3)), // J

			VertexFormat(glm::vec3(21.25, 41.08,  0), glm::vec3(0.1,0.6,0.3)), // I - VERDE
			VertexFormat(glm::vec3(-7.66, 20.48,  0), glm::vec3(0.1,0.6,0.3)), // K
			VertexFormat(glm::vec3(18.92, 10.44,  0), glm::vec3(0.1,0.6,0.3)), // L

			VertexFormat(glm::vec3(21.25, 41.08,  0), glm::vec3(0.1,0.6,0.3)), // I - VERDE
			VertexFormat(glm::vec3(75.61, 33.86,  0), glm::vec3(0.1,0.6,0.3)), // J
			VertexFormat(glm::vec3(18.92, 10.44,  0), glm::vec3(0.1,0.6,0.3)), // L

			VertexFormat(glm::vec3(-157.3, 51.91,  0), glm::vec3(0.1,0.6,0.3)), // M - VERDE
			VertexFormat(glm::vec3(-44.09, -20.82,  0), glm::vec3(0.1,0.6,0.3)), // N
			VertexFormat(glm::vec3(-60.32, 42.4,  0), glm::vec3(0.1,0.6,0.3)), // O

			VertexFormat(glm::vec3(-44.09, -20.82,  0), glm::vec3(0.1,0.6,0.3)), // N - VERDE
			VertexFormat(glm::vec3(-60.32, 42.4,  0), glm::vec3(0.1,0.6,0.3)), // O
			VertexFormat(glm::vec3(36.67, 2.65,  0), glm::vec3(0.1,0.6,0.3)), // P

			VertexFormat(glm::vec3(54.85, -17.87,  0), glm::vec3(0.9,0.7,0.1)), // G - GALBEN
			VertexFormat(glm::vec3(27.43, -42.28,  0), glm::vec3(0.9,0.7,0.1)), // Q
			VertexFormat(glm::vec3(30.71, 30.8,  0), glm::vec3(0.9,0.7,0.1)), // E

			VertexFormat(glm::vec3(30.71, 30.8,  0), glm::vec3(0.9,0.7,0.1)), // E - GALBEN
			VertexFormat(glm::vec3(27.43, -42.28,  0), glm::vec3(0.9,0.7,0.1)), // Q
			VertexFormat(glm::vec3(-7.7, 20.05,  0), glm::vec3(0.9,0.7,0.1)), // R

			VertexFormat(glm::vec3(-7.7, 20.05,  0), glm::vec3(0.9,0.7,0.1)), // R
			VertexFormat(glm::vec3(-55.43, -13.67,  0), glm::vec3(0.9,0.7,0.1)), // S
			VertexFormat(glm::vec3(27.43, -42.28,  0), glm::vec3(0.9,0.7,0.1)), // T

			VertexFormat(glm::vec3(-55.43, -13.67,  0), glm::vec3(0.9,0.7,0.1)), // S
			VertexFormat(glm::vec3(27.43, -42.28,  0), glm::vec3(0.9,0.7,0.1)), // T
			VertexFormat(glm::vec3(-86.24, -39.44,  0), glm::vec3(0.9,0.7,0.1)), // U

			VertexFormat(glm::vec3(-40.62, -40.79,  0), glm::vec3(0.8,0.4,0.2)), // V
			VertexFormat(glm::vec3(-87.81, -38.65,  0), glm::vec3(0.8,0.4,0.2)), // W
			VertexFormat(glm::vec3(-158, -114.39,  0), glm::vec3(0.8,0.4,0.2)) // Z
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			3, 4, 5,
			6, 7, 8,
			9, 10, 11,
			12, 13, 14,
			15, 16, 17,
			18, 19, 20,
			21, 22, 23,
			24, 25, 26,
			27, 28, 29,
			30, 31, 32,
			33, 34, 35,
			36, 37, 38
		};

		meshes["bird"] = new Mesh("bird");
		meshes["bird"]->InitFromData(vertices, indices);


		vector<VertexFormat> verticesSecBird
		{
			VertexFormat(glm::vec3(95.19, 11.11,  0), glm::vec3(0.1,0.6,0.3)), // F - PORTOCALIU
			VertexFormat(glm::vec3(76.66, 33.98,  0), glm::vec3(0.1,0.6,0.3)), // D
			VertexFormat(glm::vec3(30.71, 30.8,  0), glm::vec3(0.1,0.6,0.3)), // E

			VertexFormat(glm::vec3(124.51, -14.14,  0), glm::vec3(0.1,0,0.1)), // A - NEGRU
			VertexFormat(glm::vec3(93.36, 13.11,  0), glm::vec3(0.1,0,0.1)), // B
			VertexFormat(glm::vec3(75.37, -3.07,  0), glm::vec3(0.1,0,0.1)), // C

			VertexFormat(glm::vec3(95.19, 11.11,  0), glm::vec3(0.8,0.4,0.2)), // F
			VertexFormat(glm::vec3(54.85, -17.87,  0), glm::vec3(0.8,0.4,0.2)), // G
			VertexFormat(glm::vec3(30.71, 30.8,  0), glm::vec3(0.8,0.4,0.2)), // E

			VertexFormat(glm::vec3(91.46, -32.56,  0), glm::vec3(0.1,0.6,0.3)), // H - VERDE
			VertexFormat(glm::vec3(-0.75, 1.68,  0),  glm::vec3(0.1,0.6,0.3)), // I
			VertexFormat(glm::vec3(53.61, 8.9,  0),  glm::vec3(0.1,0.6,0.3)), // J

			VertexFormat(glm::vec3(-0.75, 1.68,  0),  glm::vec3(0.1,0.6,0.3)), // I - VERDE
			VertexFormat(glm::vec3(-29.66, 22.28,  0), glm::vec3(0.1,0.6,0.3)), // K
			VertexFormat(glm::vec3(-3.08, 32.33,  0), glm::vec3(0.1,0.6,0.3)), // L

			VertexFormat(glm::vec3(-0.75, 1.68,  0),  glm::vec3(0.1,0.6,0.3)), // I - VERDE
			VertexFormat(glm::vec3(53.61, 8.9,  0),  glm::vec3(0.1,0.6,0.3)), // J
			VertexFormat(glm::vec3(-3.08, 32.33,  0), glm::vec3(0.1,0.6,0.3)), // L

			VertexFormat(glm::vec3(-153.3, -44.82,  0), glm::vec3(0.1,0.6,0.3)), // M - VERDE
			VertexFormat(glm::vec3(-56.32, -35.31,  0), glm::vec3(0.1,0.6,0.3)), // N
			VertexFormat(glm::vec3(-40.09, 27.91,  0), glm::vec3(0.1,0.6,0.3)), // O

			VertexFormat(glm::vec3(40.67, 4.44,  0), glm::vec3(0.1,0.6,0.3)), // P - VERDE
			VertexFormat(glm::vec3(-56.32, -35.31,  0), glm::vec3(0.1,0.6,0.3)), // N
			VertexFormat(glm::vec3(-40.09, 27.91,  0), glm::vec3(0.1,0.6,0.3)), // O

			VertexFormat(glm::vec3(54.85, -17.87,  0), glm::vec3(0.9,0.7,0.1)), // G - GALBEN
			VertexFormat(glm::vec3(27.43, -42.28,  0), glm::vec3(0.9,0.7,0.1)), // Q
			VertexFormat(glm::vec3(30.71, 30.8,  0), glm::vec3(0.9,0.7,0.1)), // E

			VertexFormat(glm::vec3(30.71, 30.8,  0), glm::vec3(0.9,0.7,0.1)), // E - GALBEN*
			VertexFormat(glm::vec3(27.43, -42.28,  0), glm::vec3(0.9,0.7,0.1)), // Q
			VertexFormat(glm::vec3(-7.7, 20.05,  0), glm::vec3(0.9,0.7,0.1)), // R

			VertexFormat(glm::vec3(-7.7, 20.05,  0), glm::vec3(0.9,0.7,0.1)), // R
			VertexFormat(glm::vec3(-55.43, -13.67,  0), glm::vec3(0.9,0.7,0.1)), // S
			VertexFormat(glm::vec3(27.43, -42.28,  0), glm::vec3(0.9,0.7,0.1)), // T

			VertexFormat(glm::vec3(-55.43, -13.67,  0), glm::vec3(0.9,0.7,0.1)), // S
			VertexFormat(glm::vec3(27.43, -42.28,  0), glm::vec3(0.9,0.7,0.1)), // T
			VertexFormat(glm::vec3(-86.24, -39.44,  0), glm::vec3(0.9,0.7,0.1)), // U

			VertexFormat(glm::vec3(-40.62, -40.79,  0), glm::vec3(0.8,0.4,0.2)), // V
			VertexFormat(glm::vec3(-87.81, -38.65,  0), glm::vec3(0.8,0.4,0.2)), // W
			VertexFormat(glm::vec3(-158, -114.39,  0), glm::vec3(0.8,0.4,0.2)) // Z
		};

		vector<unsigned short> indicesSecBird =
		{
			0, 1, 2,	// indices for first triangle
			3, 4, 5,
			6, 7, 8,
			9, 10, 11,
			12, 13, 14,
			15, 16, 17,
			18, 19, 20,
			21, 22, 23,
			24, 25, 26,
			27, 28, 29,
			30, 31, 32,
			33, 34, 35,
			36, 37, 38
		};

		meshes["birdSec"] = new Mesh("birdSec");
		meshes["birdSec"]->InitFromData(verticesSecBird, indicesSecBird);

		vector<VertexFormat> verticesPipe
		{
			VertexFormat(glm::vec3(0, 4,  0), glm::vec3(0,0.9,0.2)),
			VertexFormat(glm::vec3(3, 4,  0), glm::vec3(0,0.9,0.2)),
			VertexFormat(glm::vec3(0, 3,  0), glm::vec3(0,0.9,0.2)),

			VertexFormat(glm::vec3(3, 4,  0), glm::vec3(0,0.6,0.5)),
			VertexFormat(glm::vec3(0, 3,  0), glm::vec3(0,0.6,0.5)),
			VertexFormat(glm::vec3(3, 3,  0), glm::vec3(0,0.6,0.5)),

			VertexFormat(glm::vec3(3, 3,  0), glm::vec3(0.1,1,0.8)),
			VertexFormat(glm::vec3(3, 0,  0), glm::vec3(0.1,1,0.8)),
			VertexFormat(glm::vec3(2, 3,  0), glm::vec3(0.1,1,0.8)),

			VertexFormat(glm::vec3(3, 0,  0), glm::vec3(0.2,0.9,0.8)),
			VertexFormat(glm::vec3(2, 3,  0), glm::vec3(0.2,0.9,0.8)),
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0.2,0.9,0.8)),

			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0.2,0.1,0.9)),
			VertexFormat(glm::vec3(2, 3,  0), glm::vec3(0.2,0.1,0.9)),
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0.2,0.1,0.9)), // H

			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0.2,0.6,0.6)),
			VertexFormat(glm::vec3(2, 3,  0), glm::vec3(0.2,0.6,0.6)),
			VertexFormat(glm::vec3(0, 3,  0), glm::vec3(0.2,0.6,0.6))
		};

		vector<unsigned short> indicesPipe =
		{
			0, 1, 2,	// indices for first triangle
			3, 4, 5,
			6, 7, 8,
			9, 10, 11,
			12, 13, 14,
			15, 16, 17
		};

		meshes["pipe"] = new Mesh("pipe");
		meshes["pipe"]->InitFromData(verticesPipe, indicesPipe);


		std::vector<VertexFormat> verticesSquare =
		{
			VertexFormat(glm::vec3(0, 0, 0),  glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(1, 1, 0),  glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(0, 1, 0),  glm::vec3(1, 1, 1))
		};

		Mesh* square = new Mesh("square");
		std::vector<unsigned short> indicesSquare = { 0, 1, 2, 3 };
		square->InitFromData(verticesSquare, indicesSquare);
	}

	gravity = 50;
	velocity = -100;
	angle = 0.01;
	scor = 0;
	counter = 0;

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	Mesh* square1 = CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);


	for (int i = 0; i < 7; ++i) {
		indexOfPipes[i] = 800 + 200 * i;
		randHeight[i] = randNum = rand() % (75);
	}
}

Mesh* Tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it

	// TODO: Create the VBO and bind it
	unsigned int VBO = 0;

	// TODO: Send vertices data into the VBO buffer

	// TODO: Crete the IBO and bind it
	unsigned int IBO = 0;

	// TODO: Send indices data into the IBO buffer

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO: Unbind the VAO

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.1, 0.5, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

Mesh* Tema1::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

void Tema1::renderBird()
{
	gravity -= 4.0;;

	modelMatrix = glm::mat4();
	modelMatrix *= Transform3D::Translate(100, gravity, 0);

	angle -= 0.009;
	modelMatrix *= Transform3D::RotateOZ(angle);

	modelMatrix *= Transform3D::Scale(0.3, 0.3, 1);
	if (counter % 40 < 20) {
		RenderMesh(meshes["bird"], shaders["VertexColor"], modelMatrix);
	}
	else if (counter % 40 > 20) {
		RenderMesh(meshes["birdSec"], shaders["VertexColor"], modelMatrix);
	}

	// doar pentru ca trebuie sa avem doua tipuri diferite de primitive
	modelMatrix = glm::mat4();
	modelMatrix *= Transform3D::Translate(112, gravity + 3, 1);
	modelMatrix *= Transform3D::RotateOZ(angle);
	modelMatrix *= Transform3D::Scale(0.05, 0.05, 1);
	RenderMesh(meshes["square1"], shaders["VertexColor"], modelMatrix);
	
}

bool Tema1::Intersect() {
	bool collisionDown = false;
	bool collisionUp = false;

	if (gravity > 720 || gravity < 0) {
		return true;
	}

	for (int i = 0; i < 7; ++i) {
			// upper pipe
			if (50 < indexOfPipes[i] + 50 &&
				50 + 45 > indexOfPipes[i] &&
				gravity < 550 - randHeight[i] + 160 &&
				gravity + 45 > 550 - randHeight[i]) {
				collisionUp = true;
			}

			//bottom pipe
			if (50 < indexOfPipes[i] + 50 &&
				50 + 45 > indexOfPipes[i] &&
				gravity < -100 + randHeight[i] + 320 &&
				gravity + 45 > -100 + randHeight[i]) {
				collisionDown = true;
			}
	}

	return collisionDown || collisionUp;
}

void Tema1::renderPipes()
{
	for (int i = 0; i < 7; ++i) {

		modelMatrix = glm::mat4();
		modelMatrix *= Transform3D::Translate(indexOfPipes[i], 550 - randHeight[i], 2);
		modelMatrix *= Transform3D::Scale(33.33, 80, 1);
		RenderMesh(meshes["pipe"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4();
		modelMatrix *= Transform3D::Translate(indexOfPipes[i], -100 + randHeight[i], 2);
		modelMatrix *= Transform3D::Scale(33.33, 80, 1);
		RenderMesh(meshes["pipe"], shaders["VertexColor"], modelMatrix);

		if (indexOfPipes[i] == 100) {
			scor++;
			cout << "Am trecut pritr-un pipe \n";
			cout << "\n *** SCOR = " << scor << " *** \n";
		}
	}

}

void Tema1::Update(float deltaTimeSeconds)
{
	if (Intersect()) {
		cout << "\n Ai pierdut \n";
		modelMatrix = glm::mat4();
		modelMatrix *= Transform3D::Translate(0, 0, 1);
		modelMatrix *= Transform3D::Scale(200, 200, 5);
		RenderMesh(meshes["square1"], shaders["VertexColor"], modelMatrix);
	}
	else {

		velocity -= 0.05;
		counter++;

		for (int i = 0; i < 7; ++i) {
			indexOfPipes[i] -= 2;
			if (indexOfPipes[i] < -100) {
				indexOfPipes[i] = 1280;
				randHeight[i] = rand() % (75);
			}
		}

		glLineWidth(3);
		glPointSize(5);
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

		renderPipes();
		renderBird();
	}

}

void Tema1::FrameEnd()
{
	DrawCoordinatSystem();
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	// TODO: switch between GL_FRONT and GL_BACK culling
	// Save the state in "cullFace" variable and apply it in the Update() method not here

	if (key == GLFW_KEY_SPACE)
	{
		gravity += 100.0;
		angle = abs(angle) + 0.1;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
} 

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
