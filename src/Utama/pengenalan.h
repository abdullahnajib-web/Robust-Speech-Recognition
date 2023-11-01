//---------------------------------------------------------------------------
#ifndef pengenalanH
#define pengenalanH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "spuk.h"
//---------------------------------------------------------------------------
class TFPengenalan : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label1;
        TPanel *Panel1;
        TButton *Button2;
        TEdit *Edit1;
        TButton *Button1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations

public:		// User declarations
        __fastcall TFPengenalan(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPengenalan *FPengenalan;
//---------------------------------------------------------------------------
#endif
