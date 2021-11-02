#pragma once

#include "ofMain.h"

class Path {
public:
	vector<glm::vec2> vertices;
	Path();
	~Path();
	Path(glm::vec2[]);
};