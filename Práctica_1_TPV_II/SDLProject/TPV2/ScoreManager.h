#pragma once

#include "Component.h"

class ScoreManager: public Component {
public:

	ScoreManager();
	ScoreManager(int rounds);
	virtual ~ScoreManager();

	int getScore() const {
		return Score_;
	}

	void setScore(int score) {
		Score_ = score;
	}

	void setFinished(bool finished) {
		finished_ = finished;
	}

	bool isFinished() const {
		return finished_;
	}

	void setStopped(bool stopped) {
		stopped_ = stopped;
	}

	bool isStopped() {
		return stopped_;
	}

private:
	bool stopped_;
	bool finished_;
	int Score_;
};
