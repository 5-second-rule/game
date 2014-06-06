#pragma once
#include "RenderableStaticObject.h"
#include "RenderableMovingObject.h"

class UIData {
public:
	struct Objects {	
		RenderableMovingObject *playerObjects[4];
		RenderableMovingObject *glowPlayerObjects[4];
		RenderableMovingObject *numberObjects[10];
		RenderableMovingObject *xObject;
		RenderableMovingObject *deadObject;
	};
private:
	Objects objectData;
	RenderingEngine *engine;
	float playerHeight;
	float margin;
	float leftEdge;

	Transmission::Model *playerModels[4];
	Transmission::Model *glowPlayerModels[4];
	Transmission::Model *numberModels[10];
	Transmission::Model *xModel;
	Transmission::Model *deadModel;

	Transmission::Vertex vertices[4];
	std::vector<Transmission::Texture *>textures;

	float calculatePlayerVertices(Transmission::Vertex *vertices);
	float calculateXVertices(Transmission::Vertex *vertices, float lastEdge);
	float calculateNumberVertices(Transmission::Vertex *vertices, float lastEdge);
	void calculateDeadVertices(Transmission::Vertex *vertices, float lastEdge);

public:
	UIData();
	~UIData();
	Objects *getData();
};

