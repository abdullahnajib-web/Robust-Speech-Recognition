#ifndef StandarIO_C
#define StandarIO_C

#include "StandarIO.h"
#include <stdio.h>



void matrik_ke_vektor(float **x,unsigned l,unsigned m,float *y,unsigned *n)
{
  /* mengubah nilai matrix menjadi vektor dengan panjang matrix tiap
     baris dimulai dari 0 sampai m-1
     K.Awal  : matrix x dengan pajang dan lebar masing-masing
               l x m sudah diisikan nilai
     K.Akhir : vektor y berisi nilai dari matrix x dengan panjang
               n = l x m
  */

  /* Kamus Lokal */
  unsigned l1,m1,k;

  /* Algotirm */
  k=0;
  for(l1=0;l1<l;l1++)
  {
    for(m1=0;m1<m;m1++)
    {
      y[k]=x[l1][m1];
      k++;
    }
  }
  *n=k;
}

void matrik_ke_vektor1(float **x,unsigned l,unsigned m,float *y,unsigned *n)
{
  /* mengubah nilai matrix menjadi vektor dengan panjang matrix tiap
     baris dimulai dari 1 sampai m
     K.Awal  : matrix x dengan pajang dan lebar masing-masing
               l x m sudah diisikan nilai
     K.Akhir : vektor y berisi nilai dari matrix x dengan panjang
               n = l x m

  */

  /* Kamus Lokal */
  unsigned l1,m1,k;

  /* Algoritma */
  k=0;
  for(l1=0;l1<l;l1++)
  {
    for(m1=1;m1<=m;m1++)
    {
      y[k]=x[l1][m1];
      k++;
    }
  }
  *n=k;
}

void salin_vektor(float * DestBuf,float *SrcBuf,unsigned len)
{
  /* menyalin nilai vektor
     K.Awal  : vektor sumber atau vektoryang akan disalin (SrcBuf)
               dengan panjang len sudah berisi nilai
     K.Akhir : vektor tempat penyalinan (DestBuf) sudah berisi nilai
               vektor sumber
  */

  /* Kamus Lokal */
  unsigned i;

  /* Algoritma */
  for(i=0;i<len;i++)
  {
    DestBuf[i]=SrcBuf[i];
  }
}

void salin_matrik(float **DestBuf,float **SrcBuf,unsigned lenx,unsigned leny)
{
  /* menyalin nilai matrix
     K.Awal  : matrix sumber atau matrix yang akan disalin (SrcBuf)
               dengan panjang lenx x leny sudah berisi nilai
     K.Akhir : matrix tempat penyalinan (DestBuf) sudah berisi nilai
               matrix sumber
  */

  /* Kamus Lokal */
  unsigned i,j;

  /* Algoritma */
  for(i=0;i<lenx;i++)
  {
    for(j=0;j<leny;j++)
    {
      DestBuf[i+1][j+1]=SrcBuf[i][j];
    }
  }
}

void baca_file_wave(float * Buf,unsigned *len,char * NamaFile)
{
  /* membaca file dengan format wave
     K.Awal  : file dengan format wave sudah ada dengan
               nama NamaFile
     K.Akhir : buffer (Buf) akan berisi nilai - nilai
               sinyal file wave dengan panjan len
  */

  /* Kamus Lokal */
  FILE *file;
  unsigned char CC;
  int retval;
  unsigned i;

  /* Algoritma */
  file = fopen(NamaFile,"r");
  fseek(file,46L,SEEK_SET);
  retval = fscanf(file,"%c",&CC);
  i=0;
  while(EOF != retval)
  {
    Buf[i]=(float)CC-128.0;
    i++;
    retval = fscanf(file,"%c",&CC);
  }
  *len=i-1;
  fclose(file);
}

void baca_file(float * Buf,unsigned *len,char * NamaFile)
{
  /* membaca suatu file 
     K.Awal  : file sudah ada dengan nama NamaFile
     K.Akhir : buffer (Buf) akan berisi nilai - nilai
               file dengan panjan len
  */

  /* Kamus Lokal */
  FILE *file;
  float CF;
  int retval;
  unsigned i;

  /* Algoritma */
  file = fopen(NamaFile,"r");
  retval = fscanf(file,"%f\n",&CF);
  *len=(unsigned)CF;
  i=0;
  retval = fscanf(file,"%f\n",&CF);
  while(EOF != retval)
  {
    Buf[i]=CF;
    i++;
    retval = fscanf(file,"%f\n",&CF);
  }
  fclose(file);
}

void tulis_file(float * Buf,unsigned len,char * NamaFile)
{
  /* menuliskan suatu file 
     K.Awal  : buffer dengan panjang len sudah berisi
               data dan nama file NamaFile sudah di -
               tentukan
     K.Akhir : file dengan nama NamaFile sudah berisi
               data
  */

  /* Kamus Lokal */
  FILE *file;
  float CF;
  unsigned int i;

  /* Algoritma */
  file = fopen(NamaFile,"w");
  CF=(float)len;
  fprintf(file,"%4.18f\n",CF);

  for(i=0;i<len;i++)
  {
    CF=Buf[i];
    fprintf(file,"%4.18f\n",CF);
  }
  fclose(file);

}
#endif

