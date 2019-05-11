#ifndef TUTORIALLAYER_h
#define TUTORIALLAYER_h

#include "LayerBase.h"

class TutorialLayer : public LayerBase
{
public:
	TutorialLayer();
	~TutorialLayer();

	CREATE_FUNC(TutorialLayer);

private:
	bool init();
};

#endif