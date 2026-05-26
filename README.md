# Sistem Manajemen & Routing Paket Logistik

Project ini adalah aplikasi console C++ berbasis in-memory untuk simulasi distribusi paket antar kota.

## Struktur Folder

```text
UTS/
|-- include/
|   |-- HistoryList.h
|   |-- Package.h
|   |-- PackageQueue.h
|   |-- RouteGraph.h
|   `-- LogisticsSystem.h
|-- src/
|   |-- HistoryList.cpp
|   |-- Package.cpp
|   |-- PackageQueue.cpp
|   |-- RouteGraph.cpp
|   `-- LogisticsSystem.cpp
|-- main.cpp
`-- README.md
```

## Cara Compile

```bash
g++ main.cpp src/*.cpp -Iinclude -o logistic_app
```

Jalankan:

```bash
./logistic_app
```

Di Windows PowerShell:

```powershell
.\logistic_app.exe
```

## Flow Program

1. User registrasi paket dengan nomor resi, kota asal, dan kota tujuan.
2. Paket dibuat menggunakan `new`, lalu disimpan di linked list data paket.
3. Paket dimasukkan ke queue hub kota asal.
4. Saat dispatch, sistem mengambil paket paling depan dari queue kota tersebut.
5. Graph mencari kota berikutnya dari posisi paket menuju kota tujuan.
6. Paket dipindahkan ke kota berikutnya dan histori perjalanan ditambah ke linked list histori.
7. User dapat melacak resi untuk melihat traversal histori paket.

## Struktur Data

### Queue Linked List

File: `PackageQueue.h` dan `PackageQueue.cpp`

Queue menggunakan node:

```cpp
struct QueueNode {
    Package* package;
    QueueNode* next;
};
```

Operasi:

- `enqueue`: tambah paket ke belakang antrean.
- `dequeue`: ambil paket dari depan antrean.
- `display`: traversal antrean dari depan ke belakang.

### Directed Graph Adjacency List

File: `RouteGraph.h` dan `RouteGraph.cpp`

Graph menggunakan node kota dan linked list edge:

```cpp
struct CityNode {
    std::string cityName;
    EdgeNode* firstEdge;
    CityNode* next;
};
```

Setiap edge menyimpan kota tujuan dan jarak.

Contoh:

```text
Jakarta -> Bandung (150 km)
```

### Linked List Histori

File: `HistoryList.h` dan `HistoryList.cpp`

Setiap paket memiliki linked list histori sendiri:

```cpp
struct HistoryNode {
    std::string cityName;
    HistoryNode* next;
};
```

Saat paket berpindah kota, kota baru ditambahkan ke akhir histori.

## Desain Class

- `Package`: menyimpan data paket, status, posisi sekarang, dan histori.
- `HistoryList`: linked list perjalanan paket.
- `PackageQueue`: queue FIFO untuk hub/kota.
- `RouteGraph`: directed graph adjacency list untuk rute antar kota.
- `LogisticsSystem`: service utama yang menghubungkan semua struktur data.

## Graph Default

```text
Jakarta -> Bandung (150 km)
Jakarta -> Semarang (450 km)
Bandung -> Yogyakarta (390 km)
Semarang -> Surabaya (350 km)
Yogyakarta -> Surabaya (330 km)
Surabaya -> Denpasar (430 km)
Bandung -> Cirebon (130 km)
Cirebon -> Semarang (240 km)
```

## Kompleksitas Big O

| Operasi | Kompleksitas | Keterangan |
| --- | --- | --- |
| Enqueue paket | O(1) | Karena queue menyimpan pointer `rear`. |
| Dequeue paket | O(1) | Karena queue menyimpan pointer `front`. |
| Tampilkan queue | O(n) | Traversal semua node antrean. |
| Tambah histori | O(1) | Karena linked list histori menyimpan pointer `tail`. |
| Tampilkan histori | O(h) | Traversal semua node histori. |
| Tambah kota graph | O(V) | Cek apakah kota sudah ada. |
| Tambah edge graph | O(V + E_kota) | Cari kota asal, lalu tambah edge di akhir adjacency list. |
| Cari paket berdasarkan resi | O(p) | Traversal linked list data paket. |
| Cari kota berikutnya | O(V + E) | DFS pada adjacency list untuk memastikan tujuan dapat dicapai. |

Keterangan:

- `n`: jumlah paket dalam satu queue.
- `h`: jumlah histori perjalanan satu paket.
- `V`: jumlah kota.
- `E`: jumlah rute.
- `p`: jumlah paket terdaftar.

## Contoh Output Terminal

```text
=== Sistem Manajemen & Routing Paket Logistik ===
1. Registrasi paket
2. Dispatch paket
3. Lacak resi
4. Tampilkan antrean semua hub
5. Tampilkan graph rute
0. Keluar
Pilih menu: 1
Masukkan nomor resi   : JKT001
Masukkan kota asal    : Jakarta
Masukkan kota tujuan  : Denpasar
Paket berhasil diregistrasi dan masuk antrean Jakarta.

Pilih menu: 2
Dispatch dari kota: Jakarta
Paket JKT001 dikirim dari Jakarta ke Bandung (150 km).

Pilih menu: 3
Masukkan nomor resi: JKT001
Nomor resi     : JKT001
Kota asal      : Jakarta
Kota tujuan    : Denpasar
Posisi saat ini: Bandung
Status         : Dalam perjalanan
Histori perjalanan:
1. Jakarta
2. Bandung
```

## Catatan Memory Management

- Semua node dibuat dengan `new`.
- Destructor menghapus node queue, node histori, node graph, dan data paket.
- Queue hanya menyimpan pointer ke paket, sedangkan linked list record paket yang bertanggung jawab menghapus objek paket.
- Tidak ada database, framework, atau file eksternal.
