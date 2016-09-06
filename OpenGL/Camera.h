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
	mat4 worldTransform;
	mat4 viewTransform;
	mat4 projectionTransform;
	mat4 projectionViewTransform;

	virtual void Update(float deltaTime) = 0;
	void setPrespective (float fieldView,float aspectRatio,float near ,float far);
	void setLookAt(vec3 from, vec3 to, vec3 up);
	void setPosition(vec3 position);
	mat4 getWorldTransform();
	mat4 getView();
	mat4 getProjection();
	mat4 getProjectionView();
	void updateProjectionViewTransform();

};


class FlyCamera : public Camera {
public:
	void Update(float deltaTime) override;
	void setSpeed(float speed);
private:
	float speed;
	vec3 up;
};
#endif
