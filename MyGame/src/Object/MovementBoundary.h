#ifndef MOVEMENTBOUNDARY_H
#define MOVEMENTBOUNDARY_H
#include "BoxCollider.h"
#include "GameObject.h"
class MovementBoundary // generates boundary boxes for enemies
{
public:
	MovementBoundary();
	MovementBoundary(ObjectProperty objProp);
	bool IsBoundarySet();
	inline SDL_Rect GetBoxCollider() { return boundaryCollider->GetBoxCollider(); }
	void UpdateBoundary();
	void Render();
private:
	ObjectProperty leftBox;
	ObjectProperty rightBox;
	BoxCollider* leftBoxCollider;
	BoxCollider* rightBoxCollider;
	BoxCollider* boundaryCollider;
	bool leftLimitReached; // limit for generating box on right side
	bool rightLimitReached; // limit for generating box on right side
	bool isBoundarySet;
};
#endif;

