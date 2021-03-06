//*****************************************************************
// This file is part of CosmOS                                    *
// Copyright (C) 2020 Tom Everett                                 *
// Released under the stated terms in the file LICENSE            *
// See the file "LICENSE" in the source distribution for details  *
// ****************************************************************
/*
* this file defines the interface that all ATA devices will implement
*/
#ifndef _DEVICEAPI_BLOCK_H
#define _DEVICEAPI_BLOCK_H

#include <types.h>
#include <sys/devicemgr/devicemgr.h>
/*
* count is the numvber of sectors to read.  it is assumed that data is at least as big as count*sector_size
*/
typedef void (*block_read_sector_function)(struct device* dev, uint32_t sector, uint8_t* data, uint32_t count);
typedef void (*block_write_sector_function)(struct device* dev, uint32_t sector, uint8_t* data, uint32_t count);
typedef uint16_t (*block_sector_size_function)(struct device* dev);
typedef uint32_t (*block_total_size_function)(struct device* dev);

struct deviceapi_block {
    block_read_sector_function read;
    block_write_sector_function write;
    block_sector_size_function sector_size;
    block_total_size_function total_size;
};

#endif