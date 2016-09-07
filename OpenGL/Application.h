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
	vec4 black, white, yellow, blue, red, grey;
	mat4 sunLoc = mat4(3), earthLoc = mat4(1.5), marsLoc = mat4(1), moonLoc = mat4(.25);

	float deltaTime = 0, currentTime = 0, prevTime = 0;

};
//The Constructer
MyApp::MyApp() {

	black = vec4(0, 0, 0, 1);
	white = vec4(1);
	red = vec4(.225, 0, 0, 1);
	yellow = vec4(0.255f, 0.255f, 0.0f, 1.0f);
	blue = vec4(0.0f, 0.0f, 0.225f, 1.0f);
	grey = vec4(0.200f, 0.200f, 0.200f, 1);
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

	//Setd the color for the fair plain 
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
	//Set the time in the game space
	currentTime = glfwGetTime();
	deltaTime = (currentTime - prevTime);
	prevTime = currentTime;

	printf("DT: %i.%i\n", deltaTime);

	//Prejection Ones praspective
	//mat4 thesunMatrix = mat4(1)
	//mat4 earth = thesunmatrix * glm::translate(vec3(5,0,0))
	//mat4 moon = earth * glm::translate(vec3(15,0,0)) * scale(.5,.5,.5)
	//vec4 transcolearth = earth[3]
	//sunLoc = sunLoc * glm::translate(vec3(0,deltaTime * cos(1),0));
	marsLoc = sunLoc * glm::translate(vec3(1.75f,0,0));
	earthLoc = sunLoc * glm::translate(vec3(2.75f,0,0));
	moonLoc = earthLoc * glm::translate(vec3(.75f,.35f,0));


	//Planet scaling 
	marsLoc = marsLoc * glm::scale(vec3(.35, .35, .35));
	earthLoc = earthLoc * glm::scale(vec3(.45, .45, .45));
	moonLoc = moonLoc * glm::scale(vec3(.15, .15, .15));
	float t = glfwGetTime();
	sunLoc *= glm::rotate(t * deltaTime, vec3(0, 1, 0));
	//planets Rotation from the sun
	//marsLoc = marsLoc * glm::rotate(10.0f * deltaTime * .5f, vec3(0, 1, 0));
	//earthLoc = earthLoc*  glm::rotate(.5f * deltaTime, vec3(0, 1, 0));
	//moonLoc = moonLoc *  glm::rotate(.5f * deltaTime, vec3(0, 1, 0));

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
	if (glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS) {
	
		
		
	}

	
	Gizmos::addSphere(vec3(sunLoc[3][0], sunLoc[3][1], sunLoc[3][2]),1, 30, 20, yellow, &sunLoc);
	Gizmos::addSphere(vec3(marsLoc[3][0], marsLoc[3][1], marsLoc[3][2]), 1, 20, 20, red, &marsLoc);
	Gizmos::addSphere(vec3(earthLoc[3][0], earthLoc[3][1], earthLoc[3][2]), 1, 20, 20, blue, &earthLoc);
	Gizmos::addSphere(vec3(moonLoc[3][0], moonLoc[3][1], moonLoc[3][2]), 1, 20, 20, grey, &moonLoc);
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
