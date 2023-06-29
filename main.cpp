#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cassert>
#include <getopt.h>
#include <cstring>

using namespace std;
int const SIDE_LEN = 9;
int const T_SIZE = 81;
int ans = 0;

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
    for (int i = 0; i < 9; i++) {
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

void generate_shudu_final_list_2(int shudu_final[][9][9], int num) {
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
                t -= 2;
                if (t < 0) {
                    printf("error\n");
                    assert(0);
                }
                continue;
            }
            shudu_final[pos][i][j] = num_used[i * SIDE_LEN + j] + 1;
            num_used[i * SIDE_LEN + j]++;
            if (!check_if_ok(shudu_final[pos], i, j)) {
                t--;
                continue;
            }
        }
        pos++;
        if (pos < num) copy_shudu(shudu_final[pos - 1], shudu_final[pos]);
        t--;
    }
}

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

void get_ans_num(int shudu_game[9][9]) {
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
            get_ans_num(shudu_game);
        }
    }
    shudu_game[x][y] = 0;
    return;
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

bool compare_shudu(int shudu_game1[9][9], int shudu_game2[9][9]) {
    for (int i = 0; i < SIDE_LEN; i++) {
        for (int j = 0; j < SIDE_LEN; j++) {
            if (shudu_game1[i][j] != shudu_game2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void test_time() {
    clock_t start, finish;
    double duration;
    start = clock();

    static int shudu[1000000][SIDE_LEN][SIDE_LEN];
    //static int shudu1[1000000][SIDE_LEN][SIDE_LEN];
    generate_shudu_final_list(shudu, 1000000);
    //generate_shudu_final_list_2(shudu1, 1000000);
    /* for (int i = 0; i < 1000000; i++) {
         if (!compare_shudu(shudu[i], shudu1[i])) {
             printf("wrong\n");
         }
     }*/
//    for(int i=0;i<10000;i++){
//        generate_shudu_final(shudu[i]);
//    }
    for (int i = 0; i < 10; i++) {
        print_shudu(shudu[i]);
    }
    cout << endl;
    for (int i = 1000000 - 1; i > 999990; i--) {
        print_shudu(shudu[i]);
    }
//    for (int i = 0; i < 1000000; i++) {
//        generate_shudu_final(shudu[i]);
//        for (int j = 1; j < 100; j++) {
//            copy_shudu(shudu[i], shudu[i+j*100]);
//        }
//    }
//    for (int i = 0; i < 10000; i++) {
//        static int shudu_game_copy[SIDE_LEN][SIDE_LEN];
//        do {
//            copy_shudu(shudu[i], shudu_game_copy);
//            generate_shudu_game(shudu_game_copy, 50, true);
//        } while (!check_ans_unique(shudu[i]));
//        copy_shudu(shudu_game_copy, shudu[i]);
//    }
    finish = clock();
    duration = (double) (finish - start) / CLOCKS_PER_SEC;
    cout << duration << endl;
}

int main(int argc, char *argv[]) {
    srand((unsigned) time(NULL));
    //handle args
    int option;
    int num_finals = 0, num_games = 0;
    char *read_path = NULL;
    int final_game_solve = 0;//1 for final, 2 for game, 3 for solve
    bool if_set_blank = false;
    int difficulty = 0;
    int blank_low = 20;
    int blank_high = 55;
    char low[5], high[5];
    bool if_unique = false;
    while ((option = getopt(argc, argv, "c:s:n:m:r:u")) != -1) {
        switch (option) {
            case 'c':
                num_finals = atoi(optarg);
                final_game_solve = 1;
                if (num_finals > 1000000) {
                    printf("num_finals should be less than 1000000\n");
                    assert(0);
                }
                if (num_finals < 1) {
                    printf("num_finals should be greater than 0\n");
                    assert(0);
                }
                break;
            case 's':
                read_path = optarg;
                final_game_solve = 3;
                break;
            case 'n':
                num_games = atoi(optarg);
                if (num_games > 10000) {
                    printf("num_games should be less than 10000\n");
                    assert(0);
                }
                if (num_games < 1) {
                    printf("num_games should be greater than 0\n");
                    assert(0);
                }
                final_game_solve = 2;
                break;
            case 'm':
                difficulty = atoi(optarg);
                if (difficulty < 1 || difficulty > 3) {
                    printf("difficulty should be 1-3\n");
                    assert(0);
                }
                if(difficulty==1){
                    blank_low = 20;
                    blank_high = 35;
                    if_unique = true;
                }
                if(difficulty==2){
                    blank_low = 36;
                    blank_high = 45;
                    if_unique = true;
                }
                if(difficulty==3){
                    blank_low = 46;
                    blank_high = 55;
                    if_unique = true;
                }
                break;
            case 'r':
                if (strlen(optarg) != 5) {
                    printf("wrong format\n");
                    assert(0);
                }
                if (optarg[2] != '~') {
                    printf("wrong format\n");
                    assert(0);
                }
                strncpy(low, optarg, 2);
                low[2] = '\0';
                strncpy(high, optarg + 3, 2);
                high[2] = '\0';
                blank_low = atoi(low);
                blank_high = atoi(high);
                if (blank_low > blank_high) {
                    int temp = blank_low;
                    blank_low = blank_high;
                    blank_high = temp;
                }
                if (blank_low < 20) {
                    printf("blanks too few\n");
                    assert(0);
                }
                if (blank_high > 55) {
                    printf("blanks too many\n");
                    assert(0);
                }
                if_set_blank = true;
                break;
            case 'u':
                if_unique = true;
                break;
        }
    }
    if (final_game_solve == 0) {
        printf("no mode option\n");
        assert(0);
    }
    if (final_game_solve != 2 && (difficulty != 0 ||  if_unique)) {
        printf("wrong option\n");
        assert(0);
    }
    if (final_game_solve == 1) {
        static int shudu[1000000][SIDE_LEN][SIDE_LEN];
        generate_shudu_final_list(shudu, num_finals);
        ofstream fout;
        fout.open("final.txt");
        for (int i = 0; i < num_finals; i++) {
            for (int j = 0; j < SIDE_LEN; j++) {
                for (int k = 0; k < SIDE_LEN; k++) {
                    fout << shudu[i][j][k] << " ";
                }
                fout << endl;
            }
            fout << endl;
        }
        fout << endl;
        fout.close();
        return 0;
    }
    if (final_game_solve == 2) {
        static int shudu[10000][SIDE_LEN][SIDE_LEN];
        static int shudu_game_copy[SIDE_LEN][SIDE_LEN];
        int space_num;
        for (int i = 0; i < num_games; i++) {
            space_num = rand() % (blank_high - blank_low + 1) + blank_low;
            generate_shudu_final(shudu[i]);
            copy_shudu(shudu[i], shudu_game_copy);
            generate_shudu_game(shudu_game_copy, space_num, if_unique);
            //generate_shudu_game(shudu[i], space_num, );
            if (if_unique) {
                while (!check_ans_unique(shudu_game_copy)) {
                    space_num = rand() % (blank_high - blank_low + 1) + blank_low;
                    copy_shudu(shudu[i], shudu_game_copy);
                    generate_shudu_game(shudu_game_copy, space_num, false);
                }
                copy_shudu(shudu_game_copy, shudu[i]);
                if(space_num>50){
                    cout<<"unique "<<space_num<<endl;
                }
            }
        }
        ofstream fout("game.txt");
        fout << num_games << endl;
        for (int i = 0; i < num_games; i++) {
            for (int j = 0; j < SIDE_LEN; j++) {
                for (int k = 0; k < SIDE_LEN; k++) {
                    fout << shudu[i][j][k] << " ";
                }
                fout << endl;
            }
            fout << endl;
        }
        fout << endl;
        fout.close();
        return 0;
    }
    if (final_game_solve == 3) {

        ifstream fin(read_path);
        if (!fin) {
            cout << "open file failed" << endl;
            assert(0);
        }
        fin >> num_games;
        if (num_games > 10000) {
            cout << "num_games should be less than 10000" << endl;
            assert(0);
        }
        ofstream fout("sudoku.txt");
        static int shudu[10000][SIDE_LEN][SIDE_LEN];
        for (int i = 0; i < num_games; i++) {
            for (int j = 0; j < SIDE_LEN; j++) {
                for (int k = 0; k < SIDE_LEN; k++) {
                    fin >> shudu[i][j][k];
                }
            }
        }
        for (int i = 0; i < num_games; i++) {
            solve_shudu_game(shudu[i]);
            for (int j = 0; j < SIDE_LEN; j++) {
                for (int k = 0; k < SIDE_LEN; k++) {
                    fout << shudu[i][j][k] << " ";
                }
                fout << endl;
            }
            fout << endl;
        }
        fout << endl;
        fout.close();
        fin.close();
    }

//    int **shudu = new int *[SIDE_LEN];
//    for (int i = 0; i < SIDE_LEN; i++) {
//        shudu[i] = new int[SIDE_LEN];
//    }
    //test_time();


//    generate_shudu_game(shudu, 50, false);
//    for (int i = 0; i < SIDE_LEN; i++) {
//        for (int j = 0; j < SIDE_LEN; j++) {
//            cout << shudu[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//    //get_ans_num(shudu);
//    //cout << ans << endl;
//    if (check_ans_unique(shudu)) {
//        cout << "ans unique" << endl;
//    } else {
//        cout << "ans not unique" << endl;
//    }
//    solve_shudu_game(shudu);
//    for (int i = 0; i < SIDE_LEN; i++) {
//        for (int j = 0; j < SIDE_LEN; j++) {
//            cout << shudu[i][j] << " ";
//        }
//        cout << endl;
//    }

}