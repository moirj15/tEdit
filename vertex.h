#ifndef VERTEX_H
#define VERTEX_H

typedef struct vertex_t {
	float x;
	float y;
	float z;
}Vertex;

#define printVert(v) printf("(%f, %f, %f)\n", v.x, v.y, v.z)

#endif
