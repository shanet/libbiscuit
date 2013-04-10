#include "bisc.h"
#include "biscCore.h"


int biscDefineSong(unsigned char songNum, unsigned char *notes, unsigned char *notesDurations, unsigned int notesLen) {
    if(songNum > BISC_MAX_SONG_NUM)                   return BISC_ERR;
    if(sizeof(notes) != sizeof(notesDurations))       return BISC_ERR;
    if(notesLen <= 0 || notesLen > BISC_MAX_SONG_LEN) return BISC_ERR;

    if(biscSendByte(BISC_CMD_SONG_DEFINE) == BISC_ERR) return BISC_ERR;
    if(biscSendByte(songNum)              == BISC_ERR) return BISC_ERR;
    if(biscSendByte(notesLen)             == BISC_ERR) return BISC_ERR;

    for(unsigned int i=0; i<notesLen; i++) {
        assert(notes[i] >= BISC_MIN_NOTE && notes[i] <= BISC_MAX_NOTE);

        if(biscSendByte(notes[i])          == BISC_ERR) return BISC_ERR;
        if(biscSendByte(notesDurations[i]) == BISC_ERR) return BISC_ERR;
    }

    return BISC_SUCCESS;
}


int biscPlaySong(unsigned char songNum) {
    if(songNum > BISC_MAX_SONG_NUM) return BISC_ERR;

    if(biscSendByte(BISC_CMD_SONG_PLAY) == BISC_ERR) return BISC_ERR;
    if(biscSendByte(songNum) == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscBeep(void) {
    unsigned char beep[]  = {70};
    unsigned char beepd[] = {10};

    if(biscDefineSong(0, beep, beepd, sizeof(beepd)) == BISC_ERR) return BISC_ERR;

    return biscPlaySong(0);
}


int biscPlayFireflies(void) {
    unsigned char part1[]  = {58, 70, 86, 58, 70, 82, 75, 63, 75, 77, 75, 77, 82, 75};
    unsigned char part1d[] = {10, 10, 10, 10, 10, 20, 10, 10, 10, 10, 10, 10, 20, 10};
    
    unsigned char part2[]  = {56, 72, 70, 72, 75, 63, 56, 70, 72, 70, 60, 70, 75, 77};
    unsigned char part2d[] = {20, 10, 10, 10, 10, 10, 20, 10, 10, 10, 10, 10, 10, 10};

    unsigned char part3[]  = {56, 77, 86, 74, 65, 82, 75, 63, 70, 77, 75, 80, 79, 75, 70};
    unsigned char part3d[] = {10, 10, 10, 10, 10, 20, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    unsigned char part4[]  = {56, 72, 63, 56, 70, 63, 72, 56, 72, 70, 60, 75, 77};
    unsigned char part4d[] = {20, 10, 10, 10, 20, 10, 10, 10, 10, 10, 10, 10, 20};
    
    unsigned char part5[]  = {74, 70, 65, 74, 70, 72};
    unsigned char part5d[] = {30, 30, 20, 30, 30, 20};

    unsigned char part6[]  = {56, 72, 70, 72, 75, 70, 56, 72, 75, 60, 77};
    unsigned char part6d[] = {20, 10, 10, 10, 10, 10, 10, 30, 10, 20, 20};

    unsigned char part7[]  = {56, 63, 70, 70, 79, 77, 75};
    unsigned char part7d[] = {40, 10, 10, 20, 30, 30, 20};

    unsigned char part8[]  = {56, 72, 63, 56, 70, 63, 72, 56, 72, 70, 60, 75, 77, 75};
    unsigned char part8d[] = {20, 10, 10, 10, 20, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    if(biscDefineSong(1, part1, part1d, sizeof(part1)) == BISC_ERR) return BISC_ERR;
    if(biscDefineSong(2, part2, part2d, sizeof(part2)) == BISC_ERR) return BISC_ERR;
    if(biscDefineSong(3, part3, part3d, sizeof(part3)) == BISC_ERR) return BISC_ERR;
    if(biscDefineSong(4, part4, part4d, sizeof(part4)) == BISC_ERR) return BISC_ERR;
    if(biscDefineSong(5, part5, part5d, sizeof(part5)) == BISC_ERR) return BISC_ERR;
    if(biscDefineSong(6, part6, part6d, sizeof(part6)) == BISC_ERR) return BISC_ERR;
    if(biscDefineSong(7, part7, part7d, sizeof(part7)) == BISC_ERR) return BISC_ERR;
    if(biscDefineSong(8, part8, part8d, sizeof(part8)) == BISC_ERR) return BISC_ERR;

    if(biscPlaySong(1) == BISC_ERR) return BISC_ERR;
    usleep(2405*1000);
    if(biscPlaySong(2) == BISC_ERR) return BISC_ERR;
    usleep(2410*1000);
    if(biscPlaySong(3) == BISC_ERR) return BISC_ERR;
    usleep(2405*1000);
    if(biscPlaySong(4) == BISC_ERR) return BISC_ERR;
    usleep(2445*1000);
    if(biscPlaySong(5) == BISC_ERR) return BISC_ERR;
    usleep(2475*1000);
    if(biscPlaySong(6) == BISC_ERR) return BISC_ERR;
    usleep(2435*1000);
    if(biscPlaySong(7) == BISC_ERR) return BISC_ERR;
    usleep(2445*1000);
    if(biscPlaySong(8) == BISC_ERR) return BISC_ERR;
    usleep(2445*1000);

    return BISC_SUCCESS;
}