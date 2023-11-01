//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "pelatihan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFPelatihan *FPelatihan;
extern char berhenti;
//---------------------------------------------------------------------------
void TFPelatihan::semua_edit(bool enable)
{
  Edit1->Enabled=enable;Edit2->Enabled=enable;Edit3->Enabled=enable;
  Edit4->Enabled=enable;Edit5->Enabled=enable;Edit6->Enabled=enable;
  Edit7->Enabled=enable;Edit8->Enabled=enable;Edit9->Enabled=enable;

}

__fastcall TFPelatihan::TFPelatihan(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFPelatihan::Button1Click(TObject *Sender)
{
  Button1->Enabled=false;
  Button2->Enabled=true;
  semua_edit(false);

  pelatihan_ucapan_kata(Edit1->Text,Edit6->Text,StrToInt(Edit3->Text),StrToInt(Edit4->Text),StrToInt(Edit5->Text),
                         StrToFloat(Edit8->Text),StrToFloat(Edit7->Text),
                         StrToInt(Edit2->Text),StrToInt(Edit9->Text),Label10);
  Button1->Enabled=true;
  Button2->Enabled=false;
  semua_edit(true);
}
//---------------------------------------------------------------------------

void __fastcall TFPelatihan::Button2Click(TObject *Sender)
{
  berhenti=1;
  Button1->Enabled=true;
  Button2->Enabled=false;
  semua_edit(true);
}
//---------------------------------------------------------------------------


void __fastcall TFPelatihan::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Label10->Caption=" ";        
        
}
//---------------------------------------------------------------------------





