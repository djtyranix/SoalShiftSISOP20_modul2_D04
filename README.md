# Laporan Penjelasan dan Penyelesaian Praktikum Sistem Operasi 2020
# Modul 2
## Kelompok D04
1. Michael Ricky (05111840000078)
2. Yaniar Pradityas Effendi (05111840000047)

# Penjelasan dan Penyelesaian Soal Praktikum
## 1. Soal Nomor 1
Link ke file yang dibuat:
* [soal1.c](https://github.com/djtyranix/SoalShiftSISOP20_modul2_D04/blob/master/soal1/soal1.c) - Soal 1

## Soal
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai
c. Program hanya menerima 1 config cron
d. Program berjalan di background (daemon)
e. Tidak boleh menggunakan fungsi system()
Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.

## Jawaban
File sudah tersedia, tetapi masih error.

## 2. Soal Nomor 2
Link ke file yang dibuat:
* [soal2.c](https://github.com/djtyranix/SoalShiftSISOP20_modul2_D04/blob/master/soal2/soal2.c) - Soal 2

## Soal
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.
a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].
b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah

detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" yang siap di run(executable) untuk

menterminasi semua operasi program tersebut. Setelah di run, program yang
menterminasi ini lalu akan mendelete dirinya sendiri.
e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
Buatlah program dalam mimpi Kiwa jadi nyata!
Catatan:
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal
Hint:
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
tertentu
- Epoch Unix bisa didapatkan dari time()

## Jawaban
Untuk jawaban belum ada.

## 3. Soal Nomor 3
Link ke file yang dibuat:
* [soal3.c](https://github.com/djtyranix/SoalShiftSISOP20_modul2_D04/blob/master/soal3/soal3.c) - Soal 3

## Soal
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).
a. Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
“/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.
c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
“/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
“/home/[USER]/modul2/indomie/”.
d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
3 detik kemudian membuat file bernama “coba2.txt”.
(contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
program tersebut.
Catatan :
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk

## Jawaban
```
void moving (const char* path)
```

Fungsi moving merupakan fungsi untuk memindahkan folder dan file hasil ekstrak yang berada di folder jpg, ke folder indomie untuk folder dan ke folder sedaap untuk yang berupa file. Kemudian di fungsi ini juga membuat file coba1.txt dan coba2.txt untuk masing masing folder yang telah dipindahkan ke folder indomie. Fungsi tidak mengembalikan nilai apapun.
```
  while ((a = readdir(dir)) != NULL){
    if (strcmp(a->d_name, ".") == 0 || strcmp(a->d_name, "..") == 0){
      continue;
    }
```

untuk direktori “.” dan “..” dilewati.
```
      if(a->d_type == DT_DIR){
        sprintf(src,"%s%s%s", "/home/yaniarpe/modul2/jpg/", a->d_name, "/");
        sprintf(src2,"%s%s%s", "/home/yaniarpe/modul2/indomie/", a->d_name, "/");
        sprintf(file,"%s%s", src2, "coba1.txt");
        sprintf(file2,"%s%s", src2, "coba2.txt");
        child_id2 = fork();
        if (child_id2 < 0) {
          exit(EXIT_FAILURE);
        }
        if (child_id2 == 0){
          char *argv4[] = {"mv", src, "/home/yaniarpe/modul2/indomie/", NULL};
          execv("/bin/mv", argv4);
        }
```

Jika direktori berjenis folder, format path asal nama folder disimpan ke dalam src, sementara src2 untuk menyimpan format path nama folder jika telah dipindah. Dan variabel file dan file2 menyimpan path untuk file txt yang akan dibuat. Pemindahan folder dilakukan dengan execv() yang melakukan mv.
```
          if (child == 0) {
            char *argv5[] = {"touch", file, NULL};
            execv("/usr/bin/touch", argv5);
          }
          else{
            while((wait(&status))>0){
              sleep(3);
              char *argv5[] = {"touch", file2, NULL};
              execv("/usr/bin/touch", argv5);
            }
```

Ini untuk membuat file kosong coba1.txt dan coba2.txt pada setiap folder yang memiliki format nama sesuai variabel file dan file2
```      
      else{
        sprintf(src,"%s%s", "/home/yaniarpe/modul2/jpg/", a->d_name);
        char *argv6[] = {"mv", src, "/home/yaniarpe/modul2/sedaap/", NULL};
        execv("/bin/mv", argv6);
      }
```

untuk direktori jenis file dipindah ke folder sedaap dengan execv() seperti di atas

Pada fungsi main, dibuat banyak child untuk melakukan execv() sesuai kebutuhan.
```
      char *argv1[] = {"mkdir", "-p", "/home/yaniarpe/modul2/indomie/", NULL};
      execv("/bin/mkdir", argv1);
```

Untuk membuat folder indomie di dalam folder modul2 menggunakan execv() menjalankan mkdir
```
      while((wait(&status))>0){
        sleep(5);
        char *argv2[] = {"mkdir", "-p", "/home/yaniarpe/modul2/sedaap/", NULL};
        execv("/bin/mkdir", argv2);
      }
```

Untuk membuat folder sedaap di dalam folder modul2 menggunakan execv() menjalankan mkdir. Namun folder sedaap baru dibuat 5 detik setelah pembuatan folder indomie sehingga diberi jeda dengan sleep(5).
```
        char *argv3[] = {"unzip", "/home/yaniarpe/modul2/jpg.zip", "-d", "/home/yaniarpe/modul2/", NULL};
        execv("/usr/bin/unzip", argv3);
```     

Untuk melakukan extract pada file jpg.zip dapat menggunakan execv() unzip dan hasil ekstrak disimpan di folder modul2 seperti di atas.
```
        moving ("/home/yaniarpe/modul2/jpg/");
```

Untuk memanggil fungsi moving dilakukan seperti di atas.

Berikut adalah hasilnya :

![Hasil Soal 1](https://github.com/djtyranix/SoalShiftSISOP20_modul2_D04/blob/master/soal1/images/image.png)
