/*
 * Linux内核诊断工具--用户接口API
 *
 * Copyright (C) 2020 Alibaba Ltd.
 *
 * 作者: Baoyou Xie <baoyou.xie@linux.alibaba.com>
 *
 * License terms: GNU General Public License (GPL) version 3
 *
 */

#ifndef UAPI_LOAD_MONITOR_H
#define UAPI_LOAD_MONITOR_H

#include <linux/ioctl.h>

int load_monitor_syscall(struct pt_regs *regs, long id);

//#define DIAG_LOAD_MONITOR_ACTIVATE (DIAG_BASE_SYSCALL_LOAD_MONITOR)
//#define DIAG_LOAD_MONITOR_DEACTIVATE (DIAG_LOAD_MONITOR_ACTIVATE + 1)
#define DIAG_LOAD_MONITOR_SET (DIAG_BASE_SYSCALL_LOAD_MONITOR)
#define DIAG_LOAD_MONITOR_SETTINGS (DIAG_LOAD_MONITOR_SET + 1)
#define DIAG_LOAD_MONITOR_DUMP (DIAG_LOAD_MONITOR_SETTINGS + 1)

struct diag_load_monitor_settings {
	unsigned int activated;
	unsigned int verbose;
	unsigned int style;
	unsigned int mass;
	unsigned int cpu_run;
	unsigned int threshold_load;   // 系统load值
	unsigned int threshold_load_r; // 正在运行的任务引起的Load
	unsigned int threshold_load_d; // D状态任务引起的Load
	unsigned int threshold_task_d; // 当前处于D状态的任务数量
};

struct load_monitor_task {
	int et_type;
	unsigned long id;
	struct diag_timespec tv;
	struct diag_task_detail task;
	struct diag_kern_stack_detail kern_stack;
	struct diag_proc_chains_detail proc_chains;
};

struct load_monitor_cpu_run {
	int et_type;
	unsigned long id;
	unsigned long cpu;
	struct diag_timespec tv;
	struct diag_task_detail task;
	struct diag_kern_stack_detail kern_stack;
	struct diag_user_stack_detail user_stack;
};

struct load_monitor_detail {
	int et_type;
	unsigned long id;
	struct diag_timespec tv;
	unsigned int load_1_1;
	unsigned int load_1_2;
	unsigned int load_5_1;
	unsigned int load_5_2;
	unsigned int load_15_1;
	unsigned int load_15_2;
	unsigned int load_r_1_1;
	unsigned int load_r_1_2;
	unsigned int load_r_5_1;
	unsigned int load_r_5_2;
	unsigned int load_r_15_1;
	unsigned int load_r_15_2;
	unsigned int load_d_1_1;
	unsigned int load_d_1_2;
	unsigned int load_d_5_1;
	unsigned int load_d_5_2;
	unsigned int load_d_15_1;
	unsigned int load_d_15_2;
};

#define CMD_LOAD_MONITOR_SET (0)
#define CMD_LOAD_MONITOR_SETTINGS (CMD_LOAD_MONITOR_SET + 1)
#define CMD_LOAD_MONITOR_DUMP (CMD_LOAD_MONITOR_SETTINGS + 1)
#define CMD_LOAD_MONITOR_TEST (CMD_LOAD_MONITOR_DUMP + 1)
#define DIAG_IOCTL_LOAD_MONITOR_SET _IOWR(DIAG_IOCTL_TYPE_LOAD_MONITOR, CMD_LOAD_MONITOR_SET, struct diag_load_monitor_settings)
#define DIAG_IOCTL_LOAD_MONITOR_SETTINGS _IOWR(DIAG_IOCTL_TYPE_LOAD_MONITOR, CMD_LOAD_MONITOR_SETTINGS, struct diag_load_monitor_settings)
#define DIAG_IOCTL_LOAD_MONITOR_DUMP _IOWR(DIAG_IOCTL_TYPE_LOAD_MONITOR, CMD_LOAD_MONITOR_DUMP, struct diag_ioctl_dump_param)
#define DIAG_IOCTL_LOAD_MONITOR_TEST _IOWR(DIAG_IOCTL_TYPE_LOAD_MONITOR, CMD_LOAD_MONITOR_TEST, int)

#endif /* UAPI_LOAD_MONITOR_H */
