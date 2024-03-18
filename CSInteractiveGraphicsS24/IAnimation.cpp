#include "IAnimation.h"
#include "GraphicsEnvironment.h"

void IAnimation::SetObject(std::shared_ptr<GraphicsObject> object)
{
	this->object = object;
}
