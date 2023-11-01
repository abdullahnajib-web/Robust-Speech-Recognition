#ifndef LPC_H
#define LPC_H


typedef struct
{
  unsigned N; /* panjang sinyal tiap frame */
  unsigned M; /* panjang selisih antar frame */
  unsigned L; /* panjang frame */
  unsigned p; /* panjang orde koefisien lpc */
  unsigned Q; /* pajang orde ceptral */
  unsigned panjang_sinyal; /* panjang sinyal suara */
}tparameter_panjang_lpc;

typedef struct
{
 float *s;  /* sinyal suara */
 float **x; /* sinyal yang telah terblok */
 float **r; /* koefisien autokorelasi */
 float **a; /* koefisien lpc */
 float **c; /* koefisien ceptral */
}tparameter_lpc;

void  Gauss(float **a,float *x,unsigned n);
/* eliminasi gauss px=b
   K.Awal  : a berisi matrix dengan panjang n x n+1,
             dimana nilai n sudah diisikan dan p
             berupa matrix a dengan orden n x n dan
             b berupa vektor dari matrix a dengan
             kolom ke n+1
   K.Akhir : vektor x sudah berisi nilai hasil eliminasi
*/

float maks_vektor(float *x,int n);
/* mencari nilai maksimum vektor
   K.Awal  : vektor berisi suatu nilai dengan panjang n
   K.Akhir : diperoleh nilai maksimum vektor
*/

void  alokasi_parameter_lpc();
/* Melakukan alokasi memori terhadap parameter-parameter lpc
   K.Awal  : Parameter-parameter panjang lpc sudah diisikan
   K.Akhir : Parameter-parameter lpc telah dialokasi
*/

void  dealokasi_parameter_lpc();
/* melakukan dealokasi memori terhadap parameter-parameter lpc
   K.Awal  : Parameter-parameter lpc telah dialokasi
   K.Akhir : Paramter-parameter lpc didealokasi
*/

void  preemphasis(float faktor);
/* proses penyamaan amplitudo (flatten)
   K.Awal  : par_lpc.s berisi sinyal suara, faktor ditentukan
             dengan batas antara 0 dan 1 dan panjang sinyal
             (par_pj_lpc.panjang_sinyal) sudah berisi nilai
   K.Akhir : par_lpc.s berisi sinyal suara yang memiliki amplitudo
             yang sama
*/

void  normalisasi();
/* menormalisasi sinyal, yang berakibat nilai sinyal berada
   diantara selang -1 dan 1
   K.Awal  : par_lpc.s berisi suatu nilai sinyal yang tidak
             semuanya 0 dan panjang sinyal (par_pj_lpc.panjang_sinyal)
             berisi nilai
   K.Akhir : par_lpc.s telah dibagi dengan nilai maksimumnya
             sehingga memiliki nilai antara -1 dan 1
*/

void  pembentukan_frame();
/* membagi sinyal menjadi frame-frame
   K.Awal  : par_lpc.s berisi sinyal, panjang frame (par_pj_lpc.L),
             panjang selisih antar frame (par_pj_lpc.M) dan panjang
             sinyal tiap frame (par_pj_lpc.N) masing-masing sudah
             berisi nilai
   K.Akhir : par_lpc.x berisi sinyal yang berupa matriks
             dengan lebar x panjang di mana lebar menyatakan
             banyaknya frame dan panjang menyatakan panjang
             sinyal tiap frame
*/

void  init_hamming_window();
/* inisialisasi konstanta hamming window sebelum
   melakukan windowing
   K.Awal  : data_lpc.w masih kosong panjang sinyal
             tiap frame (par_pj_lpc.N) sudah berisi nilai
   K.Akhir : data_lpc.w berisi konstanta window berupa
             hamming window
*/

void  hamming_window();
/* mewindowkan sinyal yang telah dibagi menjadi
   frame-frame
   K.Awal : data_lpc.w telah diinisialisasi, yang
            akan berisi konstanta hamming window dan
            par_lpc.x sudah berisi nilai,panjang frame
            (par_pj_lpc.L) dan panjang sinyal tiap frame
            (par_pj_lpc.N) masing-masing sudah berisi nilai
   K.Awal : par_lpc.x telah diwindowkan menggunakan konstanta
            hamming window
*/

void  autocorelasi();
/* proses untuk memperoleh nilai koefisien autokorelasi dari
   sinyal tiap frame
   K.Awal  : par_lpc.x berisi nilai frame sinyal
             yang sudah diwindowkan, panjang frame
             (par_pj_lpc.L), panjang sinyal tiap frame
             (par_pj_lpc.N), dan panjang  orde koefisien
             lpc (par_pj_lpc.p) masing-masing sudah berisi
             nilai
   K.Akhir : diperoleh nilai koefisien autokorelasi dari
             proses aurocorelasi par_lpc.x yang disimpan
             didalam variabel par_lpc.r
*/

void  eliminasi();
/* mencari konstanta lpc yang berupa informasi tentang
   sinyal yang diucapkan, dengan melakukan eliminasi
   terhadap matrix toeplitz, persamaan tersebut dapat
   dituliskan Ra=z dimana R berupa matrix toeplitz yang berisi
   koefisien autocorelasi dari r(0) sampai r(p-1) dan z
   vektor yang berisi koefisien autocorelasi r(1) sampai r(p)
   K.Awal  : par_lpc.r sudah berisi nilai autocorelasi,panjang frame
             (par_pj_lpc.L) dan panjang  orde koefisien
             lpc (par_pj_lpc.p) masing-masing sudah berisi
             nilai
   K.Akhir : par_lpc.a berisi konstanta lpc yang memberikan
             informasi fitur ucapan seseorang
*/

void  koeflpc_ke_ceptral();
/* mengubah koefisien lpc menjadi koefisien ceptral
   agar fitur ucapan lebih handal
   K.Awal  : par_lpc.a sudah berisi fitur ucapan kata,
             panjang frame (par_pj_lpc.L), panjang
             orde koefisien lpc (par_pj_lpc.p) dan
             panjang orde koefisien ceptral
             (par_pj_lpc.Q)masing-masing sudah berisi
             nilai
   K.Akhir : par_lpc.c berisi fitur ucapan kata yang
             handal
*/



#endif