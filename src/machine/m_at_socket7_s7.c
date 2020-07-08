/*
 * 86Box	A hypervisor and IBM PC system emulator that specializes in
 *		running old operating systems and software designed for IBM
 *		PC systems and compatibles from 1981 through fairly recent
 *		system designs based on the PCI bus.
 *
 *		This file is part of the 86Box distribution.
 *
 *		Implementation of Socket 7 machines.
 *
 *
 *
 * Authors:	Sarah Walker, <http://pcem-emulator.co.uk/>
 *		Miran Grca, <mgrca8@gmail.com>
 *		Melissa Goad, <mszoopers@protonmail.com>
 *
 *		Copyright 2010-2020 Sarah Walker.
 *		Copyright 2016-2020 Miran Grca.
 *
 */

/* BIOS downloads for select machines and system boards: */
/* http://www.elhvb.com/supportbios.info/Archives/BIOS/R-S/SUPERMICRO/index.html */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <86box/86box.h>
#include <86box/mem.h>
#include <86box/io.h>
#include <86box/rom.h>
#include <86box/pci.h>
#include <86box/device.h>
#include <86box/chipset.h>
#include <86box/hdc.h>
#include <86box/hdc_ide.h>
#include <86box/keyboard.h>
/* #include <86box/intel_sio.h>
#include <86box/piix.h> */
#include <86box/sio.h>
#include <86box/flash.h>
/* #include <86box/via_vt82c586b.h> */
#include <86box/hwm.h>
#include <86box/video.h>
#include <86box/spd.h>
#include "cpu.h"
#include <86box/machine.h>

int
machine_at_chariot_init(const machine_t *model)
{
    int ret;

    ret = bios_load_linear(L"roms/machines/chariot/P5IV183.ROM",
			   0x000e0000, 131072, 0);

    if (bios_only || !ret)
	return ret;

    machine_at_common_init(model);

    pci_init(PCI_CONFIG_TYPE_1);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x14, PCI_CARD_NORMAL, 1, 2, 3, 4);
    pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
    pci_register_slot(0x12, PCI_CARD_NORMAL, 3, 4, 2, 1);
    pci_register_slot(0x11, PCI_CARD_NORMAL, 4, 3, 2, 1);
	
    device_add(&i430fx_device);
    device_add(&piix_device);
    device_add(&keyboard_ps2_ami_pci_device);
    device_add(&pc87306_device);
    device_add(&intel_flash_bxt_device);

    return ret;
}

int
machine_at_mr586_init(const machine_t *model)
{
    int ret;

    ret = bios_load_linear(L"roms/machines/mr586/TRITON.BIO",
			   0x000e0000, 131072, 0);

    if (bios_only || !ret)
	return ret;

    machine_at_common_init(model);

    pci_init(PCI_CONFIG_TYPE_1);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
    pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
    pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
    pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	
    device_add(&i430fx_device);
    device_add(&piix_device);
    device_add(&keyboard_ps2_ami_pci_device);
    device_add(&fdc37c665_device);
    device_add(&intel_flash_bxt_device);

    return ret;
}

int
machine_at_p55t2p4_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/p55t2p4/0207_j2.bin",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);

	return ret;
}


int
machine_at_p55t2s_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/p55t2s/s6y08t.rom",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);

	return ret;
}
int
machine_at_8500tuc_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/8500tuc/Tuc0221b.rom",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&um8669f_device);
	device_add(&intel_flash_bxt_device);

	return ret;
}

int
machine_at_m7shi_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/m7shi/m7shi2n.rom",
		0x000c0000, 262144, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&fdc37c935_device);
	device_add(&intel_flash_bxt_device);

	return ret;
}

int
machine_at_p65up5_cp55t2d_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/p65up5/td5i0201.awd",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_p65up5_common_init(model, &i430hx_device);

	return ret;
}

int
machine_at_p55tvp4_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/p55tvp4/0204_128.BIN",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430vx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device); //It uses the AMIKEY KBC
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);

	return ret;
}

int
machine_at_i430vx_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/430vx/55xwuq0e.bin",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430vx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&um8669f_device);
	device_add(&intel_flash_bxt_device);

	return ret;
}

int
machine_at_p55va_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/p55va/va021297.bin",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430vx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	device_add(&intel_flash_bxt_device);

	return ret;
}

int
machine_at_8500tvxa_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/8500tvxa/tvx0619b.rom",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 2, 1);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 3, 2, 1);
	device_add(&i430vx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&um8669f_device);
	device_add(&sst_flash_29ee010_device);

	return ret;
}

int
machine_at_nupro592_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/nupro592/np590b10.bin",
		0x000c0000, 262144, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 3, 4, 1, 2); /*Strongly suspect these are on-board slots*/
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 4);	/* PIIX4 */
	device_add(&i430tx_device);
	device_add(&piix4_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83977ef_device);
	device_add(&intel_flash_bxt_device);
	spd_register(SPD_TYPE_SDRAM, 0x3, 128);

	hwm_values_t machine_hwm = {
		{    /* fan speeds */
			3000,	/* Chassis */
			3000,	/* CPU */
			3000,	/* Power */
			0
		},{ /* temperatures */
			30,	/* MB */
			0,	/* unused */
			27,	/* CPU */
			0
		},{ /* voltages */
			3300,				   /* VCORE (3.3V by default) */
			0,				   /* unused */
			3300,				   /* +3.3V */
			RESISTOR_DIVIDER(5000,   11,  16), /* +5V  (divider values bruteforced) */
			RESISTOR_DIVIDER(12000,  28,  10), /* +12V (28K/10K divider suggested in the W83781D datasheet) */
			RESISTOR_DIVIDER(12000, 853, 347), /* -12V (divider values bruteforced) */
			RESISTOR_DIVIDER(5000,    1,   2), /* -5V  (divider values bruteforced) */
			0
		}
	};
	/* Pentium, Pentium OverDrive MMX, Pentium Mobile MMX: 3.3V (real Pentium Mobile MMX is 2.45V).
	Pentium MMX: 2.8 V.
	AMD K6 Model 6: 2.9 V for 166/200, 3.2 V for 233.
	AMD K6 Model 7: 2.2 V. */
	if (model->cpu[cpu_manufacturer].cpus[cpu_effective].cpu_type == CPU_PENTIUMMMX)
		machine_hwm.voltages[0] = 2800; /* set higher VCORE (2.8V) for Pentium MMX */
	else if (model->cpu[cpu_manufacturer].cpus[cpu_effective].cpu_type == CPU_K6)
		machine_hwm.voltages[0] = 2200; /* set higher VCORE (2.8V) for Pentium MMX */
	else if (model->cpu[cpu_manufacturer].cpus[cpu_effective].cpu_type == CPU_K6_2)
		machine_hwm.voltages[0] = 2200; /* set higher VCORE (2.8V) for Pentium MMX */
	hwm_set_values(machine_hwm);
	device_add(&w83781d_device);

	return ret;
}

int
machine_at_tx97_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/tx97/0112.001",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x01, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);	/* PIIX4 */
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430tx_device);
	device_add(&piix4_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877tf_acorp_device);
	device_add(&intel_flash_bxt_device);
	spd_register(SPD_TYPE_SDRAM, 0x3, 128);

	hwm_values_t machine_hwm = {
		{    /* fan speeds */
			3000,	/* Chassis */
			3000,	/* CPU */
			3000	/* Power */
		},{ /* temperatures */
			30,	/* MB */
			0,	/* unused */
			8	/* CPU */
		},{ /* voltages */
			3300,				   /* VCORE (3.3V by default) */
			0,				   /* unused */
			3300,				   /* +3.3V */
			RESISTOR_DIVIDER(5000,   11,  16), /* +5V  (divider values bruteforced) */
			RESISTOR_DIVIDER(12000,  28,  10), /* +12V (28K/10K divider suggested in the W83781D datasheet) */
			RESISTOR_DIVIDER(12000, 853, 347), /* -12V (divider values bruteforced) */
			RESISTOR_DIVIDER(5000,    1,   2)  /* -5V  (divider values bruteforced) */
		}
	};
	/* Pentium, Pentium OverDrive MMX, Pentium Mobile MMX: 3.3V (real Pentium Mobile MMX is 2.45V).
	Pentium MMX: 2.8 V.
	AMD K6 Model 6: 2.9 V for 166/200, 3.2 V for 233.
	AMD K6 Model 7: 2.2 V. */
	switch (model->cpu[cpu_manufacturer].cpus[cpu_effective].cpu_type) {
	case CPU_PENTIUMMMX:
		machine_hwm.voltages[0] = 2800;
		break;
	case CPU_K6:
	case CPU_K6_2:
		machine_hwm.voltages[0] = 2200;
		break;
	}
	hwm_set_values(machine_hwm);
	device_add(&w83781d_device);

	return ret;
}

#if defined(DEV_BRANCH) && defined(NO_SIO)
int
machine_at_586t2_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/586t2/5itw001.bin",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);	/* PIIX4 */
	device_add(&i430tx_device);
	device_add(&piix4_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&um8669f_device); /*Placeholder for ITE 8679*/
	device_add(&sst_flash_29ee010_device);
	spd_register(SPD_TYPE_SDRAM, 0x3, 128);

	return ret;
}
#endif

int
machine_at_p5mms98_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/p5mms98/s981182.rom",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);	/* PIIX4 */
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	device_add(&i430tx_device);
	device_add(&piix4_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&w83977tf_device);
	device_add(&intel_flash_bxt_device);
	spd_register(SPD_TYPE_SDRAM, 0x3, 128);

	hwm_values_t machine_hwm = {
		{    /* fan speeds */
			3000,	/* Thermal */
			3000,	/* CPU */
			3000	/* Chassis */
		},{ /* temperatures */
			0,	/* unused */
			30	/* CPU */
		},{ /* voltages */
			3300,				   /* VCORE (3.3V by default) */
			3300,				   /* VIO (3.3V) */
			3300,				   /* +3.3V */
			RESISTOR_DIVIDER(5000,   11,  16), /* +5V  (divider values bruteforced) */
			RESISTOR_DIVIDER(12000,  28,  10), /* +12V (28K/10K divider suggested in the W83781D datasheet) */
			RESISTOR_DIVIDER(12000, 853, 347), /* -12V (divider values bruteforced) */
			RESISTOR_DIVIDER(5000,    1,   2)  /* -5V  (divider values bruteforced) */
		}
	};
	/* Pentium, Pentium OverDrive MMX, Pentium Mobile MMX: 3.3V (real Pentium Mobile MMX is 2.45V).
	Pentium MMX: 2.8 V.
	AMD K6 Model 6: 2.9 V for 166/200, 3.2 V for 233.
	AMD K6 Model 7: 2.2 V. */
	switch (model->cpu[cpu_manufacturer].cpus[cpu_effective].cpu_type) {
	case CPU_PENTIUMMMX:
		machine_hwm.voltages[0] = 2800;
		break;
	case CPU_K6:
	case CPU_K6_2:
		machine_hwm.voltages[0] = 2200;
		break;
	}
	hwm_set_values(machine_hwm);
	device_add(&lm78_device);
	device_add(&lm75_1_4a_device);

	return ret;
}

int
machine_at_ficva502_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/ficva502/VA502bp.BIN",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);
	device_add(&via_vpx_device);
	device_add(&via_vt82c586b_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&sst_flash_29ee010_device);
	spd_register(SPD_TYPE_SDRAM, 0x3, 256);

	return ret;
}

int
machine_at_ficpa2012_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/ficpa2012/113jb16.awd",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);
	device_add(&via_vp3_device);
	device_add(&via_vt82c586b_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&sst_flash_39sf010_device);
	spd_register(SPD_TYPE_SDRAM, 0x7, 512);

	return ret;
}

#if defined(DEV_BRANCH) && defined(NO_SIO)
int
machine_at_advanceii_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/advanceii/VP3_V27.BIN",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);
	device_add(&via_vp3_device);
	device_add(&via_vt82c586b_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&um8669f_device); //IT8661F
	device_add(&sst_flash_39sf010_device);

	return ret;
}
#endif

/* IBM (International Business Machines) */
int
machine_ibm_pc_330_350_init(const machine_t *model)
{
	/* IBM PC 330-P75  (6575) */
	/* IBM PC 330-P90  (6575) */
	/* IBM PC 330-P100 (6575) */
	/* IBM PC 330-P133 (6576) */
	/* IBM PC 330-P166 (6576) */
	/* IBM PC 350-P75  (6575) */
	/* IBM PC 350-P90  (6575) */
	/* IBM PC 350-P100 (6575) */
	/* IBM PC 350-P133 (6576) */
	/* IBM PC 350-P166 (6576) */
	/* NOTE: These machines use an Intel Morrison64 (Holly/Blitzen) system board */
	int ret;
	/* ret = bios_load_linear_combined2(L"roms/machines/ibm_pc_330_350/4B09CC0M.BIO",
	L"roms/machines/ibm_pc_330_350/4B09CC0M.BI1",
	L"roms/machines/ibm_pc_330_350/4B09CC0M.BI2",
	L"roms/machines/ibm_pc_330_350/4B09CC0M.BI3",
	L"roms/machines/ibm_pc_330_350/1006CS1_.RCV",
	0x3a000, 128); */
	ret = bios_load_linear_combined2_norcv(L"roms/machines/ibm_pc_330_350/4B09CC0M.BIO",
		L"roms/machines/ibm_pc_330_350/4B09CC0M.BI1",
		L"roms/machines/ibm_pc_330_350/4B09CC0M.BI2",
		L"roms/machines/ibm_pc_330_350/4B09CC0M.BI3",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	/* pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0); */
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	/* device_add(&intel_flash_bxt_ami_device); */
	/* if (gfxcard == VID_INTERNAL)
	device_add(&s3_phoenix_trio64_onboard_pci_device); */
	return ret;
}

int
machine_ibm_aptiva_e_series_240_init(const machine_t *model)
{
	/* IBM Aptiva E Series 240 */
	/* NOTE: This is a placeholder for an IBM system that uses an ALi M1542 chipset and Acer V72MA system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerv35n/v35nd1s1.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	/* device_add(&acerm3a_device); */
	device_add(&intel_flash_bxb_device);
	return ret;
}

/* COMPAQ */
int
machine_at_compaq_deskpro_2000_init(const machine_t *model)
{
	/* COMPAQ Deskpro 2000 */
	int ret;
	ret = bios_load_linear(L"roms/machines/deskpro_2000/deskpro2000.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_compaq_deskpro_2000_2_init(const machine_t *model)
{
	/* COMPAQ Deskpro 2000 (BIOS update) */
	int ret;
	ret = bios_load_linear(L"roms/machines/deskpro_2000/deskpro2000_2.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Intel Corporation */
static void
machine_at_thor_common_init(const machine_t *model, int mr)
{
    machine_at_common_init_ex(model, mr);
    pci_init(PCI_CONFIG_TYPE_1);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
    pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
    pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
    pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 2, 1);
    pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 3, 2, 1);
    pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
    device_add(&i430fx_device);
    device_add(&piix_device);
    device_add(&keyboard_ps2_ami_pci_device);
    device_add(&pc87306_device);
    device_add(&intel_flash_bxt_ami_device);
}

int
machine_at_thor_init(const machine_t *model)
{
    /* Intel Advanced/ATX (Thor) */
	int ret;
    ret = bios_load_linear_combined(L"roms/machines/thor/1006cn0_.bio",
				    L"roms/machines/thor/1006cn0_.bi1", 0x20000, 128);
    if (bios_only || !ret)
	return ret;
    machine_at_thor_common_init(model, 0);
    return ret;
}

int
machine_at_mrthor_init(const machine_t *model)
{
    /* Intel Advanced/ATX (Thor) (MR BIOS) */
	int ret;
    ret = bios_load_linear(L"roms/machines/mrthor/mr_atx.bio",
			   0x000e0000, 131072, 0);
    if (bios_only || !ret)
	return ret;
    machine_at_thor_common_init(model, 1);
    return ret;
}

int
machine_at_tc430hx_init(const machine_t *model)
{
	/* Intel TC430HX (Tucson) */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/tc430hx/1007dh0_.bio",
		L"roms/machines/tc430hx/1007dh0_.bi1",
		L"roms/machines/tc430hx/1007dh0_.bi2",
		L"roms/machines/tc430hx/1007dh0_.bi3",
		L"roms/machines/tc430hx/1007dh0_.rcv",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ym430tx_init(const machine_t *model)
{
	/* Intel YM430TX */
	int ret;
	ret = bios_load_linear(L"roms/machines/ym430tx/YM430TX.003",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init_ex(model, 2);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x01, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);	/* PIIX4 */
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430tx_device);
	device_add(&piix4_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83977tf_device);
	device_add(&intel_flash_bxt_device);
	spd_register(SPD_TYPE_SDRAM, 0x3, 128);
	return ret;
}

/* Aberdeen */
int
machine_at_aberdeen_p133_pci_init(const machine_t *model)
{
	/* Aberdeen P133-PCI */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton) */
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/aberdeen_p133_pci/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_aberdeen_p133_pci2_init(const machine_t *model)
{
	/* Aberdeen P133-PCI (ORIGINAL BIOS) */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton) */
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/aberdeen_p133_pci/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Acer (including AcerOpen/AOpen) */
int
machine_at_acerv35_init(const machine_t *model)
{
	/* Acer AcerPower Pentium 200MHz */
	/* NOTE: This machine uses an Acer V35  system board with an Intel 82430HX (Triton II) chipset and Acer */
	/*       BIOS                                                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerv35n/v35_1e1.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	/* device_add(&acerm3a_device); */
	/* device_add(&intel_flash_bxb_device); */
	device_add(&sst_flash_29ee010_device);
	return ret;
}

int
machine_at_acerv35r0_init(const machine_t *model)
{
	/* Acer AcerPower Pentium 200MHz (R01-E1 R0) */
	/* NOTE: This machine uses an Acer V35  system board with an Intel 82430HX (Triton II) chipset and Acer */
	/*       BIOS                                                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerv35n/v35_1e1r0.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	/* device_add(&acerm3a_device); */
	/* device_add(&intel_flash_bxb_device); */
	device_add(&sst_flash_29ee010_device);
	return ret;
}

int
machine_at_acerv35n_init(const machine_t *model)
{
	/* Acer AcerPower 9536WM */
	/* NOTE: This machine uses an Acer V35N system board with an Intel 82430HX (Triton II) chipset and Acer */
	/*       BIOS                                                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerv35n/v35nd1s1.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	/* device_add(&acerm3a_device); */
	/* device_add(&intel_flash_bxb_device); */
	device_add(&sst_flash_29ee010_device);
	return ret;
}

int
machine_at_acerv35nc0_init(const machine_t *model)
{
	/* Acer AcerPower 9536WM (R01-C0 R3) */
	/* NOTE: This machine uses an Acer V35N system board with an Intel 82430HX (Triton II) chipset and Acer */
	/*       BIOS                                                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerv35n/v35nc0r3.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	/* device_add(&acerm3a_device); */
	/* device_add(&intel_flash_bxb_device); */
	device_add(&sst_flash_29ee010_device);
	return ret;
}

int
machine_at_acerv35nd1_init(const machine_t *model)
{
	/* Acer AcerPower 9536WM (R01-D1   ) */
	/* NOTE: This machine uses an Acer V35N system board with an Intel 82430HX (Triton II) chipset and Acer */
	/*       BIOS                                                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerv35n/v35n_d1.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	/* device_add(&acerm3a_device); */
	/* device_add(&intel_flash_bxb_device); */
	device_add(&sst_flash_29ee010_device);
	return ret;
}

int
machine_at_acerv35ns1_init(const machine_t *model)
{
	/* Acer AcerPower 9536WM        (R01-D1 S1) */
	/* Acer AcerPower Network Ready (R01-D1 S1) */
	/* Acer AcerPower 5505WM        (R01-D1 S1) */
	/* NOTE: These machines use an Acer V35N system board with an Intel 82430HX (Triton II) chipset and Acer */
	/*       BIOS                                                                                            */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerv35n/v35nd1s1.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	/* device_add(&acerm3a_device); */
	/* device_add(&intel_flash_bxb_device); */
	device_add(&sst_flash_29ee010_device);
	return ret;
}

int
machine_at_acerv35lan_init(const machine_t *model)
{
	/* Acer AcerPower Network Ready             */
	/* Acer AcerPower 5505WM                    */
	/* NOTE: These machines use an Acer V35LAN system board with an Intel 82430HX (Triton II) chipset and Acer */
	/*       BIOS                                                                                              */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerv35n/r01-e0.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	/* device_add(&acerm3a_device); */
	/* device_add(&intel_flash_bxb_device); */
	device_add(&sst_flash_29ee010_device);
	return ret;
}

int
machine_at_acerm3a_init(const machine_t *model)
{
	/* Acer AcerPower Ultima */
	/* Acer AcerAltos 300    */
	/* NOTE: These machines use an Acer M3a system board with an Intel 82430HX (Triton II) chipset and Acer */
	/*       BIOS                                                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerm3a/r01-b3.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x10, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	/* device_add(&acerm3a_device); */
	/* device_add(&intel_flash_bxb_device); */
	device_add(&sst_flash_29ee010_device);
	return ret;
}

/* ACMA */
int
machine_at_acma_z_power_100_133_init(const machine_t *model)
{
	/* ACMA z-Power 100 */
	/* ACMA z-Power 133 */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.02.CB0).                                                       */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/acma_z-power_100_133/1002CB0_.BIO",
		L"roms/machines/acma_z-power_100_133/1002CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_acma_zpower_133_166_init(const machine_t *model)
{
	/* ACMA zPower 133 */
	/* ACMA zPower 166 */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS.                                                                     */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/acma_zpower_133_166/1004CB0_.BIO",
		L"roms/machines/acma_zpower_133_166/1004CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_acma_exp200_init(const machine_t *model)
{
	/* ACMA EXP200 */
	/* NOTE: This uses an Intel TC430HX (Tuscon) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/acma_exp200/1006DH0_.BIO",
		L"roms/machines/acma_exp200/1006DH0_.BI1",
		L"roms/machines/acma_exp200/1006DH0_.BI2",
		L"roms/machines/acma_exp200/1006DH0_.BI3",
		L"roms/machines/acma_exp200/1006DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* All Computer Warehouse */
int
machine_at_acw_p5_120v_init1(const machine_t *model)
{
	/* All Computer Warehouse ACW P5-120V */
	/* NOTE: These machines use an Asus P/I-P55TP4 system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/acw_p5_120v/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_acw_p5_120v_init2(const machine_t *model)
{
	/* All Computer Warehouse ACW P5-120V */
	/* NOTE: These machines use an Asus P/I-P55TP4 system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/acw_p5_120v/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_acw_p5_120v_init3(const machine_t *model)
{
	/* All Computer Warehouse ACW P5-120V */
	/* NOTE: These machines use an Asus P/I-P55TP4 system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/acw_p5_120v/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_acw_p5_120v_init(const machine_t *model)
{
	/* All Computer Warehouse ACW P5-120V */
	/* NOTE: This machine uses an Asus P/I-P55TP4 system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/acw_p5_120v/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_acw_p5_133b_init(const machine_t *model)
{
	/* All Computer Warehouse ACW Pentium P5-133B */
	/* NOTE: This machine uses an Asus P/I-P55TP4 system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/acw_p5_120v/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_acw_p5_120hb_init(const machine_t *model)
{
	/* All Computer Warehouse ACW Pentium P5-120HB */
	/* NOTE: This machine uses an Asus P/I-P55TP4 system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/acw_p5_120v/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_acw_p5_166bp_init(const machine_t *model)
{
	/* All Computer Warehouse ACW P5-166BP */
	/* NOTE: These machines use a Tyan Titan I (S1461) or Titan II (S1468) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/acw_p5_166bp/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* AMAX Engineering */
int
machine_at_amax_p100_p133_init(const machine_t *model)
{
	/* AMAX PowerStation P100 */
	/* AMAX PowerStation P133 */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.02.CB0).                                                       */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/amax_p100_p133/1002CB0_.BIO",
		L"roms/machines/amax_p100_p133/1002CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_amax_p133f_p166f_init(const machine_t *model)
{
	/* AMAX PowerStation  133F */
	/* AMAX PowerStation  166F */
	/* NOTE: These machines use a Freetech 586F52 system board manufactured under the Impression brand name as the */
	/*       Impression Serenity with an Intel 82430DX (Triton) chipset and Award BIOS.                            */
	int ret;
	ret = bios_load_linear(L"roms/machines/amax_p133f_p166f/p200io-e.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* AME (Advanced Micro Electronics */
int
machine_at_ame_pentium_intel_triton_init(const machine_t *model)
{
	/* AME Pentium Intel Pentium */
	/* NOTE: This machine appears to use an Asus P/I-P55TP4 system board with an Intel 82430FX (Triton) chipset and*/
	/*       Award BIOS.                                                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/ame_pentium_intel_triton/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_ame_supermicro_p55_pci_init(const machine_t *model)
{
	/* AME SuperMicro P55 PCI */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton) */
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/ame_supermicro_p55_pci/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_ame_supermicro_p55_pci2_init(const machine_t *model)
{
	/* AME SuperMicro P55 PCI (ORIGINAL BIOS) */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton) */
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/ame_supermicro_p55_pci/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* American Multisystems */
int
machine_at_infogold_p90_init(const machine_t *model)
{
	/* American Multisystems InfoGold P90 */
	/* NOTE: This machine uses an Asus P/I-P55TP4 system board with an Intel 82430FX (Triton) chipset and Award*/
	/*       BIOS (07/04/1995).                                                                                */
	int ret;
	ret = bios_load_linear(L"roms/machines/american_multisystems_infogold_p90/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* AOpen (AcerOpen) */
int
machine_at_ap53_init(const machine_t *model)
{
	/* AOpen AP53 */
	int ret;
	ret = bios_load_linear(L"roms/machines/ap53/ap53r2c0.rom",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_ONBOARD, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Arrow Electronics (LOCAL RETAILER) */
int
machine_at_arrow_rev_j_init(const machine_t *model)
{
	/* Arrow Rev J (BIOS version 1.00.07.DB0) */
	/* NOTE:   This machine was manufactured by a company called Arrow Electronics, which appears to have been */
	/*         a local retailer based out of Wisconsin. The specifications for this machine were retrieved from*/
	/*         an eBay listing for a Milwaukee-based seller.                                                   */
	/*                                                                                                         */
	/* NOTE 2: This machine uses an Intel Advanced/ML (ML430HX) (Marl) system board                            */
	/* NOTE 3: The 1.00.06.DB0 BIOS version is used until the original 1.00.07.DB0 BIOS is available           */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/arrow_rev_j/1006DB0_.BIO",
		L"roms/machines/arrow_rev_j/1006DB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* AST Research */
int
machine_at_adventure_init(const machine_t *model)
{
	/* AST Advantage! Adventure 225 */
	int ret;
	/* ret = bios_load_linear(L"roms/machines/adventure/FM530260.SST",
	0x000e0000, 131072, 0); */
	ret = bios_load_linear(L"roms/machines/adventure/bios-ast-adventure-225.rom",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x17, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x19, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430vx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c932fr_device);
	device_add(&intel_flash_bxb_ast_device);
	return ret;
}

int
machine_at_ast_advantage_818_init(const machine_t *model)
{
	/* AST Advantage! 8100p */
	/* NOTE 2: This machine will use the Advantage! 8100p BIOS until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ast_advantage_8100p/1006BT0Q.BIO",
		L"roms/machines/ast_advantage_8100p/1006BT0Q.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	/* pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0); */
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ast_bravo_ms_t_5200_init(const machine_t *model)
{
	/* AST Bravo MS-T 5200 */
	/* NOTE: This machine uses an Intel Advanced/RH (RH430HX) (Rhinestone) system board */
	/* NOTE 2: The AST Advantage! 9312 BIOS is used until an original BIOS dump is available */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ast_advantage_9320/1005DL0Q.BIO",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI1",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI2",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI3",
		L"roms/machines/tc430hx/1007DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ast_advantage_9312_init(const machine_t *model)
{
	/* AST Advantage! 9312 Communications (BIOS version 1.00.05.DL0Q) */
	/* NOTE: This machine uses an Intel Advanced/RU (RU430HX) (Ruby) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ast_advantage_9320/1005DL0Q.BIO",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI1",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI2",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI3",
		L"roms/machines/tc430hx/1007DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ast_advantage_9312_06_init(const machine_t *model)
{
	/* AST Advantage! 9312 Communications (BIOS version 1.00.06.DL0Q) */
	/* NOTE: This machine uses an Intel Advanced/RU (RU430HX) (Ruby) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ast_advantage_9320/1006DL0Q.BIO",
		L"roms/machines/ast_advantage_9320/1006DL0Q.BI1",
		L"roms/machines/ast_advantage_9320/1006DL0Q.BI2",
		L"roms/machines/ast_advantage_9320/1006DL0Q.BI3",
		L"roms/machines/tc430hx/1007DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ast_advantage_9314_init(const machine_t *model)
{
	/* AST Advantage! 9314 (BIOS version 1.00.05.DL0Q) */
	/* NOTE: This machine uses an Intel Advanced/RU (RU430HX) (Ruby) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ast_advantage_9320/1005DL0Q.BIO",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI1",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI2",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI3",
		L"roms/machines/tc430hx/1007DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ast_advantage_9314_06_init(const machine_t *model)
{
	/* AST Advantage! 9314 (BIOS version 1.00.06.DL0Q) */
	/* NOTE: This machine uses an Intel Advanced/RU (RU430HX) (Ruby) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ast_advantage_9320/1006DL0Q.BIO",
		L"roms/machines/ast_advantage_9320/1006DL0Q.BI1",
		L"roms/machines/ast_advantage_9320/1006DL0Q.BI2",
		L"roms/machines/ast_advantage_9320/1006DL0Q.BI3",
		L"roms/machines/tc430hx/1007DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ast_advantage_9320_init(const machine_t *model)
{
	/* AST Advantage! 9320 (BIOS version 1.00.05.DL0Q) */
	/* NOTE: This machine uses an Intel Advanced/RU (RU430HX) (Ruby) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ast_advantage_9320/1005DL0Q.BIO",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI1",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI2",
		L"roms/machines/ast_advantage_9320/1005DL0Q.BI3",
		L"roms/machines/tc430hx/1007DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ast_advantage_9320_06_init(const machine_t *model)
{
	/* AST Advantage! 9320 (BIOS version 1.00.06.DL0Q) */
	/* NOTE: This machine uses an Intel Advanced/RU (RU430HX) (Ruby) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ast_advantage_9320/1006DL0Q.BIO",
		L"roms/machines/ast_advantage_9320/1006DL0Q.BI1",
		L"roms/machines/ast_advantage_9320/1006DL0Q.BI2",
		L"roms/machines/ast_advantage_9320/1006DL0Q.BI3",
		L"roms/machines/tc430hx/1007DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* Austin (IPC) */
int
machine_at_austin_powerplus_133_dh0_init(const machine_t *model)
{
	/* Austin PowerPLUS 133 (BIOS version 1.00.04.DH0) */
	/* NOTE: This uses an Intel TC430HX (Tuscon) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/austin_powerplus_200/1004DH0_.BIO",
		L"roms/machines/austin_powerplus_200/1004DH0_.BI1",
		L"roms/machines/austin_powerplus_200/1004DH0_.BI2",
		L"roms/machines/austin_powerplus_200/1004DH0_.BI3",
		L"roms/machines/austin_powerplus_200/1004DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_austin_powerplus_166_dh0_init(const machine_t *model)
{
	/* Austin PowerPLUS 166 (BIOS version 1.00.04.DH0) */
	/* NOTE: This uses an Intel TC430HX (Tuscon) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/austin_powerplus_200/1004DH0_.BIO",
		L"roms/machines/austin_powerplus_200/1004DH0_.BI1",
		L"roms/machines/austin_powerplus_200/1004DH0_.BI2",
		L"roms/machines/austin_powerplus_200/1004DH0_.BI3",
		L"roms/machines/austin_powerplus_200/1004DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_austin_powerplus_200_init(const machine_t *model)
{
	/* Austin PowerPLUS 200 */
	/* NOTE: This uses an Intel TC430HX (Tuscon) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/austin_powerplus_200/1004DH0_.BIO",
		L"roms/machines/austin_powerplus_200/1004DH0_.BI1",
		L"roms/machines/austin_powerplus_200/1004DH0_.BI2",
		L"roms/machines/austin_powerplus_200/1004DH0_.BI3",
		L"roms/machines/austin_powerplus_200/1004DH0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* Blue Star */
int
machine_at_blue_star_eclipse_e_133_166_init(const machine_t *model)
{
	/* Blue Star Eclipse E-133 */
	/* Blue Star Eclipse E-166 */
	/* NOTE: These machines use a Tyan Titan I (S1461) or Titan II (S1468) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/blue_star_eclipse_e_133_166/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Caliber */
int
machine_at_caliber_voyager_iii_150_init(const machine_t *model)
{
	/* Caliber Voyager III 150 */
	/* NOTE: This machine uses an Asus P/I-P55TP4 system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/caliber_voyager_iii_150/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_caliber_voyager_v_mmx_init(const machine_t *model)
{
	/* Caliber Voyager V MMX */
	/* NOTE: This machine uses an Abit IT5V system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/caliber_voyager_v_mmx/IT5V_3J.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430vx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&um8669f_device); /* Substitute for ALi M5123 until latter is added */
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* CompuLink Research (CLR) */
int
machine_at_clr_infinity_p5_init(const machine_t *model)
{
	/* CLR Infinity P5-75E    */
	/* CLR Infinity P5-75H    */
	/* CLR Infinity P5-100EDO */
	/* CLR Infinity P5-120EDO */
	/* CLR Infinity P5-133EDO */
	/* CLR Infinity P5-166EDO */
	/* NOTE: These machines use an Asus P/I-P55TP4 system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (4.50G).                                                                                       */
	int ret;
	ret = bios_load_linear(L"roms/machines/clr_infinity_p5/PT5BXH.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_clr_infinity_p5d_init(const machine_t *model)
{
	/* CLR Infinity P5D100E   */
	/* CLR Infinity P5D120EDO */
	/* CLR Infinity P5D150EDO */
	/* NOTE: These machines use an Asus P/I-P55TP4XE system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (01/24/1996).                                                                                    */
	int ret;
	ret = bios_load_linear(L"roms/machines/clr_infinity_p5d/PD5115.SMC",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	/* Award BIOS, SMC FDC37C665. */
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Computer (LOCAL RETAILER) */
int
machine_at_computer_pentium_133_mhz_init(const machine_t *model)
{
	/* Computer Pentium 133 MHz */
	/* NOTE: This machine uses an M Technology R533WP system board with an Intel 82430VX (Triton II) chipset and*/
	/*       Award BIOS.                                                                                        */
	/* NOTE 2: The M Technology R525W2 ROM BIOS is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/computer_pentium_133_mhz/r525es.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430vx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* CompuTrend */
/* See Premio */

/* Comtrade */
int
machine_at_comtrade_multimedia_mpeg_init(const machine_t *model)
{
	/* Comtrade Multimedia MPEG Dream Machine */
	/* Comtrade Multimedia Best Buy           */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/comtrade_multimedia_best_buy/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_comtrade_multimedia_mpeg2_init(const machine_t *model)
{
	/* Comtrade Multimedia MPEG Dream Machine (ORIGINAL BIOS) */
	/* Comtrade Multimedia Best Buy           (ORIGINAL BIOS) */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/comtrade_multimedia_best_buy/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_comtrade_3d_game_station_8x_init(const machine_t *model)
{
	/* Comtrade 3D Game Station 8X    */
	/* Comtrade Artists Dream Machine */
	/* Comtrade Hyperspeed Multimedia */
	/* NOTE: These machines use a Tyan Titan I (S1461) or Titan II (S1468) system board with an Intel 82430FX */
	/*       (Triton) chipset and Award BIOS (4.50G).                                                         */
	int ret;
	ret = bios_load_linear(L"roms/machines/comtrade_3d_game_station_8x/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_comtrade_wide_scsi_init(const machine_t *model)
{
	/* Comtrade Wide SCSI Powerstation */
	/* NOTE: This machine uses a DataExpert EXP8551 system board with an Intel 82430VX (Triton II) chipset and */
	/*       AMIBIOS (10/10/1994).                                                                             */
	int ret;
	ret = bios_load_linear(L"roms/machines/comtrade_wide_scsi_powerstation/85521.BIO",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device); /* Substitute for Winbond W83787F */
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* CyberMax */
/* See Quantex Microsystems */

/* DataStor (Data Storage Marketing) */
int
machine_at_datastor_p5_100_133_166_init(const machine_t *model)
{
	/* DataStor P5-100 */
	/* DataStor P5-133 */
	/* DataStor P5-166 */
	/* NOTE: These machines use an ECS (Elitegroup Computer Systems) TS54P system board with an Intel 430FX */
	/*       (Triton) chipset and Phoenix BIOS.                                                             */
	int ret;
	ret = bios_load_linear(L"roms/machines/datastor_p5_100_p5_133_p5_166/TSVIO27B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	/* device_add(&um8669f_device); */
	device_add(&fdc37c665_device);
	/* device_add(&sst_flash_29ee010_device); */
	/* device_add(&intel_flash_bxt_device); */
	return ret;
}

/* Dell Computer (formerly PC's Limited) */
int
machine_at_dell_dimension_xps_p133c_init(const machine_t *model)
{
	/* Dell Dimension P75t      */
	/* Dell Dimension P90t      */
	/* Dell Dimension P100t     */
	/* Dell Dimension P120t     */
	/* Dell Dimension P133t     */
	/* Dell Dimension XPS P75c  */
	/* Dell Dimension XPS P90c  */
	/* Dell Dimension XPS P100  */
	/* Dell Dimension XPS P100c */
	/* Dell Dimension XPS P120c */
	/* Dell Dimension XPS P133c */
	/* Dell Dimension XPS P166c */
	/* NOTE: These machines use an Intel Advanced/CM (Comanche) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS                                                                      */
	int ret;
	ret = bios_load_linear(L"roms/machines/dell_dimension_p100_p133_p166/DELLP100T.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

int
machine_at_dell_dimension_xps_p166v_init(const machine_t *model)
{
	/* Dell Dimension XPS P166v */
	/* Dell Dimension XPS P200v */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/dell_dimension_p166v_p200v/1005CY0J.BIO",
		L"roms/machines/dell_dimension_p166v_p200v/1005CY0J.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	/* pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0); */
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430vx_device);
	device_add(&piix_device);
	device_add(&fdc37c932fr_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_dell_optiplex_gxmt_init(const machine_t *model)
{
	/* Dell OptiPlex GL+   575  */
	/* Dell OptiPlex GM+   5100 */
	/* Dell OptiPlex GXMT+ 5133 */
	/* Dell OptiPlex GXMT  5133 */
	/* Dell OptiPlex GXMT  5166 */
	/* Dell OptiPlex GXM   5100 */
	/* NOTE: These machines will use the Dell Dimension BIOS until an original BIOS dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/dell_dimension_p100_p133_p166/DELLP100T.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

/* Diamond */
int
machine_at_diamond_dt100_dt133_init(const machine_t *model)
{
	/* Diamond Office    Star   DT100 */
	/* Diamond Office   Master  DT133 */
	/* Diamond Office    Mate     133 */
	/* Diamond Office Intelligent 166 */
	/* NOTE: These machines use an Asus P/I-P55TP4 system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (05/12/1995).                                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/diamond_dt100_dt133/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Digital (DEC) */
int
machine_at_digital_celebris_gl_init(const machine_t *model)
{
	/* Digital Celebris GL 5100ST */
	/* Digital Celebris GL 5120ST */
	/* Digital Celebris GL 5133ST */
	/* Digital Celebris GL 5150ST */
	/* Digital Celebris GL 5166ST */
	/* NOTE: These machines use a system board with an Intel 430FX (Triton) chipset and Phoenix ROM BIOS (4.04). */
	int ret;
	ret = bios_load_linear(L"roms/machines/digital_celebris_gl/CELEBRIS.ROM",
		0x000c0000, 262144, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	/* device_add(&sst_flash_29ee020_device); */
	/* device_add(&intel_flash_bxt_ami_device); */
	return ret;
}

/* DirectWave */
int
machine_at_directwave_blue_thunder_tr_init(const machine_t *model)
{
	/* DirectWave Blue Thunder Triton PT5P120B */
	/* DirectWave Blue Thunder Triton PT5P133B */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/directwave_blue_thunder_triton/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_directwave_blue_thunder_tr2_init(const machine_t *model)
{
	/* DirectWave Blue Thunder Triton PT5P120B (ORIGINAL BIOS) */
	/* DirectWave Blue Thunder Triton PT5P133B (ORIGINAL BIOS) */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/directwave_blue_thunder_triton/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_directwave_blue_thunder_init(const machine_t *model)
{
	/* DirectWave Blue Thunder        PT5P100B      */
	/* DirectWave Blue Thunder        PT5P100BMVP   */
	/* DirectWave Blue Thunder        PT5P133B      */
	/* DirectWave Blue Thunder        PHX133MVP Pro */
	/* NOTE: These machines use an Asus P/I-P55TP4 system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (05/12/1995 for the first three systems).                                                      */
	int ret;
	ret = bios_load_linear(L"roms/machines/directwave_blue_thunder/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_directwave_blue_thunder_ph_init(const machine_t *model)
{
	/* DirectWave Blue Thunder PH166MVP Pro */
	/* NOTE: This machine uses an ASUS P/I-P55T2P4 system board with an Intel 430HX (Triton II) chipset and Award */
	/*       BIOS.                                                                                                */
	int ret;
	ret = bios_load_linear(L"roms/machines/directwave_blue_thunder_ph166mvp_pro/T25I0106.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_dtk_quin_54_init(const machine_t *model)
{
	/* DTK QUIN-54M/P100    */
	/* DTK QUIN-54M/P120    */
	/* DTK QUIN-54M/P133    */
	/* DTK QUIN-54M/P150    */
	/* DTK QUIN-54M/P166    */
	/* DTK QUIN-54 (v1.06)  */
	/* NOTE: These machines use a DTK PAM-0054I system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (4.50G).                                                                                    */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_54/54E0N106.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_dtk_quin_54_111_init(const machine_t *model)
{
	/* DTK Quin-54 (v1.11) */
	/* NOTE: This machine uses a DTK PAM-0054I system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (4.50G).                                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_54/54e0i111.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_dtk_quin_54_112_init(const machine_t *model)
{
	/* DTK Quin-54 (v1.12) */
	/* NOTE: This machine uses a DTK PAM-0054I system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (4.50G).                                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_54/54e0h112.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_dtk_quin_54_113_init(const machine_t *model)
{
	/* DTK Quin-54 (v1.13) */
	/* NOTE: This machine uses a DTK PAM-0054I system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (4.50G).                                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_54/54E0O113.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_dtk_quin_54_122_init(const machine_t *model)
{
	/* DTK Quin-54 (v1.22) */
	/* NOTE: This machine uses a DTK PAM-0054I system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (4.50G).                                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_54/54e0l122.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_dtk_quin_54_212_init(const machine_t *model)
{
	/* DTK Quin-54 (v2.12) */
	/* NOTE: This machine uses a DTK PAM-0054I system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (4.50G).                                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_54/54e1k212.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_dtk_quin_54_232_init(const machine_t *model)
{
	/* DTK Quin-54 (v2.32) */
	/* NOTE: This machine uses a DTK PAM-0054I system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (4.50G).                                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_54/54e1j232.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_dtk_quin_55_amibios_init(const machine_t *model)
{
	/* DTK QUIN-55D/P75  (AMIBIOS)    */
	/* DTK QUIN-55D/P100 (AMIBIOS)    */
	/* DTK QUIN-55D/P120 (AMIBIOS)    */
	/* DTK QUIN-55D/P133 (AMIBIOS)    */
	/* DTK QUIN-55D/P150 (AMIBIOS)    */
	/* DTK QUIN-55D/P166 (AMIBIOS)    */
	/* DTK QUIN-55M/P75  (AMIBIOS)    */
	/* DTK QUIN-55M/P100 (AMIBIOS)    */
	/* DTK QUIN-55M/P120 (AMIBIOS)    */
	/* DTK QUIN-55M/P133 (AMIBIOS)    */
	/* DTK QUIN-55M/P150 (AMIBIOS)    */
	/* DTK QUIN-55M/P166 (AMIBIOS)    */
	/* NOTE: These machines use a DTK PAM-0055I system board with an Intel 430HX (Triton II) chipset and AMIBIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_55/55i106a.rom",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	/* device_add(&sst_flash_29ee010_device); */
	/* device_add(&intel_flash_bxt_device); */
	return ret;
}

int
machine_at_dtk_quin_55_award_bios_init(const machine_t *model)
{
	/* DTK QUIN-55D/P75  (Award BIOS) */
	/* DTK QUIN-55D/P100 (Award BIOS) */
	/* DTK QUIN-55D/P120 (Award BIOS) */
	/* DTK QUIN-55D/P133 (Award BIOS) */
	/* DTK QUIN-55D/P150 (Award BIOS) */
	/* DTK QUIN-55D/P166 (Award BIOS) */
	/* DTK QUIN-55M/P75  (Award BIOS) */
	/* DTK QUIN-55M/P100 (Award BIOS) */
	/* DTK QUIN-55M/P120 (Award BIOS) */
	/* DTK QUIN-55M/P133 (Award BIOS) */
	/* DTK QUIN-55M/P150 (Award BIOS) */
	/* DTK QUIN-55M/P166 (Award BIOS) */
	/* NOTE: These machines use a DTK PAM-0055I system board with an Intel 430HX (Triton II) chipset and Award */
	/*       BIOS.                                                                                             */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_55/5WHPG105.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* DTK PAM-0054I */
/* See DTK QUIN-54M */

/* DTK PAM-0055I */
/* See DTK QUIN-55D or DTK QUIN-55M */

/* Empac International */
int
machine_at_empac_saber_p54_100_init(const machine_t *model)
{
	/* Empac Saber P54-100 */
	/* Empac Talon  HS-100 */
	/* NOTE: These machines use an AOpen AP5C or AP5C/P system board with an Intel 430FX chipset and AMIBIOS */
	/*       (10/10/1994).                                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/empac_saber_p54_100/AP5C180A.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* EPS Technologies */
int
machine_at_eps_pinnacle_p90_p133_init(const machine_t *model)
{
	/* EPS Pinnacle    P90   */
	/* EPS Pinnacle    P120  */
	/* EPS Pinnacle    P133  */
	/* EPS Evolution   P-166 */
	/* EPS Evolution  LP-133 */
	/* EPS Evolution XLP-166 */
	/* NOTE: These machines use an FIC (First International Computer) PT-2000 system board with an Intel 82430FX  */
	/*    (Triton) chipset and Award BIOS (04/18/1995 for the first system and 07/03/1995 for the second system). */
	int ret;
	ret = bios_load_linear(L"roms/machines/eps_pinnacle_p90_p133/306C800.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Everex Systems */
int
machine_at_everex_step_pro_133_init(const machine_t *model)
{
	/* Everex Step Pro 133 */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.02.CB0).                                                      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/everex_step_pro_133/1002CB0_.BIO",
		L"roms/machines/everex_step_pro_133/1002CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_everex_step_premier_init(const machine_t *model)
{
	/* Everex Step Premier 133 */
	/* Everex Step Premier 166 */
	/* NOTE: These machines use an FIC (First International Computer) PT-2200 system board with an Intel 430HX */
	/*       (Triton II) chipset and AMIBIOS.                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/everex_step_premier/TII103.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Future Micro */
int
machine_at_future_micro_intel_endeavor_init(const machine_t *model)
{
	/* Future Micro Intel Endeavor */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS.                                                                    */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/future_micro_intel_endeavor/1002CB0_.BIO",
		L"roms/machines/future_micro_intel_endeavor/1002CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* Gateway 2000 */
int
machine_at_gateway_p5_cn0t_init(const machine_t *model)
{
	/* Gateway 2000 P5-75              (AMIBIOS version CN0T) */
	/* Gateway 2000 P5-100 Family PC   (AMIBIOS version CN0T) */
	/* Gateway 2000 P5-120             (AMIBIOS version CN0T) */
	/* Gateway 2000 P5-120 Family PC   (AMIBIOS version CN0T) */
	/* Gateway 2000 P5-133             (AMIBIOS version CN0T) */
	/* Gateway 2000 P5-133XL           (AMIBIOS version CN0T) */
	/* Gateway 2000 P5-133 Family PC   (AMIBIOS version CN0T) */
	/* Gateway 2000 P5-166             (AMIBIOS version CN0T) */
	/* Gateway 2000 P5-166XL                                  */
	/* Gateway 2000 P5-166 Family PC                          */
	/* Gateway 2000 P5-200                                    */
	/* Gateway 2000 P5-200XL                                  */
	/* Gateway 2000 P5-200 Family PC                          */
	/* Gateway 2000 Destination D5-120                        */
	/* Gateway 2000 Destination D5-133                        */
	/* Gateway 2000 Destination D5-166 (AMIBIOS version CN0T) */
	/* Gateway 2000 Destination D5-200 (AMIBIOS version CN0T) */
	/* NOTE: These machines use an Intel Advanced/ATX (Thor) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/gateway_p5_fpc/101.bio",
		L"roms/machines/gateway_p5_fpc/101.bi1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_thor_common_init(model, 0);
	return ret;
}

/* Golden Star Technology */
int
machine_at_gst_apogee_p133_init(const machine_t *model)
{
	/* GST Apogee P133 */
	/* NOTE: These machines use a Tyan Titan I (S1461) or Titan II (S1468) system board with an Intel 82430FX */
	/*       (Triton) chipset and Award BIOS (04/29/1995).                                                    */
	int ret;
	ret = bios_load_linear(L"roms/machines/gst_apogee_p133/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_gst_aapogee_p133_init(const machine_t *model)
{
	/* GST            Aapogee P133 (Intel AMIBIOS) */
	/* GST/Micro City Aapogee 8000Pt               */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (05/10/1995 for the first system and 05/17/1995/1.00.02.CB0 for the  */
	/*       second system).                                                                                */
	/* NOTE 2: The second system's BIOS is used for the first system until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/gst_aapogee_p133/1002CB0_.BIO",
		L"roms/machines/gst_aapogee_p133/1002CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

int
machine_at_gst_aapogee_p133_award_init(const machine_t *model)
{
	/* GST            Aapogee P133 (Award    BIOS) */
	/* NOTE: This machine uses an Asus P/I-P55TP4 system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS.                                                                                              */
	int ret;
	ret = bios_load_linear(L"roms/machines/gst_aapogee_p133/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_gst_aapogee_p166_init(const machine_t *model)
{
	/* GST            Aapogee P166                 */
	/* NOTE: This machine uses an ASUS P/I-P55T2P4 system board with an Intel 430HX (Triton II) chipset and Award */
	/*       BIOS.                                                                                                */
	int ret;
	ret = bios_load_linear(L"roms/machines/gst_aapogee_p166/T25I0106.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* HD Systems */
int
machine_at_hd_victoria_p133_init(const machine_t *model)
{
	/* HD Victoria P133 */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                  */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/hd_victoria_p133/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_hd_victoria_p1332_init(const machine_t *model)
{
	/* HD Victoria P133 (original BIOS) */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/hd_victoria_p133/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_hd_victoria_p_120_p_166_init(const machine_t *model)
{
	/* HD Victoria P-120 */
	/* HD Victoria P-166 */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS.                                                                     */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hd_victoria_p_120_p_166/1004CB0_.BIO",
		L"roms/machines/hd_victoria_p_120_p_166/1004CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

/* Hertz Computer Corporation */
/* Hertz        P90e  */
/* Hertz        P100e */
/* Hertz        P133e */
/* Hertz Z-Pent P133e */
/* Hertz Z-Pent P166e */
/* NOTE: See m_at_socket4_5.c (Hertz P100e) */

/* Hewlett-Packard */
int
machine_at_hp_pavilion_7130p_init(const machine_t *model)
{
	/* HP Pavilion 7090  (7130p BIOS) */
	/* HP Pavilion 7130p              */
	/* NOTE: The HP Pavilion 7130p uses an Intel Advanced/MN LPX/S (Talledega) system board with an Intel */
	/*       82430FX (Triton) chipset and Intel AMIBIOS (1.00.02.CH0L)                                    */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hp_pavilion_7130p/1002CH0L.BIO",
		L"roms/machines/hp_pavilion_7130p/1002CH0L.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_thor_common_init(model, 0);
	return ret;
}

int
machine_at_pavl7320_init(const machine_t *model)
{
	/* HP Pavilion 7320  */
	/* HP Pavilion 7330z */
	/* NOTE: These machines use an Intel Advanced/RU (Ruby) system board with an Intel 82430HX (Triton II) */
	/*       chipset and Intel AMIBIOS (1.00.05.DL0L)                                                      */
	int ret;
	ret = bios_load_linear_combined2_norcv(L"roms/machines/pavl7320/1005dl0l.bio",
		L"roms/machines/pavl7320/1005dl0l.bi1",
		L"roms/machines/pavl7320/1005dl0l.bi2",
		L"roms/machines/pavl7320/1005dl0l.bi3",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_brio80xx_init(const machine_t *model)
{
	/* HP Brio 80xx */
	int ret;
	ret = bios_load_linear(L"roms/machines/brio80xx/Hf0705.rom",
		0x000c0000, 262144, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x14, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430vx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&fdc37c935_device);
	device_add(&sst_flash_29ee020_device);
	return ret;
}

/* HiQ (HiQuality Systems) */
int
machine_at_hiq_apollo_120_133_init(const machine_t *model)
{
	/* NOTE: These machines use an Asus system board with an Intel 82430FX (Triton) chipset and Award BIOS */
	/*       (05/08/1995).                                                                                 */
	int ret;
	ret = bios_load_linear(L"roms/machines/hiq_apollo_120_133/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	/* Award BIOS, SMC FDC37C665. */
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_hiq_apollo_p133_init(const machine_t *model)
{
	/* HiQ Apollo P133 */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.02.CB0) (05/17/1995).                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hiq_apollo_p133/1002CB0_.BIO",
		L"roms/machines/hiq_apollo_p133/1002CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

int
machine_at_hiq_p133_p166_mars_station_init(const machine_t *model)
{
	/* HiQ P133 Mars Station */
	/* HiQ P166 Mars Station */
	/* NOTE: These machines use an ASUS P/I-P55T2P4 system board with an Intel 430HX (Triton II) chipset and Award */
	/*       BIOS.                                                                                                 */
	int ret;
	ret = bios_load_linear(L"roms/machines/hiq_p133_p166_mars_station/T25I0106.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* HSB Computer Laboratories */
int
machine_at_hsb_ms5120pc_series_64_bit_init(const machine_t *model)
{
	/* HSB MS5120PC Series 64-Bit PCI Bus MainBoard */
	/* NOTE: This machine uses a Micro-Star MS-5120 system board with an Intel 430FX (Triton) chipset and AMIBIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/hsb_ms5120pc_series_64_bit_pci_bus_mainboard/A37E.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Hi-Tech USA */
int
machine_at_hi_tech_usa_super_power_mpc_init(const machine_t *model)
{
	/* Hi-Tech USA Super Power MPC-120 */
	/* NOTE: This manufacturer appears to have used PC Chips system boards across much of its product line, */
	/*       including most of its non-EISA machines, and so for this reason this machine's system board is */
	/*       assumed to be a PC Chips M507 system board with an Intel 82430FX (Triton) chipset and Award    */
	/*       BIOS unless proven otherwise.                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/hi_tech_usa_super_power_mpc_120/5ifw002.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&um8669f_device); /* Placeholder for UMC UM8663BF */
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Hymco */
int
machine_at_hymco_professional_133_init(const machine_t *model)
{
	/* Hymco Professional-133 */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.02.CB0) (05/17/1995).                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hymco_professional_133/1002CB0_.BIO",
		L"roms/machines/hymco_professional_133/1002CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

/* Inteva Microsystems */
/* Inteva 5/133 */
/* See Quantex QP5 (Award BIOS) */


/* MagiPro Computers (formerly Magix Computers) */
int
machine_at_magix_office_p133_p166_init(const machine_t *model)
{
	/* Magix   Multimedia Internet */
	/* Magix     Office  P133      */
	/* Magix     Office  P166      */
	/* MagiPro Multimedia Internet */
	/* MagiPro Multimedia 133MHz   */
	/* MagiPro Multimedia 166MHz   */
	/* MagiPro   Office  P133      */
	/* NOTE: Although full information is not available for the system board that these machines used, the       */
	/*       company's description of a 256 KB cache, Plug and Play BIOS, and 64-bit accelerator with support for*/
	/*       1 MB or 2 MB of graphics memory would appear to suggest an Intel Advanced/EV (Endeavor) system board*/
	/*       with an Intel 82430FX (Triton) chipset and Intel AMIBIOS.                                           */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/magix_office_p133_p166/1004CB0_.BIO",
		L"roms/machines/magix_office_p133_p166/1004CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

/* Magix Computers */
/* See MagiPro Computers */

/* Maximus Computers */
int
machine_at_maximus_magna_graphics_pro_init(const machine_t *model)
{
	/* Maximus Magna             Media        P100 */
	/* Maximus Magna Graphics ProMedia Pentium 120 */
	/* Maximus Magna  Artist  Pro Multimedia       */
	/* Maximus Magna          ProMedia             */
	/* Maximus Magna Graphics ProMedia             */
	/* Maximus Magna Graphics                P/166 */
	/* NOTE:These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/maximus_magna_graphics_pro_media_pentium_120/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_maximus_magna_graphics_pro2_init(const machine_t *model)
{
	/* Maximus Magna             Media        P100 (original BIOS) */
	/* Maximus Magna Graphics ProMedia Pentium 120 (original BIOS) */
	/* Maximus Magna  Artist  Pro Multimedia       (original BIOS) */
	/* Maximus Magna          ProMedia             (original BIOS) */
	/* Maximus Magna Graphics ProMedia             (original BIOS) */
	/* NOTE:These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/maximus_magna_graphics_pro_media_pentium_120/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_maximus_magna_media_133_166_init(const machine_t *model)
{
	/* Maximus Magna Media P/133 */
	/* Maximus Magna Media P/166 */
	/* NOTE: These machines use a Tyan Titan I (S1461) or Titan II (S1468) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/maximus_magna_media_p_133_166/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_maximus_magna_scsi_media_init(const machine_t *model)
{
	/* Maximus Magna SCSI Media P/166 */
	/* NOTE: This machine uses an Iwill P54TSW/2 system board manufactured under the Quick Technology name with an */
	/*       Intel 430FX (Triton) chipset and Award BIOS.                                                          */
	int ret;
	ret = bios_load_linear(L"roms/machines/maximus_magna_scsi_media_p_166/TSW20105.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	/* Award BIOS, SMC FDC37C665. */
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* MDS (Marlow Data Systems) */
/* MDS    75MHz Pentium           */
/* MDS    75MHz 850MB HD PCI      */
/* MDS   120MHz Pentium PCI 1.2GB */
/* MDS 5/100 CD                   */
/* MDS 5/100 CD MiniTower         */
/* See Quantex QP5/100 M-4 */

/* Mega Computer Systems */
int
machine_at_mega_impact_590pci16d_init(const machine_t *model)
{
	/* Mega Impact  590PCI16D */
	/* Mega Impact 5133PCI16MT */
	/* NOTE: These machines use a Tyan Titan I (S1461) or Titan II (S1468) system board with an Intel 82430FX */
	/*       (Triton) chipset and Award BIOS (05/29/1995 for the first system and 07/25/1995 for the second   */
	/*       system).                                                                                         */
	int ret;
	ret = bios_load_linear(L"roms/machines/mega_impact_590pci16d/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_mega_horizon_mpc57516d_init(const machine_t *model)
{
	/* Mega Horizon MPC57516D  */
	/* Mega Impact 5133PCI16D  */
	/* Mega Impact 5166PCI16MT */
	/* NOTE: These machines use a BCM SQ595 system board with an Intel 82430FX (Triton) chipset and Award BIOS */
	/*       (08/08/1995 for the first system).                                                                */
	int ret;
	ret = bios_load_linear(L"roms/machines/mega_horizon_mpc57516d/595-a01.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Memorex Telex */
int
machine_at_memorex_telex_celerria_mini_init(const machine_t *model)
{
	/* Memorex Telex Celerria Mini Tower */
	/* NOTE: This machine uses a BCM SQ595 system board with an Intel 430FX (Triton) chipset and Award BIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/memorex_telex_celerria_mini_tower/595-a01.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Micro Express */
int
machine_at_microflex_pci_p100_init(const machine_t *model)
{
	/* Micro Express MicroFlex PCI/P100      */
	/* Micro Express MicroFlex PCI/P100 Home */
	/* Micro Express MicroFlex-686/P120+     */
	/* Micro Express MicroFlex-686/P150+     */
	/* Micro Express MicroFlex-686/P166+     */
	/* NOTE: These machines use a Tyan Titan I (S1461) or Titan II (S1468) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/microflex_pci_p100/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Micro Professionals */
int
machine_at_micro_professionals_proteva_init(const machine_t *model)
{
	/* Micro Professionals      P5/75  Pro Super Multimedia */
	/* Micro Professionals      P5/90  Pro Super Multimedia */
	/* Micro Professionals      P5/100 Pro Super Multimedia */
	/* Micro Professionals      P5/120 Pro Super Multimedia */
	/* Micro Professionals      P5/133 Pro Super Multimedia */
	/* Micro Professionals Proteva 100     Super Multimedia */
	/* NOTE: These machines use an FIC (First International Computer) PT-2000 system board with an Intel 82430FX */
	/*    (Triton) chipset and Award BIOS (09/07/1995 for the seventh system).                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/micro_professionals_proteva_100_super_multimedia/306C800.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Micron Electronics */
int
machine_at_micron_home_mpc_amibios_init(const machine_t *model)
{
	/* Micron Home MPC P166 (Intel AMIBIOS) */
	/* Micron Home MPC P200 (Intel AMIBIOS) */
	/* Micron ClientPro P100                */
	/* Micron ClientPro P120                */
	/* Micron ClientPro P200                */
	/* NOTE: These machines use an Intel Advanced/ML (Marl) system board with an Intel 82430HX (Triton II) */
	/*       chipset and Intel AMIBIOS (1.00.04.DL0L)                                                      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/micron_amibios/1009db05.bio",
		L"roms/machines/micron_amibios/1009db05.bi1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0e, PCI_CARD_NORMAL, 0, 1, 2, 3);
	pci_register_slot(0x0f, PCI_CARD_NORMAL, 1, 2, 3, 0);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 2, 3, 0, 1);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 3, 0, 1, 2);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_micron_home_mpc_init(const machine_t *model)
{
	/* Micron Home MPC P166 (Phoenix  BIOS) */
	/* Micron Home MPC P200 (Phoenix  BIOS) */
	/* NOTE: These machines use a Micronics M54Hi system board with an Intel 82430HX (Triton II) chipset   */
	/*       and Phoenix BIOS (PhoenixBIOS 4.05)                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/micron_p166_home_mpc_pro/M54HI.11",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* MidWest Micro */
int
machine_at_midwest_micro_p5_133_init(const machine_t *model)
{
	/* MidWest Micro  Home  PC P5-133 PCI */
	/* MidWest Micro Office PC P5-133 PCI */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.02.CB0).                                                       */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/midwest_micro_p5_133/1002CB0_.BIO",
		L"roms/machines/midwest_micro_p5_133/1002CB0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

int
machine_at_midwest_micro_p5_133_166_init(const machine_t *model)
{
	/* MidWest Micro P5-133 Office PC */
	/* MidWest Micro P5-166 Office PC */
	/* NOTE: These machines use an Asus P/I-P55TP4 system board with an Intel 430FX (Triton) chipset and Award */
	/*       BIOS.                                                                                             */
	int ret;
	ret = bios_load_linear(L"roms/machines/midwest_micro_p5_133_166_office_pc/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Mitsuba */
int
machine_at_mitsuba_executive_pentium_pc_init(const machine_t *model)
{
	/* Mitsuba Executive    Pentium-PC */
	/* Mitsuba Executive    P-100      */
	/* Mitsuba Executive    P-133      */
	/* Mitsuba Premier System 166      */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.02.CB0) (05/17/1995).                                          */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/mitsuba_executive_pentium_pc/1002CB0_.BIO",
		L"roms/machines/mitsuba_executive_pentium_pc/1002CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

/* Multiwave Technology */
int
machine_at_multiwave_ultra_power_init(const machine_t *model)
{
	/* Multiwave Ultra Power      */
	/* Multiwave SOHO MPEG System */
	/* NOTE: These machines use an AOpen AP5C or AP5C/P system board with an Intel 82430FX (Triton) chipset and */
	/*       AMIBIOS (10/10/1994).                                                                              */
	int ret;
	ret = bios_load_linear(L"roms/machines/multiwave_ultra_power/AP5C180A.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* National MicroComputers */
int
machine_at_nmc_expert_pcw_init(const machine_t *model)
{
	/* National MicroComputers NMC Expert System Plus 120 */
	/* National MicroComputers NMC Expert System Plus 133 */
	/* National MicroComputers NMC PCW P100               */
	/* National MicroComputers NMC Expert Plus 133        */
	/* National MicroComputers NMC Expert Plus 166        */
	/* NOTE: This machine uses an Asus P/I-P55TP4 system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/nmc_expert_pcw/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* NCR (National Cash Register) */
int
machine_at_ncr_3349_init(const machine_t *model)
{
	/* NCR 3349 */
	/* NOTE: This machine uses an Intel Advanced/ATX (Thor) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3349/1002CN0_.BIO",
		L"roms/machines/ncr_3349/1002CN0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_thor_common_init(model, 0);
	return ret;
}

int
machine_at_ncr_3349_06_init(const machine_t *model)
{
	/* NCR 3349 (BIOS version 1.00.06.CN0) */
	/* NOTE: This machine uses an Intel Advanced/ATX (Thor) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3349/1006CN0_.BIO",
		L"roms/machines/ncr_3349/1006CN0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_thor_common_init(model, 0);
	return ret;
}

int
machine_at_ncr_3259_init(const machine_t *model)
{
	/* NCR 3259 */
	/* NOTE: This machine uses an Intel Advanced/RU (RU430HX) (Ruby) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ncr_3259/BIOSDL0.REC",
		L"roms/machines/ncr_3259/BIOSDL0.RE1",
		L"roms/machines/ncr_3259/BIOSDL0.RE2",
		L"roms/machines/ncr_3259/BIOSDL0.RE3",
		L"roms/machines/ncr_3259/1009DL0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ncr_3259_09_init(const machine_t *model)
{
	/* NCR 3259 (BIOS version 1.00.09.DL0) */
	/* NOTE: This machine uses an Intel Advanced/RU (RU430HX) (Ruby) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ncr_3259/1009DL0_.BIO",
		L"roms/machines/ncr_3259/1009DL0_.BI1",
		L"roms/machines/ncr_3259/1009DL0_.BI2",
		L"roms/machines/ncr_3259/1009DL0_.BI3",
		L"roms/machines/ncr_3259/1009DL0_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device); /* Change back to i430hx_device */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* NEC Technologies */
int
machine_at_nec_ready_9520_init(const machine_t *model)
{
	/* NEC PowerMate P133               */
	/* NEC Ready 9520                   */
	/* NEC Ready 9552 (Ready 9520 BIOS) */
	/* NOTE: The NEC Ready 9520 uses an Intel Advanced/AL (Alladin) system board (also referred to by NEC under */
	/*       the Morrison64 name) with an Intel 82430FX (Triton) chipset and Intel AMIBIOS (1.00.07.CA0K).      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/nec_ready_9520/BIOSCA0.REC",
		L"roms/machines/nec_ready_9520/BIOSCA0.RE1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_nec_ready_9520_1007_init(const machine_t *model)
{
	/* NEC Ready 9520 (1.00.07.CA0K)    */
	/* NOTE: The NEC Ready 9520 uses an Intel Advanced/AL (Alladin) system board (also referred to by NEC under */
	/*       the Morrison64 name) with an Intel 82430FX (Triton) chipset and Intel AMIBIOS (1.00.07.CA0K).      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/nec_ready_9520/1007CA0K.BIO",
		L"roms/machines/nec_ready_9520/1007CA0K.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_nec_powermate_p166_init(const machine_t *model)
{
	/* NEC PowerMate P166 */
	/* NOTE: These machines a GVC (Intel 430FX chipset) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/nec_powermate_p166/B50TJ004.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	/* pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0); */
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* NETiS */
int
machine_at_netis_n5120p_powerstation_init(const machine_t *model)
{
	/* NETiS N5120P PowerStation */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                  */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/netis_n5120p_powerstation/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_netis_n5120p_powerstation2_init(const machine_t *model)
{
	/* NETiS N5120P PowerStation */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/netis_n5120p_powerstation/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_netis_n575_media_init(const machine_t *model)
{
	/* NETiS N575 Media */
	/* NOTE: This machine uses an FIC (First International Computer) PT-2000 system board with an Intel 82430FX */
	/*    (Triton) chipset and Award BIOS (09/07/1995 for the seventh system).                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/netis_n575_media/306C800.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Packard Bell */
int
machine_at_pb640_init(const machine_t *model)
{
	/* Packard Bell Force 1998CDT  */
	/* Packard Bell Force 1999CDT  */
	/* Packard Bell Legend 812CD (Intel AMIBIOS) */
	/* Packard Bell Legend 814CD (Intel AMIBIOS) */
	/* Packard Bell Legend 823CDT                */
	/* Packard Bell Legend 824CDT                */
	/* Packard Bell Legend 994CDT  */
	/* Packard Bell Legend 3540    */
	/* Packard Bell Legend 4610    */
	/* Packard Bell Legend 5385z   */
	/* Packard Bell Legend 106CDT Supreme */
	/* Packard Bell Legend 108CDT Supreme */
	/* Packard Bell Legend 117 Supreme */
	/* Packard Bell Designer Tower */
	/* Packard Bell Multimedia 70106D */
	/* Packard Bell  Multi-Media 70157C */
	/* Packard Bell  Multi-Media 70159D */
	/* Packard Bell Multimedia D160     */
	/* Packard Bell Microsoft Station   */
	/* Packard Bell Platinum I (Intel AMIBIOS) */
	/* Packard Bell Platinum III */
	/* Packard Bell Platinum X   */
	/* Packard Bell Platinum XI  */
	/* Packard Bell Platinum XXI */
	/* NOTE: These machines use a system board manufactured by Intel for Packard Bell under the PB640 (Hillary) */
	/*       or Advanced/HL (Hillary) names with an Intel 82430FX (Triton) chipset and Intel AMIBIOS            */
	int ret;
    ret = bios_load_linear_combined(L"roms/machines/pb640/1007CP0R.BIO",
				    L"roms/machines/pb640/1007CP0R.BI1", 0x1d000, 128);
    if (bios_only || !ret)
	return ret;
    machine_at_common_init(model);
    pci_init(PCI_CONFIG_TYPE_1);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
    pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
    pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 1, 3, 4);
    pci_register_slot(0x0B, PCI_CARD_NORMAL, 3, 2, 1, 4);
    pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_rev02_device);
    device_add(&piix_rev02_device);
    if (gfxcard == VID_INTERNAL)
	device_add(&gd5440_onboard_pci_device);
    device_add(&keyboard_ps2_intel_ami_pci_device);
    device_add(&pc87306_device);
    device_add(&intel_flash_bxt_ami_device);
    return ret;
}

const device_t *
at_pb640_get_device(void)
{
    return &gd5440_onboard_pci_device;
}

int
machine_at_pb680_init(const machine_t *model)
{
	/* Packard Bell PB680 */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/pb680/1012DN0R.BIO",
		L"roms/machines/pb680/1012DN0R.BI1",
		L"roms/machines/pb680/1012DN0R.BI2",
		L"roms/machines/pb680/1012DN0R.BI3",
		L"roms/machines/pb680/1012DN0R.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430vx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* PacTron Integration */
int
machine_at_packtron_daytonawin_120nx_init(const machine_t *model)
{
	/* PacTron DaytonaWin-120NX */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                  */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/packtron_daytonawin_120nx/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_packtron_daytonawin_120nx2_init(const machine_t *model)
{
	/* PacTron DaytonaWin-120NX */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/packtron_daytonawin_120nx/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* PC Partner */
int
machine_at_mb540n_init(const machine_t *model)
{
	/* PC Partner MB540N */
	int ret;
	ret = bios_load_linear(L"roms/machines/mb540n/Tx0720ug.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init_ex(model, 2);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);	/* PIIX4 */
	device_add(&i430tx_device);
	device_add(&piix4_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&um8669f_device);
	device_add(&sst_flash_29ee010_device);
	spd_register(SPD_TYPE_SDRAM, 0x3, 128);
	return ret;
}

/* PerComp MicroSystems */
int
machine_at_percomp_p75_p90_p100_init(const machine_t *model)
{
	/*    PerComp    P75  Personal     */
	/*    PerComp    P90  Personal     */
	/*    PerComp    P100 Personal     */
	/*    PerComp    P75  Family Media */
	/*    PerComp    P90  Family Media */
	/*    PerComp    P100 Family Media */
	/*    PerComp    P75  MediaPro     */
	/*    PerComp    P90  MediaPro     */
	/*    PerComp    P100 MediaPro     */
	/*    PerComp    P150 Professional */
	/*    PerComp    P150 Professional */
	/* Simply Better P75  Personal     */
	/* Simply Better P90  Personal     */
	/* Simply Better P100 Personal     */
	/* Simply Better P75  Family Media */
	/* Simply Better P90  Family Media */
	/* Simply Better P100 Family Media */
	/* Simply Better P75  MediaPro     */
	/* Simply Better P90  MediaPro     */
	/* Simply Better P100 MediaPro     */
	/* Simply Better P150 Professional */
	/* Simply Better P166 Professional */
	/* NOTE: These machines use a Chaintech 5IEM system board manufactured under the Plus Data brand name with an */
	/*       Intel 82430FX (Triton) chipset and Award BIOS (4.50G) (07/21/1995).                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/percomp_p75_p90_p100/5IEM0.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&um8669f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_percomp_professional_init(const machine_t *model)
{
	/* PerComp P120 Executive          */
	/* PerComp P133 Executive          */
	/* PerComp P100 Professional       */
	/* PerComp P120 Professional       */
	/* PerComp P133 Professional       */
	/* Simply Better P120 Executive    */
	/* Simply Better P133 Executive    */
	/* Simply Better P100 Professional */
	/* Simply Better P120 Professional */
	/* Simply Better P133 Professional */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/percomp_professional/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_percomp_professional2_init(const machine_t *model)
{
	/* PerComp P120 Executive          (ORIGINAL BIOS) */
	/* PerComp P133 Executive          (ORIGINAL BIOS) */
	/* PerComp P100 Professional       (ORIGINAL BIOS) */
	/* PerComp P120 Professional       (ORIGINAL BIOS) */
	/* PerComp P133 Professional       (ORIGINAL BIOS) */
	/* Simply Better P120 Executive    (ORIGINAL BIOS) */
	/* Simply Better P133 Executive    (ORIGINAL BIOS) */
	/* Simply Better P100 Professional (ORIGINAL BIOS) */
	/* Simply Better P120 Professional (ORIGINAL BIOS) */
	/* Simply Better P133 Professional (ORIGINAL BIOS) */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/percomp_professional/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Polywell */
int
machine_at_polywell_polystation_init(const machine_t *model)
{
	/* Polywell Poly        5100T3 */
	/* Polywell Poly        5120T3 */
	/* Polywell Poly        5133T3 */
	/* Polywell Poly         500P8 */
	/* Polywell PolyStation  133P  */
	/* Polywell PolyStation  166P  */
	/* Polywell Poly        5166P8 */
	/* NOTE: These machines use a Tyan Titan I (S1461) or Titan II (S1468) system board with an Intel 82430FX */
	/*       (Triton) chipset and Award BIOS (04/29/1995 for the 5100T3 and 06/06/1995 for the 5133T3).       */
	int ret;
	ret = bios_load_linear(L"roms/machines/poly_5120t3_5133t3/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Premio (formerly CompuTrend) */
int
machine_at_computrend_premio_p133_init(const machine_t *model)
{
	/* CompuTrend Premio                 P75  */
	/* CompuTrend Premio                 P90  */
	/* CompuTrend Premio                 P100 */
	/* CompuTrend Premio                 P120 */
	/* CompuTrend Premio                 P133 */
	/* CompuTrend Premio Triton          P75  */
	/* CompuTrend Premio Triton          P90  */
	/* CompuTrend Premio Triton          P100 */
	/* CompuTrend Premio Triton          P120 */
	/* CompuTrend Premio Triton          P133 */
	/* CompuTrend Premio Rocket PC       P75  */
	/* CompuTrend Premio Rocket PC       P90  */
	/* CompuTrend Premio Rocket PC       P100 */
	/* CompuTrend Premio Rocket PC       P120 */
	/* CompuTrend Premio Rocket PC       P133 */
	/* CompuTrend Premio Express Station P75  */
	/* CompuTrend Premio Express Station P90  */
	/* CompuTrend Premio Express Station P100 */
	/* CompuTrend Premio Express Station P120 */
	/* CompuTrend Premio Express Station P133 */
	/* CompuTrend Premio Express Server  P90  */
	/* CompuTrend Premio Express Server  P133 */
	/* NOTE: These machines use a CompuTrend Premio Denali system board with an Intel 82430FX (Triton) chipset */
	/*       and Award BIOS (05/11/1995 or 07/12/1995).                                                        */
	int ret;
	ret = bios_load_linear(L"roms/machines/computrend_premio_p133/DNLI104.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	/* pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0); */
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&pc87306_device);
	/* device_add(&intel_flash_bxt_device); */
	return ret;
}

/* Quantex Microsystems */
int
machine_at_quantex_133_166_sm_2_amibios_init(const machine_t *model)
{
	/* Quantex QP5/100 SM-2 */
	/* Quantex QP5/120 SM-2 */
	/* Quantex QP5/133 SM-2 */
	/* Quantex QP5/166 SM-2 */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board for Intel AMIBIOS models */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/quantex_133_166_sm_2/1002CB0_.BIO",
		L"roms/machines/quantex_133_166_sm_2/1002CB0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

int
machine_at_quantex_133_166_sm_2_award_init(const machine_t *model)
{
	/* CyberMax Executive Max P-75    */
	/* CyberMax Executive Max P-100   */
	/* Inteva 5/133                   */
	/* MDS    75MHz Pentium           */
	/* MDS    75MHz 850MB HD PCI      */
	/* MDS   120MHz Pentium PCI 1.2GB */
	/* MDS 5/100 CD                   */
	/* MDS 5/100 CD MiniTower         */
	/* Quantex QP5/75   M-1           */
	/* Quantex QP5/75   M-2           */
	/* Quantex QP5/75   M-3           */
	/* Quantex QP5/75   M-4           */
	/* Quantex QP5/90   M-1           */
	/* Quantex QP5/90   M-2           */
	/* Quantex QP5/90   M-3           */
	/* Quantex QP5/90   M-4           */
	/* Quantex QP5/100  M-1           */
	/* Quantex QP5/100  M-2           */
	/* Quantex QP5/100  M-3           */
	/* Quantex QP5/100  M-4           */
	/* Quantex QP5/100 SM-1           */
	/* Quantex QP5/120 SM-1           */
	/* Quantex QP5/120  M-2           */
	/* Quantex QP5/120  M-3           */
	/* Quantex QP5/120  M-4           */
	/* Quantex QP5/75  SM             */
	/* Quantex QP5/90  SM             */
	/* Quantex QP5/100 SM             */
	/* Quantex QP5/100 SM-1           */
	/* Quantex QP5/120 SM             */
	/* Quantex QP5/120 SM-1           */
	/* Quantex QP5/133 SM             */
	/* Quantex QP5/133 SM-1           */
	/* Quantex QP5/133 SM-2           */
	/* Quantex QP5/166 SM-2           */
	/* NOTE: These machines use an MBD-P5TB or -P5TB/VRE (Biostar 8500TEC) system board for Award BIOS models */
	int ret;
	ret = bios_load_linear(L"roms/machines/quantex_133_166_sm_2/8500TEC.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	/* pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0); */
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_quantex_133_166_sm_2_hx_init(const machine_t *model)
{
	/* Quantex QP5/100 SM-2 */
	/* Quantex QP5/120 SM-2 */
	/* Quantex QP5/133 SM-2 */
	/* Quantex QP5/166 SM-2 */
	/* NOTE: These machines use an MBD-P5VB (Biostar MB-8500TUC) or P5XVB (TVG) system board for AMIBIOS models */
	int ret;
	ret = bios_load_linear(L"roms/machines/quantex_133_166_sm_2/Tuc0221b.rom",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 1, 2, 3, 4);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&um8669f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Reason Technology */
int
machine_at_reason_square_5_lx_tr_ie_133_init(const machine_t *model)
{
	/* Reason Square 5 LX-TR/IE-133 */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.02.CB0).                                                      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/reason_square_5_lx_tr_ie_133/1002CB0_.BIO",
		L"roms/machines/reason_square_5_lx_tr_ie_133/1002CB0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

int
machine_at_reason_square_5_lx_tr_ie_150_init(const machine_t *model)
{
	/* Reason Square 5 LX-TR/IE-150 */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.03.CB0).                                                       */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/reason_square_5_lx_tr_ie_150_166/1003CB0_.BIO",
		L"roms/machines/reason_square_5_lx_tr_ie_150_166/1003CB0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

/* Robotech */
int
machine_at_robotech_cobra_xlt_init(const machine_t *model)
{
	/* Robotech Cobra XLT P100 */
	/* Robotech Cobra XLT P133 */
	/* NOTE: These machines appear to use a Tyan Titan I (S1461) or Titan II (S1468) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/robotech_cobra_xlt/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_robotech_cobra_xlt_p133_p166_init(const machine_t *model)
{
	/* Robotech Cobra XLT P133 (second model) */
	/* Robotech Cobra XLT P166                */
	/* NOTE: These machines appear to use a Tyan Titan III (S1468) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/robotech_cobra_xlt_p133_p166/S68AWD22.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_robotech_cobra_xlt_2_init(const machine_t *model)
{
	/* Robotech Cobra XLT/2 P133 */
	/* Robotech Cobra XLT/2 P166 */
	/* NOTE: These machines appear to use a Tyan Titan III (S1468) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/robotech_cobra_xlt_2/S68NCR25.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Royal Computer */
int
machine_at_royal_media_master_init(const machine_t *model)
{
	/* Royal       Media Master */
	/* Royal Ultra Media-15     */
	/* NOTE: These machines use a Gigabyte 586ATE system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (05/05/1995).                                                                                 */
	int ret;
	ret = bios_load_linear(L"roms/machines/royal_media_master/ATE.212",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* SAG Electronics */
int
machine_at_sag_stf_120_133_init(const machine_t *model)
{
	/* SAG STF 120 */
	/* SAG STF 133 */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/sag_stf_120_133/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_sag_stf_120_1332_init(const machine_t *model)
{
	/* SAG STF 120 (ORIGINAL BIOS) */
	/* SAG STF 133 (ORIGINAL BIOS) */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/sag_stf_120_133/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_sag_stf_150_166_init(const machine_t *model)
{
	/* SAG STF 150 */
	/* SAG STF 166 */
	/* NOTE: These machines appear to  use a Tyan Tomcat II (S1562/S1562S or S1562D) system board with an Intel */
	/*       82430HX (Triton II) chipset and Award BIOS (4.50G).                                                */
	int ret;
	ret = bios_load_linear(L"roms/machines/sag_stf_150_166/S56aw402.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Simply Better Computers */
/* See PerComp MicroSystems */

/* SONY */
int
machine_at_pcv90_init(const machine_t *model)
{
	/* Sony VAIO PCV-90  */
	/* Sony VAIO PCV-120 */
	/* NOTE: These machines use an Intel AG430HX (Agate) system board with an Intel 82430HX (Triton II) chipset */
	/*       and Intel AMIBIOS (1.00.10.DD04)                                                                   */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/sony_pcv_90/1010dd04.bio",
		L"roms/machines/sony_pcv_90/1010dd04.bi1",
		L"roms/machines/sony_pcv_90/1010dd04.bi2",
		L"roms/machines/sony_pcv_90/1010dd04.bi3",
		L"roms/machines/sony_pcv_90/1010dd04.rcv",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	/* int ret;
	ret = bios_load_linear_combined2(L"roms/machines/sony_pcv_90/1010dd04.bio",
	L"roms/machines/sony_pcv_90/1010dd04.bi1",
	L"roms/machines/sony_pcv_90/1010dd04.bi2",
	L"roms/machines/sony_pcv_90/1010dd04.bi3",
	L"roms/machines/sony_pcv_90/1010dd04.rcv",
	0x40000, 128);
	if (bios_only || !ret)
	return ret; */
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* Stargate Microsystems */
int
machine_at_stargate_pentium_75_133_init(const machine_t *model)
{
	/* Stargate Pentium     75  System    */
	/* Stargate Pentium     90  System    */
	/* Stargate Pentium    100  System    */
	/* Stargate Pentium    120  System    */
	/* Stargate Pentium 75-133+ Triton MB */
	/* NOTE: Although full information is not available for the system board that these machines used, the        */
	/*       company's description of a 256 KB cache, PCI disk controller, and 64-bit accelerator with support for*/
	/*       2 MB of graphics memory would appear to suggest an Intel Advanced/EV (Endeavor) system board with an */
	/*       Intel 82430FX (Triton) chipset and Intel AMIBIOS.                                                    */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/stargate_pentium_75_133/1002CB0_.BIO",
		L"roms/machines/stargate_pentium_75_133/1002CB0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

/* Summit Micro Design */
int
machine_at_smd_mount_lassen_shasta_init(const machine_t *model)
{
	/* SMD Mount Lassen */
	/* SMD Mount Shasta */
	/* NOTE: These machines use an Asus P/I-P55TP4 system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (05/12/1995).                                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/smd_mount_lassen_shasta/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Sys Technology */
int
machine_at_sys_performance_p100t_init(const machine_t *model)
{
	/* Sys Performance P100T */
	/* NOTE: These machines use an Asus P/I-P55TP4 system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (05/12/1995).                                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/sys_performance_p100t/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_sys_performance_p133t_init(const machine_t *model)
{
	/* Sys Performance P133T */
	/* NOTE: This machine uses a Tyan Titan I (S1461) or Titan II (S1468) system board with an Intel 82430FX */
	/*       (Triton) chipset and Award BIOS (07/25/1995).                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/sys_performance_p133t/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_sys_performance_p166t_init(const machine_t *model)
{
	/* Sys Performance P166T */
	/* NOTE: These machines use an Asus system board with an Intel 82430FX (Triton) chipset and Award BIOS */
	/*       (4.50G).                                                                                      */
	int ret;
	ret = bios_load_linear(L"roms/machines/sys_performance_p100t/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Tagram */
int
machine_at_tagram_thunderbolt_p100_init(const machine_t *model)
{
	/* Tagram Thunderbolt P100 */
	/* NOTE: This machine uses a BCM SQ595 system board with an Intel 82430FX (Triton) chipset and Award BIOS */
	/*       (07/03/1995).                                                                                    */
	int ret;
	ret = bios_load_linear(L"roms/machines/tagram_thunderbolt_p100/595-a01.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_tagram_thunderbolt_p133_init(const machine_t *model)
{
	/* Tagram Thunderbolt P133 */
	/* NOTE: This machine uses a Tyan Titan I (S1461) or Titan II (S1468) system board with an Intel 82430FX */
	/*       (Triton) chipset and Award BIOS (06/30/1995).                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/tagram_thunderbolt_p133/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Tandy */
/* See AST Research */

/* Tangent */
int
machine_at_tangent_mediastar_init(const machine_t *model)
{
	/* Tangent MediaStar 590/95  */
	/* Tangent MediaStar 5133/95 */
	/* NOTE: These machines use a Tyan Titan I (S1461) or Titan II (S1468) system board with an Intel 82430FX */
	/*       (Triton) chipset and Award BIOS (07/25/1995).                                                    */
	int ret;
	ret = bios_load_linear(L"roms/machines/tangent_mediastar/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Tatung */
int
machine_at_tatung_tcs_5100_5900_init(const machine_t *model)
{
	/* Tatung TCS-5100 */
	/* Tatung TCS-5900 */
	/* NOTE: These machines use what appears to be a Biostar 8500TAC-A system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/tatung_tcs_5100_5900/AMIBOOT.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* TechnoMedia Corporation */
int
machine_at_technomedia_fic_pt_2000_init(const machine_t *model)
{
	/* TechnoMedia FIC PT-2000 */
	/* NOTE: This machine uses an FIC (First International Computer) PT-2000 system board with an Intel 82430FX */
	/*    (Triton) chipset and Award BIOS.                                                                      */
	int ret;
	ret = bios_load_linear(L"roms/machines/technomedia_fic_pt_2000/306C800.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Top Data */
int
machine_at_top_data_p5_pci_init(const machine_t *model)
{
	/* Top Data P5-120      PCI */
	/* Top Data P5-133      PCI */
	/* Top Data P5-100/256C PCI */
	/* Top Data P5-120/256C PCI */
	/* Top Data P5-133/256C PCI */
	/* NOTE: These machines use an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset */
	/*       and Intel AMIBIOS.                                                                                  */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/top_data_p5_pci/1002BS0_.BIO",
		L"roms/machines/top_data_p5_pci/1002BS0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_top_data_p5_100c_120c_133c_init(const machine_t *model)
{
	/* Top Data P5-100C (Intel Endeavor M/B) */
	/* Top Data P5-120C (Intel Endeavor M/B) */
	/* Top Data P5-133C (Intel Endeavor M/B) */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS.                                                                     */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/top_data_p5_100c_120c_133c/1002CB0_.BIO",
		L"roms/machines/top_data_p5_100c_120c_133c/1002CB0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

int
machine_at_top_data_p5_100c_120c_133c2_init(const machine_t *model)
{
	/* Top Data P5-100C (Intel Atlantis M/B) */
	/* Top Data P5-120C (Intel Atlantis M/B) */
	/* Top Data P5-133C (Intel Atlantis M/B) */
	/* NOTE: These machines use an Intel Advanced/AL (Atlantis) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS.                                                                     */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/top_data_p5_100c_120c_133c/1004CL0_.BIO",
		L"roms/machines/top_data_p5_100c_120c_133c/1004CL0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	/* if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device); */
	return ret;
}

/* Toshiba */
int
machine_at_equium5200_init(const machine_t *model) // Information about that machine on machine.h
{
	/* Toshiba Equium 5160D */
	/* Toshiba Equium 5200D */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/equium5200/1003DK08.BIO",
		L"roms/machines/equium5200/1003DK08.BI1",
		L"roms/machines/equium5200/1003DK08.BI2",
		L"roms/machines/equium5200/1003DK08.BI3",
		L"roms/machines/equium5200/1003DK08.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 0, 0, 0); // riser
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* Tri-Star */
int
machine_at_tri_star_tri_cad_workstation_init(const machine_t *model)
{
	/* Tri-Star Tri-CAD Pro-17 Workstation 120                  */
	/* Tri-Star Tri-CAD 133/55 Workstation                      */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (03/15/1995).                                                        */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/tri_star_tri_cad_workstation/1002CB0_.BIO",
		L"roms/machines/tri_star_tri_cad_workstation/1002CB0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

int
machine_at_tri_star_tri_cad_multimedia_init(const machine_t *model)
{
	/* Tri-Star Tri-CAD Multimedia */
	/* NOTE: This machine appears to use a Biostar 8500TEC system board manufactured under the Area brand name */
	/*       with an Intel 82430FX (Triton) chipset and Award BIOS (07/18/1995).                               */
	int ret;
	ret = bios_load_linear(L"roms/machines/tri_star_tri_cad_multimedia/8500TEC.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Unisys */
int
machine_at_unisys_pw2_advantage_super_init(const machine_t *model)
{
	/* Unisys PW2 Advantage Super Series CWP51336 */
	/* NOTE: This machine uses an FIC (First International Computer) PT-2000 system board with an Intel 82430FX */
	/*    (Triton) chipset and Award BIOS (09/07/1995 for the seventh system).                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/unisys_pw2_advantage/306KC806.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Unitek Technology */
int
machine_at_unitek_thunderstreak_init(const machine_t *model)
{
	/* Unitek Thunderstreak Pentium 133 */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (05/17/1995).                                                        */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/unitek_thunderstreak_pentium_133/1002CB0_.BIO",
		L"roms/machines/unitek_thunderstreak_pentium_133/1002CB0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	return ret;
}

/* USA Flex */
int
machine_at_usa_flex_flex_pt_133_init(const machine_t *model)
{
	/* USA Flex Flex Multimedia System PT-133 */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton) */
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/usa_flex_flex_multimedia_system_pt_133/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_usa_flex_flex_pt_1332_init(const machine_t *model)
{
	/* USA Flex Flex Multimedia System PT-133 (ORIGINAL BIOS) */
	/* NOTE: This machine uses a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton) */
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/usa_flex_flex_multimedia_system_pt_133/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_usa_flex_pt100_business_init(const machine_t *model)
{
	/* USA Flex PT100 Business Workstation */
	/* USA Flex PT-90 Multimedia System    */
	/* NOTE: These machines use a Chaintech 5IEM system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (06/21/1995).                                                                                */
	int ret;
	ret = bios_load_linear(L"roms/machines/usa_flex_pt100_business_workstation/5IEM0.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&um8669f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_usa_flex_pt_166_ultimate_init(const machine_t *model)
{
	/* USA Flex PT-166 Ultimate Multimedia Tower */
	/* NOTE: This machine uses an Intel Advanced/AS (Atlantis) system board with an Intel 82430FX (Triton) chipset*/
	/*       and Intel AMIBIOS (1.00.01.CL0).                                                                     */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/usa_flex_pt_166_ultimate_multimedia_tower/1004CL0_.BIO",
		L"roms/machines/usa_flex_pt_166_ultimate_multimedia_tower/1004CL0_.BI1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_thor_common_init(model, 0);
	return ret;
}

int
machine_at_usa_flex_multimedia_classic_init(const machine_t *model)
{
	/* USA Flex Multimedia Classic */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (*/
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/usa_flex_multimedia_classic/1004cb0_.bio",
		L"roms/machines/usa_flex_multimedia_classic/1004cb0_.bi1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* Vektron International */
int
machine_at_vektron_p133_init(const machine_t *model)
{
	/* Vektron          Power Station     P-133 */
	/* Vektron Ultimate Power Station     P-133 */
	/* Vektron Multimedia Home                  */
	/* Vektron            Home Office Pro-P150  */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton) */
	/*       chipset and AMIBIOS (10/10/1994).                                                                    */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/vektron_p133/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430hx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_vektron_p1332_init(const machine_t *model)
{
	/* Vektron          Power Station P-133 (ORIGINAL BIOS) */
	/* Vektron Ultimate Power Station P-133 (ORIGINAL BIOS) */
	/* Vektron     Multimedia    Home       (ORIGINAL BIOS) */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton) */
	/*       chipset and AMIBIOS (10/10/1994).                                                                    */
	int ret;
	ret = bios_load_linear(L"roms/machines/vektron_p133/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Wedge Technology */
int
machine_at_wedge_deskmate_pro_133_init(const machine_t *model)
{
	/* Wedge DeskMate Pro 133 */
	/* NOTE: This machine uses a Tyan Titan I (S1461) or Titan II (S1468) system board with an Intel 82430FX */
	/*       (Triton) chipset and Award BIOS (07/25/1995).                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/wedge_deskmate_pro_133/S6XAWD23.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Xi Computer Corporation */
/* Xi      MTower SP166MHz */
/* Xi P133 MTower SP       */
/* Xi P166 MTower SP       */
/* Xi P200 MTower SP       */
/* NOTE: See m_at_socket4_5.c */

/* Zenith Data Systems */
int
machine_at_zenith_z_station_gt_init(const machine_t *model)
{
	/* Zenith Z-Station GT */
	/* NOTE: This machine uses an Intel Advanced/AL (Aladdin) system board with an Intel 82430FX chipset and Intel */
	/*       AMIBIOS (05/08/1995)                                                                                  */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_gt/1001CA0U.BIO",
		L"roms/machines/zenith_z_station_gt/1001CA0U.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_zenith_z_station_gt_1001_init(const machine_t *model)
{
	/* Zenith Z-Station GT (1.00.01.CA0U) */
	/* NOTE: This machine uses an Intel Advanced/AL (Aladdin) system board with an Intel 82430FX chipset and Intel */
	/*       AMIBIOS (1.00.01.CA0U).                                                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_gt/1001CA0U.BIO",
		L"roms/machines/zenith_z_station_gt/1001CA0U.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_zenith_z_station_gt_1002_init(const machine_t *model)
{
	/* Zenith Z-Station GT (1.00.02.CA0U) */
	/* NOTE: This machine uses an Intel Advanced/AL (Aladdin) system board with an Intel 82430FX chipset and Intel */
	/*       AMIBIOS (1.00.02.CA0U).                                                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_gt/1002CA0U.BIO",
		L"roms/machines/zenith_z_station_gt/1002CA0U.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_zenith_z_station_gt_1007_init(const machine_t *model)
{
	/* Zenith Z-Station GT (1.00.07.CA0U) */
	/* NOTE: This machine uses an Intel Advanced/AL (Aladdin) system board with an Intel 82430FX chipset and Intel */
	/*       AMIBIOS (1.00.07.CA0U).                                                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_gt/1007CA0U.BIO",
		L"roms/machines/zenith_z_station_gt/1007CA0U.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_zenith_z_station_gt_1009_init(const machine_t *model)
{
	/* Zenith Z-Station GT (1.00.09.CA0U) */
	/* NOTE: This machine uses an Intel Advanced/AL (Aladdin) system board with an Intel 82430FX chipset and Intel */
	/*       AMIBIOS (1.00.07.CA0U).                                                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_gt/1009CA0U.BIO",
		L"roms/machines/zenith_z_station_gt/1009CA0U.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	if (gfxcard == VID_INTERNAL)
		device_add(&s3_phoenix_trio64_onboard_pci_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* Zenon Computer Systems */
int
machine_at_zenon_dream_media_init(const machine_t *model)
{
	/* Zenon Dream Media P5-120 */
	/* Zenon Dream Media P5-133 */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/zenon_dream_media/SUPER9B.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_zenon_dream_media2_init(const machine_t *model)
{
	/* Zenon Dream Media P5-120 */
	/* Zenon Dream Media P5-133 */
	/* NOTE: These machines use a SuperMicro P55CM, P55CMA, or P55CMS system board with an Intel 82430FX (Triton)*/
	/*       chipset and AMIBIOS (10/10/1994).                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/zenon_dream_media/BIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_zenon_dream_media_p_150_166_init(const machine_t *model)
{
	/* Zenon Dream Media P-150 */
	/* Zenon Dream Media P-166 */
	/* NOTE: These machines use an Asus system board with an Intel 82430FX (Triton) chipset and Award BIOS */
	/*       (4.50G).                                                                                      */
	int ret;
	ret = bios_load_linear(L"roms/machines/zenon_dream_media_p_150_166/TX5I0202.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i430fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&w83877f_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* ZEOS International */
int
machine_at_zeos_pantera_133mhz_init(const machine_t *model)
{
	/* ZEOS Pantera  75MHz */
	/* ZEOS Pantera  90MHz */
	/* ZEOS Pantera 100MHz */
	/* ZEOS Pantera 120MHz */
	/* ZEOS Pantera 133MHz */
	/* NOTE: These machines use either a ZEOS Boa system board with a VLSI SuperCore 590 or VSLI Wildcat chipset or*/
	/*       a ZEOS system board with an Intel 82430NX (Neptune) chipset with both types of system boards using a  */
	/*       Phoenix BIOS (4.03).                                                                                  */
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_pantera_90/002811.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430nx_device);
	device_add(&sio_zb_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}
