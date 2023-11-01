#include "pelatihan.h"

char berhenti;

void  pelatihan_sinyal_suara(AnsiString NamaFile,AnsiString SimpanFile,unsigned pj_in,
                            unsigned pj_hid,unsigned pj_out,float lr,float _error,
                            unsigned jml_file,unsigned pj_sinyal,TLabel *S_MSE
                            )
{
/* kamus */

  extern ttitik *cendroit;
  extern tparameter_lpc par_lpc;
  extern tparameter_panjang_lpc par_pj_lpc;
  extern tpelatihan pelatihan;
  extern tjaringan jaringan;
  TIniFile *pIniFile;
  unsigned i,j,k;
  AnsiString nama_total,nama_kata;


  try
  {
    jaringan.pj_in=pj_in;
    jaringan.pj_hid=pj_hid;
    jaringan.pj_out=pj_out;
    jaringan.lr=lr;
    jaringan._error=_error;
    alokasi_jaringan();


    pelatihan.pj_pelatihan=jml_file*jaringan.pj_out;
    alokasi_pelatihan();

    alokasi_parameter_kuantisasi(8000,jaringan.pj_in);

    par_pj_lpc.N=240;
    par_pj_lpc.M=80;
    par_pj_lpc.p=10;
    par_pj_lpc.Q=15;
    par_pj_lpc.panjang_sinyal=8000;
    alokasi_parameter_lpc();

    init_hamming_window();

    /*** Pengubahan wav ke ceptral terkuantisasi ***/
                 
    nama_total=NamaFile;
    for(i=0;i<jaringan.pj_out;i++)
    {
      if(nama_total.Pos(" "))
      {
        nama_kata=nama_total.SubString(1,nama_total.Pos(" ")-1);
        nama_total.Delete(1,nama_total.Pos(" "));
      }
      else
      {
        nama_kata=nama_total;
      }
      for(j=0;j<jml_file;j++)
      {

        // Wav ke Ceptral
        baca_file_wave(par_lpc.s,&(par_pj_lpc.panjang_sinyal),("..//Data//"+SimpanFile+"//Kata//"+
                 nama_kata+IntToStr(j+1)+".wav").c_str());

        par_pj_lpc.panjang_sinyal=pj_sinyal;
        par_pj_lpc.L = (unsigned)(par_pj_lpc.panjang_sinyal-par_pj_lpc.N)/par_pj_lpc.M+1;
        preemphasis(0.9375);
        normalisasi();
        pembentukan_frame();
        hamming_window();
        autocorelasi();
        eliminasi();
        koeflpc_ke_ceptral();
        matrik_ke_vektor1(par_lpc.c,par_pj_lpc.L,par_pj_lpc.Q,par_lpc.s,&par_pj_lpc.panjang_sinyal);
        tulis_file(par_lpc.s,(par_pj_lpc.panjang_sinyal),("..//Data//"+SimpanFile+"//Code Book//"+
                  nama_kata+IntToStr(j+1)+".cbk").c_str());

       // Ceptral ke ceptral kuant
        kuantisasi(par_lpc.s,par_pj_lpc.panjang_sinyal,jaringan.pj_in);
        pengurutan_cendroit(jaringan.pj_in);
        for(k=1;k<=jaringan.pj_in;k++)
        {
          /* isi data untuk training */
          pelatihan.X[jml_file*i+j+1][k]=cendroit[k].y; //
        }
        for(k=1;k<=jaringan.pj_out;k++)
        {
          /* isi data untuk training */
          if (i+1==k)
          {
            pelatihan.T[jml_file*i+j+1][k]=1.0;
          }
          else
          {
            pelatihan.T[jml_file*i+j+1][k]=0.0;
          }
        } //for k

      } //for j
    } //for i


    /*** Proses pelatihaning ***/
    inisialisasi_penimbang_dan_bias();
    _error=proses_semua_pelatihan();berhenti=0;
    while((_error>jaringan._error)&&(!berhenti))
    {
      _error=proses_semua_pelatihan();
     Application->ProcessMessages();
      S_MSE->Caption=FloatToStr(_error);
    }
    /* tulis report data */

    pIniFile=new TIniFile(("..//Data//"+SimpanFile+"//Penimbang//"+
                          SimpanFile+".ini").c_str());
    //File
    pIniFile->WriteString("Files","Nama",SimpanFile.c_str());
    pIniFile->WriteString("Files","Kata",NamaFile.c_str());
    pIniFile->WriteInteger("Files","Jumlah Kata",jml_file);
    pIniFile->WriteInteger("Files","Jumlah Codebook",par_pj_lpc.L*par_pj_lpc.Q);
    pIniFile->WriteDateTime("Files","Tanggal",TDateTime().CurrentTime());

    //pelatihan
    pIniFile->WriteInteger("Pelatihan","Jumlah Input",jaringan.pj_in);
    pIniFile->WriteInteger("Pelatihan","Jumlah Hidden",jaringan.pj_hid);
    pIniFile->WriteInteger("Pelatihan","Jumlah Output",jaringan.pj_out);
    pIniFile->WriteFloat("Pelatihan","Learning Rate",lr);
    pIniFile->WriteFloat("Pelatihan","Epsilon",jaringan._error);
    pIniFile->WriteFloat("Pelatihan","MSE",_error);

    delete pIniFile;


    /* tulis Penimbang */
    k=0;
    for(i=1;i<=jaringan.pj_out+jaringan.pj_hid;i++)
    {
      for(j=1;j<=jaringan.pj_in+jaringan.pj_hid+jaringan.pj_out;j++)
      {
        par_lpc.s[k]=jaringan.W[i][j];
        k++;
      }

      par_lpc.s[k]=jaringan.th[i];
      k++;
    }

    tulis_file(par_lpc.s,k,("..//Data//"+SimpanFile+"//Penimbang//"+
              SimpanFile+".dat").c_str());
 }
  __finally
  {
    par_pj_lpc.L = (unsigned)(8000-par_pj_lpc.N)/par_pj_lpc.M+1;
    dealokasi_parameter_lpc();
    dealokasi_jaringan();
    dealokasi_pelatihan();
    dealokasi_parameter_kuantisasi(jaringan.pj_in);
  }
}
