#ifndef LPC_C
#define LPC_C

#include "lpc.h"
#include <math.h>
#include <stdlib.h>

/* Kamus Global */

/* data lpc */
struct data_lpc
{
  float *w;     /* window yang berupa koefisien hamming window
                   yang ditentukan sebelum dilakukan windowing */
  float **mat;  /* variabel tambahan untuk melakukan proses
                   eliminasi */
}_data_lpc;

tparameter_lpc par_lpc;             /* parameter-parameter lpc yang berisi
                                       nilai-nilai hasil proses pengekstraksian*/
tparameter_panjang_lpc par_pj_lpc;  /* parameter panjang lpc yang berisi
                                       panjang tiap parameter lpc */



void  Gauss(float **a,float *x,unsigned n)
{
  /* eliminasi gauss px=b
     K.Awal  : a berisi matrix dengan panjang n x n+1,
               dimana nilai n sudah diisikan dan p
               berupa matrix a dengan orden n x n dan
               b berupa vektor dari matrix a dengan
               kolom ke n+1
     K.Akhir : vektor x sudah berisi nilai hasil eliminasi
  */

  /* Kamus Lokal */
  unsigned n1;
  float  _eps=0.0000000001;
  unsigned i,j,k,l,kp1;
  float s,p;

  /* Algoritma */
  n1=n+1;
  /*I Tahap Eliminasi/penghilangan */
  for (k=1;k<=n-1;k++)
  {
    kp1=k+1;
    l=k;
    for (i=kp1;i<=n;i++)
      if (fabs(a[i][k])>fabs(a[l][k]))
        { l=i;}

    if (fabs(a[l][l])<_eps)
    {
      exit(1);
    }
    if (l!=k)
    {
      for (j=1;j<=n1;j++)
      {
        s=a[k][j];
        a[k][j]=a[l][j];
        a[l][j]=s;
      }
    }
    for(i=kp1;i<=n;i++)
    {
      p=a[i][k]/a[k][k];
      for(j=kp1;j<=n1;j++)
        a[i][j]=a[i][j]-p*a[k][j];
      a[i][k]=0.0;
    }

  } //for k

  /*II Tahap penyulihan mundur */
  if (fabs(a[n][n])<_eps)
  {
    exit(1);
  }
  x[n]=a[n][n1]/a[n][n];
  for(k=n-1;k>=1;k--)
  {
    s=0.0;    kp1=k+1;
    for (i=kp1;i<=n;i++)
      s=s+a[k][i]*x[i];
    x[k]=(a[k][n1]-s)/a[k][k];
  }
}


float maks_vektor(float *x,unsigned n)
{
  /* mencari nilai maksimum vektor
     K.Awal  : vektor berisi suatu nilai dengan panjang n
     K.Akhir : diperoleh nilai maksimum vektor
  */

  /* Kamus Lokal */
  unsigned i;
  float maks;

  /* Algoritma */
  maks=fabs(x[0]);
  for(i=1;i<n;i++)
  {
      if(fabs(x[i])>maks)
      {
        maks=fabs(x[i]);
      }
  }
  return maks;
}


void alokasi_parameter_lpc()
{
  /* Melakukan alokasi memori terhadap parameter lpc
     K.Awal  : Parameter-parameter panjang lpc sudah diisikan
     K.Akhir : Parameter-parameter lpc telah dialokasi
  */

  /* kamus lokal */
  unsigned i;

  /* Algoritma */
  par_pj_lpc.L=(unsigned)(par_pj_lpc.panjang_sinyal-par_pj_lpc.N)/par_pj_lpc.M+1;
  par_lpc.s=(float *)malloc(par_pj_lpc.panjang_sinyal*sizeof(float));
  par_lpc.x=(float **)malloc(par_pj_lpc.L*sizeof(float *));
  par_lpc.r=(float **)malloc(par_pj_lpc.L*sizeof(float *));
  par_lpc.a=(float **)malloc(par_pj_lpc.L*sizeof(float *));
  par_lpc.c=(float **)malloc(par_pj_lpc.L*sizeof(float *));

  for(i=0;i<par_pj_lpc.L;i++)
  {
    par_lpc.x[i]=(float *)malloc(par_pj_lpc.N*sizeof(float));
    par_lpc.r[i]=(float *)malloc((par_pj_lpc.p+1)*sizeof(float));
    par_lpc.a[i]=(float *)malloc((par_pj_lpc.p+1)*sizeof(float));
    par_lpc.c[i]=(float *)malloc((par_pj_lpc.Q+1)*sizeof(float));

  }

  _data_lpc.w=(float *)malloc(par_pj_lpc.N*sizeof(float));
  _data_lpc.mat=(float **)malloc((par_pj_lpc.p+1)*sizeof(float *));
  for(i=0;i<=par_pj_lpc.p;i++)
  {
    _data_lpc.mat[i]=(float *)malloc((par_pj_lpc.p+2)*sizeof(float));
  }

}

void dealokasi_parameter_lpc()
{
  /* melakukan dealokasi memori terhadap parameter lpc
     K.Awal  : Parameter-parameter lpc telah dialokasi
     K.Akhir : Paramter-parameter lpc didealokasi
  */

  /* Kamus Lokal */
  unsigned i;

  /* Algoritma */
  for(i=0;i<par_pj_lpc.L;i++)
  {
    free(par_lpc.x[i]);
    free(par_lpc.r[i]);
    free(par_lpc.a[i]);
    free(par_lpc.c[i]);
  }
  free(par_lpc.s);
  free(par_lpc.x);
  free(par_lpc.r);
  free(par_lpc.a);
  free(par_lpc.c);
  for(i=0;i<=par_pj_lpc.p;i++)
  {
    free(_data_lpc.mat[i]);
  }
  free(_data_lpc.mat);
  free(_data_lpc.w);
}

void preemphasis(float faktor)
{
  /* proses penyamaan amplitudo (flatten)
     K.Awal  : par_lpc.s berisi sinyal suara, faktor ditentukan
               dengan batas antara 0 dan 1 dan panjang sinyal
               (par_pj_lpc.panjang_sinyal) sudah berisi nilai
     K.Akhir : par_lpc.s berisi sinyal suara yang memiliki amplitudo
               yang sama
  */

  /* Kamus Lokal */
  int n;

  /* Algoritma */
  for(n=par_pj_lpc.panjang_sinyal-1;n>0;n--)
  {
    par_lpc.s[n]=par_lpc.s[n]-faktor*(par_lpc.s[n-1]);
  }
  par_lpc.s[0]=1.0-faktor;
}

void normalisasi()
{
  /* menormalisasi sinyal, yang berakibat nilai sinyal berada
     diantara selang -1 dan 1
     K.Awal  : par_lpc.s berisi suatu nilai sinyal yang tidak
               semuanya 0 dan panjang sinyal (par_pj_lpc.panjang_sinyal)
               berisi nilai
     K.Akhir : par_lpc.s telah dibagi dengan nilai maksimumnya
               sehingga memiliki nilai antara -1 dan 1
  */

  /* Kamus Lokal */
  float maks;
  unsigned int i;

  /* Algoritma */
  maks=maks_vektor(par_lpc.s,par_pj_lpc.panjang_sinyal);
  for(i=0;i<par_pj_lpc.panjang_sinyal;i++)
  {
    par_lpc.s[i]=(par_lpc.s[i])/maks;
  }
}

void pembentukan_frame()
{
  /* membagi sinyal menjadi frame-frame
     K.Awal  : par_lpc.s berisi sinyal, panjang frame (par_pj_lpc.L),
               panjang selisih antar frame (par_pj_lpc.M) dan panjang
               sinyal tiap frame (par_pj_lpc.N) masing-masing sudah
               berisi nilai
     K.Akhir : par_lpc.x berisi sinyal yang berupa matriks
               dengan lebar x panjang di mana lebar menyatakan
               banyaknya frame dan panjang menyatakan panjang
               sinyal tiap frame
  */

  /* Kamus Lokal */
   unsigned l,n,Ml;

   /* Algoritma */
   for(l=0;l<par_pj_lpc.L;l++)
   {
     Ml=(par_pj_lpc.M)*l;
     for(n=0;n<par_pj_lpc.N;n++)
     {
       par_lpc.x[l][n]=par_lpc.s[Ml+n];
     }
   }
}

void init_hamming_window()
{
  /* inisialisasi konstanta hamming window sebelum
     melakukan windowing
     K.Awal  : _data_lpc.w masih kosong panjang sinyal
               tiap frame (par_pj_lpc.N) sudah berisi nilai
     K.Akhir : _data_lpc.w berisi konstanta window berupa
               hamming window 
  */

  /* Kamus Lokal */
  float a;
  unsigned n;

  /* Algoritma */
  a=2.0*M_PI/((float)par_pj_lpc.N-1.0);
  for(n=0;n<par_pj_lpc.N;n++)
  {
    _data_lpc.w[n]=0.54-0.46*cos(a*(float)n);
  }
}

void hamming_window()
{
  /* mewindowkan sinyal yang telah dibagi menjadi
     frame-frame
     K.Awal : _data_lpc.w telah diinisialisasi, yang
              akan berisi konstanta hamming window dan
              par_lpc.x sudah berisi nilai,panjang frame
              (par_pj_lpc.L) dan panjang sinyal tiap frame
              (par_pj_lpc.N) masing-masing sudah berisi nilai
     K.Awal : par_lpc.x telah diwindowkan menggunakan konstanta
              hamming window
  */

  /* Kamus Lokal */
  unsigned l,n;

  /* Algoritma */
  for(l=0;l<par_pj_lpc.L;l++)
  {
    for(n=0;n<par_pj_lpc.N;n++)
    {
      par_lpc.x[l][n]=(par_lpc.x[l][n])*(_data_lpc.w[n]);
    }
  }
}

void autocorelasi()
{
  /* proses untuk memperoleh nilai koefisien autokorelasi dari
     sinyal tiap frame
     K.Awal  : par_lpc.x berisi nilai frame sinyal
               yang sudah diwindowkan, panjang frame
               (par_pj_lpc.L), panjang sinyal tiap frame
               (par_pj_lpc.N), dan panjang  orde koefisien
               lpc (par_pj_lpc.p) masing-masing sudah berisi
               nilai
     K.Akhir : diperoleh nilai koefisien autokorelasi dari
               proses aurocorelasi par_lpc.x yang disimpan
               didalam variabel par_lpc.r
  */
  
  /* Kamus Lokal */
  unsigned l,m,n,Nm;
  float Sum;

  /* Algoritma */
  for(l=0;l<par_pj_lpc.L;l++)
  {
    for(m=0;m<=par_pj_lpc.p;m++)
    {
      Nm=par_pj_lpc.N-1-m;
      Sum=0.0;
      for(n=0;n<=Nm;n++)
      {
        Sum=Sum+(par_lpc.x[l][n])*(par_lpc.x[l][n+m]);
      }
      par_lpc.r[l][m]=Sum;
    }

  }

}

void eliminasi()
{
  /* mencari konstanta lpc yang berupa informasi tentang
     sinyal yang diucapkan, dengan melakukan eliminasi
     terhadap matrix toeplitz, persamaan tersebut dapat
     dituliskan Ra=z dimana R berupa matrix toeplitz yang berisi
     koefisien autocorelasi dari r(0) sampai r(p-1) dan z
     vektor yang berisi koefisien autocorelasi r(1) sampai r(p)
     K.Awal  : par_lpc.r sudah berisi nilai autocorelasi,panjang frame
               (par_pj_lpc.L) dan panjang  orde koefisien
               lpc (par_pj_lpc.p) masing-masing sudah berisi
               nilai
     K.Akhir : par_lpc.a berisi konstanta lpc yang memberikan
               informasi fitur ucapan seseorang

  */

  /* Kamus Lokal */
   unsigned l,i,j;

   /* Algoritma */
   for(l=0;l<par_pj_lpc.L;l++)
   {
     for(i=0;i<par_pj_lpc.p;i++)
     {
       for(j=i;j<par_pj_lpc.p;j++)
       {
         _data_lpc.mat[i+1][j+1]=par_lpc.r[l][j-i];
         if(i!=j)
         {
           _data_lpc.mat[j+1][i+1]=_data_lpc.mat[i+1][j+1];
         }
       }
       _data_lpc.mat[i+1][par_pj_lpc.p+1]=par_lpc.r[l][i+1];
     }
     Gauss(_data_lpc.mat,par_lpc.a[l],par_pj_lpc.p);
   }
}

void koeflpc_ke_ceptral()
{
  /* mengubah koefisien lpc menjadi koefisien ceptral
     agar fitur ucapan lebih handal
     K.Awal  : par_lpc.a sudah berisi fitur ucapan kata,
               panjang frame (par_pj_lpc.L), panjang
               orde koefisien lpc (par_pj_lpc.p) dan
               panjang orde koefisien ceptral
               (par_pj_lpc.Q)masing-masing sudah berisi
               nilai
     K.Akhir : par_lpc.c berisi fitur ucapan kata yang
               handal
  */

  /* Kamus Lokal */
  unsigned l,m,k;
  float sum;

  /* Algoritma */
  for(l=0;l<par_pj_lpc.L;l++)
  {
    par_lpc.c[l][0]=0.0;

    /* menghitung koefisien ceptral dari 1 sampai p*/
    for(m=1;m<=par_pj_lpc.p;m++)
    {
      sum=0.0;
      for(k=1;k<m;k++)
      {
        sum=sum+((float)k/(float)m)*par_lpc.c[l][k]*par_lpc.a[l][m-k];
      }
      par_lpc.c[l][m]=sum+par_lpc.a[l][m];
    }

    /* menghitung koefisien ceptral dari p+1 sampai Q*/
    for(m=par_pj_lpc.p+1;m<=par_pj_lpc.Q;m++)
    {
      sum=0.0;
      for(k=m-par_pj_lpc.p;k<m;k++)
      {
        sum=sum+((float)k/(float)m)*par_lpc.c[l][k]*par_lpc.a[l][m-k];;
      }
      par_lpc.c[l][m]=sum;
      
    }

  }
}

#endif
