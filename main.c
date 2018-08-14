#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_keyboard.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
FILE *dosya;
SDL_Window  *window = NULL;
int  Running = 1;
SDL_Texture *background = NULL;
SDL_Surface  *message = NULL;
SDL_Surface  *message1 = NULL;
SDL_Surface  *message2 = NULL;
SDL_Surface  *message3 = NULL;
TTF_Font *font = NULL;
SDL_Texture *text;
SDL_Texture *text1;
SDL_Rect  textRect;
SDL_Rect  textRect1;
SDL_Texture *text2;
SDL_Texture *text3;
SDL_Rect  textRect2;
SDL_Rect  textRect3;
SDL_Rect  displayRect;
SDL_Rect  rectBackground;
SDL_Event Event;
SDL_Renderer *renderer;
int N;//matrisin boyutu
SDL_Color textColor={0,0,0};
char sayilar[10];
int w=0,h=0;
int N,sayac=0;
int LineHeight;
int sayi;
int dizi[10];
int  sayac1=0;
void dosyadan_oku(int N,int *matris);
void dosyalari_temizle(int secim);
void dosyaya_had_altmatris_yaz(int *matris,int N);
void dosyaya_mds_altmatris_yaz(int *matris,int N);
void dosyaya_sim_altmatris_yaz(int *matris,int N);
void dosyaya_dai_altmatris_yaz(int *matris,int N);
void alt_matris(int *ptr,int N,int secim);
int chio_yontemi(int *ptr,int N);
int determinant(int *matris);
int mds_matris_mi(int *ptr,int N);
int simetrik_mi(int *matris,int N);
int hadamard_mi(int *matris,int N);
int dairesel_mi(int *matris,int N);
void dosyadan_oku(int N,int *matris);
void dosyaya_had_altmatris_yaz(int *matris,int N);
void dosyaya_mds_altmatris_yaz(int *matris,int N);
void dosyaya_sim_altmatris_yaz(int *matris,int N);
void dosyaya_dai_altmatris_yaz(int *matris,int N);
void alt_matris(int *ptr,int N,int secim);
int chio_yontemi(int *ptr,int N);
int determinant(int *matris);
int mds_matris_mi(int *ptr,int N);
int simetrik_mi(int *matris,int N);
int hadamard_mi(int *matris,int N);
int dairesel_mi(int *matris,int N);

char numaraya_cevir(int scancode){
if(scancode==89) return  1;
if(scancode==90) return  2;
if(scancode==91) return  3;
if(scancode==92) return  4;
if(scancode==93) return  5;
if(scancode==94) return  6;
if(scancode==95) return  7;
if(scancode==96) return  8;
if(scancode==97) return  9;
if(scancode==98) return  0;
/*
if(scancode==88) return 88;//enter tusunun scancode karsÃ½lÃ½gÃ½
if(scancode==40) return 40;//enter tusunun scancode karsÃ½lÃ½gÃ½
//42:sdl_scancodeda silme tusunun karsÃ½lÃ½gÃ½
*/
else return -1;
}

int sayi_cevir(int dizi[],int *sayac){
int toplam=0;
int i;
int n=(*sayac)-1;

for(i=n;i>=0;i--){
   toplam+=dizi[i]*pow(10,(n-i));
}
*sayac=0;
return toplam;
}
int OnInit(){   /**OnInit() fonksiyonu  http://www.grhmedia.com/view_SDL210.html sitesindeki  c++ kodlarından  C ye çevrilmiştir*/
if(SDL_Init(SDL_INIT_EVERYTHING)<0){
    return 0;
}
window = SDL_CreateWindow("SDL_Pencerem",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        550, 480,
                        0);
if(window==NULL){
    return 0;
}
renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
SDL_SetRenderDrawColor(renderer, 160, 200, 200, 160);
if(renderer==NULL){
    return 0;
}
if(TTF_Init()==-1){
    return 0;
}
return 1;
}
int LoadContent(){  /**LoadContent() fonksiyonu  http://www.grhmedia.com/view_SDL210.html sitesindeki  c++ kodlarından  C ye çevrilmiştir*/
font=TTF_OpenFont("Tahoma.ttf",20);
if(font==NULL){
    return 0;
}
LineHeight=TTF_FontLineSkip(font);
return 1;
}
void Onloop(){/**Onloop() fonksiyonu  http://www.grhmedia.com/view_SDL210.html sitesindeki  c++ kodlarından  C ye çevrilmiştir*/
        char *p=malloc(20*sizeof(char));
        p="(4-16) boyutunda matrisin boyutunu giriniz(N):";
        message=TTF_RenderText_Solid(font,p,textColor);
        text=SDL_CreateTextureFromSurface(renderer,message);
        SDL_FreeSurface(message);
        message1=TTF_RenderText_Solid(font,"matris elemanlarini giriniz:",textColor);
        text1=SDL_CreateTextureFromSurface(renderer,message1);
        SDL_FreeSurface(message1);
        message2=TTF_RenderText_Solid(font,"Hadamard Matris Icin: 1 // MDS Matris Icin 2'ye Basin:",textColor);
        text2=SDL_CreateTextureFromSurface(renderer,message2);
        SDL_FreeSurface(message2);
        message3=TTF_RenderText_Solid(font,"Simetrik Matris Icin:3 // Dairesel Matris Icin 4'e Basin:",textColor);
        text3=SDL_CreateTextureFromSurface(renderer,message3);
        SDL_FreeSurface(message3);



}
void Cleanup(){/**Cleanup() fonksiyonu  http://www.grhmedia.com/view_SDL210.html sitesindeki  c++ kodlarından  C ye çevrilmiştir*/
TTF_CloseFont(font);
SDL_FreeSurface(message);
SDL_DestroyTexture(text);
SDL_FreeSurface(message2);
SDL_DestroyTexture(text2);
SDL_FreeSurface(message3);
SDL_DestroyTexture(text3);
SDL_FreeSurface(message1);
SDL_DestroyTexture(text1);
SDL_DestroyTexture(background);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
}
void OnRender(){/**OnRender() fonksiyonu  http://www.grhmedia.com/view_SDL210.html sitesindeki  c++ kodlarından  C ye çevrilmiştir*/
int w=0,h=0;
SDL_RenderClear(renderer);
SDL_RenderCopy(renderer, background, &rectBackground, &displayRect);

        SDL_QueryTexture(text,NULL,NULL,&w,&h);
        textRect.w=w;textRect.h=h;textRect.x=0;textRect.y=0;
        SDL_RenderCopy(renderer,text,NULL,&textRect);
        SDL_DestroyTexture(text);
        SDL_QueryTexture(text1,NULL,NULL,&w,&h);
        textRect1.w=w;textRect1.h=h;textRect1.x=0;textRect1.y=35;
        SDL_RenderCopy(renderer,text1,NULL,&textRect1);
        SDL_DestroyTexture(text1);
        SDL_QueryTexture(text2,NULL,NULL,&w,&h);
        textRect2.w=w;textRect2.h=h;textRect2.x=0;textRect2.y=70;
        SDL_RenderCopy(renderer,text2,NULL,&textRect2);
        SDL_DestroyTexture(text2);
        SDL_QueryTexture(text3,NULL,NULL,&w,&h);
        textRect3.w=w;textRect3.h=h;textRect3.x=0;textRect3.y=105;
        SDL_RenderCopy(renderer,text3,NULL,&textRect3);
        SDL_DestroyTexture(text3);
       SDL_RenderPresent(renderer);
}
void sayi_al(SDL_Event *Event){
   if(Event->type == SDL_QUIT) {
           Running=0;
           }
    if(Event->type==SDL_KEYDOWN)
    {

        //int letter=Event->key.keysym.scancode;
        //printf("%d..........\n",letter);
         switch(Event->key.keysym.scancode)
      {
    case 88://enter'Ä±n scancode karsiligi
        {
          sayi=sayi_cevir(dizi,&sayac);
          sayac1++;

          if(sayac1==1) {
            N=sayi;
             printf("\nN:%d\n",N);
            printf("sayac:%d\n",sayac1);

          }
          if(sayac1>=2&&sayac1<=N*N+1){
           printf("\nsayi[%d]:%d\n",sayac1-2,sayi);
           fprintf(dosya,"%-3d ",sayi);
          if((sayac1-1)%N==0) fputc('\n',dosya);
          }
         if(sayac1==N*N+1) Running=0;
          break;
        }
    case 40://enter'Ä±n scancode karsiligi
        {
          sayi=sayi_cevir(dizi,&sayac);
          sayac1++;
          if(sayac1==1) {
            N=sayi;
            printf("\nN:%d\n",N);
          }
          if(sayac1>=2&&sayac1<=N*N+1){
           printf("\nsayi[%d]:%d\n",sayac1-2,sayi);
           fprintf(dosya,"%-3d ",sayi);
          if((sayac1-1)%N==0) fputc('\n',dosya);
          }
         if(sayac1==N*N+1) Running=0;
          break;
        }


    default:
        {
        if(Event->key.keysym.scancode!=42){
        sayi=numaraya_cevir(Event->key.keysym.scancode);
        printf("%d",sayi);
        dizi[sayac]=sayi;
        sayac++;
        break;
        }
      if(Event->key.keysym.scancode==42){//silme tusunun scancode karsÄ±lÄ±ÄŸÄ±
           sayac--;
           dizi[sayac]=sayi;
           break;
        }
        }
      }

    }
    }
int  Grafik_ekrani(){
if(OnInit()==0) return 0;
if(LoadContent()==0) return 0;
while(Running){
   while(SDL_PollEvent(&Event)){
     sayi_al(&Event);
     }

Onloop();
OnRender();
}

Cleanup();

return 0;
}

void dosyalari_temizle(int secim){
if(secim==1){//hadamard txt haric diğer dosyaları temizler
    FILE *dosya=fopen("mds.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fclose(dosya);
    dosya=fopen("simetrik.txt","w");
     if(dosya==NULL){
        printf("dosya acilamadi");
     }
    fclose(dosya);
    dosya=fopen("dairesel.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fclose(dosya);
}
if(secim==2){//mds haric diğer dosyaları temizler
    FILE *dosya=fopen("hadamard.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fclose(dosya);
    dosya=fopen("simetrik.txt","w");
     if(dosya==NULL){
        printf("dosya acilamadi");
     }
    fclose(dosya);
    dosya=fopen("dairesel.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fclose(dosya);
}
if(secim==3){//simetrik haric siler
    FILE *dosya=fopen("mds.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fclose(dosya);
    dosya=fopen("hadamard.txt","w");
     if(dosya==NULL){
        printf("dosya acilamadi");
     }
    fclose(dosya);
    dosya=fopen("dairesel.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fclose(dosya);
}
if(secim==4){//dairesel haric diğer dosyaların içini siler
    FILE *dosya=fopen("mds.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fclose(dosya);
    dosya=fopen("simetrik.txt","w");
     if(dosya==NULL){
        printf("dosya acilamadi");
     }
    fclose(dosya);
    dosya=fopen("hadamard.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fclose(dosya);
}
}

int main(int argc,char *args[]){
   dosya=fopen("C:\\Users\\casper\\Desktop\\matris_rehberi\\matris.txt","w");
 if(dosya==NULL){
        printf("dosya acilamadi!");
        exit(1);
    }
    Grafik_ekrani();
fclose(dosya);
int secim;
int eleman;
int i,j;//matrisin satýr ve sütunu
int *girilen_matris;

   printf("hadamard matris icin:1\n");
   printf("mds matris icin:2\n");
   printf("simetrik matris icin:3\n");
   printf("dairesel matris icin:4\n");
    scanf("%d",&secim);


   switch(secim){

   case 1:
       {
       do{
     if(N==4||N==8||N==16){
        girilen_matris=malloc(N*N*sizeof(int));
        dosyadan_oku(N,girilen_matris);
    if(hadamard_mi(girilen_matris,N)==1){
    FILE *dosya=fopen("hadamard.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fprintf(dosya,"hadamard matristir\n");
    fclose(dosya);
    }
   else  {
     FILE *dosya=fopen("hadamard.txt","w");
     if(dosya==NULL){
        printf("dosya acilamadi");
     }
    fprintf(dosya,"hadamard degildir\n");
    fclose(dosya);
   }
   alt_matris(girilen_matris,N,secim);
   free(girilen_matris);
     }

   else {
    printf("hadamard matris icin boyutu lutfen 4-8-16 giriniz:");
    scanf("%d",&N);
    girilen_matris=malloc(N*N*sizeof(int));
    dosya=fopen("C:\\Users\\casper\\Desktop\\matris_rehberi\\matris.txt","w");
    if(dosya==NULL){
        printf("dosya acilamadi!");
        exit(1);
    }
     for(i=0;i<N;i++){
        printf("%d.satiri giriniz:\n",i+1);
        for(j=0;j<N;j++){
          scanf("%d",&eleman);
          fprintf(dosya,"%-3d ",eleman);//sola dayalý 3 basamak sýðacak kadar yer ayýrýr
        }
        fputc('\n',dosya);
     }
     fclose(dosya);


     }


   }while(N!=4&&N!=8&&N!=16);

     break;
    }
   case 2:
    {
      girilen_matris=malloc(N*N*sizeof(int));
      dosyadan_oku(N,girilen_matris);
    if(mds_matris_mi(girilen_matris,N)==1){
    FILE *dosya=fopen("mds.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fprintf(dosya,"mds matristir\n");
    fclose(dosya);
    }
   else  {
     FILE *dosya=fopen("mds.txt","w");
     if(dosya==NULL){
        printf("dosya acilamadi");
     }
    fprintf(dosya,"mds matris degildir\n");
    fclose(dosya);
   }
   alt_matris(girilen_matris,N,secim);
   free(girilen_matris);
      break;
    }
   case 3:
    {
    girilen_matris=malloc(N*N*sizeof(int));
    dosyadan_oku(N,girilen_matris);
    if(simetrik_mi(girilen_matris,N)==1){
    FILE *dosya=fopen("simetrik.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fprintf(dosya,"simetrik matristir\n");
    fclose(dosya);
    }
   else  {
     FILE *dosya=fopen("simetrik.txt","w");
     if(dosya==NULL){
        printf("dosya acilamadi");
     }
    fprintf(dosya,"simetrik matris degildir\n");
    fclose(dosya);
   }
   alt_matris(girilen_matris,N,secim);
   free(girilen_matris);
        break;
    }
  case 4:
    {
    girilen_matris=malloc(N*N*sizeof(int));
    dosyadan_oku(N,girilen_matris);
    if(dairesel_mi(girilen_matris,N)==1){
    FILE *dosya=fopen("dairesel.txt","w");
      if (dosya==NULL){
        printf("dosya acilamadi");
        exit(1);
      }
    fprintf(dosya,"dairesel matristir\n");
    fclose(dosya);
    }
   else  {
     FILE *dosya=fopen("dairesel.txt","w");
     if(dosya==NULL){
        printf("dosya acilamadi");
     }
    fprintf(dosya,"dairesel matris degildir\n");
    fclose(dosya);
   }
   alt_matris(girilen_matris,N,secim);
   free(girilen_matris);
        break;
    }

}
dosyalari_temizle(secim);

return 0;
}
void dosyadan_oku(int N,int *matris){
FILE *dosya;
int i,j;
dosya=fopen("C:\\Users\\casper\\Desktop\\matris_rehberi\\matris.txt","r");
//dosya=fopen("matris.txt","r");
if(dosya==NULL){
printf("dosya acilamadi!\n");
}

while(!feof(dosya)){
   for(i=0;i<N;i++){
    for(j=0;j<N;j++){
    fscanf(dosya,"%d",&matris[i*N+j]);
    }
   }
}
fclose(dosya);
}

int hadamard_mi(int *matris,int N){
int i=0,j,n,m;
int sayac;

for(i=0;i<N;i=i+2){
    for(j=0;j<N;j++){
        if(matris[i*N+j]!=matris[(i+1)*N+(j+1)]) return 0;
        j++;
        if(matris[i*N+j]!=matris[(i+1)*N+(j-1)]) return 0;
    }
}

n=N/2;
while(n>=2){
    for(i=0;i<N;i+=2*n){
        for(j=0;j<N;j++){
            for(sayac=0;sayac<n;sayac++){
                m=i;
                if(matris[i*N+j]!=matris[(i+n)*N+(j+n)]) return 0;
                  m++;
                if(matris[(m)*N+j]!=matris[(m+n)*N+(j+n)]) return 0;
                j++;
            }
            for(sayac=0;sayac<n;sayac++){
                m=i;
                if(matris[i*N+j]!=matris[(i+n)*N+(j-n)]) return 0;
                 m++;
                if(matris[m*N+j]!=matris[(m+n)*N+(j-n)]) return 0;
                j++;
            }

            j--;
        }
    }
    n=n/2;
}
return 1;
}
void dosyaya_had_altmatris_yaz(int *matris,int N){
 FILE *dosya;
 dosya=fopen("hadamard.txt","a");
    if(dosya==NULL){
    printf("dosya acilmadi\n");
    exit(1);
    }
    int i,j;
    fprintf(dosya,"%c",'\n');
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
        fprintf(dosya,"%-3d",matris[i*N+j]);
        }
    fprintf(dosya,"%c",'\n');
    }

fclose(dosya);
}
void dosyaya_mds_altmatris_yaz(int *matris,int N){
 FILE *dosya;
 dosya=fopen("mds.txt","a");
    if(dosya==NULL){
    printf("dosya acilmadi\n");
    exit(1);
    }
    int i,j;
    fprintf(dosya,"%c",'\n');
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
        fprintf(dosya,"%-3d",matris[i*N+j]);
        }
    fprintf(dosya,"%c",'\n');
    }

fclose(dosya);
}
void dosyaya_sim_altmatris_yaz(int *matris,int N){
FILE *dosya;
 dosya=fopen("simetrik.txt","a");
    if(dosya==NULL){
    printf("dosya acilmadi\n");
    exit(1);
    }
    int i,j;
    fprintf(dosya,"%c",'\n');
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
        fprintf(dosya,"%-3d",matris[i*N+j]);
        }
    fprintf(dosya,"%c",'\n');
    }

fclose(dosya);

}
void dosyaya_dai_altmatris_yaz(int *matris,int N){
 FILE *dosya;
 dosya=fopen("dairesel.txt","a");
    if(dosya==NULL){
    printf("dosya acilmadi\n");
    exit(1);
    }
    int i,j;
    fprintf(dosya,"%c",'\n');
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
        fprintf(dosya,"%-3d",matris[i*N+j]);
        }
    fprintf(dosya,"%c",'\n');
    }

fclose(dosya);
}
void alt_matris(int *ptr,int N,int secim){
int n=N-1;//alt matris boyutu
int k,i,j,t,m,p;
   while(n>=2){
int *matris=malloc(n*n*sizeof(int));
 for(k=0;k<N-(n-1);k++){
    t=k;
    for(m=0;m<N-(n-1);m++){
        p=m;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
            matris[j*n+i]=ptr[k*N+m];
            k++;
            }
            k=t;
            m++;

        }
        m=p;
  if(secim==1){
   if(n==2||n==4||n==8||n==16){
    if (hadamard_mi(matris,n)==1)
    dosyaya_had_altmatris_yaz(matris,n);
   }
  }
  if(secim==2){
   if(mds_matris_mi(matris,n)==1){
    dosyaya_mds_altmatris_yaz(matris,n);
        }
   }
   if(secim==3){
   if(simetrik_mi(matris,n)==1){
    dosyaya_sim_altmatris_yaz(matris,n);
        }
   }
   if(secim==4){
   if(dairesel_mi(matris,n)==1){
    dosyaya_dai_altmatris_yaz(matris,n);
        }
   }
    }
 }

free(matris);
n--;

}
}
int determinant(int *matris){
int det;
det=(matris[0]*matris[3]-matris[1]*matris[2]);
return det;
}
int chio_yontemi(int *ptr,int N)
{
int i,j;
float kat_sayi,carpim=1;
int *matris=malloc(4*sizeof(int));//chýo yönteminde matris 2*2 liklere ayrýlýk determinantlarý bulunur böylece matris her kademede bir kücülür
int *yeni_matris=malloc((N-1)*(N-1)*sizeof(int));
int n;//indirgenmis matrisin boyutu//yeni_matrisin boyu
n=N-1;
while(n>=2){
   kat_sayi=1/pow(ptr[0],(N-2));
   carpim*=kat_sayi;
   matris[0]=ptr[0];
   for(i=1;i<N;i++){
    for(j=1;j<N;j++){
        matris[0*2+1]=ptr[0*N+i];
        matris[1*2+0]=ptr[j*N+0];
        matris[1*2+1]=ptr[j*N+i];
    yeni_matris[(j-1)*n+(i-1)]=determinant(matris);
    }
   }
   N--;
   n--;
   ptr=malloc(N*N*sizeof(int));
   ptr=yeni_matris;
   yeni_matris=malloc(n*n*sizeof(int));

}
int det=determinant(ptr);
free(yeni_matris);
free(matris);
free(ptr);
if(carpim*det==0) return 0;
return 1;

}
int mds_matris_mi(int *ptr,int N){
int n=N;//alt matris boyutu
int k,i,j,t,m,p;
   while(n>=2){
int *matris=malloc(n*n*sizeof(int));
 for(k=0;k<N-(n-1);k++){
    t=k;
    for(m=0;m<N-(n-1);m++){
        p=m;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
            matris[j*n+i]=ptr[k*N+m];
            k++;
            }
            k=t;
            m++;

        }
        m=p;
      if(chio_yontemi(matris,n)==0) return 0;

    }
 }

free(matris);
n--;

}
return 1;
}
int simetrik_mi(int *matris,int N){
int i,j;
for(i=0;i<N;i++){
    for(j=0;j<N;j++){
        if(i!=j){
            if(matris[i*N+j]!=matris[j*N+i]) return 0;
        }
    }
}
return 1;
}
int dairesel_mi(int *matris,int N){
int i,m,j;
m=N-1;
int *ptr=malloc(N*N*sizeof(int));
ptr=matris;
for(j=1;j<N;j++){
    for(i=0;i<N;i++){
        if(matris[j*N+i]==ptr[0*N+m]){
            if(m==(N-1)) m=0;
            else  m++;
        }
        else return 0;
    }
    m--;//i döngüsünden çýktýktan sonraki bir fazla olan degeri azalttýk

}
free(ptr);
free(matris);
return 1;
}
