#ifndef __MAHASISWA
#define __MAHASISWA

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <unistd.h>

class Mahasiswa 
{
	private :
		std::string   m_nama  ;
		std::string   m_NIM   ;
		std::string   m_prodi ;
		std::string   m_kelas ;
		std::fstream  fileIO ;
	public  :

		Mahasiswa  (const std::string& nama = "", const std::string& NIM = "", const std::string& prodi = "", const std::string& kelas = "")
		: m_nama   (nama)
		, m_NIM    (NIM)
		, m_prodi  (prodi)
		, m_kelas  (kelas)
		{
			fileIO.open  ("bin/data.bin", std::ios::out | std::ios::app);
			fileIO.close ();
		}

		void getData ()
		{
			std::cout << "Masukan nama Mahasiswa : ";
			getline (std::cin, m_nama);
			std::cout << "Masukan NIM Mahasiswa : ";
			getline (std::cin, m_NIM);
			std::cout << "Masukan prodi Mahasiswa : ";
			getline (std::cin, m_prodi);
			std::cout << "Masukan kelas Mahasiswa : ";
			getline (std::cin, m_kelas);
		}

		void writeData ()
		{
			fileIO.open ("bin/data.bin", std::ios::out | std::ios::binary | std::ios::app);

				if (fileIO)
				{
					char temp[128] = {};
					char length = m_nama.length ();
					memcpy(temp, m_nama.c_str(), length + 1);
					fileIO.write (&length, 1);
					fileIO.write (reinterpret_cast <char*> (&temp), length);

					length = m_NIM.length ();
					memcpy(temp, m_NIM.c_str(), length + 1);
					fileIO.write (&length, 1);
					fileIO.write (reinterpret_cast <char*> (&temp), length);

					length = m_prodi.length ();
					memcpy(temp, m_prodi.c_str(), length + 1);
					fileIO.write (&length, 1);
					fileIO.write (reinterpret_cast <char*> (&temp), length);

					length = m_kelas.length ();
					memcpy(temp, m_kelas.c_str(), length + 1);
					fileIO.write (&length, 1);
					fileIO.write (reinterpret_cast <char*> (&temp), length);
				} else
				{
					std::cerr << "File tidak terbuka" << std::endl;
				}

			fileIO.close ();
		}

		void readData ()
		{
			int index = 1;
			std::cout << "+=====+=================================+=================+=========================+=================+\n";
			std::cout << "| No. | Nama                            | NIM             | Prodi                   | Kelas           |\n";
			std::cout << "+=====+=================================+=================+=========================+=================+\n";

			fileIO.open ("bin/data.bin", std::ios::in | std::ios::binary);

			while (true)
			{
				char length = '\0';
				char temp[128] = {};

				fileIO.read (reinterpret_cast <char*> (&length), 1);
				fileIO.read (reinterpret_cast <char*> (&temp), length);
					if (temp[0] == '\0')
					{
						break;
					}
				std::cout << "| " << std::left << std::setw (4)  << index
						  << "| " << std::left << std::setw (32) << temp  << "| ";
				memset(temp, '\0', 128);
				
				fileIO.read (reinterpret_cast <char*> (&length), 1);
				fileIO.read (reinterpret_cast <char*> (&temp), length);
				std::cout << std::left << std::setw (16) << temp << "| ";
				memset(temp, '\0', 128);

				fileIO.read (reinterpret_cast <char*> (&length), 1);
				fileIO.read (reinterpret_cast <char*> (&temp), length);
				std::cout << std::left << std::setw (24) << temp << "| ";
				memset(temp, '\0', 128);

				fileIO.read (reinterpret_cast <char*> (&length), 1);
				fileIO.read (reinterpret_cast <char*> (&temp), length);
				std::cout << std::left << std::setw (16) << temp << "|\n";
				memset(temp, '\0', 128);

				index++;
			}

			fileIO.close ();

			std::cout << "+=====+=================================+=================+=========================+=================+";
		}

        void updateData (const int dataIndex)
        {
			fileIO.open ("bin/data.bin", std::ios::in | std::ios::binary);

				getData    ();
				deleteData (dataIndex, "update");
				writeData  ();

				std::cout << "\nData berhasil diupdate, tekan enter untuk kembali";
				std::cin.get ();
				system ("cls");

			fileIO.close ();
        }

		void deleteData (const int dataIndex, const std::string& editOption)
		{
			fileIO.open ("bin/data.bin", std::ios::out | std::ios::in | std::ios::binary);
				for (int a = 1; a < dataIndex; a++)
					{
						char temp = '\0';
						fileIO.read  (&temp, 1);
						fileIO.seekg (temp, std::ios::cur);
						fileIO.read  (&temp, 1);
						fileIO.seekg (temp, std::ios::cur);
						fileIO.read  (&temp, 1);
						fileIO.seekg (temp, std::ios::cur);
						fileIO.read  (&temp, 1);
						fileIO.seekg (temp, std::ios::cur);
					}

				int putPosition = fileIO.tellg ();
				
				{
					std::cout << "+=====+=================================+=================+=========================+=================+\n";
					std::cout << "| No. | Nama                            | NIM             | Prodi                   | Kelas           |\n";
					std::cout << "+=====+=================================+=================+=========================+=================+\n";

					char length = '\0';
					char temp[128] = {};

					fileIO.read (reinterpret_cast <char*> (&length), 1);
					fileIO.read (reinterpret_cast <char*> (&temp), length);
					std::cout << "| " << std::left << std::setw (4)  << dataIndex
							  << "| " << std::left << std::setw (32) << temp  << "| ";
					memset(temp, '\0', 128);
					
					fileIO.read (reinterpret_cast <char*> (&length), 1);
					fileIO.read (reinterpret_cast <char*> (&temp), length);
					std::cout << std::left << std::setw (16) << temp << "| ";
					memset(temp, '\0', 128);

					fileIO.read (reinterpret_cast <char*> (&length), 1);
					fileIO.read (reinterpret_cast <char*> (&temp), length);
					std::cout << std::left << std::setw (24) << temp << "| ";
					memset(temp, '\0', 128);

					fileIO.read (reinterpret_cast <char*> (&length), 1);
					fileIO.read (reinterpret_cast <char*> (&temp), length);
					std::cout << std::left << std::setw (16) << temp << "|\n";
					memset(temp, '\0', 128);

					std::cout << "+=====+=================================+=================+=========================+=================+";
				}

				int getPosition = fileIO.tellg ();

				char confirm;
				if (editOption == "update")
				{
					std::cout << "\nApakah anda yakin ingin mengubah data mahasiswa ini (Y/T)? ";
					std::cin  >> confirm;
					std::cin.ignore ();
				}else 
				if (editOption == "delete")
				{
					std::cout << "\nApakah anda yakin ingin menghapus data mahasiswa ini (Y/T)? ";
					std::cin  >> confirm;
					std::cin.ignore ();
				}

				bool isTrue = confirm == 'y' || confirm == 'Y';

				while (isTrue)
				{
					fileIO.seekg (getPosition, std::ios::beg);
					
					char length [4]   = {};
					char temp1  [128] = {};
					char temp2  [32]  = {};
					char temp3  [64]  = {};
					char temp4  [32]  = {};
					fileIO.read  (&length [0], 1);
					if (length [0] == '\0')
					{
						break;
					}
					fileIO.read  (reinterpret_cast <char*> (&temp1), length [0]);
					fileIO.read  (&length [1], 1);
					fileIO.read  (reinterpret_cast <char*> (&temp2), length [1]);
					fileIO.read  (&length [2], 1);
					fileIO.read  (reinterpret_cast <char*> (&temp3), length [2]);
					fileIO.read  (&length [3], 1);
					fileIO.read  (reinterpret_cast <char*> (&temp4), length [3]);

					getPosition = fileIO.tellg ();

					fileIO.seekp (putPosition, std::ios::beg);
					fileIO.write (&length [0], 1);
					fileIO.write (reinterpret_cast <char*> (&temp1), length [0]);
					fileIO.write (&length [1], 1);
					fileIO.write (reinterpret_cast <char*> (&temp2), length [1]);
					fileIO.write (&length [2], 1);
					fileIO.write (reinterpret_cast <char*> (&temp3), length [2]);
					fileIO.write (&length [3], 1);
					fileIO.write (reinterpret_cast <char*> (&temp4), length [3]);

					putPosition = fileIO.tellp ();
				}

			fileIO.close ();

			if (isTrue)
			{
        		truncate ("bin/data.bin", putPosition);	
				
				if (editOption == "delete")
				{
				std::cout << "\nData berhasil dihapus, tekan enter untuk kembali";
				std::cin.get ();
				system ("cls");
				}
			} else 
			{
				if (editOption == "update")
				{
					std::cout << "\nPengubahan data dibatalkan, tekan enter untuk kembali";
					std::cin.get ();
					system ("cls");
				}else 
				if (editOption == "delete")
				{
					std::cout << "\nPenghapusan data dibatalkan, tekan enter untuk kembali";
					std::cin.get ();
					system ("cls");
				}
			}
		}

};

#endif
