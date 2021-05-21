#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include<ctime>

// #define _USE_MATH_DEFINES
// #include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// #define GLM_FORCE_RADIANS
// #include <glm/glm.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <glm/gtx/transform.hpp>
// #include <glm/gtx/quaternion.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image_write.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  


// struct float2
// {
// 	float2(float _x = 0.0f, float _y = 0.0f): x(_x), y(_y) {}

// 	float x;
// 	float y;
// };

// struct float3
// {
// 	float3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f): x(_x), y(_y), z(_z) {}

// 	float x;
// 	float y;
// 	float z;
// };

