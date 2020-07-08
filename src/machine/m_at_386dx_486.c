/*
 * 86Box	A hypervisor and IBM PC system emulator that specializes in
 *		running old operating systems and software designed for IBM
 *		PC systems and compatibles from 1981 through fairly recent
 *		system designs based on the PCI bus.
 *
 *		This file is part of the 86Box distribution.
 *
 *		Implementation of 386DX and 486 machines.
 *
 *
 *
 * Authors:	Sarah Walker, <http://pcem-emulator.co.uk/>
 *		Miran Grca, <mgrca8@gmail.com>
 *
 *		Copyright 2010-2020 Sarah Walker.
 *		Copyright 2016-2020 Miran Grca.
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#define HAVE_STDARG_H
#include <86box/86box.h>
#include "cpu.h"
#include <86box/timer.h>
#include <86box/io.h>
#include <86box/device.h>
#include <86box/chipset.h>
#include <86box/keyboard.h>
#include <86box/mem.h>
#include <86box/nvr.h>
#include <86box/pci.h>
#include <86box/fdd.h>
#include <86box/fdc.h>
#include <86box/rom.h>
#include <86box/sio.h>
#include <86box/hdc.h>
#include <86box/video.h>
#include <86box/flash.h>
/* #include <86box/intel_sio.h> */
#include <86box/scsi_ncr53c8xx.h>
#include <86box/machine.h>


static void
machine_at_headland1_common_init(int ht386)
{
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);

	if (ht386)
		device_add(&headland_386_device);
	else
		device_add(&headland_device);
}

static void
machine_at_scat486_init(const machine_t *model, int is_v4)
{
	machine_at_init(model);
	device_add(&fdc_at_device);

	if (is_v4)
		device_add(&scat_4_device);
	else
		device_add(&scat_device);
}

int
machine_at_acc386_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/acc386/acc386.BIN",
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
machine_at_asus386_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/asus386/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);

	return ret;
}

int
machine_at_ecs386_init(const machine_t *model)
{
	int ret;

	ret = bios_load_interleaved(L"roms/machines/ecs386/AMI BIOS for ECS-386_32 motherboard - L chip.bin",
		L"roms/machines/ecs386/AMI BIOS for ECS-386_32 motherboard - H chip.bin",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init(model);
	device_add(&cs8230_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);

	return ret;
}

static void
machine_at_ali1429_common_init(const machine_t *model)
{
	machine_at_common_ide_init(model);

	device_add(&ali1429_device);

	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
}


int
machine_at_ali1429_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/ami486/ami486.bin",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_ali1429_common_init(model);

	return ret;
}


int
machine_at_winbios1429_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/win486/ali1429g.amw",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_ali1429_common_init(model);

	return ret;
}


int
machine_at_opti495_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/award495/opt495s.awa",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_ide_init(model);

	device_add(&opti495_device);

	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);

	return ret;
}


static void
machine_at_opti495_ami_common_init(const machine_t *model)
{
	machine_at_common_ide_init(model);

	device_add(&opti495_device);

	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
}


int
machine_at_opti495_ami_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/ami495/opt495sx.ami",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_opti495_ami_common_init(model);

	return ret;
}


int
machine_at_opti495_mr_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/mr495/opt495sx.mr",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_opti495_ami_common_init(model);

	return ret;
}


static void
machine_at_sis_85c471_common_init(const machine_t *model)
{
	machine_at_common_init(model);
	device_add(&fdc_at_device);

	device_add(&sis_85c471_device);
}


int
machine_at_ami471_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/ami471/SIS471BE.AMI",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);

	return ret;
}

int
machine_at_vli486sv2g_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/vli486sv2g/0402.001",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_2ch_device);
	device_add(&keyboard_at_device);

	return ret;
}

int
machine_at_px471_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/px471/SIS471A1.PHO",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);

	return ret;
}


#if defined(DEV_BRANCH) && defined(USE_WIN471)
int
machine_at_win471_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/win471/486-SiS_AC0360136.BIN",
		0x000f0000, 65536, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);

	return ret;
}
#endif


static void
machine_at_sis_85c496_common_init(const machine_t *model)
{
	device_add(&ide_pci_2ch_device);

	pci_init(PCI_CONFIG_TYPE_1);
	pci_register_slot(0x05, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);

	pci_set_irq_routing(PCI_INTA, PCI_IRQ_DISABLED);
	pci_set_irq_routing(PCI_INTB, PCI_IRQ_DISABLED);
	pci_set_irq_routing(PCI_INTC, PCI_IRQ_DISABLED);
	pci_set_irq_routing(PCI_INTD, PCI_IRQ_DISABLED);
}


int
machine_at_r418_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/r418/r418i.bin",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	machine_at_sis_85c496_common_init(model);
	device_add(&sis_85c496_device);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x07, PCI_CARD_NORMAL, 4, 1, 2, 3);
	pci_register_slot(0x07, PCI_CARD_NORMAL, 4, 1, 2, 3);

	device_add(&fdc37c665_device);
	device_add(&keyboard_ps2_pci_device);

	return ret;
}


int
machine_at_ls486e_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/ls486e/LS486E RevC.BIN",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	machine_at_sis_85c496_common_init(model);
	device_add(&sis_85c496_ls486e_device);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0F, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 4, 1, 2, 3);

	device_add(&fdc37c665_device);
	device_add(&keyboard_ps2_ami_pci_device);

	return ret;
}


int
machine_at_4dps_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/4dps/4DPS172G.BIN",
		0x000e0000, 131072, 0);

	if (bios_only || !ret)
		return ret;

	machine_at_common_init_ex(model, 2);

	machine_at_sis_85c496_common_init(model);
	device_add(&sis_85c496_device);
	pci_register_slot(0x0B, PCI_CARD_NORMAL, 1, 2, 3, 4);
	pci_register_slot(0x0D, PCI_CARD_NORMAL, 2, 3, 4, 1);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 3, 4, 1, 2);
	pci_register_slot(0x07, PCI_CARD_NORMAL, 4, 1, 2, 3);

	device_add(&w83787f_device);
	device_add(&keyboard_ps2_pci_device);

	// device_add(&sst_flash_29ee010_device);
	device_add(&intel_flash_bxt_device);

	return ret;
}

/* #if defined(DEV_BRANCH) && defined(NO_SIO) */
int
machine_at_486sp3g_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/486sp3g/PCI-I-486SP3G_0306.001 (Beta).bin",
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
	pci_register_slot(0x02, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device); /* Uses the AMIKEY KBC */
	device_add(&sio_device);	/* Site says it has a ZB, but the BIOS is designed for an IB. */
	device_add(&pc87332_device);
	device_add(&sst_flash_29ee010_device);
	device_add(&ncr53c810_onboard_pci_device);

	device_add(&i420zx_device);

	return ret;
}
/* #endif */

/* IBM (International Business Machines) */
int
machine_at_valuepoint433_init(const machine_t *model)
{
	/* IBM PS/ValuePoint 433DX/Si */
	/* NOTE: This machine uses a system board with a SiS chipset and IBM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/valuepoint433/$IMAGEP.FLH",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_ps2_device);
	return ret;
}

int
machine_at_ibm_thinkpad_360cse_init(const machine_t *model)
{
	/* IBM ThinkPad 360CSE */
	/* NOTE: This machine uses a system board with a Pico Power chipset and IBM BIOS (08/01/1994). */
	int ret;
	ret = bios_load_linear(L"roms/machines/ibm_thinkpad_360cse/bios-ibm-thinkpad-360cse.rom",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* COMPAQ */
int
machine_at_compaq_prolinea_4_33_init(const machine_t *model)
{
	/* COMPAQ Prolinea 4/33 */
	/* COMPAQ Prolinea 4/50 */
	/* NOTE: These machines use a system board with a VLSI chipset and COMPAQ BIOS (10/06/1992). */
	int ret;
	ret = bios_load_linear(L"roms/machines/compaq_prolinea_4_33/Compaq_164594-006.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_compaq_init(model, COMPAQ_PORTABLEIII386); */
	return ret;
}

/* Intel Corporation */
int
machine_at_alfredo_init(const machine_t *model)
{
	/* Intel Classic/PCI (Alfredo) */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/alfredo/1010AQ0_.BIO",
		L"roms/machines/alfredo/1010AQ0_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i420tx_device);
	return ret;
}

/* A (LOCAL RETAILER) */
int
machine_at_a_486_init(const machine_t *model)
{
	/* A 486 */
	/* NOTE: This machine uses an AC-59610 system board with a SiS chipset and AMIBIOS (04/07/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/a_486/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Aberdeen */
int
machine_at_aberdeen_super_eisa_vlb_init(const machine_t *model)
{
	/* Aberdeen Super EISA VLB */
	/* NOTE: This machine uses an MCCI (Micro Center Computer) system board with a SiS chipset  */
	/*       and AMIBIOS (6/6/1992)                                                             */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/aberdeen_super_eisa_vlb/ft01232.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Access Computer Technologies (ACT) */
int
machine_at_act_486_66mhz_init(const machine_t *model)
{
	/* ACT 486-66MHz */
	/* NOTE: This machine uses a system board with four 16-bit ISA slots, two 32-bit VL-Bus slots, and possibly two  */
	/*       8-bit slots, with a 486 CPU socket (most likely Socket 3), and which most likely used a SiS chipset and */
	/*       AMIBIOS.                                                                                                */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/act_486_66mhz/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Acer */
int
machine_at_acerpower_486e_init(const machine_t *model)
{
	/* Acer AcerPower 486e DX2/66 Model 5657 */
	/* NOTE: This machine uses a system board with an OPTi chipset */
	/* NOTE 2: The AcerMate 386SX BIOS is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/acerpower_486e/acer386.bak",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_acera1g_init(const machine_t *model)
{
	/* Acer A1G */
	int ret;
	ret = bios_load_linear(L"roms/machines/acera1g/4alo001.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	if (gfxcard == VID_INTERNAL)
		device_add(&gd5428_a1g_device);
	device_add(&ali1429_device);
	device_add(&keyboard_ps2_acer_pci_device);
	device_add(&fdc_at_device);
	device_add(&ide_isa_2ch_device);
	return ret;
}

const device_t *
at_acera1g_get_device(void)
{
	return &gd5428_a1g_device;
}

/* ACMA */
int
machine_at_acma_386_40_init(const machine_t *model)
{
	/* ACMA 386/40 */
	/* NOTE: This machine uses a Helm Engineering system board with a SiS chipset and AMIBIOS. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/acma_386_40/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_acma_486_25_init(const machine_t *model)
{
	/* ACMA 486/25 */
	/* NOTE: This machine uses uses an AMI system board with a Chips and Technologies chipset and AMIBIOS */
	/*       (04/09/1990)                                                                                 */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/acma_486_25/386-702430d-ROM0.BIN",
	L"roms/machines/acma_486_25/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/acma_486_25/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);

	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

int
machine_at_acma_mpc_433_486_66_init(const machine_t *model)
{
	/* ACMA MPC/433 */
	/* ACMA 486-66/DX2 VESA System                                                                           */
	/* NOTE: This machine uses a Chaintech system board (425UXL, 433UXL, 425UCL, or 433UCL) with a USAI (USA */
	/*       Integration) chipset.                                                                           */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/acma_mpc_433_486_66/OPT495SX.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

int
machine_at_acma_486_pcmcia_init(const machine_t *model)
{
	/* ACMA 486 Energy Pro                      */
	/* ACMA 486DX2 66MHz with PCMCIA Card Drive */
	/* NOTE: These machines use a Freetech (FTC) system board with a SiS chipset and AMIBIOS (08/08/1993) */
	/* NOTE: The closest matching BIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/acma_486_pcmcia/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_acma_486dx2_init(const machine_t *model)
{
	/* ACMA Desktop 486DX2-66 */
	/* NOTE: This machine uses a Freetech system board with a SiS 471 chipset and Award BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/acma_486dx2/F38xg.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* ACR Systems */
int
machine_at_acr_mia66_init(const machine_t *model)
{
	/* ACR MIA66 */
	/* NOTE: This system uses a system board with a SiS chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/acr_mia66/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Agatech Computer Systems */
int
machine_at_agatech_aga_dx33_init(const machine_t *model)
{
	/* Agatech AGA-DX33 */
	/* NOTE: This machine uses a system board with a Contaq chipset and AMIBIOS (12/12/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/agatech_aga_dx33/486-Contaq.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* AGI Computer */
int
machine_at_agi_3900b_init(const machine_t *model)
{
	/* AGI 3900B */
	/* NOTE: This machine uses a system board which uses discrete logic in place of an actual chipset and which uses an */
	/*       AMIBIOS version from February 1990.                                                                        */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/agi_3900b/386-BIG AMI 896818 EVEN.BIN",
		L"roms/machines/agi_3900b/386-BIG AMI 896818 ODD.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Alaris */
int
machine_at_alaris_leopard_plus_init(const machine_t *model)
{
	/* Alaris Leopard Plus EnergySmartPC 486SLC2 66 */
	/* Alaris Cougar       EnergySmartPC 486BL3X 75 */
	/* Alaris              EnergySmartPC    BL3X100 */
	/* Alaris Leopard  VIP                   BL-100 */
	/* NOTE: These machines use an Alaris system board with an OPTi chipset and MR BIOS (Microid Research) */
	int ret;
	ret = bios_load_linear(L"roms/machines/alaris_leopard_plus_486slc2/COUGRMRB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_alaris_nx586_init(const machine_t *model)
{
	/* Alaris Nx586 (AMIBIOS) */
	/* NOTE: This system board uses a standard BIOS and chipset until the NexGen NxVL chipset is complete */
	int ret;
	ret = bios_load_linear(L"roms/machines/486_test/amibios_hot409.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_alaris_nx586_winbios_init(const machine_t *model)
{
	/* Alaris Nx586 (AMI WinBIOS) */
	/* NOTE: This system board uses a standard BIOS and chipset until the NexGen NxVL chipset is complete */
	int ret;
	ret = bios_load_linear(L"roms/machines/486_test/486-V4P895P3-SMT.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* ALR (Advanced Logic Research) */
int
machine_at_alr_ranger_init(const machine_t *model)
{
	/* ALR Ranger M425-120 *  /
	/* ALR Ranger M425s-120  */
	/* ALR Ranger MC425-120  */
	/* ALR Ranger MC425s-120 */
	/* NOTE: The closest matching BIOS is used until an original dump is available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/alr_ranger/41651-bios lo.u18",
		L"roms/machines/alr_ranger/211253-bios hi.u19",
		0x000f0000, 65536, 0x08000);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_ps2_quadtel_device);
	device_add(&wd76c10_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&paradise_wd90c11_megapc_device);
	return ret;
}

/* ALS Computer Systems (LOCAL RETAILER) */
int
machine_at_als_486dx2_66_lb_init(const machine_t *model)
{
	/* ALS 486DX2-66 LB */
	/* NOTE: This is a machine from Boston-based retailer ALS, reviewed for PC World in October 1993 for their   */
	/*       November 1993 issue. The original system board appears to have used 6 ISA slots and 2 ISA/VL-Bus    */
	/*       slots, and supported a maximum of 256 MB of RAM as well as a 256 KB cache that was upgradable to    */
	/*       512 KB, and it also used a standard CPU socket instead of a ZIF (Zero Insertion Force) socket.      */
	/*                                                                                                           */
	/*       While we have not yet been able to find a system board listing that is an exact match to the one    */
	/*       that this system has, we were still able to find the closest system boards with the exact slot      */
	/*       layout, listed below:                                                                               */
	/*        - CONTAQ 596                        (CONTAQ 596 chipset with AMIBIOS)                              */
	/*        - VISIONEX GREEN-B [4GPV3]          (CONTAQ 596 chipset with AMIBIOS, Award BIOS, or MR BIOS)      */
	/*        - Atrend 4GPV3                      (CONTAQ 596 chipset with AMIBIOS (6/6/1992))                   */
	/*                                                                                                           */
	/*       The same PC World article mentioned that the 6/6/1992 AMIBIOS was used on many of the machines that */
	/*       were tested, which matches with the versions of the 6/6/1992 AMIBIOS mentioned above.               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/als_486dx2_66_lb/486-MS4125.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Altec */
int
machine_at_altec_486_init(const machine_t *model)
{
	/* Altec 486/33 Local Bus */
	/* NOTE: This machine uses a Gigabyte system board with a UMC chipset and AMIBIOS (12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/altec_486/3umm004.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_opti495_ami_common_init(model); */ /* Substituting for UMC chipset until original chipset is added */
	return ret;
}

int
machine_at_altec_486dx2_init(const machine_t *model)
{
	/* Altec 486DX2 Local Bus */
	/* NOTE: This machine uses a Gigabyte system board with a UMC chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/altec_486/386-HOT-304.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for UMC chipset until original chipset is added */
	return ret;
}

/* Altima */
int
machine_at_altima_433_80486dx_init(const machine_t *model)
{
	/* Altima 433 80486DX */
	/* NOTE: This portable machine was manufactured by Twinhead and uses a system board with an ACC Micro chipset and */
	/*       Phoenix ROM BIOS (05/21/1992).                                                                           */
	/* NOTE 2: The closest matching Phoenix ROM BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/ergo_powerbrick_100/p101a002_sys_bios_62fc.u24",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ibm_common_ide_init(model);
	device_add(&keyboard_ps2_device);
	device_add(&acc3221_device);
	device_add(&acc2168_device);
	return ret;
}

/* AMAX */
int
machine_at_amax_386_40_isamax_init(const machine_t *model)
{
	/* AMAX 386-40 ISAmax Power Station */
	/* NOTE: This machine uses a Helm Engineering system board with a SiS chipset and AMIBIOS. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/amax_386_40_isamax_power_station/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_amax_486dx2_50_isamax_init(const machine_t *model)
{
	/* AMAX 486DX2-50 ISAmax Power Station */
	/* NOTE: This machine uses an Impression system board with a SiS chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/amax_486dx2_50_isamax_power_station/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Ambra */
int
machine_at_ambra_d466bl_init(const machine_t *model)
{
	/* Ambra S450SL    */
	/* Ambra S425SX    */
	/* Ambra S433DX    */
	/* Ambra D466BL/CD */
	/* Ambra D466BL    */
	/* Ambra D466DX    */
	/* NOTE: These machines use a system board with an FTD chipset and Phoenix BIOS (1.03) */
	int ret;
	ret = bios_load_linear(L"roms/machines/ambra_d466bl/8125873.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* machine_at_ibm_common_ide_init(model); */
	device_add(&ali1429_device);
	device_add(&keyboard_ps2_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_ambra_d466bl2_init(const machine_t *model)
{
	/* Ambra S450SL    */
	/* Ambra S425SX    */
	/* Ambra S433DX    */
	/* Ambra D466BL/CD */
	/* Ambra D466BL    */
	/* Ambra D466DX    */
	/* NOTE: These machines use a system board with an FTD chipset and Phoenix BIOS (1.03) */
	int ret;
	ret = bios_load_linear(L"roms/machines/ambra_d466bl/8128991.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* machine_at_ibm_common_ide_init(model); */
	device_add(&ali1429_device);
	device_add(&keyboard_ps2_device);
	device_add(&fdc_at_device);
	return ret;
}

/* AME (Advanced Micro Electronics) */
int
machine_at_ame_intel_486_init(const machine_t *model)
{
	/* AME Intel 486 */
	/* NOTE: This machine uses a system board with an OPTi 895 (Python) chipste and AMIBIOS (12/15/1993, 07/25/1994, or */
	/*       10/10/1994).                                                                                               */
	/* NOTE 2: The closest AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/ame_intel_486/486-V4P895P3-SMT.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* American Computer Research */
int
machine_at_acr_solar_star_486bl_75_init(const machine_t *model)
{
	/* ACR Solar Star 486BL/75 */
	/* NOTE: This machine uses an Alaris Cougar system board with an OPTi chipset and MR BIOS (Microid Research) */
	int ret;
	ret = bios_load_linear(L"roms/machines/acr_solar_star_486bl_75/COUGRMRB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* American Multisystems */
int
machine_at_infogold_486dx2_init(const machine_t *model)
{
	/* American Multisystems InfoGold 486DX2/66 */
	/* NOTE: This machine uses a Freetech system board with a SiS 471 chipset and Award BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/american_multisystems_infogold_486dx2/F38xg.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* American Mitac */
/* See Mitac */

/* American Super Computer */
int
machine_at_asc_486_33i_init(const machine_t *model)
{
	/* American Super Computer ASC 486/33i */
	/* NOTE: This machine uses an ERI system board with a Symphony chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/american_super_computer_asc_486_33i/ami_386_za590821.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Amrel */
int
machine_at_amrel_mlt486dxu33_init(const machine_t *model)
{
	/* Amrel MLT486DXU33 */
	/* NOTE: This portable machine uses a system board with an ACC Micro chipset and AMIBIOS (01/07/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/amrel_mlt486dxu33/acc386.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&acc2168_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* AMS Tech */
int
machine_at_ams_soundwave_init(const machine_t *model)
{
	/* AMS SoundWave        */
	/* AMS SoundPro DX4/75  */
	/* AMS SoundPro DX4/100 */
	/* NOTE: This portable machine uses a system board with an ACC Micro chipset and Phoenix ROM BIOS (04/19/1990). */
	/* NOTE 2: The closest matching Phoenix ROM BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/ergo_powerbrick_100/p101a002_sys_bios_62fc.u24",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ibm_common_ide_init(model);
	device_add(&keyboard_ps2_device);
	device_add(&acc3221_device);
	device_add(&acc2168_device);
	return ret;
}

int
machine_at_ams_travelpro_5333_5366_init(const machine_t *model)
{
	/* AMS TravelPro 5333 */
	/* AMS TravelPro 5366 */
	/* NOTE: This portable machine uses a system board with an ACC Micro chipset and AMIBIOS (06/06/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/ams_travelpro_5333_5366/acc386.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&acc2168_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Amstrad */
int
machine_at_amstrad_pc7486slc_init(const machine_t *model)
{
	/* Amstrad PC 7486SLC 80 */
	/* Amstrad PC7486SLC-33  */
	/* NOTE: These machines use a system board with a Winbond chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/amstrad_pc7486/PC7486SLC-33.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_ps2_quadtel_device);
	device_add(&wd76c10_device); /* Substituting for Winbond chipset until correct chipset is added */
	return ret;
}

/* AnyBus */
int
machine_at_anybus_486_33ism_init(const machine_t *model)
{
	/* AnyBus 486/33ISM */
	/* NOTE: This machine uses an Alaris Cougar 486BL system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/anybus_486_33ism/COUGRMRB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Aquilline */
int
machine_at_aquilline_nt33_init(const machine_t *model)
{
	/* Aquilline NT33 */
	/* NOTE: This portable machine uses a system board with a Chips and Technologies chipset and Award BIOS (3.20). */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/aquilline_nt33/award.bin",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_scat486_init(model, 0);
	return ret;
}

/* ARC (American Research Corporation) */
int
machine_at_arc_386_33_skyscraper_init(const machine_t *model)
{
	/* ARC 386/33 Skyscraper */
	/* NOTE: This machine uses a system board which uses discrete logic in place of an actual chipset and which uses an */
	/*       AMIBIOS version from December 1989.                                                                        */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/arc_386_33_skyscraper/386-BIG AMI 896818 EVEN.BIN",
		L"roms/machines/arc_386_33_skyscraper/386-BIG AMI 896818 ODD.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* ARC Electronics (LOCAL RETAILER) */
int
machine_at_arc_486dx4_100_init(const machine_t *model)
{
	/* ARC 486DX4-100 */
	/* NOTE: This machine uses an EDOM MV035F system board with an OPTi 82C802 chipset and AMIBIOS (12/15/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/arc_486dx4_100/486-V4P895P3-SMT.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* AROH SuperCOM Australia */
int
machine_at_arch_supercom_486_220vi_init(const machine_t *model)
{
	/* AROH SuperCOM 486-220VI */
	/* NOTE: This machine uses an Elitegroup UM486 system board with a UMC chipset and AMIBIOS (07/07/1991). */
	int ret;
	ret = bios_load_linear(L"roms/machines/arch_supercom_486_220vi/486-um486-um486sx.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Arche Technology */
int
machine_at_arche_legacy_486_init(const machine_t *model)
{
	int ret;

	ret = bios_load_linear(L"roms/machines/arche_legacy/ami.bin",
		0x000f0000, 131072, 0);
	/* ret = bios_load_linear(L"roms/machines/arche_legacy/ami.bin",
	0x000f0000, 65536, 0); */
	ret = bios_load_linear(L"roms/machines/ama932j/ami.bin",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;

	machine_at_common_ide_init(model);
	machine_at_headland1_common_init(1);

	/* if (gfxcard == VID_INTERNAL)
	device_add(&oti067_ama932j_device); */

	return ret;
}

int
machine_at_arche_legacy_4862_init(const machine_t *model)
{
	/* Arche Legacy-I 486-33  */
	/* Arche Legacy 486/66DX2 */
	/* NOTE: These machines use a system board with an OPTi chipset and AMIBIOS (07/07/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_linear(L"roms/machines/arche_legacy/ami.bin",
	0x000f0000, 131072, 0); */
	/* ret = bios_load_linear(L"roms/machines/arche_legacy/ami.bin",
	0x000f0000, 65536, 0); */
	ret = bios_load_linear(L"roms/machines/ama932j/ami.bin",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	/* machine_at_opti495_ami_common_init(model); */
	return ret;
}

/* Ares Microdevelopment */
int
machine_at_ares_386_40_sonic_init(const machine_t *model)
{
	/* Ares 386/40    Sonic     */
	/* Ares 486-50DX2 Sonic III */
	/* NOTE: These machines use a Technology Power system board with a VLSI chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/ares_386_40_sonic/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* device_add(&vlsi_scamp_device); */
	return ret;
}

int
machine_at_ares_dx4_100_init(const machine_t *model)
{
	/* Ares DX4/100 */
	/* NOTE: This machine uses an Asus VL/I-486SV2GX4 system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/ares_dx4_100/SV2G0304.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Argo Computers */
int
machine_at_argo_tower_386_33_init(const machine_t *model)
{
	/* Argo Tower 386/33 */
	/* NOTE: This machine uses an Orchid system board with a VLSI chipset and AMIBIOS (March 1990). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/argo_tower_386_33/286-vlsi-002350-041_32k.bin",
		L"roms/machines/argo_tower_386_33/286-vlsi-002350-042_32k.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	/* device_add(&vlsi_scamp_device); */
	return ret;
}

/* Ariel Design */
int
machine_at_ariel_486sx_25_best_value_init(const machine_t *model)
{
	/* Ariel 486SX/25            */
	/* Ariel 486SX-25 Best Value */
	/* Ariel 486DX2-50           */
	/* Ariel 486DX2-66VLB        */
	/* NOTE: This machine uses a Micronics system board with a Chips and Technologies or SiS-manufactured Micronics */
	/*       chipset and Phoenix ROM BIOS, with the "0.10.G20-2" ROM BIOS version being used by the Ariel 486SX-25  */
	/*       Best Value.                                                                                            */
	/* NOTE 2: The closest matching Phoenix ROM BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/ariel_486sx_25_best_value/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* ASI */
int
machine_at_asi_486dx4_100_init(const machine_t *model)
{
	/* ASI 486DX4-100 */
	/* NOTE: This machine uses an Asus VL/I-486SV2GX4 system board with a SiS 471 chipset and Award BIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/asi_486dx4_100/SV2G0304.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_2ch_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Aspen Computer */
int
machine_at_aspen_personal_486_init(const machine_t *model)
{
	/* Aspen Personal 486 */
	/* NOTE: This portable machine uses a system board with a Headland chipset and AMIBIOS (AMI 1.0). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/aspen_personal_486/3hlm002.bin",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	machine_at_headland1_common_init(1);
	return ret;
}

int
machine_at_aspen_universa_e_series_init(const machine_t *model)
{
	/* Aspen Universa-E Series */
	/* NOTE: This portable machine was manufactured by Kapok and uses a system board with a SiS chipset and Award BIOS */
	/*       (04/28/1994).                                                                                             */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/aspen_universa_e_series/ga-486svf.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_aspen_universa_cd_init(const machine_t *model)
{
	/* Aspen Universa-CD */
	/* NOTE: This portable machine was manufactured by MicroStar and uses a system board with a SiS chipset and AMIBIOS */
	/*       (AMI 1.27).                                                                                                */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/aspen_universa_cd/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_aspen_aspenta_60_66_init(const machine_t *model)
{
	/* Aspen Aspenta 60/66 */
	/* NOTE: This portable machine uses a system board with an OPTi chipset and AMIBIOS. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/aspen_aspenta_60_66/opt495sx.ami",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* AST Research (later AST Computer) */
int
machine_at_ast_advantage_4066d_init(const machine_t *model)
{
	/* AST Bravo LC 4/66d             */
	/* AST Advantage! Adventure 4066d */
	/* AST Advantage! Adventure 6066d */
	/* AST Advantage! Adventure 8066d */
	int ret;
	ret = bios_load_linear(L"roms/machines/ast_advantage_adventure_4066d/AST101.09A",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_ast_premmia_mx_466d_init(const machine_t *model)
{
	/* AST Premmia MX 4/66d  */
	/* NOTE: This machine uses an Intel system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ast_premmia_mx/1010AU0Q.BIO",
		L"roms/machines/ast_premmia_mx/1010AU0Q.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i420tx_device);
	return ret;
}

int
machine_at_ast_premmia_mx_4100t_init(const machine_t *model)
{
	/* AST Premmia MX 4/100t */
	/* NOTE: This machine uses an Intel system board */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/ast_premmia_mx/1010AU0Q.BIO",
		L"roms/machines/ast_premmia_mx/1010AU0Q.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_NORTHBRIDGE, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SOUTHBRIDGE, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i420tx_device);
	return ret;
}

int
machine_at_ast_ascentia_910n_init(const machine_t *model)
{
	/* AST Ascentia 910N */
	/* NOTE: This portable machine uses a system board with a VLSI chipset and AST BIOS (AST 2). */
	/* NOTE 2: The AST Advantage! Adventure 6066d BIOS is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/ast_ascentia_910n/AST101.09A",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Astro Research */
int
machine_at_astronote_skd_iii_init(const machine_t *model)
{
	/* AstroNote SKD III */
	/* NOTE: This portable machine was manufactured by Dual and uses a system board with an ACC Micro chipset and AMIBIOS*/
	/*       (12/07/1994).                                                                                               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/astronote_skd_iii/acc386.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&acc2168_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Atlas Industries */
int
machine_at_atlas_486sx_25_init(const machine_t *model)
{
	/* Atlas 486SX/25 */
	/* NOTE: This machine uses a Micronics system board with a SiS-manufactured Micronics chipset and Phoenix ROM   */
	/*       BIOS.                                                                                                  */
	/* NOTE 2: The closest matching Phoenix ROM BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/atlas_486sx_25/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_atlas_pronet_486ux_series_init(const machine_t *model)
{
	/* Atlas ProNet 486UX Series */
	int ret;
	ret = bios_load_linear(L"roms/machines/atlas_pronet_486ux_series/ami_j-bond_a433c-c.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* ATronics International */
int
machine_at_atronics_ati_486_init(const machine_t *model)
{
	/* ATronics ATI 486SX/20  */
	/* ATronics ATI 486SX/25  */
	/* ATronics ATI 486B/50   */
	/* ATronics ATI-486/50DX2 */
	/* NOTE  : These machines use a system board with a UMC chipset.          */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/atronics_ati_486/3umm001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_opti495_ami_common_init(model); */ /* Substituting for original chipset until documents are available */
	return ret;
}

int
machine_at_atronics_486_init(const machine_t *model)
{
	/* ATronics ATI-486-50 */
	/* ATronics ATI-486-66 */
	/* NOTE  : These machines use a system board with a UMC chipset.          */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/atronics_486/486-UM486-UM486sx.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

int
machine_at_atronics_486_vesa_init(const machine_t *model)
{
	/* ATronics ATI-466 Multi-Media */
	/* ATronics Bronze 466 VESA     */
	/* NOTE  : This machine uses a system board with a USAI (USA Integration) chipset.          */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/atronics_486_vesa/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

/* ATS */
int
machine_at_ats_ami_multimedia_486_66_init(const machine_t *model)
{
	/* ATS AMI Multimedia 486-66 */
	/* NOTE: This machine was reviewed by PC World in January 1994 for the February 1994 issue and uses a system  */
	/*       board with 2 VL-Bus slots and at least 4 standard ISA slots and which uses 4 72-pin memory slots and */
	/*    which also supports up to 64 MB of RAM and 256 KB of cache memory, and also used an AMIBIOS (8/8/1993). */
	/*                                                                                                            */
	/*       The closest available component listings are for the "Predator I Plus Overdrive" system board from   */
	/*       "American Predator Corporation". According to the same PC World article, this machine lacked both a  */
	/*       ZIF socket and an upgrade socket, however, the system board mentioned above still appears to support */
	/*       486 and Pentium OverDrive CPUs according to the documents available.                                 */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/ats_ami_multimedia_486_66/486-genoa_vlb.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Aurum Computer Corporation */
int
machine_at_aurum_goldnote_dx2_50_init(const machine_t *model)
{
	/* Aurum GoldNote DX2-50 */
	/* NOTE: This portable machine was manufactured by First International Computer and uses a system board with a */
	/*       Symphony Labs chipset and AMIBIOS (07/07/1991).                                                       */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/deico_predator/ami_386_za590821.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Austin (IPC) */
int
machine_at_austin_486sx_20_winstation_init(const machine_t *model)
{
	/* Austin 486SX/20 WinStation */
	/* Austin 486-33I  WinStation */
	/* NOTE  : These machines use a Deico system board with an OPTi chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/austin_486sx_20_winstation/386-OPTI-386WB-10.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device); */
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_austin_486dx2_66_init(const machine_t *model)
{
	/* Austin Communications Manager 486DX2-66 */
	/* NOTE: This machine uses an Intel system board (BIOS version AY0) */
	int ret;
	ret = bios_load_linear_combined(L"roms/machines/austin_486dx2_66/1005AY0_.BIO",
		L"roms/machines/austin_486dx2_66/1005AY0_.BI1", 0x1c000, 128);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	/* device_add(&intel_flash_bxt_ami_device); */
	device_add(&i420tx_device);
	return ret;
}

/* Automated Computer Technology */
int
machine_at_act386_33fe_init(const machine_t *model)
{
	/* ACT386-33FE */
	/* NOTE: This machine uses uses a system board which uses discrete logic chips in place of an actual chipset and */
	/*       which uses the 04/09/1990 version of AMIBIOS.                                                           */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/act386_33fe/386-702430d-ROM0.BIN",
	L"roms/machines/act386_33fe/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/act386_33fe/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* AUVA Computer */
int
machine_at_auva_386_40_init(const machine_t *model)
{
	/* AUVA TAM33-U0 */
	/* AUVA TAM33-U1 */
	/* AUVA TAM40-U0 */
	/* AUVA TAM40-U1 */
	/* AUVA 386/40   */
	/* NOTE  : These machines use an AUVA system board with a UMC chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/auva_386_40/386-ISA-386U30.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* AVI Systems */
int
machine_at_avi_anb3_386sxl_25_init(const machine_t *model)
{
	/* AVI ANB3-386SXL-25 */
	/* NOTE: This portable machine uses a system board with an Acer chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/avi_anb3_386sxl_25/acer386.bak",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_ali1429_common_init(model); */
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Axik */
int
machine_at_axik_ace_cache_486_init(const machine_t *model)
{
	/* Axik           486/WB/50 */
	/* Axik           486DX-33  */
	/* Axik           486DX-50  */
	/* Axik           486DX2-50 */
	/* Axik           486DX2-66 */
	/* Axik Ace Cache 486SX-25  */
	/* Axik Ace Cache 486DX2-50 */
	/* NOTE  : The Axik 486/WB/50, Axik Ace Cache 486SX-25, and Axik Ace Cache 486DX2-50 machines use a system board with*/
	/*         a Contaq chipset and AMIBIOS, with the Axik 486/WB/50 using and "AMI 2.0" BIOS and the Axik Ace Cache     */
	/*         486SX-25 and Axik Ace Cache 486DX2-50 use the 12/12/1991 version of AMIBIOS, with the remaining machines  */
	/*         still to be veriified but most likely using the same or similar components.                               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/axik_ace_cache_486/486-contaq.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_axik_ace_cache_486_33v_66v_init(const machine_t *model)
{
	/* Axik Ace Cache 486-33V/MPC */
	/* Axik Ace Cache 486DX2-66V  */
	/* Axik Ace Cache 486DX2-66VG */
	/* NOTE: These systems use a system board with a SiS chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/axik_ace_cache_486_33v_66v/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_axik_ace_cache_466_vg2_init(const machine_t *model)
{
	/* Axik Ace Cache 466 VG2 Cutlass */
	/* NOTE: This machine use appears to use a system board with a SiS 471 chipset and Award BIOS (4.50G) */
	int ret;
	ret = bios_load_linear(L"roms/machines/axik_ace_cache_466_vg2_cutlass/SV2G0304.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_2ch_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Bell */
int
machine_at_bell_bsp_1340_init(const machine_t *model)
{
	/* Bell BSP 1340 */
	/* NOTE: This machine uses a system board with an OPTi chipset and AMIBIOS. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/bell_bsp_1340/386-OPTI-386WB-10.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device); */
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Bi-Link Computer */
int
machine_at_bi_link_i486dx2_66_init(const machine_t *model)
{
	/* Bi-Link Desktop i486DX2/66 */
	/* NOTE: This machine uses an AIR system board with a UMC chipset and AMIBIOS. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/bi_link_i486dx2_66/386-UMC-3FLUD.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for UMC chipset until original chipset is added */
	return ret;
}

/* BitWise Designs */
int
machine_at_bitwise_model_433_init(const machine_t *model)
{
	/* BitWise Model 433 */
	/* NOTE: This machine uses uses an AIR Research system board with a Chips and Technologies chipset and AMIBIOS */
	/*       (May 1990)                                                                                            */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/bitwise_model_433/386-702430d-ROM0.BIN",
	L"roms/machines/bitwise_model_433/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/bitwise_model_433/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);

	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

/* Blackship */
int
machine_at_blackship_486sx_20u_init(const machine_t *model)
{
	/* Blackship 486SX/20U */
	/* NOTE: This machine uses uses a system board with a VLSI chipset and AMIBIOS (04/09/1990). */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/acma_486_25/386-702430d-ROM0.BIN",
	L"roms/machines/acma_486_25/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/blackship_486sx_20u/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);

	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

int
machine_at_blackship_blk_386_40_init(const machine_t *model)
{
	/* Blackship BLK 386/40 */
	/* NOTE  : This machine uses a system board with an OPTi chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blackship_blk_386_40/386-OPTI-386WB-10.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device); */
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_blackship_blk_486sx25_init(const machine_t *model)
{
	/* Blackship BLK 486SX/25     */
	/* Blackship BLK 486/33       */
	/* NOTE: These machines use a Freetech (Free Technology/FCT) system board with an OPTi chipset and AMIBIOS */
	/*       (06/06/1992)                                                                                      */
	/* NOTE 2: The closest matching AMIBIOS 12/12/1991 version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blackship_blk/486-920087335.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_blackship_blk_486dx2_66_init(const machine_t *model)
{
	/* Blackship BLK-486/33       */
	/* Blackship BLK 486DX2/66    */
	/* Blackship BLK 486DX2/66 LB */
	/* Blackship BLK 486/33 LB    */
	/* NOTE: The first system uses an American Megatrends Baby Voyager system board with an AMI chipset, while  */
	/*       the second system appears to use a PC Ware AT-168 system board with an ACC Micro chipset. Although */
	/*       the available documents for the second board state a maximum of 32 MB of RAM, the PC World November*/
	/*       1993 issue from October that year states that the machine supported a maximum of 64 MB.            */
	/*                                                                                                          */
	/*       We have not been able to find a 100% original BIOS for either of these machines, however, since    */
	/*       the first system uses the 12/12/1991 AMIBIOS version, and since the second machine's system board  */
	/*       was also likely to have used an AMIBIOS, a version of the 12/12/1991 AMIBIOS for the OPTi chipset  */
	/*       is substituting for the original BIOSes until they become available.                               */
	/* NOTE 2: The closest matching AMIBIOS 12/12/1991 version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blackship_blk_486dx2_66/HAWK.BIO",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_blackship_atlantis_init(const machine_t *model)
{
	/* Blackship 486DX2-66 Minitower */
	/* Blackship Atlantis            */
	/* Blackship BLK DX4/100         */
	/* NOTE: These machines use a system board with a SiS chipset and Award BIOS (07/26/1992) */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blackship_atlantis/486-SiS 486SL.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Blue Star Marketing */
int
machine_at_blue_star_486sx_25_desktop_init(const machine_t *model)
{
	/* Blue Star Upgradable       */
	/* Blue Star 486SX/25 Desktop */
	/* Blue Star 466D2U           */
	/* NOTE: These machines use a Zenny/ZEN system board with a UMC chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blue_star_486sx_25_desktop/3umm001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_opti495_ami_common_init(model); */
	return ret;
}

int
machine_at_blue_star_486dx_33_series_ii_init(const machine_t *model)
{
	/* Blue Star 486DX/33 Series II VLB/MM-Kit #7  */
	/* Blue Star 486                VLB Pro Series */
	/* NOTE: These machines use a Tyan system board with a SiS chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blue_star_486dx_33_series_ii/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* BOSS Technology */
int
machine_at_boss_486sx_25_cache_init(const machine_t *model)
{
	/* BOSS 486SX/25 Cache */
	/* NOTE: This machine uses uses a system board with a Chips and Technologies chipset and AMIBIOS. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/boss_486sx_25_cache/386-mb1325pm OK.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

int
machine_at_boss_466d_init(const machine_t *model)
{
	/* BOSS 466d */
	/* NOTE  : This machine uses an AMI system board with an AMI chipset and AMIBIOS (12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/boss_466d/HAWK.BIO",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device); */
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Brain Computer Corporation */
int
machine_at_the_brain_386_33_init(const machine_t *model)
{
	/* The Brain 386-33 */
	/* NOTE: This machine uses a system board with an OPTi chipset and AMIBIOS (December 1989). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/the_brain_386_33/386-BIG AMI 896818 EVEN.BIN",
		L"roms/machines/the_brain_386_33/386-BIG AMI 896818 ODD.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	/* machine_at_opti495_ami_common_init(model); */
	return ret;
}

/* BRICK-PC */
int
machine_at_brick_9002_4dxu_init(const machine_t *model)
{
	/* Brick 9002 4DXU */
	/* NOTE: This machine uses an Asus ISA-486SV2B system board with a SiS chipset and AMIBIOS (08/08/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/brick_9002_4dxu/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Broadax Systems (BSi) */
int
machine_at_broadax_bsi_486_init(const machine_t *model)
{
	/* Broadax BSi 486DX2-50 */
	/* Broadax BSi 486DX2-66 */
	/* NOTE: These machines use a TMC (Taiwan MyComp) system board with an OPTi chipset and AMIBIOS (06/06/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/broadax_bsi_486/486-920087335.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_broadax_bsi_nb486dx2_50_init(const machine_t *model)
{
	/* Broadax BSi NB486DX2-50 */
	/* Broadax BSi NP846 Mono  */
	/* Broadax BSi NP846D      */
	/* Broadax BSi NP846T      */
	/* NOTE: These portable machines were manufactured by Nan Tan Computer and use a system board with an ETEQ chipset   */
	/*       and Award BIOS (11/22/1989 for the first system, Award 3.2 for the second system, Award 3.2-V for the third */
	/*       system, and Award 3.2-F for the fourth system).                                                             */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/broadax_bsi_nb486dx2_50/lion3500.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_broadax_bsi_np9249d_init(const machine_t *model)
{
	/* Broadax BSi NP9249D */
	/* NOTE: This portable machine was manufactured by Nan Tan Computer and uses a system board with a SiS chipset and */
	/*       Award BIOS (08/05/1994).                                                                                  */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/commax_smartbook_iii/7500d_rev26_121593.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_broadax_bsi_np9549d_init(const machine_t *model)
{
	/* Broadax BSi NP9549D */
	/* NOTE: This portable machine was manufactured by Nan Tan Computer and MicroStar and uses a system board with a SiS */
	/*       chipset and AMIBIOS (03/02/1995).                                                                           */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/commax_smartbook_iii/7500d_rev26_121593.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Bus Computer Systems */
int
machine_at_bus_386_33_init(const machine_t *model)
{
	/* Bus 386-33 */
	/* NOTE: This machine uses an ARMAS system board which uses discrete logic in place of an actual chipset and which */
	/*       uses the 12/15/1989 version of AMIBIOS.                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/bus_386_33/286-vlsi-002350-041_32k.bin",
		L"roms/machines/bus_386_33/286-vlsi-002350-042_32k.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* C2 Micro Systems */
int
machine_at_c2_micro_486sx_init(const machine_t *model)
{
	/* C2 Micro 486SX   */
	/* C2 Saber 486/SLC */
	/* C2 Saber 4X25    */
	/* C2 Saber/50      */
	/* C2 Saber DX/2     */
	/* NOTE: The C2 Micro 486SX and C2 Saber/50 use an ERI system board with a Symphony Labs chipset and AMIBIOS (05/05/ */
	/*       1991), while the remaining systems use a similar system board with the 07/07/1991 version of AMIBIOS.       */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/c2_micro_486sx/386-386 SC Syphony.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_c2_saber_sound_init(const machine_t *model)
{
	/* C2 Saber Sound */
	/* NOTE: This machine uses an Alaris Leopard system board */
	int ret;
	ret = bios_load_linear(L"roms/machines/c2_saber_sound/486-RYC-Leopard-LX.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_c2_saber_486_vl_init(const machine_t *model)
{
	/* C2 Saber 486 VL */
	/* NOTE: This machine uses a Micro Computer Center system board with an OPTi 495 chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/c2_saber_486_vl/opt495sx.ami",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* CAD ONE Computer Design */
/* See Chicony Electronics */

/* CAF */
int
machine_at_caf_vl_bus_series_init(const machine_t *model)
{
	/* CAF VL-Bus Series */
	/* CAF VL DX/33      */
	/* CAF VL DX2/66     */
	/* NOTE: These machines use a system board with a SiS chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/caf_vl_bus_series/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Caliber */
int
machine_at_caliber_aspect_smart_weapon_init(const machine_t *model)
{
	/* Caliber-Aspect Smart Weapon 486-66 */
	/* NOTE: This system was reviewed by PC World in January 1994 for their February 1994 issue and uses the      */
	/*       8/8/1993 version of AMIBIOS and appears to use a VL-486 system board with a UMC chipset, judging     */
	/*       by the characteristics of the system board itself that were described by PC World.                   */
	/*                                                                                                            */
	/*       The page found for the VL-486 system board does not state OverDrive compatibility, although the PC   */
	/*       World article itself mentioned that the board used in the Caliber computer uses a 238-pin (non-ZIF)  */
	/*       CPU socket. All other descriptions of the board however match 100%.                                  */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/caliber_aspect_smart_weapon_486_66/4umm002.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for UMC chipset until actual chipset is added */
	return ret;
}

/* Chicony Electronics */
int
machine_at_chicony_ch_386_init(const machine_t *model)
{
	/* Chicony CH-386-33H            */
	/* Chicony CH-386-40H            */
	/* Chicony CH-486DLC-33H         */
	/* Chicony CH-486DLC-40H         */
	/* CAD ONE 386-33 MHz  64k Cache */
	/* CAD ONE 386-33 MHz 256k Cache */
	/* CAD ONE 386-40 MHz  64k Cache */
	/* NOTE: These machines a Chicony CH-386-33H, CH-386-40H, CH-486DLC-33H, or CH-486DLC-40H system board with an OPTi */
	/*        chipset and AMIBIOS.                                                                                      */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available.                        */
	int ret;
	ret = bios_load_linear(L"roms/machines/chicony_ch_386/386-OPTI-386WB-10.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_chicony_ch_486_33c_init(const machine_t *model)
{
	/* Chicony CH-486-25C            */
	/* Chicony CH-486-33C            */
	/* Chicony CH-486S-25C           */
	/* Chicony CH-486S-33C           */
	/* CAD ONE 486-25 MHz 128k Cache */
	/* CAD ONE 486-33 MHz 256k Cache */
	/* CAD ONE 486-50 MHz            */
	/* NOTE: These machines use a Chicony CH-486-25C or CH-486-33C system board with a UMC chipset and AMIBIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/chicony_ch_486_33c/ch-486-33c_ami_bios_z944944_am27.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for UMC chipset until actual chipset is added */
	return ret;
}

/* Clone Factory */
int
machine_at_clone_386_33c_init(const machine_t *model)
{
	/* Clone 386-33C */
	/* NOTE: This machine uses uses a Mek-Fab system board with an OPTi chipset and AMIBIOS (04/09/1990). */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/clone_386_33c/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_opti495_ami_common_init(model); */
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_clover_486_i_series_init(const machine_t *model)
{
	/* Clover 486-I Series */
	/* NOTE: This machine uses a QuickPath system board with an OPTi chipset and Microid Research BIOS. */
	/* NOTE 2: The closest matching Microid Research BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/clover_486_i_series/opt495sx.mr",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Clover */
int
machine_at_clover_486_quick_i_series_init(const machine_t *model)
{
	/* Clover 486 Quick-I Series */
	/* NOTE  : These machines use a QuickPath system board with an OPTi chipset and AMIBIOS (06/01/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/clover_486_quick_i_series/386-OPTI-386WB-10.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_clover_pro_vm486_init(const machine_t *model)
{
	/* Clover PRO-VM486 */
	/* NOTE: This machine uses a system board with a Contaq chipset and AMIBIOS (11/11/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/clover_pro_vm486/486-MS4125.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Club American */
int
machine_at_club_falcon_init(const machine_t *model)
{
	/* Club Falcon 325  */
	/* Club Falcon 333  */
	/* Club Falcon 420  */
	/* Club Falcon 425  */
	/* Club Falcon 433  */
	/* Club Falcon 433T */
	/* Club Falcon 450  */
	/* Club Falcon 450T */
	/* NOTE: These machines use a system board with a VLSI chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/club_falcon/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* device_add(&vlsi_scamp_device); */
	return ret;
}

/* CMO */
int
machine_at_cmo_flb433x_init(const machine_t *model)
{
	/* CMO FLB433X */
	/* NOTE: This machine uses a Shuttle Data system board with an OPTi 495 chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/cmo_flb433x/opt495sx.ami",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Comex */
int
machine_at_comex_486dx2_66_init(const machine_t *model)
{
	/* Comex 486SX/25 VESA */
	/* Comex 486DX2/66     */
	/* NOTE: These machines use a Micronics system board with a Chips and Technologies and Micronics chipset and Phoenix */
	/*       ROM BIOS (0.10 g20-2) or October 1992.                                                                      */
	/* NOTE 2: The closest matching Phoenix ROM BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/comex_486dx2_66/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Commax */
int
machine_at_commax_smartbook_iii_init(const machine_t *model)
{
	/* Commax SmartBook III */
	/* NOTE: This portable machine uses a system board with a SiS chipset and Award BIOS (09/06/1994). */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/commax_smartbook_iii/7500d_rev26_121593.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Commodore Business Machines */
int
machine_at_commodore_dt486_init(const machine_t *model)
{
	/* Commodore 486SX-25       */
	/* Commodore 486-33C        */
	/* Commodore PC DT 486SX-25 */
	/* Commodore DT 486-33C     */
	/* NOTE: This machine uses a DTK PKM-3363Y system board with a Symphony Labs SL82C461 chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/commodore_dt486/cbm-dt486dx-33c-bios-u32--v1.01-391521-02.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_commodore_t486_init(const machine_t *model)
{
	/* Commodore Tower 486 */
	/* NOTE: This machine uses a system board with a Solution chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/commodore_dt486/cbm-t486dx-bios-v-xxxxxx-xx.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_commodore_t486_50c_init(const machine_t *model)
{
	/* Commodore T 486 - 50C */
	/* NOTE: This machine uses a system board with a Solution chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/commodore_dt486/cbm-t486dx-50-bios-v1.03-.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_commodore_t486_66c_init(const machine_t *model)
{
	/* Commodore T 486 - 66C (BIOS v1.01) */
	/* NOTE: This machine uses a system board with a Solution chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/commodore_dt486/cbm-t486dx-66-bios-v1.01-391566-02.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_commodore_t486_66c2_init(const machine_t *model)
{
	/* Commodore T 486 - 66C (BIOS v1.03) */
	/* NOTE: This machine uses a system board with a Solution chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/commodore_dt486/cbm-t486dx-66-bios-v1.03-391684-02.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Comp & Soft Experts */
int
machine_at_comp_n_soft_486_33c256_init(const machine_t *model)
{
	/* Comp & Soft 486/33C256 */
	/* NOTE: This machine uses an American Digicom system board with a Symphony chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/comp_n_soft_486/386-386 SC Syphony.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_comp_n_soft_486_25sx256_vlb_init(const machine_t *model)
{
	/* Comp & Soft CS 486/25SX256-VLB */
	/* NOTE: This machine uses an EFA system board with a SiS chipset and AMIBIOS (06/06/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/comp_n_soft_486/ft01232.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* CompuAdd */
int
machine_at_compuadd_express_scalable_init(const machine_t *model)
{
	/* CompuAdd Express 325DX  Scalable */
	/* CompuAdd Express 333DX  Scalable */
	/* CompuAdd Express 340DX  Scalable */
	/* CompuAdd Express 440DLC Scalable */
	/* CompuAdd Express 425SX  Scalable */
	/* CompuAdd Express 425DX  Scalable */
	/* CompuAdd Express 433DX  Scalable */
	/* CompuAdd Express 466DX2 Scalable */
	/* NOTE: These machines use a BCM system board with an OPTi chipset and AMIBIOS (2.0 or 12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS 12/12/1991 version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/compuadd_express_scalable/HAWK.BIO",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_compuadd_c4100d_init(const machine_t *model)
{
	/* CompuAdd C4100D */
	/* CompuAdd C466D Desktop */
	/* NOTE: These machines use a Micronics MPower4 system board */
	/* NOTE 2: The LPX30WB BIOS is used until an original BIOS dump is available */
	int ret;
	/* ret = bios_load_linear(L"roms/machines/compuadd_c4100d/LPX-03.BIN",
	0x000e0000, 131072, 0); */
	ret = bios_load_linear(L"roms/machines/compuadd_c466d/lx-03.64",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_compuadd_c466d_init(const machine_t *model)
{
	/* CompuAdd C466D */
	/* NOTE: This machine uses a Micronics MX30 system board */
	/* NOTE 2: The LX30 BIOS is used until an original BIOS dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/compuadd_c466d/lx-03.64",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Compudyne */
int
machine_at_compudyne_486_init(const machine_t *model)
{
	/* Compudyne 486DX/33 Multimedia System */
	/* Compudyne SCI4DX2-66                 */
	/* Compudyne 486 System                 */
	/* NOTE: These machines use an SCI system board with an OPTi chipset and AMIBIOS (6/6/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/compudyne_486dx33/OPT495SX.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Computer Market Place */
int
machine_at_computer_market_place_486_init(const machine_t *model)
{
	/* Computer Market Place Ultra 486-25 */
	/* NOTE: This machine uses an A.I.R system board which uses discrete logic in place of an actual chipset and which */
	/*       uses an AMIBIOS version from December 1989.                                                               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/computer_market_place_ultra_486_25/286-vlsi-002350-041_32k.bin",
		L"roms/machines/computer_market_place_ultra_486_25/286-vlsi-002350-042_32k.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Computer Products United */
int
machine_at_cpu_386_20_25_init(const machine_t *model)
{
	/* CPU 386/20 */
	/* CPU 386/25 */
	/* NOTE: These machines use an American Megatrends AMI-386XT system board for the first system and AMI-386AT Mark-II */
	/*       system board for the second system with a Chips and Technologies chipset and AMIBIOS (December 1988).       */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/cpu_386_20_25/286-CHIPS-AMI1190-EVEN.BIN",
		L"roms/machines/cpu_386_20_25/286-CHIPS-AMI1190-ODD.BIN",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_scat486_init(model, 0);
	/* machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device); */
	return ret;
}

/* Computer Sales Professional */
/* See Quantex */

/* Computer Square (LOCAL RETAILER) */
int
machine_at_computer_square_pcn1_init(const machine_t *model)
{
	/* Computer Square PCN1 486DX2/66 */
	/* NOTE: This is a machine from Chicago-based retailer Computer Square, reviewed for PC World in October 1993 */
	/*       for their November 1993 issue, and which appears to use a DTK system board, specifically a DTK       */
	/*       PKM-0037S or DTK PKM-5037S system board with a SiS 461 chipset (SiS 85C461) and an AMIBIOS (the same */
	/*       article has also mentioned the use of the 6/6/1992 AMIBIOS version in some of the machines reviewed).*/
	/*                                                                                                            */
	/*       It appears that Computer Square was also known as "Myoda Computer Square", "Computer Square Myoda",  */
	/*       and "Myoda Computer Center", and that it was controlled by mail-order computer manfacturer Myoda, a  */
	/*       company which was formerly based in Naperville, Illinois and which later moved to Hoffman Estates,   */
	/*       Illinois (both of which are next to Schaumburg where Computer Square was based), and whose machines  */
	/*       have also been reviewed in PC Magazine.                                                              */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/computer_square_pcn1/ft01232.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* CompuTrend */
int
machine_at_computrend_premio_486_init(const machine_t *model)
{
	/* CompuTrend Premio 486          */
	/* Magic Box Power VESA 486DX2-66 */
	/* NOTE: The CompuTrend Premio 486 is a machine from CompuTrend (later known as Premio), while the Magic Box  */
	/*       Power VESA 486DX2-66 is a machine from Miami-based retailer Magic Box, the latter of which was       */
	/*       reviewed by PC World in October 1993 for their November 1993 issue. These systems have 6 ISA slots   */
	/*       and 2 VL-Bus slots and support up to a maximum of 1024 KB cache memory with 256 KB being the default */
	/*       that these machines shipped with.                                                                    */
	/*                                                                                                            */
	/*       According to the same PC World article, these systems supported up to a maximum of 32 MB of RAM and  */
	/*      uses a ZIF socket, however, the closest matching system board that we were able to find specifications*/
	/*       for, the Young Micro Systems VEGA 486F-2VL, supports up to a maximum of 64 MB and appears to lack a  */
	/*       ZIF socket, though people have successfully installed ZIF adapters on machines with standard sockets.*/
	/*       The same system board also uses a Symphony 82C461 chipset, which was manufactured by Symphony Labs   */
	/*      (later known as SiS, or Silicon Integrated Systems), and which is very likely to be largely equivalent*/
	/*       to a SiS 461 chipset.                                                                                */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/computrend_premio_486/486-Peacock PCK486DX.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Comtrade */
int
machine_at_comtrade_486_init(const machine_t *model)
{
	/* Comtrade Multimedia (VL-Bus) 66 */
	/* Comtrade VL-Bus Best Buy 66     */
	/* NOTE: These machines use a Join Data system board with a HiNT chipset and AMIBIOS (1/15/1993) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/comtrade_486/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

/* Cornell Computer Systems */
int
machine_at_cornell_power_pak_init(const machine_t *model)
{
	/* Cornell Power Pak */
	/* NOTE: This machine uses a Diamond FastBus VLB system board with a special ROM BIOS that was produced by Chips  */
	/*       and Technologies and subsequently modified by Diamond itself for use in its own boards.                  */
	/*                                                                                                                */
	/*       The original ROM BIOS update had a file name of "fb_12j.exe", from which the BIOS file for the updated   */
	/*       BIOS could be extracted and flashed to an actual machine using that board. Unfortunately, the FTP servers*/
	/*       containing the files have seen been taken down, so the closest match (also from Chips and Technologies)  */
	/*       is used instead.                                                                                         */
	/*                                                                                                                */
	/*       However, the emulator will still allow the use of the original 128 KB ROM BIOS files in the event that   */
	/*       they should become available again in the future.                                                        */
	int ret;
	ret = bios_load_linear(L"roms/machines/cornell_power_pak/2ctc001.bin",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_scat486_init(model, 1);
	return ret;
}

/* Cornell Computer Systems */
int
machine_at_cornell_power_pak2_init(const machine_t *model)
{
	/* Cornell Power Pak */
	/* NOTE: This machine uses a Diamond FastBus VLB system board with a special ROM BIOS that was produced by Chips  */
	/*       and Technologies and subsequently modified by Diamond itself for use in its own boards.                  */
	/*                                                                                                                */
	/*       The original ROM BIOS update had a file name of "fb_12j.exe", from which the BIOS file for the updated   */
	/*       BIOS could be extracted and flashed to an actual machine using that board. Unfortunately, the FTP servers*/
	/*       containing the files have seen been taken down, so the closest match (also from Chips and Technologies)  */
	/*       is used instead.                                                                                         */
	/*                                                                                                                */
	/*       However, the emulator will still allow the use of the original 128 KB ROM BIOS files in the event that   */
	/*       they should become available again in the future.                                                        */
	int ret;
	ret = bios_load_linear(L"roms/machines/cornell_power_pak/fb_12j.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_scat486_init(model, 1);
	return ret;
}

/* Cornell Computer Systems */
int
machine_at_cornell_power_pak3_init(const machine_t *model)
{
	/* Cornell Power Pak */
	/* NOTE: This machine uses a Diamond FastBus VLB system board with a special ROM BIOS that was produced by Chips  */
	/*       and Technologies and subsequently modified by Diamond itself for use in its own boards.                  */
	/*                                                                                                                */
	/*       The original ROM BIOS update had a file name of "fb_12j.exe", from which the BIOS file for the updated   */
	/*       BIOS could be extracted and flashed to an actual machine using that board. Unfortunately, the FTP servers*/
	/*       containing the files have seen been taken down, so the closest match (also from Chips and Technologies)  */
	/*       is used instead.                                                                                         */
	/*                                                                                                                */
	/*       However, the emulator will still allow the use of the original 128 KB ROM BIOS files in the event that   */
	/*       they should become available again in the future.                                                        */
	int ret;
	ret = bios_load_linear(L"roms/machines/cornell_power_pak/fb_12j.rom",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_scat486_init(model, 1);
	return ret;
}

/* CSR */
int
machine_at_csr_386_33_init(const machine_t *model)
{
	/* CSR 386/33 */
	/* NOTE: This machine uses a Hauppauge system board with a Chips and Technologies chipset and Award BIOS (3.03) */
	/*       (June 1989).                                                                                           */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/csr_386_33/80286-286S Turbo LO.BIN",
		L"roms/machines/csr_386_33/80286-286S Turbo HI.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_scat486_init(model, 0); */
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Cube */
int
machine_at_cube_atx_init(const machine_t *model)
{
	/* Cube 340 ATX */
	/* Cube 425 ATX */
	/* Cube 433 ATX */
	/* Cube 450 ATX */
	/* Cube 466 ATX */
	/* NOTE: These machines use a Deico system board with a Symphony chipset and AMIBIOS (AMI 1.1). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/cube_atx/386-386 SC Syphony.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* CUI */
int
machine_at_cui_advantage_486_init(const machine_t *model)
{
	/* CUI Advantage 486/25SX */
	/* CUI Advantage 486-50CX */
	/* NOTE: These machines use a system board with a Symphony chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/cui_advantage_486/386-386 SC Syphony.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* CyberMax */
int
machine_at_cybermax_ftn386_init(const machine_t *model)
{
	/* CyberMax 386/40          */
	/* Fountain 386SX           */
	/* Fountain FTNB386WH-40C   */
	/* MicroWarehouse 386/SX 33 */
	/* NOTE: These machines were manufactured by Fountain Technologies and use a system board with a VSLI SCAMP */
	/*       chipset and Quadtel BIOS.                                                                          */
	/* NOTE 2: The closest matching Quadtel BIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/cybermax_ftn386/2hlu001l.bin",
		L"roms/machines/cybermax_ftn386/2hlu001h.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Daewoo */
/* See Leading Edge */

/* DataStor (Data Storage Marketing) */
int
machine_at_datastor_isa_vl_init(const machine_t *model)
{
	/* DataStor 486-25SX   ISA VLB */
	/* DataStor 486-33SX   ISA VLB */
	/* DataStor 486-33DX   ISA VLB */
	/* DataStor 486-50DX2  ISA VLB */
	/* DataStor 486-66DX2  ISA VLB */
	/* NOTE: These machines use an ECS (Elitegroup Computer Systems) system board with a UMC chipset and AMIBIOS */
	/*       (11/11/1992).                                                                                       */
	/* NOTE 2: The closest matching AMIBIOS (11/11/1992) version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/datastor_isa_vlb/um486v.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

/* DataWorld */
int
machine_at_dataworld_data_486_dx2_50_init(const machine_t *model)
{
	/* DataWorld Data 486/DX2-50 */
	/* NOTE: This machine uses an ELT system board with an ETEQ chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/dataworld_data_486_dx2_50/ami_j-bond_a433c-c.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Deico */
int
machine_at_deico_predator_init(const machine_t *model)
{
	/* Deico Predator 386DX/25  */
	/* Deico Predator 386DX/33  */
	/* Deico Predator 386DX/40  */
	/* Deico Predator 486SX/20  */
	/* Deico Predator 486SX/25  */
	/* Deico Predator 486DX/25  */
	/* Deico Predator 486DX/33  */
	/* Deico Predator 486DX/50  */
	/* Deico Predator 486DX2/50 */
	/* Deico Predator 486DX2/66 */
	/* NOTE: These machines use a system board with a Symphony chipset and AMIBIOS (12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/deico_predator/ami_386_za590821.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Dell Computer */
int
machine_at_dell_system_486p_init(const machine_t *model)
{
	/* Dell System 486P/25 */
	/* Dell System 486P/33 */
	/* Dell System 486P/50 */
	/* Dell System 486P/66 */
	/* NOTE: These machines use a system board with a VLSI chipset and Phoenix BIOS */
	/* NOTE 2: The Dell 386SX BIOS is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/dell_system_486p/DELL386.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_dell_466_me_init(const machine_t *model)
{
	/* Dell 466/ME */
	/* NOTE: These machines use a system board with an Intel chipset and Phoenix BIOS (01/25/1993). */
	int ret;
	ret = bios_load_linear(L"roms/machines/dell_466_me/DELLBIOS.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_dell_dimension_xps_466v_init(const machine_t *model)
{
	/* Dell Dimension 425SV     */
	/* Dell Dimension 433V      */
	/* Dell Dimension 466V      */
	/* Dell Dimension XPS 450V  */
	/* Dell Dimension XPS 466V  */
	/* Dell Dimension XPS 4100V */
	/* NOTE: These machines use a Micronics system board with a Micronics chipset and Phoenix BIOS */
	int ret;
	/* ret = bios_load_linear(L"roms/machines/dell_dimension_xps_466v_4100v/SHK1A05.BIN",
	0x000e0000, 131072, 0); */
	ret = bios_load_linear(L"roms/machines/dell333sl/dell333sl.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}
int
machine_at_dell_optiplex_4100_l_init(const machine_t *model)
{
	/* Dell OptiPlex 433/LV */
	/* Dell OptiPlex 4100/L */
	/* NOTE: These machines use a system board with a Headland chipset and Phoenix BIOS */
	/* NOTE 2: The Dell 386SX BIOS is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/dell_system_486p/DELL386.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* machine_at_headland1_common_init(1); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Destiny */
int
machine_at_destiny_486_25_init(const machine_t *model)
{
	/* Destiny 486/25 */
	/* NOTE: This machine uses an A.I.R system board which uses discrete logic in place of an actual chipset and which */
	/*       uses an AMIBIOS version from December 1989.                                                               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/destiny_486_25/286-vlsi-002350-041_32k.bin",
		L"roms/machines/destiny_486_25/286-vlsi-002350-042_32k.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* DFI (Diamond Flower Industries) */
int
machine_at_dfi_mediabook_5110t_init(const machine_t *model)
{
	/* DFI MediaBook 5110T */
	/* NOTE: This portable machine was manufactured by Nan Tan Computer and uses a system board with a SiS chipset and */
	/*       Award BIOS (12/16/1994).                                                                                  */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/dfi_mediabook_5110t/7500d_rev26_121593.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Diamond */
int
machine_at_diamond_dt_486dx2_50_init(const machine_t *model)
{
	/* Diamond DT 486DX2/50 */
	/* NOTE: This machine uses a Dash system board with an OPTi chipset and AMIBIOS (06/06/1991).. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/diamond_dt_486dx2_50/486-920087335.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_diamond_dt_486_init(const machine_t *model)
{
	/* Diamond DT 486C-40 Multimedia */
	/* Diamond DT 486DX2-66          */
	/* NOTE: These machines use a Dennow system board with an OPTi chipset and AMIBIOS (3/3/1993). Note that */
	/*       "3/3/1993" may be a misprint of "8/8/1993".                                                     */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/diamond_dt_486c/386-opti-mini.bio",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_diamond_dt_486dx4_100_init(const machine_t *model)
{
	/* Diamond DT 486-66     */
	/* Diamond DT 486DX4-100 */
	/* NOTE: These machines use a system board with a SiS chipset and Award BIOS (02/02/1994) */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/diamond_dt_486dx4_100/486-SiS 486SL.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* int
machine_at_diamond_dt_p100_cyrix_init(const machine_t *model)
{ */
	/* Diamond DT P100-Cyrix */
	/* NOTE: This machine uses an Asus system board with a SiS chipset and Award BIOS (08/08/1995). */
	/* int ret;
	ret = bios_load_linear(L"roms/machines/diamond_dt_p100/4siw003.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init_ex(model, 2);
	device_add(&ls486e_nvr_device);

	machine_at_sis_85c496_common_init(model);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 4, 1, 2, 3);

	device_add(&fdc37c665_device);
	device_add(&keyboard_ps2_ami_pci_device);

	return ret;
} */

/* Digital (DEC) */
int
machine_at_decpc_xl_server_init(const machine_t *model)
{
	/* Digital DECpc XL Server 466d2 (v1.00) (English)          */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V100_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i420tx_device);
	return ret;
}

int
machine_at_decpc_xl_466d2_v101_init(const machine_t *model)
{
	/* Digital DECpc XL 466d2        (v1.01) (English)          */
	/* NOTE: This machine uses a system board with an Intel chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/EN5V101.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i420tx_device);
	return ret;
}

int
machine_at_decpc_xl_466d2_20_init(const machine_t *model)
{
	/* Digital DECpc XL 466d2        (v1.20) (English)          */
	/* NOTE: This machine uses a system board with an Intel chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V120_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i420tx_device);
	return ret;
}

int
machine_at_decpc_xl_466d2_21_init(const machine_t *model)
{
	/* Digital DECpc XL 466d2        (v1.21) (English)          */
	/* NOTE: This machine uses a system board with an Intel chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V121_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i420tx_device);
	return ret;
}

int
machine_at_decpc_xl_466d2_22_init(const machine_t *model)
{
	/* Digital DECpc XL 466d2        (v1.22) (English)          */
	/* NOTE: This machine uses a system board with an Intel chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V122_EN.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	/* device_add(&intel_flash_bxt_ami_device); */
	device_add(&i420tx_device);
	return ret;
}

int
machine_at_decpc_xl_466d2_init(const machine_t *model)
{
	/* Digital DECpc XL 466d2        (v2.00) (English)          */
	/* Digital DECpc XL Server 466d2 (v2.00) (English)          */
	/* NOTE: These machines use a system board with an Intel chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/decpc_xl/V200_en.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&ide_pci_2ch_device);
	pci_init(PCI_CONFIG_TYPE_2 | PCI_NO_IRQ_STEERING);
	pci_register_slot(0x00, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x01, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	pci_register_slot(0x06, PCI_CARD_NORMAL, 3, 2, 1, 4);
	pci_register_slot(0x0E, PCI_CARD_NORMAL, 2, 1, 3, 4);
	pci_register_slot(0x0C, PCI_CARD_NORMAL, 1, 3, 2, 4);
	pci_register_slot(0x02, PCI_CARD_SPECIAL, 0, 0, 0, 0);
	device_add(&keyboard_ps2_ami_pci_device);
	device_add(&sio_device);
	device_add(&fdc37c663_device);
	device_add(&intel_flash_bxt_ami_device);
	device_add(&i420tx_device);
	return ret;
}

/* Digital Scientific Research */
int
machine_at_dsr_tiger_386_init(const machine_t *model)
{
	/* DSR/Tiger 386 */
	/* NOTE: This machine uses a system board with a Texas Instruments Tiger chipset and Quadtel BIOS. */
	/* NOTE 2: The closest matching Quadtel BIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/dsr_tiger_386/2hlu001l.bin",
		L"roms/machines/dsr_tiger_386/2hlu001h.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Digitech */
int
machine_at_digitech_4d33_multimedia_init(const machine_t *model)
{
	/* Digitech Opusis 4D33 Multimedia System */
	/* NOTE: This system uses a Gigabyte system board with a UMC chipset and AMIBIOS (11/11/1992). */
	/* NOTE 2: The closest matching AMIBIOS (11/11/1992) version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/digitech_4d33_multimedia_system/um486v.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

/* DTK Computer */
int
machine_at_dtk486_init(const machine_t *model)
{
	/* DTK PKM-0038S E-2 */
	/* DTK Feat-39M      */
	/* NOTE: These machines use a DTK PKM-0038S E-2 system board with a SiS 471 chipset and Award BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk486/4siw005.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_dtk_dcn_4t66m_4t66p_init(const machine_t *model)
{
	/* DTK DCN-4T66M */
	/* DTK DCN-4T66P */
	/* NOTE: These portable machines use a system board with an ETEQ chipset and AMIBIOS (06/06/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_dcn_4t66m_4t66p/ami_j-bond_a433c-c.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_dtk_dtn_4t100p_init(const machine_t *model)
{
	/* DTK DTN-4T100P */
	/* NOTE: This portable machine uses a system board with an ACC Micro chipset and AMIBIOS (06/06/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/dtk_dtn_4t100p/acc386.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&acc2168_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Duracom Computer Systems */
int
machine_at_duracom_desksaver_486_vesa_init(const machine_t *model)
{
	/* Duracom Multimedia DeskSaver 486/33SX */
	/* Duracom            DeskSaver 486 VESA */
	/* NOTE: These machines use a DFI system board with a CONTAQ chipset and AMIBIOS (11/11/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/duracom_desksaver_486_vesa/486-MS4125.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_duracom_travelpro_nbac_init(const machine_t *model)
{
	/* Duracom TravelPro NBAC 486/33DX   Monochrome   */
	/* Duracom TravelPro NBAC 486/33DX  Passive Color */
	/* Duracom TravelPro NBAC 486/33DX   Active Color */
	/* Duracom TravelPro NBAC 486/66DX2  Monochrome   */
	/* Duracom TravelPro NBAC 486/66DX2 Passive Color */
	/* Duracom TravelPro NBAC 486/66DX2  Active Color */
	/* NOTE: These portable machines were manufactured by Nan Tan Computer and use a system board with an OPTi chipset */
	/*       and Award BIOS (11/22/1989).                                                                              */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/duracom_travelpro_nbac_486dx_33/lion3500.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_duracom_5110_init(const machine_t *model)
{
	/* Duracom 5110D */
	/* Duracom 5110  */
	/* NOTE: These portable machines use a system board with a SiS chipset and Award BIOS (09/06/1994). */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/duracom_5110/7500d_rev26_121593.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Dyna Micro */
int
machine_at_dyna_micro_dm486dx_250_init(const machine_t *model)
{
	/* Dyna Micro DMS486DX/250 */
	/* NOTE: This machine uses an Addonics/Asus system board with a SiS chipset and AMIBIOS (11/11/1992). */
	int ret;
	ret = bios_load_linear(L"roms/machines/dyna_micro_dm486dx_250/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_dyna_system_466_init(const machine_t *model)
{
	/* Dyna System 466 */
	/* NOTE: These machines use an Addonics system board with a SiS 471 chipset and Award BIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/dyna_system_466/SV2G0304.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_2ch_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Dynamic Decisions */
int
machine_at_dynex_486_init(const machine_t *model)
{
	/* Dynex 486 */
	/* NOTE: This machine uses uses a AMI Voyager system board with a Chips and Technologies chipset and AMIBIOS */
	/*       (04/09/1990).                                                                                       */
	/* NOTE 2: The closest matching AMIBIOS BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/acma_486_25/386-702430d-ROM0.BIN",
	L"roms/machines/acma_486_25/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/dynex_486/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);

	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

/* EasyData (GCH) */
int
machine_at_easydata_486dx_2_66_init(const machine_t *model)
{
	/* EasyData 486DX-2/66 */
	/* NOTE: This machine uses a GSS system board with a SiS chipset and AMIBIOS (12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/easydata_486dx_2_66/3sim001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
	/* machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret; */
}

/* Edge Technology */
/* See Micron Electronics */

/* Eltech Research */
int
machine_at_eltech_model_4500_dx2_init(const machine_t *model)
{
	/* Eltech Model 4500 DX2 */
	/* NOTE: This system uses a system board with a Symphony chipset and AMI BIOS (07/07/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/eltech_486/386-386 SC Syphony.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_eltech_model_4200_init(const machine_t *model)
{
	/* Eltech Model 4200 */
	/* Eltech Model 4330 */
	/* NOTE: These systems use a system board with a Symphony chipset and AMI BIOS (January 1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/eltech_486/386-386 SC Syphony.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Epson */
int
machine_at_epson_actionnote_880cx_init(const machine_t *model)
{
	/* Epson ActionNote 880C  */
	/* Epson ActionNote 880CX */
	/* NOTE: This portable machine was manufactured by ASE and uses a system board with an ACC Micro chipset and Phoenix */
	/*       ROM BIOS (04/19/1990).                                                                                      */
	/* NOTE 2: The closest matching Phoenix ROM BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/epson_actionnote_880cx/PHOE101T.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ibm_common_ide_init(model);
	device_add(&keyboard_ps2_device);
	device_add(&acc3221_device);
	device_add(&acc2168_device);
	return ret;
}

/* Ergo Computing */
int
machine_at_ergo_powerbrick_100_init(const machine_t *model)
{
	/* Ergo PowerBrick  50 */
	/* Ergo PowerBrick 100 */
	/* NOTE: These portable machines were manufactured by Arima and uses a system board with an ACC Micro chipset and */
	/*       Phoenix ROM BIOS.                                                                                        */
	/* NOTE 2: The closest matching Phoenix ROM BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/ergo_powerbrick_100/p101a002_sys_bios_62fc.u24",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ibm_common_ide_init(model);
	device_add(&keyboard_ps2_device);
	device_add(&acc3221_device);
	device_add(&acc2168_device);
	return ret;
}

/* ESI Automated Office Systems */
int
machine_at_esi_challenger_init(const machine_t *model)
{
	/* ESI Challenger */
	/* NOTE: This machine uses uses a system board with a Chips and Technologies chipset and AMIBIOS (09/15/1989). */
	/* NOTE 2: The closest matching AMIBIOS 09/15/1990 BIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/esi_challenger/386-DFI-386-20_Even.BIN",
		L"roms/machines/esi_challenger/386-DFI-386-20_Odd.BIN",
		0x000f0000, 65536, 0x08000);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

/* Everest Computer Corporation */
int
machine_at_everest_column_333_init(const machine_t *model)
{
	/* Everest Column 333 Professional */
	/* NOTE: This machine uses uses a CMP Enterprises system board with a Chips and Technologies chipset and AMIBIOS */
	/*       (09/15/1989).                                                                                           */
	/* NOTE 2: The closest matching AMIBIOS 09/15/1990 BIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/everest_column_333_professional/386-DFI-386-20_Even.BIN",
		L"roms/machines/everest_column_333_professional/386-DFI-386-20_Odd.BIN",
		0x000f0000, 65536, 0x08000);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

/* Everex */
int
machine_at_everex_tempo_m_init(const machine_t *model)
{
	/* Everex Tempo M Series */
	/* NOTE: These machines use a system board with an Everex chipset and customized version of AMIBIOS based on */
	/*       the 1987 core and further modified by Everex for use in the company's machines                      */
	/* NOTE 2: The closest matching Everex AMIBIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/everex_tempo_m/Everex EV-1806 - BIOS ROM - REV-F1A-21 - EVEN - U62.bin",
		L"roms/machines/everex_tempo_m/Everex EV-1806 - BIOS ROM - REV-F1A-21 - ODD - U61.bin",
		0x000f8000, 32768, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_everex_step_vl_eisa_init(const machine_t *model)
{
	/* Everex Step VL EISA DX-33  */
	/* Everex Step VL EISA DX2-50 */
	/* Everex Step VL EISA DX2-66 */
	/* NOTE: These machines use an MCCI system board with a SiS chipset and AMIBIOS (07/01/1993) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/everex_step_eisa_vl/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* First Computer Systems (FCS) */
int
machine_at_first_486_66_init(const machine_t *model)
{
	/* First 486-66 */
	/* NOTE: This machine uses an MCCI system board with an OPTi chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS (07/07/1991) version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/first_486_66/3opm001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* FiveStar Computers */
int
machine_at_zodiac_fivestar_386_33_init(const machine_t *model)
{
	/* Zodiac FiveStar 386/33 */
	/* NOTE: This machine uses uses a system board with uses discrete logic chips in place of an actual chipset and which*/
	/*       uses the 04/09/1990 version of AMIBIOS.                                                                     */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/zodiac_fivestar_386_33/386-702430d-ROM0.BIN",
	L"roms/machines/zodiac_fivestar_386_33/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/zodiac_fivestar_386_33/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);

	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

/* Fortron/Source */
int
machine_at_fortron_netset_433i_init(const machine_t *model)
{
	/* Fortron NetSet 433I */
	/* NOTE: This machine uses uses an AMI system board with a Chips and Technologies chipset and AMIBIOS */
	/*       (04/09/1990)                                                                                 */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/acma_486_25/386-702430d-ROM0.BIN",
	L"roms/machines/acma_486_25/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/fortron_netset_433i/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

/* Fountain Technologies */
/* See CyberMax, Inteva, MicroWarehouse, Quantex, or Pionex */

/* Future Micro */
int
machine_at_future_micro_ga_486vs_init(const machine_t *model)
{
	/* Future Micro GA-486VS */
	/* NOTE: This machine uses a Gigabyte GA-486VS system board with a SiS chipset and Award BIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/future_micro_ga_486vs/VS1121.ROM",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* FutureTech */
int
machine_at_futuretech_4414_init(const machine_t *model)
{
	/* FutureTech 4414  */
	/* FutureTech 4414A */
	/* NOTE: These machines use an Asus VL/I-486SV2GX4 system board with a SiS 471 chipset and Award BIOS (02/28/1994)*/
	int ret;
	ret = bios_load_linear(L"roms/machines/futuretech_4414/SV2G0304.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_2ch_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_futuretech_futuremate_462nv_init(const machine_t *model)
{
	/* FutureTech FutureMate 462nV */
	/* NOTE: This portable machine was manufactured by Nan Tan Computer and use a system board with an ETEQ chipset and */
	/*       Award BIOS (11/22/1989).                                                                                   */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/futuretech_futuremate_462nv/lion3500.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_futuretech_futuremate_fm910t_init(const machine_t *model)
{
	/* FutureTech FutureMate FM910T */
	/* NOTE: This portable machine was manufactured by Nan Tan Computer and Kapok and uses a system board with a SiS */
	/*       chipset and Award BIOS (08/05/1994).                                                                    */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/futuretech_futuremate_fm910t/7500d_rev26_121593.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_futuretech_futuremate_fm559d_init(const machine_t *model)
{
	/* FutureTech FutureMate FM559D */
	/* NOTE: This portable machine was manufactured by Dual and uses a system board with an ACC Micro chipset and AMIBIOS*/
	/*       (03/09/1995).                                                                                               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/futuretech_futuremate_fm559d/acc386.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&acc2168_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Gain Systems */
int
machine_at_gain_master_dx2_66_init(const machine_t *model)
{
	/* Gain Master DX2/66 */
	/* NOTE: This machine uses an AMI system board with a SiS chipset and AMIBIOS (12/15/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/gain_master_dx2_66/486-SiS_AC0360136.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Gateway 2000 */
int
machine_at_gateway_4dx2_66v_init(const machine_t *model)
{
	/* Gateway 2000 4DX2/66V */
	/* NOTE: This machine uses a Micronics Baby Gemini (DXLB) system board (09-00144 or 09-00169). */
	int ret;
	ret = bios_load_linear(L"roms/machines/gateway_4dx2_66v/LB01.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_gateway_4dx2_66v_glb05_init(const machine_t *model)
{
	/* Gateway 2000 4DX2/66V (BIOS upgrade) */
	/* NOTE: This machine uses a Micronics Baby Gemini (DXLB) system board (09-00144 or 09-00169). */
	int ret;
	ret = bios_load_linear(L"roms/machines/gateway_4dx2_66v/GLB05.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Gecco Computers */
int
machine_at_gecco_4dx_33_init(const machine_t *model)
{
	/* Gecco 4DX-33 */
	/* NOTE  : This machine uses a Koutech system board with an OPTi chipset and AMIBIOS (04/04/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/gecco_4dx_33/386-OPTI-386WB-10.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device); */
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Golden Star Technology */
int
machine_at_gst_486v_init(const machine_t *model)
{
	/* Golden Star Technology */
	/* NOTE: This machine uses a Micronics system board with a SiS-manufactured Micronics chipset and Phoenix ROM BIOS  */
	/* NOTE 2: The closest matching Phonex ROM BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/gst_486v/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* GoldStar */
int
machine_at_goldstar_gs433_init(const machine_t *model)
{
	/* GoldStar GS433 */
	/* NOTE: This machine uses a system board with a VLSI chipset and Quadtel BIOS (3.0). */
	/* NOTE 2: The closest matching Quadtel BIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/goldstar_gs433/2hlu001l.bin",
		L"roms/machines/goldstar_gs433/2hlu001h.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_gst_486v4_init(const machine_t *model)
{
	/* Golden Star Technology */
	/* NOTE: This machine uses a Micronics JX30GC system board with a SiS-manufactured Micronics chipset and Phoenix ROM */
	/*       BIOS (JX30GC-P01).                                                                                          */
	/* NOTE 2: The available JX30 BIOS files are in a non-extractable format that will only work when a flash device is */
	/*         present and for this reason the closest matching Phoenix ROM BIOS version is used until an original dump */
	/*         is available and/or until support is added for the system board's flash device.                          */
	int ret;
	ret = bios_load_linear(L"roms/machines/gst_486v4/lx-03.64",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* GRiD Systems */
/* GRiD MFP */
/* See Tandy Sensation! */

/* Hertz Computer Corporation*/
int
machine_at_hertz_486_d50x2e_init(const machine_t *model)
{
	/* Hertz 486/D50X2e */
	/* NOTE: This machine uses a system board with an ETEQ chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/hertz_d50x2e/ami_j-bond_a433c-c.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_hertz_486_d66x2gi_init(const machine_t *model)
{
	/* Hertz 486/D66X2Gi */
	/* NOTE: This system uses an Intel Classic R system board with a VSLI chipset and Phoenix BIOS (1.00.06) */
	int ret;
	ret = bios_load_linear(L"roms/machines/hertz_486_d66x2gi/AST101.09A",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_hertz_486d66x2ge_init(const machine_t *model)
{
	/* Hertz 486/D66X2Ge            */
	/* Hertz 486/D66X2Ge Multimedia */
	/* Hertz Z-Optima 486/D66X2e    */
	/* NOTE: This system uses a system board with a SiS chipset and AMIBIOS (4/9/1993) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/hertz_486d66x2ge/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_hertz_z_optima_486_notebook_init(const machine_t *model)
{
	/* Hertz Z-Optima 486 Notebook PC */
	/* NOTE: This portable machine uses a system board with an OPTi chipset and AMIBIOS (06/06/1992). /
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/hertz_z_optima_486_notebook_pc/opt495sx.ami",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Hewitt Rand */
int
machine_at_hewitt_rand_hr_486sx_25c_init(const machine_t *model)
{
	/* Hewitt Rand HR 486SX-25C */
	/* Hewitt Rand HR 486-50C   */
	/* NOTE: These machines use a system board with a Symphony chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/hewitt_rand_hr_486sx_25c/ami_386_za590821.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* HiQ (HiQuality Systems) */
int
machine_at_hiq_ultimate_433i_init(const machine_t *model)
{
	/* HiQ Ultimate 433I */
	/* NOTE: This machine uses a system board with an OPTi chipset and AMIBIOS (06/06/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/hiq_ultimate_433i/486-920087335.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_hiq_multimedia_multimagic_init(const machine_t *model)
{
	/* HiQ Multimedia Multimagic System */
	/* NOTE: This machine uses a Micronics system board with a SiS-manufactured Micronics chipset and Phoenix ROM BIOS */
	/*       (0.10 G22-2LB).                                                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/hiq_multimedia_multimagic/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_hiq_4dx33_green_pc_system_init(const machine_t *model)
{
	/* HiQ 4DX66 Green PC System */
	/* NOTE: This machine uses an Anix system board with a SiS chipset and AMIBIOS (08/08/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/hiq_4dx33_green_pc_system/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Hi-Tech USA */
int
machine_at_hi_tech_usa_dx6900a_1_init(const machine_t *model)
{
	/* Hi-Tech USA DX6900A-1 */
	/* NOTE: These machines use a PC Chips system board with a UMC chipset and AMIBIOS (07/25/1994). */
	int ret;
	/* ret = bios_load_linear(L"roms/machines/hi_tech_usa_dx6900a_1/DEEPGRN.BIN",
	0x000f0000, 65536, 0); */
	ret = bios_load_linear(L"roms/machines/hi_tech_usa_dx6900a_1/DEEPGRN.BIN",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Humphrey Instruments */
int
machine_at_humphrey_instruments_wam5737_init(const machine_t *model)
{
	/* Humphrey Instruments WAM5737 */
	/* NOTE: This system uses a Micronics EISA 3 VL-bus system board with EISA bus support and Phoenix BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/humphrey_instruments_wam5737/e3vl02.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Hyundai */
int
machine_at_hyundai_466d2_init(const machine_t *model)
{
	/* Hyundai 425S  */
	/* Hyundai 433S  */
	/* Hyundai 433D  */
	/* Hyundai 433DT */
	/* Hyundai 450D2 */
	/* Hyundai 466D2 */
	/* NOTE: These systems use a system board with an OPTi 495 chipset (AMIBIOS 6/6/1992) */
	/* NOTE 2: The closest matching AMIBIOS 6/6/1992 version is used until an original dump becomes available */
	/* NOTE 3: Certain machines (such as the 433S) have a minimum of 4 MB of RAM instead of 1 MB */
	int ret;
	ret = bios_load_linear(L"roms/machines/hyundai_466d2/OPT495SX.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* i Corp */
int
machine_at_i_corp_blazer_iis_init(const machine_t *model)
{
	/* i Corp Blazer IIs */
	/* NOTE: This machine uses a Maha system board with a Symphony chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/i_corp_blazer_iis/ami_386_za590821.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* IDS (International Data Systems) */
int
machine_at_ids_466i2_init(const machine_t *model)
{
	/* IDS 466i2 */
	/* NOTE: This machine uses uses an AMI Super Voyager system board with a Chips and Technologies chipset and AMIBIOS */
	/*       (12/12/1991).                                                                                              */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/ids_466i2/386-Peacock SCsxAIO.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

/* Image Microsystems */
int
machine_at_image_486dx_33_init(const machine_t *model)
{
	/* Image 486DX-33 */
	/* NOTE: This machine uses an Amptron system board with an OPTi chipset and AMIBIOS (07/19/1991). */
	/* NOTE 2: The closest matching AMIBIOS (11/11/1992) version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/image_486dx_33/386-OPTI-386WB-10.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_image_m_line_486dx2_66vl_init(const machine_t *model)
{
	/* Image M-Line 486DX2-66VL       */
	/* Image 486-DX-33 Vesa Local Bus */
	/* NOTE: These machines use a Gigabyte GA-486VT system board with a UMC chipset and AMIBIOS (11/11/1992). */
	/* NOTE 2: The closest matching AMIBIOS (11/11/1992) version is used until an original dump is available  */
	int ret;
	ret = bios_load_linear(L"roms/machines/image_m_line_486dx2_66vl/um486v.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

int
machine_at_initiative_iti_499vl_init(const machine_t *model)
{
	/* Initiative ITI 499VL  */
	/* Initiative ITI DX2-66 */
	/* NOTE: The first machine uses a Micronics JX30GC system board with a SiS-manufactured Micronics chipset and Phoenix*/
	/*       ROM BIOS (JX30GC-P01), while the second system appears to use a similar system board.                       */
	/* NOTE 2: The available JX30 BIOS files are in a non-extractable format that will only work when a flash device is  */
	/*         present and for this reason the closest matching Phoenix ROM BIOS version is used until an original dump  */
	/*         is available and/or until support is added for the system board's flash device.                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/iti_499vl/lx-03.64",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Inmac */
int
machine_at_inmac_insignia_450sl_init(const machine_t *model)
{
	/* Inmac Insignia 450SL */
	/* NOTE: These system uses an IBM-manufactured system board and AMIBIOS */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/inmac_insignia_466p/486-RYC-Leopard-LX.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_inmac_insignia_466p_init(const machine_t *model)
{
	/* Inmac Insignia 433P */
	/* Inmac Insignia 450P */
	/* Inmac Insignia 466P */
	/* NOTE: These systems use an IBM-manufactured system board and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/inmac_insignia_466p/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Insight */
int
machine_at_insight_486i_init(const machine_t *model)
{
	/* Insight 486SX-25   */
	/* Insight 486DX2-66I */
	/* NOTE: The first system uses a system board with an OPTi chipset and AMIBIOS (06/06/1991). The second */
	/*       machine's system board was identified as using the "AMI 4.01" version of AMIBIOS and also uses */
	/*       an OPTi chipset.                                                                               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/insight_486i/486-920087335.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_insight_486dx2_66_vl_init(const machine_t *model)
{
	/* Insight 486DX2-66 VL                */
	/* Insight 486DX2-66 VL-Bus Multimedia */
	/* NOTE: These machines appear to have used an Asus VL/ISA-486SV2 system board with a SiS chipset and AMIBIOS */
	/*       (11/11/1992).                                                                                        */
	int ret;
	ret = bios_load_linear(L"roms/machines/insight_486dx2_66_vl/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Intelec */
int
machine_at_intelec_int_486_50_init(const machine_t *model)
{
	/* Intelec INT 486-50 */
	/* NOTE: This machine uses an Octek Hippo II system board with an OPTi chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS (07/07/1991) version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/intelec_int_486_50/3opm001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* International Instrumentation */
int
machine_at_blue_max_monolith_486up_25s_init(const machine_t *model)
{
	/* International Instrumentation Blue Max Monolith 486UP/25S */
	/* NOTE: This system uses a Mylex MSI486 system board with an OPTi 495 chipset and Mylex 6.13 BIOS. */
	/* NOTE 2: The closest matching Mylex BIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blue_max_monolith_486up_25s/MSI627.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_blue_max_monolith_4250_diul_init(const machine_t *model)
{
	/* International Instrumentation Blue Max Monolith 4250 DIUL  */
	/* International Instrumentation Blue Max Monolith 486D2/66UP */
	/* NOTE: These machines use a system board with a Unichip chipset and AMIBIOS (12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blue_max_monolith_4250_diul/3ucm004.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_blue_max_monolith_init(const machine_t *model)
{
	/* International Instrumentation Blue Max Multimedia Monolith */
	/* NOTE: This machine uses a Young Micro system board with a Symphony chipset and AMIBIOS (06/06/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blue_max_multimedia_monolith/pck486dx.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_blue_max_monolith2_init(const machine_t *model)
{
	/* International Instrumentation Blue Max Monolith */
	/* NOTE: This machine uses a system board with a SiS chipset and AMIBIOS (08/08/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blue_max_monolith/ft01232.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_blue_max_mean_green_machine_init(const machine_t *model)
{
	/* International Instrumentation Blue Max Mean Green Machine       */
	/* International Instrumentation Blue Max Business Partner DX 4100 */
	/* NOTE: These machines use a system board with a SiS chipset and AMIBIOS (08/08/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/blue_max_mean_green_machine/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* ITI Technologies */
int
machine_at_iti_business_pro_433v_init(const machine_t *model)
{
	/* ITI Business Pro 433V */
	/* NOTE: This machine uses a system board with a SiS chipset and AMIBIOS (08/08/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/iti_business_pro_433v/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* JDR Microdevices */
int
machine_at_jdr_mct_m486vl_init(const machine_t *model)
{
	/* JDR MCT-M486VL-33 */
	/* JDR MCT-M486VL-66 */
	/* NOTE: These machines use an MCT-M486VL system board (manufactured by Modular Circuit Technology) with a UMC */
	/* chipset and AMIBIOS.                                                                                        */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/jdr_mct_m486vl/386--386-4N-D04A.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for UMC chipset until original chipset is added */
	return ret;
}

/* Jet Research (LOCAL RETAILER) */
int
machine_at_jet_algo_486dx2_66_init(const machine_t *model)
{
	/* Jet Research Jet Algo 486DX2/66 Local Bus System */
	/* NOTE: This is a machine from Los Angeles-based retailer Jet Research, reviewed by PC World in October 1993 */
	/*       for their November 1993 issue. The  machine has 6 ISA slots and 2 VL-Bus slots and supports up to a  */
	/*       maximum of 1024 KB cache memory with 256 KB being the default that this system shipped with.         */
	/*                                                                                                            */
	/*       According to the same PC World article, this machine supported up to a maximum of 32 MB of RAM,      */
	/*       however, the closest matching system board that we were able to find specifications for, the Young   */
	/*       Micro Systems VEGA 486F-2VL, supports up to a maximum of 64 MB. The same system board also uses a    */
	/*       Symphony 82C461 chipset, which was manufactured by Symphony Labs (later known as SiS, or Silicon     */
	/*       Integrated Systems), and which is very likely to be largely equivalent to a SiS 461 chipset.         */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/jet_algo_486dx2_66/486-Peacock PCK486DX.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Keydata International */
int
machine_at_keydata_key486s_25_isa_init(const machine_t *model)
{
	/* Keydata KEY486S-25 ISA */
	/* Keydata  KEY486-33 ISA */
	/* NOTE: These machines use an Asus system board with a SiS chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/keydata_key486s_25_isa/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_keydata_key486sx_25_init(const machine_t *model)
{
	/* Keydata KEY486SX-25  */
	/* Keydata KEY486DX-25  */
	/* Keydata KEY486DX-33  */
	/* Keydata KEY486DX2-50 */
	/* NOTE: This machine uses a Chicony system board with a SiS chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/keydata_key486sx_25/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_keydata_486sx_25_keystation_init(const machine_t *model)
{
	/* Keydata 486SX/25 KeyStation */
	/* NOTE: This machine uses a Silicon Star system board. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/keydata_486sx_25_keystation/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device); */
	return ret;
}

/* Leading Edge */
int
machine_at_leading_edge_d4_dx2_50_init(const machine_t *model)
{
	/* Leading Edge D4/DX2-50 */
	/* NOTE: This machine uses a Daewoo system board with an OPTi chipset and a Phoenix ROM BIOS */
	/* NOTE 2: The closest matching Phoenix ROM BIOS is used until an original BIOS dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/leading_edge_d4_dx2_50/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_leading_edge_fortiva_4000_init(const machine_t *model)
{
	/* Daewoo AL486V-D           */
	/* Leading Edge Fortiva 4000 */
	/* NOTE: These machiens use a Daewoo AL486V-D system board with an ALi 1429 chipset and AMIBIOS (08/08/1993). */
	int ret;
	ret = bios_load_linear(L"roms/machines/leading_edge_fortiva_4000/AL486V-D v299.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ali1429_common_init(model);
	return ret;
}

/* Lightning Computers */
int
machine_at_lightning_omniflex_486sx25_init(const machine_t *model)
{
	/* Lightning Omniflex 486SX25  */
	/* Lightning Omniflex 486DX25  */
	/* Lightning Omniflex 486DX33  */
	/* Lightning Omniflex 486DX50  */
	/* Lightning Omniflex 486DX250 */
	/* Lightning Omniflex 486DX266 */
	/* NOTE: These machines use an AMI HyQuest system board with AMI, Chips and Technologies, and Siemens chipsets */
	/*       and AMIBIOS (12/12/1991).                                                                             */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/lightning_omniflex_486sx25/amibios-31-0101-009999-00101111-121291-MXIC.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_lightning_thunderbox_init(const machine_t *model)
{
	/* Lightning ThunderBox */
	/* NOTE: This machine uses a Micronics system board with a Micronics or Chips and Technologies chipset */
	/*       chipset and Phoenix ROM BIOS (1.01).                                                          */
	/* NOTE 2: The closest matching Phoenix ROM BIOS is used until an original BIOS dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/lightning_thunderbox/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	/* machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device); */
	return ret;
}

/* LodeStar Computer */
int
machine_at_lodestar_486dlc_33_init(const machine_t *model)
{
	/* LodeStar 486DLC-33 */
	/* NOTE: This machine uses a J-Mark system board with an OPTi chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS (07/07/1991) version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/lodestar_486dlc_33/3opm001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Logisys */
int
machine_at_logisys_l_windows_486dx_33_init(const machine_t *model)
{
	/* Logisys L-Windows 486DX/33 */
	/* NOTE: This machine uses an Abit system board witha Unichip chipset and AMIBIOS. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/logisys_l_windows_486dx_33/3ucm002.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Lowland Electronics */
int
machine_at_lowland_486dx4_100_init(const machine_t *model)
{
	/* Lowland 486DX4-100 */
	/* NOTE: This machine uses a system board with a SiS chipset and AMIBIOS (12/15/1993 or 07/25/1994). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/lowland_486dx4_100/486-SiS_AC0360136.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Magic Box */
/* See CompuTrend (CompuTrend 486) */

/* Matrix Digital Products */
int
machine_at_matrix_486_50_dx2_init(const machine_t *model)
{
	/* Matrix 486-50 DX2 */
	/* NOTE: This machine uses a Micronics system board with Micronics and Chips and Technologies chipsets */
	/*       and Phoenix ROM BIOS.                                                                         */
	/* NOTE 2: The closest matching Phoenix ROM BIOS version is used until an original BIOS dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/matrix_486_50_dx2/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	/* machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device); */
	return ret;
}

int
machine_at_matrix_energy_pro_486_init(const machine_t *model)
{
	/* Matrix Energy Pro 486 */
	/* NOTE: This machine uses a BCM system board with a SiS chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/matrix_energy_pro_486/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_eisa_test_init(const machine_t *model)
{
	/* EISA TEST MACHINE */
	int ret;
	ret = bios_load_linear(L"roms/machines/eisa_test/4siw002.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Maximus Computers */
int
machine_at_maximus_medianote_init(const machine_t *model)
{
	/* Maximus MediaNote */
	/* NOTE: This machine was manufactured by Sunrex and uses a system board with an OPTi chipset and AMIBIOS (1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/maximus_medianote/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Mega Computer Systems */
int
machine_at_mega_impact_486sx_25p_init(const machine_t *model)
{
	/* Mega Impact 486SX/25+ */
	/* NOTE: This machine uses a BCM system board with a SiS chipset and AMIBIOS (12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/mega_impact_486sx_25p/3sim001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
	/* machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret; */
}

int
machine_at_mega_r486_33_mpc_init(const machine_t *model)
{
	/* Mega R486/33-MPC */
	/* NOTE: This machine uses an Intel Classic R system board with a VLSI chipset and Phoenix ROM BIOS (1.00.02.AC0). */
	int ret;
	ret = bios_load_linear(L"roms/machines/mega_r486_33_mpc/OLDBIOS.BIN",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_mega_eco486dx2_66dp_init(const machine_t *model)
{
	/* Mega ECO486DX2/66D+ */
	/* NOTE: This machine uses a BCM system board with a SiS chipset and AMIBIOS (08/08/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/mega_eco486dx2_66dp/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_mega_impact_486dx4_100dp_init(const machine_t *model)
{
	/* Mega Impact 486DX/100D+ */
	/* NOTE: This machine uses a KeyTech system board with a SiS chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/mega_impact_486dx4_100dp/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Micro Express */
int
machine_at_microflex_me486_init(const machine_t *model)
{
	/* Micro Express ME 486-50/DX2 */
	/* NOTE: This machine uses a Micronics system board with a Micronics chipset and a Phoenix ROM BIOS */
	/* NOTE 2: The closest matching Phoenix ROM BIOS is used until an original BIOS dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/microflex_me486/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	/* machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device); */
	return ret;
}

int
machine_at_microflex_me486_vl_init(const machine_t *model)
{
	/* Micro Express ME 486SX/Local Bus/25   */
	/* Micro Express ME 486-Local Bus/DX2-50 */
	/* Micro Express ME 486-Local Bus/DX2/66 */
	/* NOTE: These machines use an Ergon system board with an OPTi chipset and a Phoenix ROM BIOS */
	/* NOTE 2: The closest matching Phoenix ROM BIOS is used until an original BIOS dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/microflex_me486/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device); */
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_microflex_init(const machine_t *model)
{
	/* Micro Express MicroFLEX 386/DX/33  */
	/* Micro Express MicroFLEX 386/DX/40  */
	/* Micro Express MicroFLEX 486/SX/25  */
	/* Micro Express MicroFLEX 486/DX/25  */
	/* Micro Express MicroFLEX 486/DX/33  */
	/* Micro Express MicroFLEX 486/DX2/50 */
	/* Micro Express MicroFLEX 486/DX2/66 */
	/* NOTE: These machines use a system board with SiS and Forex chipsets and AMIBIOS (12/12/1991). */
	int ret;
	ret = bios_load_linear(L"roms/machines/microflex/forex386.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model); /*Substituting for Forex chipset until documention becomes available*/
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_microflex_vl_66_multimedia_init(const machine_t *model)
{
	/* Micro Express MicroFlex-VL/Multimedia */
	/* Micro Express MicroFlex-VL/66         */
	/* NOTE: These machines use a system board with a Forex chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/microflex_vl_66/3fom001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model); /*Substituting for Forex chipset until documention becomes available*/
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_microflex_vl_66g_init(const machine_t *model)
{
	/* Micro Express MicroFlex-VL/66  */
	/* Micro Express MicroFlex-VL/66G */
	/* NOTE: These maches use a system board with a SiS chipset and AMIBIOS (4/9/1993) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/microflex_vl_66g/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_microflex_vl_80_init(const machine_t *model)
{
	/* Micro Express MicroFlex-VL/80 */
	/* Micro Express MicroFlex-VL/D6 */
	/* NOTE: These maches appear to use a system board with a SiS chipset and AMIBIOS (7/251994)  */
	/* NOTE 2: The component listing in PC World appears to have mis-identified the BIOS as being */
	/*         an Award BIOS, however, the AMIBIOS is the only BIOS manufacturer known to have    */
	/*         used a 07/25/94 BIOS date.                                                         */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/microflex_vl_80/4sim001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_micro_express_nb8266_init(const machine_t *model)
{
	/* Micro Express NB8266M */
	/* Micro Express NB8266  */
	/* NOTE: These portable machines were manufactured by Nan Tan Computer and use a system board with an ETEQ chipset   */
	/*       and Award BIOS (11/22/1989 for the first system and 3.20-00kT for the second system).                       */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/micro_express_nb8266/lion3500.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_micro_express_nb9266_init(const machine_t *model)
{
	/* Micro Express NB9266  */
	/* Micro Express NP92DX4 */
	/* NOTE: These portable machines were manufactured by Nan Tan Computer and use a system board with a SiS chipset and */
	/*       Award BIOS (09/06/1994 for the first system and 12/16/1994 for the second system).                          */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/micro_express_nb9266/7500d_rev26_121593.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Micro Generation */
int
machine_at_micro_generation_mg50dx2_init(const machine_t *model)
{
	/* Micro Generation MG50DX2 */
	/* Micro Generation LB-25SX */
	/* NOTE: These machines use a system board with an OPTi chipset and AMIBIOS (06/06/1991), with the first machine's  */
	/*       system board being manufactured by Continental and the second machine's system board being manufactured by */
	/*       High Candor.                                                                                               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/micro_generation_mg50dx2/486-920087335.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Micro Telesis */
int
machine_at_micro_telesis_486_33_init(const machine_t *model)
{
	/* Micro Telesis 486/33 */
	/* NOTE: This machine uses uses an SIC Research system board which uses discrete logic chips in place of an actual */
	/*       chipset and which uses the 04/09/1990 version of AMIBIOS.                                                 */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/micro_telesis_486_33/386-702430d-ROM0.BIN",
	L"roms/machines/micro_telesis_486_33/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/micro_telesis_486_33/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Micron Electronics */
int
machine_at_micron_466vl_magnum_mpc_init(const machine_t *model)
{
	/* Micron 466VL Magnum MPC */
	/* Micron 466VL Magnum CD  */
	/* Micron 486VL WinStation */
	/* Micron 486DX4 (VLB)     */
	/* NOTE: These machines use a Micronics JX30GC system board with a SiS-manufactured Micronics chipset and Phoenix   */
	/*       ROM BIOS (JX30-05 for the first system, 1.01 for the second system, MJX30G-04 for the third system, and    */
	/*       JX30GC P01 for the fourth system).                                                                         */
	/* NOTE 2: The available JX30 BIOS files are in a non-extractable format that will only work when a flash device is */
	/*         present and for this reason the closest matching Phoenix ROM BIOS version is used until an original dump */
	/*         is available and/or until support is added for the system board's flash device.                          */
	int ret;
	ret = bios_load_linear(L"roms/machines/micron_466vl_magnum_mpc/lx-03.64",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* MicroSource */
int
machine_at_microsource_486vlb_66_init(const machine_t *model)
{
	/* MicroSource Tempest 486VLB-66 */
	/* NOTE: This machine uses a Pine Technology PT-428 system board with a UMC chipset and AMIBIOS. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/microsource_tempest_486vlb_66/um486v.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

/* MicroTech Computer Corporation */
int
machine_at_microtech_ultima_xvc_66_init(const machine_t *model)
{
	/* MicroTech Ultima XVC/66 */
	/* NOTE: This machine uses a Micronics system board with a SiS-manufactured Micronics chipset and Phoenix ROM BIOS  */
	/*       (0.1).                                                                                                     */
	/* NOTE 2: The available JX30 BIOS files are in a non-extractable format that will only work when a flash device is */
	/*         present and for this reason the closest matching Phoenix ROM BIOS version is used until an original dump */
	/*         is available and/or until support is added for the system board's flash device.                          */
	int ret;
	ret = bios_load_linear(L"roms/machines/microtech_ultima_xvc_66/lx-03.64",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* MicroWarehouse */
/* See CyberMax, Computer Sales Professional, or Quantex */

/* Milkyway Computer Products */
int
machine_at_milkyway_myriadbook_466_init(const machine_t *model)
{
	/* Milkyway MyriadBook/466 */
	/* NOTE: This portable machine was manufactured by Nan Tan Computer and use a system board with a SiS chipset and */
	/*       Award BIOS (09/06/1994).                                                                                 */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/milkyway_myriadbook_466/7500d_rev26_121593.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* MIS Computer Systems */
int
machine_at_mis_m466t_init(const machine_t *model)
{
	/* MIS M466T */
	/* NOTE: This system uses a Micronics EISA 3 VL-bus system board with EISA bus support and Phoenix BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/mis_m466t/e3vl02.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

int
machine_at_mis_multimedia_dx4_100_init(const machine_t *model)
{
	/* MIS Multimedia DX4-100 */
	/* NOTE: This machine uses a Micronics system board with a SiS-manufactured Micronics chipset and Phoenix ROM BIOS */
	/*       Plus.                                                                                                     */
	/* NOTE 2: The LPX30 or LPX30WB BIOS is used until an original BIOS dump is available */
	int ret;
	/* ret = bios_load_linear(L"roms/machines/mis_multimedia_dx4_100/LPX-03.BIN",
	0x000e0000, 131072, 0); */
	ret = bios_load_linear(L"roms/machines/mis_multimedia_dx4_100/lx-03.64",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* MiTAC */
int
machine_at_american_mitac_486_init(const machine_t *model)
{
	/* American Mitac D4033 */
	/* MiTAC D4125          */
	/* NOTE: These machines use an Agatech system board with a Contaq chipset and AMIBIOS (12/12/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/agatech_aga_dx33/486-Contaq.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* MITS Systems (Telemart) */
int
machine_at_mits_hsy_88_486dx_50_init(const machine_t *model)
{
	/* MITS HSY-88-486DX-50 */
	/* NOTE: This machine uses a system board with an OPTi chipset and AMIBIOS (06/06/1992). /
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/mits_hsy_88_486dx_50/opt495sx.ami",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Mitsuba */
int
machine_at_mitsuba_pro_upgradable_init(const machine_t *model)
{
	/* Mitsuba Professional Upgradable */
	/* NOTE: This machine uses a TMC (Taiwan-MyComp) PUMA system board with an OPTi chipset and AMIBIOS (12/12/1991). */
	int ret;
	ret = bios_load_linear(L"roms/machines/mitsuba_pro_upgradable/PUMA200.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_mitsuba_pro_upgradable_4sx_init(const machine_t *model)
{
	/* Mitsuba Pro Upgradable4SX/25 */
	/* NOTE: This machine uses a system board with an SiS chipset and AMIBIOS (12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/mitsuba_pro_upgradable_4sx_25/3sim001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
	/* machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret; */
}

int
machine_at_mitsuba_multi_pro_486dx_33_init(const machine_t *model)
{
	/* Mitsuba Multi-Pro 486DX/33 */
	/* Mitsuba VESA-DX4           */
	/* NOTE: These machines use a system board with a SiS chipset and AMIBIOS (06/06/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/mitsuba_multi_pro_486dx_33/ft01232.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_mitsuba_mit486_green_pc_init(const machine_t *model)
{
	/* Mitsuba MIT486 Green PC */
	/* NOTE: This machine uses a system board with a SiS chipset and AMIBIOS (11/11/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/mitsuba_mit486_green_pc/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Motherboard Discount Center */
int
machine_at_motherboard_shuttle_init(const machine_t *model)
{
	/* Motherboard Discount Center Shuttle 486DX2-80 */
	/* NOTE: This machine uses a shuttle system board with an OPTi 895 (Python) chipste and AMIBIOS (12/15/1993, 07/25/ */
	/*       1994, or 10/10/1994).                                                                                      */
	/* NOTE 2: The closest AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/motherboard_discount_center_shuttle_486dx2_80/486-V4P895P3-SMT.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* MPC Technologies */
int
machine_at_mpc_cd_book_init(const machine_t *model)
{
	/* MPC CD-Book */
	/* NOTE: This portable machine was manufactured by Sunrex and uses a system board with an OPTi chipset and AMIBIOS */
	/*       (10/05/1994 for 75 MHz models and 02/23/1995 for 100 MHz models).                                         */
	/* NOTE 2: The closest AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/mpc_cd_book/486-V4P895P3-SMT.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* MS Engineering */
int
machine_at_mse_486eisa_50mhz_init(const machine_t *model)
{
	/* MSE 486EISA-50MHz */
	/* NOTE: This machine uses an Asus system board with a SiS chipset and Award BIOS (1.0). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/mse_486eisa_50mhz/4siw002.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_mse486dx2_66v_init(const machine_t *model)
{
	/* MSE486DX-33V  */
	/* MSE486DX2-50V */
	/* MSE486DX2-66V */
	/* NOTE: These machines use a Micronics system board with a SiS-manufactured Micronics chipset and Phoenix ROM BIOS*/
	/*       (04/19/1993).                                                                                             */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/mse486dx2_66v/G22-2LB.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* MultiMicro */
int
machine_at_multimicro_mmi_3364t_init(const machine_t *model)
{
	/* MultiMicro MMI-3364T */
	/* NOTE: This machine uses a Technology Power system board which uses discrete logic chips in place of an actual */
	/*       chipset and which uses the 12/15/1989 version of AMIBIOS.                                               */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/multimicro_mmi_3364t/286-vlsi-002350-041_32k.bin",
		L"roms/machines/multimicro_mmi_3364t/286-vlsi-002350-042_32k.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Myoda */
int
machine_at_myoda_486sx_25b_init(const machine_t *model)
{
	/* Myoda 486SX-25b */
	/* NOTE: This machine uses a J-Bond Computer system board with an ETEQ chipset and AMIBIOS (07/07/1991). */
	int ret;
	ret = bios_load_linear(L"roms/machines/myoda_486sx_25b/ami_j-bond_a433c-c.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Myoda Computer Center */
/* See Computer Square */

/* Myoda Computer Square */
/* See Computer Square */

/* Naga Systems */
int
machine_at_naga_windows_workstation_init(const machine_t *model)
{
	/* Naga Windows Workstation */
	/* NOTE: This machine uses a Asus system board with a SiS chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/naga_windows_workstation/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* National MicroComputers */
int
machine_at_nmc_universal_pro_system_init(const machine_t *model)
{
	/* NMC Universal Pro System */
	/* NOTE: This machine uses an ECS system board with a UMC chipset and AMIBIOS (03/25/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/nmc_universal_pro_system/um486v.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

int
machine_at_nmc_universal_pro_system_466_init(const machine_t *model)
{
	/* NMC Universal Pro-System 466 */
	/* NOTE: This machine uses an ECS system board with a UMC chipset and AMIBIOS (04/04/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/nmc_universal_pro_system_466/3umm005.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

/* National MicroSystems */
int
machine_at_national_micro_flash_486_50_init(const machine_t *model)
{
	/* National MicroSystems Flash 486-50 */
	/* NOTE: This machine uses uses an AIR system board with a Chips and Technologies chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/national_microsystems_flash_486_50/3ctm001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

int
machine_at_national_micro_486dx2_50_lb_init(const machine_t *model)
{
	/* National MicroSystems Flash 486DX2-50 */
	/* NOTE: This machine uses an AIR system board with a UMC chipset and AMIBIOS (12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/national_microsystems_flash_486dx2_50_lb/fx-3000-bios.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

int
machine_at_national_micro_486dx_33mpc_init(const machine_t *model)
{
	/* National MicroComputers Flash 486DX-33MPC */
	/* NOTE: This machine uses a Tyan system board with a SiS chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/national_microcomputers_flash_486dx_33mpc/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* NCC Computer Systems */
int
machine_at_ncc_impact_v_init(const machine_t *model)
{
	/* NCC Impact V */
	/* NOTE: This machine uses a Vega system board with a Symphony chipset and AMIBIOS (AMI 1.1). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/ncc_impact_v/386-386 SC Syphony.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* NCR (National Cash Register) */
int
machine_at_ncr_3333_init(const machine_t *model)
{
	/* NCR System 3000 Model 3333 */
	int ret;
	ret = bios_load_linear(L"roms/machines/ncr_3333/BIOS.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device); /* Substituting for UMC chipset until correct chipset is added */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* NEC Technologies */
int
machine_at_nec_image_425_433_466_init(const machine_t *model)
{
	/* NEC Image 425       */
	/* NEC Image 433       */
	/* NEC Image 466       */
	/* NEC Image 466es     */
	/* NEC Image 4100es    */
	/* NEC PowerMate 466D  */
	/* NEC PowerMate 4100M */
	int ret;
	ret = bios_load_linear(L"roms/machines/nec_image_425_433_466/01_00_43.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* NETiS */
int
machine_at_netis_isa_425sx_init(const machine_t *model)
{
	/* NETiS ISA 425SX */
	/* NOTE: These machines use a Freetech system board with an OPTi chipset and AMIBIOS (06/06/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/netis_isa_425sx/486-920087335.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_netis_ultra_winstation_init(const machine_t *model)
{
	/* NETiS Ultra WinStation N433L */
	/* NETiS Ultra WinStation N466L */
	/* NOTE: These machines use a system board with a Unichip chipset and AMIBIOS (12/12/1991). */
	/* NTOE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/netis_ultra_winstation/3ucm004.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_netis_n4d266vl_init(const machine_t *model)
{
	/* NETiS N425VL                 */
	/* NETiS N4D266VL               */
	/* NETiS N 466 VL Power Station */
	/* NOTE: These systems use a Free Technology system board with a SiS chipset and AMIBIOS (6/6/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/netis_n4d266vl/ft01232.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_netis_486_vesa_green_machine_init(const machine_t *model)
{
	/* NETiS 486 VESA Green Machine */
	/* NOTE: These systems use a Free Technology system board with a SiS chipset and AMIBIOS (08/08/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/netis_486_vesa_green_machine/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Northgate */
int
machine_at_northgate_486e_init(const machine_t *model)
{
	/* Northgate 486e */
	/* NOTE: This system uses a TMC PET48PN system board */
	/* NOTE 2: The closest matching AMIBIOS 6/6/1992 version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/northgate_486e/OPT495SX.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_northgate_486zxp_init(const machine_t *model)
{
	/* Northgate Elegance ZXP */
	/* NOTE: This system uses a Mylex MSI486 system board with an OPTi 495 chipset */
	/* NOTE 2: These systems uses a Mylex BIOS */
	/* NOTE 3: The closest matching BIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/northgate_486zxp/MSI627.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_northgate_486szxp_init(const machine_t *model)
{
	/* Northgate SlimLine ZXP */
	/* NOTE: This system uses a Mylex MSL486 system board with a Headland chipset */
	/* NOTE 2: These systems uses a Mylex BIOS */
	/* NOTE 3: The closest matching BIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/northgate_486zxp/MSL.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	machine_at_headland1_common_init(1);
	return ret;
}

int
machine_at_northgate_superb_init(const machine_t *model)
{
	/* Northgate Superb */
	/* NOTE: This system uses a system board with a VIA chipset and AMIBIOS (11/5/1992) */
	/* NOTE 2: The closest matching BIOS version is used until an original dump becomes available   */
	int ret;
	ret = bios_load_linear(L"roms/machines/northgate_superb/486-4386-VC.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ali1429_common_init(model); /* Substituting for VIA chipset until documents are available */
	return ret;
}

int
machine_at_northgate_486vl_init(const machine_t *model)
{
	/* Northgate 486VL */
	/* NOTE: This system uses a Northgate system board with an OPTi 495 chipset */
	/* NOTE 2: The closest matching AMIBIOS 6/6/1992 version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/northgate_486vl/OPT495SX.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_northgate_zxp_eisa_vesa_init(const machine_t *model)
{
	/* Northgate ZXP EISA VESA */
	/* NOTE: This machine uses a Northgate system board with a SiS chipset and AMIBIOS (6/6/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/northgate_zxp_eisa_vesa/ft01232.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_novacor_novas_486sx_20_init(const machine_t *model)
{
	/* NOTE: This machine uses a system board with an OPTi chipset and Microid Research BIOS (1.11). */
	/* NOTE 2: The closest matching Microid Research BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/novacor_novas_486sx_20/opt495sx.mr",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

int
machine_at_novacor_novas_486_dx2_50_init(const machine_t *model)
{
	/* Novacor Novas OPTimum 486 DX2-50 */
	/* NOTE: This machine uses a system board with an OPTi chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS (07/07/1991) version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/novacor_novas_optimum_486dx2_50/3opm001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Occidental Systems */
int
machine_at_occidental_init(const machine_t *model)
{
	/* Occidental 25MHz 486SX  */
	/* Occidental 33MHz 486SX  */
	/* Occidental 25MHz 486DX  */
	/* Occidental 33MHz 486DX  */
	/* Occidental 50MHz 486DX2 */
	/* Occidental 66MHz 486DX2 */
	/* NOTE: This machine uses a ZEOS The Duck system board with a VLSI chipset and Phoenix BIOS. */
	int ret;
	ret = bios_load_linear(L"roms/machines/occidental/ODUCK.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Osicom Technologies */
int
machine_at_osicom_i466_mod_420_init(const machine_t *model)
{
	/* Osicom i466 MOD 420 */
	/* NOTE: This machine uses a system board with an OPTi chipset and AMIBIOS (06/06/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/osicom_i466_mod_420/486-920087335.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Pacific Coast Micro */
int
machine_at_pacific_intel_486_vlb_init(const machine_t *model)
{
	/* Pacific Coast Micro Intel 486 VLB */
	/* NOTE: This machine appears to use a system board with a SiS 471 chipset and Award BIOS (4.50G) */
	/* NOTE 2: The closest matching Award ROM BIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/pacific_coast_micro_intel_486_vlb/SV2G0304.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_2ch_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Packard Bell */
int
machine_at_pb410a_init(const machine_t *model)
{
	/* Packard Bell 486DX/33           */
	/* Packard Bell Legend 760 Supreme */
	/* Packard Bell Legend 790 Supreme */
	int ret;
	ret = bios_load_linear(L"roms/machines/pb410a/pb410a.080337.4abf.u25.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ibm_common_ide_init(model);
	device_add(&keyboard_ps2_device);
	device_add(&acc3221_device);
	device_add(&acc2168_device);
	if (gfxcard == VID_INTERNAL)
		device_add(&ht216_32_pb410a_device);
	return ret;
}

int
machine_at_pb450_init(const machine_t *model)
{
	/* Packard Bell Accel 1728D                  */
	/* Packard Bell Accel 66 Multimedia          */
	/* Packard Bell CD TV                        */
	/* Packard Bell Executive 1707D              */
	/* Packard Bell Legend     10CD              */
	/* Packard Bell Legend     18CD              */
	/* Packard Bell Legend     20CD              */
	/* Packard Bell Legend    140CD              */
	/* Packard Bell 486DX2/66 Multimedia System  */
	/* Packard Bell Pack-Mate 28 Plus            */
	/* Packard Bell Pro 66TV Multimedia Computer */
	/* Packard Bell Spectria 9012                */
	/* NOTE: These machines use a Packard Bell PB450 system board with an OPTi Python chipset and Phoenix BIOS (06/23*/
	/*       /1994).                                                                                                 */
	int ret;
	ret = bios_load_linear(L"roms/machines/pb450/OLDBIOS.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Panther Systems */
int
machine_at_panther_486_33_init(const machine_t *model)
{
	/* GoldStar GS433 */
	/* NOTE: This machine uses a system board with an OPTi chipset and Award BIOS (3.10). */
	/* NOTE 2: The closest matching Quadtel BIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/panther_486_33/286_LO.BIN",
		L"roms/machines/panther_486_33/286_HI.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* PC Brand */
/* See Tandon */

/* PC Craft */
int
machine_at_pc_craft_2401_33_init(const machine_t *model)
{
	/* PC Craft 2401/33 */
	/* NOTE: This machine uses a system board with a Chips and Technologies chipset and AMIBIOS (May 1990). */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/pc_craft_2401_33/386-702430d-ROM0.BIN",
	L"roms/machines/pc_craft_2401_33/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/pc_craft_2401_33/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* machine_at_scat486_init(model, 1); */
	return ret;
}

/* PC Enterprises (LOCAL RETAILER) */
int
machine_at_pc_enterprises_486_vesa_init(const machine_t *model)
{
	/* PC Enterprises 486 VESA */
	/* NOTE: This machine uses a Typhoon system board (functionally equivalent to a Gemlight GMB-486UNP or Dataexpert */
	/*       4407WB v1.1) with a Unichip chipset and AMIBIOS (06/06/1992).                                            */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/pc_enterprises_486_vesa/3ucm002.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* PC Express */
int
machine_at_pc_express_exp66_100_init(const machine_t *model)
{
	/* PC Express EXP66                    */
	/* PC Express EXP100                   */
	/* PC Express Family Multimedia System */
	/* NOTE: These machines use a system board (Firenze for the first system and Asus VL/I-486SV2GX4 for the second */
	/*       and third systems) with a SiS 471 chipset and Award BIOS (4.50G) (4.50G/04/26/1994 for the second and  */
	/*       third systems).                                                                                        */
	/* NOTE 2: The second system's ROM BIOS is used for the first system until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/pc_express_exp66_100/SV2G0304.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_2ch_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* PC Positive */
/* See Tandon */

/* PCI Systems */
int
machine_at_pci_486_50c128_init(const machine_t *model)
{
	/* PCI 486-50C128 */
	/* NOTE: This machine uses an Ideal system board with a Contaq chipset and AMIBIOS (05/05/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/pci_486_50c128/486-Contaq.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Peregrine */
int
machine_at_peregrine_486_33_flyer_init(const machine_t *model)
{
	/* Peregrine 486/33 Flyer */
	/* NOTE: This machine uses uses an AMI system board which uses discrete logic chips in place of an actual chipset and*/
	/*       which uses the 04/09/1990 version of AMIBIOS.                                                               */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/peregrine_486_33_flyer/386-702430d-ROM0.BIN",
	L"roms/machines/peregrine_486_33_flyer/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/peregrine_486_33_flyer/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Polywell */
int
machine_at_polywell_poly_486ev_init(const machine_t *model)
{
	/* Polywell Poly 486EV    */
	/* Polywell Poly 486-66EV */
	/* NOTE: These machines use an AIR system board with a SiS chipset and AMIBIOS (6/6/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/poly_486ev/ft01232.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* PowerBox */
int
machine_at_powerbox_pbs1_340i_init(const machine_t *model)
{
	/* PowerBox PBS1-340i */
	/* NOTE: This machine uses a system board with a VLSI chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/powerbox_pbs1_340i/2vlm001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	/* device_add(&vlsi_scamp_device); */
	return ret;
}

/* Premio (formerly CompuTrend) */
/* See CompuTrend */

/* Professional Computer Systems */
int
machine_at_pcs_double_pro_66_init(const machine_t *model)
{
	/* PCS Double Pro-66 */
	/* NOTE: This machine uses an AMI (American Megatrends) 486 Super Voyager system board with an AMI Series 50 chipset */
	/*       and AMIBIOS (12/12/1991).                                                                                   */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/pcs_double_pro_66/s69b2p.rom",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Professional Technologies */
int
machine_at_professional_486_init(const machine_t *model)
{
	/* Professional EXEC 486-33 */
	/* Professional ISA         */
	/* Professional VESA-1      */
	/* Professional VESA-2      */
	/* Professional VESA-3      */
	/* NOTE: The first system uses a 486 socket system board with a SiS chipset and AMIBIOS (07/07/1991). The   */
	/*       remaining machines will be configured to use the same BIOS until a copy is found that is closer    */
	/*       to the original.                                                                                   */
	/*                                                                                                          */
	/*       The ROM BIOS that the emulator is using was re-constructed by taking an AMIBIOS 07/07/1991 version */
	/*       that was intended for a 386 SiS chipset board, and editing the on-screen BIOS ID inside the BIOS   */
	/*       file using a hex editor to match that of the original.                                             */
	/*                                                                                                          */
	/*       The original BIOS ID is as follows: 30-0200-D01128-00101111-070791-SIS486-F                        */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/professional_486/3sim001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* QSI */
int
machine_at_qsi_klonimus_486_init(const machine_t *model)
{
	/* QSI Klonimus 486/SX25  */
	/* QSI Klonimus 486/33    */
	/* QSI Klonimus 486DX2/66 */
	/* NOTE: These machines use an AIM system board with a Contaq chipset and AMIBIOS (12/12/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/qsi_klonimus_486/486-Contaq.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Quantex (formerly Computer Sales Professional) */
int
machine_at_csp_ftn486_init(const machine_t *model)
{
	/* Computer Sales Professional Pro 486DX2/50 */
	/* Fountain FTNMT486DX-50C                   */
	/* Fountain FTNMT486DX2-66C                  */
	/* NOTE: These systems were manufactured by Fountain Technologies and use a system board with a Symphony */
	/*       chipset.                                                                                        */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/csp_ftn486/486-Peacock PCK486DX.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

int
machine_at_quantex_q486dx2_66mm_4_init(const machine_t *model)
{
	/* Quantex Q486SX/33VM-1   */
	/* Quantex Q486DX2/50VM-1  */
	/* Quantex Q486DX2/66VM-1  */
	/* Quantex Q486DX4/100VM-1 */
	/* Quantex Q486DX2/50VM-4  */
	/* Quantex Q486DX2/66VM-4  */
	/* Quantex Q486DX4/100VM-4 */
	/* Quantex Q486DX2/33MM-4  */
	/* Quantex Q486DX2/50MM-4  */
	/* Quantex Q486DX2/66MM-4  */
	/* Quantex Q486DX4/100MM-4 */
	/* NOTE: These systems were manufactured by Fountain Technologies and uses a Gigabyte GA-486VT system board with */
	/*       a UMC chipset and AMIBIOS (11/11/1992).                                                                 */
	/* NOTE 2: The closest matching AMIBIOS (11/11/1992) version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/quantex_q486dx2_66mm_4/um486v.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substituting for original chipset until documents are available */
	return ret;
}

/* Quill */
int
machine_at_quill_q_tech_486_init(const machine_t *model)
{
	/* Quill Q-Tech 486SX-25   */
	/* Quill Q-Tech 486DX-25   */
	/* Quill Q-Tech 486DX-50   */
	/* Quill Q-Tech 486DX2-66  */
	/* Quill Q-Tech 486 4D2/66 */
	/* Quill Q-Tech PC-4D33-4  */
	/* NOTE: These systems use a TMC system board with an OPTi chipset and AMIBIOS (6/6/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/quill_q_tech_486/486-920087335.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* SAI Systems Laboraties */
int
machine_at_sai_486_25_init(const machine_t *model)
{
	/* SAI 486/25 */
	/* NOTE: This machine uses an A.I.R. system board with a Chips and Technologies chipset and AMIBIOS (12/15/1989). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/sai_486_25/386-BIG AMI 896818 EVEN.BIN",
		L"roms/machines/sai_486_25/386-BIG AMI 896818 ODD.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_sai_486_33_init(const machine_t *model)
{
	/* SAI 486/25 */
	/* NOTE: This machine uses uses an A.I.R. system board with an Intel chipset and AMIBIOS (May 1990). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/sai_486_33/386-702430d-ROM0.BIN",
	L"roms/machines/sai_486_33/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/sai_486_33/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_sai_386dx_40_init(const machine_t *model)
{
	/* SAI 386DX-40 */
	/* NOTE: This machine uses uses a PC Chips system board with a PC Chips chipset and AMIBIOS. */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/sai_386dx_40/3pcm001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Seanix Technology */
int
machine_at_seanix_asi_9000_486_vl_init(const machine_t *model)
{
	/* Seanix 486DX266/08L */
	/* Seanix 486DX499/16L */
	/* NOTE: These machines use a system board with an OPTi chipset and Microid Research BIOS (1.6). */
	/* NOTE 2: The closest matching Microid Research BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/seanix_asi_9000/opt495sx.mr",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Sho-Tronics Computer */
int
machine_at_sho_tronics_486_init(const machine_t *model)
{
	/* Sho-Tronics Professional Starter System 486SX 25  */
	/* Sho-Tronics Professional Starter System 486DX 33  */
	/* Sho-Tronics Professional Starter System 486DX2 50 */
	/* Sho-Tronics Professional Starter System 486DX2 66 */
	/* Sho-Tronics Power Tech 386DX 40                   */
	/* Sho-Tronics Power Tech 486SX 25                   */
	/* Sho-Tronics Power Tech 486DX 33                   */
	/* Sho-Tronics Power Tech 486DX2 50                  */
	/* Sho-Tronics Super CD System 486SX 25              */
	/* Sho-Tronics Super CD System 486DX2 50             */
	/* NOTE: The first four systems use a system board with a SiS chipset and AMIBIOS. The remaining systems */
	/*       will also redirect to the same system board until the correct board is identified.              */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/sho_tronics_486/3sim001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret; */
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Sidus Systems */
int
machine_at_sidus_sci966dc256dt_init(const machine_t *model)
{
	/* Sidus SCI966DC256DT */
	/* NOTE: This machine uses a Micronics system board with a SiS-manufactured Micronics chipset and Phoenix ROM BIOS  */
	/*       BIOS (0.10).                                                                                               */
	/* NOTE 2: The available JX30 BIOS files are in a non-extractable format that will only work when a flash device is */
	/*         present and for this reason the closest matching Phoenix ROM BIOS version is used until an original dump */
	/*         is available and/or until support is added for the system board's flash device.                          */
	int ret;
	ret = bios_load_linear(L"roms/machines/sidus_sci966dc256dt/lx-03.64",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Sirius Systems Technology */
int
machine_at_sirius_sst_486dx2_66mwc_init(const machine_t *model)
{
	/* Sirius SST 486DX2-66MWC */
	/* NOTE: This machine uses a system board with an OPTi chipset and AMIBIOS (12/12/1991). */
	/* NOTE 2: The closest matching AMIBIOS 12/12/1991 version is used until an original dump becomes available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/sirius_sst_486dx2_66mwc/HAWK.BIO",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Standard Computer Corporation */
int
machine_at_standard_486sx25_init(const machine_t *model)
{
	/* Standard 486SX/25 */
	/* NOTE: This machine uses a system board with a SiS chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/standard_486sx25/3sim001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* SmartWorks */
int
machine_at_smartworks_slimline_66_init(const machine_t *model)
{
	/* SmartWorks Slimline 66 */
	/* NOTE: This machine uses a Micronics MPower4 system board with a SiS-manufactured Micronics chipset and Phoenix */
	/*       ROM BIOS Plus.                                                                                           */
	/* NOTE 2: The LPX30 or LPX30WB BIOS is used until an original BIOS dump is available */
	int ret;
	/* ret = bios_load_linear(L"roms/machines/smartworks_slimline_66/LPX-03.BIN",
	0x000e0000, 131072, 0); */
	ret = bios_load_linear(L"roms/machines/smartworks_slimline_66/lx-03.64",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* SoftWorks Development Corporation */
int
machine_at_softworks_citus_mdc_486_init(const machine_t *model)
{
	/* SoftWorks Citus MDC 486/25    */
	/* SoftWorks Citus MDC 486DX/33  */
	/* SoftWorks Citus MDC 486DX2/50 */
	/* SoftWorks Citus MDC 486DX2/66 */
	/* NOTE: These machines use a system board with a UMC chipset and AMIBIOS (07/07/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/softworks_citus_mdc/486-FX3000.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substitute for UMC chipset */
	return ret;
}

/* SolMicro */
int
machine_at_solmicro_intrepid_466_init(const machine_t *model)
{
	/* SolMicro Intrepid 466 */
	/* NOTE: This machine uses an Asus VL/I-486SV2GX4 system board with a SiS 471 chipset and Award BIOS (02/28/1994) */
	int ret;
	ret = bios_load_linear(L"roms/machines/solmicro_intrepid_466/SV2G0304.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_2ch_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Spear Technology */
int
machine_at_spear_486_isa_convertible_init(const machine_t *model)
{
	/* Spear 486 ISA Convertible */
	/* NOTE: This machine uses a QuickPath system board with an OPTi chipset and Microid Research BIOS. */
	/* NOTE 2: The closest matching Microid Research BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/spear_486_isa_convertible/opt495sx.mr",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Swan */
int
machine_at_swan_486_db_init(const machine_t *model)
{
	/* Swan Direct Bus Line */
	/* Swan 486SX/25DB      */
	/* Swan 486/33DB        */
	/* Swan 486DX2-50DB     */
	/* NOTE: These machines use a Swan system board with a SYSCON chipset and AMIBIOS (September 1989) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/swan_486_db/386-DFI-386-20_Even.BIN",
		L"roms/machines/swan_486_db/386-DFI-386-20_Odd.BIN",
		0x000f0000, 65536, 0x08000);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_swan_486_db2_init(const machine_t *model)
{
	/* Swan 486DX2-66DB */
	/* NOTE: This machine uses a Swan system board with a SYSCON chipset and AMIBIOS (05/05/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/swan_486_db/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Swan Technologies */
int
machine_at_swan_486_direct_bus_init(const machine_t *model)
{
	/* Swan 486 Direct Bus */
	/* NOTE: This machine uses a system board with an OPTi chipset and AMIBIOS (06/06/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/swan_486_direct_bus/OPT495SX.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Systems Integration Associates */
int
machine_at_sia_486_33_init(const machine_t *model)
{
	/* SIA 486/33 */
	/* NOTE: This machine uses uses a system board which uses discrete logic chips in place of an actual chipset and */
	/*       which uses the 04/09/1990 version of AMIBIOS.                                                           */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/sia_486_33/386-702430d-ROM0.BIN",
	L"roms/machines/sia_486_33/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/sia_486_33/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Tagram */
int
machine_at_tagram_thunderbolt_xl_init(const machine_t *model)
{
	/* Tagram Thunderbolt ZR */
	/* Tagram Thunderbolt XL */
	/* NOTE: These machines use a system board with an OPTi chipset and AMIBIOS (08/08/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/tagram_thunderbolt_xl/386-opti-mini.bio",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Tandon */
int
machine_at_micronics386_init(const machine_t *model)
{
	/* Tandon 386/33 */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/micronics386/386-Micronics-09-00021-EVEN.BIN",
		L"roms/machines/micronics386/386-Micronics-09-00021-ODD.BIN",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_init(model);
	device_add(&neat_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_tandon_486_init(const machine_t *model)
{
	/* Tandon MCS Pro 486-33            */
	/* Tandon Option Pro 486 25         */
	/* Tandon Option Pro 486 33         */
	/* Tandon Option Pro 486 66         */
	/* Tandon Option Pro 486 100        */
	/* PC Brand Leader Cache 486/DX2-66 */
	/* PC Brand Leader 486/DLC-33       */
	/* PC Positive 486                  */
	/* PC Positive PC425                */
	/* NOTE: These systems used a system board with a Symphony chipset and Tandon/PC Brand BIOS */
	/* NOTE 2: The Tandon 386 BIOS is used until an original BIOS dump is available */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/tandon_386_486/386-Micronics-09-00021-EVEN.BIN",
		L"roms/machines/tandon_386_486/386-Micronics-09-00021-ODD.BIN",
		0x000f0000, 65536, 0x08000);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Tandy */
int
machine_at_tandy_2500_init(const machine_t *model)
{
	/* Tandy 1000 RSX   */
	/* Tandy 2500 SX/16 */
	/* Tandy 2500 SX/33 */
	/* NOTE: These machines use a system board with a Headland chipset */
	int ret;
	ret = bios_load_linear(L"roms/machines/tandy_2500/TANDY25H.ROM",
		0x000f0000, 131072, 0);
	/* ret = bios_load_linear(L"roms/machines/tandy_2500/TANDY25H.ROM",
	0x000f0000, 65536, 0); */
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	machine_at_headland1_common_init(1);
	return ret;
}

int
machine_at_tandy_486_init(const machine_t *model)
{
	/* Tandy 2100 */
	/* NOTE: This system has a maximum 32 MB of onboard RAM */
	/* NOTE 2: The closest matching BIOS version is used until an original dump becomes available   */
	int ret;
	ret = bios_load_linear(L"roms/machines/tandy_2100/486-Highscreen.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ali1429_common_init(model); /* Substituting for VIA chipset until documents are available */
	return ret;
}

int
machine_at_tandy_sensation_init(const machine_t *model)
{
	/* Tandy 4833 LX/T MPC             */
	/* Tandy 4850 EP MPC               */
	/* Tandy Sensation!                */
	/* Tandy 3100                      */
	/* Tandy Multimedia PC             */
	/* Tandy Sensation! (Sensation II) */
	/* Tandy Multimedia PC 25-1641     */
	/* Tandy 3200                      */
	/* GRiD MFP/420s                   */
	/* GRiD MFP/420                    */
	/* GRiD MFP/425s-II                */
	/* GRiD MFP/433s+ L-Series         */
	/* GRiD MFP/433+  L-Series         */
	/* GRiD MFP/450                    */
	/* GRiD MFP/450+  L-Series         */
	/* GRiD MFP/466+  L-Series         */
	/* NOTE: These machines use a system board with a VLSI chipset and Phoenix ROM BIOS */
	int ret;
	ret = bios_load_linear(L"roms/machines/tandy_sensation/TANDY_SENSATION_2_011004_10051993.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Tangent */
int
machine_at_tangent_model_425s_init(const machine_t *model)
{
	/* Tangent Model 425s */
	/* NOTE: This machine appears to have used a Chaintech system board with a SiS chipset and AMIBIOS */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/tangent_model_425s/3sim001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_tangent_486_init(const machine_t *model)
{
	/* Tangent 486                  */
	/* Tangent Black Box Pro Series */
	/* NOTE: These machines use an MCCI system board with a HiNT chipset and AMIBIOS (7/7/1991).                */
	/*                                                                                                          */
	/*       We have not been able to find a 100% original BIOS for either of these machines, however, since    */
	/*       the first system uses the 7/7/1991 AMIBIOS version, and since the second machine's system board    */
	/*       was also likely to have used an AMIBIOS, a version of the 7/7/1991 AMIBIOS for the ALi 1217        */
	/*       chipset is substituting for the original BIOSes until they become available.                       */
	/* NOTE 2: The closest matching AMIBIOS 7/7/1991 version is used until an original dump becomes available   */
	int ret;
	/* ret = bios_load_linear(L"roms/machines/tangent_486/3alm006.bin",
	0x000f0000, 65536, 0); */
	ret = bios_load_linear(L"roms/machines/tangent_486/ami.bin",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_ali1429_common_init(model);  */ /* Substituting for HiNT chipset until documents are available */
	machine_at_common_ide_init(model); /* Second BIOS only */
	machine_at_headland1_common_init(1); /* Substituting for HiNT chipset until documents are available */
	return ret;
}

int
machine_at_tangent_vl_init(const machine_t *model)
{
	/* Tangent VL Cx486S-40 */
	/* Tangent VL 466       */
	/* NOTE: These machines use a Tyan system board with a SiS chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/tangent_vl/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* TeleVideo Systems */
int
machine_at_televideo_tele386e_init(const machine_t *model)
{
	/* TeleVideo Tele386e */
	/* NOTE: This machine uses uses a system board which uses discrete logic chips in place of an actual chipset and */
	/*       which uses the 04/09/1990 version of AMIBIOS.                                                           */
	/* NOTE 2: The closest matching AMIBIOS 04/09/1990 BIOS version is used until an original dump is available */
	int ret;
	/* ret = bios_load_interleaved(L"roms/machines/televideo_tele386e/386-702430d-ROM0.BIN",
	L"roms/machines/televideo_tele386e/386-702430d-ROM1.BIN",
	0x000f0000, 65536, 0x08000); */
	ret = bios_load_linear(L"roms/machines/televideo_tele386e/BIOS.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Tenex Computer Express */
int
machine_at_tenex_premier_486dx_33_init(const machine_t *model)
{
	/* Tenex Premier 486DX/33 */
	/* NOTE: This machine uses a DTK system board with a Symphony chipset and AMIBIOS (07/07/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/tenex_premier_486dx_33/ami_386_za590821.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_device);
	return ret;
}

/* Throughbred MicroSystems */
int
machine_at_thoroughbred_386_25_init(const machine_t *model)
{
	/* Throughbred 386/25 */
	/* NOTE: This machine uses a DTK system board which uses discrete logic chips in place of an actual chipset and which*/
	/*       uses a DTK BIOS (DTK 4/25) (June 1990).                                                                     */
	/* NOTE 2: The closest matching DTK BIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/thoroughbred_386_25/3cto001.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_init(model);
	device_add(&neat_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Toptek (LOCAL RETAILER) */
int
machine_at_toptek_top486dx2_66_init(const machine_t *model)
{
	/* Toptek Top486DX2/66 */
	/* NOTE: This is a machine from San Francisco-based retailer Toptek, reviewed by PC World in October 1993 for */
	/*       their November 1993 issue. This machine appears to have used an Asus VL/ISA-486SV2 system board with */
	/*       a SiS chipset and AMIBIOS.                                                                           */
	int ret;
	ret = bios_load_linear(L"roms/machines/toptek_top486dx2_66/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Total Peripherals */
int
machine_at_total_peripherals_386dx_40_init(const machine_t *model)
{
	/* Total Peripherals 386DX-40 */
	/* NOTE: This machine uses an Asus ISA-386C system board with a SiS chipset and AMIBIOS (05/05/1991). */
	int ret;
	ret = bios_load_linear(L"roms/machines/total_peripherals_386dx_40/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Touche Micro Technologies */
int
machine_at_touche_486dx2_50_init(const machine_t *model)
{
	/* Touche 486DX/50 */
	/* NOTE: This system uses an AMI system board */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/touche_486dx2_50/HAWK.BIO",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&opti495_device);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_touche_isa_vlb_init(const machine_t *model)
{
	/* Touche ISA VLB */
	/* NOTE: This system uses an American Megatrends (AMI) system board and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/touche_isa_vlb/PX486P3.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model);
	return ret;
}

/* Transource Computers */
int
machine_at_transource_verxion_486_init(const machine_t *model)
{
	/* Transource Verxion 486 */
	/* NOTE: This machine uses an A.I.R. system board which uses discrete logic chips in place of an actual chipset and */
	/*       which uses the 12/15/1989 version of AMIBIOS.                                                              */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_interleaved(L"roms/machines/bus_386_33/286-vlsi-002350-041_32k.bin",
		L"roms/machines/bus_386_33/286-vlsi-002350-042_32k.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Tri-Star */
int
machine_at_tri_star_486_isa_init(const machine_t *model)
{
	/* Tri-Star Tri-Win 486SX/25     */
	/* Tri-Star Tri-WIN 486DX/50 ISA */
	/* NOTE: These machines use a system board with a Contaq chipset and AMIBIOS (07/07/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/tri_star_486_isa/486-Contaq.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Twinhead */
int
machine_at_twinhead_superset_init(const machine_t *model)
{
	/* Twinhead Superset 600/425C */
	/* Twinhead Superset 600/452C */
	/* NOTE: These machines use a system board with an Acer chipset and Award BIOS (3.15). */
	/* NOTE 2: The closest matching Award BIOS version is used until an original dump becomes available   */
	int ret;
	ret = bios_load_linear(L"roms/machines/twinhead_superset/award.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ali1429_common_init(model);
	return ret;
}

/* Ultra Computers */
int
machine_at_ultra_ul486_66_lpc_init(const machine_t *model)
{
	/* Ultra UL486/66-LPC */
	/* NOTE: This machine use a Leadertech Systems system board with a SiS chipset and AMIBIOS (08/08/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/ultra_ul486_66_lpc/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* Unisys */
int
machine_at_unisys_pw2_advantage_4666_init(const machine_t *model)
{
	/* Unisys PW2 Advantage             4333    */
	/* Unisys PW2 Advantage             4666    */
	/* Unisys PW2 Advantage Plus Model  4666    */
	/* Unisys PW2 Advantage Partner ELI 4333    */
	/* Unisys                       ELI 46665   */
	/* Unisys                       CWD 4001-ZE */
	/* NOTE: These machines use an FIC (First International Computer) system board with a VIA chipset and Award BIOS. */
	/* NOTE 2: The Unisys ELI 46665 BIOS is used for the rest of the systems until original dumps are available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/unisys_pw2_advantage_4666/FIC_ELI6.BIO",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_ali1429_common_init(model); /* Substituting for VIA chipset until documents are available */
	return ret;
}

/* United Micro */
int
machine_at_um_galaxy_486vlb_33mm_init(const machine_t *model)
{
	/* United Micro UM Galaxy 486VLB-33MM */
	/* NOTE: This machine uses an Addonics system board with a SiS chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/united_micro_um_galaxy_486vlb_33mm/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* United Solutions */
int
machine_at_usi_green_pc_init(const machine_t *model)
{
	/* United Solutions USI Green PC */
	/* NOTE: This machine use a system board with a SiS chipset and AMIBIOS (11/11/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/united_solutions_usi_green_pc/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* U.S. Micro Express */
int
machine_at_us_micro_jet_486dx2_init(const machine_t *model)
{
	/* U.S. Micro Jet 486DX2-50 */
	/* U.S. Micro Jet 486DX2-66 */
	/* NOTE: These machines use an Asus system board with a SiS chipset and AMIBIOS (05/05/1991). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/us_micro_jet_486dx2/ASUS_ISA-386C_BIOS.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_init(model);
	device_add(&rabbit_device);
	device_add(&keyboard_at_ami_device);
	device_add(&fdc_at_device);
	return ret;
}

/* USA Flex */
int
machine_at_usa_flex_486sx_25_init(const machine_t *model)
{
	/* USA Flex 486SX/25 System */
	/* NOTE: This system use a Cache Computers system board with a UMC chipset and AMIBIOS (07/07/1991) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/usa_flex_486sx_25/486-FX3000.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substitute for UMC chipset */
	return ret;
}

/* Vanvier */
int
machine_at_vanvier_gpc7486_init(const machine_t *model)
{
	/* Vanvier GPC7486 */
	/* NOTE: This machine use a system board with a SiS chipset and AMIBIOS (08/08/1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available. */
	int ret;
	ret = bios_load_linear(L"roms/machines/vanvier_gpc7486/SIS471BE.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* WYSE */
int
machine_at_wyse_decision_486si_init(const machine_t *model)
{
	/* Wyse Decision 486/50 DX2 */
	/* Wyse Decision 486si      */
	/* NOTE: These systems use a WYSE system board with an OPTi chipset and a Phoenix ROM BIOS */
	/* NOTE 2: The closest matching Packard Bell BIOS is used until an original BIOS dump becomes available */
	int ret;
	ret = bios_load_linear(L"roms/machines/pb410a/pb410a.080337.4abf.u25.bin",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	/* machine_at_common_ide_init(model); */
	machine_at_ibm_common_ide_init(model);
	device_add(&keyboard_ps2_device);
	device_add(&acc3221_device);
	device_add(&acc2168_device);
	/* device_add(&opti495_device); */
	/* device_add(&keyboard_at_device); */
	/* device_add(&fdc_at_device); */
	return ret;
}

/* Xinetron */
int
machine_at_xinetron_x_lan_486_init(const machine_t *model)
{
	/* Xinetron X/Lan 486 (DX/33)  */
	/* Xinetron X/Lan 486 (DX2/66) */
	/* Xinetron 486DX2-50          */
	/* NOTE: These machines use a system board with a USA Integration chipset and AMIBIOS (6/6/1992). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/xinetron_x_lan_dx2_66/OPT495SX.AMI",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_opti495_ami_common_init(model); /* Substitute for USA chipset until original is added */
	return ret;
}

int
machine_at_xinetron_x_lan_dx2_66_init(const machine_t *model)
{
	/* Xinetron X/LAN Station DX/33  */
	/* Xinetron X/LAN Station DX2/66 */
	/* NOTE: These systems use a system board with a SiS chipset and AMIBIOS (11/11/1992) */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/xinetron_x_lan_dx2_66/486-ASUS ISA-486SV2.BIN",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}

/* ZEOS */
int
machine_at_zeos_486_mart_07_init(const machine_t *model)
{
	/* ZEOS 486DX2-66 Upgradable */
	/* NOTE: This machine uses a ZEOS Martin system board with a VLSI chipset and Phoenix BIOS (Q3.07) */
	/* NOTE 2: This function is for the 8/2/1993 BIOS version */
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_486_mart-07/BIOS.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_zeos_486_mart_07s_init(const machine_t *model)
{
	/* ZEOS 486DX2-66 Upgradable */
	/* NOTE: This machine uses a ZEOS Martin system board with a VLSI chipset and Phoenix BIOS (Q3.07) */
	/* NOTE 2: This function is for the 8/2/1993 BIOS version with SCSI */
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_486_mart-07s/BIOS.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_zeos_486_mart_10_init(const machine_t *model)
{
	/* ZEOS 486DX2-66 Upgradable */
	/* NOTE: This machine uses a ZEOS Martin system board with a VLSI chipset and Phoenix BIOS (Q3.07) */
	/* NOTE 2: This function is for the 11/11/1993 BIOS version */
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_486_mart-10/BIOS.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_zeos_486_mart_10s_init(const machine_t *model)
{
	/* ZEOS 486DX2-66 Upgradable */
	/* NOTE: This machine uses a ZEOS Martin system board with a VLSI chipset and Phoenix BIOS (Q3.07) */
	/* NOTE 2: This function is for the 11/11/1993 BIOS version with SCSI */
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_486_mart-10s/BIOS.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_zeos_486_mart_11_init(const machine_t *model)
{
	/* ZEOS 486DX2-66 Upgradable */
	/* NOTE: This machine uses a ZEOS Martin system board with a VLSI chipset and Phoenix BIOS (Q3.07) */
	/* NOTE 2: This function is for the 12/31/1993 BIOS version */
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_486_mart-11/BIOS.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_zeos_486_mart_11s_init(const machine_t *model)
{
	/* ZEOS 486DX2-66 Upgradable */
	/* NOTE: This machine uses a ZEOS Martin system board with a VLSI chipset and Phoenix BIOS (Q3.07) */
	/* NOTE 2: This function is for the 12/31/1993 BIOS version with SCSI */
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_486_mart-11s/BIOS.BIN",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_zeos_486_mart_12b_init(const machine_t *model)
{
	/* ZEOS 486DX2-66 Upgradable */
	/* NOTE: This machine uses a ZEOS Martin system board with a VLSI chipset and Phoenix BIOS (Q3.07) */
	/* NOTE 2: This function is for the 3/17/1994 BIOS version */
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_486_mart-12b/NONSCSI.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

int
machine_at_zeos_486_mart_12bs_init(const machine_t *model)
{
	/* ZEOS 486DX2-66 Upgradable */
	/* NOTE: This machine uses a ZEOS Martin system board with a VLSI chipset and Phoenix BIOS (Q3.07) */
	/* NOTE 2: This function is for the 3/17/1994 BIOS version with SCSI */
	int ret;
	ret = bios_load_linear(L"roms/machines/zeos_486_mart-12b/SCSI.ROM",
		0x000e0000, 131072, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_common_ide_init(model);
	/* device_add(&vl82c480_device); */
	device_add(&keyboard_at_device);
	device_add(&fdc_at_device);
	return ret;
}

/* Zodiac Technologies */
/* See FiveStar Computers */

/* ZOOMMAX Computers (LOCAL RETAILER) */
int
machine_at_zoommax_486_dx2_66_mhz_air_init(const machine_t *model)
{
	/* ZOOMMAX 486 DX2-66 MHz (AiR) */
	/* NOTE: This machine uses an A.I.R. 486SH system board with a SiS 461 chipset and AMIBIOS (1993). */
	/* NOTE 2: The closest matching AMIBIOS version is used until an original dump is available */
	int ret;
	ret = bios_load_linear(L"roms/machines/zoommax_486_dx2_66_mhz_air/486-genoa_vlb.bin",
		0x000f0000, 65536, 0);
	if (bios_only || !ret)
		return ret;
	machine_at_sis_85c471_common_init(model);
	device_add(&ide_vlb_device);
	device_add(&keyboard_at_ami_device);
	return ret;
}
