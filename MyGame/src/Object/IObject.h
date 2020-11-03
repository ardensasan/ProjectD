#ifndef IOBJECT_H
#define IOBJECT_H
class IObject {
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
};
#endif;