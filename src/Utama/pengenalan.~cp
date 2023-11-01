//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "pengenalan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFPengenalan *FPengenalan;
extern char berhenti;
//---------------------------------------------------------------------------

__fastcall TFPengenalan::TFPengenalan(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFPengenalan::Button2Click(TObject *Sender)
{
  Button2->Enabled=false;
  Button1->Enabled=true;
  Edit1->Enabled=false;
  Image1->Canvas->Brush->Color=clBlack;
  Image1->Canvas->FillRect(Image1->ClientRect);
  pengenalan_ucapan_kata(Edit1->Text,Image1,Panel1);

}
//---------------------------------------------------------------------------
void __fastcall TFPengenalan::Button1Click(TObject *Sender)
{
  berhenti=1;
  Button2->Enabled=true;
  Button1->Enabled=false;
  Edit1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFPengenalan::FormCreate(TObject *Sender)
{
  Image1->Canvas->Brush->Color=clBlack;
  Image1->Canvas->FillRect(Image1->ClientRect);
        
}
//---------------------------------------------------------------------------

void __fastcall TFPengenalan::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Image1->Canvas->Brush->Color=clBlack;
  Image1->Canvas->FillRect(Image1->ClientRect);
  Panel1->Caption="-";      
}
//---------------------------------------------------------------------------

