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

# Soal 2
Tujuan dari soal 2 ini adalah melakukan ekstrak pada file zip [pets.zip](https://drive.google.com/file/d/1g5rehatLEkqvuuK_eooHJXB57EfdnxVD/view?usp=sharing) dengan kondisi tertentu. Implementasi dari soal ini, kami membutuhkan beberapa fungsi bantuan, di antaranya sebagai berikut
![soal2_1](../screenshots/soal2_1.png)

## Soal 2a
Pada soal 2a kita diminta untuk melakukan ekstrak file zip [pets.zip](https://drive.google.com/file/d/1g5rehatLEkqvuuK_eooHJXB57EfdnxVD/view?usp=sharing) namun yang diminta hanya file `.jpg` dan menghapus yang selainnya. Untuk itu kita melakukan pemanggilan function `unzipAndCleanFiles()` serta dan `file_list()`
#### unzipAndCleanFiles()
1. Function ini untuk melakukan ekstraksi. Function dipanggil di dalam child process dengan pemanggilan `child_unzip = fork();`.
2. Di dalam function `unzipAndCleanFiles()` dilakukan pemanggilan child proses `child_mkdir = fork();` untuk membuat folder files (agar lebih rapi saja). Di dalam child proses, dilakukan `execv("/usr/bin/mkdir", argv);` dengan argumen `char *argv[] = {"mkdir", "files", NULL};`.
3. Selanjutnya pada parent proses dilakukan ekstrak `execv("/usr/bin/unzip", argv);` dengan argumen `char *argv[] = {"unzip", "../pets.zip", "*", NULL};`. Sebelum itu dilakukan perpindahan directory dengan `chdir("/home/[user]/soal-shift-sisop-modul-2-A08-2021/soal2/files");`.

#### file_list()
1. Function ini untuk melakukan penyetoran list file ke dalam array sekaligus menghapus semua isi selain file `.png` serta function bertipe data `size_t`. Function kami ambil referensi dari [sini](https://stackoverflow.com/a/11291863).
2. Function menerima argumen berupa directory `files` tadi dan `&files` bertipe `char` double pointer.
3. Pada Function, directory diterima oleh parameter `path` dan dimasukkan ke variabel `dp`. Jika `dp` NULL maka dilakukan pengembalian tidak ada directory. Argument kedua merupakan pointer `files` yang diterima oleh variabel `ls`. Nantinya ls ini sebagai return parameter yang berisi list file pada directory `dp`.
4. Selanjutnya terdapat variable temporary `ep = readdir(dp);` untuk melakukan perhitungan jumlah file pada directory `dp` dengan perulangan `while (NULL != ep)` dengan isi `count++`. Variable `count` nantinya untuk mengalokasikan jumlah memory array `ls` serta sebagai return value.
5. Dilakukan perulangan yang sama kembali dengan nomor 4, namun kali ini untuk mengambil list file. Diberikan conditional `if (!strcmp(ep->d_name, ".") == 0 && !strcmp(ep->d_name, "..") == 0)` untuk menghindari file `.` dan `..` serta conditional lagi `if (strcmp(strrchr(temp, '\0') - 4, ".jpg") == 0` untuk mengambil hanya berekstensi `.jpg`.
6. Pada kondisional kedua tersebut, pada cabang bernilai `True` melakukan penyetoran nama file `(*ls)[count++] = strdup(ep->d_name);`. Untuk cabang `False` melakukan penghapusan file atau folder.
7. Implementasi penghapusan pada nomor 6 adalah menggunakan pemanggilan `child_rmdir = fork();` dengan proses `execv("/usr/bin/rm", {"rm", "-r", filedir, NULL});`.
8. Terakhir dilakukan return value `count` serta didapatkan list file pada `files` yang direturn dari parameter.

## Soal 2b
Pada Soal 2b diminta untuk melakukan pembuatan folder tiap hewan. 
1. Pertama kita lakukan iterasi dari dari `files` dari 0 hingga `count`. Iterasi dilakukan kepada tiap nilai dari `files` atau tiap `files[i]`. Selanjutnya kita melakukan pengambilan nama hewan pada nama file serta pemisahan hewan yang memiliki 2 nama hewan dalam 1 file. 
2. Untuk pengambilan nama hewan, kita replace nama file 4 charachter terakhir dengan `\0` atau `files[i][strlen(files[i]) - 4] = '\0';`
3. Selanjutnya dilakukan pemisahan str nama file dengan delimiter `_` sehingga didapatkan nama hewan tiap individu yang mana disimpan dalam variabel `individualPets` atauj dengan syntax `dtmsplit(files[i], "_", &individualPets, &countTok);`. `countTok` untuk menghitung jumlah hewan individu setelah dilakukan pemisahan
4. Selanjuta tiap individu hewan dilakukan iterasi untuk diambil tiap nilai nama file dengan delimiter `;` (bila tidak gabungan, diiterasi sekali) atau dengan syntax `d = dtmsplit(temp, ";", &petAtr, &petAtrTok);`.Hasil pemisahan disimpan dalam variable `petAtr`. 
5. Di dalam perulangan yang sama, dilakukan pemanggilan  `child_id_mkdir = fork();`. Pada child process dilakukan pembuatan folder dengan `execv("/usr/bin/mkdir", {"mkdir", "-p", petDir, NULL});` dengan nilai `petDir` adalah hasil dari `sprintf(petDir, "petshop/%s", petAtr[0]);`. `petAtr[0]` adalah data nama hewannya. tanda `-p` pada mkdir untuk membatalkan pembuatan folder bila nama folder sudah ada.

## Soal 2c
Pada soal 2c diminta untuk memasukkan file `jgp` tersebut ke folder yang sesuai dengan nama hewan.
1. Untuk menyelesaikan permasalahn ini kita melanjutkan perulangan terakhir pada soal 2b. Setelah selesai pembuatan folder pada child process, dilanjutkan pemindahan file pada parent process.
2. Pertama kami melakukan pemanggilan `child_id_cp = fork();` untuk melakukan pemindahan.
3. Pertama dilakukan pemasukan nilai nama file ke variable temporary dengan `strcpy(filesUntouched, files[i]);`. Variable `filesUntouched` dimasukkan ke variable `fromFile` sebagai file asal dengan `sprintf(fromFile, "%s", filesUntouched);`. Adapun variable `toFile` sebagai destinasi file dengan `sprintf(toFile, "../petshop/%s/%s.jpg", petAtr[0], petAtr[1]);`. Kembali lagi, `petAtr[0]` adalah nama jeni hewan dan `petAtr[1]` adalah nama asli hewan tersebut.
4. Terakhir, kita lakukan copy file dengan `execv("/usr/bin/cp", {"cp", fromFile, toFile, NULL});`

## Soal 2d
Pada soal 2d diminta untuk memisahkan 1 foto yang sama yang memiliki 2 hewan berbeda, namun nama file menyesuaikan pada folder mana dia dimasukkan.
1. Hal ini sudah teratasi karena pada iterasi sebelumnya, yaitu `for (int j = 0; j < countTok; j++)` sudah menghimpun 2 hewan berbeda dalam satu file yang sama.

## Soal 2e
Pada soal 2e kita diminta untuk membuat file `keterangan.txt` berisi data informasi hewan tiap folder.
1. Untuk menyelesaikannya, kita masih pada iterasi yang sama, setiap iterasi dilakukan pemanggilan function `writeLog(petAtr[0], petAtr[1], petAtr[2]);`.
2. Pada function, pertama melakukan penulisan sesuai format yang diminta, yaitu `sprintf(templatePrint, "nama: %s\numur: %s tahun\n\n", nama, umur);`.
3. Membuka file `FILE *keteranganFile`. 
4. Penulisan directory file `sprintf(keteranganLoc, "petshop/%s/keterangan.txt", category);`
5. Pembukaan file dengan parameter `a` agar dapat ditambahkan di bawahnya bila ada penambahan atau append. Syntaxnya adalah `keteranganFile = fopen(keteranganLoc, "a");`
6. Selanjutnya ditulis dengan `fprintf(keteranganFile, "%s", templatePrint);`
7. Lalu terakhir ditutup dengan `fclose(keteranganFile);`



## Referensi Nomor 2

- save file listing into array https://stackoverflow.com/a/11291863
- Split string with delimiters https://stackoverflow.com/a/9210560

## Referensi Nomor 3

- Get Timestamp http://www.cplusplus.com/reference/ctime/localtime/
- Caesar Cipher https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
- argument https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
- get epoch time https://stackoverflow.com/questions/11765301/how-do-i-get-the-unix-timestamp-in-c-as-an-int
