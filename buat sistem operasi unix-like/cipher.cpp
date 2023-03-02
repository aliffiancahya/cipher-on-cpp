#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

struct Cipher
{
    int kosongTEKSkeBINER = 1;
    char TEKSkeBINER_teks[1000];
    char TEKSkeBINER_hasil[8000];
    int kosongBINERkeTEKS = 2;
    char BINERkeTEKS_hasil[8000];
    char BINERkeTEKS_teks[1000];
    int kosongTEKSkeDESIMAL = 3;
    char TEKSkeDESIMAL_teks[1000];
    char TEKSkeDESIMAL_hasil[8000];
    int kosongDESIMALkeTEKS = 4;
    char DESIMALkeTEKS_teks[1000];
    char DESIMALkeTEKS_hasil[8000];
    // char teksHeksa[1000]
    // char hasilHeksa[]
    // char teksOktal[1000]
    // char hasilOktal[]
};

char getPilihan();
Cipher bacaDong(fstream &data, int pos);
int ambilUkuran_data(fstream &data);
void cekData_TEKSkeBINER(fstream &data);
void cekData_BINERkeTEKS(fstream &data2);
void cekData_TEKSkeDESIMAL(fstream &data3);
void cekData_DESIMALkeTEKS(fstream &data4);
void tulisTEKSkeBINER(fstream &data, int pos, Cipher &inputTEKSkeBINER);
void tulisBINERkeTEKS(fstream &data2, int pos, Cipher &inputBINERkeTEKS);
void tulisTEKSkeDESIMAL(fstream &data3, int pos, Cipher &inputTEKSkeDESIMAL);
void tulisDESIMALkeTEKS(fstream &data4, int pos, Cipher &inputDESIMALkeTEKS);
void menuEncipher();
void menuDecipher();
void pilihMenu_encipher(fstream &data, fstream &data3);
void pilihMenu_decipher(fstream &data2, fstream &data4);
void pilihMenu_riwayat(fstream &data, fstream &data2, fstream &data3, fstream &data4);
void pilihMenu_update(fstream &data, fstream &data2, fstream &data3, fstream &data4);
void pilihMenu_delete(fstream &data, fstream &data2, fstream &data3, fstream &data4);
void menuRUD(fstream &data, fstream &data2, fstream &data3, fstream &data4); // RUD = READ, UPDATE, DELETE
void TEKSkeBINER(fstream &data);
void tampilkanTEKSkeBINER(fstream &data);
void ubahTEKSkeBINER(fstream &data);
void apusTEKSkeBINER(fstream &data);
void BINERkeTEKS(fstream &data2);
void tampilkanBINERkeTEKS(fstream &data2);
void ubahBINERkeTEKS(fstream &data2);
void apusBINERkeTEKS(fstream &data2);
void TEKSkeDESIMAL(fstream &data3);
void tampilkanTEKSkeDESIMAL(fstream &data3);
void ubahTEKSkeDESIMAL(fstream &data3);
void apusTEKSkeDESIMAL(fstream &data3);
void DESIMALkeTEKS(fstream &data4);
void tampilkanDESIMALkeTEKS(fstream &data4);
void ubahDESIMALkeTEKS(fstream &data4);
void apusDESIMALkeTEKS(fstream &data4);
void autoEnter();
void bannerSelamatDatang();
void bannerInfo();
void bannerCipher();
void bannerEncipher();
void bannerDecipher();
void bannerRiwayat();
void bannerUpdate();
void bannerDelete();
void bannerExit();
void fungsiExit();

void prosesAnimasi(ostream &os, int time, string pesan, string simbol = "#")
{
    double panjangLoading = 70;
    double prosesLoading = 150 / (panjangLoading - pesan.length());

    for (int persen = 0; persen < 101; persen += prosesLoading)
    {
        pesan += simbol;
        os << "\r[" << setw(1) << persen << "%] " << pesan;
        this_thread::sleep_for(chrono::milliseconds(time));
    }
}

char getPilihan()
{
    char pilih;

    // Cipher, undiceper
    cout << setw(46) << "Pilih menu" << endl;
    cout << setw(47) << "[1] Encipher" << endl;
    cout << setw(47) << "[2] Decipher" << endl;
    cout << setw(46) << "[3] Riwayat" << endl;
    cout << setw(43) << "[0] Exit" << endl;
    cout << setw(43) << "Pilih? ";
    autoEnter();
    pilih = getchar();
    endwin();
    // cin.ignore();
    return pilih;
}

int main()
{
    system("clear");
    fstream data, data2, data3, data4;
    char pilih;

    bannerSelamatDatang();
    bannerInfo();
    cekData_TEKSkeBINER(data);
    cekData_BINERkeTEKS(data2);
    cekData_TEKSkeDESIMAL(data3);
    cekData_DESIMALkeTEKS(data4);

    while (pilih != '0')
    {
        system("clear");
        bannerCipher();
        pilih = getPilihan();
        if (pilih == '1')
        {
            system("clear");
            bannerEncipher();
            pilihMenu_encipher(data, data3);
        }
        else if (pilih == '2')
        {
            system("clear");
            bannerDecipher();
            pilihMenu_decipher(data2, data4);
        }
        else if (pilih == '3')
        {
            system("clear");
            bannerRiwayat();
            menuRUD(data, data2, data3, data4);
        }
        else if (pilih == '0')
        {
            cout << endl;
            cout << setw(45) << "See you ^^" << endl;
        }
        else
        {
            cout << "\n\n";
            cout << "Input Salah" << endl;
            cout << "Tekan enter untuk melanjutkan... ";
            getchar();
        }
    }

    return 0;
}

Cipher bacaDong(fstream &data, int pos)
{
    Cipher bacaCipher;
    data.seekg((pos - 1) * sizeof(Cipher), ios::beg);
    data.read(reinterpret_cast<char *>(&bacaCipher), sizeof(Cipher));
    return bacaCipher;
}

int ambilUkuran_data(fstream &data)
{
    int awal, akhir;
    data.seekg(0, ios::beg);
    awal = data.tellg();
    data.seekg(0, ios::end);
    akhir = data.tellg();
    return (akhir - awal) / sizeof(Cipher);
}

void cekData_TEKSkeBINER(fstream &data)
{
    data.open("data_TEKSkeBINER.bin", ios::out | ios::in | ios::binary);
    if (data.is_open())
    {
        cout << "                        DATABASE Ditemukan" << endl;
        cout << "                        Tekan enter untuk memuat... ";
        getchar();
        cout << endl;
        prosesAnimasi(clog, 30, "Memuat DATABASE [");
        cout << "]" << endl;
        cout << "Berhasil ^^";
        cout << endl;
    }
    else
    {
        cout << "                        DATABASE Tidak Ditemukan" << endl;
        cout << "                        Tekan enter untuk membuat... ";
        getchar();
        cout << endl;
        prosesAnimasi(clog, 30, "Membuat DATABASE [");
        cout << "]" << endl;
        cout << "Berhasil ^^";
        cout << endl;
        data.close();
        data.open("data_TEKSkeBINER.bin", ios::trunc | ios::out | ios::in | ios::binary);
    }
    cout << endl;
    cout << "Tekan enter untuk melanjutkan... ";
    getchar();
}

void cekData_BINERkeTEKS(fstream &data2)
{
    data2.open("data_BINERkeTEKS.bin", ios::out | ios::in | ios::binary);
    if (data2.is_open())
    {
    }
    else
    {
        data2.close();
        data2.open("data_BINERkeTEKS.bin", ios::trunc | ios::out | ios::in | ios::binary);
    }
}

void cekData_TEKSkeDESIMAL(fstream &data3)
{
    data3.open("data_TEKSkeDESIMAL.bin", ios::out | ios::in | ios::binary);
    if (data3.is_open())
    {
    }
    else
    {
        data3.close();
        data3.open("data_TEKSkeDESIMAL.bin", ios::trunc | ios::out | ios::in | ios::binary);
    }
}

void cekData_DESIMALkeTEKS(fstream &data4)
{
    data4.open("data_DESIMALkeTEKS.bin", ios::out | ios::in | ios::binary);
    if (data4.is_open())
    {
    }
    else
    {
        data4.close();
        data4.open("data_DESIMALkeTEKS.bin", ios::trunc | ios::out | ios::in | ios::binary);
    }
}

void tulisTEKSkeBINER(fstream &data, int pos, Cipher &inputTEKSkeBINER)
{
    data.seekp((pos - 1) * sizeof(Cipher), ios::beg);
    data.write(reinterpret_cast<char *>(&inputTEKSkeBINER), sizeof(Cipher));
}

void tulisBINERkeTEKS(fstream &data2, int pos, Cipher &inputBINERkeTEKS)
{
    data2.seekp((pos - 1) * sizeof(Cipher), ios::beg);
    data2.write(reinterpret_cast<char *>(&inputBINERkeTEKS), sizeof(Cipher));
}

void tulisTEKSkeDESIMAL(fstream &data3, int pos, Cipher &inputTEKSkeDESIMAL)
{
    data3.seekp((pos - 1) * sizeof(Cipher), ios::beg);
    data3.write(reinterpret_cast<char *>(&inputTEKSkeDESIMAL), sizeof(Cipher));
}

void tulisDESIMALkeTEKS(fstream &data4, int pos, Cipher &inputDESIMALkeTEKS)
{
    data4.seekp((pos - 1) * sizeof(Cipher), ios::beg);
    data4.write(reinterpret_cast<char *>(&inputDESIMALkeTEKS), sizeof(Cipher));
}

void menuEncipher()
{
    cout << setw(45) << "Pilih menu" << endl;
    cout << setw(48) << "[1] Teks ke Biner" << endl;
    cout << setw(50) << "[2] Teks ke Desimal" << endl;
    cout << setw(55) << "[3] Teks ke Heksadesimal" << endl;
    cout << setw(48) << "[4] Teks ke Oktal" << endl;
    cout << setw(42) << "[0] Kembali" << endl;
    cout << setw(42) << "Pilih? ";
}

void menuDecipher()
{
    cout << setw(45) << "Pilih menu" << endl;
    cout << setw(48) << "[1] Biner ke teks" << endl;
    cout << setw(50) << "[2] Desimal ke teks" << endl;
    cout << setw(55) << "[3] Heksadesimal ke teks" << endl;
    cout << setw(48) << "[4] Oktal ke teks" << endl;
    cout << setw(42) << "[0] Kembali" << endl;
    cout << setw(42) << "Pilih? ";
}

void pilihMenu_encipher(fstream &data, fstream &data3)
{
    char pilihDecipher;

    menuEncipher();
    autoEnter();
    pilihDecipher = getchar();
    endwin();
    cout << "\n\n\n";
    if (pilihDecipher == '1')
    {
        TEKSkeBINER(data);
        fungsiExit();
    }
    else if (pilihDecipher == '2')
    {
        TEKSkeDESIMAL(data3);
        fungsiExit();
        // cout << "COMING SOON !" << endl;
        //  cout << endl;
    }
    else if (pilihDecipher == '3')
    {
        // TEKSkeHEKSA();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    else if (pilihDecipher == '4')
    {
        // TEKSkeOKTAL();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    else if (pilihDecipher == '0')
    {
        // kembali
    }
    else
    {
        fungsiExit();
    }
}

void pilihMenu_decipher(fstream &data2, fstream &data4)
{
    char pilihUndecipher;

    menuDecipher();
    autoEnter();
    pilihUndecipher = getchar();
    endwin();
    cout << "\n\n";
    if (pilihUndecipher == '1')
    {
        BINERkeTEKS(data2);
        fungsiExit();
    }
    else if (pilihUndecipher == '2')
    {
        DESIMALkeTEKS(data4);
        fungsiExit();
    }
    else if (pilihUndecipher == '3')
    {
        // TEKSkeHEKSA();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    else if (pilihUndecipher == '4')
    {
        // TEKSkeOKTAL();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    else if (pilihUndecipher == '0')
    {
        // kembali
    }
    else
    {
        cout << endl;
        fungsiExit();
    }
}

void pilihMenu_riwayat(fstream &data, fstream &data2, fstream &data3, fstream &data4)
{
    char pilihRiwayat, pilihRiwayat2;
    int size, size2, size3, size4;

    size = ambilUkuran_data(data);
    size2 = ambilUkuran_data(data2);
    size3 = ambilUkuran_data(data3);
    size4 = ambilUkuran_data(data4);

    cout << setw(46) << "Pilih menu" << endl;
    cout << setw(47) << "[1] Encipher" << endl;
    cout << setw(47) << "[2] Decipher" << endl;
    cout << setw(47) << "[0] Kembali " << endl;
    cout << setw(43) << "Pilih? ";
    autoEnter();
    pilihRiwayat = getchar();
    endwin();
    if (pilihRiwayat == '1')
    {
        system("clear");
        bannerRiwayat();
        menuEncipher();
        autoEnter();
        pilihRiwayat2 = getchar();
        endwin();
        cout << "\n\n\n";
        if (pilihRiwayat2 == '1')
        {
            if (size < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanTEKSkeBINER(data);
                fungsiExit();
            }
        }
        else if (pilihRiwayat2 == '2')
        {
            if (size3 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanTEKSkeDESIMAL(data3);
                fungsiExit();
            }
        }
        else if (pilihRiwayat2 == '3')
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihRiwayat2 == '4')
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihRiwayat2 == '0')
        {
            system("clear");
            bannerRiwayat();
            pilihMenu_riwayat(data, data2, data3, data4);
        }
        else
        {
            fungsiExit();
        }
    }
    else if (pilihRiwayat == '2')
    {
        system("clear");
        bannerRiwayat();
        menuDecipher();
        autoEnter();
        pilihRiwayat2 = getchar();
        endwin();
        cout << "\n\n\n";
        if (pilihRiwayat2 == '1')
        {
            if (size2 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanBINERkeTEKS(data2);
                fungsiExit();
            }
        }
        else if (pilihRiwayat2 == '2')
        {
            if (size4 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanDESIMALkeTEKS(data4);
                fungsiExit();
            }
        }
        else if (pilihRiwayat2 == '3')
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihRiwayat2 == '4')
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihRiwayat2 == '0')
        {
            system("clear");
            bannerRiwayat();
            pilihMenu_riwayat(data, data2, data3, data4);
        }
        else
        {
            fungsiExit();
        }
    }
    else if (pilihRiwayat == '0')
    {
        system("clear");
        bannerRiwayat();
        menuRUD(data, data2, data3, data4);
    }
    else
    {
        fungsiExit();
    }
}

void pilihMenu_update(fstream &data, fstream &data2, fstream &data3, fstream &data4)
{
    char pilihUpdate, pilihUpdate2;
    int size, size2, size3, size4;

    size = ambilUkuran_data(data);
    size2 = ambilUkuran_data(data2);
    size3 = ambilUkuran_data(data3);
    size4 = ambilUkuran_data(data4);

    cout << setw(46) << "Pilih menu" << endl;
    cout << setw(47) << "[1] Encipher" << endl;
    cout << setw(47) << "[2] Decipher" << endl;
    cout << setw(47) << "[0] Kembali " << endl;
    cout << setw(43) << "Pilih? ";
    autoEnter();
    pilihUpdate = getchar();
    endwin();
    if (pilihUpdate == '1')
    {
        system("clear");
        bannerUpdate();
        menuEncipher();
        autoEnter();
        pilihUpdate2 = getchar();
        endwin();
        cout << "\n\n\n";
        if (pilihUpdate2 == '1')
        {
            if (size < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanTEKSkeBINER(data);
                ubahTEKSkeBINER(data);
                fungsiExit();
            }
        }
        else if (pilihUpdate2 == '2')
        {
            if (size3 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanTEKSkeDESIMAL(data3);
                ubahTEKSkeDESIMAL(data3);
                fungsiExit();
            }
        }
        else if (pilihUpdate2 == '3')
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihUpdate2 == '4')
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihUpdate2 == '0')
        {
            system("clear");
            bannerUpdate();
            pilihMenu_update(data, data2, data3, data4);
        }
        else
        {
            fungsiExit();
        }
    }
    else if (pilihUpdate == '2')
    {
        system("clear");
        bannerUpdate();
        menuDecipher();
        autoEnter();
        pilihUpdate2 = getchar();
        endwin();
        cout << "\n\n\n";
        if (pilihUpdate2 == '1')
        {
            if (size2 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanBINERkeTEKS(data2);
                ubahBINERkeTEKS(data2);
                fungsiExit();
            }
        }
        else if (pilihUpdate2 == '2')
        {
            if (size4 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanDESIMALkeTEKS(data4);
                ubahDESIMALkeTEKS(data4);
                fungsiExit();
            }
        }
        else if (pilihUpdate2 == '3')
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihUpdate2 == '4')
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihUpdate2 == '0')
        {
            system("clear");
            bannerUpdate();
            pilihMenu_update(data, data2, data3, data4);
        }
        else
        {
            fungsiExit();
        }
    }
    else if (pilihUpdate == '0')
    {
        system("clear");
        bannerRiwayat();
        menuRUD(data, data2, data3, data4);
    }
    else
    {
        fungsiExit();
    }
}

void pilihMenu_delete(fstream &data, fstream &data2, fstream &data3, fstream &data4)
{
    char pilihDelete, pilihDelete2;
    int size, size2, size3, size4;

    size = ambilUkuran_data(data);
    size2 = ambilUkuran_data(data2);
    size3 = ambilUkuran_data(data3);
    size4 = ambilUkuran_data(data4);

    cout << setw(46) << "Pilih menu" << endl;
    cout << setw(47) << "[1] Encipher" << endl;
    cout << setw(47) << "[2] Decipher" << endl;
    cout << setw(47) << "[0] Kembali " << endl;
    cout << setw(43) << "Pilih? ";
    autoEnter();
    pilihDelete = getchar();
    endwin();
    if (pilihDelete == '1')
    {
        system("clear");
        bannerDelete();
        menuEncipher();
        autoEnter();
        pilihDelete2 = getchar();
        endwin();
        cout << "\n\n\n";
        if (pilihDelete2 == '1')
        {
            if (size < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanTEKSkeBINER(data);
                apusTEKSkeBINER(data);
                fungsiExit();
            }
        }
        else if (pilihDelete2 == '2')
        {
            if (size3 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanTEKSkeDESIMAL(data3);
                apusTEKSkeDESIMAL(data3);
                fungsiExit();
            }
        }
        else if (pilihDelete2 == '3')
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihDelete2 == '4')
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihDelete2 == '0')
        {
            system("clear");
            bannerDelete();
            pilihMenu_delete(data, data2, data3, data4);
        }
        else
        {
            fungsiExit();
        }
    }
    else if (pilihDelete == '2')
    {
        system("clear");
        bannerDelete();
        menuDecipher();
        autoEnter();
        pilihDelete2 = getchar();
        endwin();
        cout << "\n\n\n";
        if (pilihDelete2 == '1')
        {
            if (size2 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanBINERkeTEKS(data2);
                apusBINERkeTEKS(data2);
                fungsiExit();
            }
        }
        else if (pilihDelete2 == '2')
        {
            if (size4 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
                fungsiExit();
            }
            else
            {
                tampilkanDESIMALkeTEKS(data4);
                apusDESIMALkeTEKS(data4);
                fungsiExit();
            }
        }
        else if (pilihDelete2 == '3')
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihDelete2 == '4')
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihDelete2 == '0')
        {
            system("clear");
            bannerDelete();
            pilihMenu_delete(data, data2, data3, data4);
        }
        else
        {
            fungsiExit();
        }
    }
    else if (pilihDelete == '0')
    {
        system("clear");
        bannerRiwayat();
        menuRUD(data, data2, data3, data4);
    }
    else
    {
        fungsiExit();
    }
}

void menuRUD(fstream &data, fstream &data2, fstream &data3, fstream &data4)
{
    char pilihRUD;

    cout << setw(46) << "Pilih menu" << endl;
    cout << setw(48) << "[1] Tampilkan" << endl;
    cout << setw(43) << "[2] Ubah" << endl;
    cout << setw(44) << "[3] Hapus" << endl;
    cout << setw(48) << "[0] Kembali  " << endl;
    cout << setw(43) << "Pilih? ";
    autoEnter();
    pilihRUD = getchar();
    endwin();
    if (pilihRUD == '1')
    {
        system("clear");
        bannerRiwayat();
        pilihMenu_riwayat(data, data2, data3, data4);
    }
    else if (pilihRUD == '2')
    {
        system("clear");
        bannerUpdate();
        pilihMenu_update(data, data2, data3, data4);
    }
    else if (pilihRUD == '3')
    {
        system("clear");
        bannerDelete();
        pilihMenu_delete(data, data2, data3, data4);
    }
    else if (pilihRUD == '0')
    {
        // kembali
    }
    else
    {
        cout << "\n\n";
        fungsiExit();
    }
}

void TEKSkeBINER(fstream &data)
{
    Cipher inputTEKSkeBINER;
    string tampunganHasil; // digunakan untuk menampung value bitset
    int size;

    size = ambilUkuran_data(data);

    cout << "Masukkan Teks  : ";
    cin.getline(inputTEKSkeBINER.TEKSkeBINER_teks, 1000);
    for (int i = 0; i < strlen(inputTEKSkeBINER.TEKSkeBINER_teks); i++)
    {
        bitset<8> hasilTEKSkeBINER(inputTEKSkeBINER.TEKSkeBINER_teks[i]);
        tampunganHasil += hasilTEKSkeBINER.to_string();
    }
    tampunganHasil.copy(inputTEKSkeBINER.TEKSkeBINER_hasil, tampunganHasil.length());
    inputTEKSkeBINER.TEKSkeBINER_hasil[tampunganHasil.length()] = '\0';
    cout << "Hasil Encipher : " << inputTEKSkeBINER.TEKSkeBINER_hasil;
    tulisTEKSkeBINER(data, size + 1, inputTEKSkeBINER);
    cout << endl;
    cout << endl;
}

void tampilkanTEKSkeBINER(fstream &data)
{
    Cipher tampilTEKSkeBINER;
    int size;

    size = ambilUkuran_data(data);

    for (int i = 1; i <= size; i++)
    {
        tampilTEKSkeBINER = bacaDong(data, i);
        cout << i << endl;
        cout << "Teks\t\t\t\t : ";
        cout << tampilTEKSkeBINER.TEKSkeBINER_teks << endl;
        cout << "Bentuk Biner 8-Bit (Tanpa Spasi) : ";
        cout << tampilTEKSkeBINER.TEKSkeBINER_hasil << endl;
        cout << endl;
    }
}

void ubahTEKSkeBINER(fstream &data)
{
    Cipher updateTEKSkeBINER;
    string tampunganHasil;
    int pilihNomor;

    cout << "Silahkan pilih data yang akan diubah" << endl;
    cout << "No : ";
    cin >> pilihNomor;
    cin.ignore();

    updateTEKSkeBINER = bacaDong(data, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Teks                             : " << updateTEKSkeBINER.TEKSkeBINER_teks << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi) : " << updateTEKSkeBINER.TEKSkeBINER_hasil << endl;

    cout << endl;

    cout << "Ubah data" << endl;
    cout << "Teks menjadi                     : ";
    cin.getline(updateTEKSkeBINER.TEKSkeBINER_teks, 1000);
    for (int i = 0; i < strlen(updateTEKSkeBINER.TEKSkeBINER_teks); i++)
    {
        bitset<8> hasilTEKSkeBINER(updateTEKSkeBINER.TEKSkeBINER_teks[i]);
        tampunganHasil += hasilTEKSkeBINER.to_string();
    }
    tampunganHasil.copy(updateTEKSkeBINER.TEKSkeBINER_hasil, tampunganHasil.length());
    updateTEKSkeBINER.TEKSkeBINER_hasil[tampunganHasil.length()] = '\0';

    tulisTEKSkeBINER(data, pilihNomor, updateTEKSkeBINER);

    cout << endl;
    cout << "Data berhasil diubah menjadi" << endl;
    cout << "Teks                             : " << updateTEKSkeBINER.TEKSkeBINER_teks << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi) : " << updateTEKSkeBINER.TEKSkeBINER_hasil << endl;
    cout << endl;
}

void apusTEKSkeBINER(fstream &data)
{
    fstream dataSementara;
    Cipher kosong, sementara;
    int pilihNomor, keluaran, size;

    size = ambilUkuran_data(data);

    cout << "Silahkan pilih data yang akan di hapus" << endl;
    cout << "No : ";
    cin >> pilihNomor;
    cin.ignore();

    kosong = bacaDong(data, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Teks                             : " << kosong.TEKSkeBINER_teks << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi) : " << kosong.TEKSkeBINER_hasil << endl;

    kosong.kosongTEKSkeBINER = 0;
    tulisTEKSkeBINER(data, pilihNomor, kosong);

    dataSementara.open("temp.bin", ios::trunc | ios::in | ios::out | ios::binary);
    keluaran = 0;
    for (int i = 1; i <= size; i++)
    {
        sementara = bacaDong(data, i);
        if (sementara.kosongTEKSkeBINER > 0)
        {
            tulisTEKSkeBINER(dataSementara, (i - keluaran), sementara);
        }
        else
        {
            keluaran++;
            cout << "Berhasil dihapus" << endl;
            cout << endl;
        }
    }

    size = ambilUkuran_data(dataSementara);
    data.close();
    data.open("data_TEKSkeBINER.bin", ios::trunc | ios::out | ios::in | ios::binary);
    data.close();
    data.open("data_TEKSkeBINER.bin", ios::out | ios::in | ios::binary);

    for (int i = 1; i <= size; i++)
    {
        sementara = bacaDong(dataSementara, i);
        tulisTEKSkeBINER(data, i, sementara);
    }
}

void BINERkeTEKS(fstream &data2)
{
    Cipher inputBINERkeTEKS;
    string tampunganHasil;
    int size;

    size = ambilUkuran_data(data2);

    cout << endl;
    cout << "Masukkan kode biner 8-Bit (tanpa spasi) : ";
    cin.getline(inputBINERkeTEKS.BINERkeTEKS_teks, 1000);

    for (int i = 0; i < strlen(inputBINERkeTEKS.BINERkeTEKS_teks); i += 8)
    {
        string kodeBiner(inputBINERkeTEKS.BINERkeTEKS_teks);
        bitset<8> hasil(kodeBiner.substr(i, 8));
        tampunganHasil += char(hasil.to_ulong());
    }
    tampunganHasil.copy(inputBINERkeTEKS.BINERkeTEKS_hasil, tampunganHasil.length());
    inputBINERkeTEKS.TEKSkeBINER_hasil[tampunganHasil.length()] = '\0';

    cout << "Hasil Decipher                          : " << inputBINERkeTEKS.BINERkeTEKS_hasil << endl;

    tulisBINERkeTEKS(data2, size + 1, inputBINERkeTEKS);
    cout << endl;
}

void tampilkanBINERkeTEKS(fstream &data2)
{
    Cipher tampil;
    int size;

    size = ambilUkuran_data(data2);

    for (int i = 1; i <= size; i++)
    {
        tampil = bacaDong(data2, i);
        cout << i << endl;
        cout << "Bentuk Biner 8-Bit (Tanpa Spasi) : ";
        cout << tampil.BINERkeTEKS_teks << endl;
        cout << "Teks                             : ";
        cout << tampil.BINERkeTEKS_hasil << endl;
        cout << endl;
    }
}

void ubahBINERkeTEKS(fstream &data2)
{
    Cipher update;
    int pilihNomor;

    cout << "Silahkan pilih data yang akan diubah" << endl;
    cout << "No : ";
    cin >> pilihNomor;
    cin.ignore();

    update = bacaDong(data2, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi) : " << update.BINERkeTEKS_teks << endl;
    cout << "Teks                             : " << update.BINERkeTEKS_hasil << endl;

    cout << endl;

    cout << "Ubah data" << endl;
    cout << "Biner menjadi                    : ";
    cin.getline(update.BINERkeTEKS_teks, 1000);
    string hasilBINERkeTeks;
    for (int i = 0; i < strlen(update.BINERkeTEKS_teks); i += 8)
    {
        string kodeBiner(update.BINERkeTEKS_teks);
        bitset<8> hasil(kodeBiner.substr(i, 8));
        hasilBINERkeTeks += char(hasil.to_ulong());
    }
    hasilBINERkeTeks.copy(update.BINERkeTEKS_hasil, hasilBINERkeTeks.length());
    update.TEKSkeBINER_hasil[hasilBINERkeTeks.length()] = '\0';

    tulisBINERkeTEKS(data2, pilihNomor, update);

    cout << endl;
    cout << "Data berhasil diubah menjadi" << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi) : " << update.BINERkeTEKS_teks << endl;
    cout << "Teks                             : " << update.BINERkeTEKS_hasil << endl;
    cout << endl;
}

void apusBINERkeTEKS(fstream &data2)
{
    fstream dataSementara;
    Cipher kosong, sementara;
    int pilihNomor, keluaran, size;

    size = ambilUkuran_data(data2);

    cout << "Silahkan pilih data yang akan diapus" << endl;
    cout << "No : ";
    cin >> pilihNomor;
    cin.ignore();

    kosong = bacaDong(data2, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi) : " << kosong.BINERkeTEKS_hasil << endl;
    cout << "Teks                             : " << kosong.BINERkeTEKS_teks << endl;

    kosong.kosongBINERkeTEKS = 0;
    tulisBINERkeTEKS(data2, pilihNomor, kosong);

    dataSementara.open("temp.bin", ios::trunc | ios::in | ios::out | ios::binary);
    keluaran = 0;
    for (int i = 1; i <= size; i++)
    {
        sementara = bacaDong(data2, i);
        if (sementara.kosongBINERkeTEKS > 0)
        {
            tulisBINERkeTEKS(dataSementara, (i - keluaran), sementara);
        }
        else
        {
            keluaran++;
            cout << "Berhasil dihapus" << endl;
            cout << endl;
        }
    }

    size = ambilUkuran_data(dataSementara);
    data2.close();
    data2.open("data_BINERkeTEKS.bin", ios::trunc | ios::out | ios::in | ios::binary);
    data2.close();
    data2.open("data_BINERkeTEKS.bin", ios::out | ios::in | ios::binary);

    for (int i = 1; i <= size; i++)
    {
        sementara = bacaDong(dataSementara, i);
        tulisBINERkeTEKS(data2, i, sementara);
    }
}

void TEKSkeDESIMAL(fstream &data3)
{
    Cipher inputTEKSkeDESIMAL;
    string tampunganHasil;
    int size;

    size = ambilUkuran_data(data3);

    cout << "Masukkan Teks  : ";
    cin.getline(inputTEKSkeDESIMAL.TEKSkeDESIMAL_teks, 1000);
    cout << "Hasil Encipher : ";
    for (int i = 0; i < strlen(inputTEKSkeDESIMAL.TEKSkeDESIMAL_teks); i++)
    {
        cout << int(inputTEKSkeDESIMAL.TEKSkeDESIMAL_teks[i]) << " ";
        tampunganHasil += to_string(int(inputTEKSkeDESIMAL.TEKSkeDESIMAL_teks[i])) + " ";
    }
    tampunganHasil.copy(inputTEKSkeDESIMAL.TEKSkeDESIMAL_hasil, tampunganHasil.length());
    inputTEKSkeDESIMAL.TEKSkeDESIMAL_hasil[tampunganHasil.length()] = '\0';
    cout << endl;

    tulisTEKSkeDESIMAL(data3, size + 1, inputTEKSkeDESIMAL);

    cout << endl;
}

void tampilkanTEKSkeDESIMAL(fstream &data3)
{
    Cipher tampil;
    int size;

    size = ambilUkuran_data(data3);

    for (int i = 1; i <= size; i++)
    {
        tampil = bacaDong(data3, i);
        cout << i << endl;
        cout << "Teks                   : ";
        cout << tampil.TEKSkeDESIMAL_teks << endl;
        cout << "Bentuk Desimal (ASCII) : ";
        cout << tampil.TEKSkeDESIMAL_hasil << endl;
        cout << endl;
    }
}

void ubahTEKSkeDESIMAL(fstream &data3)
{
    Cipher update;
    int pilihNomor;
    string tampunganHasil;

    cout << "Silahkan pilih data yang akan diubah" << endl;
    cout << "No : ";
    cin >> pilihNomor;
    cin.ignore();
    update = bacaDong(data3, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Teks                   : " << update.TEKSkeDESIMAL_teks << endl;
    cout << "Bentuk Desimal (ASCII) : " << update.TEKSkeDESIMAL_hasil << endl;
    cout << endl;
    cout << "Ubah data" << endl;
    cout << "Teks menjadi           : ";
    cin.getline(update.TEKSkeDESIMAL_teks, 1000);
    for (int i = 0; i < strlen(update.TEKSkeDESIMAL_teks); i++)
    {
        tampunganHasil += to_string(int(update.TEKSkeDESIMAL_teks[i])) + " ";
    }
    tampunganHasil.copy(update.TEKSkeDESIMAL_hasil, tampunganHasil.length());
    update.TEKSkeDESIMAL_hasil[tampunganHasil.length()] = '\0';
    tulisTEKSkeDESIMAL(data3, pilihNomor, update);
    cout << endl;
    cout << "Data berhasil diubah menjadi" << endl;
    cout << "Teks                   : " << update.TEKSkeDESIMAL_teks << endl;
    cout << "Hasil Desimal (ASCII)  : " << update.TEKSkeDESIMAL_hasil << endl;
    cout << endl;
}

void apusTEKSkeDESIMAL(fstream &data3)
{
    fstream dataSementara;
    Cipher kosong, sementara;
    int pilihNomor, keluaran, size;

    size = ambilUkuran_data(data3);

    cout << "Silahkan pilih data yang akan diapus" << endl;
    cout << "No : ";
    cin >> pilihNomor;
    cin.ignore();

    kosong = bacaDong(data3, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Teks                   : " << kosong.TEKSkeDESIMAL_teks << endl;
    cout << "Bentuk Desimal (ASCII) : " << kosong.TEKSkeDESIMAL_hasil << endl;

    kosong.kosongTEKSkeDESIMAL = 0;
    tulisTEKSkeDESIMAL(data3, pilihNomor, kosong);

    dataSementara.open("temp.bin", ios::trunc | ios::in | ios::out | ios::binary);
    keluaran = 0;
    for (int i = 1; i <= size; i++)
    {
        sementara = bacaDong(data3, i);
        if (sementara.kosongTEKSkeDESIMAL > 0)
        {
            tulisTEKSkeDESIMAL(dataSementara, (i - keluaran), sementara);
        }
        else
        {
            keluaran++;
            cout << "Berhasil dihapus" << endl;
            cout << endl;
        }
    }

    size = ambilUkuran_data(dataSementara);
    data3.close();
    data3.open("data_TEKSkeDESIMAL.bin", ios::trunc | ios::out | ios::in | ios::binary);
    data3.close();
    data3.open("data_TEKSkeDESIMAL.bin", ios::out | ios::in | ios::binary);

    for (int i = 1; i <= size; i++)
    {
        sementara = bacaDong(dataSementara, i);
        tulisTEKSkeDESIMAL(data3, i, sementara);
    }
}

void DESIMALkeTEKS(fstream &data4)
{
    Cipher inputDESIMALkeTEKS;
    string tampunganHasil = "", angkaString = "";
    int size, angkaInt;

    size = ambilUkuran_data(data4);

    cout << endl;
    cout << "Masukkan bentuk DESIMAL/ASCII (pisah dengan spasi) : ";
    cin.getline(inputDESIMALkeTEKS.DESIMALkeTEKS_teks, 1000);

    for (int i = 0; i < strlen(inputDESIMALkeTEKS.DESIMALkeTEKS_teks); i++)
    {
        if (inputDESIMALkeTEKS.DESIMALkeTEKS_teks[i] == ' ')
        {
            angkaInt = stoi(angkaString);
            if (angkaInt >= 0 && angkaInt <= 127)
            {
                tampunganHasil += char(angkaInt);
            }
            else
            {
                cout << "Nilai DESIMAL/ASCII tidak valid        : " << angkaInt << endl;
            }
            angkaString = "";
        }
        else
        {
            angkaString += inputDESIMALkeTEKS.DESIMALkeTEKS_teks[i];
        }
    }

    if (!angkaString.empty())
    {
        int angkaInt = stoi(angkaString);
        if (angkaInt >= 0 && angkaInt <= 127)
        {
            tampunganHasil += char(angkaInt);
        }
        else
        {
            cout << "Nilai DESIMAL/ASCII tidak valid            : " << angkaInt << endl;
        }
    }

    tampunganHasil.copy(inputDESIMALkeTEKS.DESIMALkeTEKS_hasil, tampunganHasil.length());
    inputDESIMALkeTEKS.DESIMALkeTEKS_hasil[tampunganHasil.length()] = '\0';

    cout << "Hasil Decipher                                     : " << inputDESIMALkeTEKS.DESIMALkeTEKS_hasil << endl;

    tulisTEKSkeDESIMAL(data4, size + 1, inputDESIMALkeTEKS);

    cout << endl;
}

void tampilkanDESIMALkeTEKS(fstream &data4)
{
    Cipher tampil;
    int size;

    size = ambilUkuran_data(data4);

    for (int i = 1; i <= size; i++)
    {
        tampil = bacaDong(data4, i);
        cout << i << endl;
        cout << "Bentuk Desimal (ASCII) : ";
        cout << tampil.DESIMALkeTEKS_teks << endl;
        cout << "Teks                   : ";
        cout << tampil.DESIMALkeTEKS_hasil << endl;
        cout << endl;
    }
}

void ubahDESIMALkeTEKS(fstream &data4)
{
    Cipher update;
    int pilihNomor;
    string tampunganHasil = "", angkaString = "";
    int angkaInt;

    cout << "Silahkan pilih data yang akan diubah" << endl;
    cout << "No : ";
    cin >> pilihNomor;
    cin.ignore();
    update = bacaDong(data4, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Bentuk Desimal (ASCII) : " << update.DESIMALkeTEKS_teks << endl;
    cout << "Teks                   : " << update.DESIMALkeTEKS_hasil << endl;
    cout << endl;
    cout << "Ubah data" << endl;
    cout << "Desimal (ASCII) menjadi : ";
    cin.getline(update.DESIMALkeTEKS_teks, 1000);
    for (int i = 0; i < strlen(update.DESIMALkeTEKS_teks); i++)
    {
        if (update.DESIMALkeTEKS_teks[i] == ' ')
        {
            angkaInt = stoi(angkaString);
            if (angkaInt >= 0 && angkaInt <= 127)
            {
                tampunganHasil += char(angkaInt);
            }
            else
            {
                cout << "Nilai DESIMAL/ASCII tidak valid : " << angkaInt << endl;
            }
            angkaString = "";
        }
        else
        {
            angkaString += update.DESIMALkeTEKS_teks[i];
        }
    }

    if (!angkaString.empty())
    {
        int angkaInt = stoi(angkaString);
        if (angkaInt >= 0 && angkaInt <= 127)
        {
            tampunganHasil += char(angkaInt);
        }
        else
        {
            cout << "Nilai DESIMAL/ASCII tidak valid : " << angkaInt << endl;
        }
    }

    tampunganHasil.copy(update.DESIMALkeTEKS_hasil, tampunganHasil.length());
    update.DESIMALkeTEKS_hasil[tampunganHasil.length()] = '\0';

    tulisTEKSkeDESIMAL(data4, pilihNomor, update);

    cout << endl;
    cout << "Data berhasil diubah menjadi" << endl;
    cout << "Bentuk Desimal (ASCII) : " << update.DESIMALkeTEKS_teks << endl;
    cout << "Teks                   : " << update.DESIMALkeTEKS_hasil << endl;
    cout << endl;
}

void apusDESIMALkeTEKS(fstream &data4)
{
    fstream dataSementara;
    Cipher kosong, sementara;
    int pilihNomor, keluaran, size;

    size = ambilUkuran_data(data4);

    cout << "Silahkan pilih data yang akan diapus" << endl;
    cout << "No : ";
    cin >> pilihNomor;
    cin.ignore();

    kosong = bacaDong(data4, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Bentuk Desimal (ASCII) : " << kosong.DESIMALkeTEKS_teks << endl;
    cout << "Teks                   : " << kosong.DESIMALkeTEKS_hasil << endl;

    kosong.kosongDESIMALkeTEKS = 0;
    tulisDESIMALkeTEKS(data4, pilihNomor, kosong);

    dataSementara.open("temp.bin", ios::trunc | ios::in | ios::out | ios::binary);
    keluaran = 0;
    for (int i = 1; i <= size; i++)
    {
        sementara = bacaDong(data4, i);
        if (sementara.kosongDESIMALkeTEKS > 0)
        {
            tulisDESIMALkeTEKS(dataSementara, (i - keluaran), sementara);
        }
        else
        {
            keluaran++;
            cout << "Berhasil dihapus" << endl;
            cout << endl;
        }
    }

    size = ambilUkuran_data(dataSementara);
    data4.close();
    data4.open("data_DESIMALkeTEKS.bin", ios::trunc | ios::out | ios::in | ios::binary);
    data4.close();
    data4.open("data_DESIMALkeTEKS.bin", ios::out | ios::in | ios::binary);

    for (int i = 1; i <= size; i++)
    {
        sementara = bacaDong(dataSementara, i);
        tulisDESIMALkeTEKS(data4, i, sementara);
    }
}

void autoEnter()
{
    initscr();
    cbreak();
    noecho();
}

void bannerSelamatDatang()
{
    cout << endl;
    cout << "           ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗ " << endl;
    cout << "           ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝ " << endl;
    cout << "           ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗   " << endl;
    cout << "           ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝   " << endl;
    cout << "           ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗ " << endl;
    cout << "            ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝ " << endl;
    cout << endl;
}

void bannerInfo()
{
    cout << "                  Dalam program ini kalian dapat merubah teks" << endl;
    cout << "           Menjadi BINER, DESIMAL, HEKSADESIMAL, OKTAL | (vice versa)" << endl;
    cout << endl;
    cout << "                      Program ini menggunakan konsep CRUD" << endl;
    cout << "        Dimana kalian dapat men-CREATE, READ, UPDATE, DELETE, sebuah data" << endl;
    cout << endl;
    cout << "         Untuk catatan: Biner yang digunakan adalah Biner 8-bit" << endl;
    cout << "                        Semua data akan disimpan ke dalam sebuah file" << endl;
    cout << "                        Program belum final T__T" << endl;
    cout << "                        Namun CRUD sudah berjalan :)" << endl;
    cout << endl;
}

void bannerCipher()
{
    cout << endl;
    cout << "                   ██████╗██╗██████╗ ██╗  ██╗███████╗██████╗  " << endl;
    cout << "                  ██╔════╝██║██╔══██╗██║  ██║██╔════╝██╔══██╗ " << endl;
    cout << "                  ██║     ██║██████╔╝███████║█████╗  ██████╔╝ " << endl;
    cout << "                  ██║     ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗ " << endl;
    cout << "                  ╚██████╗██║██║     ██║  ██║███████╗██║  ██║ " << endl;
    cout << "                   ╚═════╝╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ " << endl;
    cout << endl;
}

void bannerEncipher()
{
    cout << endl;
    cout << "          ███████╗███╗   ██╗ ██████╗██╗██████╗ ██╗  ██╗███████╗██████╗  " << endl;
    cout << "          ██╔════╝████╗  ██║██╔════╝██║██╔══██╗██║  ██║██╔════╝██╔══██╗ " << endl;
    cout << "          █████╗  ██╔██╗ ██║██║     ██║██████╔╝███████║█████╗  ██████╔╝ " << endl;
    cout << "          ██╔══╝  ██║╚██╗██║██║     ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗ " << endl;
    cout << "          ███████╗██║ ╚████║╚██████╗██║██║     ██║  ██║███████╗██║  ██║ " << endl;
    cout << "          ╚══════╝╚═╝  ╚═══╝ ╚═════╝╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ " << endl;
    cout << endl;
}

void bannerDecipher()
{
    cout << endl;
    cout << "           ██████╗ ███████╗ ██████╗██╗██████╗ ██╗  ██╗███████╗██████╗  " << endl;
    cout << "           ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██║  ██║██╔════╝██╔══██╗ " << endl;
    cout << "           ██║  ██║█████╗  ██║     ██║██████╔╝███████║█████╗  ██████╔╝ " << endl;
    cout << "           ██║  ██║██╔══╝  ██║     ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗ " << endl;
    cout << "           ██████╔╝███████╗╚██████╗██║██║     ██║  ██║███████╗██║  ██║ " << endl;
    cout << "           ╚═════╝ ╚══════╝ ╚═════╝╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ " << endl;
    cout << endl;
}

void bannerRiwayat()
{
    cout << endl;
    cout << "             ██╗  ██╗██╗███████╗████████╗ ██████╗ ██████╗ ██╗   ██╗ " << endl;
    cout << "             ██║  ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝ " << endl;
    cout << "             ███████║██║███████╗   ██║   ██║   ██║██████╔╝ ╚████╔╝  " << endl;
    cout << "             ██╔══██║██║╚════██║   ██║   ██║   ██║██╔══██╗  ╚██╔╝   " << endl;
    cout << "             ██║  ██║██║███████║   ██║   ╚██████╔╝██║  ██║   ██║    " << endl;
    cout << "             ╚═╝  ╚═╝╚═╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝    " << endl;
    cout << endl;
}

void bannerUpdate()
{
    cout << endl;
    cout << "               ██╗   ██╗██████╗ ██████╗  █████╗ ████████╗███████╗ " << endl;
    cout << "               ██║   ██║██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██╔════╝ " << endl;
    cout << "               ██║   ██║██████╔╝██║  ██║███████║   ██║   █████╗   " << endl;
    cout << "               ██║   ██║██╔═══╝ ██║  ██║██╔══██║   ██║   ██╔══╝   " << endl;
    cout << "               ╚██████╔╝██║     ██████╔╝██║  ██║   ██║   ███████╗ " << endl;
    cout << "                ╚═════╝ ╚═╝     ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚══════╝ " << endl;
    cout << endl;
}

void bannerDelete()
{
    cout << endl;
    cout << "               ██████╗ ███████╗██╗     ███████╗████████╗███████╗ " << endl;
    cout << "               ██╔══██╗██╔════╝██║     ██╔════╝╚══██╔══╝██╔════╝ " << endl;
    cout << "               ██║  ██║█████╗  ██║     █████╗     ██║   █████╗   " << endl;
    cout << "               ██║  ██║██╔══╝  ██║     ██╔══╝     ██║   ██╔══╝   " << endl;
    cout << "               ██████╔╝███████╗███████╗███████╗   ██║   ███████╗ " << endl;
    cout << "               ╚═════╝ ╚══════╝╚══════╝╚══════╝   ╚═╝   ╚══════╝ " << endl;
    cout << endl;
}

void bannerExit()
{
    cout << endl;
    cout << "   ████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗    ██╗   ██╗ ██████╗ ██╗   ██╗ " << endl;
    cout << "   ╚══██╔══╝██║  ██║██╔══██╗████╗  ██║██║ ██╔╝    ╚██╗ ██╔╝██╔═══██╗██║   ██║ " << endl;
    cout << "      ██║   ███████║███████║██╔██╗ ██║█████╔╝      ╚████╔╝ ██║   ██║██║   ██║ " << endl;
    cout << "      ██║   ██╔══██║██╔══██║██║╚██╗██║██╔═██╗       ╚██╔╝  ██║   ██║██║   ██║ " << endl;
    cout << "      ██║   ██║  ██║██║  ██║██║ ╚████║██║  ██╗       ██║   ╚██████╔╝╚██████╔╝ " << endl;
    cout << "      ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝       ╚═╝    ╚═════╝  ╚═════╝  " << endl;
    cout << endl;
    cout << "                            █████╗ ███╗   ██╗██████╗                          " << endl;
    cout << "                           ██╔══██╗████╗  ██║██╔══██╗                         " << endl;
    cout << "                           ███████║██╔██╗ ██║██║  ██║                         " << endl;
    cout << "                           ██╔══██║██║╚██╗██║██║  ██║                         " << endl;
    cout << "                           ██║  ██║██║ ╚████║██████╔╝                         " << endl;
    cout << "                           ╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝                          " << endl;
    cout << endl;
    cout << "               ███████╗███████╗███████╗    ██╗   ██╗ ██████╗ ██╗   ██╗        " << endl;
    cout << "               ██╔════╝██╔════╝██╔════╝    ╚██╗ ██╔╝██╔═══██╗██║   ██║        " << endl;
    cout << "               ███████╗█████╗  █████╗       ╚████╔╝ ██║   ██║██║   ██║        " << endl;
    cout << "               ╚════██║██╔══╝  ██╔══╝        ╚██╔╝  ██║   ██║██║   ██║        " << endl;
    cout << "               ███████║███████╗███████╗       ██║   ╚██████╔╝╚██████╔╝        " << endl;
    cout << "               ╚══════╝╚══════╝╚══════╝       ╚═╝    ╚═════╝  ╚═════╝         " << endl;
    cout << endl;
}

void fungsiExit()
{
    char awal;

    cout << "Kembali ke awal? [y/n]: ";
    autoEnter();
    awal = getchar();
    endwin();
    if (awal == 'n' || awal == 'N')
    {
        system("clear");
        bannerExit();
        exit(0);
    }
}
