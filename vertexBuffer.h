#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "utils.h"
#include "vertex.h"

struct VertexBuffer {
	f32 	*vertexData;
	u32 	*elementData;
	u32 	vSize;
	u32 	eSize;
};

VertexBuffer *create_VertexBuffer(void);

void destroy_VertexBuffer(VertexBuffer *vb);

/**
* Adds the given vertex and element data to the given vertexBuffer.
*
* @param vb: The vertexBuffer that will have data added to it.
* @param vList: The list of verticies.
* @param eList: The list of element data.
* @param vSize: The size of the vertex list.
* @param eSize: The size of the element list.
*/
void add_data(VertexBuffer *vb, Vertex *vList, u32 *eList, u32 vS, u32 eS);

void print_data(VertexBuffer *vb);

#endif
