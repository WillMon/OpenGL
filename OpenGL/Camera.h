#ifndef CAMERA
#define CAMERA
#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>


using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera {
public:
	

	virtual void Update(float deltaTime) = 0;
	void setPrespective (float fieldview,float aspectRatio,float nEar ,float fAr);
	void setLookAt(vec3 from, vec3 to, vec3 up);
	void setPosition(vec3 position);
	mat4 getWorldTransform();
	mat4 getView();
	mat4 getProjection();
	mat4 getProjectionView();
	void updateProjectionViewTransform();
private:
	mat4 worldTransform;
	mat4 viewTransform;
	mat4 projectionTransform;
	mat4 projectionViewTransform;


};


class FlyCamera : public Camera {
public:
	void Update(float deltaTime) override;
	void setSpeed(float speed);
private:
	float speed;
	vec3 up;
};

Camera::Camera() {}

//Praspective Transform/Orthographic Projection 
void Camera::setPrespective(float fieldview, float aspectRatio, float nEar, float fAr) {
	projectionTransform[0][0] = 1 / aspectRatio * tan(fieldview / 2);
	projectionTransform[1][1] = 1 / tan(fieldview / 2);
	projectionTransform[2][2] = -((fAr + nEar / fAr - nEar));
	projectionTransform[2][3] = -((2*fAr*nEar) / (fAr - nEar));
	projectionTransform[3][2] = -1;
}
//Persoective View 
void Camera::setLookAt(vec3 from, vec3 to, vec3 up) {
	viewTransform = glm::lookAt(from, to, up);
}
//Modle Matrex
void Camera::setPosition(vec3 position) {
	worldTransform = glm::translate(position);
}
mat4 Camera::getWorldTransform() {
	mat4 world = worldTransform * viewTransform;
	return world;
}
mat4 Camera::getProjection() {

}

mat4 Camera::getView() {	
	return getWorldTransform() * viewTransform;
}
#endif
