//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TEdit *Edit1;
        TLabel *Label1;
        TLabel *Label2;
        TMemo *Memo1;
        TEdit *Edit2;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations



float TForm1::Energi(float *buf,unsigned panjang);

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 