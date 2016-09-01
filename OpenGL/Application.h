#ifndef APPLICATION
#define APPLICATION
#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>
#include <time.h>

using glm::mat4;
using glm::vec3;
using glm::vec4;

class BaseApp {
public:
	BaseApp();
	void Run() { Update(0); };
	virtual bool StartUp() = 0;
	virtual void Shutdown() = 0;
	virtual bool Update(float) = 0;
	virtual void draw() = 0;
private:

};

BaseApp::BaseApp() {}


class MyApp :public BaseApp {
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
	mat4 sunLoc, earthLoc, marsLoc, moonLoc;
	int deltaTime = 0, currentTime = 0, prevTime = 0;

};
//The Constructer
MyApp::MyApp() {

	black = vec4(0, 0, 0, 1);
	white = vec4(1);
	yellow = vec4(0.255f, 0.255f, 0.0f, 1.0f);
	blue = vec4(0.0f, 0.0f, 0.225f, 1.0f);
}

// Creats the Windows or OpenGL for the Solor System that is going to be displayed 
bool MyApp::StartUp() {
	if (glfwInit() == false)
		return false;
	//Declares the perameters for the window 
	window = glfwCreateWindow(1280, 720, "Solr System", nullptr, nullptr);
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
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	//Setd the coor for the fair plain 
	glClearColor(0.255f, 0.255f, 0.255f, 1.0f);
	
	//Set Buffer enabled 
	glEnable(GL_DEPTH_TEST);
}

void MyApp::Shutdown() {

	Gizmos::destroy();
}

void MyApp::draw() {
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(4));
	//mat4 thesunMatrix = mat4(1)
	//mat4 earth = thesunmatrix * glm::translate(vec3(5,0,0))
	//mat4 moon = earth * glm::translate(vec3(15,0,0)) * scale(.5,.5,.5)
	//vec4 transcolearth = earth[3]
	sunLoc = mat4(1);
	marsLoc = sunLoc * glm::translate(vec3(4,3,0));
	earthLoc = sunLoc * glm::translate(vec3(8,0,0));
	moonLoc = earthLoc * glm::translate(vec3(3,4,0));
	//make a matrix for each planet
	//transform that matrix  
	//you can translate * rotate * scale
	//this is called the transformation matrix
	//the original verts qare the model matrix
	//worldTransform = model * transformation matrix

	for (int i = 0; i < 42; ++i) {
		Gizmos::addLine(vec3(-20 + i, 0, 20), vec3(-20 + i, 0, -20), i == 1 ? black : white);
		Gizmos::addLine(vec3(20, 0, -20 + i), vec3(-20, 0, -20 + i), i == 20 ? black : white);
	}
	//addSphere(Location - vec3(x,y,z),radius,rows,colume,color,matrix refrenced)

	
	currentTime = clock();
	deltaTime = (currentTime - prevTime) / 10;
	prevTime = currentTime;
	if(glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS)

	Gizmos::addSphere(vec3(sunLoc[3][0], sunLoc[3][1], sunLoc[3][2]),1, 30, 20, yellow, &mat4(3));
	Gizmos::addSphere(vec3(marsLoc[3][0], marsLoc[3][1], marsLoc[3][2]), 1, 20, 20, white, &mat4(1));
	Gizmos::addSphere(vec3(earthLoc[3][0], earthLoc[3][1], earthLoc[3][2]), 1, 20, 20, blue, &mat4(1.50));
	Gizmos::addSphere(vec3(moonLoc[3][0], moonLoc[3][1], moonLoc[3][2]), 1, 20, 20, white, &mat4(.25));
	Gizmos::draw(projection * view);



	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool MyApp::Update(float num) {
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		draw();
	}
	return false; 
}
#endif
