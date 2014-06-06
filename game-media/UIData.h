#pragma once
#include "RenderableStaticObject.h"
#include "RenderableMovingObject.h"
#include "RenderableStaticObject.h"

class UIData {
public:
	struct Objects {	
		RenderableStaticObject *playerObjects[4];
		RenderableStaticObject *glowPlayerObjects[4];
		RenderableStaticObject *numberObjects[10];
		RenderableStaticObject *xObject;
		RenderableStaticObject *deadObject;
		RenderableStaticObject *adrenalineObject;
		RenderableStaticObject *countdownObjects[4];
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
	Transmission::Model *adrenalineModel;
	Transmission::Model *countdownModels[4];

	Transmission::Vertex vertices[4];
	std::vector<Transmission::Texture *>textures;

	float calculatePlayerVertices(Transmission::Vertex *vertices);
	float calculateXVertices(Transmission::Vertex *vertices, float lastEdge);
	float calculateNumberVertices(Transmission::Vertex *vertices, float lastEdge);
	void calculateDeadVertices(Transmission::Vertex *vertices, float lastEdge);
	void calculateAdrenalineVertices(Transmission::Vertex *vertices);
	void calculateCountdownVertices(Transmission::Vertex *vertices, bool isGo);

public:
	UIData();
	~UIData();
	Objects *getData();
};

