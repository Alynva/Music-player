#ifndef MUSIC_PLAYER
#define MUSIC_PLAYER

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "data_structures.h"

bool __ok;

bool __songFinished = false;
void songFinished() {
	__songFinished = true;
}

class MusicPlayer {
	Queue<Mix_Music*> queue_songs;
	
	public:
		MusicPlayer() {};
		~MusicPlayer() {
			Mix_CloseAudio();
			Mix_Quit();
		};
		bool init() {
			int mix_flags = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG;
			if((Mix_Init(mix_flags) & mix_flags) != mix_flags) {
			    SDL_Log("Mix_Init: %s\n", Mix_GetError());
			    return false;
			}
			
			if(SDL_Init(SDL_INIT_AUDIO) == -1) {
			    SDL_Log("SDL_Init: %s\n", SDL_GetError());
			    return false;
			}
			
			if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			    SDL_Log("Mix_OpenAudio: %s\n", Mix_GetError());
			    return false;
			}
		
			Mix_HookMusicFinished(songFinished);
			
			return true;
		};
		bool addMusic(const char* src) {
			Mix_Music* song = Mix_LoadMUS(src);
			if (!song) {
				SDL_Log("Mix_LoadMUS: %s", Mix_GetError());
				return false;
			}
			this->queue_songs.enqueue(song, __ok);
			
			song = NULL;
			return __ok;
		}
		int volumeMusic(int vol) {
			return Mix_VolumeMusic(vol);
		}
		bool play() {
			if (Mix_PlayMusic(this->queue_songs.getFront()->value, 1) == -1) {
				SDL_Log("Mix_PlayMusic: %s", Mix_GetError());
				return false;
			}
			return true;
		}
		void togglePlaying() {
			Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
		}
		void update() {
			if (__songFinished) {
				__songFinished = false;
				
				Mix_Music* temp;
				this->queue_songs.dequeue(temp);
				this->queue_songs.enqueue(temp, __ok);
				temp = NULL;
				
				this->play();
			}
		}
};

#endif
