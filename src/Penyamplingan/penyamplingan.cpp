/* File        : penyamplingan.cpp  */
/* Dibuat Oleh : Abdullah  23501002 */
/* Tanggal     : 10-12-2002         */

#ifndef penyamplingan_C
#define penyamplingan_C

#include "penyamplingan.h"
#include <vcl.h>
#include <MMSystem.h>
#include <stdlib.h>

/* Kamus Global */

/* Parameter penyamplingan */
struct parameter_sampling
{
  void *handel;        /* handel penyamplingan */
  unsigned  frekuensi; /* frekuensi sampel dalam proses
                          penyamplingan*/
  unsigned  amplitudo; /* amplitudo dalam proses penyamplingan */
}data_sampling;

tsinyal_digital sinyal_digital; /* sinyal suara yang diperoleh
                                   dari hasil penyamplingan */


void buat_handel_sampling(unsigned long frekuensi_sampel,unsigned short amplitudo)
{
  /* Membuat handel untuk melakukan proses penyamplingan
     K.Awal  :  frekuensi sampel (frekuensi_sampel) dan
                amplitudo (amplitudo) Sudah berisi
                masing-masing banyaknya data tiap detik dan
                besar data maksimum
     K.Akhir :  Handel Penyamplingan (data_sampling.handel) sudah dibuat 
  */

  /* Kamus Lokal */
  WAVEFORMATEX wf;

  /* Algoritma */                    
  data_sampling.frekuensi=frekuensi_sampel;
  data_sampling.amplitudo=amplitudo;
  wf.wFormatTag=WAVE_FORMAT_PCM;
  wf.nChannels=1;
  wf.nSamplesPerSec=frekuensi_sampel;
  wf.wBitsPerSample=amplitudo;
  wf.nBlockAlign=(unsigned short)INT(wf.wBitsPerSample/8);
  wf.nAvgBytesPerSec=(unsigned long)frekuensi_sampel*amplitudo/8;
  waveInOpen(&(data_sampling.handel),0,&wf,0,0,0);
  sinyal_digital.s=(unsigned char*)malloc(8000*sizeof(unsigned char));

}

void sampling(unsigned long waktu)
{
  /* Proses Penyamplingan
     K.Awal  : Handel penyamplingan (data_sampling.handel) sudah
               dibuat dan lama waktu (waktu) penyampingan sudah berisi
     k.Akhir : Diperoleh data hasil penyamplingan yang disimpan
               didalam sinyal.s dengan panjang sinyal sinyal.panjang
  */
  /* Kamus Lokal */
  WAVEHDR wh;

  /* Algoritma */
  wh.dwFlags=0;
  wh.lpData=(char *)sinyal_digital.s;
  sinyal_digital.panjang=(unsigned long)(data_sampling.frekuensi*data_sampling.amplitudo*waktu)/8000;
  wh.dwBufferLength=sinyal_digital.panjang;
  waveInPrepareHeader(data_sampling.handel,&wh,sizeof(wh));
  waveInAddBuffer(data_sampling.handel,&wh,sizeof(wh));
  waveInStart(data_sampling.handel);
  waveInStop(data_sampling.handel);
  waveInReset(data_sampling.handel);

}

void hancur_handel_sampling()
{
  /* Menghancurkan handel penyamplingan
     K.Awal  : Handel Penyamplingan (data_sampling.handel) sudah dibuat
     K.Akhir : Handel Penyamlingan (data_sampling.handel) hancur
  */

  /* Algoritma */
  free(sinyal_digital.s);
  waveInReset(data_sampling.handel);
  waveInClose(data_sampling.handel);
}

#endif
