//---------------------------------------------------------------------------
#ifndef analisisH
#define analisisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "spuk.h"
//---------------------------------------------------------------------------
class TFAnalisis : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TImage *Image2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label5;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TButton *Button1;
        TButton *Button2;
        TComboBox *ComboBox1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall ComboBox1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
  float buf1[30000],buf2[30000];
  unsigned panjang,Start,End;
    float Energi(float *Buf,unsigned len);


public:		// User declarations
        __fastcall TFAnalisis(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFAnalisis *FAnalisis;
//---------------------------------------------------------------------------
#endif
