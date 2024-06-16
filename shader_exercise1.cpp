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
	glfwInit();//初始化GLFW
	//第一个参数是选项的名称，第二个参数是一个int用来设置选项的值
	//3.3版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//核心模式Core-profile 
	//意味着我们只能使用OpenGL功能的一个子集（没有我们已不再需要的向后兼容特性
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// 无边框
	glfwWindowHint(GLFW_DISCONNECTED, GL_FALSE);
	// 透明
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// 创建窗口对象
	// 参数：宽，高，窗口标题，
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ShuoLearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //通知GLFW将窗口的上下文设置为当前线程的主上下文

	// 注册回调函数，每次窗口大小被调整时调用注册的函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD是用来管理OpenGL的函数指针
	// 所以在调用任何OpenGL的函数之前我们需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 查询顶点属性上限
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	Shader ourShader("./shader_exercise1.vs", "./shader_exercise1.fs");

	// 顶点数据
	float vertices[] = {
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};

	// 顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// 顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO); //参数1 number of buffer object names to be generated

	glBindVertexArray(VAO);
	// 把新创建的缓冲绑定到GL_ARRAY_BUFFER上
	// VBO的缓冲类型是GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 把之前定义的顶点数据复制到缓冲的内存中
	// 第四个参数：希望显卡如何管理给定的数据
	// GL_STATIC_DRAW ：数据不会或几乎不会改变。
	// GL_DYNAMIC_DRAW：数据会被改变很多。
	// GL_STREAM_DRAW ：数据每次绘制时都会改变。
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 1. 顶点属性index，前面在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)，它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里传入0 
	// 2. 单个顶点属性大小（vec3）3.数据类型 4.是否标准化 
	// 5.步长Stride 在连续的顶点属性组之间的间隔 可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）
	// 6.类型是void*，所以需要进行强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// glVertexAttribPointer绑好了所以可以解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 渲染循环
	// ----------------------------------------------------------------------------------------------------------------------------------
	// glfwWindowShouldClose函数在每次循环的开始前检查一次GLFW是否被要求退出
	// 如果是的话，该函数返回true，渲染循环将停止运行
	while (!glfwWindowShouldClose(window))
	{
		// 处理输入
		processInput(window);

		// render
		//清空屏幕所用颜色
		glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		// 每次新的渲染迭代开始时清屏，否则会看到上一次迭代的渲染结果
		// 缓冲位选项：GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT 和 GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

		// 激活shader program
		ourShader.use();

		glBindVertexArray(VAO);

		// 参数1是打算绘制的OpenGL图元的类型，参数2指定了顶点数组的起始索引。参数3指定打算绘制多少个顶点
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glBindVertexArray(0); // no need to unbind it every time 

		//交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
		glfwSwapBuffers(window);
		//检查有没有触发什么事件（比如键盘输入、鼠标移动等）
		//更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glDeleteProgram(ourShader.ID);

	// 释放删除之前分配的所有GLFW resources.
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	// 是否按下了ESC按键 没按则返回GLFW_RELEASE
	// 如果按下，设置true来关闭GLFW，因此下次循环while条件检测失败，程序关闭
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// 回调函数，每次窗口大小被调整时调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 前两个参数：窗口左下角位置
	// 后两个参数：宽度，高度
	glViewport(0, 0, width, height);
}*/