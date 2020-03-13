#include <iostream>
using namespace std;

int pointTemp [8][8]={0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0};
char isi [8][8]={'k','k','k','k','k','k','k','k',
				'k','k','k','k','k','k','k','k',
				'k','k','k','k','k','k','k','k',
				'k','k','k','h','p','k','k','k',
				'k','k','k','p','h','k','k','k',
				'k','k','k','k','k','k','k','k',
				'k','k','k','k','k','k','k','k',
				'k','k','k','k','k','k','k','k'};
struct score{
	int pemain;
	int komp;
};
score skor;
struct urutan{
	int baris;
	int kolom;
};
urutan pilih[61];
bool rekurens=false;
int skorTemp=0;

//fungsi
void tampilkanPilihan();
void tampilSkor();
void game();
bool cekSelesai();
char cekVar(char var);
void pemain();
void komputer();
void pilihanJalan();
void cekPartisi(char var,int a, int b,string ubah);
void ubahIsi(int tempA, int tempB, int i, int j, int a, int b, char var);
void skorPilih(int i, int j, int a, int b,char var);
void komputerPilih(char var);
void cekJalan(char var);
void userPilih(char var);
void ubahVariabel(char var, int i);

int main (){
	string nama;
	skor.komp=0;
	skor.pemain=0;
	
	cout<<"Masukkan nama anda\n\n";
	getline(cin,nama); 				//menginputkan nama pemain
	cout<<"\nSelamat bermain!\n";
	
	cout<<"\nTekan ENTER 2x untuk lanjutkan...";
	cin.get(); cin.ignore();
	system("CLS");
	
	game();
	
	if(skor.komp!=skor.pemain){
		cout<<"Pemenangnya adalah ";
		if(skor.komp>skor.pemain){
			cout<<"KOMPUTER\n";
		}else{
			cout<<nama<<"\n";
		}
	}else{
		cout<<"wah kamu hebat, kamu dapat mengimbangi skor komputer\n";
	}cout<<"\n--TERIMAKASIH TELAH BERMAIN!!--\n";
}

void game(){
	if (cekSelesai()==true){
		tampilSkor();
	}else{
		pemain();
		komputer();
		game();
	}
}

bool cekSelesai(){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(isi[i][j]=='k'){
				return false;
			}
		}
	}return true;
}

char cekVar(char var){
	char varLawan;
	
	if(var=='h'){
		varLawan='p';
	}else if(var=='p'){
		varLawan='h';
	}
	return varLawan;
}

void tampilSkor(){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(isi[i][j]=='h'){
				skor.pemain+=1;
			}else if(isi[i][j]=='p'){
				skor.komp+=1;
			}
		}
	}
	
	cout<<"\n----skor----\n";
	cout<<"pemain   : "<<skor.pemain<<endl;
	cout<<"komputer : "<<skor.komp<<endl;
	cout<<"------------\n\n";
	
	skor.komp=0;
	skor.pemain=0;
}

void pemain(){	
	cout<<"---GILIRAN PEMAIN---\n";
	tampilSkor();
	
	cekJalan('h');
	pilihanJalan();		//menampilkan ke layar pilihan mana yang bisa dipilih
	userPilih('h');
	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			pointTemp[i][j]=0;
		}
	}
}

void komputer(){
	cout<<"---GILIRAN KOMPUTER---\n";
	tampilSkor();
	
	cekJalan('p');
	pilihanJalan();
	komputerPilih('p');
			
	for (int i=0;i<8;i++){
		cout<<"|";
		for (int j=0;j<8;j++){
			if(isi[i][j]=='p'){
				cout<<"o|";
			}else if(isi[i][j]=='h'){
				cout<<"x|";
			}else{
				cout<<" |";
			}
		}cout<<"\n";
	}cout<<" - - - - - - - - \n";
	
	//reset matrix point temp
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			pointTemp[i][j]=0;
		}
	}
	
	cout<<"\nTekan ENTER 2x untuk lanjutkan...";
	cin.get(); cin.ignore();
	system("CLS");
}

void cekJalan(char var){ //mengecek apakah bisa jalan di situ jika bisa taruh angka berurutan
	int pilih=0;
	
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if (var==isi [i][j]){
				cekPartisi(var,i,j,"jalan");
			}
		}
	}
}

void cekPartisi(char var,int a, int b,string ubah){		//MENGECEK DI BAGIAN MANA PARTISI BERADA
	int awalI,awalJ,akhirI,akhirJ;					//a dan b menunjukkan posoisi var berada
	char varLawan=cekVar(var);
	
	if (a==0){									//kondisi ketika berada di baris pertama
		if (b==0){
			awalI=a; 
			awalJ=b;
			akhirI=a+1;
			akhirJ=b+1;
		}else if(b==7){
			awalI=a;
			awalJ=b-1;
			akhirI=a+1;
			akhirJ=b;
		}else{
			awalI=a;
			awalJ=b-1;
			akhirI=a+1;
			akhirJ=b+1;
		}
	}else if (a==7){							//kondisi ketika berada di baris terakhir
		if (b==0){
			awalI=a-1;
			awalJ=b;
			akhirI=a;
			akhirJ=b+1;
		}else if(b==7){
			awalI=a-1;
			awalJ=b-1;
			akhirI=a;
			akhirJ=b;
		}else{
			awalI=a-1;
			awalJ=b-1;
			akhirI=a;
			akhirJ=b+1;
		}
	}else{
		awalI=a-1;
		awalJ=b-1;
		akhirI=a+1;
		akhirJ=b+1;
	}
			
	for (int i=awalI;i<=akhirI;i++){
		for (int j=awalJ;j<=akhirJ;j++){
			if(i!=a || j!=b){
				if (ubah=="ubah"){	
					if (isi[i][j]==varLawan){
						ubahIsi(a,b,i,j,a,b,var);
					}
				}else{
					if (isi[i][j]==varLawan){
						skorPilih(i,j,a,b,var);
					}
				}
			}
		}
	}
}


void ubahIsi(int tempA, int tempB, int i, int j, int a, int b, char var){ //i dan j menunjukkan tempat varLawan berada, sementara a dan b adalah tempat dimana var akan berada
	if (a>i){		//var berada di atas varLawan
		if (b>j){ 			//var berada di kanan varlawan
			tempA-=1;
			tempB-=1;
		}else if (b<j){		//var berada di kiri varlawan
			tempA-=1;
			tempB+=1;
		}else{				//var berada tegak dgn varlawan
			tempA-=1;
		}
	}else if (a<i){		//var berada di bawah varLawan
		if (b>j){ 			//varLawan berada di kanan var
			tempA+=1;
			tempB-=1;
		}else if (b<j){		//var berada di kiri varlawan
			tempA+=1;
			tempB+=1;
		}else{				//var berada tegak dgn varlawan
			tempA+=1;
		}
	}else if (a==i){	//var berada sebaris dgn varLawan
		if (b>j){ 		//var berada di kanan var
			tempB-=1;
		}else if (b<j){	//var berada di kiri var
			tempB+=1;
		}
	}
	
	if (isi[tempA][tempB]==var){
		rekurens=true;
	}else if (tempA<0 || tempA>7 || tempB<0 || tempB>7){
		rekurens=false;
	}else{
		ubahIsi(tempA,tempB,i,j,a,b,var);
		if (rekurens==true){
			isi[tempA][tempB]=var;
		}
	}
}

void skorPilih(int i, int j, int a, int b, char var){	//menampilkan angka terurut sebagai pilihan pada pengguna dan menampilkan skor pada komputer (temp skor)
	//i dan j menunjukkan tempat varLawan berada, sementara a dan b adalah tempat dimana var berada
	int tempA=i,tempB=j;
	char varLawan=cekVar(var);
	
	while (tempA>0 && tempA<7 && tempB>0 && tempB<7){
		if (isi[tempA][tempB]==varLawan){ //mencari isi ketika dia udah sampe kosong belum
			if (a>i){		//var berada di atas varLawan
				if (b>j){ 			//var berada di kanan varlawan
					tempA-=1;
					tempB-=1;
				}else if (b<j){		//var berada di kiri varlawan
					tempA-=1;
					tempB+=1;
				}else{				//var berada tegak dgn varlawan
					tempA-=1;
				}
			}else if (a<i){		//var berada di bawah varLawan
				if (b>j){ 			//varLawan berada di kanan var
					tempA+=1;
					tempB-=1;
				}else if (b<j){		//var berada di kiri varlawan
					tempA+=1;
					tempB+=1;
				}else{				//var berada tegak dgn varlawan
					tempA+=1;
				}
			}else if (a==i){	//var berada sebaris dgn varLawan
				if (b>j){ 		//var berada di kanan var
					tempB-=1;
				}else if (b<j){	//var berada di kiri var
					tempB+=1;
				}
			}
			skorTemp+=1; //simpan poin sementara untuk void komputer
		}else{ 		//kalo udah sama dengan kosong atau sudah sama dengan var 
			break;
		}
	}
	pointTemp[tempA][tempB]=skorTemp;	//menyimpan poin ke array pointTemp
	skorTemp=0;
}

void pilihanJalan(){
	int urut=1;
	
	cout<<"x = pemain \no = komputer\n";
	cout<<"\n - - - - - - - - \n";
	for (int i=0;i<8;i++){
		cout<<"|";
		for (int j=0;j<8;j++){
			if(isi[i][j]=='p'){
				cout<<"o|";
			}else if(isi[i][j]=='h'){
				cout<<"x|";
			}else if(isi[i][j]=='k'){
				if(pointTemp[i][j]!=0){ 	//ketika point temp tidak sama dengan nol maka akan cout angka berurut
					cout<<urut<<"|";
					pilih[urut].baris=i;	//menyimpan baris pilihan ke array
					pilih[urut].kolom=j;	//menyimpan kolom pilihan ke array
					
					urut++;
				}else{
					cout<<" |";
				}
			}
		}cout<<"\n";
	}cout<<" - - - - - - - - \n\n";
}

void userPilih(char var){//user milih mau jalan dimana dia
	int hitung=0,pencet;
	
	for (int i=0;i<8;i++){			//hitung banyaknya jumlah point
		for (int j=0;j<8;j++){
			if (pointTemp[i][j]!=0 && isi[i][j]=='k'){
				hitung++;
			}
		}
	}
	
	A:
	cout<<"\nMasukkan pilihan anda (1 s/d "<<hitung<<") : ";
	cin>>pencet;
	if (hitung!=0){
		int i=1;
		int a,b;
		bool benar=false;
		
		for (i=1;i<=hitung;i++){
			if (pencet==i ){
				a=pilih[i].baris;
				b=pilih[i].kolom;
				benar=true;
				break;
			}
		}
		if (benar==false){
			cout<<"\nHarap pilih angka yang tersedia\n";
			goto A;
		}
	
		cout<<"\nTekan ENTER 2x untuk lanjutkan...";
		cin.get(); cin.ignore();
		system("CLS");
		
		ubahVariabel(var,i);
		for (i=1;i<=hitung;i++){
			pilih[i].baris=0;
			pilih[i].kolom=0;
		}
		hitung=0;
	}
}

void ubahVariabel(char var, int i){
	char varLawan=cekVar(var);
	
	int a=pilih[i].baris;
	int b=pilih[i].kolom;
	
	isi[a][b]=var;
	cekPartisi(var, a, b, "ubah");//mengecek partisi hubungan yang kita pilih dan yang akan di ubah	
}

void komputerPilih(char var){	
	int max=pointTemp[0][0];
	int a,b;
	
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if(pointTemp[i][j]>max && isi[i][j]=='k'){ 	//ketika point temp tidak sama dengan nol maka masukkan ke dalam array pilih
				max=pointTemp[i][j];
				a=i;
				b=j;
				//simpen indeks max untuk dipakai ketika di pilih
			}
		}
	}
	
	cekPartisi(var,a,b,"ubah");
	isi[a][b]=var;
		
	max=0;
}
