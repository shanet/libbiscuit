#include "bisc.h"
#include "biscCore.h"


int biscDefineSong(unsigned char songNum, unsigned char *notes, unsigned char *notesDurations, unsigned int notesLen) {
    assert(songNum <= 15);
    assert(sizeof(notes) == sizeof(notesDurations));
    assert(notesLen > 0 && notesLen <= 16)

    if(biscSendByte(BISC_CMD_SONG_DEFINE) == BISC_ERR) return BISC_ERR;
    if(biscSendByte(songNum)              == BISC_ERR) return BISC_ERR;
    if(biscSendByte(notesLen)             == BISC_ERR) return BISC_ERR;

    for(unsigned int i=0; i<notesLen; i++) {
        assert(notes[i] >= 31 && notes[i] <= 127);

        if(biscSendByte(notes[i])          == BISC_ERR) return BISC_ERR;
        if(biscSendByte(notesDurations[i]) == BISC_ERR) return BISC_ERR;
    }

    return BISC_SUCCESS;
}


int biscPlaySong(unsigned char songNum) {
    assert(songNum <= 15);

    if(biscSendByte(BISC_CMD_SONG_PLAY) == BISC_ERR) return BISC_ERR;
    if(biscSendByte(songNum) == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}