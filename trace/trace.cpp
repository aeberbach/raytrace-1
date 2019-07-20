// trace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.f * vec3((rand() / (RAND_MAX + 1.f)), (rand() / (RAND_MAX + 1.f)), (rand() / (RAND_MAX + 1.f))) - vec3(1.f, 1.f, 1.f);
	} while (p.squared_length() >= 1.f);
	return p;
}

vec3 color(const ray& r, hitable* world) {
	hit_record rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5f * color(ray(rec.p, target - rec.p), world);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.f);
		return (1.f - t) * vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 1.f);
	}
}

int main() {
	int nx = 200;
	int ny = 100;
	int ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable* world = new hitable_list(list, 2);
	camera cam;

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			
			for (int s = 0; s < ns; s++) {
				float u = float(i + (rand() / (RAND_MAX + 1.0))) / float(nx);
				float v = float(j + (rand() / (RAND_MAX + 1.0))) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}