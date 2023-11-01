//---------------------------------------------------------------------------
#ifndef utamafH
#define utamafH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TFUtama : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Pelatihan1;
        TMenuItem *Pengenalan1;
        TMenuItem *Analisis1;
        TMenuItem *Bantuan1;
        TMenuItem *Perihal1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TImage *Image1;
        TImageList *ImageList1;
        void __fastcall Pelatihan1Click(TObject *Sender);
        void __fastcall Pengenalan1Click(TObject *Sender);
        void __fastcall Analisis1Click(TObject *Sender);
        void __fastcall Perihal1Click(TObject *Sender);
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall ToolButton2Click(TObject *Sender);
        void __fastcall ToolButton3Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFUtama(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFUtama *FUtama;
//---------------------------------------------------------------------------
#endif
