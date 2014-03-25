#ifndef __SoundManager_h_
#define __SoundManager_h_

namespace OgreOggSound {
	class OgreOggSoundManager;
}

class SoundManager {
public:
	SoundManager();
	~SoundManager();
	void playFireSound();
	void playExplosionSound();
	void playMoveSound();

private:
	void createFireSound();
	void createExplosionSound();
	void createMoveSound();

	OgreOggSound::OgreOggSoundManager *mOggSoundManager;
};

#endif