#pragma once

#define BANKERS_ROW 5
#define BANKERS_COL 3


struct banker_ptable {
	__int64 allocated_resources[BANKERS_ROW * BANKERS_COL];
	__int64 max_resources[BANKERS_ROW * BANKERS_COL];
	__int64 need_resources[BANKERS_ROW * BANKERS_COL];

	__int64 safe_state_resources[5];
	__int64 available_resources[3];
};



void parseInputFrmFile(struct scene_ops* self)
{


}


/*
Set sample banking
data which uses random
data as input */
void sampleBankingData(struct scene_ops* self)
{
	char buffer[15];
	struct scene_3_info* scene3 = (struct scene_3_info*)self->private_data;
	DWORD i, j;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < PTABLE_CHILD_LEN; j++)
		{
			snprintf(buffer, 8, "%d", (int)rand() % 100);
			SetWindowTextA(scene3->ptable_info[i]->child_data[j], buffer);
		}
	}
}

/*
Get banking Data
from edit box and
convert it into long
for doing further
calculations
*/
void getBankingData(struct scene_ops* self, struct banker_ptable* btable_struct)
{
	char buffer[16];
	DWORD size, index;

	struct scene_3_info* scene3 = (struct scene_3_info*)self->private_data;

	/* y * cols + x = index
	index - x = y * cols
	(index - x) / cols = y
	*/
	for (index = 0; index < PTABLE_CHILD_LEN; index++)
	{
		size = GetWindowTextA(scene3->ptable_info[0]->child_data[index], buffer, 8);
		buffer[size] = '\0';
		btable_struct->allocated_resources[index] = atol(buffer);
	}

	for (index = 0; index < PTABLE_CHILD_LEN; index++)
	{
		size = GetWindowTextA(scene3->ptable_info[1]->child_data[index], buffer, 8);
		buffer[size] = '\0';
		btable_struct->max_resources[index] = atol(buffer);
	}

	for (index = 0; index < PTABLE_CHILD_LEN; index++)
	{
		size = GetWindowTextA(scene3->ptable_info[2]->child_data[index], buffer, 8);
		buffer[size] = '\0';
		btable_struct->need_resources[index] = atol(buffer);
	}

	for (index = 0; index < AVAILABLE_PTABLE_CHILD_LEN; index++)
	{
		size = GetWindowTextA(scene3->available_pt->child_data[index], buffer, 8);
		buffer[size] = '\0';
		btable_struct->available_resources[index] = atol(buffer);
	}
	for (index = 5; index < 13; index++)
	{
		size = GetWindowTextA(scene3->bchild_window[index], buffer, 8);
		buffer[size] = '\0';
		btable_struct->safe_state_resources[index - 5] = atol(buffer);

	}

}
/*
Do calculation on
banking data as per
bankers algorithm for os
*/
void calculateBankingData(struct scene_ops* self, struct banker_ptable* btable_struct)
{
	char buffer[12];
	struct scene_3_info* scene3 = (struct scene_3_info*)self->private_data;

	for (DWORD i = 0; i < BANKERS_COL * BANKERS_ROW; i++)
	{
		btable_struct->need_resources[i] = btable_struct->max_resources[i] - btable_struct->allocated_resources[i];
		snprintf(buffer, 8, "%ld", btable_struct->need_resources[i]);
		SetWindowTextA(scene3->ptable_info[2]->child_data[i], buffer);
	}
}



void resetBankingData(struct scene_ops* self)
{
	struct scene_3_info* scene3 = (struct scene_3_info*)self->private_data;
	DWORD i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < PTABLE_CHILD_LEN; j++)
		{
			SetWindowTextA(scene3->ptable_info[i]->child_data[j], "");
		}
	}

	for (i = 0; i < AVAILABLE_PTABLE_CHILD_LEN; i++)
	{
		SetWindowTextA(scene3->available_pt->child_data[i], "");
	}
	
	for (i = 5; i < 13; i++)
	{
		SetWindowTextA(scene3->bchild_window[i], "");
	}
}