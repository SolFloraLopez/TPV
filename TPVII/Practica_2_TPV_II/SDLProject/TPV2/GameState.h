#pragma once
#include "Component.h"

struct GameState : Component {
	GameState() :
		 stopped_(true),
		 finished_(false)//
	{
	}	
	void setFinished(bool finished) {finished_ = finished;}

	bool isFinished() const {return finished_;}

	void setStopped(bool stopped) {stopped_ = stopped;	}

	bool isStopped() {return stopped_;}

private:
	bool stopped_;
	bool finished_;
};
