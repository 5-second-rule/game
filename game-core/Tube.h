#pragma once
#include "StaticObject.h"

class GAMECOREDLL Tube : public StaticObject, public ICollidable
{
public:
	Tube();
	virtual ~Tube();

	// ICollidable Methods
	Common::Vector4 getGroupingParameter() const;
	bool collidesWith(const ICollidable*) const;
	void handleCollision(std::shared_ptr<const Bounds>, float dt);
	std::shared_ptr<const Bounds> getBounds() const;
	unsigned int getPriority() const;
};

