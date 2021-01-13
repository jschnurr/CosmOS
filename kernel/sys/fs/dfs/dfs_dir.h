//*****************************************************************
// This file is part of CosmOS                                    *
// Copyright (C) 2021 Tom Everett                                 *
// Released under the stated terms in the file LICENSE            *
// See the file "LICENSE" in the source distribution for details  *
// ****************************************************************

#ifndef _DFS_DIR_H
#define _DFS_DIR_H

#include <types.h>
#include <sys/devicemgr/devicemgr.h>
#include <sys/fs/dfs/dfs_block.h>

typedef bool (*dfs_file_iterator)(struct dfs_file_block* file_block);

/*
* returns file block, or zero
*/
uint64_t dfs_dir_find_file(struct device* dev, uint8_t* filename);
/*
* returns file block, or zero
*/
uint64_t dfs_dir_add_file(struct device* dev, uint8_t* filename);
/*
* iterate files
*/
void dfs_dir_iterate_files(struct device* dev, dfs_file_iterator file_iterator);

#endif