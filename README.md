# **Bioskopku: a Cinema Ticket Booking Application Using C**

![C11 Badge](https://img.shields.io/badge/11-C?label=C&labelColor=blue&color=grey) ![CMAKE Badge](https://img.shields.io/badge/3.10-C?label=CMake&labelColor=green&color=grey)

Selamat datang di repositori resmi **Bioskopku**! Aplikasi ini dirancang khusus untuk menghadirkan solusi modern dalam pengelolaan sistem pemesanan tiket bioskop dengan pendekatan berbasis **Command Line Interface (CLI)**. Simpel, cepat, dan efisien!

## Deskripsi Singkat

**Bioskopku** menawarkan pengalaman interaktif yang memadukan fleksibilitas dan fitur mendalam untuk pengelolaan bioskop, terinspirasi dari sistem bioskop modern seperti **CGV** atau **XXI** namun lebih ringan dan ramah pengguna CLI. Dengan arsitektur modular dan dinamis, aplikasi ini mendukung kebutuhan operasional bioskop secara **real-time**.

> 🎯 **Kenapa Bioskopku?**
>
> -   **Ringan & Cepat**: Bekerja optimal di CLI dengan eksekusi responsif.
> -   **Modular & Fleksibel**: Semua data dapat diperbarui tanpa ribet.
> -   **User-Friendly**: Mudah digunakan bahkan untuk pemula.
> -   **Lengkap**: Dukungan multi-peran pengguna dengan fitur spesifik.

### Empat Peran Utama:

1. **Super Admin**: Mengelola data global seperti kota, bioskop, manager, dan laporan pendapatan.
2. **Manager**: Mengatur studio, film, jadwal tayang, petugas, dan laporan pendapatan bioskop tertentu.
3. **Petugas**: Melayani transaksi tiket dengan tampilan film, studio, dan jadwal.
4. **Konsumen**: Memesan tiket secara online dengan pemilihan kursi dan validasi real-time.

## Fitur Utama

### 🚀 **Manajemen Bioskop Lengkap**

-   Tambahkan kota dan bioskop baru secara terstruktur.
-   Kelola studio, film, dan jadwal tayang dengan validasi konflik waktu otomatis.
-   Atur manajer dan petugas untuk bioskop dengan akses kontrol berbasis peran.

### 🎬 **Sistem Pemesanan Tiket Modern**

-   Konsumen dapat **memesan tiket online** dengan memilih film, studio, jadwal, dan kursi.
-   Validasi real-time untuk memastikan ketersediaan kursi.
-   Dukungan untuk transaksi offline oleh petugas di bioskop.

### 📊 **Laporan Pendapatan yang Akurat**

-   Super Admin: Melihat pendapatan total dari semua bioskop.
-   Manager: Mengakses laporan pendapatan bioskop yang dikelola.
-   Laporan dapat difilter berdasarkan periode harian, bulanan, atau tahunan.

### 🛠 **Teknologi yang Efisien**

-   Data tersimpan dalam format **CSV**, mendukung pemrosesan cepat dan aman.
-   Desain modular menggunakan `struct` dan `enum` untuk memaksimalkan pengelolaan data.
-   Sistem navigasi berbasis keyboard untuk pengalaman pengguna yang lebih cepat.

> **Kelebihan Tambahan:**
>
> -   Penyimpanan otomatis jika file tidak tersedia.
> -   Jadwal tayang dapat diperbarui langsung oleh Manager.
> -   Kapasitas studio divalidasi secara otomatis.
> -   Dukungan multi-platform untuk Windows dan Linux.

---

## Instalasi

1. Klon repositori ini:
    ```bash
    git clone https://github.com/riefproject/TugasBesar-DDP.git
    ```
2. Masuk ke folder `build` dan jalankan:
    ```bash
    cmake --build .
    ```
3. Kembali ke folder `bin` dan jalankan aplikasi:
    ```bash
    ./TUBES
    ```

## Prasyarat

-   Compiler **GCC** dengan dukungan **C11** (contoh: MinGW, MSYS UCRT).
-   **CMake** versi minimal 3.10.
-   Sistem operasi Windows atau Linux.

## Teknologi

-   **Bahasa**: C
-   **Basis Data**: CSV
-   **Lingkungan**: GCC, CMake
-   **Arsitektur**: Modular dengan pemisahan logika berdasarkan peran pengguna.

## Kontributor

-   [**riefproject**](https://github.com/riefproject)
-   [**Farraskuy**](https://github.com/farraskuy)

Laporkan masalah atau berkontribusi melalui pull request.

---

🎉 **Bioskopku** dirancang untuk mendukung operasional bioskop dengan cepat, efisien, dan fleksibel. Rasakan pengalaman pengelolaan bioskop sederhana namun modern hari ini! 🚀
