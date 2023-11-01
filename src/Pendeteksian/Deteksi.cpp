#include "Deteksi.h"
#include <math.h>
#include <stdlib.h>

unsigned rata2_energi(float **buf,unsigned L,unsigned N)
{
  /* mencari posisi frame yang berisi informasi sinyal
     yang diinginkan dengan metode energi
     K.Awal  : buf sudah berisi nilai dengan panjang frame
               L dan panjang sinyal tiap frame N
     K.Akhir : posisi frame dihasilkan
  */

  /* Kamus Lokal */
  unsigned l,n;
  float rata2,rata2_total;

  /* Algoritma */
  /* menghitung rata-rata energi sinyal keseluruhan */
  rata2_total=0.0;
  for(l=0;l<L;l++)
  {
    for(n=0;n<N;n++)
    {
      rata2_total=rata2_total+buf[l][n]*buf[l][n];
    }
  }
  rata2_total=rata2_total/((float)L*(float)N);

  /* menghitung rata-rata energi tiap frame dan dibandingkan
     dengan rata-rata energi sinyal keseluruhan jika sudah
     lebih besar maka berhenti
  */
  l=0;
  do
  {
    rata2=0.0;
    for(n=0;n<N;n++)
    {
      rata2=rata2+buf[l][n]*buf[l][n];
    }
    rata2=rata2/((float)N);
    l++;
  }while((l<=L)&&(rata2<rata2_total));

  return l-1;
}
float korelasi_diri(unsigned l,unsigned len,float *buf)
{
  /* menghitung korelasi diri dengan pergeseran l 
     K.Awal  : buffer (buf) data yang akan dilakukan korelasi
               diri sudah berisi nilai dengan panjang len dan
               pergeseran l <= len/4
     K.Akhir : diperoleh nilai korelasi diri dengan pergeseran l
  */

  /* Kamus Lokal */
  float pem,pen,sum1,sum2,sum3,sum4,sum5;
  unsigned i;

  /* Algoritma */
  sum4=0.0;
  sum5=0.0;
  for(i=0;i<len;i++)
  {
    sum4=sum4+buf[i];
    sum5=sum5+buf[i]*buf[i];
  }

  pen=len*sum5-sum4*sum4;
  pen=pen/(len*(len-1));

  sum1=0.0;
  sum2=0.0;
  sum3=0.0;
  for(i=l;i<len;i++)
  {
    sum1=sum1+buf[i]*buf[i-l];
    sum2=sum2+buf[i];
    sum3=sum3+buf[i-l];
  }
  pem=(len-l)*sum1-sum2*sum3;
  pem=pem/((len-1)*(len-l-1));
 
  return pem/pen;
}

unsigned periodicity(float **buf,unsigned L,unsigned N)
{
  /* mencari posisi frame yang berisi informasi sinyal
     yang diinginkan dengan metode periodicity
     K.Awal  : buf sudah berisi nilai dengan panjang frame
               L dan panjang sinyal tiap frame N
     K.Akhir : posisi frame dihasilkan
  */

  /* Kamus Lokal */
  unsigned l,n;
  float r,*sum,nmax;

  /* Algoritma */
  sum=(float *)malloc(L*sizeof(float));
  nmax=-1.0;
  for(l=0;l<L;l++)
  {
    sum[l]=0.0;
    for(n=0;n<(unsigned)N/(unsigned)4;n++)
    {
      r=korelasi_diri(n,N,buf[l]);
      if ((r*sqrt(N-n)>1.96)||(r*sqrt(N-n)< -1.96)) //95%
      {
        sum[l]++;
      }
    }
    if(nmax<sum[l])
    {
      nmax=sum[l];
    }
  }

  l=0;
  while((l<L)&&((sum[l]/nmax)<0.8))
  {

    l++;
  }
  free(sum);

  return l;
}
float variansi(float **Buf,unsigned L,unsigned N,unsigned frm_mulai)
{
  /*  menghitung variansi sinyal
      K.Awal  : sinyal (Buf) dengan panjang frame L dengan
                frame awal adalah frm_mulai dan panjang sinyal
                tiap frame N berisi nilai
      K.Akhir : diperoleh variansi sinyal

  */

  /* Kamus Lokal */
  unsigned l,n;
  float rata,var;

  /* Algoritma */
  /* menghitung rata-rata sinyal*/
  rata=0.0;
  for(l=0;l<L;l++)
  {
    for(n=0;n<N;n++)
    {
      rata=rata+Buf[l+frm_mulai][n];
    }
  }
  rata=rata/((float)L*(float)N);

  /* menghitung variansi sinyal */
  var=0.0;
  for(l=0;l<L;l++)
  {
    for(n=0;n<N;n++)
    {
      var=var+(Buf[l+frm_mulai][n]-rata)*(Buf[l+frm_mulai][n]-rata);
    }
  }
  var=var/((float)L*(float)N);

  return var;
}
unsigned MLR(float **Buf2,unsigned L2,float **Buf1,unsigned L1,unsigned N)
{
  /* mencari posisi frame yang berisi informasi sinyal
     yang diinginkan dengan metode Maximum Likelihood
     Ratios (MLR)
     K.Awal  : buf sudah berisi nilai dengan panjang frame
               L dan panjang sinyal tiap frame N
     K.Akhir : posisi frame dihasilkan
  */

  /* Kamus Lokal */
  float var1,var2,lamda;
  unsigned i,I,imin;

  /* Algoritma */
  var1=variansi(Buf1,L1,N,0);
  I=L2-L1;

  imin=0;
  i=1;
  while(i<=I)
  {
    var2=variansi(Buf2,L1,N,imin);
    lamda=(float)L1*log(var2/var1);
    var2=variansi(Buf2,L1,N,i);
    if(fabs(lamda)>fabs((float)L1*log(var2/var1)))
    {
      imin=i;
    }
    i++;
  }
  return imin;
}
