#ifndef CAMERA
#define CAMERA

#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>

using glm::mat4;
using glm::vec3;
using glm::vec4;
class Camera {
public:
	
	Camera(float filedOFView, float aspectRatio, float fnear, float ffar);

	virtual void update(float deltaTime) = 0;
	void setPerspective(float fieldOfView, float aspectRatio, float fnear, float ffar);
	void setLookAt(vec3 from, vec3 to);
	void setPosition(vec3 position);
	mat4 getWorldTransform() {return worldTransform;}
	mat4 getView() { return viewTransform; }
	mat4 getProjection() {return projectionTransform;
	}
	mat4 getProjectionView() { return projectionViewTransform; }
private :
	float speed;
	vec3 up;
	mat4 worldTransform;
	mat4 viewTransform;
	mat4 projectionTransform;
	mat4 projectionViewTransform;
	void updateProjectionViewTransfrom();

};

//Camera Movemenet Class based off user commands
class FlyCamera : public Camera {
private:
	
	vec3 up;
public:
	void update(float deltaTime) override;
	void setSpeed(float speed) { };
};
Camera::Camera(float filedOFView, float aspectRatio, float fnear, float ffar){
	speed = 10;
	up = vec3(0, 1, 0);
	worldTransform = mat4(1);
	viewTransform = mat4(1);
	setPerspective(filedOFView, aspectRatio, fnear, ffar);
}

//Camera Movement 
void Camera::update(float deltaTime) {
	GLFWwindow* window = glfwGetCurrentContext();

	float fs = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? deltaTime * speed * 2 : deltaTime * speed;
	
	//Translate the camera up on the z-axes  
	if (glfwGetKey(window, 'W') == GLFW_PRESS)
		worldTransform[3] -= worldTransform[2] * speed;
	//Translate the camera down on the z-axes  
	if (glfwGetKey(window, 'S') == GLFW_PRESS)
		worldTransform[3] += worldTransform[2] * speed;
	//Translate the camera down on the x-axes  
	if (glfwGetKey(window, 'A') == GLFW_PRESS)
		worldTransform[3] -= worldTransform[0] * speed;
	//Translate the camera up on the x-axes  
	if (glfwGetKey(window, 'D') == GLFW_PRESS)
		worldTransform[3] += worldTransform[0] * speed;

	// check for rotation
	static bool sbMouseButtonDown = false;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {

		static double siPrevMouseX = 0;
		static double siPrevMouseY = 0;

		if (sbMouseButtonDown == false) {
			sbMouseButtonDown = true;
			glfwGetCursorPos(window, &siPrevMouseX, &siPrevMouseY);
		}

		double mouseX = 0, mouseY = 0;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		double iDeltaX = mouseX - siPrevMouseX;
		double iDeltaY = mouseY - siPrevMouseY;

		siPrevMouseX = mouseX;
		siPrevMouseY = mouseY;

		glm::mat4 mMat;
		glm::vec3 worldVec = vec3(worldTransform[0].x, worldTransform[0].y, worldTransform[0].z );

		// pitch
		if (iDeltaY != 0) {
			mMat = glm::axisAngleMatrix(worldVec, (float)-iDeltaY / 150.0f);
			worldTransform[0] = mMat * worldTransform[0];
			worldTransform[1] = mMat * worldTransform[1];
			worldTransform[2] = mMat * worldTransform[2];
		}

		// yaw
		if (iDeltaX != 0) {
			mMat = glm::axisAngleMatrix(up, (float)-iDeltaX / 150.0f);
			worldTransform[0] = mMat * worldTransform[0];
			worldTransform[1] = mMat * worldTransform[1];
			worldTransform[2] = mMat * worldTransform[2];
		}
	}
	else 
		sbMouseButtonDown = false;

	viewTransform = glm::inverse(worldTransform);
	projectionViewTransform = projectionTransform * viewTransform;
}
	

#endif // !Camera