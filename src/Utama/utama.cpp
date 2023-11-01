//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("utama.res");
USEFORM("utamaf.cpp", FUtama);
USEFORM("pelatihan.cpp", FPelatihan);
USEUNIT("..\SPUK\spuk.cpp");
USEUNIT("..\Kuantisasi\kuantisasi_vektor.cpp");
USEUNIT("..\LPC\lpc.cpp");
USEUNIT("..\Pendeteksian\Deteksi.cpp");
USEUNIT("..\Penyamplingan\penyamplingan.cpp");
USEUNIT("..\Propagasi Balik\propagasi_balik.cpp");
USEUNIT("..\StandarIO\StandarIO.cpp");
USEFORM("pengenalan.cpp", FPengenalan);
USEFORM("analisis.cpp", FAnalisis);
USEFORM("perihal.cpp", FPerihal);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFUtama), &FUtama);
                 Application->CreateForm(__classid(TFPelatihan), &FPelatihan);
                 Application->CreateForm(__classid(TFPengenalan), &FPengenalan);
                 Application->CreateForm(__classid(TFAnalisis), &FAnalisis);
                 Application->CreateForm(__classid(TFPerihal), &FPerihal);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
