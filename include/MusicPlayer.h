#ifndef MUSIC_PLAYER
#define MUSIC_PLAYER

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "data_structures.h"

#define __MP_ERROR_CRITICAL 1
#define __MP_ERROR_INFO 2

bool __ok;

bool __songFinished = false;
void __funcSongFinished() {
	__songFinished = true;
}

class MusicPlayer {
	Queue<Mix_Music*> queue_songs;
	int errorType;
	char* error;
	void setError(int = 0, char*, ...);
	
	public:
		MusicPlayer();
		~MusicPlayer();
		char* getError() const;
		void printError() const;
		bool init() const;
		bool addMusic(const char*);
		int volumeMusic(int) const;
		bool play() const;
		void togglePlaying() const;
		void update();
		void clear();
};

MusicPlayer::MusicPlayer():error(""), errorType(0) {};

MusicPlayer::~MusicPlayer() {
	Mix_CloseAudio();
	Mix_Quit();
};

void MusicPlayer::setError(int type, char* msg, ...) {
	this->errorType = type;
	this->error = msg;
}

char* MusicPlayer::getError() const {
	return this->error;
}

void MusicPlayer::printError() const {
	switch(this->errorType) {
		case __MP_ERROR_CRITICAL:
			SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, this->getError());
			break;
		case __MP_ERROR_INFO:
			SDL_LogInfo(SDL_LOG_CATEGORY_AUDIO, this->getError());
			break;
		default:
			SDL_Log(this->getError());
	}
	SDL_Delay(5000);
}

bool MusicPlayer::init() const {
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

	int mix_flags = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG;
	if((Mix_Init(mix_flags) & mix_flags) != mix_flags) {
	    this->setError(__MP_ERROR_CRITICAL, "Mix_Init: %s\n", Mix_GetError());
	    return false;
	}
	
	if(SDL_Init(SDL_INIT_AUDIO) == -1) {
	    this->setError(__MP_ERROR_CRITICAL, "SDL_Init: %s\n", SDL_GetError());
	    return false;
	}
	
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
	    this->setError(__MP_ERROR_CRITICAL, "Mix_OpenAudio: %s\n", Mix_GetError());
	    return false;
	}

	Mix_HookMusicFinished(__funcSongFinished);
	
	return true;
};

bool MusicPlayer::addMusic(const char* src) {
	Mix_Music* song = Mix_LoadMUS(src);
	if (!song) {
		SDL_LogWarn(SDL_LOG_CATEGORY_AUDIO, "Mix_LoadMUS: %s", Mix_GetError());
		return false;
	}
	this->queue_songs.enqueue(song, __ok);
	
	song = NULL;
	return __ok;
}

int MusicPlayer::volumeMusic(int vol) const {
	return Mix_VolumeMusic(vol);
}

bool MusicPlayer::play() const {
	if (Mix_PlayMusic(this->queue_songs.getFront()->value, 1) == -1) {
		SDL_Log("Mix_PlayMusic: %s", Mix_GetError());
		return false;
	}
	return true;
}

void MusicPlayer::togglePlaying() const {
	Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
}

void MusicPlayer::update() {
	if (__songFinished) {
		__songFinished = false;
		
		Mix_Music* temp;
		this->queue_songs.dequeue(temp);
		this->queue_songs.enqueue(temp, __ok);
		temp = NULL;
		
		this->play();
	}
}

void MusicPlayer::clear() {
	this->queue_songs.clear();
}

#endif
