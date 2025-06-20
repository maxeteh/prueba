#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "audio_player.h"

struct encabezado
{
    uint32_t samplerate:4;
    uint32_t samplescount:28;
    //float *audio
};

struct elementos{
    struct encabezado sample;
    float *audio;
};

int main(){
    FILE *f = fopen("audio_list.raw","rb");
    if (f==NULL){
        printf("ERROR");
        return -1;
    }

    struct encabezado *v;
    int i=0;
    int cont=0;
    v=malloc(sizeof(struct elementos));
    while (fread(&v[0].samples, sizeof(struct encabezado),1,f)!=0);
    {
        fseek(f, v[0].samplescount*sizeof(float),SEEK_CUR);
        i++;
        cont++
    }
    printf("En total hay %d elementos",cont);
    int pista_a_reproducir;
    printf("Ingrese la pista a reproducir: ");
    scanf("%d",&pista_a_reproducir);
    audio=malloc(sizeof(struct elementos));

    fseek(f,0,SEEK_SET);
    for (int i = 0; i <cont ; i++)
    {
        fread(&v[i].sample,sizeof(struct encabezado),1,f);
        fread(&v[i].audio, sizeof(float),v[i].sample.samplescount,f);
    }


    fread(&v, sizeof(struct pistas),1,f);

    printf("SampleRate:        %d\n",v.sample.samplerate);
    printf("SampleCount:       %d\n",v.sample.samplescount);

    
    uint32_t rate;
    if (v[pista_a_reproducir].sample.samplerate==0)
    {
        rate = 32000;
    }else if(v.sample.samplerate==1){
        rate=44100;
    }else if(v.sample.samplerate==2){
        rate=48000;
    }else if (v.sample.samplerate==3)
    {
        rate=88200;
    }

    float *audio=malloc(sizeof(float)*v.samplescount);
    
    fread(audio, sizeof(float),v[pista_a_reproducir].sample.samplescount,f);
    play_audio(rate, v[pista_a_reproducir].sample.samplescount,v[pista_a_reproducir].audio);
    
    for(i=0;i<cont;i++){
         free(audio); 
    }
  
    fclose(f);

    return 0;
}