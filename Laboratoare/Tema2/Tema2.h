#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera.h"

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);


private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
	void RenderSea();
	void RenderBackSea();
	void RenderPlane();
	void RenderHeart();
	void RenderHeartFirstCamera();
	void RenderCombustibleBox();
	void RenderCombustibleBoxFirstCamera();
	bool GameOver();
	void RenderClouds();
	void RenderCombustibleBonus();
	void RenderObstacle();
	void RenderPlaneFalling();
	void RenderSomeSmoke();
	int intersect(glm::mat4 a, glm::mat4 b);

protected:
	Laborator::CameraTema2* camera;
	glm::mat4 modelMatrix;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
	float fov;
	float planeX, planeY;
	int numOfHearts;
	float remainingCombustible;
	float boxSize;
	int rotationOfElice;
	float rotationOfPlane;
	float rotationOfSea;
	float offsetElice;
	float movementOfClouds;
	float fallingElice;
	float rotationOfPlaneFalling;
	float offsetEliceX;
	float positionCloudsX[10];
	float positionCloudsY[10];
	float rotationsCloudsOX[10];
	float rotationsCloudsOY[10];
	float rotationsCloudsOZ[10];
	float smoke;
	glm::vec4 minPlane;
	glm::vec4 maxPlane;
	glm::vec4 obstacole1;
	glm::vec4 obstacole2;
	glm::vec4 obstacole3;
	glm::mat4 savePlaneMatrix;
	float harder;
	int alreadyHit[10];
	float sinDeBonus = 90;
	float xDeBonus = 2;
	float varInc = 90;
	int fP = 0;
	glm::mat4 modelMatrixAvion;
};

