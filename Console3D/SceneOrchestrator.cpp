#include "SceneOrchestrator.h"

int SceneOrchestrator::s_InstrumentVolume = 0;

void CALLBACK BassmodCallback(HSYNC handle, DWORD data, DWORD user)
{
    int instrument = LOWORD(data);
    int volume = HIWORD(data);

    //if (instrument == 48)
    //    printf("volume: %d\ninstrument: %d\n", volume, instrument);

    if (instrument == 48)
        SceneOrchestrator::s_InstrumentVolume = volume;
}

void SceneOrchestrator::InitMusic()
{
    BASSMOD_Init(-1, 44100, 0);

    if (BASSMOD_MusicLoad(FALSE, (void*)"music.xm", 0, 0, BASS_MUSIC_LOOP)) {
        BASSMOD_SetVolume(64);
        BASSMOD_MusicPlay();

        int channels = 0, instruments = 0;
        
        while (BASSMOD_MusicGetVolume(channels) != -1) {
            while (BASSMOD_MusicGetVolume(MAKELONG(instruments, channels)) != -1)
            {
                BASSMOD_MusicSetSync(BASS_SYNC_MUSICINST, MAKELONG(instruments, -1), &BassmodCallback, 0);
                instruments++;
            }
        
            channels++;
        }
    }
}