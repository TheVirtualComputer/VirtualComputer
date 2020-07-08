/*
 * 86Box	A hypervisor and IBM PC system emulator that specializes in
 *		running old operating systems and software designed for IBM
 *		PC systems and compatibles from 1981 through fairly recent
 *		system designs based on the PCI bus.
 *
 *		This file is part of the 86Box distribution.
 *
 *		Implementation of Socket 4 and 5 machines.
 *
 *
 *
 * Authors:	Sarah Walker, <http://pcem-emulator.co.uk/>
 *		Miran Grca, <mgrca8@gmail.com>
 *
 *		Copyright 2010-2019 Sarah Walker.
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
#include <86box/timer.h>
#include <86box/fdd.h>
#include <86box/fdc.h>
#include <86box/keyboard.h>
#include <86box/flash.h>
 /* #include <86box/intel_sio.h> */
#include <86box/nvr.h>
/* #include <86box/piix.h> */
#include <86box/sio.h>
#include <86box/video.h>
#include <86box/machine.h>

/*
int
machine_at_hot523_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/hot523/523R21.BIN",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x03, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x04, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x05, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 4, 1, 2, 3);

	machine_at_common_init(model);
	device_add(&keyboard_at_device);
	device_add(&ide_vlb_2ch_device);
	device_add(&fdc_at_device);
	device_add(&python_device);

	return ret;
} */

static void
machine_at_opti495_ami_common_init(const machine_t *model)
{
	machine_at_common_ide_init(model);

	device_add(&opti495_device);

	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
}


static void
machine_at_sis_85c471_common_init(const machine_t *model)
{
	machine_at_common_init(model);
	device_add(&fdc_at_device);

	device_add(&sis_85c471_device);
}

static void
machine_at_sis_85c50x_common_init(const machine_t *model)
{
	machine_at_common_init(model);

	device_add(&ide_pci_device);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x05, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x07, PCI_CARD_NORMAL, 4, 1, 2, 3);
	device_add(&keyboard_ps2_pci_device);

	pci_set_irq_routing(PCI_INTA, PCI_IRQ_DISABLED);
	pci_set_irq_routing(PCI_INTB, PCI_IRQ_DISABLED);
	pci_set_irq_routing(PCI_INTC, PCI_IRQ_DISABLED);
	pci_set_irq_routing(PCI_INTD, PCI_IRQ_DISABLED);

	device_add(&sis_85c50x_device);
}

static void
machine_at_premiere_common_init(const machine_t *model, int pci_switch)
{
    machine_at_common_init(model);
    device_add(&ide_pci_2ch_device);

	pci_init(PCI_CONFIG_TYPE_2 | pci_switch);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
    pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
    pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
    pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
    pci_register_slot(0x02, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
    device_add(&keyboard_ps2_ami_pci_device);
    device_add(&sio_zb_device);
    device_add(&fdc37c665_device);
    device_add(&intel_flash_bxt_ami_device);
}


static void
machine_at_award_common_init(const machine_t *model)
{
    machine_at_common_init(model);
    device_add(&ide_pci_2ch_device);

    pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
    pci_register_slot(0x03, PCI_CARD_NORMAL, 1, 2, 3, 4);	/* 03 = Slot 1 */
    pci_register_slot(0x04, PCI_CARD_NORMAL, 2, 3, 4, 1);	/* 04 = Slot 2 */
    pci_register_slot(0x05, PCI_CARD_NORMAL, 3, 4, 1, 2);	/* 05 = Slot 3 */
    pci_register_slot(0x06, PCI_CARD_NORMAL, 4, 1, 2, 3);	/* 06 = Slot 4 */
    pci_register_slot(0x07, PCI_CARD_SCSI, 1, 2, 3, 4);		/* 07 = SCSI */
    pci_register_slot(0x02, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
    device_add(&fdc_at_device);
    device_add(&keyboard_ps2_pci_device);
    /* device_add(&sio_device); */
}

int
machine_at_p5mp3_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/p5mp3/0205.bin",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);
	device_add(&ide_pci_device);

	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x05, PCI_CARD_NORMAL, 1, 2, 3, 4);	/* 05 = Slot 1 */
	pci_register_slot(0x04, PCI_CARD_NORMAL, 2, 3, 4, 1);	/* 04 = Slot 2 */
	pci_register_slot(0x03, PCI_CARD_NORMAL, 3, 4, 1, 2);	/* 03 = Slot 3 */
	pci_register_slot(0x02, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&fdc_at_device);
	device_add(&keyboard_ps2_pci_device);

	device_add(&sio_zb_device);

	device_add(&catalyst_flash_device);
	device_add(&i430lx_device);

	return ret;
}

int
machine_at_586mc1_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/586mc1/IS.34",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_award_common_init(model);

	device_add(&sio_device);
	device_add(&intel_flash_bxt_device);
	device_add(&i430lx_device);

	return ret;
}



int
machine_at_430nx_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/430nx/IP.20",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_award_common_init(model);

	device_add(&sio_device);
	device_add(&intel_flash_bxt_device);
	device_add(&i430nx_device);

	return ret;
}


int
machine_at_p54tp4xe_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/p54tp4xe/t15i0302.awd",
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


/* IBM (International Business Machines) */
#if defined(DEV_BRANCH) && defined(USE_VPP60)
int
machine_at_valuepointp60_init(const machine_t *model)
{
	/* IBM PS/ValuePoint P60/D */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/valuepointp60/1006AV0M.BIO",
		L"roms/machines/valuepointp60/1006AV0M.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}
#endif

/* Intel Corporation */
int
machine_at_batman_init(const machine_t *model)
{
	/* Intel Premiere/PCI (Batman's Revenge) */
	int ret;
    ret = bios_load_linear_combined(L"roms/machines/revenge/1009af2_.bio",
				    L"roms/machines/revenge/1009af2_.bi1", 0x1c000, 128);
    if (bios_only || !ret)
	return ret;
	machine_at_premiere_common_init(model, 0);
    device_add(&i430lx_device);
    return ret;
}

int
machine_at_plato_init(const machine_t *model)
{
	/* Intel Premiere/PCI II (Plato) */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/plato/1016ax1_.bio",
		L"roms/machines/plato/1016ax1_.bi1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_zappa_init(const machine_t *model)
{
	/* Intel Advanced/ZP (Zappa) */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zappa/1006bs0_.bio",
		L"roms/machines/zappa/1006bs0_.bi1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_intel_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_endeavor_init(const machine_t *model)
{
	/* Intel Advanced/EV (Endeavor) */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/endeavor/1006cb0_.bio",
		L"roms/machines/endeavor/1006cb0_.bi1", 0x1d000, 128);
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
	device_add(&keyboard_ps2_intel_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

const device_t *
at_endeavor_get_device(void)
{
	return &s3_phoenix_trio64_onboard_pci_device;
}

/* Aberdeen */
int
machine_at_aberdeen_super_p90_vl_pci_init(const machine_t *model)
{
	/* Aberdeen Super P90 VL/PCI */
	/* NOTE: This machine uses a SuperMicro Super P54VL-PCI system board with an OPTi Python chipset and AMIBIOS */
	/*       (12/15/1993).                                                                                       */
	int ret;
	/* ret = bios_load_linear(L"roms/machines/aberdeen_superp90/SM507.ROM",
		0x000e0000, 131072, 0); */
	ret = bios_load_linear_inverted(L"roms/machines/aberdeen_superp90/SM507.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x03, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x04, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x05, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 4, 1, 2, 3);
	machine_at_common_init(model);
	/* device_add(&keyboard_at_device);
	device_add(&ide_vlb_2ch_device);
	device_add(&fdc_at_device);
	device_add(&python_device); */
	device_add(&ide_vlb_device);
	device_add(&opti5x7_device);
	device_add(&fdc37c663_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_aberdeen_p100_pci_init(const machine_t *model)
{
	/* Aberdeen P100-PCI */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) chipset*/
	/*       and Intel AMIBIOS (1.00.12.AX1).                                                                       */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/aberdeen_p100_pci/1012AX1_.BIO",
		L"roms/machines/aberdeen_p100_pci/1012AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Acer (including AcerOpen/AOpen) */
/* Acer AcerPower 60MHz Pentium */
/* See m_at_socket7_s7.c file for Acer M3a system board until original BIOS is available */

/* Acer AcerPower 90MHz Pentium */
/* See m_at_socket7_s7.c file for Acer M3a system board until original BIOS is available */

int
machine_at_acerv30_init(const machine_t *model)
{
	/* Acer V30 */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerv30/V30R01N9.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x12, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x11, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x14, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x13, PCI_CARD_NORMAL, 4, 1, 2, 3);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&keyboard_ps2_acer_pci_device);
	device_add(&fdc37c665_device);
	device_add(&sst_flash_29ee010_device);
	return ret;
}

/* ACMA */
int
machine_at_acma_p60_init(const machine_t *model)
{
	/* ACMA P60 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/acma_p60/1005AF2_.BIO",
		L"roms/machines/acma_p60/1005AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_acma_p66_tower_init(const machine_t *model)
{
	/* ACMA P66 Tower */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/acma_p66_tower/1008af1_.bio",
		L"roms/machines/acma_p66_tower/1008af1_.bi1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_acma_p90_init(const machine_t *model)
{
	/* ACMA P90       */
	/* ACMA P90 Tower */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS                                                                        */
	/* NOTE 2: The closest matching ROM BIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/acma_p90/1006AX1_.RST",
		L"roms/machines/acma_p90/1006AX1_.RS1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_acma_p100_init(const machine_t *model)
{
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (01/27/1995).                                                       */
	/* NOTE 2: The closest matching Intel AMIBIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/acma_p100/1002CB0_.BIO",
		L"roms/machines/acma_p100/1002CB0_.BI1", 0x1d000, 128);
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
machine_at_acma_spower_init(const machine_t *model)
{
	/* ACMA sPower 75 */
	/* ACMA sPower 90 */
	/* NOTE: These machines use an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset and*/
	/*       Intel AMIBIOS (1.00.02.BS0).                                                                           */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/acma_spower_75/1002BS0_.BIO",
		L"roms/machines/acma_spower_75/1002BS0_.BI1", 0x20000, 128);
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

/* ALR (Advanced Logic Research) */
int
machine_at_alr_optima_590_5120_init(const machine_t *model)
{
	/* ALR Optima SL 575  Model 1    */
	/* ALR Optima SL 575  Model 850B */
	/* ALR Optima    590             */
	/* ALR Optima SL 5100 Model 1    */
	/* ALR Optima SL 5100 Model 850B */
	/* ALR Optima    5120            */
	/* NOTE: These machines use an Intel Advanced/MN (Morrison32) system board with an Intel 84230FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.03.BT0).                                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/alr_optima_590_5120/1003BT0_.BIO",
		L"roms/machines/alr_optima_590_5120/1003BT0_.BI1", 0x20000, 128);
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
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

/* AMAX */
int
machine_at_amax_powerstation_66_init(const machine_t *model)
{
	/* AMAX PowerStation 66 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/amax_powerstation_66/1007af1_.bio",
		L"roms/machines/amax_powerstation_66/1007af1_.bi1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_amax_powerstation_init(const machine_t *model)
{
	/* AMAX 90MHz PowerStation */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)  */
	/*       chipset and Intel AMIBIOS                                                                        */
	/* NOTE 2: The closest matching ROM BIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/amax_powerstation/1006ax1_.rst",
		L"roms/machines/amax_powerstation/1006ax1_.rs1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_amax_powerstation_90_init(const machine_t *model)
{
	/* AMAX PowerStation 90 */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)  */
	/*       chipset and Intel AMIBIOS                                                                        */
	/* NOTE 2: The closest matching ROM BIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/amax_powerstation_90/1006ax1_.bio",
		L"roms/machines/amax_powerstation_90/1006ax1_.bi1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Ambra */
int
machine_at_ambradp60_init(const machine_t *model)
{
	/* Ambra DP60PCI */
	/* Ambra TP60PCI */
	/* NOTE: These machines use an Intel Premiere/PCI (Batman) system board with an Intel 82430LX (Mercury) */
	/*       chipset and Intel AMIBIOS                                                                      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ambradp60/1004AF1P.BIO",
		L"roms/machines/ambradp60/1004AF1P.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_ambradp90_init(const machine_t *model)
{
	/* Ambra DP90PCI */
	/* Ambra TP90PCI */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS                                                                        */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ambradp90/1002AX1P.BIO",
		L"roms/machines/ambradp90/1002AX1P.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* American Megatrends (AMI) */
int
machine_at_excalibur_init(const machine_t *model)
{
	/* AMI Excalibur VLB */
	int ret;
	ret = bios_load_linear_inverted(L"roms/machines/excalibur/S75P.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&opti5x7_device);
	device_add(&fdc37c661_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* American Multisystems */
int
machine_at_infogold_pentium_66_init(const machine_t *model)
{
	/* American Multisystems InfoGold Pentium/66 */
	int ret;
	ret = bios_load_linear(L"roms/machines/american_multisystems_infogold_66/AWMI0205.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_infogold_pentium_90_init(const machine_t *model)
{
	/* American Multisystems InfoGold Pentium/90 */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/american_multisystems_infogold_90/1006ax1_.rst",
		L"roms/machines/american_multisystems_infogold_90/1006ax1_.rs1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Ares Microdevelopment */
int
machine_at_ares_pentiumpro90_init(const machine_t *model)
{
	/* ARES Pentium Pro 90 */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS.                                                                      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ares_pentiumpro90/1006ax1_.rst",
		L"roms/machines/ares_pentiumpro90/1006ax1_.rs1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* AST Research (AST Computer) */
int
machine_at_ast_premmia_lx_p60_init(const machine_t *model)
{
	/* AST Premmia LX P/60 */
	/* NOTE: This machine uses an Intel Premiere/PCI Low Profile (Robin) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ast_premmia_mx/1010AU0Q.BIO",
		L"roms/machines/ast_premmia_mx/1010AU0Q.BI1", 0x1c000, 128);
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
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_zb_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_ast_premmia_gx_p90_init(const machine_t *model)
{
	/* AST Premmia GX P/90 Model 733 */
	/* AST Premmia GX P/100          */
	/* NOTE: These machines use a system board with an Intel 82430NX (Neptune) chipset and AST BIOS */
	/* NOTE 2: The AST Premmia LX P/60 ROM BIOS is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ast_premmia_gx_p90_model_733/1010AU0Q.BIO",
		L"roms/machines/ast_premmia_gx_p90_model_733/1010AU0Q.BI1", 0x1c000, 128);
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
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_zb_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_ast_advantage_8100p_init(const machine_t *model)
{
	/* AST Advantage! 8100p */
	/* AST Advantage! 8120p */
	/* AST Advantage! 8133p */
	/* NOTE: These machinese use an Intel Advanced/MN (Morrison32) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.06.BT0Q).                                                         */
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

/* AT&T */
/* AT&T Globalyst 590 */
/* See NCR 3346 */

/* AT&T Globalyst 600 */
/* See NCR 3356 */

/* ATronics International */
int
machine_at_atronics_ati_pentium_init(const machine_t *model)
{
	/* ATronics Pentium Pinnacle I */
	/* ATronics Pantera-66         */
	/* NOTE: These machines use an Asus system board with an Intel 82430LX (Mercury) chipset and Award BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/atronics_ati_pentium/AWMI0205.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

/* Austin (IPC) */
int
machine_at_austin_p5_60_init(const machine_t *model)
{
	/* Austin P5-60                 */
	/* Austin P5-66                 */
	/* Austin Premier P5-60 Desktop */
	/* Austin Power System 60       */
	/* Austin Deskside P5-66        */
	/* NOTE: These machines use an Intel Premiere/PCI (Batman) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_p66/1005AF1_.BIO",
		L"roms/machines/austin_p66/1005AF1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_austin_p66_init(const machine_t *model)
{
	/* Austin Communications Manager P66 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_p66/1007AF2_.BIO",
		L"roms/machines/austin_p66/1007AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_austin_edutainer_plus_init(const machine_t *model)
{
	/* Austin Edutainer Plus */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_edutainer_plus/1003AF2_.BIO",
		L"roms/machines/austin_edutainer_plus/1003AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_austin_power_system_90_init(const machine_t *model)
{
	/* Austin P90             */
	/* Austin Power System 90 */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_power_system_90/1006AX1_.RST",
		L"roms/machines/austin_power_system_90/1006AX1_.RS1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_austin_power_plus_75_init(const machine_t *model)
{
	/* Austin Power Plus 75 */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_power_plus_75/1012AX1_.RST",
		L"roms/machines/austin_power_plus_75/1012AX1_.RS1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_austin_power_plus_100_init(const machine_t *model)
{
	/* Austin Power Plus 100 */
	/* NOTE: This machine uses an Intel Advanced/ZP (Zappa)             system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_power_plus_120_133/1002BS0_.BIO",
		L"roms/machines/austin_power_plus_120_133/1002BS0_.BI1", 0x20000, 128);
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
machine_at_austin_power_plus_120_init(const machine_t *model)
{
	/* Austin Power Plus 120 */
	/* NOTE: This machine uses an Intel Advanced/ZE (Zappa A or Tahiti) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_power_plus_100_120/1004BR0_.BIO",
		L"roms/machines/austin_power_plus_100_120/1004BR0_.BI1", 0x20000, 128);
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
machine_at_austin_power_plus_120_bs0_init(const machine_t *model)
{
	/* Austin Power Plus 120 (BIOS version 1.00.02.BS0) */
	/* NOTE: This machine uses an Intel Advanced/ZP (Zappa)             system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_power_plus_120_133/1002BS0_.BIO",
		L"roms/machines/austin_power_plus_120_133/1002BS0_.BI1", 0x20000, 128);
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
machine_at_austin_power_plus_133_init(const machine_t *model)
{
	/* Austin Power Plus 133 */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor)          system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_power_plus_120_133/1002CB0_.BIO",
		L"roms/machines/austin_power_plus_120_133/1002CB0_.BI1", 0x1d000, 128);
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
machine_at_austin_powerplus_133_init(const machine_t *model)
{
	/* Austin PowerPlus 133 */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor)          system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_power_plus_120_133/1002CB0_.BIO",
		L"roms/machines/austin_power_plus_120_133/1002CB0_.BI1", 0x1d000, 128);
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
machine_at_austin_powerplus_133_2_init(const machine_t *model)
{
	/* Austin PowerPlus 133 (1.00.04.CB0) */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor)          system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_powerplus_133_166/1004CB0_.BIO",
		L"roms/machines/austin_powerplus_133_166/1004CB0_.BI1", 0x1d000, 128);
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
machine_at_austin_powerplus_166_init(const machine_t *model)
{
	/* Austin PowerPlus 166 */
	/* NOTE: This machine uses an Intel Advanced/EV (Endeavor)          system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_powerplus_133_166/1004CB0_.BIO",
		L"roms/machines/austin_powerplus_133_166/1004CB0_.BI1", 0x1d000, 128);
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
machine_at_austin_powerplus_75_init(const machine_t *model)
{
	/* Austin PowerPlus 75 */
	/* NOTE: This machine uses an Intel Advanced/ZP (Zappa)             system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_power_plus_120_133/1002BS0_.BIO",
		L"roms/machines/austin_power_plus_120_133/1002BS0_.BI1", 0x20000, 128);
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

/* Axik Computer */
int
machine_at_axik_ace_cache_586dx_66_cd_init(const machine_t *model)
{
	/* Axik Ace Cache 586DX-66/CD */
	/* NOTE: This machine uses a system board with an OPTi 495 or OPTi 895 (Python) chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/axik_ace_power_586_90pci/amibios_hot409.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_axik_ace_cache_586_66pci_mpc_init(const machine_t *model)
{
	/* Axik Ace Cache 586-66PCI/MPC */
	/* NOTE: This machine appears to use an Asus, Gigabyte, or FIC (First International Computer) system board */
	/*       with an Intel 82430LX (Mercury) chipset and Award BIOS (12/27/1993).                              */
	/* NOTE 2: The closest matching BIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/axik_ace_power_586_90pci/IS.34",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

/* Blackship */
int
machine_at_blackship_p90_neptune_init(const machine_t *model)
{
	/* Blackship P90 Neptune */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)  */
	/*       chipset and Intel AMIBIOS (1.00.10.AX1).                                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/blackship_p90_neptune/1010AX1_.BIO",
		L"roms/machines/blackship_p90_neptune/1010AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Blue Max */
/* See International Instrumentation */

/* Broadax Systems (BSi) */
int
machine_at_broadax_bsi_np7549d_init(const machine_t *model)
{
	/* Broadax BSi NP7549D */
	/* Broadax BSi NP7657D */
	/* Broadax BSi NP7659T */
	/* NOTE: These portable machines were manufactured by Nan Tan Computer and use a system board with an ACC Micro */
	/*       chipset and AMIBIOS (06/06/1992).                                                                      */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/broadax_np7549d/acc386.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&acc2168_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_broadax_bsi_np3656t_init(const machine_t *model)
{
	/* Broadax BSi NP3656T */
	/* NOTE: This portable machine was manufactured by Nan Tan Computer and uses a system board with an OPTi chipset and */
	/*       AMIBIOS (06/06/1992).                                                                                       */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/broadax_bsi_np3656t/opt495sx.ami",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Comp & Soft Experts */
int
machine_at_comp_n_soft_58660c512vlb_init(const machine_t *model)
{
	/* Comp & Soft CS 58660C512VLB */
	/* NOTE: This machine uses a TMC (Taiwan-MyComp) system board with an OPTi chipset and AMIBIOS (11/11/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/comp_n_soft_58660c512vlb/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* CompuAdd */
int
machine_at_compuadd_cp90p_init(const machine_t *model)
{
	/* CompuAdd CP90p Mini-Tower */
	/* CompuAdd CP90p Tower      */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.08.AX1)                                                          */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/compuadd_cp90p/1008AX1_.BIO",
		L"roms/machines/compuadd_cp90p/1008AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_compuadd_cp75p_init(const machine_t *model)
{
	/* CompuAdd CP75p Mini-Tower               */
	/* CompuAdd CP75p Tower                    */
	/* CompuAdd CP90p Mini-Tower (1.00.12.AX1) */
	/* CompuAdd CP90p Tower      (1.00.12.AX1) */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.12.AX1)                                                          */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/compuadd_cp75p/1012AX1_.BIO",
		L"roms/machines/compuadd_cp75p/1012AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_compuadd_cp100p_init(const machine_t *model)
{
	/* CompuAdd CP90p  Mini-Tower ( 0.7.02.BR0) */
	/* CompuAdd CP90p  Tower      ( 0.7.02.BR0) */
	/* CompuAdd CP100p Minitower                */
	/* CompuAdd CP100p Tower                    */
	/* NOTE: These machines use an Intel Advanced/ZE (Zappa E or Tahiti) system board with an Intel 82430FX */
	/*       (Triton) chipset and Intel AMIBIOS ( 0.7.02.BR0).                                              */
	/* NOTE 2: The closest matching Intel AMIBIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/compuadd_cp100p/1004BR0_.BIO",
		L"roms/machines/compuadd_cp100p/1004BR0_.BI1", 0x20000, 128);
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

/* Comtrade */
int
machine_at_comtrade_p590_init(const machine_t *model)
{
	/* Comtrade Professional P5/90 */
	/* Comtrade CAD/Publishing 590 */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.03.AX1Z)                                                         */
	/* NOTE 2: The closest matching Intel AMIBIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/comtrade_p590/1006AX1_.RST",
		L"roms/machines/comtrade_p590/1006AX1_.RS1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_comtrade_pci_566_init(const machine_t *model)
{
	/* Comtrade PCI Best Buy 566   */
	/* Comtrade CAD/Publishing 566 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board with an Intel 82430LX */
	/*       (Mercury) chipset and Intel AMIBIOS (1.00.07.AF2)                                             */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/comtrade_pci_566/1007AF2_.BIO",
		L"roms/machines/comtrade_pci_566/1007AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_comtrade_p75_p100_init(const machine_t *model)
{
	/* Comtrade Multimedia Tornado 4X    P75  */
	/* Comtrade Multimedia Dream Machine P100 */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.19.AX1).                                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/comtrade_p75_p100/1010AX1_.BIO",
		L"roms/machines/comtrade_p75_p100/1010AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Cornell Computer Systems */
int
machine_at_cornell_p5_60_pci_init(const machine_t *model)
{
	/* Cornell P5-60 PCI */
	/* NOTE: This machine uses an Asus system board with an Intel 82430LX (Mercury) chipset and Award BIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/cornell_p5_60_pci/AWMI0205.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_cornell_ultima_p100_init(const machine_t *model)
{
	/* Cornell Ultima/P100 */
	/* NOTE: This machine uses a system board with an Intel 82430NX (Neptune) chipset and Award BIOS */
	/*       (10/05/1994).                                                                           */
	/* NOTE 2: The closest matching BIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/cornell_ultima_p100/AWMI0401.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430nx_device);
	return ret;
}

/* Data Storage Marketing */
int
machine_at_datastor_p5_66_init(const machine_t *model)
{
	/* DataStor P5-66 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board with an Intel 82430LX */
	/*       (Mercury) chipset and Intel AMIBIOS (1.00.07.AF2)                                             */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/datastor_p5_66/1007AF2_.BIO",
		L"roms/machines/datastor_p5_66/1007AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_datastor_p5_90_init(const machine_t *model)
{
	/* DataStor P5-90 */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)  */
	/*       chipset and Intel AMIBIOS (1.00.03.AX1Z)                                                         */
	/* NOTE 2: The closest matching Intel AMIBIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/datastor_p5_90/1006AX1_.RST",
		L"roms/machines/datastor_p5_90/1006AX1_.RS1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430nx_device);
	return ret;
}

/* Dell Computer */
int
machine_at_dell_omniplex_560_566_init(const machine_t *model)
{
	/* Dell OmniPlex 560 */
	/* Dell OmniPlex 566 */
	/* NOTE: This machine uses a system board with an Intel 82430LX (Mercury) chipset. */
	/* NOTE 2: The Dell Dimension XPS P60 BIOS is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/dell_omniplex_560_566/XP60-A08.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_dfi_diamond_p100_init(const machine_t *model)
{
	/* DFI Diamond P90  */
	/* DFI Diamond P100 */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.10.AX1)                                                          */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/dfi_diamond_p100/1010AX1_.BIO",
		L"roms/machines/dfi_diamond_p100/1010AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Digital (DEC) */
int
machine_at_decpc_xl_560_566_init(const machine_t *model)
{
	/* Digital DECpc XL 560        (v1.01) (English) */
	/* Digital DECpc XL 566        (v1.01) (English) */
	/* Digital DECpc XL Server 560 (v1.01) (English) */
	/* Digital DECpc XL Server 566 (v1.01) (English) */
	/* NOTE: These machines use a system board with an Intel 82430LX (Mercury) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/EN5V101.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_decpc_xl_560_566_20_init(const machine_t *model)
{
	/* Digital DECpc XL 560        (v1.20) (English) */
	/* Digital DECpc XL 566        (v1.20) (English) */
	/* NOTE: These machines use a system board with an Intel 82430LX (Mercury) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V120_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_decpc_xl_560_566_21_init(const machine_t *model)
{
	/* Digital DECpc XL 560        (v1.21) (English) */
	/* Digital DECpc XL 566        (v1.21) (English) */
	/* NOTE: These machines use a system board with an Intel 82430LX (Mercury) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V121_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_decpc_xl_560_566_22_init(const machine_t *model)
{
	/* Digital DECpc XL 560        (v1.22) (English) */
	/* Digital DECpc XL 566        (v1.22) (English) */
	/* NOTE: These machines use a system board with an Intel 82430LX (Mercury) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V122_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_decpc_xl_560_566_200_init(const machine_t *model)
{
	/* Digital DECpc XL 560        (v2.00) (English) */
	/* Digital DECpc XL 566        (v2.00) (English) */
	/* Digital DECpc XL Server 560 (v2.00) (English) */
	/* Digital DECpc XL Server 566 (v2.00) (English) */
	/* NOTE: These machines use a system board with an Intel 82430LX (Mercury) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V200_en.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_decpc_xl_590_20_init(const machine_t *model)
{
	/* Digital DECpc XL 590        (v1.20) (English) */
	/* NOTE: These machines use a system board with an Intel 82430NX (Neptune) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V120_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_decpc_xl_590_21_init(const machine_t *model)
{
	/* Digital DECpc XL 590        (v1.21) (English) */
	/* NOTE: These machines use a system board with an Intel 82430NX (Neptune) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V121_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_decpc_xl_590_22_init(const machine_t *model)
{
	/* Digital DECpc XL 590        (v1.22) (English) */
	/* NOTE: These machines use a system board with an Intel 82430NX (Neptune) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V122_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_decpc_xl_590_200_init(const machine_t *model)
{
	/* Digital DECpc XL 590        (v2.00) (English) */
	/* Digital DECpc XL Server 590 (v2.00) (English) */
	/* NOTE: These machines use a system board with an Intel 82430NX (Neptune) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V200_en.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_decpc_xl_server_560_566_init(const machine_t *model)
{
	/* Digital DECpc XL Server 560 (v1.02) (English) */
	/* Digital DECpc XL Server 566 (v1.02) (English) */
	/* NOTE: These machines use a system board with an Intel 82430LX (Mercury) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V102_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_decpc_xl_server_560_566_2_init(const machine_t *model)
{
	/* Digital DECpc XL Server 560 (v1.03) (English) */
	/* Digital DECpc XL Server 566 (v1.03) (English) */
	/* NOTE: These machines use a system board with an Intel 82430LX (Mercury) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V103_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_decpc_xl_server_590_init(const machine_t *model)
{
	/* Digital DECpc XL Server 590 (v1.03) (English) */
	/* NOTE: These machines use a system board with an Intel 82430NX (Neptune) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V103_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_decpc_xl_server_590_4_init(const machine_t *model)
{
	/* Digital DECpc XL Server 590 (v1.04) (English) */
	/* NOTE: These machines use a system board with an Intel 82430NX (Neptune) chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V104_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430nx_device);
	return ret;
}

/* Dolch Computer Systems */
int
machine_at_dolch_a_pac_586_60c_init(const machine_t *model)
{
	/* Dolch P.A.C. 586    */
	/* Dolch A-PAC 586-60C */
	/* NOTE: These machines uses an AIR (Advanced Integration Research) 586MI system board which has three     */
	/*       16-bit ISA slots, three 32-bit VL-Bus slots, and one 8-bit slot, with a Socket 4 ZIF socket, four */
	/*       rows of 72-pin RAM slots, a 512 KB cache (512 KB maximum amount), a maximum of 128 MB of RAM, a   */
	/*       SiS chipset, and AMIBIOS.                                                                         */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/dolch_a_pac_586_60c/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_dolch_pac_586_br0_init(const machine_t *model)
{
	/* Dolch PAC 586 (BR0) */
	/* NOTE: This machine uses an Intel Advanced/ZE (Zappa E or Tahiti) system board with an Intel 82430FX */
	/*       (Triton) chipset and Intel AMIBIOS (1.00.03.BR0)                                              */
	/* NOTE 2: The closest matching Intel AMIBIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/dolch_pac_586_br0/BIOSBR0.REC",
		L"roms/machines/dolch_pac_586_br0/1004BR0_.BI1", 0x20000, 128);
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

/* DTK Computer */

/* DTK PAM-0030P */
/* DTK Quin-32   */
/* NOTE: These machines use a DTK PAM-0030P system board with an OPTi 895 (Python) chipset and Award BIOS */
/* NOTE 2: The closest matching DTK Award BIOS version is used until an original dump is available */
/* See m_at_386dx_486.c for DTK PKM-0038S E-2 */

int
machine_at_dtk_quin_35_init(const machine_t *model)
{
	/* DTK Quin-35         */
	/* DTK Quin-35   (106) */
	/* DTK PAM-0035S       */
	/* DTK PAM-0035S (106) */
	/* NOTE: This machine uses a DTK PAM-0035S system board with a SiS chipset and Award BIOS (4.50G) (10/18/94). */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_35/35s106.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c50x_common_init(model);
	device_add(&w83877f_device);
	return ret;
}

int
machine_at_dtk_quin_35_203_init(const machine_t *model)
{
	/* DTK Quin-35   (203) */
	/* DTK PAM-0035S (106) */
	/* NOTE: This machine uses a DTK PAM-0035S system board with a SiS chipset and Award BIOS (4.50G) (10/18/94). */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_quin_35/35s203.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c50x_common_init(model);
	device_add(&w83877f_device);
	return ret;
}

/* Duracom Computer Systems */
int
machine_at_duracom_desksaver_pentium_init(const machine_t *model)
{
	/* Duracom DeskSaver Pentium-PCI */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman) system board with an Intel 82430LX (Mercury) */
	/*       chipset and Intel AMIBIOS.                                                                    */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/duracom_desksaver_pentium_pci/1005AF1_.BIO",
		L"roms/machines/duracom_desksaver_pentium_pci/1005AF1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_duracom_586_66_init(const machine_t *model)
{
	/* Duracom 586/66 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board with an Intel 82430LX */
	/*       (Mercury) chipset and Intel AMIBIOS (1.00.07.AF2).                                            */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/duracom_586_66/1007AF2_.BIO",
		L"roms/machines/duracom_586_66/1007AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_duracom_filepro_586_90_init(const machine_t *model)
{
	/* Duracom FilePro 586/90 */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.03.AX1Z).                                                       */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/duracom_filepro_586_90/1006AX1_.BIO",
		L"roms/machines/duracom_filepro_586_90/1006AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430nx_device);
	return ret;
}

/* EPS Technologies */
int
machine_at_eps_p60_phantom_init(const machine_t *model)
{
	/* EPS P60 Phantom */
	/* NOTE: This machine uses a Gigabyte system board with an Intel 82430LX (Mercury) chipst and Award BIOS */
	/*       (4.50G) (1994)                                                                                  */
	/* NOTE 2: The closest matching BIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/eps_p60_phantom/IS.34",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_eps_p90_explorer_vl_pci_init(const machine_t *model)
{
	/* EPS P90 Explorer (models with    VL-Bus slots) */
	/* NOTE: This machine uses a SuperMicro system board with an OPTi Python (OPTi 895) chipset and AMIBIOS */
	/*       (12/15/1993)                                                                                   */
	/* NOTE 2: The closest matching BIOS update is used until an original dump is available */
	/* NOTE 3: This system board is disabled until emulation of it is more complete */
	int ret;
	ret = bios_load_linear(L"roms/machines/eps_p60_phantom/IS.34",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_eps_p90_explorer_pci_init(const machine_t *model)
{
	/* EPS P90 Explorer (models without VL-Bus slots) */
	/* EPS P90 Predator                               */
	/* NOTE: These machines use a Gigabyte system board with an Intel 82430NX (Neptune) chipst and Award BIOS */
	/*       (4.50G) (1994)                                                                                   */
	/* NOTE 2: The closest matching BIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/eps_p90_predator/IP.18",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430nx_device);
	return ret;
}

/* Epson */
int
machine_at_epson_endeavor_p60_init(const machine_t *model)
{
	/* Epson Endeavor P60 */
	/* NOTE: This machine uses an Intel Premiere/PCI LC (Robin) system board with an Intel 82430LX (Mercurt)  */
	/*       chipset and Intel AMIBIOS (1.00.07)                                                              */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/epson_endeavor_p60/1007AU0.BIO",
		L"roms/machines/epson_endeavor_p60/1007AU0.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

/* Ergo Computing */
int
machine_at_ergo_thunderbrick_init(const machine_t *model)
{
	/* Ergo ThunderBrick 100 */
	/* Ergo ThunderBrick 120 */
	/* Ergo ThunderBrick 133 */
	/* NOTE: These machines use an Intel system board with an Intel 82430FX (Triton) chipset and Intel AMIBIOS */
	/*       (05/10/1995).                                                                                     */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ergo_thunderbrick/1002CB0_.BIO",
		L"roms/machines/ergo_thunderbrick/1002CB0_.BI1", 0x1d000, 128);
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

/* Everex Systems */
int
machine_at_everex_step_sp_75_100_init(const machine_t *model)
{
	/* Everex Step SP/75  */
	/* Everex Step SP/100 */
	/* NOTE: These machines use a First International Computer (FIC) PN-2000 system board with an Intel 82430NX */
	/*       (Neptune) chipset and Award BIOS                                                                   */
	int ret;
	ret = bios_load_linear(L"roms/machines/everex_step_sp75/1560304b.awd",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x03, PCI_CARD_NORMAL, 1, 2, 3, 4);	/* 03 = Slot 1 */
	pci_register_slot(0x04, PCI_CARD_NORMAL, 2, 3, 4, 1);	/* 04 = Slot 2 */
	pci_register_slot(0x05, PCI_CARD_NORMAL, 3, 4, 1, 2);	/* 05 = Slot 3 */
	pci_register_slot(0x06, PCI_CARD_NORMAL, 4, 1, 2, 3);	/* 06 = Slot 4 */
	pci_register_slot(0x07, PCI_CARD_SCSI, 1, 2, 3, 4);		/* 07 = SCSI */
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&fdc_at_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430nx_device);
	device_add(&sio_device);
	/* device_add(&pc87306_device); */
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Future Micro */
int
machine_at_future_micro_intel_premiere_init(const machine_t *model)
{
	/* Future Micro Intel Premiere II */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS.                                                                      */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/future_micro_intel_premiere_ii/1012AX1_.BIO",
		L"roms/machines/future_micro_intel_premiere_ii/1012AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_future_micro_advanced_zp_init(const machine_t *model)
{
	/* Future Micro Intel Advanced/ZP */
	/* NOTE: This machine uses an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset */
	/*       and Intel AMIBIOS.                                                                                 */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/future_micro_intel_advanced_zp/1002BS0_.BIO",
		L"roms/machines/future_micro_intel_advanced_zp/1002BS0_.BI1", 0x20000, 128);
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

/* FutureTech */
int
machine_at_futuretech_futuremate_fm366t_init(const machine_t *model)
{
	/* FutureTech FutureMate FM366T */
	/* NOTE: This portable machine was manufactured by Nan Tan Computer and uses a system board with an OPTi chipset and */
	/*       AMIBIOS (06/06/1992).                                                                                       */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/futuretech_futuremate_fm366t/opt495sx.ami",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Gateway 2000 */
int
machine_at_gateway_p5_60_66_af1_init(const machine_t *model)
{
	/* Gateway 2000 P5-60 (1.00.06.AF1)  */
	/* Gateway 2000 P5-66 (1.00.06.AF1)  */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/gateway_p5_60_66_af1/1006af1_.bio",
		L"roms/machines/gateway_p5_60_66_af1/1006af1_.bi1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

/* Gateway 2000 */
int
machine_at_gateway_p5_60_66_init(const machine_t *model)
{
	/* Gateway 2000 P5-60           (1.00.08.AF2)  */
	/* Gateway 2000 P5-60 Family PC                */
	/* Gateway 2000 P5-66           (1.00.08.AF2)  */
	int ret;
	ret = bios_load_linear(L"roms/machines/gateway_p5_60_66/oldbios.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_gateway_p5_60_66_af2t_init(const machine_t *model)
{
	/* Gateway 2000 P5-60           (1.00.10.AF2T) */
	/* Gateway 2000 P5-60 Family PC (1.00.10.AF2T) */
	/* Gateway 2000 P5-66           (1.00.10.AF2T) */
	/* Gateway 2000 P5-66 Family PC (1.00.10.AF2T) */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/gateway_p5_60_66_af2t/1010af2t.bio",
		L"roms/machines/gateway_p5_60_66_af2t/1010af2t.bi1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_gateway_p5_90_ax1_init(const machine_t *model)
{
	/* Gateway 2000 P5-75           (1.00.09.AX1)  */
	/* Gateway 2000 P5-75 Family PC                */
	/* Gateway 2000 P5-90           (1.00.09.AX1)  */
	/* Gatewat 2000 P5-90 Family PC                */
	/* Gateway 2000 P5-90 XL        (1.00.09.AX1)  */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.09.AX1)                                                          */
	int ret;
	ret = bios_load_linear(L"roms/machines/gateway_p5_75_90_ax1/oldbios.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_gateway_p5_90_ax1t_init(const machine_t *model)
{
	/* Gateway 2000 P5-75           (1.00.12.AX1T) */
	/* Gateway 2000 P5-75 Family PC (1.00.12.AX1T) */
	/* Gateway 2000 P5-90           (1.00.12.AX1T) */
	/* Gateway 2000 P5-90 Family PC (1.00.12.AX1T) */
	/* Gateway 2000 P5-90 XL        (1.00.12.AX1T) */
	/* Gateway 2000 P5-100          (1.00.12.AX1T) */
	/* Gateway 2000 P5-100XL        (1.00.12.AX1T) */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS.                                                                       */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/gateway_p5_75_90_ax1t/1012ax1t.bio",
		L"roms/machines/gateway_p5_75_90_ax1t/1012ax1t.bi1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_gateway_p5_90_ax2t_init(const machine_t *model)
{
	/* Gateway 2000 P5-75           (1.00.13.AX1T) */
	/* Gateway 2000 P5-75 Family PC (1.00.13.AX1T) */
	/* Gateway 2000 P5-90           (1.00.13.AX1T) */
	/* Gateway 2000 P5-90 Family PC (1.00.13.AX1T) */
	/* Gateway 2000 P5-90 XL        (1.00.13.AX1T) */
	/* Gateway 2000 P5-100          (1.00.13.AX1T) */
	/* Gateway 2000 P5-100XL        (1.00.13.AX1T) */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS.                                                                       */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/gateway_p5_75_90_04_ax1t/1013ax1t.bio",
		L"roms/machines/gateway_p5_75_90_04_ax1t/1013ax1t.bi1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_gateway_p5_100_133_init(const machine_t *model)
{
	/* Gateway 2000 P5-75           (1.00.11.BS0T) */
	/* Gateway 2000 P5-75 Family PC (1.00.11.BS0T) */
	/* Gateway 2000 P5-90           (1.00.11.BS0T) */
	/* Gateway 2000 P5-90 Family PC (1.00.11.BS0T) */
	/* Gateway 2000 P5-100          (1.00.11.BS0T) */
	/* Gateway 2000 P5-120          (1.00.11.BS0T) */
	/* Gateway 2000 P5-133 Best Buy (1.00.11.BS0T) */
	/* NOTE: These machines use an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset*/
	/*       and Intel AMIBIOS (1.00.11.BS0T).                                                                  */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/gateway_p5_100_133/1011bs0t.bio",
		L"roms/machines/gateway_p5_100_133/1011bs0t.bi1", 0x20000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	/* pci_register_slot(0x0E, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 2, 3, 4, 1); */
	pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_gateway_p5_100_xl_init(const machine_t *model)
{
	/* Gateway 2000 P5-100XL        (1.00.10.BR0T) */
	/* Gateway 2000 P5-120XL        (1.00.10.BR0T) */
	/* Gateway 2000 P5-133XL        (1.00.10.BR0T) */
	/* Gateway 2000 10th Anniversary PC            */
	/* Gateway 2000 Holiday XL                     */
	/* NOTE: These machines use an Intel Advanced/AL (Alladin) system board with an Intel 82430FX (Triton)      */
	/*       chipset and Intel AMIBIOS (1.00.10.BR0T).                                                          */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/gateway_p5_aladdin/1010BR0T.bio",
		L"roms/machines/gateway_p5_aladdin/1010BR0T.bi1", 0x20000, 128);
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

/* Hertz Computer Corporation */
int
machine_at_hertz_p100e_init(const machine_t *model)
{
	/* Hertz        P90e  */
	/* Hertz        P100e */
	/* Hertz        P133e */
	/* Hertz Z-Pent P133e */
	/* Hertz Z-Pent P166e */
	/* NOTE: These machines use an Asus PCI/I-P54TP4 system board with an Intel 82430FX (Triton) chipset and */
	/*       Award BIOS (01/10/1995 for the Hertz P100e and 07/20/1995 for the Hertz P90e and Hertz P133e)   */
	/* NOTE 2: The Asus PCI/I-P54TP4 BIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/hertz_p100e/TX5I0202.AWD",
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

/* Hewitt Rand */
int
machine_at_hewitt_rand_hr_p5_90_panther_init(const machine_t *model)
{
	/* Hewitt Rand HR P5-90 Panther */
	/* NOTE: This machines uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS.                                                                       */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hewitt_rand_hr_p5_90_panther/1006AX1_.BIO",
		L"roms/machines/hewitt_rand_hr_p5_90_panther/1006AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_hewitt_rand_hr_p5_75_100_init(const machine_t *model)
{
	/* Hewitt Rand HR P5-75 Tower */
	/* Hewitt Rand HR P5-100      */
	/* NOTE: This machines uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.12.AX1).                                                         */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hewitt_rand_hr_p5_75_100/1012AX1_.BIO",
		L"roms/machines/hewitt_rand_hr_p5_75_100/1012AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_hewitt_rand_hr_p5_133_tower_init(const machine_t *model)
{
	/* Hewitt Rand HR P5-133 Tower */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       and Intel AMIBIOS (05/17/1995).                                                                */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hewitt_rand_hr_p5_133_tower/1002CB0_.BIO",
		L"roms/machines/hewitt_rand_hr_p5_133_tower/1002CB0_.BI1", 0x1d000, 128);
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

/* Hewlett Packard */
int
machine_at_hp_pavilion_5030_7055_init(const machine_t *model)
{
	/* HP Pavilion 5030  (7130p BIOS) */
	/* HP Pavilion 5040  (7130p BIOS) */
	/* HP Pavilion 7010  (7130p BIOS) */
	/* HP Pavilion 7020  (7130p BIOS) */
	/* HP Pavilion 7030  (7130p BIOS) */
	/* HP Pavilion 7050S (7130p BIOS) */
	/* HP Pavilion 7055  (7130p BIOS) */
	/* NOTE: These machines use an Intel Advanced/MN (Morrison32) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (1.00.09.BT0L) (08/03/1995).                                           */
	/* NOTE 2: The HP Pavilion 7130p BIOS is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hp_pavilion_7130p/1002CH0L.BIO",
		L"roms/machines/hp_pavilion_7130p/1002CH0L.BI1", 0x20000, 128);
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
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	/* machine_at_thor_common_init(model, 0); */
	return ret;
}

#if defined(DEV_BRANCH) && defined(USE_VECTRA54)
int
machine_at_vectra54_init(const machine_t *model)
{
	/* Hewlett-Packard Vectra VL 4 5/120 */
	/* Hewlett-Packard Vectra VL 4 5/133 */
	/* Hewlett-Packard Vectra 500 Model 515MCx 5/166 */
	int ret;
	ret = bios_load_linear(L"roms/machines/vectra54/GT0724.22",
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
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&fdc37c932qf_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}
#endif

/* HiQ (HiQuality) */
int
machine_at_hiq_p66_pentium_init(const machine_t *model)
{
	/* HiQ P66 Pentium Graphics Ultra Station */
	/* NOTE: These machines use a TMC (Taiwan-MyComp) system board with an OPTi chipset and AMIBIOS (11/11/1992).*/
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/hiq_p66_pentium/amibios-40-0200-001107-00101111-111192-OP495SLC.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_hiq_neptune_ii_p66_pci_init(const machine_t *model)
{
	/* HiQ Neptune II P66/PCI */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board with an Intel 82430LX    */
	/*       (Mercury) chipset and Intel AMIBIOS (1.00.07.AF2).                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hiq_neptune_ii_p66_pci/1007AF2_.BIO",
		L"roms/machines/hiq_neptune_ii_p66_pci/1007AF2_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_hiq_neptune_ii_p90_pci_init(const machine_t *model)
{
	/* HiQ Neptune II P90/PCI */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)  */
	/*       chipset and Intel AMIBIOS (1.00.06.AX1).                                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hiq_neptune_ii_p90_pci/1006AX1_.BIO",
		L"roms/machines/hiq_neptune_ii_p90_pci/1006AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_hiq_saturn_p100_init(const machine_t *model)
{
	/* HiQ Saturn Station */
	/* HiQ Saturn P100    */
	/* NOTE: These machines use an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset */
	/*       and Intel AMIBIOS (1.00.01.BS0 for the HiQ Saturn Station and 1.00.02.BS0 from 05/05/1995  for the  */
	/*       HiQ Saturn P100).                                                                                   */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/hiq_saturn_p100/1002BS0_.BIO",
		L"roms/machines/hiq_saturn_p100/1002BS0_.BI1", 0x20000, 128);
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

/* HyperData Technology */
int
machine_at_hyperdata_hyperbook_900a_init(const machine_t *model)
{
	/* HyperData HyperBook 900A */
	/* NOTE: This portable machine was manufactured by Sunrex and uses a system board with an OPTi chipset and AMIBIOS */
	/*       (02/17/1995).                                                                                             */
	/* NOTE 2: The closest AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/hyperdate_hyperbook_900a/486-V4P895P3-SMT.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Infotel */
/* See MidWest Micro */

/* Insight */
int
machine_at_insight_pci_p60_cd_init(const machine_t *model)
{
	/* Insight PCI P60 CD */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman) system board with an Intel 82430LX (Mercury) */
	/*       chip set and Intel AMIBIOS (09/20/1993)                                                       */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/insight_pci_p60_cd/BIOSAF1.REC",
		L"roms/machines/insight_pci_p60_cd/1005AF1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_insight_pci_p60_mm_init(const machine_t *model)
{
	/* Insight PCI P60 MM */
	/* Insight PCI P66 MM */
	/* Insight P60 PCI TW */
	/* NOTE: These machines use an Intel Premiere/PCI (Batman's Revenge) system board with an Intel 82430LX   */
	/*       (Mercury) chipset and Intel AMIBIOS (1.00.07.AF2).                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/insight_pci_p60_mm/1007AF2_.BIO",
		L"roms/machines/insight_pci_p60_mm/1007AF2_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_insight_pci_p90_mm_init(const machine_t *model)
{
	/* Insight PCI P90 MM      */
	/* Insight P90 Special PCI */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.08.AX1).                                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/insight_pci_p90_mm/1008AX1_.BIO",
		L"roms/machines/insight_pci_p90_mm/1008AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_insight_pci_p75_mm_init(const machine_t *model)
{
	/* Insight PCI P75 MM      */
	/* NOTE: This machine use  an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.12.AX1).                                                        */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/insight_pci_p75_mm/1012AX1_.BIO",
		L"roms/machines/insight_pci_p75_mm/1012AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_insight_pci_p100_mm_init(const machine_t *model)
{
	/* Insight PCI P100 MM */
	/* Insight Hemisphere PCI P100 MM */
	/* Insight PCI P120 MM */
	/* NOTE: These machines use an Intel Advanced/EV (Endeavor) system board with an Intel 82430FX (Triton) */
	/*       chipset and Intel AMIBIOS (01/12/1995).                                                        */
	/* NOTE 2: The closest matching Intel AMIBIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/insight_pci_p100_mm/1003CB0_.BIO",
		L"roms/machines/insight_pci_p100_mm/1003CB0_.BI1", 0x1d000, 128);
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

/* Intelesys */
int
machine_at_intelesys_star_75_init(const machine_t *model)
{
	/* Intelesys Star 75 */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.12.AX1).                                                        */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/intelesys_star_75/1012AX1_.BIO",
		L"roms/machines/intelesys_star_75/1012AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* International Instrumentation */
int
machine_at_blue_max_monolith_75_init(const machine_t *model)
{
	/* Blue Max Monolith Business Partner P5 */
	/* NOTE: These machines use a system board with an OPTi chipset and AMIBIOS (10/19/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blue_max_monolith_business_partner_75/386-opti-mini.bio",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* International Upgrade Source */
int
machine_at_intel_pci_premier_init(const machine_t *model)
{
	/* International Upgrade Source Intel PCI Premier */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge ) system board with an Intel 82430LX */
	/*       (Mercury) chipset and Intel AMIBIOS.                                                           */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/international_upgrade_source_intel_pci_premier/1007AF2_.BIO",
		L"roms/machines/international_upgrade_source_intel_pci_premier/1007AF2_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

/* Itautec */
int
machine_at_itautec_infoway_multimidia_init(const machine_t *model)
{
	/* Itautec InfoWay Multimidia */
	/* NOTE: This machine uses an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset */
	/*       and Intel AMIBIOS.                                                                                 */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/itautec_infoway_multimidia/1002BS0_.BIO",
		L"roms/machines/itautec_infoway_multimidia/1002BS0_.BI1", 0x20000, 128);
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

/* Maximus Computers */
int
machine_at_maximus_powermax_init(const machine_t *model)
{
	/* Maximus PowerMax */
	/* NOTE: This portable machine was manufactured by Sunrex and uses a system board with an OPTi chipset and AMIBIOS */
	/*       (02/17/1995).                                                                                             */
	/* NOTE 2: The closest AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/maximus_powermax/486-V4P895P3-SMT.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Media On */
int
machine_at_media_on_mp60_66_init(const machine_t *model)
{
	/* Media On MP60  */
	/* Media On MP66  */
	/* NOTE: These machines use a slimline case design that was almost exclusively used for Intel system boards  */
	/*       and so most likely use an Intel Premiere/PCI Low Profile (Robin) system board with an Intel 82430LX */
	/*       (Mercury) chipset and Intel AMIBIOS.                                                                */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/media_on_mp60_66/1010AU0_.BIO",
		L"roms/machines/media_on_mp60_66/1010AU0_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_media_on_mp75_90_100_init(const machine_t *model)
{
	/* Media On MP75  */
	/* Media On MP90  */
	/* Media On MP100 */
	/* NOTE: These machines use a slimline case design that was almost exclusively used for Intel system boards  */
	/*     and so most likely use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX */
	/*       (Neptune) chipset and Intel AMIBIOS.                                                                */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/media_on_mp75_90_100/1007BF0_.BIO",
		L"roms/machines/media_on_mp75_90_100/1007BF0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Mega Computer Systems */
int
machine_at_mega_impact_v60pci_plus_init(const machine_t *model)
{
	/* Mega Impact V-60PCI+ */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman) system board with an Intel 82430LX (Mercury) */
	/*       chipset and Intel AMIBIOS (1.00.05.AF1).                                                      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/mega_impact_v60pci_plus/1005AF1_.BIO",
		L"roms/machines/mega_impact_v60pci_plus/1005AF1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

/* Memorex Telex */
int
machine_at_memorex_telex_celerria_lp90_init(const machine_t *model)
{
	/* Memorex Telex Celerria LP90 */
	/* NOTE: This machine uses an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX */
	/*       (Neptune) chipset and Intel AMIBIOS (05/02/1994).                                                */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/memorex_telex_celerria_lp90/1007BF0_.BIO",
		L"roms/machines/memorex_telex_celerria_lp90/1007BF0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Micro Express */
int
machine_at_microflex_vl_pentium_init(const machine_t *model)
{
	/* Micro Express MicroFlex-VL/Pentium    */
	/* Micro Express MicroFlex-VL/P60        */
	/* Micro Express MicroFlex-VL/P66        */
	/* NOTE: These machines use a system board with an OPTi 895 (Python) chipset and AMIBIOS (12/17/1993) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/microflex_vl_pentium_90/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_microflex_vl_pentium_90_init(const machine_t *model)
{
	/* Micro Express MicroFLEX-VL/Pentium/90 */
	/* NOTE: This machine uses a system board with an OPTi 895 (Python) chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/microflex_vl_pentium_90/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Micron Electronics */
int
machine_at_micron_p90pci_powerstation_init(const machine_t *model)
{
	/* Micron P90PCI PowerStation */
	/* Micron P90 Home MPC        */
	/* NOTE: These machines use a Micronics M54Pi system board with an Intel 82430NX (Neptune) chipset and */
	/*       Phoenix BIOS.                                                                                 */
	int ret;
	ret = bios_load_linear(L"roms/machines/micron_p90pci/BIOS.N21OLD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x03, PCI_CARD_NORMAL, 1, 2, 3, 4);	/* 03 = Slot 1 */
	pci_register_slot(0x04, PCI_CARD_NORMAL, 2, 3, 4, 1);	/* 04 = Slot 2 */
	pci_register_slot(0x05, PCI_CARD_NORMAL, 3, 4, 1, 2);	/* 05 = Slot 3 */
	pci_register_slot(0x06, PCI_CARD_NORMAL, 4, 1, 2, 3);	/* 06 = Slot 4 */
	pci_register_slot(0x07, PCI_CARD_SCSI, 1, 2, 3, 4);		/* 07 = SCSI */
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&fdc_at_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&fdc37c663_device);
	/* device_add(&intel_flash_bxt_device); */
	device_add(&i430nx_device);
	return ret;
}

/* MicroSource */
int
machine_at_microsource_premier_pci_init(const machine_t *model)
{
	/* MicroSource Tempest Premier/PCI */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman) system board with an Intel 430LX (Mercury) chipset and */
	/*       Intel AMIBIOS (1.00.06.AF1).                                                                            */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/microsource_tempest_premier_pci/1006AF1_.BIO",
		L"roms/machines/microsource_tempest_premier_pci/1006AF1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

/* MidWest Micro (later Systemax) */
int
machine_at_midwest_micro_elite_p5_60_init(const machine_t *model)
{
	/* MidWest Micro Elite P5-60 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman) system board with an Intel 82430LX (Mercury) */
	/*       chipset and Intel AMIBIOS (1.00.03.AF1).                                                      */
	/* NOTE 2: The closest matching Intel AMIBIOS update is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/midwest_micro_elite_p5_60/1005AF1_.BIO",
		L"roms/machines/midwest_micro_elite_p5_60/1005AF1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_midwest_micro_elite_p5_66_init(const machine_t *model)
{
	/* MidWest Micro Elite P5-66 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman) system board with an Intel 82430LX (Mercury) */
	/*       chipset and Intel AMIBIOS (1.00.07.AF2).                                                      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/midwest_micro_elite_p5_66/1007AF2_.BIO",
		L"roms/machines/midwest_micro_elite_p5_66/1007AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_midwest_micro_elite_p5_90_init(const machine_t *model)
{
	/* MidWest Micro Elite P5-90 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.06.AX1).                                                      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/midwest_micro_elite_p5_90/1006AX1_.BIO",
		L"roms/machines/midwest_micro_elite_p5_90/1006AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_midwest_micro_home_p5_90_init(const machine_t *model)
{
	/* MidWest Micro Elite P5-90 (1.00.08.AX1) */
	/* MidWest Micro Elite Home PC P5-90       */
	/* NOTE: These machines use an Intel Premiere/PCI (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.08.AX1).                                                      */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/midwest_micro_elite_p5_90/1008AX1_.BIO",
		L"roms/machines/midwest_micro_elite_p5_90/1008AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_midwest_micro_p5_75_init(const machine_t *model)
{
	/* MidWest Micro P5-75 Office PC */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.17).                                                            */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/midwest_micro_p5_75/1012AX1_.BIO",
		L"roms/machines/midwest_micro_p5_75/1012AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_midwest_micro_p5_100_120_init(const machine_t *model)
{
	/* MidWest Micro  Home  PC P5-100 PCI */
	/* MidWest Micro  Home  PC P5-120 PCI */
	/* MidWest Micro Office PC P5-100 PCI */
	/* MidWest Micro Office PC P5-120 PCI */
	/* NOTE: These machines use an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset */
	/*       and Intel AMIBIOS (01/12/1995 or 05/05/1995/1.00.02.BS0).                                           */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/midwest_micro_p5_100_120/1002BS0_.BIO",
		L"roms/machines/midwest_micro_p5_100_120/1002BS0_.BI1", 0x20000, 128);
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
machine_at_midwest_micro_p590_init(const machine_t *model)
{
	/* MidWest Micro P590 Home PC */
	/* NOTE: This machine uses an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset */
	/*       and Intel AMIBIOS (05/05/1995/1.00.02.BS0).                                                        */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/midwest_micro_p590/1002BS0_.BIO",
		L"roms/machines/midwest_micro_p590/1002BS0_.BI1", 0x20000, 128);
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

/* Mitsuba */
int
machine_at_mitsuba_professional_pentium_init(const machine_t *model)
{
	/* Mitsuba Professional Pentium */
	/* NOTE: This machine uses a system board with an OPTi 895 (Python) chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/mitsuba_professional_pentium/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_mitsuba_fileserver_p_90_init(const machine_t *model)
{
	/* Mitsuba Fileserver-P-90 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.06.AX1).                                                     */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/mitsuba_fileserver_p_90/1006AX1_.BIO",
		L"roms/machines/mitsuba_fileserver_p_90/1006AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* MS Engineering */
int
machine_at_mse_pentium_p_init(const machine_t *model)
{
	/* MSE Pentium-P */
	/* NOTE: This machine uses an Asus system board with an Intel 82430LX (Mercury) chipset and Award BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/mse_pentium_p/AWMI0205.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

/* National MicroComputers */
int
machine_at_nmc_expert_p66_init(const machine_t *model)
{
	/* NMC Expert-System P66 */
	/* NOTE: This machine uses an Elitegroup system board with an Intel 82430LX (Mercury) chipset and Award BIOS */
	/* NOTE 2: The closest matching Award ROM BIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/nmc_expert_system_p66/AWMI0205.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x03, PCI_CARD_NORMAL, 1, 2, 3, 4);	/* 03 = Slot 1 */
	pci_register_slot(0x04, PCI_CARD_NORMAL, 2, 3, 4, 1);	/* 04 = Slot 2 */
	pci_register_slot(0x05, PCI_CARD_NORMAL, 3, 4, 1, 2);	/* 05 = Slot 3 */
	pci_register_slot(0x06, PCI_CARD_NORMAL, 4, 1, 2, 3);	/* 06 = Slot 4 */
	pci_register_slot(0x07, PCI_CARD_SCSI, 1, 2, 3, 4);		/* 07 = SCSI */
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&fdc_at_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&sio_device);
	/* According to PC Magazine, this machine does not support this feature */
	/* device_add(&intel_flash_bxt_device); */
	device_add(&i430lx_device);
	return ret;
}

/* NCR (National Cash Register) */
int
machine_at_ncr_3260_init(const machine_t *model)
{
	/* NCR 3260 */
	/* NOTE: This machine uses an Intel Premiere/PCI Low Profile (Robin) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3260/1010AU0_.BIO",
		L"roms/machines/ncr_3260/1010AU0_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_ncr_3346_init(const machine_t *model)
{
	/* NCR 3346 (AT&T Globalyst 590) */
	/* NOTE: This machine uses an Intel Premiere/PCI Low Profile (Robin) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3346/1003AU0B.BIO",
		L"roms/machines/ncr_3346/1003AU0B.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_ncr_3346_04_init(const machine_t *model)
{
	/* NCR 3346 (AT&T Globalyst 590) (BIOS version 1.00.04.AU0B) */
	/* NOTE: This machine uses an Intel Premiere/PCI Low Profile (Robin) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3346/1004AU0B.BIO",
		L"roms/machines/ncr_3346/1004AU0B.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_ncr_3346_05_init(const machine_t *model)
{
	/* NCR 3346 (AT&T Globalyst 590) (BIOS version 1.00.05.AU0B) */
	/* NOTE: This machine uses an Intel Premiere/PCI Low Profile (Robin) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3346/1005AU0B.BIO",
		L"roms/machines/ncr_3346/1005AU0B.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_ncr_3346_09_init(const machine_t *model)
{
	/* NCR 3346 (AT&T Globalyst 590) (BIOS version 1.00.09.AU0 ) */
	/* NOTE: This machine uses an Intel Premiere/PCI Low Profile (Robin) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3346/1009AU0_.BIO",
		L"roms/machines/ncr_3346/1009AU0_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_ncr_3356_init(const machine_t *model)
{
	/* NCR 3356 (AT&T Globalyst 600) */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS.                                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3356/1003BF0_.BIO",
		L"roms/machines/ncr_3356/1003BF0_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_ncr_3356_beta_init(const machine_t *model)
{
	/* NCR (3356 (AT&T Globalyst 600) (BETA/NFR) */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS.                                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3356/BIOSBF0.REC",
		L"roms/machines/ncr_3356/BIOSBF0.RE1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_ncr_3356_07_init(const machine_t *model)
{
	/* NCR 3356 (AT&T Globalyst 600) (BIOS version 1.00.07.BF0B) */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS.                                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3356/1007BF0B.BIO",
		L"roms/machines/ncr_3356/1007BF0B.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_ncr_3356_08_init(const machine_t *model)
{
	/* NCR 3356 (AT&T Globalyst 600) (BIOS version 1.00.08.BF0B) */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS.                                                               */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3356/1008BF0B.BIO",
		L"roms/machines/ncr_3356/1008BF0B.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_ncr_3249_init(const machine_t *model)
{
	/* NCR 3249 */
	/* NOTE: This machine uses an Intel Advanced/MN LPX/S (Talladega) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3249/BIOSCH0.REC",
		L"roms/machines/ncr_3249/BIOSCH0.RE1", 0x20000, 128);
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
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&pc87306_device);
	device_add(&intel_flash_bxt_ami_device);
	return ret;
}

int
machine_at_ncr_3249_06_init(const machine_t *model)
{
	/* NCR 3249 (BIOS version 1.00.06.CH0) */
	/* NOTE: This machine uses an Intel Advanced/MN LPX/S (Talladega) system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ncr_3249/1006CH0_.BIO",
		L"roms/machines/ncr_3249/1006CH0_.BI1", 0x20000, 128);
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

/* NEC Technologies */
int
machine_at_nec_powermate_p60d_init(const machine_t *model)
{
	/* NEC Image     P60D */
	/* NEC Image     P60M */
	/* NEC PowerMate P60D */
	/* NEC PowerMate P60M */
	/* NEC Ready     P60M */
	/* NOTE: These machines use an Intel Premiere/PCI LC (Robin LC) system board with an Intel 82430LX (Mercury)*/
	/*       chipset and Intel AMIBIOS (1.00.01.BC0K)                                                           */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/nec_powermate_p60d/1004BC0_.BIO",
		L"roms/machines/nec_powermate_p60d/1004BC0_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_powermate_v_init(const machine_t *model)
{
    /* NEC PowerMate V100 */
	int ret;
    ret = bios_load_linear(L"roms/machines/powermate_v/BIOS.ROM",
			   0x000e0000, 131072, 0);
    if (bios_only || !ret)
	return ret;
    machine_at_common_init(model);
    pci_init(PCI_CONFIG_TYPE_1);
    pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x07, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
    pci_register_slot(0x08, PCI_CARD_NORMAL, 0, 0, 0, 0);
    pci_register_slot(0x11, PCI_CARD_NORMAL, 1, 2, 3, 4);
    pci_register_slot(0x13, PCI_CARD_NORMAL, 2, 3, 4, 1);
    device_add(&keyboard_ps2_ami_pci_device);
    device_add(&i430fx_device);
    device_add(&piix_device);
    device_add(&fdc37c665_device);
    device_add(&intel_flash_bxt_device);
    return ret;
}

/* NETiS Technology */
int
machine_at_netis_n566vl_init(const machine_t *model)
{
	/* NETiS Pentium N566VL */
	/* NOTE: This machine uses a TMC system board with an OPTi 895 (Python) chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/netis_n566vl/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_netis_n566p_init(const machine_t *model)
{
	/* NETiS N566P                 */
	/* NETiS N566 Best Buy         */
	/* NETiS Pentium N566 Best Buy */
	/* NETiS N566M                 */
	/* NOTE: These machines use an Asus system board with an Intel 82430LX (Mercury) chipset and Award BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/netis_n566_n590/AWMI0205.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_netis_n590p_pci_system_init(const machine_t *model)
{
	/* NETiS N590P PCI System */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.10.AX1).                                                        */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/netis_n590p_pci_system/1010AX1_.BIO",
		L"roms/machines/netis_n590p_pci_system/1010AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_netis_budget_n5100p_init(const machine_t *model)
{
	/* NETiS Budget N5100P */
	/* NOTE: This machine uses an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset */
	/*       and Intel AMIBIOS (05/05/1995/1.00.02.BS0).                                                        */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/netis_budget_n5100p/1002BS0_.BIO",
		L"roms/machines/netis_budget_n5100p/1002BS0_.BI1", 0x20000, 128);
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

/* Novacor */
int
machine_at_novacor_novas_init(const machine_t *model)
{
	/* Novacor Novas */
	/* NOTE: This machine uses an American Digicom system board with an OPTi chipset and AMIBIOS (10/12/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/novacor_novas/386-opti-mini.bio",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_novacor_nova_pentium_90_init(const machine_t *model)
{
	/* Novacor Nova Pentium 90 */
	/* NOTE: This machine uses an Intel system board manufactured under the American Digicom brand name with an */
	/*       Intel 82430NX (Neptune) chipset and Intel AMIBIOS (1.00.03.AX1Z).                                  */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/novacor_nova_pentium_90/1006AX1_.BIO",
		L"roms/machines/novacor_nova_pentium_90/1006AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Olivetti */
int
machine_at_olivetti_modulo_m4_82_init(const machine_t *model)
{
	/* Olivetti Modulo M4-82 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board with an Intel 82430LX (Mercury)*/
	/*       chipset and Intel AMIBIOS (1.00.06.AF2).                                                               */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/olivetti_modulo_m4_82/1007AF2_.BIO",
		L"roms/machines/olivetti_modulo_m4_82/1007AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

/* Packard Bell */
int
machine_at_pb520_init(const machine_t *model)
{
	/* Packard Bell Legend 5000      */
	/* Packard Bell Pentium Computer */
	/* NOTE: These machines use a system board manufactured by Intel for Packard Bell under the PB520  name using*/
	/*       the Intel Premiere/PCI LC (Robin) system board with an Intel 82430LX (Mercury) chipset and Intel    */
	/*       AMIBIOS (1.00.05.AU0R)                                                                              */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/pb520r/1006AU0R.BIO",
		L"roms/machines/pb520r/1006AU0R.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_pb520r_init(const machine_t *model)
{
	/* Packard Bell Accel 1602D   */
	/* Packard Bell Accel 1707D   */
	/* Packard Bell Executive 560 */
	/* Packard Bell Legend 300CD  */
	/* Packard Bell Legend 322CDT */
	/* Packard Bell Legend 60CD Supreme */
	/* Packard Bell Pack-Mate 3960CD    */
	/* NOTE: These machines use a system board manufactured by Intel for Packard Bell under the PB520R name with */
	/*       an Intel 82430LX (Mercury) chipset and Intel AMIBIOS (1.00.09.BC0R)                                 */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/pb520r/1009BC0R.BIO",
		L"roms/machines/pb520r/1009BC0R.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_pb540_init(const machine_t *model)
{
	/* Packard Bell Force 2738 D/4 */
	/* Packard Bell Force 2742 T/4 */
	/* Packard Bell Force 443CD    */
	/* Packard Bell Legend 100CD   */
	/* Packard Bell Legend 105CD   */
	/* Packard Bell Legend 110CDT  */
	/* Packard Bell Legend 436CDT  */
	/* Packard Bell Legend 70CD Supreme */
	/* Packard Bell Multimedia Pentium PC */
	/* Packard Bell Pack-Mate 3987CD    */
	/* Packard Bell Pack-Mate 4990CD    */
	/* NOTE: These machines use a system board manufactured by Intel for Packard Bell under the PB540  name with */
	/*       an Intel 82430NX (Neptune) chipset and Intel AMIBIOS (1.00.12.BB0R)                                 */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/pb540/1012BB0R.BIO",
		L"roms/machines/pb540/1012BB0R.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_pb570_init(const machine_t *model)
{
	/* Packard Bell Executive 590T              */
	/* Packard Bell Force 482CDT                */
	/* Packard Bell Force 860CD                 */
	/* Packard Bell Force 872CDT                */
	/* Packard Bell Legend 401CD                */
	/* Packard Bell Legend 402CD                */
	/* Packard Bell Legend 403CD                */
	/* Packard Bell Legend 406CD                */
	/* Packard Bell Legend 408CD                */
	/* Packard Bell Legend 410CDT               */
	/* Packard Bell Legend 418CDT               */
	/* Packard Bell Legend 423CDT               */
	/* Packard Bell Multi-Media Corner 90 (C90) */
	/* Packard Bell Pentium 100 Designer Tower  */
	/* NOTE: These machines use a system board manufactured by Intel for Packard Bell under the PB570 name with */
	/*       an Intel 82430FX (Triton) chipset and Intel AMIBIOS (1.00.06.BY0R)                                 */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/pb570/1007by0r.bio",
		L"roms/machines/pb570/1007by0r.bi1", 0x1d000, 128);
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

/* PC Express */
int
machine_at_pc_express_exp90_init(const machine_t *model)
{
	/* PC Express EXP90 */
	/* NOTE: This machine uses an Intel system board with an Intel 82430NX (Neptune) chipset and Intel AMIBIOS */
	/*       I(1.00.03.AX1Z).                                                                                  */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/pc_express_exp90/1006AX1_.BIO",
		L"roms/machines/pc_express_exp90/1006AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* PC Partner */
int
machine_at_mb500n_init(const machine_t *model)
{
	/* PC Partner MB500N */
	int ret;
	ret = bios_load_linear(L"roms/machines/mb500n/031396s.bin",
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
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430fx_device);
	device_add(&piix_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Personal Computer Graphics */
int
machine_at_pcg_burstar_p90_init(const machine_t *model)
{
	/* PCG BurSTar P90 */
	/* NOTE: This machine uses an Intel system board with an Intel 82430NX (Neptune) chipset and Intel AMIBIOS */
	/*       I(1.00.03.AX1Z).                                                                                  */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/pcg_burstar_p90/1006AX1_.BIO",
		L"roms/machines/pcg_burstar_p90/1006AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Polywell */
int
machine_at_polywell_poly_590ip_init(const machine_t *model)
{
	/* Polywell Poly 586-90VIP */
	/* Polywell Poly 590IP     */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS                                                                        */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/poly_590ip/1006AX1_.BIO",
		L"roms/machines/poly_590ip/1006AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_polywell_poly_575ip_init(const machine_t *model)
{
	/* Polywell Poly 575IP     */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.10.AX1).                                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/poly_575ip/1010AX1_.BIO",
		L"roms/machines/poly_575ip/1010AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_polywell_poly_586_90vlb_init(const machine_t *model)
{
	/* Polywell Poly 586-66V1  */
	/* Polywell Poly 586-90VLB */
	/* NOTE: The second machine uses a TMC system board with an OPTi 895 (Python) chipset and AMIBIOS    */
	/*       (03/01/1994). The first machine's system board still has yet to be identified but is likely */
	/*       similar to the second system.                                                               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/poly_586_90vlb/486-V4P895P3-SMT.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Precision Systems Group */
int
machine_at_precision_pti_66_init(const machine_t *model)
{
	/* Precision PTI-66 */
	/* NOTE: This machine uses an Intel Premiere/PCI (Batman's Revenge) system board with an Intel 82430LX */
	/*       (Mercury) chipset and Intel AMIBIOS (1.00.03.AF2).                                            */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/precision_pti_66/1003AF2_.BIO",
		L"roms/machines/precision_pti_66/1003AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_precision_pti_90_init(const machine_t *model)
{
	/* Precision PTI-90 */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.08.AX1).                                                        */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/precision_pti_90/1008AX1_.BIO",
		L"roms/machines/precision_pti_90/1008AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Quantex Microsystems */
int
machine_at_quantex_qp5_60_66_init(const machine_t *model)
{
	/* Quantex QP5/60B-1   */
	/* Quantex QP5/60B-2   */
	/* Quantex QP5/60 PM   */
	/* Quantex QP5/60 PM-1 */
	/* Quantex QP5/60 PM-2 */
	/* Quantex QP5/60 PM-3 */
	/* Quantex QP5/60 W-1  */
	/* Quantex QP5/60 W-2  */
	/* Quantex QP5/60 XM   */
	/* Quantex QP5/60 XM-1 */
	/* Quantex QP5/66B-1   */
	/* Quantex QP5/66B-2   */
	/* Quantex QP5/66 PM   */
	/* Quantex QP5/66 PM-1 */
	/* Quantex QP5/66 PM-2 */
	/* Quantex QP5/66 PM-3 */
	/* Quantex QP5/66 W-1  */
	/* Quantex QP5/66 W-2  */
	/* NOTE: These machines use an Intel Premiere/PCI (Batman or Batman's Revenge ) system board with an Intel */
	/*       82430LX (Mercury) chipset and Intel AMIBIOS                                                       */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/quantex_qp5_60_66/1007AF2_.BIO",
		L"roms/machines/quantex_qp5_60_66/1007AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_quantex_qp5_90_init(const machine_t *model)
{
	/* Quantex QP5/90B-1    */
	/* Quantex QP5/90B-2    */
	/* Quantex QP5/90 PM    */
	/* Quantex QP5/90 PM-1  */
	/* Quantex QP5/90 PM-2  */
	/* Quantex QP5/90 PM-3  */
	/* Quantex QP5/90 W-1   */
	/* Quantex QP5/90 W-2   */
	/* Quantex QP5/90 W-3   */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.05.AX1)                                                          */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/poly_590ip/1006AX1_.BIO",
		L"roms/machines/poly_590ip/1006AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_quantex_qp5_90_w3_init(const machine_t *model)
{
	/* Quantex QP5/90 PM   (1.00.10.AX1) */
	/* Quantex QP5/90 PM-1 (1.00.10.AX1) */
	/* Quantex QP5/90 PM-2 (1.00.10.AX1) */
	/* Quantex QP5/90 PM-3 (1.00.10.AX1) */
	/* Quantex QP5/90 W-1  (1.00.10.AX1) */
	/* Quantex QP5/90 W-2  (1.00.10.AX1) */
	/* Quantex QP5/90 W-3  (1.00.10.AX1) */
	/* Quantex QP5/90 XM-1               */
	/* Quantex QP5/90 XM-3               */
	/* Quantex QP5/90 XW                 */
	/* Quantex QP5/75 XM-1               */
	/* Quantex QP5/75 XM-3               */
	/* Quantex QP5/75 XW                 */
	/* Quantex QP5/100 XM-1              */
	/* Quantex QP5/100 XM-3              */
	/* Quantex QP5/100 XW-1              */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.10.AX1)                                                          */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/quantex_qp5_90/1010AX1_.BIO",
		L"roms/machines/quantex_qp5_90/1010AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Reason Technology */
int
machine_at_reason_square_5_lx_tr_iz_120_init(const machine_t *model)
{
	/* Reason Square 5 LX-TR/IZ-120 */
	/* NOTE: This machine appears to use an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton)*/
	/*       chipset and Intel AMIBIOS (02/03/1995).                                                             */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/reason_square_5_lx_tr_iz_120/1002BS0_.BIO",
		L"roms/machines/reason_square_5_lx_tr_iz_120/1002BS0_.BI1", 0x20000, 128);
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

/* Robotech */
int
machine_at_robotech_cobra_rs_p90_init(const machine_t *model)
{
	/* Robotech Cobra RS p90  Graphics Workstation */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)  */
	/*       chipset and Intel AMIBIOS (1.00.03.AX1Z)                                                         */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/robotech_cobra_rs_p90/1006AX1_.BIO",
		L"roms/machines/robotech_cobra_rs_p90/1006AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_robotech_cobra_rs_p100_init(const machine_t *model)
{
	/* Robotech Cobra RS p100 Graphics Workstation */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)  */
	/*       chipset and Intel AMIBIOS (1.00.10.AX1).                                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/robotech_cobra_rs_p100/1010AX1_.BIO",
		L"roms/machines/robotech_cobra_rs_p100/1010AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Sidus Systems */
int
machine_at_sidus_sci9p590pdt_init(const machine_t *model)
{
	/* Sidus SCI9P590PDT */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.08.AX1)                                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/sidus_sci9p590pdt/1008AX1_.BIO",
		L"roms/machines/sidus_sci9p590pdt/1008AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Silicon Valley Computer */
int
machine_at_silicon_valley_pylon1_586_init(const machine_t *model)
{
	/* Silicon Valley Pylon 1 586 */
	/* NOTE: This machine uses a TMC system board with an OPTi 895 (Python) chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/silicon_valley_pylon1_586/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Simply Better Computers */
/* See PerComp MicroSystems */

/* STD (Standard Systems Supply) */
int
machine_at_std_p60_pci_init(const machine_t *model)
{
	/* STD P60 PCI */
	/* NOTE: This machine appears to use an Intel Premiere/PCI (Batman's Revenge ) system board with an Intel 82430LX */
	/*       (Mercury) chipset and Intel AMIBIOS.                                                                     */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/std_p60_pci/1007AF2_.BIO",
		L"roms/machines/std_p60_pci/1007AF2_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

/* Tangent */
int
machine_at_tangent_p560_init(const machine_t *model)
{
	/* Tangent P560 */
	/* NOTE: This machine appears to use either an Americaon Digicom system board or an  an Intel Premiere/PCI  */
	/*       (Batman) system board with an Intel 82430LX (Mercury) chipset and AMIBIOS or Intel AMIBIOS         */
	/*       (08/24/1993).                                                                                      */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/tangent_p560/1005AF1_.BIO",
		L"roms/machines/tangent_p560/1005AF1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

/* TC Computers */
int
machine_at_tc_p5_75_media_init(const machine_t *model)
{
	/* TC P5-75 Media */
	/* NOTE: This machine use  a First International Computer (FIC) PN-2000 system board with an Intel 82430NX */
	/*       (Neptune) chipset and Award BIOS (11/24/1994).                                                    */
	int ret;
	ret = bios_load_linear(L"roms/machines/tc_p5_75_media/1560304b.awd",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x03, PCI_CARD_NORMAL, 1, 2, 3, 4);	/* 03 = Slot 1 */
	pci_register_slot(0x04, PCI_CARD_NORMAL, 2, 3, 4, 1);	/* 04 = Slot 2 */
	pci_register_slot(0x05, PCI_CARD_NORMAL, 3, 4, 1, 2);	/* 05 = Slot 3 */
	pci_register_slot(0x06, PCI_CARD_NORMAL, 4, 1, 2, 3);	/* 06 = Slot 4 */
	pci_register_slot(0x07, PCI_CARD_SCSI, 1, 2, 3, 4);		/* 07 = SCSI */
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&fdc_at_device);
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430nx_device);
	device_add(&sio_device);
	/* device_add(&pc87306_device); */
	device_add(&intel_flash_bxt_device);
	return ret;
}

/* Techway */
int
machine_at_techway_endeavour_ii_init(const machine_t *model)
{
	/* Techway Endeavour II */
	/* NOTE: This machine uses an Asus PCI/I-P54SP4 Rev 1.5 system board with a SiS chipset and Award BIOS (4.50G) */
	/*                   (02/10/1995).                                                                             */
	int ret;
	ret = bios_load_linear(L"roms/machines/techway_endeavour_ii/SI5I0104.AWD",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c50x_common_init(model);
	device_add(&fdc37c665_device);
	return ret;
}

/* Treasure Chest Computers */
int
machine_at_treasure_chest_tcp575_init(const machine_t *model)
{
	/* Treasure Chest TCP575 */
	/* NOTE: This machine uses an Asus P/I-P55TP4 system board with an Intel 82430FX (Triton) chipset and Award */
	/*       BIOS (07/04/1995).                                                                                 */
	int ret;
	ret = bios_load_linear(L"roms/machines/treasure_chest_tcp575/TX5I0202.AWD",
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

/* Unisys */
int
machine_at_unisys_pw2_series_svi_init(const machine_t *model)
{
	/* Unisys PW2 Series Model CWP 5906  */
	/* Unisys PW2 Series Model SVI 5907  */
	/* Unisys PW2 Series Model SVI 51007 */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS (1.00.08.AX1).                                                         */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/unisys_svi_51007/1008AX1_.BIO",
		L"roms/machines/unisys_svi_51007/1008AX1_.BI1", 0x1d000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* USA Flex */
int
machine_at_usa_flex_pentium_init(const machine_t *model)
{
	/* USA Flex Pentium 60MHz System                */
	/* USA Flex Flex PT60 Pentium Multimedia System */
	/* NOTE: These machines appear to  use an Intel Premiere/PCI (Batman or Batman's Revenge ) system board with*/
	/*       an Intel 82430LX (Mercury) chipset and Intel AMIBIOS                                               */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/usa_flex_pentium/1007AF2_.BIO",
		L"roms/machines/usa_flex_pentium/1007AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_usa_flex_pt_75_90_100_init(const machine_t *model)
{
	/* USA Flex      PT90                   */
	/* USA Flex      PT90      Power System */
	/* USA Flex      PT90   MidTower        */
	/* USA Flex      PT-75   Desktop System */
	/* USA Flex      PT-100    Tower System */
	/* USA Flex Flex PT75 Multimedia System */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)   */
	/*       chipset and Intel AMIBIOS (1.00.10.AX1).                                                           */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/usa_flex_pt_75_90_100/1010AX1_.BIO",
		L"roms/machines/usa_flex_pt_75_90_100/1010AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_usa_flex_pt_75_multimedia_init(const machine_t *model)
{
	/* USA Flex PT-75  MultiMedia Classic */
	/* USA Flex PT-133 Power      System  */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)   */
	/*       chipset and Intel AMIBIOS (1.00.12.AX1).                                                           */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/usa_flex_pt_75_90_100/1012AX1_.BIO",
		L"roms/machines/usa_flex_pt_75_90_100/1012AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Vektron International */
int
machine_at_vektron_pci_power_station_60_init(const machine_t *model)
{
	/* Vektron PCI Professional Multimedia/Pentium 60 */
	/* Vektron PCI Power Station?Pentium 60           */
	/* NOTE: These machines use an Asus system board with an Intel 82430LX (Mercury) chipst and Award BIOS   */
	/*       (4.50).                                                                                         */
	int ret;
	ret = bios_load_linear(L"roms/machines/vektron_pentium_60/AWMI0205.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

/* VTech */
/* See PC Partner */

/* Windows Memory Corporation */
int
machine_at_windows_memory_pentium_60_66_init(const machine_t *model)
{
	/* Windows Memory Pentium 60/66 PC w/IO */
	/* NOTE: This machine appears to use an Intel Premiere/PCI (Batman or Batman's Revenge) system board with an*/
	/*       Intel 82430LX (Mercury) chipset and Intel AMIBIOS.                                                 */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/windows_memory_pentium_60_66/1009AF2_.BIO",
		L"roms/machines/windows_memory_pentium_60_66/1009AF2_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, 0);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_windows_memory_premiere_ii_init(const machine_t *model)
{
	/* Windows Memory Intel Premiere 90  II w/IO */
	/* Windows Memory Intel Premiere 100 II w/IO */
	/* Windows Memory Intel Premiere     IV w/IO */
	/* NOTE: These machines use an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune) */
	/*       chipset and Intel AMIBIOS.                                                                       */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/windows_memory_premiere_ii/1012AX1_.BIO",
		L"roms/machines/windows_memory_premiere_ii/1012AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Worldwide Technologies */
int
machine_at_worldwide_intel_zappa_init(const machine_t *model)
{
	/* Worldwide Technologies Intel Zappa P5-75  */
	/* Worldwide Technologies Intel Zappa P5-90  */
	/* Worldwide Technologies Intel Zappa P5-100 */
	/* NOTE: These machines use an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset */
	/*       and Intel AMIBIOS.                                                                                  */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/worldwide_intel_zappa/1002BS0_.BIO",
		L"roms/machines/worldwide_intel_zappa/1002BS0_.BI1", 0x20000, 128);
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

/* Xi Computer Corporation */
int
machine_at_xi_p100_ntower_sp_init(const machine_t *model)
{
	/* Xi P100 NTower SP       */
	/* Xi      MTower SP166MHz */
	/* Xi P133 MTower SP       */
	/* Xi P166 MTower SP       */
	/* Xi P200 MTower SP       */
	/* NOTE: These machines use an Asus PCI/I-P54TP4 system board with an Intel 82430FX (Triton) chipset and Award BIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/xi_p100_ntower_sp/TX5I0202.AWD",
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

/* Xinetron */
int
machine_at_xinetron_x_lan_xp66_init(const machine_t *model)
{
	/* Xinetron X/Lan XP66 */
	/* NOTE: This machine uses a system board which appears to have three 16-bit ISA slots and three 32-bit  */
	/*       VL-Bus slots, with a Socket 4 ZIF socket, four rows of 72-pin RAM slots, a 512 KB cache (512 KB */
	/*       maximum amount), a maximum of 128 MB of RAM, and AMIBIOS (08/08/1993).                          */
	/*                                                                                                       */
	/*       The closest system board available for viewing on Stason.org is an AIR (Advanced Integration    */
	/*       Research) 586MI system board, which includes an 8-bit ISA slot but otherwise matches many of the*/
	/*       descriptions mentioned above, and which uses a SiS chipset and AMIBIOS.                         */
	int ret;
	ret = bios_load_linear(L"roms/machines/xinetron_x_lan_xp66/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Zenith Data Systems */
int
machine_at_zenith_z_station_ex_init(const machine_t *model)
{
	/* Zenith Z-Station EX      */
	/* Zenith Z-Station EX MDII */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS (9.99.99.BF0U).                                                */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_ex/1004BF0U.BIO",
		L"roms/machines/zenith_z_station_ex/1004BF0U.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_zenith_z_station_ex_1004_init(const machine_t *model)
{
	/* Zenith Z-Station EX      (1.00.04.BF0U) */
	/* Zenith Z-Station EX MDII (1.00.04.BF0U) */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS (1.00.04.BF0U).                                                */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_ex/1004BF0U.BIO",
		L"roms/machines/zenith_z_station_ex/1004BF0U.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_zenith_z_station_ex_1005_init(const machine_t *model)
{
	/* Zenith Z-Station EX      (1.00.05.BF0U) */
	/* Zenith Z-Station EX MDII (1.00.05.BF0U) */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS (1.00.05.BF0U).                                                */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_ex/1005BF0U.BIO",
		L"roms/machines/zenith_z_station_ex/1005BF0U.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_zenith_z_station_ex_1007_init(const machine_t *model)
{
	/* Zenith Z-Station EX      (1.00.07.BF0U) */
	/* Zenith Z-Station EX MDII (1.00.07.BF0U) */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS (1.00.07.BF0U).                                                */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_ex/1007BF0U.BIO",
		L"roms/machines/zenith_z_station_ex/1007BF0U.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_zenith_z_station_ex_1009_init(const machine_t *model)
{
	/* Zenith Z-Station EX      (1.00.09.BF0U) */
	/* Zenith Z-Station EX MDII (1.00.09.BF0U) */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS (1.00.09.BF0U).                                                */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_ex/1009BF0U.BIO",
		L"roms/machines/zenith_z_station_ex/1009BF0U.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

int
machine_at_zenith_z_station_ex_1011_init(const machine_t *model)
{
	/* Zenith Z-Station EX      (1.00.11.BF0U) */
	/* Zenith Z-Station EX MDII (1.00.11.BF0U) */
	/* NOTE: These machines use an Intel Premiere/GX Low Profile (Socrates) system board with an Intel 82430NX  */
	/*       (Neptune) chipset and Intel AMIBIOS (1.00.11.BF0U).                                                */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenith_z_station_ex/1011BF0U.BIO",
		L"roms/machines/zenith_z_station_ex/1011BF0U.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* Zenon Computer Systems */
int
machine_at_zenon_z_optimuspentium_60mhz_init(const machine_t *model)
{
	/* Zenon Z-Optimus PCI Pentium 60MHz */
	/* NOTE: This machine uses an Asus system board with an Intel 82430LX (Mercury) chipst and Award BIOS    */
	/*       (4.50).                                                                                         */
	int ret;
	ret = bios_load_linear(L"roms/machines/zenon_z_optimus_pci_pentium_60mhz/AWMI0205.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_award_common_init(model);
	device_add(&sio_device);
	device_add(&i430lx_device);
	return ret;
}

int
machine_at_zenon_pci_dream_media_4x_init(const machine_t *model)
{
	/* Zenon PCI Dream Media 4X */
	/* NOTE: This machine uses an Intel Advanced/ZP (Zappa) system board with an Intel 82430FX (Triton) chipset */
	/*       and Intel AMIBIOS (02/03/1995).                                                                    */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenon_pci_dream_media_4x/1002BS0_.BIO",
		L"roms/machines/zenon_pci_dream_media_4x/1002BS0_.BI1", 0x20000, 128);
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
machine_at_zenon_z_titan_pentium_90mhz_init(const machine_t *model)
{
	/* Zenon Z-Titan Pentium 90MHz */
	/* NOTE: This machine uses an Intel Premiere/PCI II (Plato) system board with an Intel 82430NX (Neptune)  */
	/*       chipset and Intel AMIBIOS.                                                                       */
	/* NOTE 2: The closest matching Intel AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/zenon_z_titan_pentium_90mhz/1006AX1_.BIO",
		L"roms/machines/zenon_z_titan_pentium_90mhz/1006AX1_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_premiere_common_init(model, PCI_CAN_SWITCH_TYPE);
	device_add(&i430nx_device);
	return ret;
}

/* ZEOS International */
int
machine_at_zeos_pantera_cobra12_init(const machine_t *model)
{
	/* ZEOS Pantera 60              */
	/* ZEOS Pantera 60 (11/30/1994) */
	/* ZEOS Pantera 66              */
	/* ZEOS Pantera 66 (11/30/1994) */
	/* ZEOS Pantera 90              */
	/* ZEOS Pantera 90 (11/30/1994) */
	/* NOTE: These systems use the ZEOS Cobra system board with the Intel 82430LX (Mercury) chipset and Phoenix */
	/*       BIOS. In addition, the ZEOS Pantera 90 has a special CPU board mounted onto the standard CPU socket*/
	/*       to convert the Socket 4 into a Socket 5 in order to allow the system board to accept Socket 5 CPUs.*/
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_pantera_cobra12/002612.BIN",
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
	pci_register_slot(0x02, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430lx_device);
	device_add(&sio_zb_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_zeos_pantera_cobra13_init(const machine_t *model)
{
	/* ZEOS Pantera 60 (07/14/1995) */
	/* ZEOS Pantera 66 (07/14/1995) */
	/* ZEOS Pantera 90 (07/14/1995) */
	/* NOTE: These systems use the ZEOS Cobra system board with the Intel 82430LX (Mercury) chipset and Phoenix */
	/*       BIOS. In addition, the ZEOS Pantera 90 has a special CPU board mounted onto the standard CPU socket*/
	/*       to convert the Socket 4 into a Socket 5 in order to allow the system board to accept Socket 5 CPUs.*/
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_pantera_cobra13/002613.BIN",
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
	pci_register_slot(0x02, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430lx_device);
	device_add(&sio_zb_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}

int
machine_at_zeos_pantera_pentium_init(const machine_t *model)
{
	/* NOTE: These systems use the ZEOS Coral system board with the Intel 82430NX (Neptune) chipset and Phoenix */
	/*       BIOS.                                                                                             .*/
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
	pci_register_slot(0x02, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_pci_device);
	device_add(&i430nx_device);
	device_add(&sio_zb_device);
	device_add(&fdc37c665_device);
	device_add(&intel_flash_bxt_device);
	return ret;
}
