#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cassert>
#include <getopt.h>
#include <cstring>
#include "sudoku.h"
using namespace std;
void copy_shudu(int shudu_game[9][9], int shudu_game_copy[9][9]) {
    for (int i = 0; i < SIDE_LEN; i++) {
        for (int j = 0; j < SIDE_LEN; j++) {
            shudu_game_copy[i][j] = shudu_game[i][j];
        }
    }
}

bool row[10][9];
bool col[10][9];
bool block[10][9];

bool check_if_ok(int shudu_final[9][9], int x, int y) {
    int i, j;
    for (i = 0; i < SIDE_LEN; i++) {
        if (i != x && shudu_final[i][y] == shudu_final[x][y]) {
            return false;
        }
    }
    for (j = 0; j < SIDE_LEN; j++) {
        if (j != y && shudu_final[x][j] == shudu_final[x][y]) {
            return false;
        }
    }
    int i_start = x / 3 * 3;
    int j_start = y / 3 * 3;
    for (i = i_start; i < i_start + 3; i++) {
        for (j = j_start; j < j_start + 3; j++) {
            if (i != x && j != y && shudu_final[i][j] == shudu_final[x][y]) {
                return false;
            }
        }
    }
    return true;
}

int get_random_num() {
    return rand() % 9 + 1;
}
void clean_shudu(int shudu_final[9][9]) {
    for (int i = 0; i < SIDE_LEN; i++) {
        for (int j = 0; j < SIDE_LEN; j++) {
            shudu_final[i][j] = 0;
        }
    }
}
void generate_shudu_final(int shudu_final[9][9]) {
    static set<int> num_used[T_SIZE];
    for (int i = 0; i < T_SIZE; i++) {
        num_used[i].clear();
    }
    int i, j, t;
    int iter = 0;
    for (t = 0; t < T_SIZE; t++) {
        iter++;
        i = t / SIDE_LEN;
        j = t % SIDE_LEN;
        if (num_used[i * SIDE_LEN + j].size() == 9) {
            num_used[i * SIDE_LEN + j].clear();
            shudu_final[i][j] = 0;
            t -= 2;
            if (t < 0) {
                printf("error\n");
                assert(0);
            }
            continue;
        }
        shudu_final[i][j] = get_random_num();
        if (num_used[i * SIDE_LEN + j].find(shudu_final[i][j]) != num_used[i * SIDE_LEN + j].end()) {
            shudu_final[i][j] = 0;
            t--;
            continue;
        }
        num_used[i * SIDE_LEN + j].insert(shudu_final[i][j]);
        if (!check_if_ok(shudu_final, i, j)) {
            t--;
            continue;
        }

    }
    //printf("iter: %d\n", iter);

}

void generate_shudu_final_list(int shudu_final[][9][9], int num) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            row[i][j] = false;
            col[i][j] = false;
            block[i][j] = false;
        }
    }
    int pos = 0;
    static int num_used[T_SIZE];
    for (int i = 0; i < T_SIZE; i++) {
        num_used[i] = 0;
    }
    int i, j, t;
    int iter = 0;
    t = 0;
    while (pos < num) {
        for (; t < T_SIZE; t++) {
            iter++;
            i = t / SIDE_LEN;
            j = t % SIDE_LEN;
            if (num_used[i * SIDE_LEN + j] == 9) {
                num_used[i * SIDE_LEN + j] = 0;
                shudu_final[pos][i][j] = 0;
                int x = t - 1;
                int i0 = x / SIDE_LEN;
                int j0 = x % SIDE_LEN;
                int row0 = i0;
                int col0 = j0;
                int block0 = i0 / 3 * 3 + j0 / 3;
                row[shudu_final[pos][i0][j0]][row0] = false;
                col[shudu_final[pos][i0][j0]][col0] = false;
                block[shudu_final[pos][i0][j0]][block0] = false;
                t -= 2;
                continue;
            }
            int x = num_used[i * SIDE_LEN + j] + 1;
            shudu_final[pos][i][j] = x;
            num_used[i * SIDE_LEN + j]++;
            int row0 = i;
            int col0 = j;
            int block0 = i / 3 * 3 + j / 3;
            if (row[x][row0] || col[x][col0] || block[x][block0]) {
                t--;
                continue;
            }
            row[x][row0] = true;
            col[x][col0] = true;
            block[x][block0] = true;
//            if (row[]) {
//                t--;
//                continue;
//            }
        }
        pos++;
        if (pos < num) copy_shudu(shudu_final[pos - 1], shudu_final[pos]);
        //cout<<t;
        t = 68;
        for (int i = t + 1; i < T_SIZE; i++) num_used[i] = 0;
        for (int i = t; i < T_SIZE; i++) {
            int x = i / SIDE_LEN;
            int y = i % SIDE_LEN;
            shudu_final[pos][x][y] = 0;
            int row0 = x;
            int col0 = y;
            int block0 = x / 3 * 3 + y / 3;
            row[shudu_final[pos - 1][x][y]][row0] = false;
            col[shudu_final[pos - 1][x][y]][col0] = false;
            block[shudu_final[pos - 1][x][y]][block0] = false;
        }
//        t--;
//        row[shudu_final[pos][8][8]][8]=false;
//        col[shudu_final[pos][8][8]][8]=false;
//        block[shudu_final[pos][8][8]][8]=false;

    }
}

//void generate_shudu_final_list_2(int shudu_final[][9][9], int num) {
//    int pos = 0;
//    static int num_used[T_SIZE];
//    for (int i = 0; i < T_SIZE; i++) {
//        num_used[i] = 0;
//    }
//    int i, j, t;
//    int iter = 0;
//    t = 0;
//    while (pos < num) {
//        for (; t < T_SIZE; t++) {
//            iter++;
//            i = t / SIDE_LEN;
//            j = t % SIDE_LEN;
//            if (num_used[i * SIDE_LEN + j] == 9) {
//                num_used[i * SIDE_LEN + j] = 0;
//                shudu_final[pos][i][j] = 0;
//                t -= 2;
//                if (t < 0) {
//                    printf("error\n");
//                    assert(0);
//                }
//                continue;
//            }
//            shudu_final[pos][i][j] = num_used[i * SIDE_LEN + j] + 1;
//            num_used[i * SIDE_LEN + j]++;
//            if (!check_if_ok(shudu_final[pos], i, j)) {
//                t--;
//                continue;
//            }
//        }
//        pos++;
//        if (pos < num) copy_shudu(shudu_final[pos - 1], shudu_final[pos]);
//        t--;
//    }
//}

void generate_shudu_game(int shudu_game[9][9], int space_num, bool from_final) {
    if (!from_final)generate_shudu_final(shudu_game);
    assert(space_num <= 81 && space_num >= 0);
    set<int> space_set;
    for (int i = 0; i < space_num; i++) {
        int x, y;
        do {
            x = rand() % 9;
            y = rand() % 9;
        } while (space_set.find(x * 9 + y) != space_set.end());
        shudu_game[x][y] = 0;
        space_set.insert(x * 9 + y);
    }

}

bool solve_shudu_game(int shudu_game[9][9]) {
    int i, j;
    bool space_found = false;
    for (i = 0; i < SIDE_LEN; i++) {
        for (j = 0; j < SIDE_LEN; j++) {
            if (shudu_game[i][j] == 0) {
                space_found = true;
                break;
            }
        }
        if (space_found) {
            break;
        }
    }
    if (!space_found) {
        return true;

    }
    int x = i, y = j;

    for (int k = 1; k <= 9; k++) {
        shudu_game[x][y] = k;
        if (check_if_ok(shudu_game, x, y)) {
            bool exist = solve_shudu_game(shudu_game);
            if (exist) {
                return true;
            }
        }
    }
    shudu_game[x][y] = 0;
    return false;
}

void get_ans_num(int shudu_game[9][9],int &ans) {
    int i, j;
    bool space_found = false;
    for (i = 0; i < SIDE_LEN; i++) {
        for (j = 0; j < SIDE_LEN; j++) {
            if (shudu_game[i][j] == 0) {
                space_found = true;
                break;
            }
        }
        if (space_found) {
            break;
        }
    }
    if (!space_found) {
        ans++;
        return;
    }
    int x = i, y = j;
    bool exist = false;
    for (int k = 1; k <= 9; k++) {
        shudu_game[x][y] = k;
        if (check_if_ok(shudu_game, x, y)) {
            get_ans_num(shudu_game,ans);
        }
    }
    shudu_game[x][y] = 0;
    return;
}
int get_ans(int shudu_game[9][9]) {
    int ans=0;
    get_ans_num(shudu_game,ans);
    return ans;
}
bool solve_shudu_reverse(int shudu_game[9][9]) {
    int i, j;
    bool space_found = false;
    for (i = 0; i < SIDE_LEN; i++) {
        for (j = 0; j < SIDE_LEN; j++) {
            if (shudu_game[i][j] == 0) {
                space_found = true;
                break;
            }
        }
        if (space_found) {
            break;
        }
    }
    if (!space_found) {
        return true;
    }
    int x = i, y = j;
    for (int k = 9; k >= 1; k--) {
        shudu_game[x][y] = k;
        if (check_if_ok(shudu_game, x, y)) {
            bool exist = solve_shudu_reverse(shudu_game);
            if (exist) {
                return true;
            }
        }

    }
    shudu_game[x][y] = 0;
    return false;
}

bool check_ans_unique(int shudu_game[9][9]) {
    static int shudu1[SIDE_LEN][SIDE_LEN], shudu2[SIDE_LEN][SIDE_LEN];
    for (int i = 0; i < SIDE_LEN; i++) {
        for (int j = 0; j < SIDE_LEN; j++) {
            shudu1[i][j] = shudu_game[i][j];
            shudu2[i][j] = shudu_game[i][j];
        }
    }
    solve_shudu_game(shudu1);
    solve_shudu_reverse(shudu2);
    for (int i = 0; i < SIDE_LEN; i++) {
        for (int j = 0; j < SIDE_LEN; j++) {
            if (shudu2[i][j] != shudu1[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void print_shudu(int shudu_game[9][9]) {
    for (int i = 0; i < SIDE_LEN; i++) {
        for (int j = 0; j < SIDE_LEN; j++) {
            printf("%d ", shudu_game[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//bool compare_shudu(int shudu_game1[9][9], int shudu_game2[9][9]) {
//    for (int i = 0; i < SIDE_LEN; i++) {
//        for (int j = 0; j < SIDE_LEN; j++) {
//            if (shudu_game1[i][j] != shudu_game2[i][j]) {
//                return false;
//            }
//        }
//    }
//    return true;
//}

//void test_time() {
//    clock_t start, finish;
//    double duration;
//    start = clock();
//
//    static int shudu[1000000][SIDE_LEN][SIDE_LEN];
//    //static int shudu1[1000000][SIDE_LEN][SIDE_LEN];
//    generate_shudu_final_list(shudu, 1000000);
//    //generate_shudu_final_list_2(shudu1, 1000000);
//    /* for (int i = 0; i < 1000000; i++) {
//         if (!compare_shudu(shudu[i], shudu1[i])) {
//             printf("wrong\n");
//         }
//     }*/
////    for(int i=0;i<10000;i++){
////        generate_shudu_final(shudu[i]);
////    }
//    for (int i = 0; i < 10; i++) {
//        print_shudu(shudu[i]);
//    }
//    cout << endl;
//    for (int i = 1000000 - 1; i > 999990; i--) {
//        print_shudu(shudu[i]);
//    }
////    for (int i = 0; i < 1000000; i++) {
////        generate_shudu_final(shudu[i]);
////        for (int j = 1; j < 100; j++) {
////            copy_shudu(shudu[i], shudu[i+j*100]);
////        }
////    }
////    for (int i = 0; i < 10000; i++) {
////        static int shudu_game_copy[SIDE_LEN][SIDE_LEN];
////        do {
////            copy_shudu(shudu[i], shudu_game_copy);
////            generate_shudu_game(shudu_game_copy, 50, true);
////        } while (!check_ans_unique(shudu[i]));
////        copy_shudu(shudu_game_copy, shudu[i]);
////    }
//    finish = clock();
//    duration = (double) (finish - start) / CLOCKS_PER_SEC;
//    cout << duration << endl;
//}

