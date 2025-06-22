#include <stdio.h>  // Sirve para entrada y salida estándar (input/output) y funciones comunes.
#include <stdint.h> // Define tipos de datos con tamaño exacto.
#include <stdlib.h> // Contiene funciones de utilidad general(para vec dinamicos).
#include <math.h>   // Funciones matemáticas avanzadas.
#include"audio_player.h"
/*
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
    v(pista_a_reproducir).audio=malloc(sizeof(struct elementos));

    fseek(f,0,SEEK_SET);
    for (int i = 0; i <cont ; i++)
    {
        fread(&v[i].sample,sizeof(struct encabezado),1,f);
          v[i].audio=malloc(size
            of(struct elementos));
        fread(v[i].audio, sizeof(float),v[i].sample.samplescount,f); 
      
    }


    //fread(&v, sizeof(struct pistas),1,f);

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

    //float *audio=malloc(sizeof(float)*v.samplescount);
    
    fread(v[pista_a_reproducir].audio, sizeof(float),v[pista_a_reproducir].sample.samplescount,f);
    play_audio(rate, v[pista_a_reproducir].sample.samplescount,v[pista_a_reproducir].audio);
    
    for(int i=0;i<cont;i++){
         free(v[i].audio); 
    }
  
    fclose(f);

    return 0;
}
*/

struct encabezado{
    uint32_t velocidad: 4;
    uint32_t cantidad: 28;
};

struct pista
{
    struct encabezado samples;
    float *audio;
};

int main(){

    FILE *f = fopen("audio_list.raw","rb");
    if(f == NULL){
        printf("ERROR opening the file\n");
        return -1;
    }

    int cont = 0;
    struct pista *v;
    v = malloc(sizeof(struct pista));

    while(fread(&(v->samples),sizeof(struct encabezado),1,f)!=0)
    {
        fseek(f,v->samples.cantidad * sizeof(float), SEEK_CUR); // salteo la cantidad de floats q hay para llegar al otro encabezado
        cont++;
    }
    fseek(f,0,SEEK_SET); //vuelvo el puntero del baffer al inicio
    printf("La cantidad de pistas es: %d", cont);
    free(v);
    v = malloc(sizeof(struct pista)*cont);

    for(int i = 0; i<cont ; i++){
        fread(&v[i].samples, sizeof(struct encabezado),1,f);
        v[i].audio = malloc(v[i].samples.cantidad*sizeof(float));
        fread(v[i].audio,sizeof(float),v[i].samples.cantidad,f); //leo la cantidad de muestras (v[i].samples.cantidad)
    } 
    printf("\nIngrese la pista que quiere escuchar: ");
    int track;
    scanf("%d",&track);

    int rate;
    if(v[track].samples.velocidad == 0){
        rate = 32000;
    }else if(v[track].samples.velocidad == 1){
        rate = 44100;
    }else if(v[track].samples.velocidad == 2){
        rate = 48000;
    }else if (v[track].samples.velocidad == 3){
        rate = 88200;
    }
    
    play_audio(rate, v[track].samples.cantidad, v[track].audio);

    for(int i=0; i<cont; i++){
        free(v[i].audio);
    }
    free(v);
    
    fclose(f);
    return 0;
}