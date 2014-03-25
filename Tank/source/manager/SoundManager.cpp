#include "include\manager\SoundManager.h"

#include "OgreOggSound.h"

SoundManager::SoundManager() {
	mOggSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
	mOggSoundManager->init();
	createFireSound();
	createExplosionSound();
	createMoveSound();
}

void SoundManager::createFireSound() {
	mOggSoundManager->createSound("fire", "fire.wav", false, false, false);
}

void SoundManager::createExplosionSound() {
	mOggSoundManager->createSound("explosion", "explosion.wav", false, false, false);
}

void SoundManager::createMoveSound() {
	mOggSoundManager->createSound("move", "engine.wav", false, false, false);
}

void SoundManager::playFireSound() {
	mOggSoundManager->getSound("fire")->stop();
	mOggSoundManager->getSound("fire")->play();
}

void SoundManager::playExplosionSound() {
	if (!mOggSoundManager->getSound("explosion")->isPlaying()) { 
		mOggSoundManager->getSound("explosion")->play();
	} 
}

void SoundManager::playMoveSound() {
	if (!mOggSoundManager->getSound("move")->isPlaying()) {
	    mOggSoundManager->getSound("move")->play();
	}
}

SoundManager::~SoundManager() {
	mOggSoundManager->destroyAllSounds();
}