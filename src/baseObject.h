#pragma once

#include "ofMain.h"

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
	BaseObject();
	glm::vec3 trans, scale;
	float	rot;
	bool	bSelected;
	void setPosition(glm::vec3);
	// Gets the Tranformation Matrix of the object using rotation, scale, and translation
	//
	glm::mat4 getTransformMatrix() {
		glm::mat4 T = glm::translate(glm::mat4(1.0), trans);
		T = glm::rotate(T, glm::radians(rot), glm::vec3(0, 0, 1));
		T = glm::scale(T, scale);
		return T;
	}
	// Gets a vector representing the current heading of the object. Always of length 1, relative to y-axis
	//
	glm::vec3 getHeading() {
		return glm::normalize(glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1)) * glm::vec4(0, 1, 0, 0));
	}
};