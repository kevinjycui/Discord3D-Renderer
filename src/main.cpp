#include "../include/main.h"
#include "../include/vertices.h"
#include "../include/shader.h"
#include "../include/texture.h"

#include "../include/main_socket.h"


#define FRAMES_PER_REQ 20

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  


GLFWwindow* window;
Shader shader;

GLsizei nrChannels = 3;
GLsizei stride = nrChannels * WIDTH + ((nrChannels * WIDTH % 4) ? (4 - nrChannels * WIDTH % 4) : 0);
GLsizei bufferSize = stride * HEIGHT;
std::vector<char> buffer(bufferSize);

int img_index;
float _clock;
char * pixelData;
char pixels[2880000];


int gl_Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", NULL, NULL);
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

	shader.init("shaders/shader.vs", "shaders/shader.fs");
	GenerateTexture();

	glEnable(GL_DEPTH_TEST);
	img_index = 0;
	_clock = 0.0f;

	return 0;
}

int gl_Close()
{
	glfwTerminate();
	return 0;
}

int gl_Loop()
{
	if (img_index >= FRAMES_PER_REQ) {
		img_index = 0;
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	LoadModel();

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");

	glm::mat4 trans = glm::mat4(1.0f);
	// trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  
	trans = glm::rotate(trans, /*(float) glfwGetTime()*/ _clock * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	for(unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i; 
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	glfwSwapBuffers(window);
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glReadBuffer(GL_FRONT);	
	glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
	glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	
	// std::ostringstream ss;
	// ss << "frames/" << img_index << ".png";
	// std::string path = ss.str();

	// stbi_flip_vertically_on_write(true);
	// stbi_write_png(path.c_str(), WIDTH, HEIGHT, nrChannels, buffer.data(), stride);
	/* Saving PNGs to drive not best practice, may be harmful to drive in long run (though negligible for only a few files)
		* TODO: Change this part to HTTP server, set pixel data as returnable byte data
		*/

	img_index++;
	_clock += 0.1;

	return 0;
}

// int main()
// {
// 	int rc;
// 	rc = gl_Init();
// 	if (rc != 0) return rc;

// 	while(!glfwWindowShouldClose(window)) {
// 		gl_Loop();
// 	}

//     gl_Close();

// 	return 0;
// }

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
