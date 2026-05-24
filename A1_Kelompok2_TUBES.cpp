// Code Kelompok 2 sistem matchmaking game dengan graph
// Implementasi Kode
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <thread>
#include <chrono>
#include <windows.h>
#include <ctime>
#include <cmath>

using namespace std;

const double INF = 999999;

// Struktur data player

struct Player
{
    string id;
    string rank;
    double wr;

    vector<string> roles;
};

// Struktur data party

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



struct Edge
{
    int to;
    double weight;
};


struct Team
{
    vector<int> parties;

    double score;
};


void loading(string text)
{
    cout << "\n" << text;

    for(int i=0; i<5; i++)
    {
        cout << ".";
        Sleep(400);
    }

    cout << endl;
}
class MatchmakingGraph {

private:

    int V;

    vector<vector<Edge>> graph;

    vector<Party> parties;
    vector<Team> validTeams;
    

public:

    MatchmakingGraph(int V)
    {
        this->V = V;

        graph.resize(V);
    }


    void addParty(Party p)
    {
        parties.push_back(p);
    }


    void addEdge(int u, int v, double weight)
    {
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }

    void tampilParty()
    {
        cout << "\nLIST PARTY\n";

        for(int i=0; i<parties.size(); i++)
        {
            cout << i
                 << ". "
                 << parties[i].id
                 << " | "
                 << parties[i].type
                 << " | Avg WR : "
                 << fixed << setprecision(2)
                 << parties[i].avgWR
                 << "%"
                 << endl;
        }
    }


    void detailParty()
    {
        cout << "\nPARTY DETAIL\n";

        for(auto p : parties)
        {
            cout << "\n====================================";
            cout << "\nParty : " << p.id;
            cout << "\nType  : " << p.type;
            cout << "\nAvg WR: " << p.avgWR << "%";

            cout << "\n\nMembers:\n";

            for(auto m : p.members)
            {
                cout << "- "
                     << m.id
                     << " | "
                     << m.rank
                     << " | WR "
                     << m.wr
                     << "%\n";
            }
        }
    }


    void tampilGraph()
    {
        cout << "\nGRAPH MATCHMAKING\n";

        for(int i=0; i<V; i++)
        {
            cout << "\n[" << parties[i].id << "]\n";

            for(auto edge : graph[i])
            {
                cout << " -> "
                     << parties[edge.to].id
                     << " | Weight : "
                     << edge.weight
                     << endl;
            }
        }
    }


    void teamOptimal()
    {
        loading("Membangun koneksi matchmaking optimal");

        vector<double> key(V, INF);

        vector<bool> mst(V, false);

        vector<int> parent(V, -1);

        key[0] = 0;

        double totalCompatibility = 0;

        for(int count=0; count<V-1; count++)
        {
            int u = -1;

            for(int i=0; i<V; i++)
            {
                if(!mst[i] &&
                (u==-1 || key[i] < key[u]))
                {
                    u = i;
                }
            }

            cout << "\nMenghubungkan "
                << parties[u].id
                << "...";

            Sleep(500);

            mst[u] = true;

            for(auto edge : graph[u])
            {
                int v = edge.to;

                // penalty cost
                double penalty = 100 - edge.weight;

                if(!mst[v] && penalty < key[v])
                {
                    key[v] = penalty;

                    parent[v] = u;
                }
            }
        }

        cout << "\n\n================================";
        cout << "\n KONEKSI MATCHMAKING OPTIMAL";
        cout << "\n================================\n";

        for(int i=1; i<V; i++)
        {
            double compatibility =
                100 - key[i];

            double penalty =
                key[i];

            totalCompatibility += compatibility;

            cout << "\n"
                << parties[parent[i]].id
                << " <--> "
                << parties[i].id;

            cout << "\nCompatibility : "
                << fixed << setprecision(2)
                << compatibility
                << "%";

            cout << "\nPenalty Cost : "
                << penalty;

            cout << "\n--------------------------------";
        }

        cout << "\n\nTOTAL GRAPH COMPATIBILITY : "
            << fixed << setprecision(2)
            << totalCompatibility;

        double avgCompatibility =
            totalCompatibility / (V - 1);

        cout << "\nAVERAGE COMPATIBILITY : "
            << avgCompatibility
            << "%";

        if(avgCompatibility >= 95)
            cout << "\nGRAPH CHEMISTRY : PERFECT\n";

        else if(avgCompatibility >= 85)
            cout << "\nGRAPH CHEMISTRY : HIGH\n";

        else
            cout << "\nGRAPH CHEMISTRY : NORMAL\n";
    }


    void dfsTeam(
        int index,
        vector<int>& current,
        int totalPlayer,
        double totalScore
    )
    {
        
        if(totalPlayer == 5)
        {
            Team t;

            t.parties = current;

            t.score = totalScore;

            validTeams.push_back(t);

            return;
        }

        
        if(totalPlayer > 5 || index >= V)
        {
            return;
        }

        
        current.push_back(index);

        dfsTeam(
            index + 1,
            current,
            totalPlayer + parties[index].size,
            totalScore + parties[index].avgWR
        );

        current.pop_back();

        
        dfsTeam(
            index + 1,
            current,
            totalPlayer,
            totalScore
        );
    }


    void matchmaking5v5()
    {
        loading("Membentuk balanced matchmaking 5 VS 5");

        validTeams.clear();

        vector<int> current;

        dfsTeam(0, current, 0, 0);

        if(validTeams.size() < 2)
        {
            cout << "\nTidak cukup team valid!\n";
            return;
        }

        double bestDiff = INF;

        Team bestA;
        Team bestB;


        for(int i=0; i<validTeams.size(); i++)
        {
            for(int j=i+1; j<validTeams.size(); j++)
            {
                bool overlap = false;

                for(auto a : validTeams[i].parties)
                {
                    for(auto b : validTeams[j].parties)
                    {
                        if(a == b)
                        {
                            overlap = true;
                        }
                    }
                }

                if(overlap)
                    continue;

                double avgA =
                    validTeams[i].score /
                    validTeams[i].parties.size();

                double avgB =
                    validTeams[j].score /
                    validTeams[j].parties.size();

                double diff =
                    fabs(avgA - avgB);

                if(diff < bestDiff)
                {
                    bestDiff = diff;

                    bestA = validTeams[i];

                    bestB = validTeams[j];
                }
            }
        }

       

        cout << "\n================================";
        cout << "\n MATCHMAKING....................";
        cout << "\n================================";


        cout << "\n\nTEAM A\n";

        int totalA = 0;

        double wrA = 0;

        for(auto idx : bestA.parties)
        {
            cout << "- "
                << parties[idx].id
                << " ("
                << parties[idx].size
                << " Player)\n";

            totalA += parties[idx].size;

            wrA += parties[idx].avgWR;
        }

        wrA /= bestA.parties.size();


        cout << "\nTEAM B\n";

        int totalB = 0;

        double wrB = 0;

        for(auto idx : bestB.parties)
        {
            cout << "- "
                << parties[idx].id
                << " ("
                << parties[idx].size
                << " Player)\n";

            totalB += parties[idx].size;

            wrB += parties[idx].avgWR;
        }

        wrB /= bestB.parties.size();


        cout << "\n================================";

        cout << "\nSTATISTIK MATCHMAKING";

        cout << "\n================================";

        cout << "\n\nTEAM A";

        cout << "\nTotal Player : "
            << totalA;

        cout << "\nAverage WR : "
            << fixed << setprecision(2)
            << wrA
            << "%";

        cout << "\n\nTEAM B";

        cout << "\nTotal Player : "
            << totalB;

        cout << "\nAverage WR : "
            << fixed << setprecision(2)
            << wrB
            << "%";

        cout << "\n\nWR Difference : "
            << bestDiff
            << "%";


        cout << "\n\nMATCH BALANCE : ";

        if(bestDiff <= 1)
            cout << "PERFECT";

        else if(bestDiff <= 3)
            cout << "HIGH";

        else
            cout << "NORMAL";

        cout << "\n\nMATCH FOUND!\n";
    }
    };


int main()
{
    system("color 0D");
    MatchmakingGraph g(12);

    Player P1 = {"P1", "Mythic 20", 58, {"Jung","EXP","Roam"}};
    Player P2 = {"P2", "Mythic 21", 57, {"EXP","Roam","Mid"}};
    Player P3 = {"P3", "Mythic 19", 59, {"Roam","Mid","Gold"}};

    Player P4 = {"P4", "Mythic 22", 60, {"Gold","Mid","EXP"}};
    Player P5 = {"P5", "Mythic 21", 59, {"Mid","Gold","Roam","EXP"}};

    Player P6 = {"P6", "Mythic 23", 61, {"ALL ROLE"}};

    Player P7 = {"P7", "Mythic 17", 55, {"Jung","Mid"}};
    Player P8 = {"P8", "Mythic 18", 56, {"EXP","Gold","Roam"}};
    Player P9 = {"P9", "Legend 1 b4", 58, {"Roam","Gold","Mid"}};

    Player P10 = {"P10", "Mythic 18", 54, {"Jung","EXP","Mid"}};
    Player P11 = {"P11", "Legend 1 b2", 55, {"Roam","Mid","Gold"}};

    Player P12 = {"P12", "Mythic 18", 56, {"EXP","Roam","Mid"}};

    Player P13 = {"P13", "Mythic 17", 54, {"Jung","EXP"}};
    Player P14 = {"P14", "Mythic 18", 55, {"EXP","Roam","Gold"}};
    Player P15 = {"P15", "Legend 2 b5", 54, {"Mid","Gold","Roam"}};

    Player P16 = {"P16", "Mythic 16", 53, {"Gold","Mid","Roam"}};

    Player P17 = {"P17", "Mythic 21", 57, {"Jung","EXP","Mid","Roam"}};

    Player P18 = {"P18", "Mythic 22", 60, {"EXP","Gold","Mid","Roam"}};

    Player P19 = {"P19", "Legend 1 b5", 56, {"ALL ROLE"}};

    Player P20 = {"P20", "Mythic 20", 58, {"Jung","Gold","Mid"}};

    Party T1 = {"T1","Trio",3,20,58,{"ALL ROLE"},{P1,P2,P3}};
    Party D1 = {"D1","Duo",2,22,59.5,{"Gold","Mid","EXP","Roam"},{P4,P5}};
    Party S1 = {"S1","Solo",1,23,61,{"ALL ROLE"},{P6}};
    Party T2 = {"T2","Trio",3,11,56.3,{"ALL ROLE"},{P7,P8,P9}};
    Party D2 = {"D2","Duo",2,8,54.5,{"ALL ROLE"},{P10,P11}};
    Party S2 = {"S2","Solo",1,18,56,{"EXP","Roam","Mid"},{P12}};
    Party T3 = {"T3","Trio",3,10,54.3,{"ALL ROLE"},{P13,P14,P15}};
    Party S3 = {"S3","Solo",1,16,53,{"Gold","Mid","Roam"},{P16}};
    Party S4 = {"S4","Solo",1,21,57,{"Jung","EXP","Mid","Roam"},{P17}};
    Party S5 = {"S5","Solo",1,22,60,{"EXP","Gold","Mid","Roam"},{P18}};
    Party S6 = {"S6","Solo",1,0,56,{"ALL ROLE"},{P19}};
    Party S7 = {"S7","Solo",1,20,58,{"Jung","Gold","Mid"},{P20}};

    g.addParty(T1);
    g.addParty(D1);
    g.addParty(S1);
    g.addParty(T2);
    g.addParty(D2);
    g.addParty(S2);
    g.addParty(T3);
    g.addParty(S3);
    g.addParty(S4);
    g.addParty(S5);
    g.addParty(S6);
    g.addParty(S7);

    g.addEdge(0,3,92.40);
    g.addEdge(0,5,95.00);
    g.addEdge(0,9,98.00);
    g.addEdge(0,6,99.50);
    g.addEdge(1,5,95.38);
    g.addEdge(1,9,99.63);
    g.addEdge(1,6,89.20);
    g.addEdge(3,4,95.10);
    g.addEdge(3,7,95.33);
    g.addEdge(3,9,91.58);
    g.addEdge(3,6,92.98);
    g.addEdge(4,2,88.38);
    g.addEdge(4,7,95.88);
    g.addEdge(4,8,79.63);
    g.addEdge(4,6,89.13);
    g.addEdge(6,5,93.58);
    g.addEdge(6,8,91.85);
    g.addEdge(6,9,89.18);
    g.addEdge(8,9,98.25);
    g.addEdge(8,7,83.75);
    g.addEdge(2,7,94.00);
    g.addEdge(4,10,79.63); 
    g.addEdge(4,11,89.13); 
    g.addEdge(6,10,81.58);
    g.addEdge(7,10,82.25); 
    g.addEdge(8,10,83.75); 
    g.addEdge(9,10,82.00); 
    g.addEdge(0,11,99.50); 
    g.addEdge(3,11,92.98); 

    int pilih;

    do {

        cout << "\n====================================";
        cout << "\n MATCHMAKING MOBILE LEGENDS.........";
        cout << "\n====================================";

        cout << "\n1. Tampilkan Graph";
        cout << "\n2. Detail Party";
        cout << "\n3. Bentuk Team Optimal (Prim)";
        cout << "\n4. Matchmaking 5 VS 5";
        cout << "\n5. Keluar";

        cout << "\n\nPilihan : ";
        cin >> pilih;

        switch(pilih)
        {
        case 1:

            g.tampilGraph();

            break;

        case 2:

            g.detailParty();

            break;

        

        case 3:

            g.teamOptimal();

            break;

        case 4:

            g.matchmaking5v5();

            break;

        case 5:

            cout << "\nProgram selesai...\n";

            break;

        default:

            cout << "\nPilihan tidak valid!\n";
        }

    } while(pilih != 5);

    return 0;
}