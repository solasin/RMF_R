#include"Storage_Structure.h"
#include<iostream>
#include<cstdio>
#include<cstring>
void rat_mtx_strc::Push_Data(int rat_num){
	int i = rela_num / 2;
	while(i < rat_num){
		Buld_Rela(inpt_elem[i].usr_idx, inpt_elem[i].itm_idx + U_NUM, inpt_elem[i].rat);
		Buld_Rela(inpt_elem[i].itm_idx + U_NUM, inpt_elem[i].usr_idx, inpt_elem[i].rat);
		lega_usr[inpt_elem[i].usr_idx] = true;
		lega_itm[inpt_elem[i].itm_idx] = true;
		i++;
	}
	return;
}

void rat_mtx_strc::Buld_Rela(int frst_idx, int secn_idx, double rat){
	rela_num++;
	lnk_node[rela_num].elem_info = secn_idx;
	lnk_node[rela_num].elem_rat = rat;
	lnk_node[rela_num].nex_elem = lnk_head[frst_idx];
	lnk_head[frst_idx] = rela_num;
	return;
}

void rat_mtx_strc::Init_Rat_Mtx_Strc(){
	memset(lnk_head, 0, sizeof(lnk_head));
	rela_num = 0;
	memset(lega_usr, 0, sizeof(lega_usr));
	memset(lega_itm, 0, sizeof(lega_itm));
	return;
}
