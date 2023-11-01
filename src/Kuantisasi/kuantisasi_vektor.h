#ifndef VKuant_H
#define VKuant_H

#define _eps 0.005

typedef struct
{
  float x; /* koordinat sumbu x */
  float y; /* koordinat sumbu y */
}ttitik;

void alokasi_parameter_kuantisasi(int maks_data,int maks_cendroit);
/* melakukan alokasi memori untuk parameter kuantisasi
   K.Awal  : jumlah maksimum data dan cendroit telah ditentukan
   K.Akhir : parameter kuantisasi dialokasi
*/

void dealokasi_parameter_kuantisasi(int maks_cendroit);
/* melakukan dealokasi memori untuk parameter-parameter kuantisasi
   K.Awal  : parameter kuantisasi telah dialokasi
   K.Akhir : parameter kuantisasi didealokasi
*/

void pengurutan_cendroit(int jumlah_cendroit);
/* melakukan pengurutan cendroit berdasarkan sumbu x
   K.Awal  : cendroit telah berisi nilai
   K.Akhir : cendroit terurut berdasarkan sumbu x
*/

void kuantisasi(float *data,int jumlah_data,int jumlah_cendroit);
/* melakukan kuantisasi terhadap data
   K.Awal  : data, jumlah data dan jumlah cendroit yang akan
             dibuat telah diisikan
   K.Akhir : variabel cendroit.y berisi cendroit hasil kuantisasi
*/

#endif
