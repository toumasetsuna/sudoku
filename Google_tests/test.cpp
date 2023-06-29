//
// Created by 86138 on 2023/6/30.
//
#include <iostream>
#include <gtest/gtest.h>
#include "../sudoku.h"

using namespace std;

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

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running main() from gtest_main.cc\n";

    testing::InitGoogleTest(&argc, argv);//解析命令行中的GoogleTest参数，它允许用户通过多样的命令行参数来控制测试程序的行为（即定制命令行参数的行为）
    return RUN_ALL_TESTS();//将会搜索不同的Test Case和不同的源文件中所有已经存在测试案例，然后运行它们，所有Test都成功时返回1，否则返回0。
}

TEST(TestCase, test1) {
    EXPECT_STREQ("hello world", "hello world");
    test_time();
}
