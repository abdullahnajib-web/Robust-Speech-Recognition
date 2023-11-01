#ifndef propagasi_balik_H
#define propagasi_balik_H

typedef struct
{
  float    *O;     /* parameter input, hidden dan output */
  float    *T;     /* parameter target */
  float    **W;    /* penimbang */
  float    *th;    /* bias unit */
  float    lr;     /* koefisien laju belajar */
  float    _error; /* error yang masih dapat ditolelir */
  unsigned pj_in;  /* panjang parameter input */
  unsigned pj_hid; /* panjang parameter hidden */
  unsigned pj_out; /* panjang parameter output */
}tjaringan;

typedef struct
{
  float    **X;          /* input target untuk melakukan pelatihan */
  float    **T;          /* target untuk melakukan pelatihan */
  unsigned pj_pelatihan; /* banyaknya data untuk pelatihan */
}tpelatihan_sinyal;

float sigmoid(float x);
/* Fungsi mengubah nilai real menjadi nilai
   antara 0 dan 1
   K.Awal  : x berisi nilai real
   K.Akhir : fungsi menghasilkan nilai antara
             0 dan 1
*/

void  alokasi_jaringan();
/* melakukan alokasi memori pada parameter-parameter jaringan
   K.Awal  : parameter panjang jaringan berisi nilai
   K.Akhir : parameter -parameter jaringan dialokasi
*/

void  dealokasi_jaringan();
/* melakukan dealokasi memori pada parameter-parameter jaringan
   K.Awal  : parameter-parameter jaringan telah dialokasi
   K.Akhir : parameter-parameter jaringan didealokasi
*/

void  alokasi_pelatihan();
/* melakukan alokasi memori pada parameter-parameter pelatihan
   K.Awal  : parameter panjang pelatihan dan jaringan
             berisi nilai
   K.Akhir : parameter -parameter pelatihan dialokasi
*/

void  dealokasi_pelatihan();
/* melakukan dealokasi memori pada parameter-parameter pelatihan
   K.Awal  : parameter-parameter pelatihan telah dialokasi
   K.Akhir : parameter-parameter pelatihan didealokasi
*/

void  inisialisasi_penimbang_dan_bias();
/* melakukan inisialisasi pada penimbang dan bias unit
   K.Awal  : parameter jaringan telah berisi nilai
   K.Akhir : penimbang (jaringan.W) dan bias (jaringan.th)
             berisi nilai antara 0 dan 1
*/

float aktivasi_node(int p,int q,int node);
/* melakukan proses aktivasi untuk setiap node
   K.Awal  : nomor node,posisi awal dan akhir dari
             jaringan yang menuju ke node sudah
             bernilai
   K.Akhir : diperoleh nilai aktifasi node
*/

void  aktivasi_jaringan();
/* melakukan proses aktivasi untuk seluruh jaringan
   K.Awal  : parameter input, penimbang dan bias sudah
             berisi nilai
   K.Akhir : diperoleh nilai aktivasi seluruh jaringan
*/

void  pelatihan_node(char IsOut,int node);
/* proses pelatihan untuk setiap node
   K.Awal  : penimbang dan bias node sudah diinisialisasi
   K.Akhir : penimbang dan bias node telah dilakukan
             pelatihan
*/

void  pelatihan_jaringan();
/* proses pelatihan untuk seluruh jaringan
   K.Awal  : penimbang dan bias seluruh jaringan
             telah diinisialisasi
   K.Akhir : penimbang dan bias seluruh jaringan
             telah dilakukan pelatihan
*/

float proses_semua_pelatihan();
/* seluruh data input target dan target dilakukan proses
   pelatihan dan diperoleh MSE(Mean Suquare Error)
   K.Awal  : semua input target,target,banyaknya data untuk
             pelatihan dan parameter jaringan telah berisi
             nilai
   K.Akhir : seluruh input target dan target telah dilakukan
             pelatihan dengan MSE yang dihasilkan
*/


#endif
