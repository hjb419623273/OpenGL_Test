#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <Shader.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//��������任���ü�����
//Vclip = Mprojection * Mview * Mmodel * Vlocal   ���������Ķ�����˷� 


//���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����������ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵���
//�����ڱ���һ����ʾ��ʱ��framebuffer_size_callbackҲ�ᱻ���á���������Ĥ(Retina)��ʾ����width��height�������Ա�ԭ����ֵ����һ�㡣
void framebuffer_size_callback3(GLFWwindow* window, int width, int height);
void processInput3(GLFWwindow *windows);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// stores how much we're seeing of either texture
float mixValue = 0.2f;
int main3()
{
	//glfw initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);		//���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);		//�ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);		//��ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)����ȷ����GLFW������Ҫʹ�ú���ģʽ��ζ������ֻ��ʹ��OpenGL���ܵ�һ���Ӽ���û�������Ѳ�����Ҫ�����������ԣ�
#ifdef __APPLE__														//���ʹ�õ���Mac OS Xϵͳ���㻹��Ҫ���������д��뵽��ĳ�ʼ����������Щ���ò���������
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif
	//glfw windows creation
	//---------------------
	//glfwCreateWindow������Ҫ���ڵĿ�͸���Ϊ����ǰ����������������������ʾ������ڵ����ƣ����⣩����������ʹ��"LearnOpenGL"����Ȼ��Ҳ����ʹ����ϲ�������ơ������������������ʱ���ԡ�����������᷵��һ��GLFWwindow�������ǻ���������GLFW������ʹ�õ��������괰�����ǾͿ���֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳����������ˡ�
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);			//�������ڶ���
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback3);

	//glad load all OpenGL function pointers
	//GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// build and compile our shader zporgram
	Shader ourShader("D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/texture.vs", "D:/LearnOpenGl/LearnProject/LearnOpenGlFirst/LearnOpenGlFirst/res/texture.fs");
	//set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		//position           // colors            // texture corrds 
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0,1,3,// first triangle 
		1,2,3 // second triangle
	};

	//������ɫ��(Vertex Shader) ͼ����Ⱦ���ߵĵ�һ�������Ƕ�����ɫ��(Vertex Shader)������һ�������Ķ�����Ϊ���롣������ɫ����Ҫ��Ŀ���ǰ�3D����תΪ��һ��3D���꣨�������ͣ���ͬʱ������ɫ���������ǶԶ������Խ���һЩ��������
	//ͼԪװ��(Primitive Assembly) �׶ν�������ɫ����������ж�����Ϊ���루�����GL_POINTS����ô����һ�����㣩�������еĵ�װ���ָ��ͼԪ����״
	//������ɫ��(Geometry Shader)  ͼԪװ��׶ε�����ᴫ�ݸ�������ɫ��(Geometry Shader)��������ɫ����ͼԪ��ʽ��һϵ�ж���ļ�����Ϊ���룬������ͨ�������¶��㹹����µģ����������ģ�ͼԪ������������״
	//��դ���׶�(Rasterization Stage)  ������ɫ��������ᱻ�����դ���׶�(Rasterization Stage)�����������ͼԪӳ��Ϊ������Ļ����Ӧ�����أ����ɹ�Ƭ����ɫ��(Fragment Shader)ʹ�õ�Ƭ��(Fragment)����Ƭ����ɫ������֮ǰ��ִ�в���(Clipping)�����лᶪ�����������ͼ������������أ���������ִ��Ч�ʡ�
	//Ƭ����ɫ��  ��ҪĿ���Ǽ���һ�����ص�������ɫ����Ҳ������OpenGL�߼�Ч�������ĵط���ͨ����Ƭ����ɫ������3D���������ݣ�������ա���Ӱ�������ɫ�ȵȣ�����Щ���ݿ��Ա����������������ص���ɫ��
	//Alpha���Ժͻ��(Blending)�׶� ���Ƭ�εĶ�Ӧ����ȣ���ģ��(Stencil)��ֵ������ὲ�������������ж�������������������ǰ�滹�Ǻ��棬�����Ƿ�Ӧ�ö���������׶�Ҳ����alphaֵ��alphaֵ������һ�������͸���ȣ�����������л��(Blend)�����ԣ���ʹ��Ƭ����ɫ���м��������һ�������������ɫ������Ⱦ��������ε�ʱ������������ɫҲ������ȫ��ͬ��

	//�����������Vertex Array Object��VAO
	//���㻺�����Vertex Buffer Object��VBO
	//Ԫ�ػ������Element Buffer Object��EBO �� ����������� Index Buffer Object��IBO

	//���ǻ������Ϊ���뷢�͸�ͼ����Ⱦ���ߵĵ�һ������׶Σ�������ɫ����������GPU�ϴ����ڴ����ڴ������ǵĶ������ݣ���Ҫ����OpenGL��ν�����Щ�ڴ棬����ָ������η��͸��Կ���������ɫ�����Żᴦ���������ڴ���ָ�������Ķ���
	//���㻺�����(Vertex Buffer Objects, VBO)��������ڴ棬������GPU�ڴ棨ͨ������Ϊ�Դ棩�д���������㡣ʹ����Щ�������ĺô������ǿ���һ���Եķ���һ�������ݵ��Կ��ϣ�������ÿ�����㷢��һ�Ρ���CPU�����ݷ��͵��Կ���Խ���������ֻҪ�������Ƕ�Ҫ���Ծ���һ���Է��;����ܶ�����ݡ������ݷ������Կ����ڴ��к󣬶�����ɫ���������������ʶ��㣬���Ǹ��ǳ���Ĺ��̡�
	
	//EBO��һ��������������һ�����㻺��������һ�������洢 OpenGL ��������Ҫ������Щ�����������������ν����������(Indexed Drawing)������������Ľ������
	unsigned int VBO, VAO, EBO;					//�����������(Vertex Array Object, VAO)�����񶥵㻺������������󶨣��κ����Ķ������Ե��ö��ᴢ�������VAO�С������ĺô����ǣ������ö�������ָ��ʱ����ֻ��Ҫ����Щ����ִ��һ�Σ�֮���ٻ��������ʱ��ֻ��Ҫ����Ӧ��VAO�����ˡ���ʹ�ڲ�ͬ�������ݺ���������֮���л���÷ǳ��򵥣�ֻ��Ҫ�󶨲�ͬ��VAO�����ˡ��ո����õ�����״̬�����洢��VAO��
	glGenVertexArrays(1, &VAO);					
	glGenBuffers(1,&VBO);						//���㻺�������������OpenGL�̳��е�һ�����ֵ�OpenGL���󡣾���OpenGL�е���������һ�������������һ����һ�޶���ID���������ǿ���ʹ��glGenBuffers������һ������ID����һ��VBO����
	glGenBuffers(1,&EBO);						//Ԫ�ػ������

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);			//OpenGL�кܶ໺��������ͣ����㻺�����Ļ���������GL_ARRAY_BUFFER��OpenGL��������ͬʱ�󶨶�����壬ֻҪ�����ǲ�ͬ�Ļ������͡����ǿ���ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ���ϣ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);	//����ʹ�õ��κΣ���GL_ARRAY_BUFFERĿ���ϵģ�������ö����������õ�ǰ�󶨵Ļ���(VBO)��Ȼ�����ǿ��Ե���glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ���

	//glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ��������ĵ�һ��������Ŀ�껺������ͣ����㻺�����ǰ�󶨵�GL_ARRAY_BUFFERĿ���ϡ��ڶ�������ָ���������ݵĴ�С(���ֽ�Ϊ��λ)����һ���򵥵�sizeof������������ݴ�С���С�����������������ϣ�����͵�ʵ�����ݡ�

	//	���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�����������ʽ��

	//	GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
	//	GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
	//	GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	//�����ε�λ�����ݲ���ı䣬ÿ����Ⱦ����ʱ������ԭ������������ʹ�����������GL_STATIC_DRAW�����������˵һ�������е����ݽ�Ƶ�����ı䣬��ôʹ�õ����;���GL_DYNAMIC_DRAW��GL_STREAM_DRAW����������ȷ���Կ������ݷ����ܹ�����д����ڴ沿�֡�
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

	// position attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	//color attribute 
	glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void *)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture coord attribute 
	glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 8*sizeof(float),(void *)(6* sizeof(float)));
	glEnableVertexAttribArray(2);

	//load and create a texture
	//glGenTextures����������Ҫ�������������������Ȼ������Ǵ����ڵڶ���������unsigned int�����У����ǵ�������ֻ�ǵ�����һ��unsigned int����������������һ����������Ҫ��������֮���κε�����ָ��������õ�ǰ�󶨵�����glGenTextures����������Ҫ�������������������Ȼ������Ǵ����ڵڶ���������unsigned int�����У����ǵ�������ֻ�ǵ�����һ��unsigned int����������������һ����������Ҫ��������֮���κε�����ָ��������õ�ǰ�󶨵�����
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);   // all upcoming GL_TETURE_2D operations now have effect on this texture object
	//set the texture wrapping parameters 
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	//��������ķ�Χͨ���Ǵ�(0, 0)��(1, 1)����������ǰ��������������ڷ�Χ֮��ᷢ��ʲô��OpenGLĬ�ϵ���Ϊ���ظ��������ͼ�����ǻ����Ϻ��Ը�������������������֣�����OpenGL�ṩ�˸����ѡ��
	//���Ʒ�ʽ	����
	//	GL_REPEAT	�������Ĭ����Ϊ���ظ�����ͼ��
	//	GL_MIRRORED_REPEAT	��GL_REPEATһ������ÿ���ظ�ͼƬ�Ǿ�����õġ�
	//	GL_CLAMP_TO_EDGE	��������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч����
	//	GL_CLAMP_TO_BORDER	����������Ϊ�û�ָ���ı�Ե��ɫ��
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//set texture  filtering parameters
	// �������겻�����ڷֱ���(Resolution)�������������⸡��ֵ������OpenGL��Ҫ֪����������������(Texture Pixel��Ҳ��Texel����ע1)ӳ�䵽�������ꡣ������һ���ܴ�����嵫������ķֱ��ʺܵ͵�ʱ����ͱ�ú���Ҫ�ˡ�������Ѿ��µ��ˣ�OpenGLҲ�ж����������(Texture Filtering)��ѡ���������кܶ��ѡ�������������ֻ��������Ҫ�����֣�GL_NEAREST��GL_LINEAR��
	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load image create texture and generate mipmaps 
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository sp we can find files on any IDE/platform; replace it with own iamge path
	unsigned char *data = stbi_load("res/container.jpg", &width, &height, &nrChannels,0);
	if (data)
	{
		//�������ͨ��glTexImage2D�����ɣ�
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//texture2 
	//
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	data = stbi_load("res/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//tell opengl for each smpler to which texture unit it belongs to 
	ourShader.use(); // dont forget to activate/use the shader before settiing uniforms
	glUniform1i(glGetUniformLocation(ourShader.ID,"texture1"),0);
	ourShader.setInt("texture2", 1);
	// render loop 
	//glfwWindowShouldClose����������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ⱦѭ��������ˣ�֮��Ϊ���ǾͿ��Թر�Ӧ�ó����ˡ�
	while (!glfwWindowShouldClose(window))
	{
		//input 
		processInput3(window);
		//render 
		//�������Ļ���õ���ɫ
		glClearColor(0.2f, 0.3f, 0.3f , 1.0f);
		//��ÿ���µ���Ⱦ������ʼ��ʱ����������ϣ�������������������ܿ�����һ�ε�������Ⱦ����������������Ҫ��Ч������ͨ���ⲻ�ǣ������ǿ���ͨ������glClear�����������Ļ����ɫ���壬������һ������λ(Buffer Bit)��ָ��Ҫ��յĻ��壬���ܵĻ���λ��GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT��������������ֻ������ɫֵ����������ֻ�����ɫ���塣
		glClear(GL_COLOR_BUFFER_BIT);
		//bind texture 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.setFloat("mixValue", mixValue);

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.5, -0.5, 0.0f));
		transform = glm::rotate(transform,(float)glfwGetTime(), glm::vec3(0,0,1.0));

		//render container 
		ourShader.use();

		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");		//�ڰ�λ����������gl_Position֮ǰ�����������һ��uniform�����ҽ�����任������ˡ�
		glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(transform));				//

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw swap buffers and poll IO events 
		//glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		glfwSwapBuffers(window);
		//glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
		glfwPollEvents();
	}

	//option de-allocate all resources once they've outlived their purpose 
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//����Ⱦѭ��������������Ҫ��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ
	glfwTerminate();
	return 0;
}

// process all input query GLFW whether relevant keys are pressed/re;eased this frame and react accordingly
void processInput3(GLFWwindow *window)
{
	//�������Ǽ���û��Ƿ����˷��ؼ�(Esc)
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}

//glfw whenever then window size changed this callback function executes 
void framebuffer_size_callback3(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	//�����ǿ�ʼ��Ⱦ֮ǰ����һ����Ҫ������Ҫ�������Ǳ������OpenGL��Ⱦ���ڵĳߴ��С�����ӿ�(Viewport)������OpenGL��ֻ��֪���������ݴ��ڴ�С��ʾ���ݺ����ꡣ���ǿ���ͨ������glViewport���������ô��ڵ�ά��
	glViewport(0, 0, width, height);
}

