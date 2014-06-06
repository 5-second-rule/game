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
		RenderableStaticObject *boostObject;
		RenderableStaticObject *boostMeterFullObject;
		RenderableStaticObject *boostMeterEmptyObject;
		RenderableStaticObject *adrenalineObject;
		RenderableStaticObject *winnerObjects[4];
	};
private:
	Objects objectData;
	RenderingEngine *engine;
	float playerHeight;
	float boostHeight;
	float margin;
	float leftEdge;
	float rightEdge;

	Transmission::Model *playerModels[4];
	Transmission::Model *glowPlayerModels[4];
	Transmission::Model *numberModels[10];
	Transmission::Model *xModel;
	Transmission::Model *deadModel;
	Transmission::Model *boostModel;
	Transmission::Model *boostMeterFullModel;
	Transmission::Model *boostMeterEmptyModel;
	Transmission::Model *adrenalineModel;
	Transmission::Model *winnerModels[4];

	Transmission::Vertex vertices[4];
	std::vector<Transmission::Texture *>textures;

	float calculatePlayerVertices(Transmission::Vertex *vertices);
	float calculateXVertices(Transmission::Vertex *vertices, float lastEdge);
	float calculateNumberVertices(Transmission::Vertex *vertices, float lastEdge);
	void calculateDeadVertices(Transmission::Vertex *vertices, float lastEdge);
	float calculateBoostVertices(Transmission::Vertex *vertices);
	void calculateBoostTileVertices(Transmission::Vertex *vertices, float lastEdge);
	void calculateAdrenalineVertices(Transmission::Vertex *vertices);
	void calculateWinnerVertices(Transmission::Vertex *vertices);

public:
	UIData();
	~UIData();
	Objects *getData();
};

