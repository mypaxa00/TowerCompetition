#pragma once

struct Animation {
	int animIndex = 0;
	int index;
	int frames;
	int speed;

	Animation() {}
	Animation(int i, int f, int s) {
		index = i;
		frames = f;
		speed = s;
	}

	/*if (aniamated) {
		src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
	}

	src.y = src.h * animIndex;*/

	std::map<const char*, Animation> animations;

	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};