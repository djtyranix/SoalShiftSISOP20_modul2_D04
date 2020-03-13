# Laporan Penjelasan dan Penyelesaian Praktikum Sistem Operasi 2020
# Modul 2
## Kelompok D04
1. Michael Ricky (05111840000078)
2. Yaniar Pradityas Effendi (05111840000047)

# Penjelasan dan Penyelesaian Soal Praktikum
## 1. Soal Nomor 1

## 2. Soal Nomor 2

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
        child_id2 = fork();
        if (child_id2 < 0) {
          exit(EXIT_FAILURE);
        }
        if (child_id2 == 0){
          char *argv4[] = {"mv", src, "/home/yaniarpe/modul2/indomie/", NULL};
          execv("/bin/mv", argv4);
        }
```

Jika direktori berjenis folder, format path asal nama folder disimpan ke dalam src, sementara src2 untuk menyimpan format path nama folder jika telah dipindah. Pemindahan folder dilakukan dengan execv() yang melakukan mv.
```
          if (child_id == 0) {
            sprintf(file,"%s%s", src2, "coba1.txt");
            sprintf(file2,"%s%s", src2, "coba2.txt");
            char *argv5[] = {"touch", file, file2, NULL};
            execv("/usr/bin/touch", argv5);
          }
```

Ini untuk membuat file kosong coba1.txt dan coba2.txt pada setiap folder yang memiliki format nama sesuai variabel src 2
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

