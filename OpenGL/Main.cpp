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
	
	return 0;
}