/*
 * 86Box	A hypervisor and IBM PC system emulator that specializes in
 *		running old operating systems and software designed for IBM
 *		PC systems and compatibles from 1981 through fairly recent
 *		system designs based on the PCI bus.
 *
 *		This file is part of the 86Box distribution.
 *
 *		Implementation of the VLSI 82C591/VL82C593 chip.
 *
 *
 *
 * Authors:	Sarah Walker, <http://pcem-emulator.co.uk/>
 *		Miran Grca, <mgrca8@gmail.com>
 *
 *		Copyright 2019 Miran Grca.
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
#include <86box/keyboard.h>
#include <86box/port_92.h>
#include <86box/chipset.h>


typedef struct vl82c590_t
{
    /* VL82C591 */

    /* VL82C593 */

    /* Registers */
    uint8_t pci_conf[2][256];

    /* VL82C591/VL82C593 ISA */
	int cfg_index;
	uint8_t cfg_regs[256];
} vl82c590_t

#define CFG_ID     0x00
#define CFG_AAXS   0x0d
#define CFG_BAXS   0x0e
#define CFG_CAXS   0x0f
#define CFG_DAXS   0x10
#define CFG_EAXS   0x11
#define CFG_FAXS   0x12

#define ID_VL82C590 0x90

static void
shadow_control(uint32_t addr, uint32_t size, int state)
{
	/*      pclog("shadow_control: addr=%08x size=%04x state=%i\n", addr, size, state); */
	switch (state) {
	case 0:
		mem_set_mem_state(addr, size, MEM_READ_EXTANY | MEM_WRITE_EXTANY);
		break;
	case 1:
		mem_set_mem_state(addr, size, MEM_READ_EXTANY | MEM_WRITE_INTERNAL);
		break;
	case 2:
		mem_set_mem_state(addr, size, MEM_READ_INTERNAL | MEM_WRITE_EXTANY);
		break;
	case 3:
		mem_set_mem_state(addr, size, MEM_READ_INTERNAL | MEM_WRITE_INTERNAL);
		break;
	}
	flushmmucache_nopc();
}

static void
vl82c591_write(int func, int addr, uint8_t val, void *priv)
{
	vl82c590_t *dev = (vl82c590_t *) priv;
    if (func)
		return;
    dev->pci_conf[0][addr] = val;
}


static void
vl82c593_write(int func, int addr, uint8_t val, void *priv)
{
    vl82c590_t *dev = (vl82c590_t *) priv;

    if (func > 0)
	return;

    if (addr < 0x41)
	return;

	case 0x41:
		if (val & 0x80)
			pci_set_irq_routing(PCI_INTA, PCI_IRQ_DISABLED);
		else
			pci_set_irq_routing(PCI_INTA, val & 0xf);
		break;
	case 0x42:
		if (val & 0x80)
			pci_set_irq_routing(PCI_INTC, PCI_IRQ_DISABLED);
		else
			pci_set_irq_routing(PCI_INTC, val & 0xf);
		break;
	case 0x43:
		if (val & 0x80)
			pci_set_irq_routing(PCI_INTB, PCI_IRQ_DISABLED);
		else
			pci_set_irq_routing(PCI_INTB, val & 0xf);
		break;
	case 0x44:
		if (val & 0x80)
			pci_set_irq_routing(PCI_INTD, PCI_IRQ_DISABLED);
		else
			pci_set_irq_routing(PCI_INTD, val & 0xf);
		break;
    }

    dev->pci_conf[1][addr] = val;
}


static uint8_t
vl82c591_read(int func, int addr, void *priv)
{
    vl82c590_t *dev = (vl82c590_t *) priv;
    if (func)
	return 0xff;
    return dev->pci_conf[0][addr];
}


static uint8_t
vl82c593_read(int func, int addr, void *priv)
{
	vl82c590_t *dev = (vl82c590_t *)priv;
    if (func > 0)
	return 0xff;
    return dev->pci_conf[1][addr];
}

static void
vl82c590_isa_write(uint16_t port, uint8_t val, void *p)
{
	vl82c590_t *dev = (vl82c590_t *)p;
	switch (port) {
	case 0xec:
		dev->cfg_index = val;
		break;
	case 0xed:
		if (dev->cfg_index >= 0x01 && dev->cfg_index <= 0x24) {
			dev->cfg_regs[dev->cfg_index] = val;
			switch (dev->cfg_index) {
			case CFG_AAXS:
				shadow_control(0xa0000, 0x4000, val & 3);
				shadow_control(0xa4000, 0x4000, (val >> 2) & 3);
				shadow_control(0xa8000, 0x4000, (val >> 4) & 3);
				shadow_control(0xac000, 0x4000, (val >> 6) & 3);
				break;
			case CFG_BAXS:
				shadow_control(0xb0000, 0x4000, val & 3);
				shadow_control(0xb4000, 0x4000, (val >> 2) & 3);
				shadow_control(0xb8000, 0x4000, (val >> 4) & 3);
				shadow_control(0xbc000, 0x4000, (val >> 6) & 3);
				break;
			case CFG_CAXS:
				shadow_control(0xc0000, 0x4000, val & 3);
				shadow_control(0xc4000, 0x4000, (val >> 2) & 3);
				shadow_control(0xc8000, 0x4000, (val >> 4) & 3);
				shadow_control(0xcc000, 0x4000, (val >> 6) & 3);
				break;
			case CFG_DAXS:
				shadow_control(0xd0000, 0x4000, val & 3);
				shadow_control(0xd4000, 0x4000, (val >> 2) & 3);
				shadow_control(0xd8000, 0x4000, (val >> 4) & 3);
				shadow_control(0xdc000, 0x4000, (val >> 6) & 3);
				break;
			case CFG_EAXS:
				shadow_control(0xe0000, 0x4000, val & 3);
				shadow_control(0xe4000, 0x4000, (val >> 2) & 3);
				shadow_control(0xe8000, 0x4000, (val >> 4) & 3);
				shadow_control(0xec000, 0x4000, (val >> 6) & 3);
				break;
			case CFG_FAXS:
				shadow_control(0xf0000, 0x4000, val & 3);
				shadow_control(0xf4000, 0x4000, (val >> 2) & 3);
				shadow_control(0xf8000, 0x4000, (val >> 4) & 3);
				shadow_control(0xfc000, 0x4000, (val >> 6) & 3);
				break;
			}
		}
		break;
	case 0xee:
		if (mem_a20_alt)
			outb(0x92, inb(0x92) & ~2);
		break;
	}
}

static uint8_t
vl82c590_isa_read(uint16_t port, void *priv)
{
	vl82c590_t *dev = (vl82c590_t *)priv;
	uint8_t ret = 0xff;
	switch (port) {
	case 0xec:
		ret = dev->cfg_index;
		break;
	case 0xed:
		ret = dev->cfg_regs[dev->cfg_index];
		break;
	case 0xee:
		if (!mem_a20_alt)
			outb(0x92, inb(0x92) | 2);
		break;
	case 0xef:
		softresetx86();
		cpu_set_edx();
		break;
	}
	return ret;
}

static void
vl82c590_reset(void *priv)
{
	vl82c590_t *dev = (vl82c590_t *) priv;
    uint8_t val = 0;
}


static void
vl82c590_setup(vl82c590_t *dev)
{
    memset(dev, 0, sizeof(vl82c590_t));

    /* VL82C591 */
    dev->pci_conf[0][0x00] = 0x04; /* VLSI */
    dev->pci_conf[0][0x01] = 0x10; 
    dev->pci_conf[0][0x02] = 0x05; /* VL82C591 */
    dev->pci_conf[0][0x03] = 0x04; 

    dev->pci_conf[0][0x04] = 7;
    dev->pci_conf[0][0x05] = 0;

    dev->pci_conf[0][0x06] = 0x80;
    dev->pci_conf[0][0x07] = 0x02;

    dev->pci_conf[0][0x08] = 0; /*Device revision*/

    dev->pci_conf[0][0x09] = 0x00; /*Device class (PCI bridge)*/
    dev->pci_conf[0][0x0a] = 0x00;
    dev->pci_conf[0][0x0b] = 0x06;

    dev->pci_conf[0][0x0e] = 0x00; /*Single function device*/

    /* dev->pci_conf[0][0x40] = 0x00; */ /* bus number */
    /* dev->pci_conf[0][0x41] = 0x00; */ /* subordinate bus number */
    dev->pci_conf[0][0x54] = dev->pci_conf[0][0x55] = 0x00; /* device specific configuration registers */
    dev->pci_conf[0][0x58] = dev->pci_conf[0][0x59] = 0x00; /* device specific configuration registers */
	dev->pci_conf[0][0x5c] = dev->pci_conf[0][0x5d] = dev->pci_conf[0][0x5e] = dev->pci_conf[0][0x5f] = 0x00; /* device specific configuration registers */

	/* VL82C593 */
	dev->pci_conf[0][0x00] = 0x04; /* VLSI */
	dev->pci_conf[0][0x01] = 0x10;
	dev->pci_conf[0][0x02] = 0x06; /* VL82C591 */
	dev->pci_conf[1][0x03] = 0x00;

    dev->pci_conf[1][0x04] = 7;
    dev->pci_conf[1][0x05] = 0;

    dev->pci_conf[1][0x06] = 0x80;
    dev->pci_conf[1][0x07] = 0x02;

    dev->pci_conf[1][0x08] = 0; /*Device revision*/

    dev->pci_conf[1][0x09] = 0x00; /*Device class (PCI bridge)*/
    dev->pci_conf[1][0x0a] = 0x01;
    dev->pci_conf[1][0x0b] = 0x06;

    dev->pci_conf[1][0x0e] = 0x00; /*Single function device*/

	/* device-specific configuration registers */
	dev->pci_conf[1][0x50] = dev->pci_conf[1][0x51] = dev->pci_conf[1][0x52] = dev->pci_conf[1][0x53] = dev->pci_conf[1][0x54] = dev->pci_conf[1][0x55] = dev->pci_conf[1][0x56] = dev->pci_conf[1][0x57] = dev->pci_conf[1][0x58] = dev->pci_conf[1][0x59] = dev->pci_conf[1][0x5a] = 0x00;
	/* device-specific configuration registers */
	dev->pci_conf[1][0x5c] = dev->pci_conf[1][0x5d] = dev->pci_conf[1][0x5e] = dev->pci_conf[1][0x5f] = 0x00;
	dev->pci_conf[1][0x50] = dev->pci_conf[1][0x51] = dev->pci_conf[1][0x52] = dev->pci_conf[1][0x53] = dev->pci_conf[1][0x54] = dev->pci_conf[1][0x55] = dev->pci_conf[1][0x56] = dev->pci_conf[1][0x57] = dev->pci_conf[1][0x58] = dev->pci_conf[1][0x59] = dev->pci_conf[1][0x5a] = dev->pci_conf[1][0x5b] = dev->pci_conf[1][0x5c] = dev->pci_conf[1][0x5d] = dev->pci_conf[1][0x5e] = dev->pci_conf[1][0x5f] = 0x00;
	dev->pci_conf[1][0x60] = dev->pci_conf[1][0x61] = dev->pci_conf[1][0x62] = dev->pci_conf[1][0x63] = dev->pci_conf[1][0x64] = dev->pci_conf[1][0x65] = dev->pci_conf[1][0x66] = dev->pci_conf[1][0x67] = dev->pci_conf[1][0x68] = dev->pci_conf[1][0x69] = dev->pci_conf[1][0x6a] = dev->pci_conf[1][0x6b] = dev->pci_conf[1][0x6c] = dev->pci_conf[1][0x6d] = dev->pci_conf[1][0x6e] = dev->pci_conf[1][0x6f] = 0x00;
	dev->pci_conf[1][0x70] = dev->pci_conf[1][0x71] = dev->pci_conf[1][0x72] = dev->pci_conf[1][0x73] = dev->pci_conf[1][0x74] = 0x00;
	dev->pci_conf[1][0xff] = 0x00; /* device-specific configuration register */
}


static void
vl82c590_close(void *priv)
{
	vl82c590_t *dev = (vl82c590_t *) priv;
    free(dev);
}


static void *
vl82c590_init(const device_t *info)
{
	vl82c590_t *dev = (vl82c590_t *) malloc(sizeof(vl82c590_t));
	/* dev->cfg_regs[CFG_ID] = ID_VL82C590;
	io_sethandler(0x00ec, 0x0004, vl82c590_isa_read, NULL, NULL, vl82c590_isa_write, NULL, NULL, dev); */
	pci_add_card(0, vl82c591_read, vl82c591_write, dev);
    pci_add_card(5, vl82c593_read, vl82c593_write, dev);
	vl82c590_setup(dev);
    device_add(&port_92_pci_device);
    return dev;
}

const device_t vl82c590_device =
{
    "VLSI VL82C591/VL82C593",
    DEVICE_PCI,
    0,
	vl82c590_init,
	vl82c590_close,
	vl82c590_reset,
    NULL,
    NULL,
    NULL,
    NULL
};
