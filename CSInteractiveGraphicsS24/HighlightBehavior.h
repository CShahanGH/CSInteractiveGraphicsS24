#pragma once
#include "IBehavior.h"
#include "GraphicsObject.h"
class HighlightBehavior : public IBehavior
{
protected:
	HighlightParams params;
	float ambientIntensity = 0.0f;

public:
	void StoreDefaults();
	void SetParameter(IParams& param);
	void Update(double elapsedSeconds);

};


