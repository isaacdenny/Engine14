#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VBO.h"
#include"VAO.h"
#include"EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat vertices[] = {
	   -0.5f, -0.5f * float(sqrt(3)) / 3,		0.0f,    0.8f, 0.3f, 0.02f,
		0.5f, -0.5f * float(sqrt(3)) / 3,		0.0f,    0.8f, 0.3f, 0.02f,
		0.0f,  0.5f * float(sqrt(3)) * 2 / 3,  0.0f,    1.0f, 0.6f, 0.32f,
	   -0.25f, 0.5f * float(sqrt(3)) / 6,		0.0f,    0.9f, 0.45f, 0.17f,
		0.25f, 0.5f * float(sqrt(3)) / 6,		0.0f,    0.9f, 0.45f, 0.17f,
		0.0f, -0.5f * float(sqrt(3)) / 3,		0.0f,    0.8f, 0.3f, 0.02f
};

GLuint indices[] = {
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};

int main() 
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(width, height, "Engine 14", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete(); 

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}