#ifndef GLOBAL_FUNCTION
#define GLOBAL_FUNCTION
#include "Storage_Structure.h"
int Glb_Init(ftr_mtx_strc& cur_fms, rat_mtx_strc& cur_rms, stttc_strc& cur_ss);
int Glb_Inpt_Init(int data_idx, ftr_mtx_strc& cur_fms,rat_mtx_strc& cur_rms, stttc_strc& cur_ss);

int Batch_Train(int rat_num,ftr_mtx_strc& cur_fms, rat_mtx_strc& cur_rms, stttc_strc& cur_ss);
int Incre_Train(int rat_num,ftr_mtx_strc& cur_fms, rat_mtx_strc& cur_rms, stttc_strc& cur_ss);
#endif