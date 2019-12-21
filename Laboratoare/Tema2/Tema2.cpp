#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include "Transform3D.h"
#include "LabCamera.h"

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	planeX = 1;
	planeY = 3;
	rotationOfPlane = 0;
	numOfHearts = 3;
	remainingCombustible = 0.04;
	boxSize = 3.5;
	rotationOfElice = 0;
	rotationOfSea = 0;
	offsetElice = 0.32;
	offsetEliceX = 0.22;
	fallingElice = 0;
	rotationOfPlaneFalling = 3;
	smoke = -0.5;
	harder = 0.0f;

	for (int i = 0; i < 10; ++i) {
		alreadyHit[i] = 0;
	}

	glm::vec3 center = glm::vec3(0, 0, 0);

	camera = new Laborator::CameraTema2();
	camera->Set(glm::vec3(0, 2, 4), glm::vec3(0, 2, 0), glm::vec3(0, 2, 0));

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	{
		Mesh* mesh = new Mesh("mare");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "marea.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("square");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "square.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("planeUV");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "planeUV.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("elice");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "elice.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("Heart");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "heart_lp.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("bonus");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("obstacle");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("bonus");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Teapot/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Teapot/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("obstacle");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Obstacle/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Obstacle/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("FumDinCur");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/CombustibleBox/BlackBox/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/CombustibleBox/BlackBox/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("BlackBox");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/CombustibleBox/BlackBox/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/CombustibleBox/BlackBox/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("GreenBox");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/CombustibleBox/GreenBox/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/CombustibleBox/GreenBox/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("Sea");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Sea/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Sea/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("BackSea");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/BackSea/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/BackSea/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("Heart");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Heart/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Heart/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("Plane");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Plane/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Plane/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		vector<VertexFormat> verticesClouds
		{
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1, 0.9, 0.8)),
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 0.9, 0.8)),
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 0.9, 0.8)),

			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1, 0.9, 0.8)),	
			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 0.9, 0.8)),	
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 0.9, 0.8)),		

			VertexFormat(glm::vec3(0, 0,  -1), glm::vec3(1, 0.9, 0.8)),	
			VertexFormat(glm::vec3(1, 0,  -1), glm::vec3(1, 0.9, 0.8)),	
			VertexFormat(glm::vec3(1, 1,  -1), glm::vec3(1, 0.9, 0.8)),

			VertexFormat(glm::vec3(0, 0,  -1), glm::vec3(1, 0.9, 0.8)),	
			VertexFormat(glm::vec3(0, 1,  -1), glm::vec3(1, 0.9, 0.8)),	
			VertexFormat(glm::vec3(1, 1,  -1), glm::vec3(1, 0.9, 0.8)),	

			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0.9, 0.8, 0.6)),
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0.9, 0.8, 0.6)),
			VertexFormat(glm::vec3(0, 0, -1), glm::vec3(0.9, 0.8, 0.6)),

			VertexFormat(glm::vec3(0, 0, -1), glm::vec3(0.9, 0.8, 0.6)),
			VertexFormat(glm::vec3(1, 0, -1), glm::vec3(0.9, 0.8, 0.6)),
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0.9, 0.8, 0.6)),

			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0.9, 0.8, 0.6)),
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0.9, 0.8, 0.6)),
			VertexFormat(glm::vec3(0, 1, -1), glm::vec3(0.9, 0.8, 0.6)),

			VertexFormat(glm::vec3(0, 1, -1), glm::vec3(0.9, 0.8, 0.6)),
			VertexFormat(glm::vec3(1, 1, -1), glm::vec3(0.9, 0.8, 0.6)),
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0.9, 0.8, 0.6)),

			VertexFormat(glm::vec3(1, 0, -1), glm::vec3(0.8, 0.6, 0.5)),
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0.8, 0.6, 0.5)),
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0.8, 0.6, 0.5)),

			VertexFormat(glm::vec3(1, 1, -1), glm::vec3(0.8, 0.6, 0.5)),
			VertexFormat(glm::vec3(1, 0, -1), glm::vec3(0.8, 0.6, 0.5)),
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0.8, 0.6, 0.5)),

			VertexFormat(glm::vec3(0, 0, -1), glm::vec3(0.8, 0.6, 0.5)),
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0.8, 0.6, 0.5)),
			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0.8, 0.6, 0.5)),

			VertexFormat(glm::vec3(0, 0, -1), glm::vec3(0.8, 0.6, 0.5)),
			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0.8, 0.6, 0.5)),
			VertexFormat(glm::vec3(0, 1, -1), glm::vec3(0.8, 0.6, 0.5)),
		};

		vector<unsigned short> indicesClouds =
		{
			0, 1, 2,
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
		};

		CreateMesh("clouds", verticesClouds, indicesClouds);
	}

	positionCloudsX[0] = 2;
	positionCloudsY[0] = 2;
	for (int i = 1; i < 10; ++i) {
		positionCloudsX[i] = positionCloudsX[i-1] + 0.06;
		positionCloudsY[i] = (i % 2 == 0 ) ? positionCloudsY[i-1] + 0.01 : positionCloudsY[i - 1] - 0.01;
		rotationsCloudsOY[i] = rand() % 360;
		rotationsCloudsOX[i] = rand() % 360;
		rotationsCloudsOZ[i] = rand() % 360;
	}

	movementOfClouds = 3;
	minPlane = glm::vec4(-0.5, 3, -0.5, 1);
	maxPlane = glm::vec4(0.5, 3.5, +0.5, 1);
	glm::vec4 obstacole1 = glm::vec4(2.5, -1, 0, 1);
}
Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));


	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// OBSERVATION: after interchanging the colour and normal pipes, the colours appear altered
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}


void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.7, 0.5, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	harder = harder + 0.001;
	if (GameOver() == false) {
		if (fP == 1) {
			glm::vec4 matrix = glm::vec4(1);
			matrix = modelMatrixAvion * matrix;
			camera->Set(glm::vec3(matrix.x + 0.1, planeY + 0.6, matrix.z + 0.1), glm::vec3(900, planeY - 400, 2), glm::vec3(0, 1, 0));
		}
		if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
		{
			rotationOfSea = rotationOfElice * 0.05 + harder;
			rotationOfElice = rotationOfElice + 100 + harder;
			movementOfClouds = movementOfClouds + 5 + harder;
			boxSize -= remainingCombustible * 0.1;
			remainingCombustible -= 0.0005;
			RenderSomeSmoke();
		}
		else {
			rotationOfElice = rotationOfElice + 10 + harder;
			rotationOfSea = rotationOfElice * 0.05 + harder;
			movementOfClouds += 0.5 + harder;
			boxSize -= remainingCombustible * 0.001;
			remainingCombustible -= 0.00001;
		}
		if (fP == 0) {
			RenderHeart();
			RenderCombustibleBox();
		}
		else {
			RenderHeartFirstCamera();
			RenderCombustibleBoxFirstCamera();
		}
		RenderSea();
		RenderClouds();
		RenderPlane();
		RenderCombustibleBonus();
		RenderObstacle();
	}
	else {
		rotationOfElice = rotationOfElice + 10;
		rotationOfSea = rotationOfElice * 0.05;
		movementOfClouds += 0.5;
		boxSize -= remainingCombustible * 0.001;
		remainingCombustible -= 0.00001;
		rotationOfPlaneFalling += 1;;
		planeY -= 0.03;
		RenderSea();
		RenderPlaneFalling();

		RenderObstacle();
		RenderClouds();
		RenderCombustibleBonus();
	}
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location1 = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	int location2 = glGetUniformLocation(shader->program, "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	int location3 = glGetUniformLocation(shader->program, "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	float time = Engine::GetElapsedTime();
	int location4 = glGetUniformLocation(shader->program, "time");
	glUniform1f(location4, time);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// add key press event
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C && fP == 0) {
		fP = 1;
		glm::vec4 matrix = glm::vec4(1);
		matrix = modelMatrixAvion * matrix;
		camera->Set(glm::vec3(matrix.x, planeY, matrix.z), glm::vec3(5, matrix.y, 2), glm::vec3(0, 1, 0));
	}
	else if (key == GLFW_KEY_C && fP == 1) {
		fP = 0;
		camera->Set(glm::vec3(0, 2, 4), glm::vec3(0, 2, 0), glm::vec3(0, 2, 0));
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (GameOver() == false) {
		planeY -= deltaY * 0.005f;
		if (deltaY > 0 && !(rotationOfPlane > 10 || rotationOfPlane < -10)) {
			rotationOfPlane += 1;
			offsetEliceX += 0.005;
		}

		if (deltaY < 0 && !(rotationOfPlane > 10 || rotationOfPlane < -10)) {
			rotationOfPlane -= 1;
			offsetEliceX -= 0.005;
		}

		if (deltaY == 0) {
			//rotationOfPlane = 0;
			//offsetEliceX = 0.22;
		}

		if (rotationOfPlane > 10) {
			rotationOfPlane = 10;
			offsetEliceX = 0.22 + 0.05;
		}
		if (rotationOfPlane < -10) {
			rotationOfPlane = -10;
			offsetEliceX = 0.22 - 0.05;
		}
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	//planeX = mouseX;
	//planeY = mouseY;
}

void Tema2::OnWindowResize(int width, int height)
{
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::RenderSea()
{
	RenderBackSea();
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, -2.7, -5);
	modelMatrix *= Transform3D::Scale(1.1, 1.1, 1.1);
	modelMatrix *= Transform3D::RotateOX(RADIANS(90));
	modelMatrix *= Transform3D::RotateOY(RADIANS(rotationOfSea));
	RenderMesh(meshes["mare"], shaders["Sea"], modelMatrix);
}

void Tema2::RenderBackSea()
{
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, -2.7, -5);
	modelMatrix *= Transform3D::Scale(1, 1, 1);
	modelMatrix *= Transform3D::RotateOX(RADIANS(90));
	modelMatrix *= Transform3D::RotateOY(RADIANS(rotationOfSea));
	RenderMesh(meshes["mare"], shaders["BackSea"], modelMatrix);
}

void Tema2::RenderPlane()
{
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, planeY, 0);
	modelMatrix *= Transform3D::Scale(0.1, 0.1, 0.1);
	modelMatrix *= Transform3D::RotateOY(RADIANS(180));
	modelMatrix *= Transform3D::RotateOZ(RADIANS(rotationOfPlane));

	modelMatrixAvion = modelMatrix;
	
	minPlane = modelMatrix * minPlane;
	maxPlane = modelMatrix * maxPlane;
	savePlaneMatrix = modelMatrix;
	RenderMesh(meshes["planeUV"], shaders["Plane"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(offsetEliceX, planeY + offsetElice, 0);
	modelMatrix *= Transform3D::Scale(0.1, 0.05, 0.05);
	modelMatrix *= Transform3D::RotateOX(RADIANS(rotationOfElice));
	modelMatrix *= Transform3D::RotateOZ(RADIANS(90));
	RenderMesh(meshes["elice"], shaders["BlackBox"], modelMatrix);
	fallingElice = planeY + offsetElice;
}

void Tema2::RenderPlaneFalling() {
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, planeY, 0);
	modelMatrix *= Transform3D::Scale(0.1, 0.1, 0.1);
	modelMatrix *= Transform3D::RotateOY(RADIANS(180) + rotationOfPlaneFalling * 0.01);
	modelMatrix *= Transform3D::RotateOZ(RADIANS(rotationOfPlaneFalling));
	RenderMesh(meshes["planeUV"], shaders["Plane"], modelMatrix);

	modelMatrixAvion = modelMatrix;

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(offsetEliceX+=0.05, fallingElice-=0.05, 0);
	modelMatrix *= Transform3D::Scale(0.1, 0.05, 0.05);
	modelMatrix *= Transform3D::RotateOX(RADIANS(rotationOfElice));
	modelMatrix *= Transform3D::RotateOZ(RADIANS(90));
	RenderMesh(meshes["elice"], shaders["BlackBox"], modelMatrix);
}

void Tema2::RenderCombustibleBox()
{
	if (remainingCombustible >= 0) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(3.5, 4, 0);
		modelMatrix *= Transform3D::Scale(0.05, 0.02, 0.00001);
		RenderMesh(meshes["square"], shaders["BlackBox"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(boxSize, 4, 0);
		modelMatrix *= Transform3D::Scale(remainingCombustible, 0.015, 0.00005);
		RenderMesh(meshes["square"], shaders["GreenBox"], modelMatrix);
	}
}

void Tema2::RenderCombustibleBoxFirstCamera()
{
	/*if (remainingCombustible >= 0) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(2, planeY + 0.5, -0.5);
		modelMatrix *= Transform3D::Scale(0.05, 0.02, 0.00001);
		modelMatrix *= Transform3D::RotateOY(-0.03);
		modelMatrix *= Transform3D::RotateOZ(42.4);
		RenderMesh(meshes["square"], shaders["BlackBox"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(2, planeY + 0.5, -0.5);
		modelMatrix *= Transform3D::Scale(remainingCombustible, 0.015, 0.00005);
		modelMatrix *= Transform3D::RotateOZ(42.4);
		RenderMesh(meshes["square"], shaders["GreenBox"], modelMatrix);
	}*/
}

bool Tema2::GameOver() {
	if (remainingCombustible <= 0 || numOfHearts<= 0) {
		printf("GAME OVER");
		return true;
	}
	return false;
}

void Tema2::RenderHeart()
{
	switch (numOfHearts)
	{
	case 3: 
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-4, 4, 0);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-3.8, 4, 0);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-3.6, 4, 0);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);
		break;

	case 2:
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-4, 4, 0);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-3.8, 4, 0);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);
		break;

	case 1:
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-4, 4, 0);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);
		break;

	default:
		break;
	}
}

void Tema2::RenderHeartFirstCamera()
{
	switch (numOfHearts)
	{
	case 3:
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(2, planeY +0.5 , -1.2);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		modelMatrix *= Transform3D::RotateOX(-0.3);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(2, planeY + 0.5, -1.4);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		modelMatrix *= Transform3D::RotateOX(-0.3);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(2, planeY + 0.5, -1.6);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		modelMatrix *= Transform3D::RotateOX(-0.3);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);
		break;

	case 2:
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(2, planeY + 0.5, -1.4);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		modelMatrix *= Transform3D::RotateOX(-0.3);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(2, planeY + 0.5, -1.6);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		modelMatrix *= Transform3D::RotateOX(-0.3);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);
		break;

	case 1:
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(2, planeY + 0.5, -1.6);
		modelMatrix *= Transform3D::Scale(0.005, 0.005, 0);
		modelMatrix *= Transform3D::RotateOX(-0.3);
		RenderMesh(meshes["Heart"], shaders["Heart"], modelMatrix);
		break;

	default:
		break;
	}
}

void Tema2::RenderClouds()
{
	for (int i = 0; i < 10; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::RotateOZ(RADIANS(movementOfClouds));
		modelMatrix *= Transform3D::Translate(positionCloudsX[i], positionCloudsY[i], 1);
		modelMatrix *= Transform3D::Scale(0.15, 0.15, 0.15);
		if (i % 5 == 0) {
			modelMatrix *= Transform3D::RotateOX(RADIANS(rotationsCloudsOX[i] += 1));
		}

		if (i % 5 == 2) {
			modelMatrix *= Transform3D::RotateOY(RADIANS(rotationsCloudsOY[i] += 1));
		}

		if (i % 5 == 3) {
			modelMatrix *= Transform3D::RotateOZ(RADIANS(rotationsCloudsOZ[i] += 1));
		}

		if (i % 5 == 4) {
			modelMatrix *= Transform3D::RotateOX(RADIANS(rotationsCloudsOX[i] -= 1));
		}

		if (i % 5 == 1) {
			modelMatrix *= Transform3D::RotateOY(RADIANS(rotationsCloudsOY[i] -= 5));
		}
		RenderMesh(meshes["clouds"], shaders["VertexColor"], modelMatrix);
	}

	for (int i = 0; i < 10; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::RotateOZ(RADIANS(movementOfClouds));
		modelMatrix *= Transform3D::Translate(positionCloudsX[i] + 1, positionCloudsY[i] - 1, 1);
		modelMatrix *= Transform3D::Scale(0.15, 0.15, 0.15);
		if (i % 5 == 4) {
			modelMatrix *= Transform3D::RotateOX(RADIANS(rotationsCloudsOX[i] += 1));
		}

		if (i % 5 == 3) {
			modelMatrix *= Transform3D::RotateOY(RADIANS(rotationsCloudsOY[i] += 1));
		}

		if (i % 5 == 2) {
			modelMatrix *= Transform3D::RotateOZ(RADIANS(rotationsCloudsOZ[i] += 1));
		}

		if (i % 5 == 1) {
			modelMatrix *= Transform3D::RotateOX(RADIANS(rotationsCloudsOX[i] -= 1));
		}

		if (i % 5 == 0) {
			modelMatrix *= Transform3D::RotateOY(RADIANS(rotationsCloudsOY[i] -= 5));
		}
		RenderMesh(meshes["clouds"], shaders["VertexColor"], modelMatrix);
	}


	for (int i = 0; i < 10; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::RotateOZ(RADIANS(movementOfClouds));
		modelMatrix *= Transform3D::Translate(positionCloudsX[i], positionCloudsY[i] - 2, 1);
		modelMatrix *= Transform3D::Scale(0.15, 0.15, 0.15);
		if (i % 5 == 3) {
			modelMatrix *= Transform3D::RotateOX(RADIANS(rotationsCloudsOX[i] += 1));
		}

		if (i % 5 == 4) {
			modelMatrix *= Transform3D::RotateOY(RADIANS(rotationsCloudsOY[i] += 1));
		}

		if (i % 5 == 1) {
			modelMatrix *= Transform3D::RotateOZ(RADIANS(rotationsCloudsOZ[i] += 1));
		}

		if (i % 5 == 2) {
			modelMatrix *= Transform3D::RotateOX(RADIANS(rotationsCloudsOX[i] -= 1));
		}

		if (i % 5 == 0) {
			modelMatrix *= Transform3D::RotateOY(RADIANS(rotationsCloudsOY[i] -= 5));
		}
		RenderMesh(meshes["clouds"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema2::RenderCombustibleBonus() {
	varInc++;
	sinDeBonus = sin(RADIANS(varInc));
	xDeBonus -= 0.01;

	if (xDeBonus < -10) {
		xDeBonus = 0;
	}

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(2.5 + xDeBonus, 1.5 + 2 * sinDeBonus, 0);
	modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
	modelMatrix *= Transform3D::RotateOX(RADIANS(movementOfClouds));
	if (alreadyHit[4] == 0) {
		alreadyHit[4] = intersect(savePlaneMatrix, modelMatrix);
		RenderMesh(meshes["bonus"], shaders["bonus"], modelMatrix);
	}
	else if (alreadyHit[4] != 2) {
		remainingCombustible += 0.001;
		alreadyHit[4] = 2;
		printf("bonus");
	}


	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(1 + xDeBonus, 3 + sinDeBonus, 0);
	modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
	modelMatrix *= Transform3D::RotateOX(RADIANS(movementOfClouds));
	if (alreadyHit[5] == 0) {
		alreadyHit[5] = intersect(savePlaneMatrix, modelMatrix);
		RenderMesh(meshes["bonus"], shaders["bonus"], modelMatrix);
	}
	else if (alreadyHit[5] != 2) {
		remainingCombustible += 0.005;
		alreadyHit[5] = 2;
		printf("bonus");
	}


	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-1.5 + xDeBonus, 4 + sinDeBonus, 0);
	modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
	modelMatrix *= Transform3D::RotateOX(RADIANS(movementOfClouds));
	if (alreadyHit[6] == 0) {
		alreadyHit[6] = intersect(savePlaneMatrix, modelMatrix);
		RenderMesh(meshes["bonus"], shaders["bonus"], modelMatrix);
	}
	else if (alreadyHit[6] != 2) {
		remainingCombustible += 0.005;
		alreadyHit[6] = 2;
		printf("bonus");
	}


	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-3 + xDeBonus, 2 + 3 * sinDeBonus, 0);
	modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
	modelMatrix *= Transform3D::RotateOX(RADIANS(movementOfClouds));
	if (alreadyHit[7] == 0) {
		alreadyHit[7] = intersect(savePlaneMatrix, modelMatrix);
		RenderMesh(meshes["bonus"], shaders["bonus"], modelMatrix);
	}
	else if (alreadyHit[7] != 2) {
		remainingCombustible += 0.005;
		alreadyHit[7] = 2;
		printf("bonus");
	}
}

void Tema2::RenderObstacle() {
	
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::RotateOZ(RADIANS(movementOfClouds));
	modelMatrix *= Transform3D::Translate(2.5, -1, 0);
	modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
	modelMatrix *= Transform3D::RotateOX(RADIANS(movementOfClouds));
	printf("%f", intersect(savePlaneMatrix, modelMatrix));
	if (alreadyHit[0] == 0) {
		alreadyHit[0] = intersect(savePlaneMatrix, modelMatrix);
		RenderMesh(meshes["obstacle"], shaders["obstacle"], modelMatrix);
	}
	else if (alreadyHit[0] != 2) {
		numOfHearts--;
		alreadyHit[0] = 2;
		printf("s-au lovit");
	}


	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::RotateOZ(RADIANS(movementOfClouds));
	modelMatrix *= Transform3D::Translate(3, -3, 0);
	modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
	modelMatrix *= Transform3D::RotateOX(RADIANS(movementOfClouds));
	printf("%f", intersect(savePlaneMatrix, modelMatrix));
	if (alreadyHit[1] == 0) {
		alreadyHit[1] = intersect(savePlaneMatrix, modelMatrix);
		RenderMesh(meshes["obstacle"], shaders["obstacle"], modelMatrix);
	}
	else if (alreadyHit[1] != 2) {
		numOfHearts--;
		alreadyHit[1] = 2;
		printf("s-au lovit");
	}


	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::RotateOZ(RADIANS(movementOfClouds));
	modelMatrix *= Transform3D::Translate(4, -4, 0);
	modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
	modelMatrix *= Transform3D::RotateOX(RADIANS(movementOfClouds));
	printf("%f", intersect(savePlaneMatrix, modelMatrix));
	if (alreadyHit[2] == 0) {
		alreadyHit[2] = intersect(savePlaneMatrix, modelMatrix);
		RenderMesh(meshes["obstacle"], shaders["obstacle"], modelMatrix);
	}
	else if (alreadyHit[2] != 2) {
		numOfHearts--;
		alreadyHit[2] = 2;
		printf("s-au lovit");
	}


	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::RotateOZ(RADIANS(movementOfClouds));
	modelMatrix *= Transform3D::Translate(3.5, -2.5, 0);
	modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
	modelMatrix *= Transform3D::RotateOX(RADIANS(movementOfClouds));
	printf("%f", intersect(savePlaneMatrix, modelMatrix));
	if (alreadyHit[3] == 0) {
		alreadyHit[3] = intersect(savePlaneMatrix, modelMatrix);
		RenderMesh(meshes["obstacle"], shaders["obstacle"], modelMatrix);
	}
	else if (alreadyHit[3] != 2) {
		numOfHearts--;
		alreadyHit[3] = 2;
		printf("s-au lovit");
	}
}


void Tema2::RenderSomeSmoke() {
	smoke = smoke - 0.05;
	for (int i = 0; i < 10; ++i) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-i * 0.25 + smoke, planeY + 0.25, 0);
		modelMatrix *= Transform3D::Scale(0.05, 0.05, 0.05);
		RenderMesh(meshes["obstacle"], shaders["FumDinCur"], modelMatrix);
	}
		if (smoke < -1.5) {
			smoke = -0.2;
		}
}

int Tema2::intersect(glm::mat4 a, glm::mat4 b) {
	return ((a[3][0] - 0.25) <= (b[3][0] + 0.25) && (a[3][0] + 0.25) >= (b[3][0] - 0.25)) &&
		((a[3][1] - 0.25) <= (b[3][1] + 0.25) && (a[3][1] + 0.25) >= (b[3][1] - 0.25)) &&
		((a[3][2] - 0.25) <= (b[3][2] + 0.25) && (a[3][2] + 0.25) >= (b[3][2] - 0.25));
}
