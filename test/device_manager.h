/**
 * @file device_manager.h
 * @author Yao J (jieyao.lxr@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-07-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __STORAGE_DEVICE_H
#define __STORAGE_DEVICE_H

typedef int (*read_fp)(void);

struct storage_device {
    char name[20];
    read_fp read;
};

extern int register_device(struct storage_device dev);
extern int read_device(char *device_name);

#endif
