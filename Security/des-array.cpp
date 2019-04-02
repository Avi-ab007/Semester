#include <bits/stdc++.h>

#define ull unsigned long long int
using namespace std;

// string msg = "000000100100011010001010110011110001001101010111100110111101111";
// string key = "001001100110100010101110111100110011011101111001101111111110001";


int IP[][8] = 
{
    {58,   50,   42,   34,   26,  18,   10,   2},
    {60,   52,   44,   36,   28,  20,   12,   4},
    {62,   54,   46,   38,   30,  22,   14,   6},
    {64,   56,   48,   40,   32,  24,   16,   8},
    {57,   49,   41,   33,   25,  17,    9,   1},
    {59,   51,   43,   35,   27,  19,   11,   3},
    {61,   53,   45,   37,   29,  21,   13,   5},
    {63,   55,   47,   39,   31,  23,   15,   7}
};

int PC1[][7] =
{
    {57,  49,   41,  33,   25,   17,   9},
    {1,   58,   50,  42,   34,   26,  18},
    {10,   2,   59,  51,   43,   35,  27},
    {19,  11,    3,  60,   52,   44,  36},
    {63,  55,   47,  39,   31,   23,  15},
    {7,   62,   54,  46,   38,   30,  22},
    {14,   6,   61,  53,   45,   37,  29},
    {21,  13,    5,  28,   20,   12,   4}
};

int PC2[][6] = 
{
    {14,   17,  11,   24,    1,   5},
    {3,    28,  15,    6,   21,  10},
    {23,   19,  12,    4,   26,   8},
    {16,    7,  27,   20,   13,   2},
    {41,   52,  31,   37,   47,  55},
    {30,   40,  51,   45,   33,  48},
    {44,   49,  39,   56,   34,  53},
    {46,   42,  50,   36,   29,  32}
};

int E[][6] = 
{
    {32,   1,    2,    3,    4,   5},
    {4,    5,    6,    7,    8,   9},
    {8,    9,   10,   11,   12,  13},
    {12,   13,  14,   15,   16,  17},
    {16,   17,  18,   19,   20,  21},
    {20,   21,  22,   23,   24,  25},
    {24,   25,  26,   27,   28,  29},
    {28,   29,  30,   31,   32,   1}
};

int FP[][8] = 
{
    {40, 8, 48, 16, 56, 24, 64, 32},
    {39, 7, 47, 15, 55, 23, 63, 31},
    {38, 6, 46, 14, 54, 22, 62, 30},
    {37, 5, 45, 13, 53, 21, 61, 29},
    {36, 4, 44, 12, 52, 20, 60, 28},
    {35, 3, 43, 11, 51, 19, 59, 27},
    {34, 2, 42, 10, 50, 18, 58, 26},
    {33, 1, 41,  9, 49, 17, 57, 25}
};

int S[8][4][16] = {
    {
        {14,  4,  13,  1,   2, 15,  11,  8,   3, 10,   6, 12,   5,  9,   0,  7},
        {0, 15,  7, 4, 14, 2, 13, 1, 10, 6, 12, 11,  9,  5,   3,   8},
        {4,  1,  14,  8,  13,  6,   2, 11,  15, 12,   9,  7,  3, 10,   5,  0},
        {15, 12,   8,  2,   4,  9,   1,  7,   5, 11,   3, 14,  10,  0,   6, 13}
    },
    {
        {15,  1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0,  5, 10},
        {3, 13,  4, 7, 15, 2,  8, 14, 12, 0,  1, 10,  6, 9, 11, 5},
        {0, 14,  7, 11, 10, 4, 13, 1,  5, 8, 12, 6,  9, 3,  2, 15},
        {13, 8, 10, 1,  3, 15,  4, 2, 11, 6,  7, 12,  0, 5, 14, 9}
    },
    {
        {10, 0,  9, 14,  6, 3, 15, 5,  1, 13, 12, 7, 11, 4,  2, 8},
        {13, 7,  0, 9,  3, 4,  6, 10,  2, 8,  5, 14, 12, 11, 15, 1},
        {13, 6,  4, 9,  8, 15,  3, 0, 11, 1,  2, 12,  5, 10, 14, 7},
        {1, 10, 13, 0,  6, 9,  8, 7,  4, 15, 14, 3, 11, 5,  2, 12}
    },
    {
        {7, 13, 14, 3,  0, 6,  9, 10,  1, 2,  8, 5, 11, 12,  4, 15},
        {13, 8, 11, 5,  6, 15,  0, 3,  4, 7,  2, 12,  1, 10, 14, 9},
        {10, 6,  9, 0, 12, 11,  7, 13, 15, 1,  3, 14,  5, 2,  8, 4},
        {3, 15,  0, 6, 10, 1, 13, 8,  9, 4,  5, 11, 12, 7,  2, 14}
    },
    {
        {2, 12,  4, 1,  7, 10, 11, 6,  8, 5,  3, 15, 13, 0, 14, 9},
        {14, 11,  2, 12,  4, 7, 13, 1,  5, 0, 15, 10,  3, 9,  8, 6},
        {4, 2,  1, 11, 10, 13,  7, 8, 15, 9, 12, 5,  6, 3,  0, 14},
        {11, 8, 12, 7,  1, 14,  2, 13,  6, 15,  0, 9, 10, 4,  5, 3}
    },
    {
        {12, 1, 10, 15,  9, 2,  6, 8,  0, 13,  3, 4, 14, 7,  5, 11},
        {10, 15,  4, 2,  7, 12,  9, 5,  6, 1, 13, 14,  0, 11,  3, 8},
        {9, 14, 15, 5,  2, 8, 12, 3,  7, 0,  4, 10,  1, 13, 11, 6},
        {4, 3,  2, 12,  9, 5, 15, 10, 11, 14,  1, 7,  6, 0,  8, 13}
    },
    {
        {4, 11,  2, 14, 15, 0,  8, 13,  3, 12,  9, 7,  5, 10,  6, 1},
        {13, 0, 11, 7,  4, 9,  1, 10, 14, 3,  5, 12,  2, 15,  8, 6},
        {1, 4, 11, 13, 12, 3,  7, 14, 10, 15,  6, 8,  0, 5,  9, 2},
        {6, 11, 13, 8,  1, 4, 10, 7,  9, 5,  0, 15, 14, 2,  3, 12}
    },
    {
        {13, 2,  8, 4,  6, 15, 11, 1, 10, 9,  3, 14,  5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3,  7, 4, 12, 5,  6, 11,  0, 14,  9, 2},
        {7, 11,  4, 1,  9, 12, 14, 2,  0, 6, 10, 13, 15, 3,  5, 8},
        {2, 1, 14, 7,  4, 10,  8, 13, 15, 12,  9, 0,  3, 5,  6, 11}
    }
};

int P[][4] = 
{
    {16,  7, 20, 21},
    {29, 12, 28, 17},
    {1, 15, 23, 26},
    {5, 18, 31, 10},
    {2,  8, 24, 14},
    {32, 27,  3,  9},
    {19, 13, 30,  6},
    {22, 11,  4, 25}
};

int IP_1[][8] =
{
    {40,  8,  48,  16,   56,  24,   64,  32},
    {39,  7,  47,  15,   55,  23,   63,  31},
    {38,  6,  46,  14,   54,  22,   62,  30},
    {37,  5,  45,  13,   53,  21,   61,  29},
    {36,   4,  44,  12,  52, 20,  60, 28},
    {35,  3,  43,  11,  51, 19,  59, 27},
    {34,   2,  42,  10,  50, 18,  58, 26},
    {33,  1,  41,   9,  49, 17,  57, 25}
};

string leftShift(string a) {
    return (a.substr(1) + a[0]);
}

performXor(string &a, string &b) {

    for (int i = 0; i < a.length(); i++) {
        if (a[i] == b[i])
            a[i] = '0';
        else
            a[i] = '1';
    }
}

int bstoi(string bin) {

    int num = 0;
    for (int i = bin.length() - 1; i >= 0; i--) {
        num += bin[i]*pow(2, i);
    }
    return num;
}

string itobs(int num) {

    string bin = "";
    while (num != 0) {
        bin += ('0' + num%2);
        num /= 2;
    }
    reverse(bin.begin(), bin.end());
    return bin;
}

string initialPermutation(string msg) {

    int k = 0;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            msg[k++] = msg[IP[i][j] - 1];
        }
    }
    return msg;
}

string pc1_key(string key) {
    
    string pckey = "";
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 8; j++)
            pckey += key[PC1[i][j]];
    }

    return pckey;
}

string expansion(string ri) {

    string expRi = "";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; i++) {
            expRi += ri[E[i][j]];
        }
    }
    return expRi;
}

string pc2_key(string key) {
    
    string p2key = "";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++)
            p2key = key[PC2[i][j]];
    }
    return p2key;
} 

string subsBox(string ri) {

    string subri = "";
    for (int i = 0; i < 8; i++) {

        string tmp = ri.substr(6*i, 6*(i+1));
        string srow = "";
        srow += tmp[0];
        srow += tmp[5];
        string scol = tmp.substr(1,5);
        int row = bstoi(srow), col = stoi(scol);
        subri += itobs(S[i][row][col]);
    }

    return subri;
}

void permutation(string &ri) {
    
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++)
            ri[k++] = ri[P[i][j]];
    }
}

void computeRound(string &li, string &ri, string &ci, string &di) {

    ri = expansion(ri);
    ci = leftShift(ci);
    di = leftShift(di);
    ci += di;
    string ki = pc2_key(ci);

    performXor(ri, ki);

    ri = subsBox(ri);

    permutation(ri);
}

void finalSwap(string &text) {

    int k = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            text[k++] = text[FP[i][j]];
    }
}

void inverseIP(string &text) {

    int k = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            text[k++] = text[IP_1[i][j]];
    }
}

string encrypt(string msg, string key) {

    string text = initialPermutation(msg);
    string pkey = pc1_key(key);

    string Li = text.substr(0, 32), Ri = text.substr(32);

    string Ci = pkey.substr(0, 28), Di = pkey.substr(28);

    for (int i = 0; i < 16; i++) {
        string tmp = Ri;
        computeRound(Li, Ri, Ci, Di);
        performXor(Ri, Li);
        Li = tmp;
    }

    Li += Ri;

    cout<<Li<<endl;
    // finalSwap(Li);
    // inverseIP(Li);

    return Li;
}

int main() {

    string msg = "0000000100100011010001010110011110001001101010111100110111101111";
    string key = "0001001100110100010101110111100110011011101111001101111111110001";

    string cipher = encrypt(msg, key);

    cout<<cipher<<" "<<cipher.length();

    return 0;
}










//     int m_len = s_msg.length();
//     ull msg = 0;
//     for (int i = 0; i < m_len ; i++) {
//         int pos = m_len - i - 1;
//         ull mask = 1<<pos;
//         if (s_msg[i] == '1')
//             msg |= mask;
//         mask >>= 1;
//     }
//     cout<<"Binary1 = "<<s_msg<<endl;
//     cout<<"Binary2 = ";
//     for(int i=63;i>=0;i--)
//     {
//         ull mask = 1<<i;
//         if(mask&msg) cout<<"1";
//         else cout<<"0";
//     }
//     cout<<endl;