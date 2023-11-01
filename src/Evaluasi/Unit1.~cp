//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

float TForm1::Energi(float *buf,unsigned panjang)
{
  unsigned i;
  float Sum;

  Sum=0.0;
  for(i=0;i<panjang;i++) //??
  {
    Sum=Sum+buf[i]*buf[i];
  }
  return Sum;
}

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  FILE *file1,*file2,*file3,*file4;
  unsigned char CC1,CC2;
  char XX;
  int retval1,retval2;
  unsigned i;
  float *buf1,*buf2,*buf3,E1,E2;

  buf1=(float *)malloc(30000*sizeof(float));
  buf2=(float *)malloc(30000*sizeof(float));
  buf3=(float *)malloc(30000*sizeof(float));

  randomize();


  file1 = fopen(("wav\\SinyalM"+Edit1->Text+".wav").c_str(),"r");
  file2=fopen(("wav\\_Derau"+Edit1->Text+".wav").c_str(),"r");
  file3=fopen(("wav\\SinyalMD"+Edit1->Text+".wav").c_str(),"w");
  file4=fopen(("wav\\Derau"+Edit1->Text+".wav").c_str(),"w");

  for(i=0;i<46;i++)
  {
      fscanf(file2,"%c",&CC2);
      fscanf(file1,"%c",&CC1);
      fprintf(file3,"%c",CC1);
      fprintf(file4,"%c",CC1);
  }
  retval1 = fscanf(file1,"%c",&CC1);
  retval2 = fscanf(file2,"%c",&CC2);

  i=0;
  while((EOF != retval2))
  {
    CC2=INT((CC2-128)*StrToFloat(Edit2->Text)+128);
    buf1[i]=(float)CC1-128.0;
    buf2[i]=(float)CC2-128.0;
    buf3[i]=buf1[i]+buf2[i];
    i++;

    fprintf(file3,"%c",(CC1-128)+CC2);
    fprintf(file4,"%c",CC2);
    retval1=fscanf(file1,"%c",&CC1);
    retval2=fscanf(file2,"%c",&CC2);
  }

  fclose(file3);fclose(file4);
  fclose(file1);fclose(file2);
  E1=Energi(buf2,i-1);Label1->Caption=E1;
  E2=Energi(buf3,i-1);Label2->Caption=E2;
  Caption=10.0*log10(E2/E1);
  
  free(buf1);free(buf2);free(buf3);
}
//---------------------------------------------------------------------------
