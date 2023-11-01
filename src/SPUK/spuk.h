#ifndef spukH
#define spukH



#include <inifiles.hpp>
#include "standario.h"
#include "kuantisasi_vektor.h"
#include  "lpc.h"
#include "propagasi_balik.h"
#include "penyamplingan.h"
#include "deteksi.h"
#include <vcl>
#include <math.h>


unsigned IMIN(float *Buf,unsigned len);
void Gambar(TImage *Img,float *Buf,unsigned len);
void GarisFrame(TImage *Img,unsigned Fr1,unsigned Fr2,
                        unsigned M,unsigned len,TColor Cl);
void pelatihan_ucapan_kata(AnsiString NamaFile,AnsiString SimpanFile,unsigned pj_in,
                            unsigned pj_hid,unsigned pj_out,float lr,float _error,
                            unsigned jml_file,unsigned pj_sinyal,TLabel *S_MSE
                            );
void  pengenalan_ucapan_kata(AnsiString NamaFile,TImage *Img,TPanel *Panel);
void analisis_pendeteksian_sinyal_suara(TImage *Img1,TImage *Img2,float buf1[],float buf2[],
                                        TLabel *lb1,TLabel *lb2,TLabel *lb3,unsigned Start,
                                        unsigned End,unsigned panjang,char energi,char periodik,
                                        char mlr);



#endif
