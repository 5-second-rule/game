#pragma once
#include "RenderableStaticObject.h"
#include "RenderableMovingObject.h"

class UIData {
public:
	struct Objects {	
		RenderableMovingObject *playerObjects[4];
		RenderableMovingObject *numberObjects[10];
		RenderableMovingObject *xObject;

		RenderableMovingObject *jumboPlayerObjects[4];
		RenderableMovingObject *jumboNumberObjects[10];
		RenderableMovingObject *jumbboXObject;
	};
private:
	Objects objectData;
	RenderingEngine *engine;
	float playerHeight;


	Transmission::Model *playerModels[4];
	Transmission::Model *numberModels[10];
	Transmission::Model *xModel;

	Transmission::Model *jumboPlayerModels[4];
	Transmission::Model *jumboNumberModels[10];
	Transmission::Model *jumboXModel;

	Transmission::Vertex vertices[4];
	std::vector<Transmission::Texture *>textures;

	float calculatePlayerVertices(Transmission::Vertex *vertices, float margin, bool isJumbo);
	float calculateXVertices(Transmission::Vertex *vertices, float margin, float lastEdge, bool isJumbo);
	void calculateNumberVertices(Transmission::Vertex *vertices, float margin, float lastEdge, bool isJumbo);

public:
	UIData();
	~UIData();
	Objects *getData();
};

