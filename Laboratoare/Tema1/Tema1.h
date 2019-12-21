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

#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	void renderBird();
	void renderPipes();
	bool Intersect();

protected:
	GLenum cullFace;
	GLenum polygonMode;
	glm::mat4 modelMatrix;
	float translateX, translateY, translateZ;
	float scaleX, scaleY, scaleZ;
	float angularStepOX, angularStepOY, angularStepOZ;

	float gravity;
	float velocity;
	float angle;

	int indexOfPipes[10];
	int randHeight[10];
	float randNum;
	int scor = 0;
	int counter;
};
