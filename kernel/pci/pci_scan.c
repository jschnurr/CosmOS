/*****************************************************************
 * This file is part of CosmOS                                   *
 * Copyright (C) 2020 Kurt M. Weber                              *
 * Released under the stated terms in the file LICENSE           *
 * See the file "LICENSE" in the source distribution for details *
 *****************************************************************/

#ifndef _PCI_SCAN_C
#define _PCI_SCAN_C

#include <types.h>
#include <asm/asm.h>
#include <console/console.h>
#include <pci/pci.h>
#include <pci/devicetree.h>

bool pci_device_exists(uint8_t bus, uint8_t device){
	if (pci_header_read_vendor(bus, device) == 0xFFFF){
		return false;
	} else {
		return true;
	}
}

void pci_scan(){
	uint16_t bus = 0, device = 0, function = 0;
	uint32_t register_dword;
	uint16_t device_id, vendor_id;
	uint8_t class_code, subclass_code, header_code;
	
	kprintf("Scanning for PCI devices...\n");
	
	for (bus = 0; bus < 256; bus++){
		for (device = 0; device < 32; device++){
			for (function = 0; function < 8; function++){
				asm_out_d(PCI_CONFIG_ADDRESS_PORT, pci_config_address_build(bus, device, function, 0, 1));
				register_dword = asm_in_d(PCI_CONFIG_DATA_PORT);
				
				vendor_id = (uint16_t)(register_dword & 0x0000FFFF);
				device_id = (uint16_t)(register_dword >> 16);
				
				if (vendor_id != 0xFFFF){
					kprintf("PCI device found at %#hX:%#hX:%#hX, vendor %#X, device %#X\n", bus, device, function, vendor_id, device_id);
					asm_out_d(PCI_CONFIG_ADDRESS_PORT, pci_config_address_build(bus, device, function, 0x08, 1));
					register_dword = asm_in_d(PCI_CONFIG_DATA_PORT);
					
					class_code = (uint8_t)(register_dword >> 24);
					subclass_code = (uint8_t)((register_dword >> 16) & 0x00FF);
					
					asm_out_d(PCI_CONFIG_ADDRESS_PORT, pci_config_address_build(bus, device, function, 0x0C, 1));
					register_dword = asm_in_d(PCI_CONFIG_DATA_PORT);
					header_code = (uint8_t)((register_dword >> 16) & 0x00FF);
					
					kprintf("\tClass %#hX, subclass %#hX, header type %#hX\n", class_code, subclass_code, header_code);
				}
			}
		}
	}
	
	
	pci_scan_bus(0);
	
	return;
}

void pci_scan_bus(uint8_t bus){
	uint8_t i;
	
	for (i = 0; i < 32; i++){
		if (!pci_device_exists(bus, i)){
			continue;
		}
		
		
	}
}

#endif