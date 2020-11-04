#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "GameObject.h"
#include "Animation.h"
#include "BoxCollider.h"
class MovingObject : public GameObject
{
public:
	MovingObject();
	MovingObject(ObjectProperty objProp);
	void UpdatePosX(float x);
	void UpdatePosY(float y);
	inline bool IsOnGround() { return isOnGround; }
	void SetJump(bool b);
	virtual void Update();
	virtual bool CheckCollisionToObject(SDL_Rect objectCollider) { return false; }
	virtual SDL_Rect GetCollider() { return boxCollider->GetBoxCollider(); }
	virtual void Render();
	virtual void Clean();
	void SetTexture(std::string id);
	bool JumpCollide() { return jumpCollide; }
	void SetIsHit(bool b) { isHit = b; }
	inline bool IsHit() { return isHit; }
protected:
	float yVelocity,xVelocity;  // 1=left 2=up 3=right 4=down
	float gravity;
	int direction;
private:
	SDL_RendererFlip flip;
	Animation* animation;
	BoxCollider* boxCollider;
	bool jumpCollide;
	bool isOnGround;
	int animationDelay;
	bool isHit;
	int isHitCD; // cooldown before object can be hit again
};
#endif
