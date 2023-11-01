#ifndef propagasi_balik_C
#define propagasi_balik_C

#include "propagasi_balik.h"
#include <stdlib.h>
#include <math.h>

/* Kamus Global */

tjaringan jaringan;   /* parameter jaringan */
tpelatihan_sinyal pelatihan_sinyal; /* parameter pelatihan */
float * delta;       /* gradien pelatihan */

float sigmoid(float x)
{
  /* Fungsi mengubah nilai real menjadi nilai
     antara 0 dan 1
     K.Awal  : x berisi nilai real
     K.Akhir : fungsi menghasilkan nilai antara
               0 dan 1
  */

  /* Algoritma */
  if(x<-50.0)   /* x < -50*/
  {
    return 0.0;
  }
  else if (x>50.0) /* x > 50*/
  {
    return 1.0;
  }
  else /*-50 <= x <= 50*/
  {
    return (float)(1/(1+exp(-(double)x)));
  }
}

void alokasi_jaringan()
{
  /* melakukan alokasi memori pada parameter-parameter jaringan
     K.Awal  : parameter panjang jaringan berisi nilai
     K.Akhir : parameter -parameter jaringan dialokasi
  */

  /* Kamus Lokal */
  int i,pj_total;

  /* Algoritma */
  pj_total=jaringan.pj_in+jaringan.pj_hid+jaringan.pj_out;
  jaringan.O =(float *)malloc((pj_total+1)*sizeof(float));
  jaringan.T =(float *)malloc((jaringan.pj_out+1)*sizeof(float));
  jaringan.W =(float **)malloc((jaringan.pj_hid+jaringan.pj_out+1)*sizeof(float*));
  for(i=1;i<=jaringan.pj_hid+jaringan.pj_out;i++)
  {
    jaringan.W[i] =(float *)malloc((pj_total+1)*sizeof(float));
  }
  jaringan.th =(float *)malloc((jaringan.pj_hid+jaringan.pj_out+1)*sizeof(float));
  delta =(float *)malloc((jaringan.pj_hid+jaringan.pj_out+1)*sizeof(float));
}

void dealokasi_jaringan()
{
  /* melakukan dealokasi memori pada parameter-parameter jaringan
     K.Awal  : parameter-parameter jaringan telah dialokasi
     K.Akhir : parameter-parameter jaringan didealokasi
  */

  /* Kamus Lokal */
  int i;

  /* Algoritma */
  for(i=1;i<=jaringan.pj_hid+jaringan.pj_out;i++)
  {
    free(jaringan.W[i]);
  }
  free(jaringan.W);
  free(jaringan.O);
  free(jaringan.T);
  free(jaringan.th);
  free(delta);
}

void alokasi_pelatihan()
{
  /* melakukan alokasi memori pada parameter-parameter pelatihan
     K.Awal  : parameter panjang pelatihan dan jaringan
               berisi nilai
     K.Akhir : parameter -parameter pelatihan dialokasi
  */

  /* Kamus Lokal */
  int i;

  /* Algoritma */
  pelatihan_sinyal.X=(float **)malloc((pelatihan_sinyal.pj_pelatihan+1)*sizeof(float*));
  pelatihan_sinyal.T=(float **)malloc((pelatihan_sinyal.pj_pelatihan+1)*sizeof(float*));
  for(i=1;i<=pelatihan_sinyal.pj_pelatihan;i++)
  {
    pelatihan_sinyal.X[i]=(float *)malloc((jaringan.pj_in+1)*sizeof(float));
    pelatihan_sinyal.T[i]=(float *)malloc((jaringan.pj_out+1)*sizeof(float));
  }
}
void dealokasi_pelatihan()
{
  /* melakukan dealokasi memori pada parameter-parameter pelatihan
     K.Awal  : parameter-parameter pelatihan telah dialokasi
     K.Akhir : parameter-parameter pelatihan didealokasi
  */

  int i;
  for(i=1;i<=pelatihan_sinyal.pj_pelatihan;i++)
  {
    free(pelatihan_sinyal.X[i]);
    free(pelatihan_sinyal.T[i]);
  }
  free(pelatihan_sinyal.X);
  free(pelatihan_sinyal.T);
}


void inisialisasi_penimbang_dan_bias()
{
  /* melakukan inisialisasi pada penimbang dan bias unit
     K.Awal  : parameter jaringan telah berisi nilai
     K.Akhir : penimbang (jaringan.W) dan bias (jaringan.th)
               berisi nilai antara 0 dan 1
  */

  /* Kamus Lokal */
  int i,j;

  /* Algoritma */
  for(i=1;i<=jaringan.pj_out+jaringan.pj_hid;i++)
  {
    for(j=1;j<=jaringan.pj_out+jaringan.pj_hid+jaringan.pj_in;j++)
    {
      jaringan.W[i][j]=0.001;
    }
    jaringan.th[i]=0.002;
  }
}

float  aktivasi_node(int p,int q,int node)
{
  /* melakukan proses aktivasi untuk setiap node
     K.Awal  : nomor node,posisi awal dan akhir dari
               jaringan yang menuju ke node sudah
               bernilai  
     K.Akhir : diperoleh nilai aktifasi node
  */

  /* Kamus Lokal */
  int i;
  float Sum;

  /* Algoritma */
  Sum=0.0;
  for(i=p;i<=q;i++)
  {

    Sum=Sum+((jaringan.W[node][i])*(jaringan.O[i]));
  }
  return(Sum-jaringan.th[node]);
}

void aktivasi_jaringan()
{
  /* melakukan proses aktivasi untuk seluruh jaringan
     K.Awal  : parameter input, penimbang dan bias sudah
               berisi nilai
     K.Akhir : diperoleh nilai aktivasi seluruh jaringan
  */

  /* Kamus Lokal */
  int i;

  /* Algoritma */
  /* Aktivasi Untuk Layer Hidden */
  for(i=jaringan.pj_out+1;i<=jaringan.pj_out+jaringan.pj_hid;i++)
  {          
    jaringan.O[i]=sigmoid(aktivasi_node(jaringan.pj_out+jaringan.pj_hid+1,
                          jaringan.pj_out+jaringan.pj_hid+jaringan.pj_in,i));
  }

  /* Aktivasi Untuk Layer Output */
  for(i=1;i<=jaringan.pj_out;i++)
  {          
    jaringan.O[i]=sigmoid(aktivasi_node(jaringan.pj_out+1,jaringan.pj_out+
                          jaringan.pj_hid+jaringan.pj_in,i));
  }
}

void  pelatihan_node(char IsOut,int node)
{
  /* proses pelatihan untuk setiap node
     K.Awal  : penimbang dan bias node sudah diinisialisasi
     K.Akhir : penimbang dan bias node telah dilakukan
               pelatihan

  */

  /* Kamus Lokal */
  int i,From,To;
  float mudlt,delout,sumdel;

  /* Algoritma */
  delout=jaringan.O[node]*(1.0-jaringan.O[node]);
  if(IsOut) /* Menghitung delta untuk layer output */
  {
    From=jaringan.pj_out+1;
    To=jaringan.pj_out+jaringan.pj_hid+jaringan.pj_in;
    delta[node]=delout*(jaringan.T[node]-jaringan.O[node]);
  }
  else /* Menghitung delta untuk layer hidden */
  {
    From=jaringan.pj_out+jaringan.pj_hid+1;
    To=jaringan.pj_out+jaringan.pj_hid+jaringan.pj_in;

    sumdel=0.0;
    for(i=1;i<=jaringan.pj_out;i++)
    {
      sumdel=sumdel+delta[i]*jaringan.W[i][node];
    }
    delta[node]=delout*sumdel;
  }

  /* Proses pelatihan node */
  mudlt=jaringan.lr*delta[node];
  for(i=From;i<=To;i++)
  {
    jaringan.W[node][i]=jaringan.W[node][i]+mudlt*jaringan.O[i];
  }
  jaringan.th[node]=-(-jaringan.th[node]+mudlt);
}

void pelatihan_jaringan()
{
  /* proses pelatihan untuk seluruh jaringan
     K.Awal  : penimbang dan bias seluruh jaringan
               telah diinisialisasi
     K.Akhir : penimbang dan bias seluruh jaringan
               telah dilakukan pelatihan
  */

  /* Kamus Lokal */
  int j;

  /* Algoritma */
  /* pelatihan untuk layer output */
  for(j=1;j<=jaringan.pj_out;j++)
  {
    pelatihan_node(1,j);
  }
  
  /* pelatihan untuk layer hidden */
  for(j=jaringan.pj_out+1;j<=jaringan.pj_out+jaringan.pj_hid;j++)
  {
    pelatihan_node(0,j);
  }
}

float proses_semua_pelatihan()
{
  /* seluruh data input target dan target dilakukan proses
     pelatihan dan diperoleh MSE(Mean Suquare Error)
     K.Awal  : semua input target,target,banyaknya data untuk
               pelatihan dan parameter jaringan telah berisi
               nilai
     K.Akhir : seluruh input target dan target telah dilakukan
               pelatihan dengan MSE yang dihasilkan
  */
  
  /* Kamus Lokal */
  int i,j;  float sum,meansum;

  /* Algoritma */
  meansum=0.0;

  for(i=1;i<=pelatihan_sinyal.pj_pelatihan;i++) /* data pelatihan ke i*/
  {
    /* seluruh input target dan target diisikan untuk data ke i*/
    for(j=1;j<=jaringan.pj_out;j++)
    {
      jaringan.T[j]=pelatihan_sinyal.T[i][j];
    }
    for(j=1;j<=jaringan.pj_in;j++)
    {
      jaringan.O[jaringan.pj_hid+ jaringan.pj_out+j]=pelatihan_sinyal.X[i][j];
    }

    /* lakukan aktivasi seluruh jaringan untuk data ke i*/
    aktivasi_jaringan();
    
    /* hitung Mean Square Error untuk data ke i*/
    sum=0.0;
    for(j=1;j<=jaringan.pj_out;j++)
    {
      sum=sum+(jaringan.T[j]-jaringan.O[j])*(jaringan.T[j]-jaringan.O[j]);
    }
    sum=sum/2;
    /* lakukan pelatihan seluruh jaringan untuk data ke i*/
    pelatihan_jaringan();

    /* hitung jumlah seluruh error */
    meansum=meansum+sum;
  }
  return meansum;

}
#endif


