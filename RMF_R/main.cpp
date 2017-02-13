#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<mkl.h>
#include<algorithm>
#include<cmath>
#include<ctime>
#include "Global_Config.h"
#include"Storage_Structure.h"
#include"Global_Function.h"
using namespace std;
ftr_mtx_strc fms;
rat_mtx_strc rms;
stttc_strc ss;
bool sam_used[R_NUM];
int main(){
	char outp_data_path[PATH_LENGTH];
	//sprintf(outp_data_path, "%s%s", DATA_PATH, "result");
	//freopen(outp_data_path, "w", stdout);
	int head_tmst, tail_tmst;
	int rat_num;
	head_tmst = clock();
	Glb_Init(fms, rms, ss);
	rat_num=Glb_Inpt_Init(0,fms,rms,ss);
	rms.Push_Data(rat_num);
	Batch_Train(rat_num,fms, rms, ss);//batch_training();
	for (int i = 1; i < DEPARTS_NUM; i++){
		long long t1 = clock();
		rat_num=Glb_Inpt_Init(i, fms, rms, ss);
		Incre_Train(rat_num,fms, rms, ss);//incremental_training();
		long long t2 = clock();
        long long dett=(t2-t1)*1000/CLOCKS_PER_SEC;
		printf("%lld\n", dett);
	}
	tail_tmst = clock();
	//fclose(stdout);
	//printf("Fin Cost Time = %d ms\n", (tail_tmst - head_tmst)*1000/CLOCKS_PER_SEC);
	return 0;
}
