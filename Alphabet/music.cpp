#include "music.h"

bool Music::loadMusic() {
    bool success = true;

    song = Mix_LoadMUS(MUSIC_PATH);
    if (song == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}

void Music::playSong() {
    Mix_PlayMusic(song, -1);
}

void Music::free() {
    Mix_FreeMusic(song);
    song = NULL;
}