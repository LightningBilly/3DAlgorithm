//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
////窗口大小回调函数
//void framsize_callback(GLFWwindow* window, int width,int height);
////处理键盘鼠标输入输出事件
//void processInput(GLFWwindow* window);
//
//const unsigned int SCR_WIDHT = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location =0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"	gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
//"}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"}\n\0";
//
//int main() {
//	//初始化GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	//窗口
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDHT, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
//	if (window == NULL) {
//		std::cout << "Failed to create Window." << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	//由指定窗口生成上下文
//	glfwMakeContextCurrent(window);
//	//注册窗口回调
//	glfwSetFramebufferSizeCallback(window, framsize_callback);
//	//glad 加载合适的函数
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "GLAD load failed." << std::endl;
//		return -1;
//	}
//	//vertex shader
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//	int  success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	//frag shader
//	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragShader);
//	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	//program
//	unsigned int shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragShader);
//	glLinkProgram(shaderProgram);
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
//	}
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragShader);
//
//	float vertices[] = {
//		 0.5f,  0.5f, 0.0f,  // top right
//		 0.5f, -0.5f, 0.0f,  // bottom right
//		-0.5f, -0.5f, 0.0f,  // bottom left
//		-0.5f,  0.5f, 0.0f   // top left 
//	};
//	unsigned int indices[] = {  // note that we start from 0!
//		0, 1, 3,  // first Triangle
//		1, 2, 3   // second Triangle
//	};
//
//	unsigned int VBO, VAO, EBO;
//	//顶点属性数组
//	glGenVertexArrays(1, &VAO);
//	//缓冲区
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//	//操作当前顶点属性数组
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	
//	
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	glBindVertexArray(0);
//	//每一帧
//	while (!glfwWindowShouldClose(window)) {
//
//		processInput(window);
//		//设置清屏颜色
//		glClearColor(0.1f, 0.3f, 0.1f, 1.0f);
//		//清除颜色缓冲
//		glClear(GL_COLOR_BUFFER_BIT);
//		//设置线框模式
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		//调用着色器程序
//		glUseProgram(shaderProgram);
//		//绑定顶点属性数组
//		glBindVertexArray(VAO);
//		//索引绘制
//		//glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	glfwTerminate();
//	return 0;
//}
//void processInput(GLFWwindow* window) {
//
//	if (glfwGetKey(window, GLFW_PRESS) == GLFW_KEY_ESCAPE) {
//		glfwSetWindowShouldClose(window,true);
//	}
//}
//void framsize_callback(GLFWwindow* window, int width, int height) {
//	
//	glViewport(0,0,width, height);
//}
//
#include <GLFW/glfw3.h>

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
