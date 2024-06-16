#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"
/*
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	glfwInit();//��ʼ��GLFW
	//��һ��������ѡ������ƣ��ڶ���������һ��int��������ѡ���ֵ
	//3.3�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//����ģʽCore-profile 
	//��ζ������ֻ��ʹ��OpenGL���ܵ�һ���Ӽ���û�������Ѳ�����Ҫ������������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// �ޱ߿�
	glfwWindowHint(GLFW_DISCONNECTED, GL_FALSE);
	// ͸��
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// �������ڶ���
	// ���������ߣ����ڱ��⣬
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ShuoLearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //֪ͨGLFW�����ڵ�����������Ϊ��ǰ�̵߳���������

	// ע��ص�������ÿ�δ��ڴ�С������ʱ����ע��ĺ���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD����������OpenGL�ĺ���ָ��
	// �����ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ��ѯ������������
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	Shader ourShader("./shader_exercise1.vs", "./shader_exercise1.fs");

	// ��������
	float vertices[] = {
		// λ��              // ��ɫ
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};

	// �����������
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// ���㻺�����
	unsigned int VBO;
	glGenBuffers(1, &VBO); //����1 number of buffer object names to be generated

	glBindVertexArray(VAO);
	// ���´����Ļ���󶨵�GL_ARRAY_BUFFER��
	// VBO�Ļ���������GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ��֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
	// ���ĸ�������ϣ���Կ���ι������������
	// GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
	// GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
	// GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 1. ��������index��ǰ���ڶ�����ɫ����ʹ��layout(location = 0)������position�������Ե�λ��ֵ(Location)�������԰Ѷ������Ե�λ��ֵ����Ϊ0����Ϊ����ϣ�������ݴ��ݵ���һ�����������У��������ﴫ��0 
	// 2. �����������Դ�С��vec3��3.�������� 4.�Ƿ��׼�� 
	// 5.����Stride �������Ķ���������֮��ļ�� ��������Ϊ0����OpenGL�������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã�
	// 6.������void*��������Ҫ����ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)������λ������������Ŀ�ͷ������������0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// glVertexAttribPointer��������Կ��Խ��
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// �߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ��Ⱦѭ��
	// ----------------------------------------------------------------------------------------------------------------------------------
	// glfwWindowShouldClose������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
	// ����ǵĻ����ú�������true����Ⱦѭ����ֹͣ����
	while (!glfwWindowShouldClose(window))
	{
		// ��������
		processInput(window);

		// render
		//�����Ļ������ɫ
		glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		// ÿ���µ���Ⱦ������ʼʱ����������ῴ����һ�ε�������Ⱦ���
		// ����λѡ�GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT �� GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

		// ����shader program
		ourShader.use();

		glBindVertexArray(VAO);

		// ����1�Ǵ�����Ƶ�OpenGLͼԪ�����ͣ�����2ָ���˶����������ʼ����������3ָ��������ƶ��ٸ�����
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glBindVertexArray(0); // no need to unbind it every time 

		//������ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩
		glfwSwapBuffers(window);
		//�����û�д���ʲô�¼�������������롢����ƶ��ȣ�
		//���´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ�����
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glDeleteProgram(ourShader.ID);

	// �ͷ�ɾ��֮ǰ���������GLFW resources.
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	// �Ƿ�����ESC���� û���򷵻�GLFW_RELEASE
	// ������£�����true���ر�GLFW������´�ѭ��while�������ʧ�ܣ�����ر�
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// �ص�������ÿ�δ��ڴ�С������ʱ����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ǰ�����������������½�λ��
	// ��������������ȣ��߶�
	glViewport(0, 0, width, height);
}*/