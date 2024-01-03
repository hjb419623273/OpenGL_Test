/*
	֡����
	https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/05%20Framebuffers/
	���ã���Ⱦ��ĳ�������ͬ��֡�����ܹ��������ڳ����м������ƾ��ӵĶ��������������ܿ�ĺ��ڴ���Ч��
	
	��ɫ���� ��Ȼ��� ģ�建�� ��Щ��������������֡����
	glGenFramebuffers�ĺ���������һ��֡�������(Framebuffer Object, FBO)

	������֡���� ��Ҫ����һ������
	1��������һ������ 
	2������һ����ɫ����
	3���и�����������������
	4ÿ�����嶼Ӧ������ͬ��������
	��������ҪΪ֡���崴��һЩ���������������ӵ�֡�����ϡ�
	�������ǵ�֡���岻��Ĭ��֡���壬��Ⱦָ�����Դ��ڵ��Ӿ�������κ�Ӱ�졣�������ԭ����Ⱦ��һ����ͬ��֡���屻����������Ⱦ(Off-screen Renderin)

������
	����һ�������ӵ�֡�����ʱ�� ���е���Ⱦָ�����д�뵽��������С���������һ����ͨ����ɫ/��Ȼ���ģ�建��һ����ʹ��������ŵ��ǣ�����
	��Ⱦ�����Ľ�����ᱻ������һ������ͼ���У�����֮���������ɫ���з���ʹ������
	���ǽ�ά������Ϊ����Ļ��С�������ⲻ�Ǳ���ģ����������Ǹ������data����������NULL����������������ǽ����������ڴ��û�����������������������������Ⱦ��֡����֮������
	�С�
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	������뽫�����Ļ��Ⱦ��һ����С�����������ϣ�����Ҫ������Ⱦ�����֡����֮ǰ���ٴε���glViewport��ʹ���������ά����Ϊ����������ֻ��һС���ֵ��������Ļ�ᱻ��Ⱦ����������ϡ�
	���������Ѿ�������һ�������ˣ�Ҫ�������һ���¾��ǽ������ӵ�֡�������ˣ�
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	
	Ҳ���Խ���Ȼ����ģ�建�帽��Ϊһ�����������������ÿ32λ��ֵ������24λ�������Ϣ��8λ��ģ����Ϣ��Ҫ����Ⱥ�ģ�建�帽��Ϊһ������Ļ�������ʹ��GL_DEPTH_STENCIL_ATTACHMENT���ͣ�����������ĸ�ʽ�����������ϲ�����Ⱥ�ģ��ֵ����һ����Ⱥ�ģ�建�帽��Ϊһ������֡��������ӿ����������ҵ���

	glTexImage2D(
	GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0,
	GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
	);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

��Ⱦ������󸽼�
	��Ⱦ������� renderbuffer object ��������֮�����뵽opengl�У���Ϊһ�����õ�֡���帽�����͵ģ�����
	�ڹ�ȥ������Ψһ���õĸ�����������ͼ��һ������Ⱦ���������һ�������Ļ��壬��һϵ�е��ֽڡ����������صȡ���Ⱦ������󸽼ӵĺô��ǣ�
	���Ὣ���ݴ���ΪOpenGLԭ������Ⱦ��ʽ������Ϊ������Ⱦ��֡�����Ż����ġ�

	��Ⱦ�������ֱ�ӽ����е���Ⱦ���ݴ��浽���Ļ����У��������κ���������ʽ��ת����������Ϊһ������Ŀ�д������ʡ�
	��Ϊ���������Ѿ���ԭ���ĸ�ʽ�ˣ���д����߸����������ݵ�����������ʱ�Ƿǳ���ġ����ԣ��������������Ĳ�����ʹ����Ⱦ�������ʱ��ǳ��졣
	������ÿ����Ⱦ�������ʹ�õ�glfwSwapBuffers��Ҳ����ͨ����Ⱦ�������ʵ�֣�ֻ��Ҫд��һ����Ⱦ����ͼ�񣬲�����󽻻�������һ����Ⱦ����Ϳ����ˡ���Ⱦ�����������ֲ����ǳ�������
	
	������Ⱦ�������ͨ������ֻд�ģ����ǻᾭ��������Ⱥ�ģ�帽������Ϊ�󲿷�ʱ�����Ƕ�����Ҫ����Ⱥ�ģ�建���ж�ȡֵ��ֻ������Ⱥ�ģ����ԡ�������Ҫ��Ⱥ�ģ��ֵ���ڲ��ԣ�������Ҫ�����ǽ��в�����������Ⱦ�������ǳ��ʺ����ǡ������ǲ���Ҫ����Щ�����в�����ʱ��ͨ������ѡ����Ⱦ���������Ϊ������Ż�һ�㡣
	

*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shader.h>
#include <camera.h>
#include <model.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FrameBuffer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW windows" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	Shader shader("D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/framebuffers.vs", "D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/framebuffers.fs");
	Shader screenShader("D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/framebuffers_screen.vs", "D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/framebuffers_screen.fs");

	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	float planeVertices[] = {
		// positions          // texture Coords 
		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							 // positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	// plane VAO
	unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// screen quad VAO
	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	unsigned int cubeTexture = loadTexture("D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/container.jpg");
	unsigned int floorTexture = loadTexture("D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/metal.png");
	shader.use();
	shader.setInt("texture1", 0);

	screenShader.use();
	screenShader.setInt("screenTexture", 0);

	//framebuffer configuration
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//create a color attachment texture
	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//���������Ѿ�������һ�������ˣ�Ҫ�������һ���¾��ǽ������ӵ�֡�������ˣ�
	//target��֡�����Ŀ�꣨���ơ���ȡ�������߽��У�
	//attachment��������Ҫ���ӵĸ������͡���ǰ�������ڸ���һ����ɫ������ע������0��ζ�����ǿ��Ը��Ӷ����ɫ���������ǽ���֮��Ľ̳����ᵽ��
	//textarget����ϣ�����ӵ���������
	//texture��Ҫ���ӵ�������
	//level���༶��Զ����ļ������ǽ�������Ϊ0��
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, textureColorbuffer, 0);

	//����һ����Ⱦ�������
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	//����Ⱦ������� ��֮�����е���Ⱦ�������Ӱ�쵱ǰrbo
	glBindRenderbuffer(GL_RENDERBUFFER,rbo);
	//����һ����Ⱥ�ģ����Ⱦ�������
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
	//���������Ⱦ�������
	//��Ⱦ���������Ϊ���֡��������ṩһЩ�Ż�����֪��ʲôʱ��ʹ����Ⱦ�������ʲôʱ��ʹ�������Ǻ���Ҫ�ġ�
	//ͨ���Ĺ����ǣ�����㲻��Ҫ��һ�������в������ݣ���ô���������ʹ����Ⱦ�������������ǵ�ѡ��
	//�������Ҫ�ӻ����в�����ɫ�����ֵ�����ݣ���ô��Ӧ��ѡ�������������ܷ�������������ǳ����Ӱ��ġ�
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "ERROR::FRAMEBUFER::Framebuffer is not complete��" << endl;
	}

	//�������Լ��ִ��֮ǰ��������Ҫ��֡���帽��һ��������������һ���ڴ�λ�ã����ܹ���Ϊ֡�����һ�����壬���Խ�������Ϊһ��ͼ��
	//������һ��������ʱ������������ѡ��������Ⱦ�������(Renderbuffer Object)
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);


		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		model = glm::translate(model, glm::vec3(-1, 0, -1));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2, 0, 0));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(planeVAO);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		shader.setMat4("model", glm::mat4(1));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glDisable(GL_DEPTH_TEST);
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//����ȫ������
		screenShader.use();
		glBindVertexArray(quadVAO);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &planeVAO);
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &planeVBO);
	glDeleteBuffers(1, &quadVBO);
	glDeleteRenderbuffers(1, &rbo);
	glDeleteFramebuffers(1, &framebuffer);

	glfwTerminate();
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
