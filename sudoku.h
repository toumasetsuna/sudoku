//
// Created by 86138 on 2023/6/30.
//

#ifndef SUDOKU_MAIN_H
#define SUDOKU_MAIN_H
int const SIDE_LEN = 9;
int const T_SIZE = 81;
void copy_shudu(int shudu_game[9][9], int shudu_game_copy[9][9]);
void generate_shudu_game(int shudu_game[9][9], int blank_num,bool from_final);
void generate_shudu_final(int shudu_final[9][9]);
void generate_shudu_final_list(int shudu_final_list[][9][9], int num);
void print_shudu(int shudu[9][9]);
bool check_ans_unique(int shudu[9][9]);
bool solve_shudu_game(int shudu_game[9][9]);
void get_ans_num(int shudu_game[9][9]);
void clean_shudu(int shudu_game[9][9]);
int get_ans(int shudu_game[9][9]);
#endif //SUDOKU_MAIN_H
