#ifndef STORAGE_STRUCTURE
#define STORAGE_STRUCTURE
#include<mkl.h>
#include "Global_Config.h"
//rating input storage structure
struct rat_strc{
	int usr_idx, itm_idx, tmst;
	double rat;	
};

//rating sparse storage structure (array)
struct elem_strc{
	int nex_elem, elem_info;
	double elem_rat;
};
struct rat_mtx_strc{
	rat_strc inpt_elem[R_NUM];
	elem_strc lnk_node[2 * R_NUM];
	int lnk_head[I_NUM + U_NUM];
	int rela_num;
	bool lega_usr[U_NUM];
	bool lega_itm[I_NUM];
	void Init_Rat_Mtx_Strc();
	void Buld_Rela(int frst_idx,int secn_idx,double rat);
	void Push_Data(int rat_num);
};

//feature matrix storage structure (array)
struct ftr_mtx_strc{
	double usr_mtx[U_NUM][MATRIX_RANK];
	double itm_mtx[I_NUM][MATRIX_RANK];
	VSLStreamStatePtr stream;
	void Init_Ftr_Mtx_Strc();
	int Inc_Usr_Ftr_Train(int usr_idx,rat_mtx_strc& cur_rms);
	int Inc_Itm_Ftr_Train(int itm_idx,rat_mtx_strc& cur_rms);
};

//statistics information storage structure
struct stttc_strc{
	double glb_mse;
	double glb_num;
	double rat_max, rat_min;
	double rat_mean;
	double ret_rmse,trn_rmse;
	double glb_err;
	void Init_Stttc_Strc();
};
#endif