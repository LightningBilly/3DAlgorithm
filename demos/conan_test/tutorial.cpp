//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
////���ڴ�С�ص�����
//void framsize_callback(GLFWwindow* window, int width,int height);
////������������������¼�
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
//	//��ʼ��GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	//����
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDHT, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
//	if (window == NULL) {
//		std::cout << "Failed to create Window." << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	//��ָ����������������
//	glfwMakeContextCurrent(window);
//	//ע�ᴰ�ڻص�
//	glfwSetFramebufferSizeCallback(window, framsize_callback);
//	//glad ���غ��ʵĺ���
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
//	//������������
//	glGenVertexArrays(1, &VAO);
//	//������
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//	//������ǰ������������
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
//	//ÿһ֡
//	while (!glfwWindowShouldClose(window)) {
//
//		processInput(window);
//		//����������ɫ
//		glClearColor(0.1f, 0.3f, 0.1f, 1.0f);
//		//�����ɫ����
//		glClear(GL_COLOR_BUFFER_BIT);
//		//�����߿�ģʽ
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		//������ɫ������
//		glUseProgram(shaderProgram);
//		//�󶨶�����������
//		glBindVertexArray(VAO);
//		//��������
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
