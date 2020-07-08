/*
* 86Box	A hypervisor and IBM PC system emulator that specializes in
*		running old operating systems and software designed for IBM
*		PC systems and compatibles from 1981 through fairly recent
*		system designs based on the PCI bus.
*
*		This file is part of the 86Box distribution.
*
*		Definitions for project version, branding, and external links.
*
* Authors:	Miran Grca, <mgrca8@gmail.com>
*
*		Copyright 2020 Miran Grca.
*/

/* Version info. */
#define EMU_NAME	"Virtual Computer"
#define EMU_NAME_W	L"Virtual Computer"
#ifdef RELEASE_BUILD
#define EMU_VERSION	"2.07"
#define EMU_VERSION_W	L"2.07"
#define EMU_VERSION_MAJ	2
#define EMU_VERSION_MIN	7
#else
#define EMU_VERSION	"2.10"
#define EMU_VERSION_W	L"2.10"
#define EMU_VERSION_MAJ	2
#define EMU_VERSION_MIN	10
#endif
#define COPYRIGHT_YEAR	"2020"

/* Web URL info. */
#define EMU_SITE	L"N/A"
#define EMU_ROMS_URL	L"https://PLACEHOLDER"
