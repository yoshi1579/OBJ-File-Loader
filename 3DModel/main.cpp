#include "Window.h"
#include "Shader2.h"
#include "Texture2.h"
#include <GL\glew.h>
#include "Mesh2.h"
#include "transform.h"
#include "camera.h"
#include <string>

#define WIDTH 800
#define HEIGHT 600

using namespace std;


int main(int argc, char** argv)
{
	Window window(800, 800, "First Window");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0),glm::vec2(0,0)),
							Vertex(glm::vec3(0, 0.5, 0),glm::vec2(0.5,1.0)),
							Vertex(glm::vec3(0.5, -0.5, 0),glm::vec2(1.0,0))
	};

	unsigned int indices[] = { 0, 1, 2 };

	//Mesh Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	
	Mesh mesh2("./res/monkey3.obj");
	Shader shader("./res/firstShader");
	Texture texture("./res/bricks.jpg");
	Camera camera(glm::vec3(0, 0, -8), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while (!window.GetbClosed())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		transform.GetPos().x = sinf(counter * 0.1);
		transform.GetPos().z = sinf(counter * 0.07);
		transform.GetRot().z = counter * 0.1;
		transform.GetRot().y = counter * 0.1;

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh2.Draw();

		window.SwapBuffer();
		counter += 0.01f;
		
	}
	

	window.~Window();

	return 0;
}