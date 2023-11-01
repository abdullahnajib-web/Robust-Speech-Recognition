/* File        : penyamplingan.h    */
/* Dibuat Oleh : Abdullah  23501002 */
/* Tanggal     : 10-12-2002         */

#ifndef penyamplinganH
#define penyamplinganH


typedef struct
{
  unsigned char *s;  /* sinyal  */
  unsigned  panjang; /* panjang sinyal */
}tsinyal_digital;



void buat_handel_sampling(unsigned long frekuensi_sampel,unsigned short amplitudo);
/* Membuat handle untuk melakukan proses penyamplingan
   K.Awal  :  frekuensi sampel (frekuensi_sampel) dan
              amplitudo (amplitudo) Sudah berisi
              masing-masing banyaknya data tiap detik dan
              besar data maksimum
   K.Akhir :  Handle Penyamplingan (data_sampling.handel) sudah dibuat
*/

void sampling(unsigned long waktu);
/* Proses Penyamplingan
   K.Awal  : Handel penyamplingan (data_sampling.handel) sudah
             dibuat dan lama waktu (waktu) penyampingan sudah berisi
   k.Akhir : Diperoleh data hasil penyamplingan yang disimpan
             didalam sinyal.s dengan panjang sinyal sinyal.panjang
*/

void hancur_handel_sampling();
/* Menghancurkan handel penyamplingan
   K.Awal  : Handel Penyamplingan (data_sampling.handel) sudah dibuat
   K.Akhir : Handel Penyamlingan (data_sampling.handel) hancur
*/

#endif
