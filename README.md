# soal-shift-sisop-modul-4-B10-2021

# Soal 1

Di suatu jurusan, terdapat admin lab baru yang super duper gabut, ia bernama Sin. Sin baru menjadi admin di lab tersebut selama 1 bulan. Selama sebulan tersebut ia bertemu orang-orang hebat di lab tersebut, salah satunya yaitu Sei. Sei dan Sin akhirnya berteman baik. Karena belakangan ini sedang ramai tentang kasus keamanan data, mereka berniat membuat filesystem dengan metode encode yang mutakhir. Berikut adalah filesystem rancangan Sin dan Sei :
	
NOTE : 
Semua file yang berada pada direktori harus ter-encode menggunakan Atbash cipher(mirror).
Misalkan terdapat file bernama kucinglucu123.jpg pada direktori DATA_PENTING
“AtoZ_folder/DATA_PENTING/kucinglucu123.jpg” → “AtoZ_folder/WZGZ_KVMGRMT/pfxrmtofxf123.jpg”
Note : filesystem berfungsi normal layaknya linux pada umumnya, Mount source (root) filesystem adalah directory /home/[USER]/Downloads, dalam penamaan file ‘/’ diabaikan, dan ekstensi tidak perlu di-encode.
Referensi : https://www.dcode.fr/atbash-cipher

a. Jika sebuah direktori dibuat dengan awalan “AtoZ_”, maka direktori tersebut akan menjadi direktori ter-encode.  
b. Jika sebuah direktori di-rename dengan awalan “AtoZ_”, maka direktori tersebut akan menjadi direktori ter-encode.  
c. Apabila direktori yang terenkripsi di-rename menjadi tidak ter-encode, maka isi direktori tersebut akan terdecode.  
d. Setiap pembuatan direktori ter-encode (mkdir atau rename) akan tercatat ke sebuah log. Format : /home/[USER]/Downloads/[Nama Direktori] → /home/[USER]/Downloads/AtoZ_[Nama Direktori]  
e. Metode encode pada suatu direktori juga berlaku terhadap direktori yang ada di dalamnya (rekursif).    

Jawaban : Pada suatu direktori yang apabila direname menjadi ``AtoZ_`` akan di enskripsi dengan algoritma atbash cipher dan yang semula ``AtoZ_[nama file]`` menjadi ``[nama file]`` akan dilakukan deskripsi dengan algoritma atbash pula. Maka untuk fungsi enskrip maupun deskrip dengan fungsi atbash cipher yaitu : 

```c
void encryptAtbash(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")) return;
	
	printf("encrypt path Atbash: %s\n", path);
	
	int endid = split_ext_id(path);
	if(endid == strlen(path)) endid = ext_id(path);
	int startid = slash_id(path, 0);
	
	for (int i = startid; i < endid; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char tmp = path[i];
			if(isupper(path[i])) tmp -= 'A';
			else tmp -= 'a';
			tmp = 25 - tmp; //Atbash cipher
			if(isupper(path[i])) tmp += 'A';
			else tmp += 'a';
			path[i] = tmp;
		}
	}
}

void decryptAtbash(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")) return;
	
	printf("decrypt path Atbash: %s\n", path);
	
	int endid = split_ext_id(path);
	if(endid == strlen(path)) endid = ext_id(path);
	int startid = slash_id(path, endid);
	
	for (int i = startid; i < endid; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char tmp = path[i];
			if(isupper(path[i])) tmp -= 'A';
			else tmp -= 'a';
			tmp = 25 - tmp; //Atbash cipher
			if(isupper(path[i])) tmp += 'A';
			else tmp += 'a';
			path[i] = tmp;
		}
	}
}
```  
Pada fungsi enskripsi dan deskripsi tersebut dalam memperoleh nama file maupun folder maka dilakukan pengecekan letak folder terakhir yakni ditandai dengan slash(/) terakhir dan letak file terakhir yakni ditandai dengan titik (.) terakhir. Pengecekan tersebut dilakukan pada saat looping. Dimana folder maupun file terakhir itulah yang akan dilakukan proses enskripsi maupun deskripsi menggunakan atbash cipher. 

Apabila fungsi enskrip maupun deskrip tersebut berjalan atau dipanggil oleh suatu fungsi lain maka akan dicatat pada file log yaitu SinSeiFS.log dimana pencatatan ini memiliki fungsi tersendiri yang akan dijelaskan pada soal nomer 4.  
Dokumentasi :  
- sebelum rename direktori  
pada file system :  
![image](https://user-images.githubusercontent.com/55240758/121781891-0bb5cf80-cbd1-11eb-9464-d9a6cbf11cd1.png)   
![image](https://user-images.githubusercontent.com/55240758/121782566-5422bc80-cbd4-11eb-8af2-63f864d97c38.png)  
pada downloads :  
![image](https://user-images.githubusercontent.com/55240758/121782576-643a9c00-cbd4-11eb-86a6-84dd72e73d64.png)  
![image](https://user-images.githubusercontent.com/55240758/121782172-74517c00-cbd2-11eb-879a-bc9aa9c04c30.png)  
- rename direktori menjadi "AtoZ_coba" (enskripsi)  
pada file system :  
![image](https://user-images.githubusercontent.com/55240758/121782826-b7611e80-cbd5-11eb-8a3d-2ef486fb3cf9.png) 
![image](https://user-images.githubusercontent.com/55240758/121782837-c5af3a80-cbd5-11eb-9c0f-3387020ac859.png)  
pada download :  
![image](https://user-images.githubusercontent.com/55240758/121782850-d2339300-cbd5-11eb-9b7d-a097ba5c8aef.png)
![image](https://user-images.githubusercontent.com/55240758/121782864-df508200-cbd5-11eb-83cb-2f85c93abfc1.png)  
- rename direktori menjadi "hadeh" (deskripsi)   
pada file system :  
![image](https://user-images.githubusercontent.com/55240758/121782742-46ba0200-cbd5-11eb-8fa7-faaafb9bb79b.png)  
![image](https://user-images.githubusercontent.com/55240758/121782763-5fc2b300-cbd5-11eb-865d-03340da93399.png)  
pada download :  
![image](https://user-images.githubusercontent.com/55240758/121782779-6d783880-cbd5-11eb-89d8-01e5611c1068.png)  
![image](https://user-images.githubusercontent.com/55240758/121782785-7701a080-cbd5-11eb-9d6d-24666e053c8d.png)  
- log  
![image](https://user-images.githubusercontent.com/55240758/121782963-6f8ec700-cbd6-11eb-8ce4-d84fbef4736c.png)  

- Hasil Encode log
![image](https://github.com/Fitrah1812/soal-shift-sisop-modul-4-B10-2021/blob/main/Dokumentasi/encodelog.jpeg)

# Soal 2

Selain itu Sei mengusulkan untuk membuat metode enkripsi tambahan agar data pada komputer mereka semakin aman. Berikut rancangan metode enkripsi tambahan yang dirancang oleh Sei
a. Jika sebuah direktori dibuat dengan awalan “RX_[Nama]”, maka direktori tersebut akan menjadi direktori terencode beserta isinya dengan perubahan nama isi sesuai kasus nomor 1 dengan algoritma tambahan ROT13 (Atbash + ROT13).  
b. Jika sebuah direktori di-rename dengan awalan “RX_[Nama]”, maka direktori tersebut akan menjadi direktori terencode beserta isinya dengan perubahan nama isi sesuai dengan kasus nomor 1 dengan algoritma tambahan Vigenere Cipher dengan key “SISOP” (Case-sensitive, Atbash + Vigenere).  
c. Apabila direktori yang terencode di-rename (Dihilangkan “RX_” nya), maka folder menjadi tidak terencode dan isi direktori tersebut akan terdecode berdasar nama aslinya.  
d. Setiap pembuatan direktori terencode (mkdir atau rename) akan tercatat ke sebuah log file beserta methodnya (apakah itu mkdir atau rename).  
e. Pada metode enkripsi ini, file-file pada direktori asli akan menjadi terpecah menjadi file-file kecil sebesar 1024 bytes, sementara jika diakses melalui filesystem rancangan Sin dan Sei akan menjadi normal. Sebagai contoh, Suatu_File.txt berukuran 3 kiloBytes pada directory asli akan menjadi 3 file kecil yakni:  

Suatu_File.txt.0000  
Suatu_File.txt.0001  
Suatu_File.txt.0002  

Ketika diakses melalui filesystem hanya akan muncul Suatu_File.txt  

Jawaban : Sama seperti pengerjaan no.1, namun pada nomer ini, pada suatu direktori yang apabila direname menjadi ``RX_`` akan di enskripsi dengan algoritma atbash+ROT13 dan yang semula ``RX_[nama folder]`` menjadi ``[nama folder]`` akan dilakukan deskripsi dengan algoritma Vigenere Cipher dengan key “SISOP” (Case-sensitive, Atbash + Vigenere). Maka untuk fungsi enskrip maupun deskrip dengan ROT13  dan Vigenere Cipher yaitu :  
```c
void encryptRot13(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")) return;
	
	printf("encrypt path ROT13: %s\n", path);
	
	int endid = split_ext_id(path);
	int startid = slash_id(path, 0);
	
	for (int i = startid; i < endid; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char tmp = path[i];
			if(isupper(path[i])) tmp -= 'A';
			else tmp -= 'a';
			tmp = (tmp + 13) % 26; //ROT13 cipher
			if(isupper(path[i])) tmp += 'A';
			else tmp += 'a';
			path[i] = tmp;
		}
	}
}

void decryptRot13(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")) return;
	
	printf("decrypt path ROT13: %s\n", path);
	
	int endid = split_ext_id(path);
	int startid = slash_id(path, endid);
	
	for (int i = startid; i < endid; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char tmp = path[i];
			if(isupper(path[i])) tmp -= 'A';
			else tmp -= 'a';
			tmp = (tmp + 13) % 26; //ROT13 cipher
			if(isupper(path[i])) tmp += 'A';
			else tmp += 'a';
			path[i] = tmp;
		}
	}
}

void encryptVigenere(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")) return;
	
	printf("encrypt path Vigenere: %s\n", path);
	
	int endid = split_ext_id(path);
	int startid = slash_id(path, 0);
	
	for (int i = startid; i < endid; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char tmp1 = path[i];
			char tmp2 = key[(i-startid) % strlen(key)];
			if(isupper(path[i])){
				tmp1 -= 'A';
				tmp2 -= 'A';
				tmp1 = (tmp1 + tmp2) % 26; //Vigenere cipher
				tmp1 += 'A';
			}
			else{
				tmp1 -= 'a';
				tmp2 = tolower(tmp2) - 'a';
				tmp1 = (tmp1 + tmp2) % 26; //Vigenere cipher
				tmp1 += 'a';
			}
			path[i] = tmp1;
		}
	}
}

void decryptVigenere(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")) return;
	
	printf("decrypt path Vigenere: %s\n", path);
	
	int endid = split_ext_id(path);
	int startid = slash_id(path, endid);
	
	for (int i = startid; i < endid; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char tmp1 = path[i];
			char tmp2 = key[(i-startid) % strlen(key)];
			if(isupper(path[i])){
				tmp1 -= 'A';
				tmp2 -= 'A';
				tmp1 = (tmp1 - tmp2 + 26) % 26; //Vigenere cipher
				tmp1 += 'A';
			}
			else{
				tmp1 -= 'a';
				tmp2 = tolower(tmp2) - 'a';
				tmp1 = (tmp1 - tmp2 + 26) % 26; //Vigenere cipher
				tmp1 += 'a';
			}
			path[i] = tmp1;
		}
	}
}
```  

selanjutnya dengan menggunakan fungsi strstr(), melakukan pengecekan apakah nama directory dibuat dengan awalan ``RX_`` atau tidak.    

```c
static int xmp_rename(const char *from, const char *to)
{
	int res;
	char frompath[1000], topath[1000];
	
	char *a = strstr(to, atoz);
	if (a != NULL) decryptAtbash(a);
	
	char *b = strstr(from, rx);
	if (b != NULL){
		decryptRot13(b);
		decryptAtbash(b);
	}
	
	char *c = strstr(to, rx);
	if (c != NULL){
		decryptRot13(c);
		decryptAtbash(c);
	}

	sprintf(frompath, "%s%s", dirPath, from);
	sprintf(topath, "%s%s", dirPath, to);

	res = rename(frompath, topath);
	if (res == -1) return -errno;

	tulisLog2("RENAME", frompath, topath);
	
	if (c != NULL){
		enkripsi2(topath);
		tulisLog2("ENCRYPT2", from, to);
	}

	if (b != NULL && c == NULL){
		dekripsi2(topath);
		tulisLog2("DECRYPT2", from, to);
	}
	return 0;
}

```  
Apabila nama direktori tersebut berawalan ``RX_`` pada path yang dituju maka dapat diketahui bahwa direktori tersebut melakukan perename-an dengan menambahkan ``RX_`` pada nama direktori file sistem. Setelah itu pada fungsi enskripsi2, file yang terdapat dalam direktori tersebut akan di split menjadi beberapa file dengan ukuran 1024 bytes pada direktori dengan path asal.  
```c
void enkripsi2(char *fpath)
{
	chdir(fpath);
	DIR *dp;
	struct dirent *dir;
	
	dp = opendir(".");
	if(dp == NULL) return;
	struct stat lol;
	char dirPath[1000];
	char filePath[1000];
	
    while ((dir = readdir(dp)) != NULL){
		printf("dirname %s\n", dir->d_name);
		printf("%s/%s\n", fpath, dir->d_name);
		if (stat(dir->d_name, &lol) < 0);
		else if (S_ISDIR(lol.st_mode)){
			if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0) continue;
			sprintf(dirPath,"%s/%s",fpath, dir->d_name);
			enkripsi2(dirPath);
			printf("dirpath %s\n", dirPath);
		}
		else{
			sprintf(filePath,"%s/%s",fpath,dir->d_name);
			FILE *input = fopen(filePath, "r");
			if (input == NULL) return;
			int bytes_read, count = 0;
			void *buffer = malloc(1024);
			while((bytes_read = fread(buffer, 1, 1024, input)) > 0){
				char newFilePath[1000];
				sprintf(newFilePath, "%s.%04d", filePath, count);
				count++;
				FILE *output = fopen(newFilePath, "w+");
				if(output == NULL) return;
				fwrite(buffer, 1, bytes_read, output);
				fclose(output);
				memset(buffer, 0, 1024);
			}
			fclose(input);
			printf("filepath %s\n", filePath);
			remove(filePath);
		}
	}
    closedir(dp);
}
```  
Namun apabila nama direktori tersebut berawalan ``RX_`` pada path yang asal namun tidak pada path tujuan maka dapat diketahui bahwa direktori tersebut melakukan perename-an dengan menghapus ``RX_`` pada nama direktori file sistem. Setelah itu pada fungsi deskripsi2, file yang terdapat dalam direktori yang semula split menjadi beberapa file dengan ukuran 1024 bytes akan digabungkan menjadi satu pada direktori pada path asal.   

Apabila fungsi enskrip maupun deskrip tersebut berjalan atau dipanggil oleh suatu fungsi lain maka akan dicatat pada file log yaitu SinSeiFS.log dimana pencatatan ini memiliki fungsi tersendiri yang akan dijelaskan pada soal nomer 4.  

Dokumentasi :  
- sebelum rename direktori  
pada file system :  
![image](https://user-images.githubusercontent.com/55240758/121781891-0bb5cf80-cbd1-11eb-9464-d9a6cbf11cd1.png)  
![image](https://user-images.githubusercontent.com/55240758/121782566-5422bc80-cbd4-11eb-8af2-63f864d97c38.png)  
pada downloads :  
![image](https://user-images.githubusercontent.com/55240758/121782576-643a9c00-cbd4-11eb-86a6-84dd72e73d64.png)
![image](https://user-images.githubusercontent.com/55240758/121782172-74517c00-cbd2-11eb-879a-bc9aa9c04c30.png)  
- rename direktori menjadi "RX_coba" (enskripsi)  
pada file system :
![image](https://user-images.githubusercontent.com/55240758/121782260-e3c76b80-cbd2-11eb-8635-2c59f439bd44.png)  
pada download :  
![image](https://user-images.githubusercontent.com/55240758/121782360-52a4c480-cbd3-11eb-81cd-f3f895d8027c.png)  
- rename direktori menjadi "coba" (deskripsi)   
pada file system :  
![image](https://user-images.githubusercontent.com/55240758/121782468-bfb85a00-cbd3-11eb-9ccc-f2720da765e3.png)  
pada downloads :  
![image](https://user-images.githubusercontent.com/55240758/121782448-aca58a00-cbd3-11eb-88c1-cf1ff1bbe92e.png)  



# Soal 3

Karena Sin masih super duper gabut akhirnya dia menambahkan sebuah fitur lagi pada filesystem mereka. 
a. Jika sebuah direktori dibuat dengan awalan “A_is_a_”, maka direktori tersebut akan menjadi sebuah direktori spesial.  
b. Jika sebuah direktori di-rename dengan memberi awalan “A_is_a_”, maka direktori tersebut akan menjadi sebuah direktori spesial.  
c. Apabila direktori yang terenkripsi di-rename dengan menghapus “A_is_a_” pada bagian awal nama folder maka direktori tersebut menjadi direktori normal.  
d. Direktori spesial adalah direktori yang mengembalikan enkripsi/encoding pada direktori “AtoZ_” maupun “RX_” namun masing-masing aturan mereka tetap berjalan pada direktori di dalamnya (sifat recursive  “AtoZ_” dan “RX_” tetap berjalan pada subdirektori).  
e. Pada direktori spesial semua nama file (tidak termasuk ekstensi) pada fuse akan berubah menjadi lowercase insensitive dan diberi ekstensi baru berupa nilai desimal dari binner perbedaan namanya.  


Contohnya jika pada direktori asli nama filenya adalah “FiLe_CoNtoH.txt” maka pada fuse akan menjadi “file_contoh.txt.1321”. 1321 berasal dari biner 10100101001.  

Jawaban : Berikut cara yang dilakukan adalah dengan cara membuat encrypt dan decrypt dari folder yang spesial yaitu melakukan encrypt dengan memperhatikan posisi huruf besar dan huruf kecil apabila huruf besar maka akan dipassing nilai 1 di biner sedangkan apabila sudah huruf kecil maka akan dipassing nol.   

fungsi get binary :  
```c
void getBinary(char *fname, char *bin, char *lowercase){

	int endid = ext_id(fname);

	int startid = slash_id(fname, 0);

	int i;

	for(i=startid; i<endid; i++){
		if(isupper(fname[i])){

			bin[i] = '1';
			lowercase[i] = fname[i] + 32;
		}
		else{

			bin[i] = '0';
			lowercase[i] = fname[i];
		}
	}

	bin[endid] = '\0';

	for(; i<strlen(fname); i++){

		lowercase[i] = fname[i];
	}

	lowercase[i] = '\0';
}
```  
 fungsi bin_to_dec:
```c
int bin_to_dec(char *bin){

	int tmp = 1, res = 0;

	for(int i=strlen(bin)-1; i>=0; i--){

		if(bin[i] == '1') res += tmp;

		tmp *= 2;

	}

	return res;

}
```

```c
int convertDec(char *ext){

	int dec = 0, pengali = 1;

	for(int i=strlen(ext)-1; i>=0; i--){

		dec += (ext[i]-'0')*pengali;

		pengali *= 10;

	}

	return dec;

}
```

```c
void dec_to_bin(int dec, char *bin, int len){

	int idx = 0;

	while(dec){

		if(dec & 1) bin[idx] = '1';

		else bin[idx] = '0';

		idx++;

		dec /= 2;

	}

	while(idx < len){

		bin[idx] = '0';

		idx++;

	}

	bin[idx] = '\0';

	

	for(int i=0; i<idx/2; i++){

		char tmp = bin[i];

		bin[i] = bin[idx-1-i];

		bin[idx-1-i] = tmp;

	}

}
```  

```c
void encryptBinary(char *fpath)
{
	chdir(fpath);
	DIR *dp;
	struct dirent *dir;
	struct stat lol;
	dp = opendir(".");
	if(dp == NULL) return;
	
	char dirPath[1000];
	char filePath[1000];
	char filePathBinary[1000];
	
    while ((dir = readdir(dp)) != NULL){
		if (stat(dir->d_name, &lol) < 0);
		else if (S_ISDIR(lol.st_mode)){
			if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0) continue;
			sprintf(dirPath,"%s/%s",fpath, dir->d_name);
			encryptBinary(dirPath);
		}
		else{
			sprintf(filePath,"%s/%s",fpath, dir->d_name);
			char bin[1000], lowercase[1000];
			getBinary(dir->d_name, bin, lowercase);
			int dec = bin_to_dec(bin);
			sprintf(filePathBinary,"%s/%s.%d",fpath,lowercase,dec);
			rename(filePath, filePathBinary);
		}
	}
    closedir(dp);
}

void decryptBinary(char *fpath)
{
	chdir(fpath);
	DIR *dp;
	struct dirent *dir;
	struct stat lol;
	dp = opendir(".");
	if(dp == NULL) return;
	
	char dirPath[1000];
	char filePath[1000];
	char filePathDecimal[1000];
	
    while ((dir = readdir(dp)) != NULL){
		if (stat(dir->d_name, &lol) < 0);
		else if (S_ISDIR(lol.st_mode)){
			if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0) continue;
			sprintf(dirPath,"%s/%s",fpath, dir->d_name);
			decryptBinary(dirPath);
		}
		else{
			sprintf(filePath,"%s/%s",fpath, dir->d_name);
			char fname[1000], bin[1000], normalcase[1000], clearPath[1000];
			
			strcpy(fname, dir->d_name);
			char *ext = strrchr(fname, '.');
			int dec = convertDec(ext+1);
			for(int i=0; i<strlen(fname)-strlen(ext); i++) clearPath[i] = fname[i];
			
			char *ext2 = strrchr(clearPath, '.');
			dec_to_bin(dec, bin, strlen(clearPath)-strlen(ext2));
			getDecimal(clearPath, bin, normalcase);
			sprintf(filePathDecimal,"%s/%s",fpath,normalcase);
			rename(filePath, filePathDecimal);
		}
	}
    closedir(dp);
}

```  
Apabila fungsi enskrip maupun deskrip tersebut berjalan atau dipanggil oleh suatu fungsi lain maka akan dicatat pada file log yaitu SinSeiFS.log dimana pencatatan ini memiliki fungsi tersendiri yang akan dijelaskan pada soal nomer 4.  

Hasilnya adalah sebagai berikut :

Folder sebelumnya :

![image](https://github.com/Fitrah1812/soal-shift-sisop-modul-4-B10-2021/blob/main/Dokumentasi/Awal.jpeg)

Folder setelahnya :

![image2](https://github.com/Fitrah1812/soal-shift-sisop-modul-4-B10-2021/blob/main/Dokumentasi/Awal.jpeg)



# Soal 4

Untuk memudahkan dalam memonitor kegiatan pada filesystem mereka Sin dan Sei membuat sebuah log system dengan spesifikasi sebagai berikut.
a. Log system yang akan terbentuk bernama “SinSeiFS.log” pada direktori home pengguna (/home/[user]/SinSeiFS.log). Log system ini akan menyimpan daftar perintah system call yang telah dijalankan pada filesystem.  
b. Karena Sin dan Sei suka kerapian maka log yang dibuat akan dibagi menjadi dua level, yaitu INFO dan WARNING.  
c. Untuk log level WARNING, digunakan untuk mencatat syscall rmdir dan unlink.  
d. Sisanya, akan dicatat pada level INFO.  
e. Format untuk logging yaitu:  


[Level]::[dd][mm][yyyy]-[HH]:[MM]:[SS]:[CMD]::[DESC :: DESC]

Level : Level logging, dd : 2 digit tanggal, mm : 2 digit bulan, yyyy : 4 digit tahun, HH : 2 digit jam (format 24 Jam),MM : 2 digit menit, SS : 2 digit detik, CMD : System Call yang terpanggil, DESC : informasi dan parameter tambahan

INFO::28052021-10:00:00:CREATE::/test.txt
INFO::28052021-10:01:00:RENAME::/test.txt::/rename.txt

Jawaban : Berikut menrupakan hasil untuk menampilkan dengan yang diinginkan oleh soal apabila terdapat rmdir dan unlink maka diminta menuliskan warning dan sisanya akan ditulis sebagai INFO.

File info dan warning dibuat untuk mengeluarkan hal-hal yang diminta oleh soal

```c
void tulisLog(char *nama, char *fpath)
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char haha[1000];

	FILE *file;
	file = fopen("/home/fitraharie/SinSeiFS.log", "a");

	if (strcmp(nama, "RMDIR") == 0 || strcmp(nama, "UNLINK") == 0)
		sprintf(haha, "WARNING::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, nama, fpath);
	else
		sprintf(haha, "INFO::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, nama, fpath);

	fputs(haha, file);
	fclose(file);
	return;
}

void tulisLog2(char *nama, const char *from, const char *to)
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char haha[1000];

	FILE *file;
	file = fopen("/home/fitraharie/SinSeiFS.log", "a");

	if (strcmp(nama, "RMDIR") == 0 || strcmp(nama, "UNLINK") == 0)
		sprintf(haha, "WARNING::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, nama, from, to);
	else
		sprintf(haha, "INFO::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, nama, from, to);

	fputs(haha, file);
	fclose(file);
	return;
}

```


Hasilnya adalah sebagai berikut :

![image](https://github.com/Fitrah1812/soal-shift-sisop-modul-4-B10-2021/blob/main/Dokumentasi/WarningInfo.jpeg)


