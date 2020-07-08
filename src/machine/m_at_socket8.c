/*
 * 86Box	A hypervisor and IBM PC system emulator that specializes in
 *		running old operating systems and software designed for IBM
 *		PC systems and compatibles from 1981 through fairly recent
 *		system designs based on the PCI bus.
 *
 *		This file is part of the 86Box distribution.
 *
 *		Implementation of Socket 8 machines.
 *
 *
 *
 * Authors:	Miran Grca, <mgrca8@gmail.com>
 *
 *		Copyright 2016-2019 Miran Grca.
 */
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
#include <86box/flash.h>
 /* #include <86box/intel_sio.h>
#include <86box/piix.h> */
#include <86box/sio.h>
#include <86box/hwm.h>
#include <86box/spd.h>
#include <86box/video.h>
#include "cpu.h"
#include <86box/machine.h>

int
machine_at_686nx_init(const machine_t *model)
{
    int ret;

    ret = bios_load_linear(L"roms/machines/686nx/6nx.140",
			   0x000e0000, 131072, 0);

    if (bios_only || !ret)
	return ret;

    machine_at_common_init(model);

    pci_init(PCI_CONFIG_TYPE_1);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
    pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
    pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
    pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
    device_add(&i440fx_device);
    device_add(&piix3_device);
    device_add(&keyboard_ps2_ami_pci_device); //Uses the AMIKEY keyboard controller
    device_add(&um8669f_device);
    device_add(&intel_flash_bxt_device);

    return ret;
}


int
machine_at_8500ttc_init(const machine_t *model)
{
    int ret;

    ret = bios_load_linear(L"roms/machines/8500ttc/TTC0715B.ROM",
			   0x000e0000, 131072, 0);

    if (bios_only || !ret)
	return ret;

    machine_at_common_init(model);

    pci_init(PCI_CONFIG_TYPE_1);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_NORMAL, 1, 2, 3, 4);
    pci_register_slot(0x09, PCI_CARD_NORMAL, 2, 3, 4, 1);
    pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
    pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
    device_add(&i440fx_device);
    device_add(&piix3_device);
    device_add(&keyboard_ps2_ami_pci_device);
    device_add(&fdc37c669_device);
    device_add(&intel_flash_bxt_device);

    return ret;
}

int
machine_at_m6mi_init(const machine_t *model)
{
    int ret;

    ret = bios_load_linear(L"roms/machines/m6mi/M6MI05.ROM",
			   0x000e0000, 131072, 0);

    if (bios_only || !ret)
	return ret;

    machine_at_common_init(model);

    pci_init(PCI_CONFIG_TYPE_1);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
    pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
    pci_register_slot(0x10, PCI_CARD_NORMAL, 3, 4, 1, 2);
    pci_register_slot(0x0F, PCI_CARD_NORMAL, 4, 1, 2, 3);
    device_add(&i440fx_device);
    device_add(&piix3_device);
    device_add(&keyboard_ps2_ami_pci_device);
    device_add(&fdc37c935_device);
    device_add(&intel_flash_bxt_device);

    return ret;
}

void
machine_at_p65up5_common_init(const machine_t *model, const device_t *northbridge)
{
    machine_at_common_init(model);

    pci_init(PCI_CONFIG_TYPE_1);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x01, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x09, PCI_CARD_NORMAL, 4, 1, 2, 3);
    pci_register_slot(0x0A, PCI_CARD_NORMAL, 3, 4, 1, 2);
    pci_register_slot(0x0B, PCI_CARD_NORMAL, 2, 3, 4, 1);
    pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 2, 3, 4);
    pci_register_slot(0x0D, PCI_CARD_NORMAL, 4, 1, 2, 3);
    device_add(northbridge);
    device_add(&piix3_device);
    device_add(&keyboard_ps2_ami_pci_device);
    device_add(&w83877f_device);
    device_add(&intel_flash_bxt_device);
	device_add(&ioapic_device);
}

int
machine_at_p65up5_cp6nd_init(const machine_t *model)
{
    int ret;

    ret = bios_load_linear(L"roms/machines/p65up5/nd6i0218.awd",
			   0x000e0000, 131072, 0);

    if (bios_only || !ret)
	return ret;

    machine_at_p65up5_common_init(model, &i440fx_device);

    return ret;
}

/* Intel Corporation */
int
machine_at_vs440fx_init(const machine_t *model)
{
	/* Intel VS440FX (Venus) */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/vs440fx/1018CS1_.bio",
		L"roms/machines/vs440fx/1018CS1_.bi1",
		L"roms/machines/vs440fx/1018CS1_.bi2",
		L"roms/machines/vs440fx/1018CS1_.bi3",
		L"roms/machines/vs440fx/1018CS1_.rcv",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_intel_ami_pci_device);
	device_add(&pc87307_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ap440fx_init(const machine_t *model)
{
	/* Intel AP440FX (Apollo/Krakatoa) */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ap440fx/1011CT1_.bio",
		L"roms/machines/ap440fx/1011CT1_.bi1",
		L"roms/machines/ap440fx/1011CT1_.bi2",
		L"roms/machines/ap440fx/1011CT1_.bi3",
		L"roms/machines/ap440fx/1011CT1_.rcv",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 3, 0, 0, 0);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 4);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87307_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* Acer */
int
machine_at_v60n_init(const machine_t *model)
{
	/* Acer V60N */
	int ret;
	ret = bios_load_linear(L"roms/machines/v60n/V60NE5.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 2, 3, 4, 1);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c935_device);
	device_add(&sst_flash_29ee010_device);
	return ret;
}

/* ACMA */
int
machine_at_acma_zpower_pro_200_init(const machine_t *model)
{
	/* ACMA zPower Pro 200 */
	/* NOTE: This machine uses an Intel Performance/VS (VS440FX) (Venus) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/acma_zpower_pro_200/1006CS1_.BIO",
		L"roms/machines/acma_zpower_pro_200/1006CS1_.BI1",
		L"roms/machines/acma_zpower_pro_200/1006CS1_.BI2",
		L"roms/machines/acma_zpower_pro_200/1006CS1_.BI3",
		L"roms/machines/acma_zpower_pro_200/1006CS1_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 2, 1);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 3, 2, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	/* device_add(&intel_flash_bxtw_ami_device); */
	return ret;
}

int
machine_at_acma_exp_pro_266_init(const machine_t *model)
{
	/* ACMA EXP Pro 266 */
	/* NOTE: This machine uses an PD440FX (Portland) system board */
	int ret;
	/* ret = bios_load_linear_combined2(L"roms/machines/acma_exp_pro_266/1005DT0_.BIO",
	L"roms/machines/acma_exp_pro_266/1005DT0_.BI1",
	L"roms/machines/acma_exp_pro_266/1005DT0_.BI2",
	L"roms/machines/acma_exp_pro_266/1005DT0_.BI3",
	L"roms/machines/acma_exp_pro_266/1005DT0_.RCV",
	0x3a000, 128); */
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
	device_add(&i440fx_device); /* Change back to 440FX */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* AST Research */
int
machine_at_ast_bravo_ms_t_6200_init(const machine_t *model)
{
	/* AST Bravo MS-T 6200 (BIOS version 1.00.04.CS1Q) */
	/* NOTE: This machine uses an Intel Performance/VS (VS440FX) (Venus) system board */
	/* NOTE 2: The standard Intel VS440FX (Advanced/VS) BIOS is used until an original BIOS dump is available */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ast_bravo_ms_t_6200/1004CS1Q.BIO",
		L"roms/machines/ast_bravo_ms_t_6200/1004CS1Q.BI1",
		L"roms/machines/ast_bravo_ms_t_6200/1004CS1Q.BI2",
		L"roms/machines/ast_bravo_ms_t_6200/1004CS1Q.BI3",
		L"roms/machines/ast_bravo_ms_t_6200/1006CS1_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 2, 1);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 3, 2, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	/* device_add(&intel_flash_bxtw_ami_device); */
	return ret;
}

int
machine_at_ast_bravo_ms_t_6200_05_init(const machine_t *model)
{
	/* AST Bravo MS-T 6200 (BIOS version 1.00.05.CS1Q) */
	/* NOTE: This machine uses an Intel Performance/VS (VS440FX) (Venus) system board */
	/* NOTE 2: The standard Intel VS440FX (Advanced/VS) BIOS is used until an original BIOS dump is available */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ast_bravo_ms_t_6200/1005CS1Q.BIO",
		L"roms/machines/ast_bravo_ms_t_6200/1005CS1Q.BI1",
		L"roms/machines/ast_bravo_ms_t_6200/1005CS1Q.BI2",
		L"roms/machines/ast_bravo_ms_t_6200/1005CS1Q.BI3",
		L"roms/machines/ast_bravo_ms_t_6200/1006CS1_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 2, 1);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 3, 2, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	/* device_add(&intel_flash_bxtw_ami_device); */
	return ret;
}

int
machine_at_ast_bravo_lc_6233_init(const machine_t *model)
{
	/* AST Bravo LC 6233 (BIOS version 1.00.01.DU0I)  */
	/* NOTE: This machine uses an Intel DB440FX (Dublin) system board */
	/* NOTE 2: The standard Intel DB440FX (Dublin) BIOS is used until an original BIOS dump is available */
	int ret;
	/* ret = bios_load_linear_combined2(L"roms/machines/ast_bravo_lc_6233/1001DU0I.BIO",
	L"roms/machines/ast_bravo_lc_6233/1001DU0I.BI1",
	L"roms/machines/ast_bravo_lc_6233/1001DU0I.BI2",
	L"roms/machines/ast_bravo_lc_6233/1001DU0I.BI3",
	L"roms/machines/ast_bravo_lc_6233/1004DT0_.RCV",
	0x3a000, 128); */
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
	device_add(&i440fx_device); /* Change back to 440FX */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ast_bravo_lc_6233_02_init(const machine_t *model)
{
	/* AST Bravo LC 6233 (BIOS version 1.00.02.DU0I)  */
	/* NOTE: This machine uses an Intel DB440FX (Dublin) system board */
	int ret;
	/* ret = bios_load_linear_combined2(L"roms/machines/ast_bravo_lc_6233/1002DU0I.BIO",
	L"roms/machines/ast_bravo_lc_6233/1002DU0I.BI1",
	L"roms/machines/ast_bravo_lc_6233/1002DU0I.BI2",
	L"roms/machines/ast_bravo_lc_6233/1002DU0I.BI3",
	L"roms/machines/ast_bravo_lc_6233/1004DT0_.RCV",
	0x3a000, 128); */
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
	device_add(&i440fx_device); /* Change back to 440FX */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* Austin (IPC) */
int
machine_at_austin_elan_200_init(const machine_t *model)
{
	/* Austin Elan Workstation 200 */
	/* NOTE: This machine uses an Intel Performance/VS (VS440FX) (Venus) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/austin_elan_200/1006CS1_.BIO",
		L"roms/machines/austin_elan_200/1006CS1_.BI1",
		L"roms/machines/austin_elan_200/1006CS1_.BI2",
		L"roms/machines/austin_elan_200/1006CS1_.BI3",
		L"roms/machines/austin_elan_200/1006CS1_.RCV",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x08, PCI_CARD_ONBOARD, 4, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 2, 1);
	pci_register_slot(0x10, PCI_CARD_NORMAL, 4, 3, 2, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	/* device_add(&intel_flash_bxtw_ami_device); */
	return ret;
}

/* Gateway 2000 */
int
machine_at_gw2kvs_init(const machine_t *model)
{
	/* Gateway 2000 G6-180 */
	/* Gateway 2000 G6-200 */
	/* NOTE: These machines use an Intel VS440FX (Venus) system board with an Intel 82440FX (Natoma) chipset */
	/*       and Intel AMIBIOS (1.00.11.CS1T).                                                               */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/gw2kvs/1011CS1T.bio",
		L"roms/machines/gw2kvs/1011CS1T.bi1",
		L"roms/machines/gw2kvs/1011CS1T.bi2",
		L"roms/machines/gw2kvs/1011CS1T.bi3",
		L"roms/machines/gw2kvs/1011CS1T.rcv",
		0x3a000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_intel_ami_pci_device);
	device_add(&pc87307_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}
/* NCR (National Cash Register) */
int
machine_at_ncr_3269_init(const machine_t *model)
{
	/* NCR 3269 */
	/* NOTE: This machine uses an Intel AP440FX (Apollo) system board */
	int ret;
	ret = bios_load_linear_combined2(L"roms/machines/ncr_3269/3269B108.BIO",
		L"roms/machines/acma_exp200/3269B108.BI1",
		L"roms/machines/acma_exp200/3269B108.BI2",
		L"roms/machines/acma_exp200/3269B108.BI3",
		L"roms/machines/acma_exp200/1008CT1_.RCV",
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
	device_add(&i440fx_device); /* Change back to 440FX */
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* PC Partner MB600N */
int
machine_at_mb600n_init(const machine_t *model)
{
	/* PC Partner MB600N */
	int ret;
	ret = bios_load_linear(L"roms/machines/mb600n/60915cs.rom",
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
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&fdc37c669_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Xi Computer */
int
machine_at_xi_pro_200mtower_dp_sp_init(const machine_t *model)
{
	/* Xi Pro 200MTower DP/SP (Award BIOS) */
	/* NOTE: This machine uses a Tyan Titan Pro ATX (S1668) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/xi_pro_200mtower_dp_sp/NTMAW303.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_xi_pro_200mtower_dp_sp_ami_init(const machine_t *model)
{
	/* Xi Pro 200MTower DP/SP (AMIBIOS) */
	/* NOTE: This machine uses a Tyan Titan Pro ATX (S1668) system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/xi_pro_200mtower_dp_sp/S1668P.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_xi_pro_200mtower_sp_init(const machine_t *model)
{
	/* Xi Pro 200MTower SP */
	/* NOTE: This machine uses a Tyan Tacoma (S1672) system board                                            */
	/* NOTE: PC Magazine (December 3rd, 1996) misidentifies the system board as being an FIC                 */
	/* (First International Computer) system board with 3 ISA slots and four PCI slots when it is actually a */
	/* Tyan Tacoma (S1672) system with four ISA slots and four PCI slots                                     */
	int ret;
	ret = bios_load_linear(L"roms/machines/xi_pro_200mtower_sp/S1672P.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x0A, PCI_CARD_NORMAL, 1, 2, 3, 4);
	device_add(&i440fx_device);
	device_add(&piix3_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}
