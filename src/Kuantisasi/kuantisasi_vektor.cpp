#ifndef VKuant_C
#define VKuant_C

#include <stdlib.h>
#include <math.h>
#include "kuantisasi_vektor.h"


/* data kuantisasi */
struct data_kuant
{
  ttitik **R;             /* kluster */
  ttitik **temp1,**temp2; /* penyimpanan data sementara */
  int *L;                 /* banyaknya data untuk tiap kluster */
  int *i1,*i2;            /* data indeks sementara */
}_data_kuant;

ttitik *cendroit;  /* array untuk menyimpan cendroit dalam sumbu y*/

void alokasi_parameter_kuantisasi(int maks_data,int maks_cendroit)
{
  /* melakukan alokasi memori untuk parameter-parameter kuantisasi
     K.Awal  : jumlah maksimum data dan cendroit telah ditentukan
     K.Akhir : parameter kuantisasi dialokasi

  */

  /* Kamus Lokal */
  int i;

  /* Algoritma */
  cendroit=(ttitik *)malloc((maks_cendroit+1)*sizeof(ttitik));
  _data_kuant.R=(ttitik **)malloc((maks_cendroit+1)*sizeof(ttitik *));
  _data_kuant.temp1=(ttitik **)malloc((maks_cendroit+1)*sizeof(ttitik *));
  _data_kuant.temp2=(ttitik **)malloc((maks_cendroit+1)*sizeof(ttitik *));
  _data_kuant.L=(int *)malloc((maks_cendroit+1)*sizeof(int));
  _data_kuant.i1=(int *)malloc((maks_cendroit+1)*sizeof(int));
  _data_kuant.i2=(int *)malloc((maks_cendroit+1)*sizeof(int));
  for(i=0;i<=maks_cendroit;i++)
  {
    _data_kuant.R[i]=(ttitik *)malloc((maks_data+1)*sizeof(ttitik));
    _data_kuant.temp1[i]=(ttitik *)malloc((maks_data+1)*sizeof(ttitik));
    _data_kuant.temp2[i]=(ttitik *)malloc((maks_data+1)*sizeof(ttitik));
  }
}

void dealokasi_parameter_kuantisasi(int maks_cendroit)
{
  /* melakukan dealokasi memori untuk parameter-parameter kuantisasi
     K.Awal  : parameter kuantisasi telah dialokasi
     K.Akhir : parameter kuantisasi didealokasi
  */

  /* Kamus Lokal */
  int i;

  /* Algoritma */
  free(cendroit);free(_data_kuant.L);
  free(_data_kuant.i1);free(_data_kuant.i2);
  for(i=0;i<=maks_cendroit;i++)
  {
    free(_data_kuant.R[i]);free(_data_kuant.temp1[i]);
    free(_data_kuant.temp2[i]);
  }
  free(_data_kuant.R);free(_data_kuant.temp1);
  free(_data_kuant.temp2);
}

void pengurutan_cendroit(int jumlah_cendroit)
{
  /* melakukan pengurutan cendroit berdasarkan sumbu x
     K.Awal  : cendroit telah berisi nilai
     K.Akhir : cendroit terurut berdasarkan sumbu x
  */

  /* Kamus Lokal */
  int i,j;
  ttitik Temp;

  /* Algoritma */
  for(i=1;i<=jumlah_cendroit-1;i++)
  {
    for(j=i+1;j<=jumlah_cendroit;j++)
    {
      if((cendroit[i].x)>(cendroit[j].x))
      {
        Temp=cendroit[i];
        cendroit[i]=cendroit[j];
        cendroit[j]=Temp;
      }
    }
  }
}
void kuantisasi(float *data,int jumlah_data,int jumlah_cendroit)
{
  /* melakukan kuantisasi terhadap data
     K.Awal  : data, jumlah data dan jumlah cendroit yang akan
               dibuat telah diisikan
     K.Akhir : variabel cendroit.y berisi cendroit hasil kuantisasi
  */

  /* Kamus Lokal */
  int j,m,k;
  float D,D1;
  ttitik cent1,cent2;

  /* Algoritma */
  _data_kuant.L[1]=jumlah_data;
  for(j=1;j<=_data_kuant.L[1];j++)
  {
    _data_kuant.R[1][j].x=(float)j;
    _data_kuant.R[1][j].y=data[j-1];
  }

  cendroit[1].x=0.0;
  cendroit[1].y=0.0;

  m=1;D=0.0;
  for(j=1;j<=_data_kuant.L[1];j++)
  {
    cendroit[1].x=cendroit[1].x+_data_kuant.R[1][j].x;
    cendroit[1].y=cendroit[1].y+_data_kuant.R[1][j].y;
  }
  cendroit[1].x=cendroit[1].x/(float)_data_kuant.L[1];
  cendroit[1].y=cendroit[1].y/(float)_data_kuant.L[1];

  while(m<jumlah_cendroit)
  {
    //spliting
    for(k=1;k<=m;k++)
    {
      cendroit[k+m].x=cendroit[k].x*(1.0-_eps);
      cendroit[k].x=cendroit[k].x*(1.0+_eps);
      cendroit[k+m].y=cendroit[k].y*(1.0-_eps);
      cendroit[k].y=cendroit[k].y*(1.0+_eps);
    }

    do
    {
      D1=D;
      D=0.0;
      for(k=1;k<=m;k++)
      {
        _data_kuant.i1[k]=0;cent1.x=0;cent1.y=0;
        _data_kuant.i2[k]=0;cent2.x=0;cent2.y=0;
        for(j=1;j<=_data_kuant.L[k];j++)
        {
          if(sqrt((_data_kuant.R[k][j].x-cendroit[k].x)*(_data_kuant.R[k][j].x-cendroit[k].x)+
                  (_data_kuant.R[k][j].y-cendroit[k].y)*(_data_kuant.R[k][j].y-cendroit[k].y)
                  )>
             sqrt((_data_kuant.R[k][j].x-cendroit[k+m].x)*(_data_kuant.R[k][j].x-cendroit[k+m].x)+
                  (_data_kuant.R[k][j].y-cendroit[k+m].y)*(_data_kuant.R[k][j].y-cendroit[k+m].y)
                  )
             )
          {
            _data_kuant.i2[k]=_data_kuant.i2[k]+1;
            cent2.x=cent2.x+_data_kuant.R[k][j].x;
            cent2.y=cent2.y+_data_kuant.R[k][j].y;
            _data_kuant.temp2[k][_data_kuant.i2[k]].x=_data_kuant.R[k][j].x;
            _data_kuant.temp2[k][_data_kuant.i2[k]].y=_data_kuant.R[k][j].y;
          }
          else
          {
            _data_kuant.i1[k]=_data_kuant.i1[k]+1;
            cent1.x=cent1.x+_data_kuant.R[k][j].x;
            cent1.y=cent1.y+_data_kuant.R[k][j].y;
            _data_kuant.temp1[k][_data_kuant.i1[k]].x=_data_kuant.R[k][j].x;
            _data_kuant.temp1[k][_data_kuant.i1[k]].y=_data_kuant.R[k][j].y;
          }
        }//for j

        if(_data_kuant.i1[k] != 0)
        {
          cendroit[k].x=cent1.x/_data_kuant.i1[k];
          cendroit[k].y=cent1.y/_data_kuant.i1[k];
        }
        if(_data_kuant.i2[k] != 0)
        {
          cendroit[k+m].x=cent2.x/_data_kuant.i2[k];
          cendroit[k+m].y=cent2.y/_data_kuant.i2[k];
        }

        for(j=1;j<=_data_kuant.i1[k];j++)
        {
          D=D+sqrt((_data_kuant.temp1[k][j].x-cendroit[k].x)*(_data_kuant.temp1[k][j].x-cendroit[k].x)+(_data_kuant.temp1[k][j].y-cendroit[k].y)*(_data_kuant.temp1[k][j].y-cendroit[k].y)
                    );
        }

        for(j=1;j<=_data_kuant.i2[k];j++)
        {
          D=D+sqrt((_data_kuant.temp2[k][j].x-cendroit[k+m].x)*(_data_kuant.temp2[k][j].x-cendroit[k+m].x)+
                   (_data_kuant.temp2[k][j].y-cendroit[k+m].y)*(_data_kuant.temp2[k][j].y-cendroit[k+m].y)
                   );
        }
      }//for k


    }while(((D-D1)/D)>=_eps);

    for(k=1;k<=m;k++)
    {
      _data_kuant.L[k]=_data_kuant.i1[k];
      _data_kuant.L[k+m]=_data_kuant.i2[k];
      for(j=1;j<=_data_kuant.L[k];j++)
      {
         _data_kuant.R[k][j].x=_data_kuant.temp1[k][j].x;
         _data_kuant.R[k][j].y=_data_kuant.temp1[k][j].y;
      }
      for(j=1;j<=_data_kuant.L[k+m];j++)
      {
        _data_kuant.R[k+m][j].x=_data_kuant.temp2[k][j].x;
        _data_kuant.R[k+m][j].y=_data_kuant.temp2[k][j].y;
      }

    }
    m=m*2;
  }//while
  
}

#endif

