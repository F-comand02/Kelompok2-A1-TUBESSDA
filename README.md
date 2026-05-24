# 🎮 Mobile Legends Matchmaking System Using Weighted Graph

<p align="center">
  <img src="https://img.shields.io/badge/C++-Project-blue?style=for-the-badge&logo=cplusplus">
  <img src="https://img.shields.io/badge/Graph-Weighted-red?style=for-the-badge">
  <img src="https://img.shields.io/badge/Algorithm-Dijkstra-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/Algorithm-Prim-orange?style=for-the-badge">
</p>

---

# 📌 Deskripsi Project

Project ini merupakan simulasi sistem matchmaking pada game Mobile Legends menggunakan konsep:

- Weighted Graph
- Adjacency List
- Priority Queue
- Dijkstra Algorithm
- Prim Algorithm

Program digunakan untuk mensimulasikan:

✅ Matchmaking terbaik  
✅ Team chemistry  
✅ Jalur koneksi optimal  
✅ Minimum Spanning Tree (MST)  
✅ Statistik matchmaking  
✅ Random matchmaking  

---

# 👨‍💻 Anggota Kelompok

| Nama | NIM |
|---|---|
| Farel Yamotaro Hia| 251402069 |
| Rodotua Naomi M. Simamora| 251402030 |
| Dian Indriani | 251402040 |
| Yazri Khoiri Matondang| 251402016 |
| Chynthia Rachel A. Hutabarat| 251402022 |

---

# 🧠 Konsep Struktur Data

Program menggunakan beberapa struktur data utama.

---

# 1️⃣ Struct Player

Digunakan untuk menyimpan data pemain.

```cpp
struct Player
{
    string id;
    string rank;
    double wr;

    vector<string> roles;
};
```

## Fungsi:
- Menyimpan ID player
- Rank player
- Win Rate
- Role hero

---

# 2️⃣ Struct Party

Digunakan untuk merepresentasikan:

- Solo
- Duo
- Trio

```cpp
struct Party
{
    string id;
    string type;

    int size;

    double avgStar;
    double avgWR;

    vector<string> rolePool;

    vector<Player> members;
};
```

## Fungsi:
- Menyimpan jenis party
- Menyimpan rata-rata rank
- Menyimpan rata-rata WR
- Menyimpan anggota party

---

# 3️⃣ Struct Edge

Digunakan untuk menyimpan hubungan antar node.

```cpp
struct Edge
{
    int to;
    double weight;
};
```

## Fungsi:
- Menyimpan node tujuan
- Menyimpan bobot hubungan matchmaking

---

# 4️⃣ Struct Team

Digunakan untuk menyimpan kandidat team hasil matchmaking.

```cpp
struct Team
{
    vector<int> parties;

    double score;
};
```

---

# 📊 Representasi Graph

Graph disimpan menggunakan:

```cpp
vector<vector<Edge>> graph;
```

Representasi ini disebut:

# Adjacency List

---

# 🎯 Algoritma Yang Digunakan

---

# 🔹 Dijkstra Algorithm

Digunakan untuk:

✅ mencari matchmaking terbaik  
✅ mencari jalur koneksi optimal  
✅ shortest path pada weighted graph  

## Struktur Data:
- Priority Queue
- Weighted Graph
- Adjacency List

## Kompleksitas:
```text
O((V + E) log V)
```

---

# 🔹 Prim Algorithm

Digunakan untuk:

✅ membangun team optimal  
✅ membentuk Minimum Spanning Tree (MST)  

## Kompleksitas:
```text
O(V²)
```

---

# 📌 Mengapa Menggunakan Prim?

Karena graph matchmaking yang digunakan sudah terhubung dan Prim lebih cocok untuk membangun koneksi team optimal pada weighted graph dibandingkan Kruskal.

---

# 📈 Rumus Matchmaking

## RankScore

```text
100 - |RankValueA - RankValueB|
```

---

## WRScore

```text
100 - 2|WRA - WRB|
```

---

## Weight

```text
0.75(RankScore)
+
0.25(WRScore)
```

---

# 🗺️ Node Matchmaking

| Node | Tipe |
|---|---|
| T1 | Trio |
| D1 | Duo |
| S1 | Solo |
| T2 | Trio |
| D2 | Duo |
| S2 | Solo |
| T3 | Trio |
| S3 | Solo |
| S4 | Solo |
| S5 | Solo |
| S6 | Solo |
| S7 | Solo |

Total:
```text
12 Node
```

---

# 📋 Data Party

| Node | Rank Avg | WR Avg | Role Pool |
|---|---|---|---|
| T1 | Mythic 20 | 58.0% | ALL ROLE |
| D1 | Mythic 22 | 59.5% | Gold, Mid, EXP, Roam |
| S1 | Mythic 23 | 61.0% | ALL ROLE |
| T2 | Mythic 11 | 56.3% | ALL ROLE |
| D2 | Mythic 8 | 54.5% | ALL ROLE |
| S2 | Mythic 18 | 56.0% | EXP, Roam, Mid |
| T3 | Mythic 10 | 54.3% | ALL ROLE |
| S3 | Mythic 16 | 53.0% | Gold, Mid, Roam |
| S4 | Mythic 21 | 57.0% | Jung, EXP, Mid, Roam |
| S5 | Mythic 22 | 60.0% | EXP, Gold, Mid, Roam |
| S6 | Legend 1 b5 | 56.0% | ALL ROLE |
| S7 | Mythic 20 | 58.0% | Jung, Gold, Mid |

---

# 🔗 Tabel Bobot Matchmaking

| Node A | Node B | Weight |
|---|---|---|
| T1 | T2 | 92.40 |
| T1 | S2 | 95.00 |
| T1 | S5 | 98.00 |
| T1 | S7 | 99.50 |
| D1 | S2 | 95.38 |
| D1 | S5 | 99.63 |
| D1 | T3 | 89.20 |
| T2 | D2 | 95.10 |
| T2 | S3 | 95.33 |
| T2 | S5 | 91.58 |
| T2 | S7 | 92.98 |
| D2 | S1 | 88.38 |
| D2 | S3 | 95.88 |
| D2 | S6 | 79.63 |
| D2 | S7 | 89.13 |
| T3 | S2 | 93.58 |
| T3 | S4 | 91.85 |
| T3 | S5 | 89.18 |
| T3 | S6 | 81.58 |
| S1 | S3 | 94.00 |
| S3 | S6 | 82.25 |
| S4 | S5 | 98.25 |
| S4 | S6 | 83.75 |
| S5 | S6 | 82.00 |

---

# ✨ Fitur Program

✅ Weighted Graph Matchmaking  
✅ Dijkstra Visualization  
✅ Prim (MST)  
✅ Random Matchmaking  
✅ Team Chemistry  
✅ Matchmaking Statistics  
✅ Console Color UI  
✅ Loading Animation  
✅ Real-Time Dijkstra Scanning  
✅ Adjacency List Representation  
✅ Priority Queue  
✅ Detail Party Information  

---

# 🖥️ Tampilan Menu

```text
====================================
 MOBILE LEGENDS MATCHMAKING
====================================

1. Tampilkan Graph
2. Detail Party
3. Cari Matchmaking Terbaik
4. Bentuk Team Optimal (Prim)
5. Random Matchmaking
6. Keluar
```

---

# ⚡ Contoh Output

```text
Searching Best Matchmaking.....

Scanning T1...
Scanning S5...
Scanning D1...

Rute Matchmaking:
T1
 -> S5
 -> D1

================================
TEAM MATCH STATISTICS
================================

Average Team WR : 92.38%
Team Chemistry : PERFECT
```

---

# 💾 Struktur Memori

Program menggunakan:

- Vector (Dynamic Array)
- Adjacency List
- Priority Queue

## Keuntungan:
✅ lebih hemat memori  
✅ fleksibel  
✅ cocok untuk sparse graph  

---

# 🔗 Hubungan Struktur Data dan Memory

Program menggunakan:

```cpp
vector<vector<Edge>> graph;
```

yang merupakan kombinasi:
- Dynamic Array
- Konsep Linked List modern

Sehingga penggunaan memori lebih efisien dibanding adjacency matrix.

---

# 🛠️ Teknologi

- C++
- STL Vector
- STL Priority Queue
- Graph Theory
- Weighted Graph

---

# 🚀 Cara Menjalankan Program

## Compile

```bash
g++ main.cpp -o app
```

---

## Run

### Windows
```bash
app.exe
```

### Linux / Mac
```bash
./app
```

---

# 📚 Kesimpulan

Project ini mengimplementasikan konsep:

- weighted graph
- adjacency list
- shortest path
- minimum spanning tree
- priority queue

untuk mensimulasikan sistem matchmaking Mobile Legends secara lebih realistis dan optimal.

---

# ⭐ Credits

Project dibuat untuk memenuhi tugas:
## Struktur Data dan Algoritma

Universitas Sumatera Utara

---

# 🎮 Preview

```text
MATCH FOUND!

Team Synergy : 94.21%
Chemistry : PERFECT
```

---

# 📌 Repository

```text
https://github.com/username/mobile-legends-matchmaking](https://github.com/F-comand02/Kelompok2-A1-TUBESSDA
```
