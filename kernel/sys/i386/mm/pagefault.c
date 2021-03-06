/*****************************************************************
 * This file is part of CosmOS                                   *
 * Copyright (C) 2021 Kurt M. Weber                              *
 * Released under the stated terms in the file LICENSE           *
 * See the file "LICENSE" in the source distribution for details *
 *****************************************************************/

#include <types.h>
#include <sys/asm/misc.h>
#include <sys/console/console.h>
#include <sys/i386/mm/mm.h>
#include <sys/i386/mm/pagetables.h>

void page_fault_handler(uint64_t error, void *cr2, pttentry cr3){
    uint64_t page;

    // note that the PFE_ERROR_PRESENT flag is zero if the flag is NOT present
    if (!(error & PFE_ERROR_PRESENT)){
        page = slab_allocate(1, PDT_INUSE);

        map_page_at(page, cr2, asm_cr3_read(), false);
    }

    return;
}