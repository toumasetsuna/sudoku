//
// Created by 86138 on 2023/6/30.
//
#include <iostream>
#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cassert>
#include <getopt.h>
#include <cstring>
#define TEST
using namespace std;
int start(int argc, char* argv[]){
    srand((unsigned) time(NULL));
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }
    int option;
    int num_finals = 0, num_games = 0;
    char *read_path = NULL;
    int final_game_solve = 0;//1 for final, 2 for game, 3 for solve
    int difficulty = 0;
    int blank_low = 20;
    int blank_high = 55;
    char low[5], high[5];
    optind = 1;
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
#ifdef TEST
        for(int i=0;i<1000000;i++){
            for(int j=0;j<SIDE_LEN;j++){
                for(int k=0;k<SIDE_LEN;k++){
                    shudu[i][j][k]=0;
                }
            }
        }
#endif
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
#ifdef TEST
        for(int i=0;i<10000;i++){
            for(int j=0;j<SIDE_LEN;j++){
                for(int k=0;k<SIDE_LEN;k++){
                    shudu[i][j][k]=0;
                }
            }
        }
#endif
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
}