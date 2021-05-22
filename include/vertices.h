#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


extern unsigned int VAO;
extern unsigned int EBO;

extern glm::mat4 model;
extern glm::mat4 view;
extern glm::mat4 projection;

extern glm::vec3 cubePositions[];

void LoadModel();
void InitVertices();
