
#include <stdlib.h>
#include "vertexBuffer.h"


VertexBuffer *create_VertexBuffer(void) 
{
	VertexBuffer *vb = (VertexBuffer *)safe_malloc(sizeof(VertexBuffer));
	vb->vertexData = NULL;
	vb->elementData = NULL;
	vb->vSize = 0;
	vb->eSize = 0;

	return vb;
}

void destroy_VertexBuffer(VertexBuffer *vb) 
{
	if (vb->vertexData)
		free(vb->vertexData);
	if (vb->elementData)
		free(vb->elementData);
	free(vb);
}

/**
 * Adds the given vertex and element data to the given vertexBuffer.
 *
 * @param vb: The vertexBuffer that will have data added to it.
 * @param vList: The list of verticies.
 * @param eList: The list of element data.
 * @param vS: The size of the vertex list.
 * @param eS: The size of the element list.
 */
void add_data(VertexBuffer *vb, Vertex *vList, u32 *eList, u32 vS, u32 eS) 
{
	f32 *tmpVD = NULL;
	u32 *tmpED = NULL;
	if (!vb->vertexData) {
		//vb->vertexData = (f32 *)safe_malloc(sizeof(f32) * 2000);
		tmpVD = (f32 *)safe_malloc(sizeof(f32) * vS * 4);
	}
	else {
		tmpVD = (float *) realloc((void *)vb->vertexData, 
						sizeof(float) * (vb->vSize + (vS * sizeof(Vertex) )));
		if (!tmpVD) {
			fprintf(stderr, "failed to realloc\n");
			exit(EXIT_FAILURE);
		}
	}
	if (!vb->elementData) {
		//vb->elementData = (u32 *)safe_malloc(sizeof(u32) * 2000);
		tmpED = (u32 *)safe_malloc(sizeof(u32) * eS);
	}
	else {
		tmpED = (u32 *) realloc(vb->elementData, 
						sizeof(u32) * (vb->eSize + eS));
		if (!tmpED) {
			fprintf(stderr, "failed to realloc\n");
			exit(EXIT_FAILURE);
		}
	}
	u32 v = vb->vSize;
	u32 e = vb->eSize;

	for (u32 i = 0; i < vS; i++) {
		tmpVD[v]= vList[i].x;
		v++;
		tmpVD[v] = vList[i].y;
		v++;
		tmpVD[v] = vList[i].z;
		v++;
		tmpVD[v] = 1.0;		// make w = 1
		v++;
	}
	vb->vertexData = tmpVD;
	vb->vSize += vS * 4;
	
	for (u32 i = 0; i < eS; i++) {
		tmpED[e] = eList[i] + (vb->vSize / 4) - 4;	
		e++;
	}
	vb->elementData = tmpED;
	vb->eSize += eS;
}

void print_data(VertexBuffer *vb) {
	int v = 0;
	int e = 0;
	while (v < vb->vSize) {
		Vertex tmp1 = {vb->vertexData[v], vb->vertexData[v + 1], vb->vertexData[v + 2]};
		v += 4;
		Vertex tmp2 = {vb->vertexData[v], vb->vertexData[v + 1], vb->vertexData[v + 2]};
		v += 4;
		Vertex tmp3 = {vb->vertexData[v], vb->vertexData[v + 1], vb->vertexData[v + 2]};
		v += 4;
		Vertex tmp4 = {vb->vertexData[v], vb->vertexData[v + 1], vb->vertexData[v + 2]};
		printVert(tmp1);
		printVert(tmp2);
		printVert(tmp3);
		printVert(tmp4);
		v += 4;
		printf("connections: %d, %d, %d, %d, %d, %d\n", vb->elementData[e],
				vb->elementData[e + 1],vb->elementData[e + 2], vb->elementData[e + 3],
				vb->elementData[e + 4],vb->elementData[e + 5]);
		e += 6;
	}
}
