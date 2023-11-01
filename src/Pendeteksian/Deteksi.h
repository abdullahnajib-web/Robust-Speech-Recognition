#ifndef DeteksiH
#define DeteksiH

unsigned rata2_energi(float **buf,unsigned L,unsigned N);
/* mencari posisi frame yang berisi informasi sinyal
   yang diinginkan dengan metode energi
   K.Awal  : buf sudah berisi nilai dengan panjang frame
             L dan panjang sinyal tiap frame N
   K.Akhir : posisi frame dihasilkan
*/

float    korelasi_diri(unsigned l,unsigned len,float *buf);
/* menghitung korelasi diri dengan pergeseran l 
   K.Awal  : buffer (buf) data yang akan dilakukan korelasi
             diri sudah berisi nilai dengan panjang len dan
             pergeseran l <= len/4
   K.Akhir : diperoleh nilai korelasi diri dengan pergeseran l
*/

unsigned periodicity(float **buf,unsigned L,unsigned N);
/* mencari posisi frame yang berisi informasi sinyal
   yang diinginkan dengan metode periodicity
   K.Awal  : buf sudah berisi nilai dengan panjang frame
             L dan panjang sinyal tiap frame N
   K.Akhir : posisi frame dihasilkan
*/

float    variansi(float **Buf,unsigned L,unsigned N,unsigned frm_mulai);
/*  menghitung variansi sinyal
    K.Awal  : sinyal (Buf) dengan panjang frame L dengan
              frame awal adalah frm_mulai dan panjang sinyal
              tiap frame N berisi nilai
    K.Akhir : diperoleh variansi sinyal
*/

unsigned MLR(float **Buf2,unsigned L2,float **Buf1,unsigned L1,unsigned N);
/* mencari posisi frame yang berisi informasi sinyal
   yang diinginkan dengan metode Maximum Likelihood
   Ratios (MLR)
   K.Awal  : buf sudah berisi nilai dengan panjang frame
             L dan panjang sinyal tiap frame N
   K.Akhir : posisi frame dihasilkan
*/

#endif
