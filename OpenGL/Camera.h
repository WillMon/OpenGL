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

Camera::Camera() {
}
void Camera::setPrespective(float fieldview, float aspectRatio, float nEar, float fAr) {
	viewTransform[0][0] = 1 / aspectRatio * tan(fieldview / 2);
	viewTransform[1][1] = 1 / tan(fieldview / 2);
	viewTransform[2][2] = -((fAr + nEar / fAr - nEar));
	viewTransform[2][3] = -((2*fAr*nEar) / (fAr - nEar));
}
void Camera::setLookAt(vec3 from, vec3 to, vec3 up) {
	glm::lookAt(from, to, up);
}
mat4 Camera::getProjection() {

}
mat4 Camera::getView() {
	return viewTransform;
}


#endif
