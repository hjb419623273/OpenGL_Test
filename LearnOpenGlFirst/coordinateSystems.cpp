#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <Shader.h>

/*
	
	֪ʶ��
	OpenGLϣ����ÿ�ζ�����ɫ�����к����ǿɼ������ж��㶼Ϊ��׼���豸����(Normalized Device Coordinate, NDC)��Ҳ����˵��ÿ�������x��y��z���궼Ӧ����-1.0��1.0֮�䣬����������귶Χ�Ķ��㶼�����ɼ�
	����ͨ�����Լ��趨һ������ķ�Χ��֮�����ڶ�����ɫ���н���Щ����任Ϊ��׼���豸���ꡣȻ����Щ��׼���豸���괫���դ��(Rasterizer)�������Ǳ任Ϊ��Ļ�ϵĶ�ά��������ء�

	������任Ϊ��׼���豸���꣬������ת��Ϊ��Ļ����Ĺ���ͨ���Ƿֲ����еģ�Ҳ������������ˮ�������ӡ�����ˮ���У�����Ķ���������ת��Ϊ��Ļ����֮ǰ���ᱻ�任���������ϵͳ(Coordinate System)
	1.�ֲ��ռ�(Local Space�����߳�Ϊ����ռ�(Object Space))
	2.����ռ�(World Space)
	3.�۲�ռ�(View Space�����߳�Ϊ�Ӿ��ռ�(Eye Space))
	4.�ü��ռ�(Clip Space)
	5.��Ļ�ռ�(Screen Space)

	Ϊ�˽������һ������ϵ�任����һ������ϵ��������Ҫ�õ������任��������Ҫ�ļ����ֱ���ģ��(Model)���۲�(View)��ͶӰ(Projection)��������
	1.�ֲ������Ƕ�������ھֲ�ԭ������꣬Ҳ��������ʼ�����ꡣ
	2.��һ���ǽ��ֲ�����任Ϊ����ռ����꣬����ռ������Ǵ���һ������Ŀռ䷶Χ�ġ���Щ��������������ȫ��ԭ�㣬���ǻ����������һ������������ԭ����аڷš�
	3.���������ǽ���������任Ϊ�۲�ռ����꣬ʹ��ÿ�����궼�Ǵ����������˵�۲��ߵĽǶȽ��й۲�ġ�
	4.���굽��۲�ռ�֮��������Ҫ����ͶӰ���ü����ꡣ�ü�����ᱻ������-1.0��1.0�ķ�Χ�ڣ����ж���Щ���㽫���������Ļ�ϡ�
	5.������ǽ��ü�����任Ϊ��Ļ���꣬���ǽ�ʹ��һ�������ӿڱ任(Viewport Transform)�Ĺ��̡��ӿڱ任��λ��-1.0��1.0��Χ������任����glViewport��������������귶Χ�ڡ����任���������꽫���͵���դ��������ת��ΪƬ�Ρ�

	�ֲ��ռ�
		�ֲ��ռ���ָ�������ڵ�����ռ䣬�������ʼ���ڵĵط�����������һ����ģ���������˵Blender���д�����һ�������塣�㴴�����������ԭ���п���λ��(0, 0, 0)���������п�������ڳ����д�����ȫ��ͬ��λ�á������п����㴴��������ģ�Ͷ���(0, 0, 0)Ϊ��ʼλ�ã���ע��Ȼ�����ǻ����ճ���������Ĳ�ͬλ�ã������ԣ����ģ�͵����ж��㶼���ھֲ��ռ��У�������������������˵���Ǿֲ��ġ�

	����ռ�
		����ռ��е�����������������ָ��������ڣ���Ϸ����������ꡣ�����ϣ���������ɢ�������ϰڷţ��ر��Ƿǳ���ʵ�����������������ϣ������任���Ŀռ䡣��������꽫��Ӿֲ��任������ռ䣻�ñ任����ģ�;���(Model Matrix)ʵ�ֵ�
	�۲�ռ�
		�۲�ռ侭�������ǳ�֮OpenGL�������(Camera)��������ʱҲ��Ϊ������ռ�(Camera Space)���Ӿ��ռ�(Eye Space)�����۲�ռ��ǽ�����ռ�����ת��Ϊ�û���Ұǰ��������������Ľ������˹۲�ռ���Ǵ���������ӽ����۲쵽�Ŀռ䡣����ͨ������һϵ�е�λ�ƺ���ת���������ɣ�ƽ��/��ת�����Ӷ�ʹ���ض��Ķ��󱻱任���������ǰ������Щ�����һ��ı任ͨ���洢��һ���۲����(View Matrix)�������������������任���۲�ռ�۲�ռ侭�������ǳ�֮OpenGL�������(Camera)��������ʱҲ��Ϊ������ռ�(Camera Space)���Ӿ��ռ�(Eye Space)�����۲�ռ��ǽ�����ռ�����ת��Ϊ�û���Ұǰ��������������Ľ������˹۲�ռ���Ǵ���������ӽ����۲쵽�Ŀռ䡣����ͨ������һϵ�е�λ�ƺ���ת���������ɣ�ƽ��/��ת�����Ӷ�ʹ���ض��Ķ��󱻱任���������ǰ������Щ�����һ��ı任ͨ���洢��һ���۲����(View Matrix)�������������������任���۲�ռ�
	�ü��ռ�
		��һ��������ɫ�����е����OpenGL�������е����궼������һ���ض��ķ�Χ�ڣ����κ��������Χ֮��ĵ㶼Ӧ�ñ��ü���(Clipped)�����ü���������ͻᱻ���ԣ�����ʣ�µ�����ͽ���Ϊ��Ļ�Ͽɼ���Ƭ�Ρ���Ҳ���ǲü��ռ�(Clip Space)���ֵ�������
		��Ϊ�����пɼ������궼ָ����-1.0��1.0�ķ�Χ�ڲ��Ǻ�ֱ�ۣ��������ǻ�ָ���Լ������꼯(Coordinate Set)�������任�ر�׼���豸����ϵ������OpenGL������������


	��ͶӰ���󴴽��Ĺ۲���(Viewing Box)����Ϊƽ��ͷ��(Frustum)��ÿ��������ƽ��ͷ�巶Χ�ڵ����궼�����ճ������û�����Ļ�ϡ����ض���Χ�ڵ�����ת������׼���豸����ϵ�Ĺ��̣������������ױ�ӳ�䵽2D�۲�ռ����꣩����֮ΪͶӰ(Projection)����Ϊʹ��ͶӰ�����ܽ�3D����ͶӰ(Project)��������ӳ�䵽2D�ı�׼���豸����ϵ�С�
	һ�����ж��㱻�任���ü��ռ䣬���յĲ�������͸�ӳ���(Perspective Division)����ִ�У���������������ǽ�λ��������x��y��z�����ֱ�������������w������͸�ӳ����ǽ�4D�ü��ռ�����任Ϊ3D��׼���豸����Ĺ��̡���һ������ÿһ��������ɫ�����е�����Զ�ִ�С�
	����һ�׶�֮�����յ����꽫�ᱻӳ�䵽��Ļ�ռ��У�ʹ��glViewport�е��趨���������任��Ƭ�Ρ�
	���۲�����任Ϊ�ü������ͶӰ�������Ϊ���ֲ�ͬ����ʽ��ÿ����ʽ�������˲�ͬ��ƽ��ͷ�塣���ǿ���ѡ�񴴽�һ������ͶӰ����(Orthographic Projection Matrix)��һ��͸��ͶӰ����(Perspective Projection Matrix)��

*/


void framebuffer_size_callback5(GLFWwindow*window, int width, int height);
void processInput5(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main5()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback5);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader ourShader("D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/coordinateSystem.vs", "D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/corrdinateSystem.fs");
	
	float vertices[] = {
		// positions          // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// load and create a texture 
	// -------------------------
	unsigned int texture1, texture2;
	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load("res/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("res/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use();
	ourShader.setInt("texture1",0);
	ourShader.setInt("texture2",1);

	while (!glfwWindowShouldClose(window))
	{
		processInput5(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,texture2);

		ourShader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model , glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0));
		view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		unsigned int modelLoc = glGetUniformLocation(ourShader.ID,"model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE,&view[0][0]);
		ourShader.setMat4("projection", projection);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);
	glfwTerminate();

	return 0;
}



void processInput5(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window,true);
	}
}

void framebuffer_size_callback5(GLFWwindow*window, int width, int height)
{
	glViewport(0,0,width,height);
}