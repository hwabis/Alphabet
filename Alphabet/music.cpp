#include "music.h"

bool Music::loadMusic(std::string path) {
    bool success = true;

    song = Mix_LoadWAV(path.c_str());
    if (song == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}

void Music::playSong() {
    Mix_PlayChannel(-1, song, 0);
}

bool Music::isPlaying() {
    return Mix_Playing(-1);
}

void Music::free() {
    Mix_FreeChunk(song);
    song = NULL;
}