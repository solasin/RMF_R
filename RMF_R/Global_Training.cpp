#include"Storage_Structure.h"
#include"Global_Config.h"
#include<mkl.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<omp.h>
int Batch_Train(int rat_num,ftr_mtx_strc& cur_fms, rat_mtx_strc& cur_rms, stttc_strc& cur_ss){
	int iter = ITERATION_NUM;
	while (iter--){
		//printf("%d\n", iter);
		for (int tmp_idx = 0; tmp_idx < rat_num; tmp_idx++){
			int tmp_usr = cur_rms.inpt_elem[tmp_idx].usr_idx;
			int tmp_itm = cur_rms.inpt_elem[tmp_idx].itm_idx;
			double tmp_resi = cur_rms.inpt_elem[tmp_idx].rat - cblas_ddot(MATRIX_RANK, &cur_fms.usr_mtx[tmp_usr][0], 1, &cur_fms.itm_mtx[tmp_itm][0], 1);

			//user latent feature vectors update
			cblas_dscal(MATRIX_RANK, 1.0 - STEP_SIZE*REGULARIZED_LAMBDA, &cur_fms.usr_mtx[tmp_usr][0], 1);
			cblas_daxpy(MATRIX_RANK, STEP_SIZE*tmp_resi, &cur_fms.itm_mtx[tmp_itm][0], 1, &cur_fms.usr_mtx[tmp_usr][0], 1);

			//tmp_resi = cur_rms.lnk_node[tmp_idx].elem_rat - cblas_ddot(MATRIX_RANK, &cur_fms.usr_mtx[tmp_usr][0], 1, &cur_fms.itm_mtx[tmp_itm][0], 1);
			//item latent feature vectors update
			cblas_dscal(MATRIX_RANK, 1.0 - STEP_SIZE*REGULARIZED_LAMBDA, &cur_fms.itm_mtx[tmp_itm][0], 1);
			cblas_daxpy(MATRIX_RANK, STEP_SIZE*tmp_resi, &cur_fms.usr_mtx[tmp_usr][0], 1, &cur_fms.itm_mtx[tmp_itm][0], 1);
		}
	}
	return 0;
}

int Incre_Train(int rat_num,ftr_mtx_strc& cur_fms, rat_mtx_strc& cur_rms, stttc_strc& cur_ss){
	int *last_pos;
	int sam_num = 0;
	memset(sam_used, 0, sizeof(sam_used));
	last_pos = (int*)malloc(sizeof(int)*(U_NUM + I_NUM));
	memset(last_pos, -1, sizeof(int)*(U_NUM + I_NUM));
	int i = cur_rms.rela_num / 2;
	while (i < rat_num){
		last_pos[cur_rms.inpt_elem[i].usr_idx] = i;
		last_pos[cur_rms.inpt_elem[i].itm_idx + U_NUM] = i;
		i++;
	}
	i = cur_rms.rela_num / 2;
	while (i<rat_num){
		cur_rms.lega_usr[cur_rms.inpt_elem[i].usr_idx] = true;
		cur_rms.lega_itm[cur_rms.inpt_elem[i].itm_idx] = true;
		double tmp_resi = cur_rms.inpt_elem[i].rat - cblas_ddot(MATRIX_RANK, &cur_fms.usr_mtx[cur_rms.inpt_elem[i].usr_idx][0], 1, &cur_fms.itm_mtx[cur_rms.inpt_elem[i].itm_idx][0], 1);
		double tmp_pb = rand() / double(RAND_MAX)*1.0;
		if (tanh(tmp_resi*tmp_resi)>tmp_pb){
            cur_rms.Buld_Rela(cur_rms.inpt_elem[i].usr_idx, cur_rms.inpt_elem[i].itm_idx + U_NUM, cur_rms.inpt_elem[i].rat);
            cur_rms.Buld_Rela(cur_rms.inpt_elem[i].itm_idx + U_NUM, cur_rms.inpt_elem[i].usr_idx, cur_rms.inpt_elem[i].rat);
			if (i==last_pos[cur_rms.inpt_elem[i].usr_idx] || i==last_pos[cur_rms.inpt_elem[i].itm_idx+U_NUM]){
				sam_num+=cur_fms.Inc_Usr_Ftr_Train(cur_rms.inpt_elem[i].usr_idx, cur_rms);
				sam_num+=cur_fms.Inc_Itm_Ftr_Train(cur_rms.inpt_elem[i].itm_idx, cur_rms);
            }
		}
		i++;
	}
	printf("%d\t%d\t",cur_rms.rela_num/2, sam_num);
	free(last_pos);
	return 0;
}
