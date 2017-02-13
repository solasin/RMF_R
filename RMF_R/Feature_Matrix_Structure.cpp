#include"Storage_Structure.h"
#include"Global_Config.h"
#include<mkl.h>
#include<iostream>
int ftr_mtx_strc::Inc_Itm_Ftr_Train(int itm_idx, rat_mtx_strc& cur_rms){
	int iter = ITERATION_NUM;
	int sam_num = 0;
	vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF, stream, MATRIX_RANK, itm_mtx[itm_idx], 0.0, SEG / 2);
	/*for (int i = 0; i < MATRIX_RANK; i++)
		itm_mtx[itm_idx][i] = (rand() / double(RAND_MAX) * 2 * SEG - SEG);*/
	while (iter--){
		for (int tmp_idx = cur_rms.lnk_head[itm_idx+U_NUM]; tmp_idx != 0; tmp_idx = cur_rms.lnk_node[tmp_idx].nex_elem){
			if (sam_used[(tmp_idx + 1) / 2] == false)
				sam_num++;
			sam_used[(tmp_idx + 1) / 2] = true;
			int usr_idx = cur_rms.lnk_node[tmp_idx].elem_info;
			double tmp_resi = cur_rms.lnk_node[tmp_idx].elem_rat - cblas_ddot(MATRIX_RANK, &usr_mtx[usr_idx][0], 1, &itm_mtx[itm_idx][0], 1);
			cblas_dscal(MATRIX_RANK, 1.0 - STEP_SIZE*REGULARIZED_LAMBDA, &itm_mtx[itm_idx][0], 1);
			cblas_daxpy(MATRIX_RANK, STEP_SIZE*tmp_resi, &usr_mtx[usr_idx][0], 1, &itm_mtx[itm_idx][0], 1);
		}
	}
	return sam_num;
}

int ftr_mtx_strc::Inc_Usr_Ftr_Train(int usr_idx,rat_mtx_strc& cur_rms){
	int iter = ITERATION_NUM;
	int sam_num = 0;
	vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF, stream, MATRIX_RANK, usr_mtx[usr_idx], 0.0, SEG / 2);
    /*for (int i = 0; i < MATRIX_RANK; i++)
        usr_mtx[usr_idx][i] = (rand() / double(RAND_MAX) * 2 * SEG - SEG);*/
	while (iter--){
		for (int tmp_idx = cur_rms.lnk_head[usr_idx]; tmp_idx != 0; tmp_idx = cur_rms.lnk_node[tmp_idx].nex_elem){
			if (sam_used[(tmp_idx + 1) / 2] == false)
				sam_num++;
			sam_used[(tmp_idx + 1) / 2] = true;
			int itm_idx = cur_rms.lnk_node[tmp_idx].elem_info - U_NUM;
			double tmp_resi = cur_rms.lnk_node[tmp_idx].elem_rat - cblas_ddot(MATRIX_RANK, &usr_mtx[usr_idx][0], 1, &itm_mtx[itm_idx][0], 1);
			cblas_dscal(MATRIX_RANK, 1.0 - STEP_SIZE*REGULARIZED_LAMBDA, &usr_mtx[usr_idx][0], 1);
			cblas_daxpy(MATRIX_RANK, STEP_SIZE*tmp_resi, &itm_mtx[itm_idx][0], 1, &usr_mtx[usr_idx][0], 1);
		}
	}
	return sam_num;
}

void ftr_mtx_strc::Init_Ftr_Mtx_Strc(){
	//normal distribution
	vslNewStream(&stream, VSL_BRNG_MCG31, 1);
	for (int i = 0; i < U_NUM; i++)
		vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF, stream, MATRIX_RANK, usr_mtx[i], 0.0, SEG/2);
	for (int i = 0; i < I_NUM; i++)
		vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF, stream, MATRIX_RANK, itm_mtx[i], 0.0, SEG/2);
	
    //uniform distribution
	/*for (int i = 0; i < U_NUM;i++)
	for (int j = 0; j < MATRIX_RANK; j++)
		usr_mtx[i][j] = (rand() / double(RAND_MAX) * 2 * SEG - SEG);
	for (int i = 0; i < I_NUM;i++)
	for (int j = 0; j < MATRIX_RANK; j++)
		itm_mtx[i][j] = (rand() / double(RAND_MAX) * 2 * SEG - SEG);
    */
	return;
}
