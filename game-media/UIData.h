#pragma once
#include "RenderableStaticObject.h"
#include "RenderableMovingObject.h"

class UIData {
public:
	struct Objects {
		RenderableMovingObject *player1Objects[4];
		//RenderableStaticObject *player2Objects[4];
		//RenderableStaticObject *player3Objects[4];
		//RenderableStaticObject *player4Objects[4];
		//RenderableStaticObject *player1NumberObjects[4];
		//RenderableStaticObject *player2NumberObjects[4];
		//RenderableStaticObject *player3NumberObjects[4];
		//RenderableStaticObject *player4NumberObjects[4];
	};
private:
	Objects objectData;
	RenderingEngine *engine;

	Transmission::Model *player1Models[4];
	//Transmission::Model *player2Models[4];
	//Transmission::Model *player3Models[4];
	//Transmission::Model *player4Models[4];
	//Transmission::Model *player1NumberModels[4];
	//Transmission::Model *player2NumberModels[4];
	//Transmission::Model *player3NumberModels[4];
	//Transmission::Model *player4NumberModels[4];

	Transmission::Vertex vertices[4];
	std::vector<Transmission::Texture *>textures;

	void calculateNumberVertices(Transmission::Vertex *vertices, int playerIndex, float margin);
	void calculatePlayerVertices(Transmission::Vertex *vertices, int playerIndex, float margin);

public:
	UIData();
	~UIData();
	Objects *getData();
};

