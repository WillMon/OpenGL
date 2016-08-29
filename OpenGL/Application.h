#ifndef APPLICATION
#define APPLICATION
#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>

using glm::mat4;
using glm::vec3;
using glm::vec4;

class BaseApp{
public: 
	BaseApp();
	virtual void Run() = 0;
	virtual bool StartUp() = 0;
	virtual void Shutdown() = 0;
	virtual bool Update(float) = 0;
	virtual void draw() = 0;
private:

};

BaseApp::BaseApp() {}


class MyApp:public BaseApp {
public:
	MyApp();
	bool StartUp() override;
	void Shutdown() override;
	bool Update(float) override;
	void draw() override;
private:

	GLFWwindow* window;
	mat4 view, projection;
	vec4 black, white, yellow, blue;

};
//The Constructer
MyApp::MyApp() {

	black = vec4(0.255f, 0.255f, 0.255f, 1.0f);
	white = vec4(1);
	yellow = vec4(0.255f, 0.255f, 0.0f, 1.0f);
	blue = vec4(0.0f, 0.0f, 0.225f, 1.0f);
}

// Creats the Windows or OpenGL for the Solor System that is going to be displayed 
bool MyApp::StartUp() {
	if (glfwInit() == false)
		return false;
	//Declares the perameters for the window 
	window = glfwCreateWindow(2560, 1440, "Solr System", nullptr, nullptr);
	// Makes the checks for existance in so that if it crashes it can be terminated 
	if (window == nullptr) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	//identifies that ogl has failed
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
	}
	//Helper Class, it simply a tool to easly vidualise shapes and lines 
	Gizmos::create();

	view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	projection = glm::perspective(glm::pi<float>() * 0.35f, 16 / 9.f, 0.1f, 1000.f);

	auto major = ogl_GetMajorVersion();
	auto miner = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, miner);

	//Setd the coor for the fair plain 
	glClearColor(0.255f, 0.255f, 0.255f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Set Buffer enabled 
	glEnable(GL_DEPTH_TEST);
}

void MyApp::Shutdown() {
	glfwSwapBuffers(window);
	glfwPollEvents();

	Gizmos::destroy();
}

void MyApp::draw() {
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));
}

bool MyApp::Update(float num) {
	while (glfwWindowShouldClose(window) == false
		&& glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
		draw();

}
#endif
