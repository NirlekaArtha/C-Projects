#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>

#include "Mahasiswa.hpp"

void errorCatcher ();

Mahasiswa tempMahasiswa;
int pilihan;

int main ()
{
	while (true)
	{
		std::cout << "+===============================================+\n";
		std::cout << "| Selamat datang di program CRUD data Mahasiswa |\n";
		std::cout << "|          Dibuat Oleh : M. Hafizh R. H         |\n";
		std::cout << "|                                               |\n";
		std::cout << "|  Apa yang ingin anda lakukan?                 |\n";
		std::cout << "|  (1) Menambahkan Data Mahasiswa               |\n";
		std::cout << "|  (2) Menampilkan Data Mahasiswa               |\n";
		std::cout << "|  (3) Mengubah Data Mahasiswa                  |\n";
		std::cout << "|  (4) Menghapus Data Mahasiswa                 |\n";
		std::cout << "|  (5) Keluar dari program                      |\n";
		std::cout << "+===============================================+\n\n";
		std::cout << "Pilihan Anda ==> ";
		std::cin  >> pilihan;
		std::cin.ignore ();

		errorCatcher ();


		switch (pilihan)
		{
			case 1 :
			{
				system ("cls");
				std::cout << "Menambahkan data mahasiswa\n\n";
				tempMahasiswa.getData   ();
				tempMahasiswa.writeData ();
				std::cout << "\n\nData berhasil ditambahkan, tekan enter untuk kembali";
				std::cin.get ();
				system ("cls");
					continue;
			}
			case 2 :
			{
				system ("cls");
				tempMahasiswa.readData  ();
				std::cout << "\n\nTekan enter untuk melanjutkan";
				std::cin.get ();
				system ("cls");
					continue;
			}
			case 3 :
			{
				system ("cls");
				tempMahasiswa.readData ();
				int index = 0;

				_update :
				std::cout << "\nMasukan nomor urut mahasiswa yang ingin anda ubah ==> ";
				std::cin  >> index;
				std::cin.ignore ();

				errorCatcher ();

				if (index < 1)
				{
					std::cout << "input invalid";
					goto _update;
				}

				tempMahasiswa.updateData (index);
					continue;
			}
			case 4 :
			{
				system ("cls");
				tempMahasiswa.readData  ();
				int index = 0;

				_delete :
				std::cout << "\nMasukan nomor urut mahasiswa yang ingin anda hapus ==> ";
				std::cin  >> index;
				std::cin.ignore ();

				errorCatcher ();

				if (index < 1)
				{
					std::cout << "input invalid";
					goto _delete;
				}

				system ("cls");

				tempMahasiswa.deleteData (index, "delete");
					continue;
			}
			case 5 :
			{
				std::cout << "\n\nSelamat tinggal";
					return 0;
			}
			default :
			{
				system ("cls");
				std::cout << "Perintah tidak dikenali!!\n\n";
					continue;
			}
		}
	}

	
	return 0;
}

void errorCatcher ()
{
	if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(); 
        }

}