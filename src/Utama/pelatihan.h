//---------------------------------------------------------------------------
#ifndef pelatihanH
#define pelatihanH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "spuk.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFPelatihan : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *Edit1;
        TEdit *Edit2;
        TButton *Button1;
        TButton *Button2;
        TEdit *Edit6;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit7;
        TEdit *Edit8;
        TEdit *Edit9;
        TLabel *Label12;
        TPanel *Panel1;
        TPanel *Panel2;
        TLabel *Label13;
        TPanel *Panel3;
        TPanel *Panel4;
        TLabel *Label14;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
void semua_edit(bool enable);

public:		// User declarations
        __fastcall TFPelatihan(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPelatihan *FPelatihan;
//---------------------------------------------------------------------------
#endif
