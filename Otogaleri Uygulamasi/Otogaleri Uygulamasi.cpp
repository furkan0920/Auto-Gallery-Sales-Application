#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

struct node {
	string plaka;
	string marka;
	string model;
	string renk;
	int fiyat;
	node* next;
	node* prev;
};
node* head = NULL;

void aracEkle(string plaka, string marka, string model, string renk, int fiyat) {
	node* arac = new node;
	arac->plaka = plaka;
	arac->marka = marka;
	arac->model = model;
	arac->renk = renk;
	arac->fiyat = fiyat;

	if (head == NULL) {
		head = arac;
		head->next = head;
		head->prev = head;
		cout << plaka << " plakali arac galeriye eklendi" << endl;
	}
	else {
		node* temp = head;
		while (temp->next != head)
		{
			temp = temp->next;
		}
		arac->next = head;
		head->prev = arac;
		head = arac;
		temp->next = head;
		head->prev = temp;
		cout << plaka << " plakali arac galeriye eklendi" << endl;
	}
}
void aracSat(string plaka) {
	if (head == NULL) {
		cout << "galeriye satilik arac yok" << endl;
	}
	else {
		if (head->next == head && head->plaka == plaka) {		//satılan arac liste kalan son araç ise bu kısım çalışır
			int fiyat = head->fiyat + head->fiyat * 0.10;
			delete head;
			cout << plaka << "plakali sonuc arac" << fiyat << "TL ye satildi" << endl;
			head = NULL;
		}
		else if (head->next != head && head->plaka == plaka) {		//satılan arac listenin en basindaki arac ise bu kısım calışır
			node* temp2 = head;
			while (temp2->next != head)
			{
				temp2 = temp2->next;
			}
			node* temp = head->next;
			int fiyat = head->fiyat + head->fiyat * 0.10;
			cout << plaka << "plakali arac " << fiyat << " TL ye satildi" << endl;
			delete head;
			head = temp;
			head->prev = temp2;
			temp2->next = head;
		}
		else {
			node* temp = head;
			while (temp->next != head)
			{
				if (temp->plaka == plaka) {				//satılan araç listenin içinde bir arac ise bu kısım çalışır
					node* temp2 = temp->prev;
					node* temp3 = temp->next;
					int fiyat = temp->fiyat + temp->fiyat * 0.10;
					cout << plaka << " plakali arac" << fiyat << " TL ye satildi" << endl;
					delete temp;
					temp2->next = head;
					head->prev = temp2;
					break;
				}
				temp = temp->next;
			}
			if (temp->plaka == plaka) {				//satılan arac listenin en sonundaki arac ise bu kısım calişir
				node* temp2 = temp->prev;
				int fiyat = temp->fiyat + temp->fiyat * 0.10;
				cout << plaka << " plakali arac" << fiyat << " TL ye satildi" << endl;
				delete temp;
				temp2->next = head;
				head->prev = temp2;
			}
		}

	}
}
void yazdir() {
	system("cls");
	if (head == NULL) {
		cout << "galeride arac yok" << endl;
	}
	else {
		cout << "galerideki mevcut araclar" << endl;
		node* temp = head;
		while (temp->next != head)
		{
			cout << temp->plaka << " " << temp->marka << " " << temp->model << " " << temp->renk << " " << temp->fiyat << endl;
			temp = temp->next;
		}
		cout << temp->plaka << " " << temp->marka << " " << temp->model << " " << temp->renk << " " << temp->fiyat << endl;
	}
}
void dosyayaYaz() {
	system("cls");
	if (head == NULL) {
		cout << "galeride arac yok" << endl;
	}
	else {
		ofstream yaz("galeri.txt", ios::app);
		node* temp = head;
		while (temp->next != head)
		{
			yaz << temp->plaka << endl;
			yaz << temp->marka << endl;
			yaz << temp->model << endl;
			yaz << temp->renk << endl;
			yaz << temp->fiyat << endl;

			temp = temp->next;
		}
		yaz << temp->plaka << endl;
		yaz << temp->marka << endl;
		yaz << temp->model << endl;
		yaz << temp->renk << endl;
		yaz << temp->fiyat << endl;

		yaz.close();
		cout << "galerideki araclar 'galeri.txt' isimli dosyaya kaydedildi" << endl;
	}
}
void dosyadanOku() {
	system("cls");
	ifstream oku("galeri.txt");
	string satir = " ";
	cout << "dosyada kayitli arac bilgileri: " << endl;
	int adet = 0;
	while (getline(oku, satir))
	{
		if (adet % 5 != 0) {
			cout << satir << " ";
		}
		else {
			cout << endl << satir << " ";
		}
		adet++;
	}
	oku.close();
}
void dosyadanBaglilisteyeAktar() {
	system("cls");
	cout << "'galeri.txt' isimli dosyadaki veriler bagli listeye aktariliyor..." << endl;
	ifstream oku("galeri.txt");
	string plaka = "", marka = "", model = "", renk = "";
	int fiyat = 0;
	string strFiyat;

	string satir;
	cout << "dosyada kayitli arac bilgileri :" << endl;
	char karakter;
	while (getline(oku, satir))
	{
		oku >> plaka;
		oku >> marka;
		oku >> model;
		oku >> renk;
		oku >> strFiyat;

		fiyat = stoi(strFiyat);

		aracEkle(plaka, marka, model, renk, fiyat);
	}
	oku.close();
}
int main() {
	int sayi, fiyat, secim;
	string plaka, marka, model, renk;

	while (1)
	{
		cout << endl;
		cout << "CYDABL ile Otogaleri Uygulamasi" << endl;
		cout << "1--Arac al" << endl;
		cout << "2--Arac sat" << endl;
		cout << "3--Araclari getir" << endl;
		cout << "4--Araclari dosyaya kaydet" << endl;
		cout << "5--Dosyadaki araclari getir" << endl;
		cout << "6--Dosyadaki araclari bagli listeye aktar" << endl;
		cout << "0--CIKIS" << endl;
		cin >> secim;
		switch (secim)
		{
		case 1:cout << "galeri eklenecek arac bilgileri giriniz:" << endl;
			cout << "plaka     :"; cin >> plaka;
			cout << "marka     :"; cin >> marka;
			cout << "model     :"; cin >> model;
			cout << "renk      :"; cin >> renk;
			cout << "fiyat     :"; cin >> fiyat;
			aracEkle(plaka, marka, model, renk, fiyat);
			break;
		case 2:cout << "satisi yapilan arac plakasi: ";	cin >> plaka;
			aracSat(plaka);
			break;
		case 3:yazdir();
			break;
		case 4:dosyayaYaz();
			break;
		case 5:dosyadanOku();
			break;
		case 6:dosyadanBaglilisteyeAktar();
			break;
		case 0:cout << "cikis yaptiniz....." << endl;
			system("pause");
			return 0;
			break;
		default:cout << "Hatali giris yaptiniz..." << endl;
			break;
		}
	}
}