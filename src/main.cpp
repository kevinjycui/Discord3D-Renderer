#include "../include/main.h"
#include "../include/vertices.h"
#include "../include/shader.h"
#include "../include/texture.h"

#define WIDTH 800
#define HEIGHT 600


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
  
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

	InitVertices();

	Shader shader("shaders/shader.vs", "shaders/shader.fs");
	GenerateTexture();

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		LoadModel();

		int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projectionLoc = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  
		trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		
		shader.use();
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLsizei nrChannels = 3;
		GLsizei stride = nrChannels * WIDTH;
		stride += (stride % 4) ? (4 - stride % 4) : 0;
		GLsizei bufferSize = stride * HEIGHT;
		std::vector<char> buffer(bufferSize);
		glPixelStorei(GL_PACK_ALIGNMENT, 4);
		glReadBuffer(GL_FRONT);	
		glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
		stbi_flip_vertically_on_write(true);
		stbi_write_png("sample.png", WIDTH, HEIGHT, nrChannels, buffer.data(), stride);
	}

    
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
