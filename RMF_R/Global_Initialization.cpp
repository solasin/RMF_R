#include"Storage_Structure.h"
#include"Global_Function.h"
#include<mkl.h>
#include<ctime>
#include<iostream>
#include<string>
#include<omp.h>
#include<cmath>
#include<cstdio>
using namespace std;
int Glb_Init(ftr_mtx_strc& cur_fms,rat_mtx_strc& cur_rms,stttc_strc& cur_ss){
	srand(unsigned(time(0)));
	omp_set_num_threads(NUM_OF_THREADS);
	cur_fms.Init_Ftr_Mtx_Strc();
	cur_rms.Init_Rat_Mtx_Strc();
	cur_ss.Init_Stttc_Strc();
	return 0;
}

int Glb_Inpt_Init(int data_idx, ftr_mtx_strc& cur_fms,rat_mtx_strc& cur_rms, stttc_strc& cur_ss){
	char cur_data_path[PATH_LENGTH];
	sprintf(cur_data_path, "%s%d.in", DATA_PATH, data_idx);
	freopen(cur_data_path, "r", stdin);
	
	int rat_num = cur_rms.rela_num/2;
	while (scanf("%d::%d::%lf::%d", &cur_rms.inpt_elem[rat_num].usr_idx, &cur_rms.inpt_elem[rat_num].itm_idx, &cur_rms.inpt_elem[rat_num].rat,&cur_rms.inpt_elem[rat_num].tmst) != EOF)
		rat_num++;
	if (data_idx != 0){
		double loc_err = 0;
		double loc_num = 0;
		for (int i = cur_rms.rela_num / 2; i < rat_num; i++){
			if (cur_rms.lega_usr[cur_rms.inpt_elem[i].usr_idx] && cur_rms.lega_itm[cur_rms.inpt_elem[i].itm_idx]){
				double tmp_mult = cblas_ddot(MATRIX_RANK, &cur_fms.usr_mtx[cur_rms.inpt_elem[i].usr_idx][0], 1, &cur_fms.itm_mtx[cur_rms.inpt_elem[i].itm_idx][0], 1);
				tmp_mult += cur_ss.rat_mean;
				if (tmp_mult < cur_ss.rat_min) tmp_mult = cur_ss.rat_min;
				if (tmp_mult> cur_ss.rat_max) tmp_mult = cur_ss.rat_max;
				loc_err += (cur_rms.inpt_elem[i].rat - tmp_mult)*(cur_rms.inpt_elem[i].rat - tmp_mult);
				loc_num += 1.0;
			}
			cur_rms.inpt_elem[i].rat = cur_rms.inpt_elem[i].rat-cur_ss.rat_mean;
		}
		cur_ss.glb_mse += loc_err;
		cur_ss.glb_num += loc_num;
		printf("%d\t%.8lf\t%.8lf\t", data_idx, sqrt(cur_ss.glb_mse / cur_ss.glb_num), sqrt(loc_err / loc_num));
	}

	//0 - mean
	if (data_idx == 0){
		for (int i = 0; i < rat_num; i++){
			if (cur_rms.inpt_elem[i].rat>cur_ss.rat_max)
				cur_ss.rat_max = cur_rms.inpt_elem[i].rat;
			if (cur_rms.inpt_elem[i].rat < cur_ss.rat_min)
				cur_ss.rat_min = cur_rms.inpt_elem[i].rat;
			cur_ss.rat_mean += cur_rms.inpt_elem[i].rat;
		}
		cur_ss.rat_mean = ((double)cur_ss.rat_mean)/((double)(rat_num));
		for (int i = 0; i < rat_num; i++)
			cur_rms.inpt_elem[i].rat = cur_rms.inpt_elem[i].rat - cur_ss.rat_mean;
	}
    
	fclose(stdin);
	return rat_num;
}
