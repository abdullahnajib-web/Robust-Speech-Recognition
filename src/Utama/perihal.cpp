//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "perihal.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TFPerihal *FPerihal;
//--------------------------------------------------------------------- 
__fastcall TFPerihal::TFPerihal(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TFPerihal::OKButtonClick(TObject *Sender)
{
  FPerihal->Close();        
}
//---------------------------------------------------------------------------

