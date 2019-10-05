#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Render.h"

#include "Texture.h"
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Glew init failed" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	/* Loop until the user closes the window */

	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	/*float positions[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f, 
		 0.5f,  0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f
	};*/
	unsigned int index[] = {
		0,1,2,
		2,3,0
	};

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	VertexArray va;
	VertexBuffer vbo(positions, sizeof(positions));
	IndexBuffer ibo(index, sizeof(index) / sizeof(unsigned int));
	VertexBufferLayout layout;
	Renderer renderer;

	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vbo, layout);
	
	Shader shader("res/shaders/Basic.shader");
	shader.Bind();

	Texture texture("res/textures/texture.png");
	texture.Bind();

	shader.SetUniform4f("u_Color", 0.5f, 0.7f, 0.1f, 1.0f);
	shader.SetUniform1i("u_Texture", 0);

	vbo.Unbind();
	ibo.Unbind();
	va.Unbind();
	shader.Unbind();

	float r = 0.0f, g = 0.54f, b = 0.79f, delta = 0.01f;

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		shader.Bind();
		//shader.SetUniform4f("u_Color", r, g, b, 1.0);
		renderer.Draw(va, ibo, shader);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		if (r > 1.0f || r < 0.0f)
		{
			delta *= -1;
		}
		r += delta;
		g += delta;
		b += delta;

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}