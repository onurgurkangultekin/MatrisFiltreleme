// MatrisFiltreleme.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

// matris boyutları, n:satır sayısı, m:sütun sayısı
int n, m = 0;


//kullanicidan matris degerleri alinir
float** matrisOku()
{
	// matris için gerekli boyut bilgisi kullanıcıdan alınır
	bool gecersizGiris = true;
	while (gecersizGiris)
	{
		cout << "Matris satir sayisini giriniz (m): ";
		cin >> m;
		cout << "Matris kolon sayisini giriniz (n): ";
		cin >> n;
		// m veya n 3den küçük ise geçersiz giriş olur.
		gecersizGiris = m < 3 || n < 3;

		//eger boyutlar 3den küçük girildi ise kullanıcıdan tekrar giriş alınır
		if (gecersizGiris)
			cout << "Girislerinizi 3den buyuk olacak sekilde giriniz." << endl;
	}


	// dinamik m x n boyutlu bir matris üretir.
	float** A = new float*[m];
	for (int i = 0; i < m; ++i)
		A[i] = new float[n];

	//matris değerleri tek tek kullanıcıdan alınır
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "A[" << i << "][" << j << "] : ";
			cin >> A[i][j];
		}
	}
	return A;
}

//ekrana girilen matrisi yazdirir
void matrisYazdir(float** A)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(10) << A[i][j] << " ";
		}
		cout << endl << endl;
	}
}

//matrisi kopyalar
float** matrisKopyala(float** A)
{
	// dinamik m x n boyutlu bir matris üretir.
	float** B = new float*[m];
	for (int i = 0; i < m; ++i)
		B[i] = new float[n];

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			B[i][j] = A[i][j];
		}
	}
	return B;
}

// kullanicidan filtre tipi alinir
int filtreTipiOku()
{
	// filtre tipi, 0: aritmetik, 1:medyan
	int filtreTipi;

	bool gecersizGiris = true;
	while (gecersizGiris)
	{
		cout << "Filtre tipini seciniz (0: aritmetik, 1:medyan) : ";
		cin >> filtreTipi;
		gecersizGiris = !(filtreTipi == 1 || filtreTipi == 0);
		if (gecersizGiris)
			cout << "Gecersiz giris yaptiniz, lutfen tekrar deneyiniz." << endl;
	}
	return filtreTipi;
}

// 9 elemanlı dizi elemanları toplanır ve 9 a bölünerek aritmetik ortalama bulunur
float aritmetikOrtalamaAl(float pencere3x3[])
{
	float toplam = 0;
	for (int i = 0; i < 9; i++)
	{
		toplam += pencere3x3[i];
	}
	return toplam / 9;
}

// medyan ortalamaya göre, sıralamada ortada kalan eleman dönülür. 
//örneğin: X= [9,10,11,12,13,14,15,16,17] dizisi için X[4] ile 13 dönülür (indeksleme 0 dan başlar)
float medyanOrtalamaAl(float pencere3x3[])
{
	// sort() fonksiyonu 9 elemanlı dizinin içindeki elemanları sıralar.
	sort(pencere3x3, pencere3x3 + 9);

	return pencere3x3[4];
}


// matris içindeki elemanların üzerinde gezer ve her bir eleman için filtre uygular 
// (ilk satır, son satır, ilk kolon ve son kolon üzerinden geçilmez) (indis 1'den başlar, m-1 ve n-1'de biter)
float** filtreUygula(float** B, int filtreTipi)
{
	for (int i = 1; i < m - 1; i++)
	{
		for (int j = 1; j < n - 1; j++)
		{
			float pencere3x3[] = { B[i - 1][j - 1], B[i - 1][j] , B[i - 1][j + 1],
				B[i][j - 1], B[i][j], B[i][j + 1],
				B[i + 1][j - 1], B[i + 1][j], B[i + 1][j + 1] };

			if (filtreTipi == 0) // aritmatik filtre
			{
				B[i][j] = aritmetikOrtalamaAl(pencere3x3);
			}
			else // medyan filtre
			{
				B[i][j] = medyanOrtalamaAl(pencere3x3);
			}
		};
	}
	return B;
}

int main()
{
	cout << fixed;
	cout << setprecision(2);

	float** A = matrisOku();
	cout << "Girlen matris : " << endl;
	matrisYazdir(A);
	float** B = matrisKopyala(A);
	int filtreTipi = filtreTipiOku();
	B = filtreUygula(B, filtreTipi);
	cout << "Filtrelenmis matris : " << endl;
	matrisYazdir(B);
	system("pause");
	return 0;
}

