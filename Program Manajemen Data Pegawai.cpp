#include <iostream>
#include <string>

using namespace std;

const int MAX_PEGAWAI = 100;

struct Pegawai {
    string nama;
    int id;
    double gaji;
    string golongan;
    string kontak;
    bool menikah;
    int jumlahAnak;
};

Pegawai daftarPegawai[MAX_PEGAWAI];
int jumlahPegawai = 0;

// Stack untuk menyimpan ID pegawai
const int MAX_STACK = 100;
int stack[MAX_STACK];
int top = -1;

// Deklarasi fungsi
double hitungGaji(const string& golongan);
void tambahPegawai();
void tampilkanSemuaPegawai();
void perbaruiInformasiPegawai();
void hapusPegawai();
void cariPegawai();
void urutkanPegawai();
void pushToStack(int id);
int popFromStack();

// Menghitung total gaji berdasarkan golongan, status menikah, dan jumlah anak
double hitungGaji(const string& golongan, bool menikah, int jumlahAnak) {
    double gajiPokok;

    if (golongan == "1") {
        gajiPokok = 5000000;
    } else if (golongan == "2") {
        gajiPokok = 4500000;
    } else if (golongan == "3") {
        gajiPokok = 4000000;
    } else if (golongan == "4") {
        gajiPokok = 3500000;
    } else if (golongan == "5") {
        gajiPokok = 3000000;
    } else {
        // Nilai default jika golongan tidak dikenali
        return 0;
    }

    // Menghitung tunjangan keluarga
    double tunjanganKeluarga = (menikah) ? 0.1 * gajiPokok : 0;

    // Menghitung tunjangan anak
    double tunjanganAnak = 0.05 * gajiPokok * jumlahAnak;

    // Menghitung total gaji
    double totalGaji = gajiPokok + tunjanganKeluarga + tunjanganAnak;

    return totalGaji;
}


// Implementasi fungsi untuk menambah pegawai
void tambahPegawai() {
    if (jumlahPegawai < MAX_PEGAWAI) {
        Pegawai pegawaiBaru;
        cout << "\nMasukkan Nama      : ";
        cin.ignore();
        getline(cin, pegawaiBaru.nama);
        cout << "Masukkan ID Pegawai: ";
        cin >> pegawaiBaru.id;
        cout << "Masukkan Golongan  : ";
        cin.ignore();
        getline(cin, pegawaiBaru.golongan);
        cout << "Masukkan Kontak    : ";
        getline(cin, pegawaiBaru.kontak);
        cout << "Status Menikah (1: Menikah, 0: Belum Menikah): ";
        cin >> pegawaiBaru.menikah;
        cout << "Jumlah Anak        : ";
        cin >> pegawaiBaru.jumlahAnak;

        // Menghitung total gaji menggunakan fungsi hitungGaji
        double totalGaji = hitungGaji(pegawaiBaru.golongan, pegawaiBaru.menikah, pegawaiBaru.jumlahAnak);

        // Menambahkan data ke dalam array
        daftarPegawai[jumlahPegawai++] = pegawaiBaru;

        // Menambahkan ID pegawai ke stack
        pushToStack(pegawaiBaru.id);

        // Menampilkan informasi pegawai
        cout << "\nPegawai berhasil ditambahkan." << endl;
        cout << "\nInformasi Pegawai: " << endl;
        cout << "ID: " << pegawaiBaru.id << "\tNama\t\t\t: " << pegawaiBaru.nama << endl;
       	cout << "\tTotal Gaji\t\t: " << totalGaji << endl;
		cout << "\tTunjangan Keluarga\t: " << (pegawaiBaru.menikah ? 0.1 * totalGaji : 0) << endl;
		cout << "\tTunjangan Anak\t\t: " << 0.05 * totalGaji * pegawaiBaru.jumlahAnak << endl;
        cout << "\tGolongan\t\t: " << pegawaiBaru.golongan << endl;
        cout << "\tKontak\t\t\t: " << pegawaiBaru.kontak << endl;
        cout << "\tMenikah\t\t\t: " << (pegawaiBaru.menikah ? "Ya" : "Tidak") << endl;
        cout << "\tJumlah Anak\t\t: " << pegawaiBaru.jumlahAnak << endl;
    } else {
        cout << "Maaf, sudah mencapai batas maksimal pegawai." << endl;
    }
}

// Implementasi fungsi untuk memperbarui informasi pegawai
void perbaruiInformasiPegawai() {
    if (jumlahPegawai > 0) {
        int idPegawai;
        cout << "\nMasukkan ID Pegawai yang akan diperbarui: ";
        cin >> idPegawai;

        for (int i = 0; i < jumlahPegawai; ++i) {
            if (daftarPegawai[i].id == idPegawai) {
                cout << "Nama Pegawai: ";
                cin.ignore();
                getline(cin, daftarPegawai[i].nama);

                // Menghitung total gaji menggunakan fungsi hitungGaji
                double totalGaji = hitungGaji(daftarPegawai[i].golongan, daftarPegawai[i].menikah, daftarPegawai[i].jumlahAnak);

                cout << "\nInformasi Pegawai berhasil diperbarui."<< endl;
                cout << "ID: " << daftarPegawai[i].id << "\tNama\t\t\t: " << daftarPegawai[i].nama << endl;
                cout << "\tTotal Gaji\t\t: " << totalGaji << endl;
                cout << "\tTunjangan Keluarga\t: " << (daftarPegawai[i].menikah ? 0.1 * totalGaji : 0) << endl;
                cout << "\tTunjangan Anak\t\t: " << 0.05 * totalGaji * daftarPegawai[i].jumlahAnak << endl;
                cout << "\tGolongan\t\t: " << daftarPegawai[i].golongan << endl;
                cout << "\tKontak\t\t\t: " << daftarPegawai[i].kontak << endl;
                cout << "\tMenikah\t\t\t: " << (daftarPegawai[i].menikah ? "Ya" : "Tidak") << endl;
                cout << "\tJumlah Anak\t\t: " << daftarPegawai[i].jumlahAnak << endl;

                return;
            }
        }

        cout << "ID Pegawai tidak ditemukan."<< endl;
    } else {
        cout << "Belum ada pegawai yang ditambahkan." << endl;
    }
}

// Implementasi fungsi untuk menampilkan semua pegawai
void tampilkanSemuaPegawai() {
    if (jumlahPegawai > 0) {
        cout << "\nDaftar Pegawai: " << endl;
        for (int i = 0; i < jumlahPegawai; ++i) {
            // Menghitung total gaji menggunakan fungsi hitungGaji
            double totalGaji = hitungGaji(daftarPegawai[i].golongan, daftarPegawai[i].menikah, daftarPegawai[i].jumlahAnak);

            cout << "\nID: " << daftarPegawai[i].id << "\tNama\t\t\t: " << daftarPegawai[i].nama << endl;
            cout << "\tTotal Gaji\t\t: " << totalGaji << endl;
			cout << "\tTunjangan Keluarga\t: " << (daftarPegawai[i].menikah ? 0.1 * totalGaji : 0) << endl;
			cout << "\tTunjangan Anak\t\t: " << 0.05 * totalGaji * daftarPegawai[i].jumlahAnak << endl;
            cout << "\tGolongan\t\t: " << daftarPegawai[i].golongan << endl;
            cout << "\tKontak\t\t\t: " << daftarPegawai[i].kontak << endl;
            cout << "\tMenikah\t\t\t: " << (daftarPegawai[i].menikah ? "Yes" : "No") << endl;
            cout << "\tJumlah Anak\t\t: " << daftarPegawai[i].jumlahAnak << endl;
        }
    } else {
        cout << "Belum ada pegawai yang ditambahkan." << endl;
    }
}


// Implementasi fungsi untuk menghapus pegawai
void hapusPegawai() {
    if (jumlahPegawai > 0) {
        int idPegawai;
        cout << "\nMasukkan ID Pegawai yang akan dihapus: ";
        cin >> idPegawai;

        for (int i = 0; i < jumlahPegawai; ++i) {
            if (daftarPegawai[i].id == idPegawai) {
                // Geser elemen-elemen setelah posisi pegawai yang dihapus
                for (int j = i; j < jumlahPegawai - 1; ++j) {
                    daftarPegawai[j] = daftarPegawai[j + 1];
                }

                --jumlahPegawai;
                popFromStack(); // Hapus ID pegawai dari stack
                cout << "Pegawai berhasil dihapus." << endl;
                return;
            }
        }

        cout << "ID Pegawai tidak ditemukan." << endl;
    } else {
        cout << "\nBelum ada pegawai yang ditambahkan." << endl;
    }
}

// Implementasi fungsi untuk mencari pegawai berdasarkan ID
void cariPegawai() {
    if (jumlahPegawai > 0) {
        int idPegawai;
        cout << "\nMasukkan ID Pegawai yang akan dicari: ";
        cin >> idPegawai;

        for (int i = 0; i < jumlahPegawai; ++i) {
            if (daftarPegawai[i].id == idPegawai) {
                // Menghitung total gaji menggunakan fungsi hitungGaji
                double totalGaji = hitungGaji(daftarPegawai[i].golongan, daftarPegawai[i].menikah, daftarPegawai[i].jumlahAnak);

                cout << "Pegawai ditemukan:\n";
		        cout << "ID: " << daftarPegawai[i].id << "\tNama\t\t\t: " << daftarPegawai[i].nama << endl;
		        cout << "\tTotal Gaji\t\t: " << totalGaji << endl;
                cout << "\tTunjangan Keluarga\t: " << (daftarPegawai[i].menikah ? 0.1 * totalGaji : 0) << endl;
                cout << "\tTunjangan Anak\t\t: " << 0.05 * totalGaji * daftarPegawai[i].jumlahAnak << endl;
		        cout << "\tGolongan\t\t: " << daftarPegawai[i].golongan << endl;
		        cout << "\tKontak\t\t\t: " << daftarPegawai[i].kontak << endl;
		        cout << "\tMenikah\t\t\t: " << (daftarPegawai[i].menikah ? "Yes" : "No") << endl;
		        cout << "\tJumlah Anak\t\t: " << daftarPegawai[i].jumlahAnak << endl;
                return;
            }
        }

        cout << "\nID Pegawai tidak ditemukan." << endl;
    } else {
        cout << "\nBelum ada pegawai yang ditambahkan." << endl;
    }
}


// Implementasi fungsi untuk mengurutkan pegawai berdasarkan ID
void urutkanPegawai() {
    if (jumlahPegawai > 0) {
        // Menggunakan bubble sort untuk tujuan demonstrasi
        for (int i = 0; i < jumlahPegawai - 1; ++i) {
            for (int j = 0; j < jumlahPegawai - i - 1; ++j) {
                if (daftarPegawai[j].id > daftarPegawai[j + 1].id) {
                    swap(daftarPegawai[j], daftarPegawai[j + 1]);
                }
            }
        }

        cout << "\nPegawai berhasil diurutkan berdasarkan ID." << endl;
        
        // Menampilkan informasi pegawai setelah diurutkan
        cout << "\nDaftar Pegawai Setelah Diurutkan: " << endl;
        for (int i = 0; i < jumlahPegawai; ++i) {
            double totalGaji = hitungGaji(daftarPegawai[i].golongan, daftarPegawai[i].menikah, daftarPegawai[i].jumlahAnak);

            cout << "\nID: " << daftarPegawai[i].id << "\tNama\t\t\t: " << daftarPegawai[i].nama << endl;
            cout << "\tTotal Gaji\t\t: " << totalGaji << endl;
            cout << "\tTunjangan Keluarga\t: " << (daftarPegawai[i].menikah ? 0.1 * totalGaji : 0) << endl;
            cout << "\tTunjangan Keluarga\t\t: " << 0.05 * totalGaji * daftarPegawai[i].jumlahAnak << endl;
            cout << "\tGolongan\t\t: " << daftarPegawai[i].golongan << endl;
            cout << "\tKontak\t\t\t: " << daftarPegawai[i].kontak << endl;
            cout << "\tMenikah\t\t\t: " << (daftarPegawai[i].menikah ? "Yes" : "No") << endl;
            cout << "\tJumlah Anak\t\t: " << daftarPegawai[i].jumlahAnak << endl;
    }
    } else {
        cout << "\nBelum ada pegawai yang ditambahkan." << endl;
    }
}

// Implementasi fungsi untuk menambahkan ID pegawai ke stack
void pushToStack(int id) {
    if (top < MAX_STACK - 1) {
        stack[++top] = id;
    } else {
        cout << "Stack penuh. Tidak dapat menambahkan ID." << endl;
    }
}

// Implementasi fungsi untuk menghapus ID pegawai dari stack
int popFromStack() {
    if (top >= 0) {
        return stack[top--];
    } else {
        cout << "Stack kosong." << endl;
        return -1;
    }
}

int main() {
    int pilihan;

    do {
        // Tampilkan menu
        cout << "\nMenu:" << endl;
        cout << "1. Tambah Pegawai" << endl;
        cout << "2. Tampilkan Semua Pegawai" << endl;
        cout << "3. Perbarui Informasi Pegawai" << endl;
        cout << "4. Hapus Pegawai" << endl;
        cout << "5. Cari Pegawai" << endl;
        cout << "6. Urutkan Pegawai" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu (0-6): ";
        cin >> pilihan;

        // Proses pilihan menu
        switch (pilihan) {
            case 1:
                tambahPegawai();
                break;
            case 2:
                tampilkanSemuaPegawai();
                break;
            case 3:
                perbaruiInformasiPegawai();
                break;
            case 4:
                hapusPegawai();
                break;
            case 5:
                cariPegawai();
                break;
            case 6:
                urutkanPegawai();
                break;
            case 0:
                cout << "Program selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 0);

    return 0;
}

