#ifndef GLOBAL_CONFIG
#define GLOBAL_CONFIG

//dataset settings
#define PATH_LENGTH 100
#define DATA_PATH "/home/xunpenghuang/LFT_Experiment/data/MovieLens10M/incremental_departs/" 
#define U_NUM 80000
#define I_NUM 70000
#define R_NUM 10200000
#define SEG 2e-2
#define FOLDS 5
#define DEPARTS_NUM 200


//parameters settings
#define STEP_SIZE 0.00018 
#define MATRIX_RANK 70
#define ITERATION_NUM 1200
#define NUM_OF_THREADS 2
#define REGULARIZED_LAMBDA 0.01

//extern char DATA_PATH[PATH_LENGTH];
//extern double REGULARIZED_LAMBDA;
extern bool sam_used[R_NUM];
#endif
