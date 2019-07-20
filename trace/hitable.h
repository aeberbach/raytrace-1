#pragma once

#include "ray.h"

struct hit_record {
	float t = 0.0;
	vec3 p;
	vec3 normal;
};

class hitable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

