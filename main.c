#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "audio_player.h"

struct pistas
{
    uint32_t samplerate:4;
    uint32_t samplescount:28;
    //float *audio
};

struct {
    struct pistas sample;
    float *audio;
};

int main(){
    FILE *f = fopen("audio_list.raw","rb");
    if (f==NULL){
        printf("ERROR");
        return -1;
    }

    struct pistas v;
    //v=malloc(sizeof(struct pistas));

    fread(&v, sizeof(struct pistas),1,f);

    printf("SampleRate:        %d\n",v.samplerate);
    printf("SampleCount:       %d\n",v.samplescount);

    uint32_t i=0;
    while(v.samplescount>i){
    uint32_t rate;
    if (v.samplerate==0)
    {
        rate = 32000;
    }else if(v.samplerate==1){
        rate=44100;
    }else if(v.samplerate==2){
        rate=48000;
    }else if (v.samplerate==3)
    {
        rate=88200;
    }
    i++;


    
    float *audio=malloc(sizeof(float)*v.samplescount);
    
    fread(audio, sizeof(float),v.samplescount,f);
    play_audio(rate, v.samplescount,audio);
    free(audio);
    }
    fclose(f);

    return 0;
}