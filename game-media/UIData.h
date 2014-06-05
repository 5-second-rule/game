#pragma once
#include "RenderableStaticObject.h"
#include "RenderableMovingObject.h"

class UIData {
public:
	struct Objects {
		RenderableMovingObject *playerObjects[4];
		RenderableMovingObject *numberObjects[10];
		RenderableMovingObject *xObject;
	};
private:
	Objects objectData;
	RenderingEngine *engine;
	float playerHeight;

	Transmission::Model *playerModels[4];
	Transmission::Model *numberModels[4];
	Transmission::Model *xModel;

	Transmission::Vertex vertices[4];
	std::vector<Transmission::Texture *>textures;

	float calculatePlayerVertices(Transmission::Vertex *vertices, float margin);
	float calculateXVertices(Transmission::Vertex *vertices, float margin, float lastEdge);
	void calculateNumberVertices(Transmission::Vertex *vertices, float margin, float lastEdge);

public:
	UIData();
	~UIData();
	Objects *getData();
};

