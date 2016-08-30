#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>
#include "Application.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;


int main() {
	BaseApp * app = new MyApp();
	if (app->StartUp())
		app->Run();
	app->Shutdown();
	
	//if (glfwInit() == false)
	//	return -1;
	////Creats a wimdow to display for our OpenGL
	//GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	//if (window == nullptr) {
	//	glfwTerminate();
	//	return -2;
	//}

	//glfwMakeContextCurrent(window);

	//// the rest of our code goes here!

	//if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
	//	glfwDestroyWindow(window);
	//	glfwTerminate();
	//	return -3;
	//}
	////Gizmos ~ a Helper class, it simply a tool to easily visualises shapes and lines 
	//Gizmos::create();

	////Initialises all of the gizmos and sets up our virtual camera
	//mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	//mat4 projection = glm::perspective(glm::pi<float>() * 0.35f, 16 / 9.f, 0.1f, 1000.f);

	//auto major = ogl_GetMajorVersion();
	//auto minor = ogl_GetMinorVersion();
	//printf("GL: %i.%i\n", major, minor);

	//
	////Checks if the closed button has been pressed or if the escaped button has been clicked 
	//while (glfwWindowShouldClose(window) == false &&
	//	glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

	//	//Set the Color of the windows 
	//	glClearColor(0.160, 0.160, 0.160, 1);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	//glClearColor(0.25f, 0.25f, 0.25, 1);
	//	glEnable(GL_DEPTH_TEST);

	//	while(glfwWindowShouldClose(window) == false 
	//		&& glfwGetKey (window,GLFW_KEY_ESCAPE) != GLFW_PRESS) {

	//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//		Gizmos::clear();
	//		Gizmos::addTransform(glm::mat4(1));
	//		
	//		vec4 white(1);
	//		vec4 black(0, 0, 0, 1);

	//		for (int i = 0; i < 21; ++i) {
	//			Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 5 ? black : white);
	//			Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? black : white);
	//		}

	//		//addSphere(Location - vec3(x,y,z),radius,rows,colume,color,matrix refrenced)
	//		Gizmos::addSphere(vec3(0,0,0),1,20,20,vec4(0.255,0.255,0,1),nullptr);
	//		Gizmos::draw(projection * view);
	//		

	//		glfwSwapBuffers(window);
	//		glfwPollEvents();
	//	}

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}
	//
	//Gizmos::destroy();

	//glfwDestroyWindow(window);
	//glfwTerminate();
	return 0;
}