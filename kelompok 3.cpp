#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

struct Barang {
    string kode;
    string nama;
    double harga;
    int stok;
};

struct Transaksi {
    vector<Barang> barangDibeli;
    vector<int> jumlah;
    double totalHarga;
};

vector<Barang> inventaris;
vector<Transaksi> riwayatTransaksi;

void tambahBarang() {
    Barang barangBaru;
    cout << "Masukkan kode barang: ";
    cin >> barangBaru.kode;
    cout << "Masukkan nama barang: ";
    cin.ignore();
    getline(cin, barangBaru.nama);
    cout << "Masukkan harga barang: ";
    cin >> barangBaru.harga;
    cout << "Masukkan stok barang: ";
    cin >> barangBaru.stok;

    inventaris.push_back(barangBaru);
    cout << "Barang berhasil ditambahkan ke dalam inventaris." << endl;
}

void tampilkanInventaris() {
    cout << left << setw(10) << "Kode" << setw(20) << "Nama" << setw(10) << "Harga" << setw(10) << "Stok" << endl;
    for (const auto& barang : inventaris) {
        cout << left << setw(10) << barang.kode << setw(20) << barang.nama << setw(10) << barang.harga << setw(10) << barang.stok << endl;
    }
}

void cariBarang() {
    string kode;
    cout << "Masukkan kode barang yang dicari: ";
    cin >> kode;

    bool ditemukan = false;
    for (const auto& barang : inventaris) {
        if (barang.kode == kode) {
            cout << left << setw(10) << "Kode" << setw(20) << "Nama" << setw(10) << "Harga" << setw(10) << "Stok" << endl;
            cout << left << setw(10) << barang.kode << setw(20) << barang.nama << setw(10) << barang.harga << setw(10) << barang.stok << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Barang dengan kode " << kode << " tidak ditemukan." << endl;
    }
}

void catatTransaksi() {
    Transaksi transaksiBaru;
    char lanjut;
    do {
        string kode;
        int jumlah;
        cout << "Masukkan kode barang: ";
        cin >> kode;
        cout << "Masukkan jumlah: ";
        cin >> jumlah;

        bool ditemukan = false;
        for (auto& barang : inventaris) {
            if (barang.kode == kode) {
                if (barang.stok >= jumlah) {
                    transaksiBaru.barangDibeli.push_back(barang);
                    transaksiBaru.jumlah.push_back(jumlah);
                    barang.stok -= jumlah;
                    transaksiBaru.totalHarga += barang.harga * jumlah;
                    ditemukan = true;
                } else {
                    cout << "Stok tidak mencukupi." << endl;
                }
                break;
            }
        }

        if (!ditemukan) {
            cout << "Barang dengan kode " << kode << " tidak ditemukan." << endl;
        }

        cout << "Tambah barang lagi? (y/n): ";
        cin >> lanjut;
    } while (lanjut == 'y');

    riwayatTransaksi.push_back(transaksiBaru);
    cout << "Transaksi berhasil dicatat." << endl;
}

void terimaPembayaran() {
    if (riwayatTransaksi.empty()) {
        cout << "Belum ada transaksi yang dicatat." << endl;
        return;
    }

    Transaksi& transaksiTerakhir = riwayatTransaksi.back();
    double pembayaran;
    cout << "Total harga: " << transaksiTerakhir.totalHarga << endl;
    cout << "Masukkan jumlah pembayaran: ";
    cin >> pembayaran;

    if (pembayaran >= transaksiTerakhir.totalHarga) {
        double kembalian = pembayaran - transaksiTerakhir.totalHarga;
        cout << "Kembalian: " << kembalian << endl;
        cout << "Pembayaran berhasil." << endl;
    } else {
        cout << "Pembayaran tidak mencukupi." << endl;
    }
}

void cetakStruk() {
    if (riwayatTransaksi.empty()) {
        cout << "Belum ada transaksi yang dicatat." << endl;
        return;
    }

    const Transaksi& transaksiTerakhir = riwayatTransaksi.back();
    cout << "=== STRUK PEMBELIAN ===" << endl;
    cout << left << setw(20) << "Nama Barang" << setw(10) << "Jumlah" << setw(10) << "Harga" << endl;
    for (size_t i = 0; i < transaksiTerakhir.barangDibeli.size(); ++i) {
        cout << left << setw(20) << transaksiTerakhir.barangDibeli[i].nama
             << setw(10) << transaksiTerakhir.jumlah[i]
             << setw(10) << transaksiTerakhir.barangDibeli[i].harga << endl;
    }
    cout << "Total Harga: " << transaksiTerakhir.totalHarga << endl;
    cout << "=======================" << endl;
}

void simpanData() {
    ofstream fileInventaris("inventaris.txt");
    for (const auto& barang : inventaris) {
        fileInventaris << barang.kode << " " << barang.nama << " " << barang.harga << " " << barang.stok << endl;
    }
    fileInventaris.close();

    ofstream fileTransaksi("transaksi.txt");
    for (const auto& transaksi : riwayatTransaksi) {
        for (size_t i = 0; i < transaksi.barangDibeli.size(); ++i) {
            fileTransaksi << transaksi.barangDibeli[i].kode << " "
                          << transaksi.jumlah[i] << " "
                          << transaksi.barangDibeli[i].harga << endl;
        }
        fileTransaksi << "Total " << transaksi.totalHarga << endl;
    }
    fileTransaksi.close();
}

void muatData() {
    ifstream fileInventaris("inventaris.txt");
    Barang barang;
    while (fileInventaris >> barang.kode >> barang.nama >> barang.harga >> barang.stok) {
        inventaris.push_back(barang);
    }
    fileInventaris.close();

    ifstream fileTransaksi("transaksi.txt");
    Transaksi transaksi;
    string kode;
    int jumlah;
    double harga;
    while (fileTransaksi >> kode >> jumlah >> harga) {
        if (kode == "Total") {
            transaksi.totalHarga = jumlah;  // jumlah disini adalah total harga
            riwayatTransaksi.push_back(transaksi);
            transaksi = Transaksi();  // reset transaksi
        } else {
            Barang barang;
            for (const auto& b : inventaris) {
                if (b.kode == kode) {
                    barang = b;
                    break;
                }
            }
            transaksi.barangDibeli.push_back(barang);
            transaksi.jumlah.push_back(jumlah);
            transaksi.totalHarga += harga * jumlah;
        }
    }
    fileTransaksi.close();
}

int main() {
    muatData();

    int pilihan;
    do {
        cout << "=== Aplikasi Penjualan ===" << endl;
        cout << "1. Tambah Barang Baru" << endl;
        cout << "2. Tampilkan Inventaris" << endl;
        cout << "3. Cari Barang" << endl;
        cout << "4. Catat Transaksi" << endl;
        cout << "5. Terima Pembayaran" << endl;
        cout << "6. Cetak Struk" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilkanInventaris();
                break;
            case 3:
                cariBarang();
                break;
            case 4:
                catatTransaksi();
                break;
            case 5:
                terimaPembayaran();
                break;
            case 6:
                cetakStruk();
                break;
            case 7:
                simpanData();
                cout << "Terima kasih telah menggunakan aplikasi ini." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 7);

    return 0;
}
