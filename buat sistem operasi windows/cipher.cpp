#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

struct Cipher
{
    int kosongTEKSkeBINER = 1;
    char TEKSkeBINER_teks[1000];
    char TEKSkeBINER_hasil[8000];
    int kosongBINERkeTEKS = 1;
    char BINERkeTEKS_hasil[8000];
    char BINERkeTEKS_teks[1000];
    // char teksDesimal[1000]
    // char hasilDesimal[]
    // char teksHeksa[1000]
    // char hasilHeksa[]
    // char teksOktal[1000]
    // char hasilOktal[]
};

string getPilihan();
Cipher bacaDong(fstream &data, int pos);
int ambilUkuran_data(fstream &data);
void cekData_TEKSkeBINER(fstream &data);
void cekData_BINERkeTEKS(fstream &data2);
void tulisTEKSkeBINER(fstream &data, int pos, Cipher &inputTEKSkeBINER);
void tulisBINERkeTEKS(fstream &data2, int pos, Cipher &inputBINERkeTEKS);
void menuEncipher();
void menuDecipher();
void pilihMenu_encipher(fstream &data, fstream &data2);
void pilihMenu_decipher(fstream &data, fstream &data2);
void pilihMenu_riwayat(fstream &data, fstream &data2);
void pilihMenu_update(fstream &data, fstream &data2);
void pilihMenu_delete(fstream &data, fstream &data2);
void menuRUD(fstream &data, fstream &data2);
void TEKSkeBINER(fstream &data);
void tampilkanTEKSkeBINER(fstream &data);
void ubahTEKSkeBINER(fstream &data);
void apusTEKSkeBINER(fstream &data);
void BINERkeTEKS(fstream &data2);
void tampilkanBINERkeTEKS(fstream &data2);
void ubahBINERkeTEKS(fstream &data2);
void apusBINERkeTEKS(fstream &data2);
void bannerSelamatDatang();
void bannerInfo();
void bannerCipher();
void bannerEncipher();
void bannerDecipher();
void bannerRiwayat();
void bannerUpdate();
void bannerDelete();
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

string getPilihan()
{
    string pilih;

    // Cipher, undiceper
    cout << setw(45) << "Pilih menu" << endl;
    cout << setw(45) << "1. Encipher" << endl;
    cout << setw(45) << "2. Decipher" << endl;
    cout << setw(44) << "3. Riwayat" << endl;
    cout << setw(41) << "0. Exit" << endl;
    cout << setw(41) << "Pilih? ";
    getline(cin, pilih);
    return pilih;
}

int main()
{
    fstream data, data2;
    string pilih;

    bannerSelamatDatang();
    bannerInfo();
    cekData_TEKSkeBINER(data);
    cekData_BINERkeTEKS(data2);

    while (pilih != "0")
    {
        system("cls");
        bannerCipher();
        pilih = getPilihan();
        if (pilih == "1")
        {
            system("cls");
            bannerEncipher();
            pilihMenu_encipher(data, data2);
        }
        else if (pilih == "2")
        {
            system("cls");
            bannerDecipher();
            pilihMenu_decipher(data, data2);
        }
        else if (pilih == "3")
        {
            system("cls");
            bannerRiwayat();
            menuRUD(data, data2);
        }
        else if (pilih == "0")
        {
            cout << setw(44) << "See you ^^" << endl;
        }
        else
        {
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
        cout << "DATABASE Ditemukan" << endl;
        cout << "Tekan enter untuk memuat... ";
        getchar();
        cout << endl;
        prosesAnimasi(clog, 30, "Memuat DATABASE [");
        cout << "]" << endl;
        cout << "Berhasil ^^";
        cout << endl;
    }
    else
    {
        cout << "DATABASE Tidak Ditemukan" << endl;
        cout << "Tekan enter untuk membuat... ";
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

void menuEncipher()
{
    cout << setw(45) << "Pilih menu" << endl;
    cout << setw(48) << "1. Teks ke Biner" << endl;
    cout << setw(50) << "2. Teks ke Desimal" << endl;
    cout << setw(55) << "3. Teks ke Heksadesimal" << endl;
    cout << setw(48) << "4. Teks ke Oktal" << endl;
    cout << setw(58) << "Tekan enter untuk kembali!" << endl;
    cout << setw(39) << "Pilih? ";
}

void menuDecipher()
{
    cout << setw(45) << "Pilih menu" << endl;
    cout << setw(48) << "1. Biner ke teks" << endl;
    cout << setw(50) << "2. Desimal ke teks" << endl;
    cout << setw(55) << "3. Heksadesimal ke teks" << endl;
    cout << setw(48) << "4. Oktal ke teks" << endl;
    cout << setw(58) << "Tekan enter untuk kembali!" << endl;
    cout << setw(39) << "Pilih? ";
}

void pilihMenu_encipher(fstream &data, fstream &data2)
{
    string pilihDecipher;

    menuEncipher();
    getline(cin, pilihDecipher);
    if (pilihDecipher == "1")
    {
        TEKSkeBINER(data);
    }
    else if (pilihDecipher == "2")
    {
        // TEKSkeDESIMAL();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    else if (pilihDecipher == "3")
    {
        // TEKSkeHEKSA();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    else if (pilihDecipher == "4")
    {
        // TEKSkeOKTAL();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    fungsiExit();
}

void pilihMenu_decipher(fstream &data, fstream &data2)
{
    string pilihUndecipher;

    menuDecipher();
    getline(cin, pilihUndecipher);
    if (pilihUndecipher == "1")
    {
        BINERkeTEKS(data2);
    }
    else if (pilihUndecipher == "2")
    {
        // TEKSkeDESIMAL();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    else if (pilihUndecipher == "3")
    {
        // TEKSkeHEKSA();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    else if (pilihUndecipher == "4")
    {
        // TEKSkeOKTAL();
        cout << "COMING SOON !" << endl;
        cout << endl;
    }
    fungsiExit();
}

void pilihMenu_riwayat(fstream &data, fstream &data2)
{
    string pilihRiwayat, pilihRiwayat2;
    int size, size2;

    size = ambilUkuran_data(data);
    size2 = ambilUkuran_data(data2);

    cout << setw(45) << "Pilih menu" << endl;
    cout << setw(45) << "1. Encipher" << endl;
    cout << setw(45) << "2. Decipher" << endl;
    cout << setw(60) << "Tekan enter untuk kembali!" << endl;
    cout << setw(41) << "Pilih? ";
    getline(cin, pilihRiwayat);
    if (pilihRiwayat == "1")
    {
        system("cls");
        bannerRiwayat();
        menuEncipher();
        getline(cin, pilihRiwayat2);
        if (pilihRiwayat2 == "1")
        {
            if (size < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
            }
            else
            {
                tampilkanTEKSkeBINER(data);
            }
        }
        else if (pilihRiwayat2 == "2")
        {
            // tampilkanDesimal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihRiwayat2 == "3")
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihRiwayat2 == "4")
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else
        {
        }
    }
    else if (pilihRiwayat == "2")
    {
        system("cls");
        bannerRiwayat();
        menuDecipher();
        getline(cin, pilihRiwayat2);
        if (pilihRiwayat2 == "1")
        {
            if (size2 < 1)
            {
                cout << "Riwayat tidak ditemukan!" << endl;
            }
            else
            {
                tampilkanBINERkeTEKS(data2);
            }
        }
        else if (pilihRiwayat2 == "2")
        {
            // tampilkanDesimal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihRiwayat2 == "3")
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihRiwayat2 == "4")
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else
        {
        }
    }
    fungsiExit();
}

void pilihMenu_update(fstream &data, fstream &data2)
{
    string pilihUpdate, pilihUpdate2;
    int size, size2;

    size = ambilUkuran_data(data);
    size2 = ambilUkuran_data(data2);

    cout << setw(45) << "Pilih menu" << endl;
    cout << setw(45) << "1. Encipher" << endl;
    cout << setw(45) << "2. Decipher" << endl;
    cout << setw(60) << "Tekan enter untuk kembali!" << endl;
    cout << setw(41) << "Pilih? ";
    getline(cin, pilihUpdate);
    if (pilihUpdate == "1")
    {
        system("cls");
        bannerUpdate();
        menuEncipher();
        getline(cin, pilihUpdate2);
        if (pilihUpdate2 == "1")
        {
            if (size < 1)
            {
                cout << "Data tidak ditemukan!" << endl;
            }
            else
            {
                tampilkanTEKSkeBINER(data);
                ubahTEKSkeBINER(data);
            }
        }
        else if (pilihUpdate2 == "2")
        {
            // tampilkanDesimal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihUpdate2 == "3")
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihUpdate2 == "4")
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else
        {
        }
    }
    else if (pilihUpdate == "2")
    {
        system("cls");
        bannerUpdate();
        menuDecipher();
        getline(cin, pilihUpdate2);
        if (pilihUpdate2 == "1")
        {
            if (size2 < 1)
            {
                cout << "Data tidak ditemukan!" << endl;
            }
            else
            {
                tampilkanBINERkeTEKS(data2);
                ubahBINERkeTEKS(data2);
            }
        }
        else if (pilihUpdate2 == "2")
        {
            // tampilkanDesimal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihUpdate2 == "3")
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihUpdate2 == "4")
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else
        {
        }
    }
    fungsiExit();
}

void pilihMenu_delete(fstream &data, fstream &data2)
{
    string pilihDelete, pilihDelete2;
    int size, size2;

    size = ambilUkuran_data(data);
    size2 = ambilUkuran_data(data2);

    cout << setw(45) << "Pilih menu" << endl;
    cout << setw(45) << "1. Encipher" << endl;
    cout << setw(45) << "2. Dechiper" << endl;
    cout << setw(60) << "Tekan enter untuk kembali!" << endl;
    cout << setw(41) << "Pilih? ";
    getline(cin, pilihDelete);
    if (pilihDelete == "1")
    {
        system("cls");
        bannerDelete();
        menuEncipher();
        getline(cin, pilihDelete2);
        if (pilihDelete2 == "1")
        {
            if (size < 1)
            {
                cout << "Data tidak ditemukan!" << endl;
            }
            else
            {
                tampilkanTEKSkeBINER(data);
                apusTEKSkeBINER(data);
            }
        }
        else if (pilihDelete2 == "2")
        {
            // tampilkanDesimal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihDelete2 == "3")
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihDelete2 == "4")
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else
        {
        }
    }
    else if (pilihDelete == "2")
    {
        system("cls");
        bannerDelete();
        menuDecipher();
        getline(cin, pilihDelete2);
        if (pilihDelete2 == "1")
        {
            if (size2 < 1)
            {
                cout << "Data tidak ditemukan!" << endl;
            }
            else
            {
                tampilkanBINERkeTEKS(data2);
                apusBINERkeTEKS(data2);
            }
        }
        else if (pilihDelete2 == "2")
        {
            // tampilkanDesimal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihDelete2 == "3")
        {
            // tampilkanHeksa();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else if (pilihDelete2 == "4")
        {
            // tampilkanOktal();
            cout << "COMING SOON !" << endl;
            cout << endl;
        }
        else
        {
        }
    }
    fungsiExit();
}

void menuRUD(fstream &data, fstream &data2)
{
    string pilihRUD;

    cout << setw(45) << "Pilih menu" << endl;
    cout << setw(46) << "1. Tampilkan" << endl;
    cout << setw(41) << "2. Ubah" << endl;
    cout << setw(42) << "3. Hapus" << endl;
    cout << setw(60) << "Tekan enter untuk kembali!" << endl;
    cout << setw(41) << "Pilih? ";
    getline(cin, pilihRUD);
    if (pilihRUD == "1")
    {
        system("cls");
        bannerRiwayat();
        pilihMenu_riwayat(data, data2);
    }
    else if (pilihRUD == "2")
    {
        system("cls");
        bannerUpdate();
        pilihMenu_update(data, data2);
    }
    else if (pilihRUD == "3")
    {
        system("cls");
        bannerDelete();
        pilihMenu_delete(data, data2);
    }
}

void TEKSkeBINER(fstream &data)
{
    Cipher inputTEKSkeBINER;
    string strbit; // digunakan untuk menampung value bitset
    int size;

    size = ambilUkuran_data(data);

    cout << "Masukkan teks: ";
    cin.getline(inputTEKSkeBINER.TEKSkeBINER_teks, 1000);

    for (int i = 0; i < strlen(inputTEKSkeBINER.TEKSkeBINER_teks); i++)
    {
        bitset<8> hasilTEKSkeBINER(inputTEKSkeBINER.TEKSkeBINER_teks[i]);
        strbit += hasilTEKSkeBINER.to_string();
    }
    strbit.copy(inputTEKSkeBINER.TEKSkeBINER_hasil, strbit.length());
    inputTEKSkeBINER.TEKSkeBINER_hasil[strbit.length()] = '\0';

    cout << "Hasil Cipher: " << inputTEKSkeBINER.TEKSkeBINER_hasil;

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
        cout << "No: ";
        cout << i << endl;
        cout << "Teks\t\t\t\t: ";
        cout << tampilTEKSkeBINER.TEKSkeBINER_teks << endl;
        cout << "Bentuk Biner 8-Bit (Tanpa Spasi): ";
        cout << tampilTEKSkeBINER.TEKSkeBINER_hasil << endl;
        cout << endl;
    }
}

void ubahTEKSkeBINER(fstream &data)
{
    Cipher updateTEKSkeBINER;
    string strbit;
    int pilihNomor;

    cout << "Silahkan pilih data yang akan diubah" << endl;
    cout << "No: ";
    cin >> pilihNomor;
    cin.ignore();

    updateTEKSkeBINER = bacaDong(data, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Teks                            : " << updateTEKSkeBINER.TEKSkeBINER_teks << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi): " << updateTEKSkeBINER.TEKSkeBINER_hasil << endl;

    cout << endl;

    cout << "Ubah data" << endl;
    cout << "Teks menjadi                    : ";
    cin.getline(updateTEKSkeBINER.TEKSkeBINER_teks, 1000);
    for (int i = 0; i < strlen(updateTEKSkeBINER.TEKSkeBINER_teks); i++)
    {
        bitset<8> hasilTEKSkeBINER(updateTEKSkeBINER.TEKSkeBINER_teks[i]);
        strbit += hasilTEKSkeBINER.to_string();
    }
    strbit.copy(updateTEKSkeBINER.TEKSkeBINER_hasil, strbit.length());
    updateTEKSkeBINER.TEKSkeBINER_hasil[strbit.length()] = '\0';

    tulisTEKSkeBINER(data, pilihNomor, updateTEKSkeBINER);

    cout << endl;
    cout << "Data berhasil diubah menjadi" << endl;
    cout << "Teks                            : " << updateTEKSkeBINER.TEKSkeBINER_teks << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi): " << updateTEKSkeBINER.TEKSkeBINER_hasil << endl;
    cout << endl;
}

void apusTEKSkeBINER(fstream &data)
{
    fstream dataSementara;
    Cipher kosong, sementara;
    int pilihNomor, keluaran, size;

    size = ambilUkuran_data(data);

    cout << "Silahkan pilih data yang akan diapus" << endl;
    cout << "No: ";
    cin >> pilihNomor;
    cin.ignore();

    kosong = bacaDong(data, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Teks                            : " << kosong.TEKSkeBINER_teks << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi): " << kosong.TEKSkeBINER_hasil << endl;

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
    int size;

    size = ambilUkuran_data(data2);

    cout << endl;
    cout << "Masukkan kode biner 8-Bit (tanpa spasi): ";
    cin.getline(inputBINERkeTEKS.BINERkeTEKS_teks, 1000);

    string hasilBINERkeTeks;
    for (int i = 0; i < strlen(inputBINERkeTEKS.BINERkeTEKS_teks); i += 8)
    {
        string kodeBiner(inputBINERkeTEKS.BINERkeTEKS_teks);
        bitset<8> hasil(kodeBiner.substr(i, 8));
        hasilBINERkeTeks += char(hasil.to_ulong());
    }
    hasilBINERkeTeks.copy(inputBINERkeTEKS.BINERkeTEKS_hasil, hasilBINERkeTeks.length());
    inputBINERkeTEKS.BINERkeTEKS_hasil[hasilBINERkeTeks.length()] = '\0';

    cout << "Hasil Undecipher                       : " << inputBINERkeTEKS.BINERkeTEKS_hasil << endl;

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
        cout << "No: ";
        cout << i << endl;
        cout << "Bentuk Biner 8-Bit (Tanpa Spasi): ";
        cout << tampil.BINERkeTEKS_teks << endl;
        cout << "Teks\t\t\t\t: ";
        cout << tampil.BINERkeTEKS_hasil << endl;
        cout << endl;
    }
}

void ubahBINERkeTEKS(fstream &data2)
{
    Cipher update;
    string strbit;
    int pilihNomor;

    cout << "Silahkan pilih data yang akan diubah" << endl;
    cout << "No: ";
    cin >> pilihNomor;
    cin.ignore();

    update = bacaDong(data2, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi): " << update.BINERkeTEKS_teks << endl;
    cout << "Teks                            : " << update.BINERkeTEKS_hasil << endl;

    cout << endl;

    cout << "Ubah data" << endl;
    cout << "Biner menjadi                   : ";
    cin.getline(update.BINERkeTEKS_teks, 1000);
    string hasilBINERkeTeks;
    for (int i = 0; i < strlen(update.BINERkeTEKS_teks); i += 8)
    {
        string kodeBiner(update.BINERkeTEKS_teks);
        bitset<8> hasil(kodeBiner.substr(i, 8));
        hasilBINERkeTeks += char(hasil.to_ulong());
    }
    hasilBINERkeTeks.copy(update.BINERkeTEKS_hasil, hasilBINERkeTeks.length());
    update.BINERkeTEKS_hasil[hasilBINERkeTeks.length()] = '\0';

    tulisBINERkeTEKS(data2, pilihNomor, update);

    cout << endl;
    cout << "Data berhasil diubah menjadi" << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi): " << update.BINERkeTEKS_teks << endl;
    cout << "Teks                            : " << update.BINERkeTEKS_hasil << endl;
    cout << endl;
}

void apusBINERkeTEKS(fstream &data2)
{
    fstream dataSementara;
    Cipher kosong, sementara;
    int pilihNomor, keluaran, size;

    size = ambilUkuran_data(data2);

    cout << "Silahkan pilih data yang akan diapus" << endl;
    cout << "No: ";
    cin >> pilihNomor;
    cin.ignore();

    kosong = bacaDong(data2, pilihNomor);
    cout << endl;
    cout << "Data." << endl;
    cout << "Bentuk Biner 8-Bit (Tanpa Spasi): " << kosong.BINERkeTEKS_hasil << endl;
    cout << "Teks                            : " << kosong.BINERkeTEKS_teks << endl;

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

void bannerSelamatDatang()
{
    cout << endl;
    cout << "              _______ _______ _______ _______ _______ _______ _______ " << endl;
    cout << "             |       |       |       |       |       |       |       |" << endl;
    cout << "             | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "             | |   | | |   | | |   | | |   | | |   | | |   | | |   | |" << endl;
    cout << "             | |W  | | |E  | | |L  | | |C  | | |O  | | |M  | | |E  | |" << endl;
    cout << "             | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "             |_______|_______|_______|_______|_______|_______|_______|" << endl;
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
    cout << "                 _______ _______ _______ _______ _______ _______ " << endl;
    cout << "                |       |       |       |       |       |       |" << endl;
    cout << "                | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "                | |   | | |   | | |   | | |   | | |   | | |   | |" << endl;
    cout << "                | |C  | | |I  | | |P  | | |H  | | |E  | | |R  | |" << endl;
    cout << "                | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "                |_______|_______|_______|_______|_______|_______|" << endl;
    cout << endl;
}

void bannerEncipher()
{
    cout << endl;
    cout << "         _______ _______ _______ _______ _______ _______ _______ _______ " << endl;
    cout << "        |       |       |       |       |       |       |       |       |" << endl;
    cout << "        | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "        | |   | | |   | | |   | | |   | | |   | | |   | | |   | | |   | |" << endl;
    cout << "        | |E  | | |N  | | |C  | | |I  | | |P  | | |H  | | |E  | | |R  | |" << endl;
    cout << "        | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "        |_______|_______|_______|_______|_______|_______|_______|_______|" << endl;
    cout << endl;
}

void bannerDecipher()
{
    cout << endl;
    cout << "         _______ _______ _______ _______ _______ _______ _______ _______ " << endl;
    cout << "        |       |       |       |       |       |       |       |       |" << endl;
    cout << "        | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "        | |   | | |   | | |   | | |   | | |   | | |   | | |   | | |   | |" << endl;
    cout << "        | |D  | | |E  | | |C  | | |I  | | |P  | | |H  | | |E  | | |R  | |" << endl;
    cout << "        | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "        |_______|_______|_______|_______|_______|_______|_______|_______|" << endl;
    cout << endl;
}

void bannerRiwayat()
{
    cout << endl;
    cout << "            _______ _______ _______ _______ _______ _______ _______ " << endl;
    cout << "           |       |       |       |       |       |       |       |" << endl;
    cout << "           | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "           | |   | | |   | | |   | | |   | | |   | | |   | | |   | |" << endl;
    cout << "           | |H  | | |I  | | |S  | | |T  | | |O  | | |R  | | |Y  | |" << endl;
    cout << "           | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "           |_______|_______|_______|_______|_______|_______|_______|" << endl;
    cout << endl;
}

void bannerUpdate()
{
    cout << endl;
    cout << "	          _______ _______ _______ _______ _______ _______ " << endl;
    cout << "	         |       |       |       |       |       |       |" << endl;
    cout << "	         | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "	         | |   | | |   | | |   | | |   | | |   | | |   | |" << endl;
    cout << "	         | |U  | | |P  | | |D  | | |A  | | |T  | | |E  | |" << endl;
    cout << "	         | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "	         |_______|_______|_______|_______|_______|_______|" << endl;
    cout << endl;
}

void bannerDelete()
{
    cout << endl;
    cout << "	          _______ _______ _______ _______ _______ _______ " << endl;
    cout << "	         |       |       |       |       |       |       |" << endl;
    cout << "	         | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "	         | |   | | |   | | |   | | |   | | |   | | |   | |" << endl;
    cout << "	         | |D  | | |E  | | |L  | | |E  | | |T  | | |E  | |" << endl;
    cout << "	         | +---+ | +---+ | +---+ | +---+ | +---+ | +---+ |" << endl;
    cout << "	         |_______|_______|_______|_______|_______|_______|" << endl;
    cout << endl;
}

void fungsiExit()
{
    string awal;

    cout << "kembali ke awal? [y/n]: ";
    getline(cin, awal);
    if (awal == "n" || awal == "N")
    {
        exit(0);
    }
}
