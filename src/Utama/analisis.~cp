//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "analisis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFAnalisis *FAnalisis;
//---------------------------------------------------------------------------
float TFAnalisis::Energi(float *buf,unsigned panjang)
{
  unsigned i;
  float Sum;

  Sum=0.0;
  for(i=0;i<panjang;i++)
  {
    Sum=Sum+buf[i]*buf[i];
  }
  return Sum;
}

__fastcall TFAnalisis::TFAnalisis(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TFAnalisis::Button1Click(TObject *Sender)
{

  Image2->Canvas->FillRect(Image2->ClientRect);  
  analisis_pendeteksian_sinyal_suara(Image1,Image2,buf1,buf2,
                                        Label16,Label17,Label18,Start,
                                        End,panjang,CheckBox1->Checked,CheckBox2->Checked,
                                        CheckBox3->Checked);


}
//---------------------------------------------------------------------------

void __fastcall TFAnalisis::ComboBox1Click(TObject *Sender)
{
  float E1,E2;
  extern tparameter_panjang_lpc par_pj_lpc;

  Label16->Caption="";
  Label17->Caption="";
  Label18->Caption="";

  Image1->Canvas->FillRect(Image1->ClientRect);
  Image2->Canvas->FillRect(Image2->ClientRect);
  baca_file_wave(buf1,&panjang,("Wave//Derau"+ComboBox1->Text+".wav").c_str());
  E2=Energi(buf1,panjang);


  baca_file_wave(buf2,&panjang,("Wave//SinyalMD"+ComboBox1->Text+".wav").c_str());
  Gambar(Image2,buf2,panjang);
  E1=Energi(buf2,panjang);

  baca_file_wave(buf1,&panjang,("Wave//SinyalM"+ComboBox1->Text+".wav").c_str());
  Gambar(Image1,buf1,panjang);

  Label12->Caption=Format("%.2f",ARRAYOFCONST((E1)));
  Label13->Caption=Format("%.2f",ARRAYOFCONST((E2)));
  Label14->Caption=Format("%.2f dB",ARRAYOFCONST((10.0*log10(E1/E2))));


  Start=2;
  while(buf1[Start]==0)
  {
    Start++;
  }
  End=panjang-1;
  while(buf1[End]==0)
  {
    End--;
  }

  Start=Start/80;
  End=ceil((float)End/80.0);
  Label15->Caption=IntToStr(Start)+" - "+IntToStr(End);
  GarisFrame(Image1,Start,End,80,panjang,clRed);

        
}
//---------------------------------------------------------------------------

void __fastcall TFAnalisis::FormCreate(TObject *Sender)
{
  Image1->Canvas->Brush->Color=clBlack;
  Image1->Canvas->Pen->Color=clLime;
  Image1->Canvas->FillRect(Image1->ClientRect);

  Image2->Canvas->Brush->Color=clBlack;
  Image2->Canvas->Pen->Color=clLime;
  Image2->Canvas->FillRect(Image2->ClientRect);        
}
//---------------------------------------------------------------------------


void __fastcall TFAnalisis::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Image1->Canvas->FillRect(Image1->ClientRect);
  Image2->Canvas->FillRect(Image2->ClientRect);

  CheckBox1->Checked=false;
  CheckBox2->Checked=false;
  CheckBox3->Checked=false;

  ComboBox1->Text="0";

  Label12->Caption="";
  Label13->Caption="";
  Label14->Caption="";
  Label15->Caption="";
  Label16->Caption="";
  Label17->Caption="";
  Label18->Caption="";
}
//---------------------------------------------------------------------------

void __fastcall TFAnalisis::Button2Click(TObject *Sender)
{
  FAnalisis->Close();        
}
//---------------------------------------------------------------------------

