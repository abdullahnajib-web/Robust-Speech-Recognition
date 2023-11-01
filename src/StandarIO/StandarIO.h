#ifndef StandarIO_H
#define StandarIO_H

void matrik_ke_vektor(float **x,unsigned l,unsigned m,float *y,unsigned *n);
/* mengubah nilai matrix menjadi vektor dengan panjang matrix tiap
   baris dimulai dari 0 sampai m-1
   K.Awal  : matrix x dengan pajang dan lebar masing-masing
             l x m sudah diisikan nilai
   K.Akhir : vektor y berisi nilai dari matrix x dengan panjang
             n = l x m
*/

void matrik_ke_vektor1(float **x,unsigned l,unsigned m,float *y,unsigned *n);
/* mengubah nilai matrix menjadi vektor dengan panjang matrix tiap
   baris dimulai dari 1 sampai m
   K.Awal  : matrix x dengan pajang dan lebar masing-masing
             l x m sudah diisikan nilai
   K.Akhir : vektor y berisi nilai dari matrix x dengan panjang
             n = l x m
*/

void salin_vektor(float * DestBuf,float *SrcBuf,unsigned len);
/* menyalin nilai vektor
   K.Awal  : vektor sumber atau vektoryang akan disalin (SrcBuf)
             dengan panjang len sudah berisi nilai
   K.Akhir : vektor tempat penyalinan (DestBuf) sudah berisi nilai
             vektor sumber
*/

void salin_matrik(float **DestBuf,float **SrcBuf,unsigned lenx,unsigned leny);
/* menyalin nilai matrix
   K.Awal  : matrix sumber atau matrix yang akan disalin (SrcBuf)
             dengan panjang lenx x leny sudah berisi nilai
   K.Akhir : matrix tempat penyalinan (DestBuf) sudah berisi nilai
             matrix sumber
*/

void baca_file_wave(float * Buf,unsigned *len,char * NamaFile);
/* membaca file dengan format wave
   K.Awal  : file dengan format wave sudah ada dengan
             nama NamaFile
   K.Akhir : buffer (Buf) akan berisi nilai - nilai
             sinyal file wave dengan panjan len
*/


void baca_file(float * Buf,unsigned *len,char * NamaFile);
/* membaca suatu file 
   K.Awal  : file sudah ada dengan nama NamaFile
   K.Akhir : buffer (Buf) akan berisi nilai - nilai
             file dengan panjan len
*/

void tulis_file(float * Buf,unsigned len,char * NamaFile);
/* menuliskan suatu file 
   K.Awal  : buffer dengan panjang len sudah berisi
             data dan nama file NamaFile sudah di -
             tentukan
   K.Akhir : file dengan nama NamaFile sudah berisi
             data
*/

#endif
