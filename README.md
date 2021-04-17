# Soal 1
![soal1](./screenshots/soal1a1.png)
![soal1](./screenshots/soal1(1).png)
#### Cara Pengerjaan
1. Pada soal kali ini kami menggunakan Plate Daemon dengan destinasi program pada `/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1`
2. Fungsi `getTime` yaitu untuk mendapatkan timeStamp dengan command `strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d_%H:%M:%S", tmp)` sehingga mendapatkan format tersebut.
##  Soal 1a
![soal1a](./screenshots/soal1a2.png)
#### Cara Pengerjaan
1. Kami menggunakan fungsi `void reusable(char *link, char *folderName, char *downloadName)` yang bertujuan untuk membuat folder baru.
2. Command `char baseFolder[200] ="/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/"` dengan store base folder sementara/temp untuk membuat folder baru pada destinasi tersebut
3. `strcat(baseFolder, folderName)` yaitu untuk melakukan rename atau penamaan folder baru sesuai dengan `foldername` yang sudah dideklrasi pada saat fungsi digunakan `reusable(musikLink, "Musyik", "MUSIK/")` seperti berikut sehingga folder akan berlabel `Musyik`.
4. Command `sprintf(filesFolder, "%s/%s", baseFolder, downloadName)` sebagai sebuah temp memindahkan file download ke folder sesuai dengan `baseFolder, downloadName` seperti `Fylm/FILM` sehingga download file langsung masuk ke folder FILM
5. Dengan menggunakan `child_id` Kami melakukan Command `char *argv[] = {"mkdir", folderName, NULL}` dan `execv("/usr/bin/mkdir", argv)` yaitu membuat folder sesuai dengan inisialisasi fungsi contohnya `Musyik`.

## Soal 1b
![soal1b](./screenshots/soal1b1.png)
#### Cara Pengerjaan
1. Kemudian Kami dengan menggunakan `child_id2` untuk melakukan proses download yaitu `sprintf(downloadLoc, "%s/Download.zip", folderName)` sehingga kita mendownload dengan format `Musyik/Download.zip` lalu meletakkan nya pada foldername `Musyik`.
2. Untuk melakukan download kami menggunakan `char *argv[] = {"wget", "-q", "--no-check-certificate", link, "-O",downloadLoc, NULL}` command `wget -q` untuk mendownload dalam keadaan quiet sehingga tidak terdapat pada log. `Link` yaitu alamat download yang diinisialisasikan saat memanggil fungsi seperti contoh `reusable(musikLink, "Musyik", "MUSIK/")` yaitu memanggil musikLink yang sudah dideklarasi sebelumnya. Lalu melakukan `execv("/usr/bin/wget", argv)`.

## Soal 1c
![soal1c](./screenshots/soal1c.png)
#### Cara Pengerjaan
1. Sebelum melakukan uncompress kita harus berpindah dengan `chdir(baseFolder)` dimana baseFolder berada seperti di `Musyik` atau folder yang dideklarasi saat memanggil fungsi.
2. Untuk melakukan uncompress kami menggunakan `char *argv[] = {"unzip", "-q", "Download.zip", NULL}` yaitu unzip Download.zip tetapi masih dalam folder `MUSIK`.

## Soal 1d
![soal1d](./screenshots/soal1d.png)
#### Cara Pengerjaan
1. sebelum memindahkan file tersebut menggunakan `chdir(filesFolder)` untuk pindah ke folder `MUSIK` untuk melakukan proses selanjutnya.
2. Kami menggunakan `char *argv[] = {"cp", "-r", ".", "..", NULL}` dengan `cp` yaitu mengCopy files `.` yaitu semua files pada folder tersebut , yang destinasi nya `..` ke satu folder sebelumnya/parentnya.
3. Karena file tadi masih ada di folder `MUSIK` sehingga kita perlu untuk menghapus folder `MUSIK` beserta isinya dengan `char *argv[] = {"rm", "-r", downloadName, "Download.zip", NULL}`. serta menghapus `Download.zip` yang sebelumnya masih ada.

## Soal 1e
![soal1e1](./screenshots/soal1e1.png)
#### Cara Pengerjaan
1. Dengan menggunakan fungsi getTime kita dapat melakukan `if (child_id == 0) {if (strcmp(time, "2021-04-09_16:22:00") == 0)` sehingga pada saat 6 jam sebelum ULTAH kita melakukan command `runBuildFolder()` untuk melakukan fungsi proses yang dibutuhkan.
![soal1e](./screenshots/soal1e.png)
2. Untuk melakukan semua proses dalam waktu bersamaan kami menggunakan `pid_t child_q1, child_q2` untuk membantu prosesnya multithread. 
3. Dengan `child_q1 = fork()` bertujuan untuk spawn proses pertama. `if (child_q1 == 0) reusable(musikLink, "Musyik", "MUSIK/")` yaitu jika child_q1 = 0 maka proses  akan berjalan.
4. Kemudian `else {child_q2 = fork()` lalu kemudian juga spawn proses kedua dengan variabel child_q2 untuk agar proses berjalan bersamaan. maka `(child_q2 == 0) {reusable(fotoLink, "Pyoto", "FOTO/")` maka proses kedua berjalan juga. dan `else {reusable(filmLink, "Fylm", "FILM/")` proses ketiga juga ikut berjalan pada saat bersamaan.

## Soal 1f
![soal1f](./screenshots/soal1f.png)
#### Cara Pengerjaan
1. Jika sudah memasuki ULTAH `else if (strcmp(time,"2021-04-09_22:22:00") == 0) {zipAndDestroy()` yaitu dengan melakukan fungsi `zipAndDestroy`
2. Pada proses ini, kami menggunakan `char *argv[] = {"zip",   "-r",      "-q",     "Lopyu_Stevany.zip","Fylm/", "Musyik/", "Pyoto/", NULL}` yang bertujuan `zip` yaitu untuk melakukan compress atau zip file, `-q` disini melakukan dengan quiet. `"Lopyu_Stevany.zip"` yaitu untuk label zip. Dan `"Fylm/", "Musyik/", "Pyoto/"` yaitu untuk source melakukan zip pada semua file di folder tersebut.
3. Dan untuk menghapus file yang sudah dilakukan compress/zip yaitu dengan `char *argv[] = {"rm", "-r", "Fylm/", "Musyik/", "Pyoto/", NULL}` . command `rm` disini untuk menghapus file yang terdapat pada folder `Fylm/", "Musyik/", "Pyoto/"`. 

## Referensi Nomor 2

- save file listing into array https://stackoverflow.com/a/11291863
- Split string with delimiters https://stackoverflow.com/a/9210560

## Referensi Nomor 3

- Get Timestamp http://www.cplusplus.com/reference/ctime/localtime/
- Caesar Cipher https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
- argument https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
- get epoch time https://stackoverflow.com/questions/11765301/how-do-i-get-the-unix-timestamp-in-c-as-an-int
