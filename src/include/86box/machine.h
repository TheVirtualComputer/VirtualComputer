/*
 * 86Box	A hypervisor and IBM PC system emulator that specializes in
 *		running old operating systems and software designed for IBM
 *		PC systems and compatibles from 1981 through fairly recent
 *		system designs based on the PCI bus.
 *
 *		This file is part of the 86Box distribution.
 *
 *		Handling of the emulated machines.
 *
 *
 *
 * Authors:	Sarah Walker, <http://pcem-emulator.co.uk/>
 *		Miran Grca, <mgrca8@gmail.com>
 *		Fred N. van Kempen, <decwiz@yahoo.com>
 *
 *		Copyright 2008-2020 Sarah Walker.
 *		Copyright 2016-2020 Miran Grca.
 *		Copyright 2017-2020 Fred N. van Kempen.
 */
#ifndef EMU_MACHINE_H
# define EMU_MACHINE_H


/* Machine feature flags. */
#ifdef NEW_FLAGS
#define MACHINE_PC		0x000000	/* PC architecture */
#define MACHINE_AT		0x000001	/* PC/AT architecture */
#define MACHINE_PS2		0x000002	/* PS/2 architecture */
#define MACHINE_ISA		0x000010	/* sys has ISA bus */
#define MACHINE_CBUS		0x000020	/* sys has C-BUS bus */
#define MACHINE_EISA		0x000040	/* sys has EISA bus */
#define MACHINE_VLB		0x000080	/* sys has VL bus */
#define MACHINE_MCA		0x000100	/* sys has MCA bus */
#define MACHINE_PCI		0x000200	/* sys has PCI bus */
#define MACHINE_AGP		0x000400	/* sys has AGP bus */
#define MACHINE_HDC		0x001000	/* sys has int HDC */
#define MACHINE_VIDEO		0x002000	/* sys has int video */
#define MACHINE_VIDEO_FIXED	0x004000	/* sys has ONLY int video */
#define MACHINE_MOUSE		0x008000	/* sys has int mouse */
#define MACHINE_SOUND		0x010000	/* sys has int sound */
#define MACHINE_NONMI		0x020000	/* sys does not have NMI's */
#define MACHINE_FDC		0x040000	/* sys has int FDC */
#else
#define MACHINE_PC		0x000000	/* PC architecture */
#define MACHINE_AT		0x000001	/* PC/AT architecture */
#define MACHINE_PS2		0x000002	/* PS/2 architecture */
#define MACHINE_ISA		0x000010	/* sys has ISA bus */
#define MACHINE_CBUS		0x000020	/* sys has C-BUS bus */
#define MACHINE_EISA		0x000040	/* sys has EISA bus */
#define MACHINE_VLB		0x000080	/* sys has VL bus */
#define MACHINE_MCA		0x000100	/* sys has MCA bus */
#define MACHINE_PCI		0x000200	/* sys has PCI bus */
#define MACHINE_AGP		0x000400	/* sys has AGP bus */
#define MACHINE_HDC		0x001000	/* sys has int HDC */
#define MACHINE_VIDEO		0x002000	/* sys has int video */
#define MACHINE_VIDEO_FIXED	0x004000	/* sys has ONLY int video */
#define MACHINE_MOUSE		0x008000	/* sys has int mouse */
#define MACHINE_SOUND		0x010000	/* sys has int sound */
#define MACHINE_NONMI		0x020000	/* sys does not have NMI's */
#define MACHINE_SMP		0x020000	/* Symmetric Multiprocessing */
#define MACHINE_FDC		0x040000	/* sys has int FDC */
#endif

#define IS_ARCH(m, a)		(machines[(m)].flags & (a)) ? 1 : 0;

enum {
	MACHINE_TYPE_NONE = 0,
	/* System boards */
	MACHINE_TYPE_8088,
	MACHINE_TYPE_8086,
	MACHINE_TYPE_286,
	MACHINE_TYPE_386SX,
	MACHINE_TYPE_386DX,
	MACHINE_TYPE_486,
	MACHINE_TYPE_SOCKET4,
	MACHINE_TYPE_SOCKET5,
	MACHINE_TYPE_SOCKET7_3V,
	MACHINE_TYPE_SOCKET7,
	MACHINE_TYPE_SOCKETS7,
	MACHINE_TYPE_SOCKET8,
	MACHINE_TYPE_SLOT1,
	MACHINE_TYPE_SLOT2,
	MACHINE_TYPE_SOCKET370,
	/* Computer manufacturers */
	MACHINE_TYPE_MFG,		/* Computer manufacturer and model of any type */
	/* IBM (International Business Machines) */
	/* COMPAQ */
	/* Intel Corporation */
	/* A (LOCAL RETAILER) */
	/* Aberdeen */
	/* Access Computer Technologies (ACT) */
	/* Acer */
	/* ACMA */
	/* ACR Systems */
	/* ADC (Advanced Digital Corporation) */
	/* Agatech Computer Systems */
	/* AGI Computer */
	/* Alaris */
	/* All Computer Warehouse */
	/* ALR (Advanced Logic Research) */
	/* ALS Computer Systems (LOCAL RETAILER) */
	/* Altec */
	/* Altima */
	/* AMAX Engineering */
	/* Ambra */
	/* AME (Advanced Micro Electronics) */
	/* American Computer Research */
	/* American Megatrends (AMI) */
	/* American Mitac */
	/* American Multisystems */
	/* American Super Computer */
	/* Amrel Technology */
	/* AMS Tech */
	/* Amstrad */
	/* AnyBus Technology */
	/* AOpen (AcerOpen) */
	/* Aquilline */
	/* ARC (American Research Corporation) */
	/* ARC Electronics (LOCAL RETAILER) */
	/* Arche Technologies */
	/* Ares Microdevelopment */
	/* Argo Computers */
	/* Ariel Designs */
	/* AROH SuperCOM Australia */
	/* Arrow Electronics (LOCAL RETAILER) */
	/* ASI */
	/* Aspen Computer */
	/* AST Research (AST Computer) */
	/* Astro Research */
	/* AT&T (Olivetti and NCR) */
	/* Atlas Industries */
	/* ATronics International */
	/* ATS */
	/* Aurum Computer Corporation */
	/* Austin (IPC) */
	/* Automated Computer Technology */
	/* AUVA Computer */
	/* AVI Systems */
	/* Axik Computer */
	/* Bell Computer */
	/* Bi-Link Computer */
	/* BitWise Designs */
	/* Blackship Computer Systems */
	/* Blue Star Marketing */
	/* BOSS Technology */
	/* Brain Computer Corporation */
	/* BRICK-PC */
	/* Broadax Systems (BSi) */
	/* Bus Computer Systems */
	/* C2 Micro Systems */
	/* CAD ONE Computer Design */
	/* CAF Technology */
	/* Caliber */
	/* Chicony */
	/* Clone Computers */
	/* Clover */
	/* Club American */
	/* CMO Micro Systems */
	/* Comex */
	/* Commax */
	/* Commodore */
	/* Comp & Soft Experts */
	/* CompuAdd */
	/* Compudyne */
	/* CompuLink Research (CLR) */
	/* Computer (LOCAL RETAILER) */
	/* Computer Market Place */
	/* Computer Products United */
	/* Computer Sales Professional */
	/* Computer Square */
	/* CompuTrend (later Premio) */
	/* Comtrade */
	/* Cornell Computer Systems */
	/* Cote Computers of Arizona */
	/* CSR */
	/* Cube */
	/* CUI */
	/* CyberMax */
	/* Daewoo */
	/* DataStor (Data Storage Marketing) */
	/* DataWorld */
	/* Deico */
	/* Dell Computer (formerly PC's Limited) */
	/* Destiny */
	/* DFI (Diamond Flower Industries) */
	/* Diamond Technologies */
	/* Digital (DEC) */
	/* Digital Scientific Research */
	/* Digitech */
	/* DirectWave */
	/* Dolch Computer Systems */
	/* DTK Computer */
	/* Duracom Computer Systems */
	/* Dyna Micro */
	/* Dynamic Decisions */
	/* EasyData */
	/* Eltech Research */
	/* Empac International */
	/* EPS Technologies */
	/* Epson */
	/* Ergo Computing */
	/* ESI Automated Office Systems */
	/* Everest Computer Corporation */
	/* Everex Systems */
	/* FastMicro */
	/* First Computer Systems (FCS) */
	/* FiveStar Computers */
	/* Fortron/Source */
	/* Fountain Technologies */
	/* Future Micro */
	/* FutureTech */
	/* Gain Systems */
	/* Gateway 2000 */
	/* Gecco Systems */
	/* Golden Star Technology */
	/* GoldStar */
	/* GRiD Systems */
	/* HD Systems */
	/* Hedaka */
	/* Hertz Computer Corporation */
	/* Hewitt Rand */
	/* Hewlett-Packard */
	/* HiQ (HiQuality Systems) */
	/* Hi-Tech USA */
	/* Humphrey Instruments */
	/* Hymco */
	/* HyperData Technology */
	/* Hyundai */
	/* i Corp */
	/* IDS (International Data Systems) */
	/* Image Microsystems */
	/* Initiative Technology */
	/* Inmac */
	/* Insight Direct */
	/* Intelec */
	/* Intelesys */
	/* International Instrumentation */
	/* International Upgrade Source */
	/* Itautec */
	/* ITI Technologies */
	/* Iverson Computer Corporation */
	/* JDR Microdevices */
	/* Jet Research (LOCAL RETAILER) */
	/* Juko Electronics */
	/* Keydata International */
	/* Leading Edge */
	/* Lightning Computers */
	/* LodeStar Computer */
	/* Lowland Electronics (LOCAL RETAILER) */
	/* Magic Box (LOCAL RETAILER) */
	/* Magix Computers (later MagiPro Computers) */
	/* Matrix Digital Products */
	/* Maximus Computers */
	/* Media On */
	/* Mega Computer Systems */
	/* Memorex Telex */
	/* Micro Express */
	/* Micro Generation */
	/* Micro Professionals */
	/* Micro Telesis */
	/* Micron Electronics */
	/* MicroTech Computer Corporation */
	/* MicroWarehouse */
	/* MidWest Micro (later Systemax) */
	/* Milkyway Computer Products */
	/* MIS Computer Systems */
	/* MiTAC */
	/* MITS Systems (Telemart) */
	/* Mitsuba */
	/* Motherboard Discount Center */
	/* MPC Technologies */
	/* MS Engineering */
	/* MultiMicro */
	/* Multiwave Technology */
	/* Myoda */
	/* Naga Systems */
	/* National MicroComputers */
	/* National MicroSystems */
	/* NCC Computer Systems */
	/* NCR (National Cash Register) */
	/* NEC Technologies */
	/* NETiS Technology */
	/* Northgate Computer Systems */
	/* Novacor */
	/* Occidental Systems */
	/* Olivetti */
	/* Osicom Technologies */
	/* Pacific Coast Micro */
	/* Packard Bell */
	/* PacTron Integration */
	/* Panther Systems */
	/* PC Brand */
	/* PC Craft */
	/* PC Enterprises (LOCAL RETAILER) */
	/* PC Express */
	/* PC Partner */
	/* PC Positive */
	/* PCI Systems */
	/* PerComp MicroSystems */
	/* Peregrine */
	/* POISK */
	/* Polywell Computers */
	/* PowerBox */
	/* Precision Systems Group */
	/* Premio (formerly CompuTrend) */
	/* Professional Computer Systems (PCS) */
	/* Professional Technologies */
	/* QSI */
	/* Quantex */
	/* Quill */
	/* Reason Technology */
	/* Robotech */
	/* Royal Computer */
	/* SAG Electronics */
	/* SAI Systems Laboratories */
	/* Samsung */
	/* Schneider */
	/* Seanix Technology */
	/* Sho-Tronics Computer */
	/* Sidus Systems */
	/* Siemens-Nixdorf */
	/* Silicon Valley Computer */
	/* Simply Better Computers */
	/* Sirius Systems Technology */
	/* SmartWorks */
	/* SoftWorks Development Corporation */
	/* SolMicro */
	/* Sony */
	/* Spear Technology */
	/* Standard Computer Corporation */
	/* Stargate Microsystems */
	/* STD (Standard Systems Supply) */
	/* Summit Micro Design (SMD) */
	/* Swan */
	/* Sys Technology */
	/* Systems Integration Associates (SIA) */
	/* Tagram */
	/* Tandon */
	/* Tandy (later AST Research) */
	/* Tangent */
	/* Tatung */
	/* TC Computers */
	/* TechnoMedia Corporation */
	/* Techway */
	/* TeleVideo Systems */
	/* Tenex Computer Express */
	/* Thoroughbred MicroSystems */
	/* TigerDirect */
	/* Top Data */
	/* Toptek (LOCAL RETAILER) */
	/* Toshiba */
	/* Total Peripherals */
	/* Touche Micro Technologies */
	/* Transource Computers */
	/* Treasure Chest Computers */
	/* Tri-Star */
	/* TriGem */
	/* Twinhead */
	/* Ultra Computers */
	/* Unisys */
	/* United Micro */
	/* United Solutions */
	/* Unitek Technology */
	/* U.S. Micro Express */
	/* USA Flex */
	/* Vanvier */
	/* Vektron International */
	/* VTech */
	/* Wedge Technology */
	/* Windows Memory Corporation */
	/* Worldwide Technologies */
	/* Wyse */
	/* Xi8088 */
	/* Xi Computer Corporation */
	/* Xinetron */
	/* Zenith Data Systems (ZDS) */
	/* Zenon Computer Systems */
	/* ZEOS */
	/* Zodiac Technologies */
	/* ZOOMMAX Computers (LOCAL RETAILER) */
	MACHINE_TYPE_MAX
};


typedef struct _machine_type_ {
	const char	*name;
	const char  id;
} machine_type_t;


#ifdef NEW_STRUCT
typedef struct _machine_ {
    const char	*name;
    const char	*internal_name;
	const char  type; 
#ifdef EMU_DEVICE_H
    const device_t	*device;
#else
    void	*device;
#endif
    struct {
	const char *name;
#ifdef EMU_CPU_H
	CPU *cpus;
#else
	void *cpus;
#endif
    }		cpu[5];
    int		flags;
    uint32_t	min_ram, max_ram;
    int		ram_granularity;
    int		nvrmask;
} machine_t;
#else
typedef struct _machine_ {
    const char	*name;
    const char	*internal_name;
	const char  type;
	struct {
	const char *name;
#ifdef EMU_CPU_H
	CPU *cpus;
#else
	void *cpus;
#endif
    }		cpu[5];
    int		flags;
    uint32_t	min_ram, max_ram;
    int		ram_granularity;
    int		nvrmask;
    int		(*init)(const struct _machine_ *);
#ifdef EMU_DEVICE_H
    const device_t	*(*get_device)(void);
#else
    void	*get_device;
#endif
} machine_t;
#endif


/* Global variables. */
extern const machine_type_t	machine_types[];
extern const machine_t		machines[];
extern int			bios_only;
extern int			machine;
extern int			AT, PCI;


/* Core functions. */
extern int	machine_count(void);
extern int	machine_available(int m);
extern char	*machine_getname(void);
extern char	*machine_get_internal_name(void);
extern int	machine_get_machine_from_internal_name(char *s);
extern void	machine_init(void);
#ifdef EMU_DEVICE_H
extern const device_t	*machine_getdevice(int m);
#endif
extern char	*machine_get_internal_name_ex(int m);
extern int	machine_get_nvrmask(int m);
extern void	machine_close(void);


/* Initialization functions for boards and systems. */
extern void	machine_common_init(const machine_t *);

extern void	machine_at_common_init_ex(const machine_t *, int type);
extern void	machine_at_common_init(const machine_t *);
extern void	machine_at_init(const machine_t *);
extern void	machine_at_ps2_init(const machine_t *);
extern void	machine_at_common_ide_init(const machine_t *);
extern void	machine_at_ibm_common_ide_init(const machine_t *);
extern void	machine_at_ide_init(const machine_t *);
extern void	machine_at_ps2_ide_init(const machine_t *);

#if defined(DEV_BRANCH) && defined(USE_OPEN_AT)
extern int	machine_at_open_at_init(const machine_t *);
#endif

#if defined(DEV_BRANCH) && defined(USE_AMI386SX)
extern int	machine_at_headland_init(const machine_t *);
#endif

//IBM AT with custom BIOS
extern int	machine_at_ibmatami_init(const machine_t *); // IBM AT with AMI BIOS
extern int	machine_at_ibmatpx_init(const machine_t *); //IBM AT with Phoenix BIOS
extern int	machine_at_ibmatquadtel_init(const machine_t *); // IBM AT with Quadtel BIOS

extern int	machine_genxt_init(const machine_t *);


extern int	machine_xt_amixt_init(const machine_t *);
extern int	machine_xt_open_xt_init(const machine_t *);
extern int	machine_xt_pxxt_init(const machine_t *);


/* m_at_286_386sx.c */
extern int	machine_at_px286_init(const machine_t *);
extern int	machine_at_quadt286_init(const machine_t *);
extern int	machine_at_mr286_init(const machine_t *);

extern int	machine_at_neat_ami_init(const machine_t *);


extern int	machine_at_award286_init(const machine_t *);
extern int	machine_at_gw286ct_init(const machine_t *);
extern int	machine_at_kmxc02_init(const machine_t *);

extern int	machine_at_shuttle386sx_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t	*at_ama932j_get_device(void);
extern const device_t	*at_commodore_sl386sx_get_device(void);
#endif

/* m_at_386dx_486.c */

extern int	machine_at_acc386_init(const machine_t *);
extern int	machine_at_asus386_init(const machine_t *); 
extern int  machine_at_ecs386_init(const machine_t *);


extern int	machine_at_ali1429_init(const machine_t *);
extern int	machine_at_winbios1429_init(const machine_t *);

extern int	machine_at_opti495_init(const machine_t *);
extern int	machine_at_opti495_ami_init(const machine_t *);
extern int	machine_at_opti495_mr_init(const machine_t *);

extern int	machine_at_vli486sv2g_init(const machine_t *);
extern int	machine_at_ami471_init(const machine_t *);
extern int	machine_at_px471_init(const machine_t *);
#if defined(DEV_BRANCH) && defined(USE_WIN471)
extern int	machine_at_win471_init(const machine_t *);
#endif

extern int	machine_at_r418_init(const machine_t *);
extern int	machine_at_ls486e_init(const machine_t *);
extern int	machine_at_4dps_init(const machine_t *);
/* #if defined(DEV_BRANCH) && defined(NO_SIO) */
extern int	machine_at_486sp3g_init(const machine_t *);
/* #endif */

/* m_at_commodore.c */

/* m_at_compaq.c */

/* m_at_socket4_5.c */
extern int	machine_at_hot523_init(const machine_t *); 
extern int	machine_at_p5mp3_init(const machine_t *); 
extern int	machine_at_586mc1_init(const machine_t *);

extern int	machine_at_430nx_init(const machine_t *);

extern int	machine_at_p54tp4xe_init(const machine_t *);
extern int	machine_at_mb500n_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t	*at_endeavor_get_device(void);
#endif

/* m_at_socket7_s7.c */
extern int	machine_at_chariot_init(const machine_t *);
extern int	machine_at_mr586_init(const machine_t *);

extern int	machine_at_p55t2p4_init(const machine_t *);
extern int	machine_at_8500tuc_init(const machine_t *); 
extern int	machine_at_p55t2s_init(const machine_t *);
extern int	machine_at_m7shi_init(const machine_t *);
extern int	machine_at_p65up5_cp55t2d_init(const machine_t *);

extern int	machine_at_p55tvp4_init(const machine_t *);
extern int	machine_at_p55va_init(const machine_t *);
extern int	machine_at_i430vx_init(const machine_t *);
extern int	machine_at_8500tvxa_init(const machine_t *);

extern int	machine_at_nupro592_init(const machine_t *);
extern int	machine_at_tx97_init(const machine_t *);
#if defined(DEV_BRANCH) && defined(NO_SIO)
extern int	machine_at_586t2_init(const machine_t *);
#endif
extern int	machine_at_p5mms98_init(const machine_t *);

extern int	machine_at_ficva502_init(const machine_t *);

extern int	machine_at_ficpa2012_init(const machine_t *);
#if defined(DEV_BRANCH) && defined(NO_SIO)
extern int	machine_at_advanceii_init(const machine_t *);
#endif

#ifdef EMU_DEVICE_H
extern const device_t	*at_pb640_get_device(void);
#endif

/* m_at_super7_ss7.c */

/* m_at_socket8.c */
extern int	machine_at_686nx_init(const machine_t *);
extern int	machine_at_8500ttc_init(const machine_t *);
extern int	machine_at_m6mi_init(const machine_t *);
#ifdef EMU_DEVICE_H
extern void	machine_at_p65up5_common_init(const machine_t *, const device_t *northbridge);
#endif
extern int	machine_at_p65up5_cp6nd_init(const machine_t *);

/* m_at_slot1.c */
extern int	machine_at_p65up5_cpknd_init(const machine_t *);
extern int	machine_at_kn97_init(const machine_t *); 
extern int	machine_at_lx6_init(const machine_t *); 
extern int	machine_at_p6i440e2_init(const machine_t *);
extern int	machine_at_p6kfx_init(const machine_t *);

#if defined(DEV_BRANCH) && defined(NO_SIO)
extern int	machine_at_6bxc_init(const machine_t *);
#endif
extern int	machine_at_p2bls_init(const machine_t *);
extern int	machine_at_p3bf_init(const machine_t *);
extern int	machine_at_bf6_init(const machine_t *);
extern int	machine_at_atc6310bxii_init(const machine_t *); 
/* #if defined(DEV_BRANCH) && defined(NO_SIO) */
extern int	machine_at_tsunamiatx_init(const machine_t *);
/* #endif */
extern int	machine_at_p6sba_init(const machine_t *);

#ifdef EMU_DEVICE_H
/* #if defined(DEV_BRANCH) && defined(NO_SIO) */
extern const device_t 	*at_tsunamiatx_get_device(void);
/* #endif */
#endif

/* m_at_slot2.c */
#if defined(DEV_BRANCH) && defined(NO_SIO)
extern int	machine_at_s2dge_init(const machine_t *);
#endif
extern int	machine_at_6gxu_init(const machine_t *);

/* m_at_socket370.c */
/* #if defined(DEV_BRANCH) && defined(NO_SIO) */
extern int	machine_at_s370slm_init(const machine_t *);
/* #endif */
extern int	machine_at_cubx_init(const machine_t *);
extern int	machine_at_atc7020bxii_init(const machine_t *);
extern int	machine_at_63a_init(const machine_t *);
extern int	machine_at_s370sba_init(const machine_t *);

/* m_at_t3100e.c */

/* m_europc.c */

/* m_oivetti_m24.c */

/* m_pcjr.c */

/* m_ps1.c */

/* m_ps1_hdc.c */
#ifdef EMU_DEVICE_H
extern void	ps1_hdc_inform(void *, uint8_t *);
extern const device_t ps1_hdc_device;
#endif

/* m_ps2_isa.c */

/* m_ps2_mca.c */

#ifdef EMU_DEVICE_H
extern const device_t	*tandy1k_get_device(void);
extern const device_t	*tandy1k_hx_get_device(void);
#endif

/* m_xt_laserxt.c */

/* m_xt_t1000.c */

#ifdef EMU_DEVICE_H
extern const device_t	*t1000_get_device(void);
extern const device_t	*t1200_get_device(void);
#endif

/* m_xt_zenith.c */

#ifdef EMU_DEVICE_H
extern const device_t	*xi8088_get_device(void);
#endif

/* IBM (International Business Machines) */
/* m_xt.c */
extern int	machine_pc_init(const machine_t *);								/* IBM PC              (Model 5150)                         */
extern int	machine_pc82_init(const machine_t *);							/* IBM PC              (Model 5150)     (October 1982 BIOS) */
extern int	machine_xt_init(const machine_t *);								/* IBM PC/XT           (Model 5160)                         */
extern int	machine_xt86_init(const machine_t *);							/* IBM PC/XT           (Model 5160)     (    May 1986 BIOS) */
/* m_pcjr.c */
extern int	machine_pcjr_init(const machine_t *);							/* IBM PCjr            (Model 4860)                         */
#ifdef EMU_DEVICE_H
extern const device_t	*pcjr_get_device(void);
#endif
/* See machine_xt_init */													/* IBM Portable PC     (Model 5155)                         */
/* See machine_xt86_init */													/* IBM Portable PC     (Model 5155)     (    May 1986 BIOS) */
extern int	machine_at_ibm_init(const machine_t *);							/* IBM PC/AT           (Model 5170)                         */
extern void	machine_at_init(const machine_t *);								/* IBM PC/AT           (Model 5170)                         */
extern int	machine_at_ibmxt286_init(const machine_t *);					/* IBM PC/XT Model 286 (Model 5162)                         */
/* m_ps2_mca.c */
/* m_ps2_isa.c */
extern int	machine_ps2_model_50_init(const machine_t *);					/* IBM PS/2 Model 50                                        */
/* See above */																/* IBM PS/2 Model 60                                        */
extern int	machine_ps2_model_80_init(const machine_t *);					/* IBM PS/2 Model 80                                        */
/* See below */																/* IBM PS/2 Model 25/286                                    */
extern int	machine_ps2_m30_286_init(const machine_t *);					/* IBM PS/2 Model 30/286                                    */
extern int	machine_ps2_model_55sx_init(const machine_t *);					/* IBM PS/2 Model 55SX                                      */
extern int	machine_ps2_model_70_type3_init(const machine_t *);				/* IBM PS/2 Model 70 (386) (Type 3)                         */
#if defined(DEV_BRANCH) && defined(USE_PS2M70T4)
extern int	machine_ps2_model_70_type4_init(const machine_t *);				/* IBM PS/2 Model 70 (486) (Type 4)                         */
#endif
extern int	machine_ps2_model_95_xp_type_1_init(const machine_t *);			/* IBM PS/2 Model 95 XP (Type 1)                            */
extern int	machine_ps2_model_95_xp_type_2_init(const machine_t *);			/* IBM PS/2 Model 95 XP (Type 2)                            */
extern int	machine_ps2_model_76_77_init(const machine_t *);				/* IBM PS/2 Model 76                                        */
extern int	machine_ps2_server_model_95_init(const machine_t *);			/* IBM PS/2 Server Model 95                                 */
/* m_ps1.c */
extern int	machine_ps1_m2011_init(const machine_t *);						/* IBM PS/1 Model 2011                                      */
extern int	machine_ps1_m2121_init(const machine_t *);						/* IBM PS/1 Model 2121                                      */
/* m_ps1_hdc.c */
#ifdef EMU_DEVICE_H
extern void	ps1_hdc_inform(void *, uint8_t *);
extern const device_t ps1_hdc_device;
#endif
extern int	machine_ps1_m2133_init(const machine_t *);						/* IBM PS/1 Model 2133                                      */
#ifdef EMU_DEVICE_H
extern const device_t	*ps1_m2133_get_device(void); 
#endif
/* See above */																/* IBM PS/1 Model 2155                                      */
/* See above */																/* IBM PS/1 Consultant DX2-66                               */
extern int	machine_ps1_m2168_init(const machine_t *);						/* IBM PS/1 Model 2168                                      */
/* See above */																/* IBM Aptiva 2168 (486 models)                             */
extern int	machine_at_valuepoint433_init(const machine_t *);				/* IBM PS/ValuePoint 433DX/Si                               */
extern int	machine_at_valuepointp60_init(const machine_t *);				/* IBM PS/ValuePoint P60/D                                  */
extern int	machine_ibm_pc_330_350_init(const machine_t *);					/* IBM PC 330                                               */
/* See above */																/* IBM PC 350                                               */
extern int	machine_at_ibm_thinkpad_360cse_init(const machine_t *);			/* IBM ThinkPad 360CSE                                      */

/* COMPAQ */
/* m_xt_compaq.c */
extern int	machine_xt_compaq_init(const machine_t *);						/* COMPAQ Portable                                          */
/* See above */																/* COMPAQ Portable Plus                                     */
/* m_at_compaq.c */
/* See below */																/* COMPAQ DeskPro/286                                       */
/* See below */																/* COMPAQ Portable/286                                      */
extern int	machine_at_portableii_init(const machine_t *);					/* COMPAQ Portable II                                       */
extern int	machine_at_portableiii_init(const machine_t *);					/* COMPAQ Portable III                                      */
/* See below */																/* COMPAQ DeskPro/386                                       */
extern int	machine_at_portableiii386_init(const machine_t *);				/* COMPAQ Portable/386                                      */
extern int	machine_at_compaq_deskpro_m_init(const machine_t *);			/* COMPAQ Deskpro  386/25M                                  */
/* See above */																/* COMPAQ Deskpro  386/25M (02/25/1992 BIOS)                */
extern int	machine_at_compaq_deskpro_m2_init(const machine_t *);			/* COMPAQ Deskpro  386/25M (10/22/1992 BIOS)                */
/* See above */																/* COMPAQ Deskpro  386/33M                                  */
/* See above */																/* COMPAQ Deskpro  486s/16M                                 */
/* See above */																/* COMPAQ Deskpro  486s/25M                                 */
/* See above */																/* COMPAQ Deskpro  486/33M                                  */
/* See above */																/* COMPAQ Deskpro  486/50L                                  */
/* See above */																/* COMPAQ Deskpro     50M                                   */
/* See above */																/* COMPAQ Deskpro     66M                                   */
/* See above */																/* COMPAQ Portable 486C                                     */
extern int	machine_at_compaq_prolinea_4_33_init(const machine_t *);		/* COMPAQ Prolinea 4/33                                     */
/* See above */																/* COMPAQ Prolinea 4/50                                     */
extern int	machine_at_compaq_deskpro_2000_init(const machine_t *);			/* COMPAQ Deskpro 2000                                      */
extern int	machine_at_compaq_deskpro_2000_2_init(const machine_t *);		/* COMPAQ Deskpro 2000 (BIOS update)                        */
#ifdef EMU_DEVICE_H
extern const device_t 	*at_cpqiii_get_device(void);
#endif

/* Intel Corporation */
extern int	machine_at_alfredo_init(const machine_t *);						/* Intel  Classic/PCI    (Alfredo)                          */
extern int	machine_at_batman_init(const machine_t *);						/* Intel Premiere/PCI    (Batman's Revenge)                 */
extern int	machine_at_plato_init(const machine_t *);						/* Intel Premiere/PCI II (Plato)                            */
extern int	machine_at_zappa_init(const machine_t *);						/* Intel Advanced/ZP     (Zappa)                            */
extern int	machine_at_endeavor_init(const machine_t *);					/* Intel Advanced/EV     (Endeavor)                         */
extern int	machine_at_thor_init(const machine_t *);						/* Intel Advanced/ATX    (Thor)                             */
extern int	machine_at_mrthor_init(const machine_t *);						/* Intel Advanced/ATX    (Thor) (MR BIOS)                   */
/* See below */																/* Intel Performance/VS  (Venus)                            */
extern int	machine_at_vs440fx_init(const machine_t *);						/* Intel VS440FX         (Venus)                            */
extern int	machine_at_ap440fx_init(const machine_t *);						/* Intel AP440FX         (Apollo/Krakatoa)                  */
extern int	machine_at_tc430hx_init(const machine_t *);						/* Intel TC430HX         (Tucson)                           */
extern int	machine_at_ym430tx_init(const machine_t *);						/* Intel YM430TX         (Yamamoto)                         */
extern int	machine_at_pd440fx_init(const machine_t *);						/* Intel PD440FX         (Portland)                         */

/* A (LOCAL RETAILER) */
extern int	machine_at_a_486_init(const machine_t *);						/* A 486                                                    */

/* Aberdeen */
extern int	machine_at_aberdeen_super_eisa_vlb_init(const machine_t *);		/* Aberdeen Super EISA VLB                                  */
extern int	machine_at_aberdeen_super_p90_vl_pci_init(const machine_t *);	/* Aberdeen Super P90 VL/PCI                                */
extern int	machine_at_aberdeen_p100_pci_init(const machine_t *);			/* Aberdeen P100-PCI                                        */
extern int	machine_at_aberdeen_p133_pci_init(const machine_t *);			/* Aberdeen P133-PCI                                        */
extern int	machine_at_aberdeen_p133_pci2_init(const machine_t *);			/* Aberdeen P133-PCI                                        */

/* Access Computer Technologies (ACT) */
extern int	machine_at_act_486_66mhz_init(const machine_t *);				/* ACT 486-66MHz                                            */

/* Acer (including AcerOpen/AOpen) */
extern int	machine_at_acerpower_486e_init(const machine_t *);				/* Acer AcerPower 486e DX2/66 Model 5657                    */
extern int	machine_at_acera1g_init(const machine_t *);						/* Acer A1G                                                 */
#ifdef EMU_DEVICE_H
extern const device_t 	*at_acera1g_get_device(void);
#endif
/* See below */																/* Acer AcerPower 60MHz Pentium                             */
/* See below */																/* Acer AcerPower 90MHz Pentium                             */
extern int	machine_at_acerv30_init(const machine_t *);						/* Acer V30                                                 */
extern int	machine_at_v60n_init(const machine_t *);						/* Acer V60N                                                */
extern int	machine_at_acerv35_init(const machine_t *);						/* Acer AcerPower Pentium 200 MHz                           */
extern int	machine_at_acerv35r0_init(const machine_t *);					/* Acer AcerPower Pentium 200 MHz (R01-E1 R0)               */
extern int	machine_at_acerv35n_init(const machine_t *);					/* Acer AcerPower 9536WM                                    */
extern int	machine_at_acerv35nc0_init(const machine_t *);					/* Acer AcerPower 9536WM (R01-C0 R3)                        */
extern int	machine_at_acerv35nd1_init(const machine_t *);					/* Acer AcerPower 9536WM (R01-D1   )                        */
extern int	machine_at_acerv35ns1_init(const machine_t *);					/* Acer AcerPower 9536WM (R01-D1 S1)                        */
/* See above */																/* Acer AcerPower Network Ready (R01-D1 S1)                 */
extern int	machine_at_acerv35lan_init(const machine_t *);					/* Acer AcerPower Network Ready                             */
/* See machine_at_acerv35ns1_init */										/* Acer AcerPower 5505WM (R01-D1 S1)                        */
/* See machine_at_acerv35land_init */										/* Acer AcerPower 5505WM                                    */
/* See below */																/* Acer AcerPower Ultima                                    */
extern int	machine_at_acerm3a_init(const machine_t *);						/* Acer AcerAltos 300                                       */

/* ACMA */
extern int	machine_at_acma_386_40_init(const machine_t *);					/* ACMA 386/40                                              */
extern int	machine_at_acma_486_25_init(const machine_t *);					/* ACMA 486/25                                              */
extern int	machine_at_acma_mpc_433_486_66_init(const machine_t *);			/* ACMA MPC/433                                             */
/* See above */																/* ACMA 486-66/DX2 VESA System                              */
extern int	machine_at_acma_486_pcmcia_init(const machine_t *);				/* ACMA 486 Energy Pro                                      */
/* See above */																/* ACMA 486DX2-66 PCMCIA System                             */
extern int	machine_at_acma_486dx2_init(const machine_t *);					/* ACMA Desktop 486DX2-66                                   */
extern int	machine_at_acma_p60_init(const machine_t *);					/* ACMA P60                                                 */
extern int	machine_at_acma_p66_tower_init(const machine_t *);				/* ACMA P66 Tower                                           */
extern int	machine_at_acma_p90_init(const machine_t *);					/* ACMA P90                                                 */
/* See above */																/* ACMA P90 Tower                                           */
extern int	machine_at_acma_p100_init(const machine_t *);					/* ACMA P100                                                */
extern int	machine_at_acma_spower_init(const machine_t *);					/* ACMA sPower 75                                           */
/* See above */																/* ACMA sPower 90                                           */
extern int	machine_at_acma_z_power_100_133_init(const machine_t *);		/* ACMA z-Power 100                                         */
/* See above */																/* ACMA z-Power 133                                         */
extern int	machine_at_acma_zpower_133_166_init(const machine_t *);			/* ACMA zPower 133                                          */
/* See above */																/* ACMA zPower 166                                          */
extern int	machine_at_acma_zpower_pro_200_init(const machine_t *);			/* ACMA zPower Pro 200                                      */
extern int	machine_at_acma_exp200_init(const machine_t *);					/* ACMA EXP200                                              */
extern int	machine_at_acma_exp_pro_266_init(const machine_t *);			/* ACMA EXP Pro 266                                         */

/* ACR Systems */
extern int	machine_at_acr_mia66_init(const machine_t *);					/* ACR MIA66                                                */

/* ADC (Advacned Digital Corporation) */
extern int	machine_at_adc_powerlite_386sx_init(const machine_t *);			/* ADC Powerlite 386SX                                      */

/* ADI */
extern int	machine_at_adi386sx_init(const machine_t *);					/* ADI 386SX                                                */

/* Agatech Computer Systems */
extern int	machine_at_agatech_aga_dx33_init(const machine_t *);			/* Agatech AGA-DX33                                         */

/* AGI Computer */
extern int	machine_at_agi_3900b_init(const machine_t *);					/* AGI 3900B                                                */

/* Alaris */
extern int	machine_at_alaris_leopard_plus_init(const machine_t *);			/* Alaris Leopard Plus EnergySmartPC 486SLC2 66             */
/* See above */																/* Alaris Cougar EnergySmartPC 486BL3X 75                   */
/* See above */																/* Alaris EnergySmartPC BL3X100                             */
/* See above */																/* Alaris Leopard VIP BL-100                                */
extern int	machine_at_alaris_nx586_init(const machine_t *);				/* Alaris Nx586 (AMIBIOS)                                   */
extern int	machine_at_alaris_nx586_winbios_init(const machine_t *);		/* Alaris Nx586 (AMI WinBIOS)                               */

/* All Computer Warehouse */
extern int	machine_at_acw_p5_120v_init1(const machine_t *);				/* All Computer Warehouse ACW P5-120V                       */
extern int	machine_at_acw_p5_120v_init2(const machine_t *);				/* All Computer Warehouse ACW P5-120V                       */
extern int	machine_at_acw_p5_120v_init3(const machine_t *);				/* All Computer Warehouse ACW P5-120V                       */
extern int	machine_at_acw_p5_120v_init(const machine_t *);					/* All Computer Warehouse ACW P5-120V                       */
extern int	machine_at_acw_p5_133b_init(const machine_t *);					/* All Computer Warehouse ACW Pentium P5-133B               */
extern int	machine_at_acw_p5_120hb_init(const machine_t *);				/* All Computer Warehouse ACW P5-120HB                      */
extern int	machine_at_acw_p5_166bp_init(const machine_t *);				/* All Computer Warehouse ACW P5-166BP                      */

/* ALR (Advanced Logic Research) */
extern int	machine_at_alr_ranger_init(const machine_t *);					/* ALR Ranger M425-120                                      */
/* See above */																/* ALR Ranger M425s-120                                     */
/* See above */																/* ALR Ranger MC425-120                                     */
/* See above */																/* ALR Ranger MC425s-120                                    */
/* See below */																/* ALR Optima SL 575 Model 1                                */
/* See below */																/* ALR Optima SL 575 Model 850B                             */
extern int	machine_at_alr_optima_590_5120_init(const machine_t *);			/* ALR Optima    590                                        */
/* See above */																/* ALR Optima SL 5100 Model 1                               */
/* See above */																/* ALR Optima SL 5100 Model 850B                            */
/* See above */																/* ALR Optima    5120                                       */

/* ALS Computer Systems (LOCAL RETAILER) */
extern int	machine_at_als_486dx2_66_lb_init(const machine_t *);			/* ALS 486DX2-66 LB                                         */

/* Altec */
extern int	machine_at_altec_486_init(const machine_t *);					/* Altec 486/33 Local Bus                                   */
extern int	machine_at_altec_486dx2_init(const machine_t *);				/* Altec 486DX2 Local Bus                                   */

/* Altima */
extern int	machine_at_altima_433_80486dx_init(const machine_t *);			/* Altima 433 80486DX                                       */

/* AMAX Engineering */
extern int	machine_at_amax_386_40_isamax_init(const machine_t *);			/* AMAX 386-40    ISAmax Power Station                      */
extern int	machine_at_amax_486dx2_50_isamax_init(const machine_t *);		/* AMAX 486DX2-50 ISAmax Power Station                      */
extern int	machine_at_amax_powerstation_66_init(const machine_t *);		/* AMAX PowerStation 66                                     */
extern int	machine_at_amax_powerstation_init(const machine_t *);			/* AMAX 90MHz PowerStation                                  */
extern int	machine_at_amax_powerstation_90_init(const machine_t *);		/* AMAX PowerStation 90                                     */
extern int	machine_at_amax_p100_p133_init(const machine_t *);				/* AMAX PowerStation P100                                   */
/* See above */																/* AMAX PowerStation P133                                   */
extern int	machine_at_amax_p133f_p166f_init(const machine_t *);			/* AMAX PowerStation  133F                                  */
/* See above */																/* AMAX PowerStation  166F                                  */

/* AmazePC */
extern int	machine_at_ambx133_init(const machine_t *);						/* AmazePC AM-BX133                                         */

/* Ambra */
/* See below */																/* Ambra S450SL                                             */
/* See below */																/* Ambra S425SX                                             */
/* See below */																/* Ambra S433DX                                             */
/* See below */																/* Ambra D466BL/CD                                          */
/* See below */																/* Ambra D466BL/CD (BIOS update)                            */
extern int	machine_at_ambra_d466bl_init(const machine_t *);				/* Ambra D466BL                                             */
extern int	machine_at_ambra_d466bl2_init(const machine_t *);				/* Ambra D466BL (BIOS update)                               */
/* See above */																/* Ambra D466DX                                             */
/* See above */																/* Ambra D466DX (BIOS update)                               */
/* See above */																/* Ambra T466BL/CD                                          */
/* See above */																/* Ambra T466BL/CD (BIOS update)                            */
/* See above */																/* Ambra T466BL                                             */
/* See above */																/* Ambra T466BL (BIOS update)                               */
/* See above */																/* Ambra T466DX                                             */
/* See above */																/* Ambra T466DX (BIOS update)                               */
extern int	machine_at_ambradp60_init(const machine_t *);					/* Ambra DP60PCI                                            */
/* See above */																/* Ambra TP60PCI                                            */
extern int	machine_at_ambradp90_init(const machine_t *);					/* Ambra DP90PCI                                            */
/* See above */																/* Ambra TP90PCI                                            */

/* AME (Advanced Micro Electronics) */
extern int	machine_at_ame_intel_486_init(const machine_t *);				/* AME            Intel 486                                 */
extern int	machine_at_ame_pentium_intel_triton_init(const machine_t *);	/* AME Pentium    Intel Triton                              */
extern int	machine_at_ame_supermicro_p55_pci_init(const machine_t *);		/* AME SuperMicro P55   PCI                                 */
extern int	machine_at_ame_supermicro_p55_pci2_init(const machine_t *);		/* AME SuperMicro P55   PCI                                 */

/* American Computer Research */
extern int	machine_at_acr_solar_star_486bl_75_init(const machine_t *);		/* ACR Solar Star 486BL/75                                  */

/* American Megatrends (AMI) */
extern int	machine_at_excalibur_init(const machine_t *);					/* AMI Excalibur                                            */

/* American Mitac */
/* See Mitac */

/* American Multisystems */
extern int	machine_at_infogold_486dx2_init(const machine_t *);				/* American Multisystems InfoGold 486DX2/66                 */
extern int	machine_at_infogold_pentium_66_init(const machine_t *);			/* American Multisystems InfoGold Pentium/66                */
extern int	machine_at_infogold_pentium_90_init(const machine_t *);			/* American Multisystems InfoGold Pentium/90                */
extern int	machine_at_infogold_p90_init(const machine_t *);				/* American Multisystems InfoGold        P90                */

/* American Super Computer */
extern int	machine_at_asc_486_33i_init(const machine_t *);					/* American Super Computer 486/33i                          */

/* Amrel */
extern int	machine_at_amrel_mlt486dxu33_init(const machine_t *);			/* Amrel MLT486DXU33                                        */

/* AMS Tech */
extern int	machine_at_ams_soundwave_init(const machine_t *);				/* AMS  SoundWave                                           */
extern int	machine_at_ams_travelpro_5333_5366_init(const machine_t *);		/* AMS TravelPro 5333                                       */
/* See above */																/* AMS TravelPro 5366                                       */
/* See machine_at_ams_soundwave_init */										/* AMS  SoundPro DX4/75                                     */
/* See above */																/* AMS  SoundPro DX4/100                                    */

/* Amstrad */
/* m_amstrad.c */
extern int	machine_pc1512_init(const machine_t *);							/* Amstrad PC1512                                           */
extern int	machine_pc1640_init(const machine_t *);							/* Amstrad PC1640                                           */
extern int	machine_pc200_init(const machine_t *);							/* Amstrad PC20                                             */
/* See above */																/* Amstrad PC200                                            */
extern int	machine_ppc512_init(const machine_t *);							/* Amstrad PPC512                                           */
/* See above */																/* Amstrad PPC640                                           */
extern int	machine_pc2086_init(const machine_t *);							/* Amstrad PC2086                                           */
extern int	machine_pc3086_init(const machine_t *);							/* Amstrad PC3086                                           */
#ifdef EMU_DEVICE_H
extern const device_t  	*pc1512_get_device(void);
extern const device_t 	*pc1640_get_device(void);
extern const device_t 	*pc200_get_device(void);
extern const device_t 	*ppc512_get_device(void);
extern const device_t 	*pc2086_get_device(void);
extern const device_t 	*pc3086_get_device(void);
#endif
extern int	machine_at_wd76c10_init(const machine_t *);						/* Amstrad PC7386SX                                         */
/* See above */																/* Amstrad Mega PC                                          */
extern int	machine_at_amstrad_pc7486slc_init(const machine_t *);			/* Amstrad PC 7486SLC 80                                    */
/* See above */																/* Amstrad PC7486SLC-33                                     */

/* AnyBus Technology */
extern int	machine_at_anybus_486_33ism_init(const machine_t *);			/* AnyBus 486/33ISM                                         */

/* AOpen (AcerOpen) */
extern int	machine_at_ap53_init(const machine_t *);						/* AOpen AP53                                               */
extern int	machine_at_ax59pro_init(const machine_t *);						/* AOpen AX59 Pro                                           */
extern int	machine_at_ax6bc_init(const machine_t *);						/* AOpen AX6BC                                              */

/* Aquilline */
extern int	machine_at_aquilline_nt33_init(const machine_t *);				/* Aquilline NT33                                           */

/* ARC (American Research Corporation) */
extern int	machine_at_arc_386_33_skyscraper_init(const machine_t *);		/* ARC 386/33 Skyscraper                                    */

/* ARC Electronics (LOCAL RETAILER) */
extern int	machine_at_arc_486dx4_100_init(const machine_t *);				/* ARC 486DX4-100                                           */

/* AROH SuperCOM Australia */
extern int	machine_at_arch_supercom_486_220vi_init(const machine_t *);		/* AROH SuperCOM 486-220VI                                  */

/* Arche Technologies */
extern int	machine_at_ama932j_init(const machine_t *);						/* Arche AMA-932J                                           */
#ifdef EMU_DEVICE_H
extern const device_t 	*at_ama932j_get_device(void);
extern const device_t	*at_commodore_sl386sx_get_device(void);
#endif
/* See above */																/* Arche Master   386-40                                    */
/* See above */																/* Arche Legacy   386-40                                    */
extern int	machine_at_arche_legacy_486_init(const machine_t *);			/* Arche Legacy-I 486-33                                    */

/* Ares Microdevelopment */
extern int	machine_at_ares_386_40_sonic_init(const machine_t *);			/* Ares 386/40    Sonic                                     */
/* See above */																/* Ares 486-50DX2 Sonic III                                 */
extern int	machine_at_ares_dx4_100_init(const machine_t *);				/* Ares DX4/100                                             */
extern int	machine_at_ares_pentiumpro90_init(const machine_t *);			/* ARES Pentium Pro 90                                      */

/* Argo Computer */
extern int	machine_at_argo_tower_386_33_init(const machine_t *);			/* Argo Tower 386/33                                        */

/* Ariel Design */
/* See below */																/* Ariel 486SX/25                                           */
extern int	machine_at_ariel_486sx_25_best_value_init(const machine_t *);	/* Ariel 486SX-25 Best Value                                */
/* See above */																/* Ariel 486DX2-50                                          */
/* See above */																/* Ariel 486DX2-66VLB                                       */

/* Arrow Electronics (LOCAL RETAILER) */
extern int	machine_at_arrow_rev_j_init(const machine_t *);					/* Arrow Rev J                                              */

/* ASI */
extern int	machine_at_asi_486dx4_100_init(const machine_t *);				/* ASI 486DX4-100                                           */

/* Aspen */
extern int	machine_at_aspen_personal_486_init(const machine_t *);			/* Aspen Personal 486                                       */
extern int	machine_at_aspen_universa_e_series_init(const machine_t *);		/* Aspen Universa E-Series                                  */
extern int	machine_at_aspen_universa_cd_init(const machine_t *);			/* Aspen Universa CD                                        */
extern int	machine_at_aspen_aspenta_60_66_init(const machine_t *);			/* Aspen  Aspenta 60/66                                     */

/* AST Research (later AST Computer) */
extern int	machine_at_ast_advantage_4066d_init(const machine_t *);			/* AST Bravo LC 4/66d                                       */
/* See above */																/* AST Advantage! Adventure 4066d                           */
/* See above */																/* AST Advantage! Adventure 6066d                           */
/* See above */																/* AST Advantage! Adventure 8066d                           */
extern int	machine_at_ast_premmia_mx_466d_init(const machine_t *);			/* AST Premmia MX 4/66d                                     */
extern int	machine_at_ast_premmia_mx_4100t_init(const machine_t *);		/* AST Premmia MX 4/100t                                    */
extern int	machine_at_ast_premmia_lx_p60_init(const machine_t *);			/* AST Premmia LX P/60                                      */
extern int	machine_at_ast_premmia_gx_p90_init(const machine_t *);			/* AST Premmia GX P/90 Model 733                            */
/* See above */																/* AST Premmia GX P/100                                     */
extern int	machine_at_ast_advantage_8100p_init(const machine_t *);			/* AST Advantage! 8100p                                     */
/* See above */																/* AST Advantage! 8120p                                     */
/* See above */																/* AST Advantage! 8133p                                     */
extern int	machine_at_ast_advantage_818_init(const machine_t *);			/* AST Advantage! 818                                       */
extern int	machine_at_adventure_init(const machine_t *);					/* AST Advantage! Adventure 225                             */
extern int	machine_at_ast_bravo_ms_t_6200_init(const machine_t *);			/* AST Bravo MS-T 6200                                      */
extern int	machine_at_ast_bravo_ms_t_6200_05_init(const machine_t *);		/* AST Bravo MS-T 6200               (1.00.05.CS1Q)         */
extern int	machine_at_ast_bravo_ms_t_5200_init(const machine_t *);			/* AST Bravo MS-T 5200                                      */
extern int	machine_at_ast_advantage_9312_init(const machine_t *);			/* AST Advantage! 9312 Communcations                        */
extern int	machine_at_ast_advantage_9312_06_init(const machine_t *);		/* AST Advantage! 9312 Communcations (1.00.06.DL0Q)         */
extern int	machine_at_ast_advantage_9314_init(const machine_t *);			/* AST Advantage! 9314                                      */
extern int	machine_at_ast_advantage_9314_06_init(const machine_t *);		/* AST Advantage! 9314               (1.00.06.DL0Q)         */
extern int	machine_at_ast_advantage_9320_init(const machine_t *);			/* AST Advantage! 9320                                      */
extern int	machine_at_ast_advantage_9320_06_init(const machine_t *);		/* AST Advantage! 9320               (1.00.06.DL0Q)         */
extern int	machine_at_ast_bravo_lc_6233_init(const machine_t *);			/* AST Bravo LC 6233                                        */
extern int	machine_at_ast_bravo_lc_6233_02_init(const machine_t *);		/* AST Bravo LC 6233                 (1.00.02.DU0I)         */
extern int	machine_at_ast_ascentia_910n_init(const machine_t *);			/* AST Ascentia 910N (AST Advantage! BIOS)                  */

/* Astro Research */
extern int	machine_at_astronote_skd_iii_init(const machine_t *);			/* AstroNote SKD III                                        */

/* AT&T (Olivett and NCR) */
/* See Olivetti M24 */														/* AT&T 6300 (Olivetti M24)                                 */
/* See NCR */																/* AT&T Globalyst                                           */

/* Atlas Industries */
extern int	machine_at_atlas_486sx_25_init(const machine_t *);				/* Atlas        486SX/25                                    */
extern int	machine_at_atlas_pronet_486ux_series_init(const machine_t *);	/* Atlas ProNet 486UX Series                                */

/* ATronics International */
extern int	machine_at_atronics_ati_486_init(const machine_t *);			/* ATronics ATI 486SX/20                                    */
/* See above */																/* ATronics ATI 486SX-25                                    */
/* See above */																/* ATronics ATI 486B/50                                     */
/* See above */																/* ATronics ATI-486/50DX2                                   */
extern int	machine_at_atronics_486_init(const machine_t *);				/* ATronics ATI-486-50                                      */
/* See above */																/* ATronics ATI-486-66                                      */
extern int	machine_at_atronics_486_vesa_init(const machine_t *);			/* ATronics ATI-486 Multi Media                             */
/* See above */																/* ATronics Bronze 466 VESA                                 */
extern int	machine_at_atronics_ati_pentium_init(const machine_t *);		/* ATronics ATI Pentium Pinnacle I                          */
/* See above */																/* ATronics ATI-Pantera-66                                  */

/* ATS */
extern int	machine_at_ats_ami_multimedia_486_66_init(const machine_t *);	/* ATS AMI Multimedia 486-66                                */

/* Aurum Computer Corporation */
extern int	machine_at_aurum_goldnote_dx2_50_init(const machine_t *);		/* Aurum GoldNote DX2-50                                    */

/* Austin (IPC) */
extern int	machine_at_austin_486sx_20_winstation_init(const machine_t *);	/* Austin 486SX/20 WinStation                               */
/* See above */																/* Austin 486-33I  WinStation                               */
/* See below */																/* Austin P5-60                                             */
/* See below */																/* Austin P5-66                                             */
extern int	machine_at_austin_p5_60_init(const machine_t *);				/* Austin Premier P5-60 Desktop                             */
/* See above */																/* Austin Power System 60                                   */
/* See above */																/* Austin Deskside P5-66                                    */
extern int	machine_at_austin_486dx2_66_init(const machine_t *);			/* Austin Communications Manager 486DX2-66                  */
extern int	machine_at_austin_p66_init(const machine_t *);					/* Austin Communications Manager P66                        */
extern int	machine_at_austin_edutainer_plus_init(const machine_t *);		/* Austin Edutainer Plus                                    */
/* See below */																/* Austin P90                                               */
extern int	machine_at_austin_power_system_90_init(const machine_t *);		/* Austin Power System 90                                   */
extern int	machine_at_austin_power_plus_75_init(const machine_t *);		/* Austin Power Plus 75                                     */
extern int	machine_at_austin_power_plus_100_init(const machine_t *);		/* Austin Power Plus 100                                    */
extern int	machine_at_austin_power_plus_120_init(const machine_t *);		/* Austin Power Plus 120                                    */
extern int	machine_at_austin_power_plus_120_bs0_init(const machine_t *);	/* Austin Power Plus 120 (1.00.02.BS0)                      */
extern int	machine_at_austin_power_plus_133_init(const machine_t *);		/* Austin Power Plus 133                                    */
extern int	machine_at_austin_powerplus_133_init(const machine_t *);		/* Austin PowerPlus 133                                     */
extern int	machine_at_austin_powerplus_133_2_init(const machine_t *);		/* Austin PowerPlus 133 (1.00.04.CB0)                       */
extern int	machine_at_austin_powerplus_75_init(const machine_t *);			/* Austin PowerPlus 75                                      */
extern int	machine_at_austin_powerplus_133_dh0_init(const machine_t *);	/* Austin PowerPLUS 133 (1.00.04.DH0)                       */
extern int	machine_at_austin_powerplus_166_init(const machine_t *);		/* Austin PowerPlus 166                                     */
extern int	machine_at_austin_powerplus_166_dh0_init(const machine_t *);	/* Austin PowerPLUS 200 (1.00.04.DH0)                       */
extern int	machine_at_austin_powerplus_200_init(const machine_t *);		/* Austin PowerPLUS 200                                     */
extern int	machine_at_austin_elan_200_init(const machine_t *);				/* Austin Elan Workstation 200                              */

/* Automated Computer Technology */
extern int	machine_at_act386_33fe_init(const machine_t *);					/* ACT386-33FE                                              */

/* AUVA Computer */
extern int	machine_at_auva_386_40_init(const machine_t *);					/* AUVA TAM33-U0                                            */
/* See above */																/* AUVA TAM33-U1                                            */
/* See above */																/* AUVA TAM40-U0                                            */
/* See above */																/* AUVA TAM40-U1                                            */
/* See above */																/* AUVA 386/40                                              */

/* AVI Systems */
extern int	machine_at_avi_anb3_386sxl_25_init(const machine_t *);			/* AVI ANB3-386SXL-25                                       */

/* Axik Computer */
extern int	machine_at_axik_ace_cache_486_init(const machine_t *);			/* Axik           486/WB/50                                 */
/* See above */																/* Axik           486DX-33                                  */
/* See above */																/* Axik           486DX-50                                  */
/* See above */																/* Axik           486DX2-50                                 */
/* See above */																/* Axik           486DX2-66                                 */
/* See above */																/* Axik Ace Cache 486SX-25                                  */
/* See above */																/* Axik Ace Cache 486DX2-50                                 */
extern int	machine_at_axik_ace_cache_486_33v_66v_init(const machine_t *);	/* Axik Ace Cache 486-33V/MPC                               */
/* See above */																/* Axik Ace Cache 486DX2-66V                                */
extern int	machine_at_axik_ace_cache_586dx_66_cd_init(const machine_t *);	/* Axik Ace Cache 586DX-66/CD                               */
extern int	machine_at_axik_ace_cache_586_66pci_mpc_init(const machine_t *);/* Axik Ace Cache 586-66PC/MPC                              */
extern int	machine_at_axik_ace_cache_466_vg2_init(const machine_t *);		/* Axik Ace Cache 466 VG2 Cutlass                           */

/* Bell */
extern int	machine_at_bell_bsp_1340_init(const machine_t *);				/* Bell BSP 1340                                            */

/* Bi-Link Computer */
extern int	machine_at_bi_link_i486dx2_66_init(const machine_t *);			/* Bi-Link Desktop i486DX2/66                               */

/* BitWise Designs */
extern int	machine_at_bitwise_model_433_init(const machine_t *);			/* BitWise Model 433                                        */

/* Blackship */
extern int	machine_at_blackship_blk_386_40_init(const machine_t *);		/* Blackship BLK 386/40                                     */
extern int	machine_at_blackship_486sx_20u_init(const machine_t *);			/* Blackship     486SX/20U                                  */
/* See below */																/* Blackship BLK 486SX/25                                   */
extern int	machine_at_blackship_blk_486sx25_init(const machine_t *);		/* Blackship BLK 486/33                                     */
extern int	machine_at_blackship_blk_486dx2_66_init(const machine_t *);		/* Blackship BLK 486DX2/66                                  */
/* See above */																/* Blackship BLK 486DX2/66 LB                               */
/* See below */																/* Blackship 486DX2-66 Minitower                            */
extern int	machine_at_blackship_atlantis_init(const machine_t *);			/* Blackship Atlantis                                       */
/* See above */																/* Blackship BLK DX4/100                                    */
extern int	machine_at_blackship_p90_neptune_init(const machine_t *);		/* Blackship P90 Neptune                                    */

/* Blue Max */
/* See International Instrumentation */

/* Blue Star Marketing */
/* See below */																/* Blue Star Upgradable                                     */
extern int	machine_at_blue_star_486sx_25_desktop_init(const machine_t *);	/* Blue Star 486SX/25 Desktop                               */
/* See above */																/* Blue Star 466D2U                                         */
extern int	machine_at_blue_star_486dx_33_series_ii_init(const machine_t *);/* Blue Star 486DX/33 Series II VLB/MM-Kit #7               */
/* See above */																/* Blue Star 486                VLB Pro Series              */
extern int	machine_at_blue_star_eclipse_e_133_166_init(const machine_t *);	/* Blue Star Eclipse E-133                                  */
/* See above */																/* Blue Star Eclipse P-166                                  */

/* BOSS Technology */
extern int	machine_at_boss_486sx_25_cache_init(const machine_t *);			/* BOSS 486SX/25 Cache                                      */
extern int	machine_at_boss_466d_init(const machine_t *);					/* BOSS 466d                                                */

/* Brain Computer Corporation */
extern int	machine_at_the_brain_386_33_init(const machine_t *);			/* The Brain 386-33                                         */

/* BRICK-PC */
extern int	machine_at_brick_9002_4dxu_init(const machine_t *);				/* Brick 9002 4DXU                                          */

/* Broadax Systems (BSi) */
extern int	machine_at_broadax_bsi_486_init(const machine_t *);				/* Broadax BSi   486DX2-50                                  */
/* See above */																/* Broadax BSi   486DX2-66                                  */
extern int	machine_at_broadax_bsi_nb486dx2_50_init(const machine_t *);		/* Broadax BSi NB486DX2-50                                  */
/* See above */																/* Broadax BSi NP846   Mono                                 */
/* See above */																/* Broadax BSi NP846D                                       */
/* See above */																/* Broadax BSi NP846T                                       */
extern int	machine_at_broadax_bsi_np7549d_init(const machine_t *);			/* Broadax BSi NP7549D                                      */
/* See above */																/* Broadax BSi NP7657D                                      */
/* See above */																/* Broadax BSi NP7659T                                      */
extern int	machine_at_broadax_bsi_np9249d_init(const machine_t *);			/* Broadax BSi NP9249D                                      */
extern int	machine_at_broadax_bsi_np9549d_init(const machine_t *);			/* Broadax BSi NP9549D                                      */
extern int	machine_at_broadax_bsi_np3656t_init(const machine_t *);			/* Broadax BSi NP3656T Pentiu                               */

/* BSi (Broadax Systems) */
/* See Broadax Systems (BSi) */

/* Bus Computer Systems */
extern int	machine_at_bus_386_33_init(const machine_t *);					/* Bus 386-33                                               */

/* C2 Micro Systems */
extern int	machine_at_c2_micro_486sx_init(const machine_t *);				/* C2 Micro 486SX                                           */
/* See above */																/* C2 Saber 486/SLC                                         */
/* See above */																/* C2 Saber 4X25                                            */
/* See above */																/* C2 Saber/50                                              */
/* See above */																/* C2 Saber DX/2                                            */
extern int	machine_at_c2_saber_sound_init(const machine_t *);				/* C2 Saber Sound                                           */
extern int	machine_at_c2_saber_486_vl_init(const machine_t *);				/* C2 Saber 486 VL                                          */

/* CAD ONE Computer Design */
/* See Chicony */															/* CAD ONE 386SX-16 Mhz                                     */
/* See Chicony */															/* CAD ONE 386SX-25-MHz    Cache Opt                        */
/* See Chicony */															/* CAD ONE 386-33 MHz  64k Cache                            */
/* See Chicony */															/* CAD ONE 386-33 MHz 256k Cache                            */
/* See Chicony */															/* CAD ONE 386-40 MHz  64k Cache                            */
/* See Chicony */															/* CAD ONE 486-25 MHz 128k Cache                            */
/* See Chicony */															/* CAD ONE 486-33 MHz 256k Cache                            */
/* See Chicony */															/* CAD ONE 486-50 MHz                                       */

/* CAF Technology */
extern int	machine_at_caf_vl_bus_series_init(const machine_t *);			/* CAF VL DX/33                                             */
/* See above */																/* CAF VL DX2/66                                            */

/* Caliber */
extern int	machine_at_caliber_aspect_smart_weapon_init(const machine_t *);	/* Caliber-Aspect Smart Weapon 486-66                       */
extern int	machine_at_caliber_voyager_iii_150_init(const machine_t *);		/* Caliber Voyager III 150                                  */
extern int	machine_at_caliber_voyager_v_mmx_init(const machine_t *);		/* Caliber Voyager V MMX                                    */

/* Chicony Electronics */
extern int	machine_at_chicony_ch_386s_init(const machine_t *);				/* Chicony CH-386S-16B                                      */
/* See above */																/* Chicony CH-386S-20B                                      */
/* See above */																/* Chicony CH-386S-25B                                      */
extern int	machine_at_chicony_ch_386_init(const machine_t *);				/* Chicony CH-386-33H                                       */
/* See above */																/* Chicony CH-386-40H                                       */
/* See above */																/* Chicony CH-486DLC-33H                                    */
/* See above */																/* Chicony CH-486DLC-40H                                    */
extern int	machine_at_chicony_ch_486_33c_init(const machine_t *);			/* Chicony CH-486-25C                                       */
/* See above */																/* Chicony CH-486-33C                                       */

/* Clone Computers */
extern int	machine_at_clone_386_33c_init(const machine_t *);				/* Clone 386-33C                                            */

/* Clover */
extern int	machine_at_clover_486_i_series_init(const machine_t *);			/* Clover 486      -I Series                                */
extern int	machine_at_clover_486_quick_i_series_init(const machine_t *);	/* Clover 486 Quick-I Series                                */
extern int	machine_at_clover_pro_vm486_init(const machine_t *);			/* Clover PRO-VM486                                         */

/* Club American */
extern int	machine_at_club_falcon_init(const machine_t *);					/* Club Falcon 325                                          */
/* See above */																/* Club Falcon 333                                          */
/* See above */																/* Club Falcon 420                                          */
/* See above */																/* Club Falcon 425                                          */
/* See above */																/* Club Falcon 433                                          */
/* See above */																/* Club Falcon 433T                                         */
/* See above */																/* Club Falcon 450                                          */
/* See above */																/* Club Falcon 450T                                         */

/* CMO Micro Systems */
extern int	machine_at_cmo_flb433x_init(const machine_t *);					/* CMO FLB433X                                              */

/* Comex */
/* See below */																/* Comex 486SX/25 VESA                                      */
extern int	machine_at_comex_486dx2_66_init(const machine_t *);				/* Comex 486DX2/66                                          */

/* Commax */
extern int	machine_at_commax_smartbook_iii_init(const machine_t *);		/* Commax SmartBook III                                     */

/* Commodore */
extern int	machine_at_cmdpc_init(const machine_t *);						/* Commodore PC 30 III                                      */
extern int	machine_at_commodore_sl386sx_init(const machine_t *);			/* Commodore SL386SX                                        */
extern int	machine_at_commodore_dt486_init(const machine_t *);				/* Commodore 486SX-25                                       */
/* See above */																/* Commodore 486-33C                                        */
/* See above */																/* Commodore PC DT 486SX-25                                 */
/* See above */																/* Commodore DT 486-33C                                     */
extern int	machine_at_commodore_t486_init(const machine_t *);				/* Commodore Tower 486                                      */
extern int	machine_at_commodore_t486_50c_init(const machine_t *);			/* Commodore T 486 - 50C                                    */
extern int	machine_at_commodore_t486_66c_init(const machine_t *);			/* Commodore T 486 - 66C (BIOS v1.01)                       */
extern int	machine_at_commodore_t486_66c2_init(const machine_t *);			/* Commodore T 486 - 66C (BIOS v1.03)                       */

/* Comp & Soft */
extern int	machine_at_comp_n_soft_486_33c256_init(const machine_t *);		/* Comp & Soft CS 486/33C256                                */
extern int	machine_at_comp_n_soft_486_25sx256_vlb_init(const machine_t *);	/* Comp & Soft CS 486/25SX256-VLB                           */
extern int	machine_at_comp_n_soft_58660c512vlb_init(const machine_t *);	/* Comp & Soft CS 58660C512VLB                              */

/* CompuAdd */
extern int	machine_at_compuadd_express_scalable_init(const machine_t *);	/* CompuAdd Express 325DX  Scalable                         */
/* See above */																/* CompuAdd Express 333DX  Scalable                         */
/* See above */																/* CompuAdd Express 340DX  Scalable                         */
/* See above */																/* CompuAdd Express 440DLC Scalable                         */
/* See above */																/* CompuAdd Express 425SX  Scalable                         */
/* See above */																/* CompuAdd Express 425DX  Scalable                         */
/* See above */																/* CompuAdd Express 433DX  Scalable                         */
/* See above */																/* CompuAdd Express 466DX2 Scalable                         */
extern int	machine_at_compuadd_c4100d_init(const machine_t *);				/* CompuAdd C4100D                                          */
/* See above */																/* CompuAdd C466D  Desktop                                  */
extern int	machine_at_compuadd_c466d_init(const machine_t *);				/* CompuAdd C466D                                           */
extern int	machine_at_compuadd_cp90p_init(const machine_t *);				/* CompuAdd CP90p  Mini-Tower                               */
/* See machine_at_compuadd_cp75p_init  */									/* CompuAdd CP90p  Mini-Tower (1.00.12.AX1)                 */
/* See machine_at_compuadd_cp100p_init */									/* CompuAdd CP90p  Mini-Tower ( 0.7.02.BR0)                 */
/* See machine_at_compuadd_cp90p_init  */									/* CompuAdd CP90p  Tower                                    */
/* See machine_at_compuadd_cp75p_init  */									/* CompuAdd CP90p  Tower      (1.00.12.AX1)                 */
/* See machine_at_compuadd_cp100p_init */									/* CompuAdd CP90p  Tower      ( 0.7.02.BR0)                 */
extern int	machine_at_compuadd_cp75p_init(const machine_t *);				/* CompuAdd CP75p  Mini-Tower                               */
/* See above */																/* CompuAdd CP75p  Tower                                    */
extern int	machine_at_compuadd_cp100p_init(const machine_t *);				/* CompuAdd CP100p Minitower                                */
/* See above */																/* CompuAdd CP100p Tower                                    */

/* Compudyne */
extern int	machine_at_compudyne_486_init(const machine_t *);				/* Compudyne 486DX/33 Multimedia System                     */
/* See above */																/* Compudyne SCI4DX2-66                                     */
/* See above */																/* Compudyne 486 System                                     */

/* CompuLink Research */
extern int	machine_at_clr_infinity_p5_init(const machine_t *);				/* CLR Infinity P5-75E                                      */
/* See above */																/* CLR Infinity P5-75H                                      */
/* See above */																/* CLR Infinity P5-100EDO                                   */
/* See above */																/* CLR Infinity P5-120EDO                                   */
/* See above */																/* CLR Infinity P5-133EDO                                   */
/* See above */																/* CLR Infinity P5-166EDO                                   */
extern int	machine_at_clr_infinity_p5d_init(const machine_t *);			/* CLR Infinity P5D100E                                     */
/* See above */																/* CLR Infinity P5D120EDO                                   */
/* See above */																/* CLR Infinity P5D150EDO                                   */

/* Computer (LOCAL RETAILER) */
extern int	machine_at_computer_pentium_133_mhz_init(const machine_t *);	/* Computer Pentium 133 MHz                                 */

/* Computer Market Place */
extern int	machine_at_computer_market_place_486_init(const machine_t *);	/* Computer Market Place Ultra 486-25                       */

/* Computer Products United */
extern int	machine_at_cpu_386_20_25_init(const machine_t *);				/* CPU 386/20                                               */
/* See above */																/* CPU 386/25                                               */

/* Computer Sales Professional */
/* See Quantex */

/* Computer Square (LOCAL RETAILER) */
extern int	machine_at_computer_square_pcn1_init(const machine_t *);		/* Computer Square PCN1 486DX2/66                           */

/* CompuTrend */
/* See Premio */

/* Comtrade */
extern int	machine_at_comtrade_486_init(const machine_t *);				/* Comtrade Multimedia (VL-Bus)            66               */
/* See above */																/* Comtrade VL-Bus Best Buy                66               */
extern int	machine_at_comtrade_p590_init(const machine_t *);				/* Comtrade Professional                P5/90               */
extern int	machine_at_comtrade_pci_566_init(const machine_t *);			/* Comtrade PCI Best Buy                  566               */
/* See above */																/* Comtrade CAD/Publishing                566               */
/* See machine_at_comtrade_p590_init */										/* Comtrade CAD/Publishing                590               */
extern int	machine_at_comtrade_p75_p100_init(const machine_t *);			/* Comtrade Multimedia Tornado 4X         P75               */
/* See above */																/* Comtrade Multimedia      Dream Machine P100              */
extern int	machine_at_comtrade_multimedia_mpeg_init(const machine_t *);	/* Comtrade Multimedia Best Buy                             */
extern int	machine_at_comtrade_multimedia_mpeg2_init(const machine_t *);	/* Comtrade Multimedia Best Buy                             */
/* See above */																/* Comtrade Multimedia MPEG Dream Machine                   */
extern int	machine_at_comtrade_3d_game_station_8x_init(const machine_t *);	/* Comtrade 3D Game    Station 8X                           */
/* See above */																/* Comtrade Artists         Dream Machine                   */
/* See above */																/* Comtrade Hyperspeed Multimedia                           */
extern int	machine_at_comtrade_wide_scsi_init(const machine_t *);			/* Comtrade Wide SCSI Powerstation                          */

/* Cornell Computer Systems */
extern int	machine_at_cornell_power_pak_init(const machine_t *);			/* Cornell Power Pak                                        */
extern int	machine_at_cornell_power_pak2_init(const machine_t *);			/* Cornell Power Pak                                        */
extern int	machine_at_cornell_power_pak3_init(const machine_t *);			/* Cornell Power Pak                                        */
extern int	machine_at_cornell_p5_60_pci_init(const machine_t *);			/* Cornell P5-60 PCI                                        */
extern int	machine_at_cornell_ultima_p100_init(const machine_t *);			/* Cornell Ultima/P100                                      */

/* Cote Computers of Arizona */
extern int	machine_at_cote_386_plus_init(const machine_t *);				/* Cote 386 Plus                                            */

/* CSR */
extern int	machine_at_csr_386_33_init(const machine_t *);					/* CSR 386/33                                               */

/* Cube */
extern int	machine_at_cube_atx_init(const machine_t *);					/* Cube 340 ATX                                             */
/* See above */																/* Cube 425 ATX                                             */
/* See above */																/* Cube 433 ATX                                             */
/* See above */																/* Cube 450 ATX                                             */
/* See above */																/* Cube 466 ATX                                             */

/* CUI */
extern int	machine_at_cui_advantage_486_init(const machine_t *);			/* CUI Advantage 486/25SX                                   */
/* See above */																/* CUI Advantage 486-50CX                                   */

/* CyberMax */
extern int	machine_at_cybermax_ftn386_init(const machine_t *);				/* CyberMax 386/40                                          */
/* See Quantex QP5/100 SM-1 */												/* CyberMax Executive Max P-75                              */
/* See Quantex QP5/100 SM-1 */												/* CyberMax Executive Max P-100                             */

/* Data Storage Marketing */
extern int	machine_at_datastor_isa_vl_init(const machine_t *);				/* DataStor 486-25SX  ISA VL                                */
/* See above */																/* DataStor 486-33SX  ISA VL                                */
/* See above */																/* DataStor 486-33DX  ISA VL                                */
/* See above */																/* DataStor 486-50DX2 ISA VL                                */
/* See above */																/* DataStor 486-66DX2 ISA VL                                */
extern int	machine_at_datastor_p5_66_init(const machine_t *);				/* DataStor P5-66                                           */
extern int	machine_at_datastor_p5_90_init(const machine_t *);				/* DataStor P5-90                                           */
extern int	machine_at_datastor_p5_100_133_166_init(const machine_t *);		/* DataStor P5-100                                          */
/* See above */																/* DataStor P5-133                                          */
/* See above */																/* DataStor P5-166                                          */

/* DataWorld */
extern int	machine_at_dataworld_data_486_dx2_50_init(const machine_t *);	/* DataWorld Data 486/DX2-50                                */

/* Deico */
extern int	machine_at_deico_predator_init(const machine_t *);				/* Deico Predator 386DX/25                                  */
/* See above */																/* Deico Predator 386DX/33                                  */
/* See above */																/* Deico Predator 386DX/40                                  */
/* See above */																/* Deico Predator 486SX/20                                  */
/* See above */																/* Deico Predator 486SX/25                                  */
/* See above */																/* Deico Predator 486DX/25                                  */
/* See above */																/* Deico Predator 486DX/33                                  */
/* See above */																/* Deico Predator 486DX/50                                  */
/* See above */																/* Deico Predator 486DX2/50                                 */
/* See above */																/* Deico Predator 486DX2/66                                 */

/* Dell */
extern int	machine_at_dell_system_486p_init(const machine_t *);			/* Dell System 486P/25                                      */
/* See above */																/* Dell System 486P/33                                      */
/* See above */																/* Dell System 486P/50                                      */
/* See above */																/* Dell System 486P/66                                      */
extern int	machine_at_dell_466_me_init(const machine_t *);					/* Dell          466/ME                                     */
/* See below */																/* Dell Dimension 425SV                                     */
/* See below */																/* Dell Dimension 433V                                      */
/* See below */																/* Dell Dimension 466V                                      */
/* See below */																/* Dell Dimension XPS 450V                                  */
extern int	machine_at_dell_dimension_xps_466v_init(const machine_t *);		/* Dell Dimension XPS 466V                                  */
/* See above */																/* Dell Dimension XPS 4100V                                 */
/* See below */																/* Dell Dimension P60 (P90t BIOS)                           */
/* See below */																/* Dell Dimension P75t                                      */
/* See below */																/* Dell Dimension P90t                                      */
/* See below */																/* Dell Dimension P100t                                     */
/* See below */																/* Dell Dimension P120t                                     */
/* See below */																/* Dell Dimension P133t                                     */
/* See below */																/* Dell Dimension XPS P75c                                  */
/* See below */																/* Dell Dimension XPS P90c                                  */
/* See below */																/* Dell Dimension XPS P100c                                 */
/* See below */																/* Dell Dimension XPS P120c                                 */
extern int	machine_at_dell_dimension_xps_p133c_init(const machine_t *);	/* Dell Dimension XPS P133c                                 */
/* See above */																/* Dell Dimension XPS P166c                                 */
extern int	machine_at_dell_dimension_xps_p166v_init(const machine_t *);	/* Dell Dimension XPS P166v                                 */
/* See above */																/* Dell Dimension XPS P200v                                 */
extern int	machine_at_dell_omniplex_560_566_init(const machine_t *);		/* Dell OmniPlex 560                                        */
/* See above */																/* Dell OmniPlex 566                                        */
/* See below */																/* Dell OptiPlex 433/LV                                     */
extern int	machine_at_dell_optiplex_4100_l_init(const machine_t *);		/* Dell OptiPlex 4100/L                                     */
/* See below */																/* Dell OptiPlex GL+   575                                  */
/* See below */																/* Dell OptiPlex GM+   5100                                 */
/* See below */																/* Dell OptiPlex GXM   5100                                 */
/* See below */																/* Dell OptiPlex GXMT+ 5133                                 */
extern int	machine_at_dell_optiplex_gxmt_init(const machine_t *);			/* Dell OptiPlex GXMT  5133                                 */
/* See above */																/* Dell OptiPlex GXMT  5166                                 */

/* Destiny */
extern int	machine_at_destiny_486_25_init(const machine_t *);				/* Destiny 486/25                                           */

/* DFI (Diamond Flower Industries) */
/* See below */																/* DFI Diamond   P90                                        */
extern int	machine_at_dfi_diamond_p100_init(const machine_t *);			/* DFI Diamond   P100                                       */
extern int	machine_at_dfi_mediabook_5110t_init(const machine_t *);			/* DFI MediaBook 5110T                                      */

/* Diamond Technologies */
extern int	machine_at_diamond_dt_486dx2_50_init(const machine_t *);		/* Diamond DT 486DX2/50                                     */
extern int	machine_at_diamond_dt_486_init(const machine_t *);				/* Diamond DT 486C-40 Multimedia                            */
/* See above */																/* Diamond DT 486DX2-66                                     */
/* See below */																/* Diamond DT 486-66                                        */
extern int	machine_at_diamond_dt_486dx4_100_init(const machine_t *);		/* Diamond DT 486DX4-100                                    */
extern int	machine_at_diamond_dt_p100_cyrix_init(const machine_t *);		/* Diamond DT P100-Cyrix                                    */
extern int	machine_at_diamond_dt100_dt133_init(const machine_t *);			/* Diamond Office    Star   DT100                           */
/* See above */																/* Diamond Office   Master  DT133                           */
/* See above */																/* Diamond Office    Mate     133                           */
/* See above */																/* Diamond Office Intelligent 166                           */

/* Digital (DEC) */
extern int	machine_at_decpc_xl_466d2_v101_init(const machine_t *);			/* Digital   DECpc  XL 466d2        (v1.01) (English)       */
extern int	machine_at_decpc_xl_466d2_20_init(const machine_t *);			/* Digital   DECpc  XL 466d2        (v1.20) (English)       */
extern int	machine_at_decpc_xl_466d2_21_init(const machine_t *);			/* Digital   DECpc  XL 466d2        (v1.21) (English)       */
extern int	machine_at_decpc_xl_466d2_22_init(const machine_t *);			/* Digital   DECpc  XL 466d2        (v1.22) (English)       */
extern int	machine_at_decpc_xl_466d2_init(const machine_t *);				/* Digital   DECpc  XL 466d2        (v2.00) (English)       */
extern int	machine_at_decpc_xl_560_566_init(const machine_t *);			/* Digital   DECpc  XL 560          (v1.01) (English)       */
extern int	machine_at_decpc_xl_560_566_20_init(const machine_t *);			/* Digital   DECpc  XL 560          (v1.20) (English)       */
extern int	machine_at_decpc_xl_560_566_21_init(const machine_t *);			/* Digital   DECpc  XL 560          (v1.21) (English)       */
extern int	machine_at_decpc_xl_560_566_22_init(const machine_t *);			/* Digital   DECpc  XL 560          (v1.22) (English)       */
extern int	machine_at_decpc_xl_560_566_200_init(const machine_t *);		/* Digital   DECpc  XL 560          (v2.00) (English)       */
/* See machine_at_decpc_xl_560_566_init */									/* Digital   DECpc  XL 566          (v1.01) (English)       */
/* See machine_at_decpc_xl_560_566_20_init */								/* Digital   DECpc  XL 566          (v1.20) (English)       */
/* See machine_at_decpc_xl_560_566_21_init */								/* Digital   DECpc  XL 566          (v1.21) (English)       */
/* See machine_at_decpc_xl_560_566_22_init */								/* Digital   DECpc  XL 566          (v1.22) (English)       */
/* See machine_at_decpc_xl_560_566_200_init */								/* Digital   DECpc  XL 566          (v2.00) (English)       */
extern int	machine_at_decpc_xl_590_20_init(const machine_t *);				/* Digital   DECpc  XL 590          (v1.20) (English)       */
extern int	machine_at_decpc_xl_590_21_init(const machine_t *);				/* Digital   DECpc  XL 590          (v1.21) (English)       */
extern int	machine_at_decpc_xl_590_22_init(const machine_t *);				/* Digital   DECpc  XL 590          (v1.22) (English)       */
extern int	machine_at_decpc_xl_590_200_init(const machine_t *);			/* Digital   DECpc  XL 590          (v2.00) (English)       */
extern int	machine_at_decpc_xl_server_init(const machine_t *);				/* Digital   DECpc  XL Server 466d2 (v1.00) (English)       */
/* See machine_at_decpc_xl_466d2_init */									/* Digital   DECpc  XL Server 466d2 (v2.00) (English)       */
/* See machine_at_decpc_xl_560_566_init */									/* Digital   DECpc  XL Server 560   (v1.01) (English)       */
extern int	machine_at_decpc_xl_server_560_566_init(const machine_t *);		/* Digital   DECpc  XL Server 560   (v1.02) (English)       */
extern int	machine_at_decpc_xl_server_560_566_2_init(const machine_t *);	/* Digital   DECpc  XL Server 560   (v1.03) (English)       */
/* See machine_at_decpc_xl_560_566_200_init */								/* Digital   DECpc  XL Server 560   (v2.00) (English)       */
/* See machine_at_decpc_xl_560_566_init */									/* Digital   DECpc  XL Server 566   (v1.01) (English)       */
/* See machine_at_decpc_xl_server_560_566_init */							/* Digital   DECpc  XL Server 566   (v1.02) (English)       */
/* See machine_at_decpc_xl_server_560_566_2_init */							/* Digital   DECpc  XL Server 566   (v1.03) (English)       */
/* See machine_at_decpc_xl_560_566_200_init */								/* Digital   DECpc  XL Server 566   (v2.00) (English)       */
extern int	machine_at_decpc_xl_server_590_init(const machine_t *);			/* Digital   DECpc  XL Server 590   (v1.03) (English)       */
extern int	machine_at_decpc_xl_server_590_4_init(const machine_t *);		/* Digital   DECpc  XL Server 590   (v1.04) (English)       */
/* See machine_at_decpc_xl_590_200_init */									/* Digital   DECpc  XL Server 590   (v2.00) (English)       */
extern int	machine_at_digital_celebris_gl_init(const machine_t *);			/* Digital Celebris GL        5100ST                        */
/* See above */																/* Digital Celebris GL        5120ST                        */
/* See above */																/* Digital Celebris GL        5133ST                        */
/* See above */																/* Digital Celebris GL        5150ST                        */
/* See above */																/* Digital Celebris GL        5166ST                        */

/* Digitech */
extern int	machine_at_digitech_4d33_multimedia_init(const machine_t *);	/* Digitech Opusis 4D33 Multimedia System                   */

/* DirectWave */
extern int	machine_at_directwave_blue_thunder_tr_init(const machine_t *);	/* DirectWave Blue Thunder Triton PT5P120B                  */
extern int	machine_at_directwave_blue_thunder_tr2_init(const machine_t *);	/* DirectWave Blue Thunder Triton PT5P120B                  */
/* See above */																/* DirectWave Blue Thunder Triton PT5P133B                  */
extern int	machine_at_directwave_blue_thunder_init(const machine_t *);		/* DirectWave Blue Thunder        PT5P100B                  */
/* See above */																/* DirectWave Blue Thunder        PT5P100BMVP               */
/* See above */																/* DirectWave Blue Thunder        PT5P133B                  */
/* See above */																/* DirectWave Blue Thunder        PHX133MVP Pro             */
extern int	machine_at_directwave_blue_thunder_ph_init(const machine_t *);	/* DirectWave Blue Thunder        PH166MVP  Pro             */

/* Dolch Computer Systems */
/* See below */																/* Dolch P.A.C. 586                                         */
extern int	machine_at_dolch_a_pac_586_60c_init(const machine_t *);			/* Dolch A-PAC 586-60C                                      */
extern int	machine_at_dolch_pac_586_br0_init(const machine_t *);			/* Dolch PAC 586 (BR0)                                      */

/* DSR (Digital Scientific Research) */
extern int	machine_at_dsr_tiger_386_init(const machine_t *);				/* DSR/Tiger 386                                            */

/* DTK Computer */
extern int	machine_xt_dtk_init(const machine_t *);							/* DTK XT                                                   */
extern int	machine_at_neat_init(const machine_t *);						/* DTK 386SX                                                */
/* See DTK PAM-0038S E-2 */													/* DTK Feat-39M                                             */
/* See DTK PAM-0038S E-2 */													/* DTK QUIN-32                                              */
extern int	machine_at_dtk_quin_35_init(const machine_t *);					/* DTK QUIN-35                                              */
/* See above */																/* DTK QUIN-35 (v1.06)                                      */
extern int	machine_at_dtk_quin_35_203_init(const machine_t *);				/* DTK QUIN-35 (v2.03)                                      */
extern int	machine_at_dtk_quin_54_init(const machine_t *);					/* DTK QUIN-54M/P100                                        */
/* See above */																/* DTK QUIN-54M/P120                                        */
/* See above */																/* DTK QUIN-54M/P133                                        */
/* See above */																/* DTK QUIN-54M/P150                                        */
/* See above */																/* DTK QUIN-54M/P166                                        */
/* See above */																/* DTK QUIN-54 (v1.06)                                      */
extern int	machine_at_dtk_quin_54_111_init(const machine_t *);				/* DTK QUIN-54 (v1.11)                                      */
extern int	machine_at_dtk_quin_54_112_init(const machine_t *);				/* DTK QUIN-54 (v1.12)                                      */
extern int	machine_at_dtk_quin_54_113_init(const machine_t *);				/* DTK QUIN-54 (v1.13)                                      */
extern int	machine_at_dtk_quin_54_122_init(const machine_t *);				/* DTK QUIN-54 (v1.22)                                      */
extern int	machine_at_dtk_quin_54_212_init(const machine_t *);				/* DTK QUIN-54 (v2.12)                                      */
extern int	machine_at_dtk_quin_54_232_init(const machine_t *);				/* DTK QUIN-54 (v2.32)                                      */
extern int	machine_at_dtk_quin_55_amibios_init(const machine_t *);			/* DTK QUIN-55D/P75  (AMIBIOS)                              */
extern int	machine_at_dtk_quin_55_award_bios_init(const machine_t *);		/* DTK QUIN-55D/P75  (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55D/P100 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55D/P100 (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55D/P120 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55D/P120 (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55D/P133 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55D/P133 (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55D/P150 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55D/P150 (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55D/P166 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55D/P166 (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55M/P75  (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55M/P75  (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55M/P100 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55M/P100 (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55M/P120 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55M/P120 (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55M/P133 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55M/P133 (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55M/P150 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55M/P150 (Award BIOS)                           */
/* See DTK QUIN-55D/P75  (AMIBIOS)    */									/* DTK QUIN-55M/P166 (AMIBIOS)                              */
/* See DTK QUIN-55D/P75  (Award BIOS) */									/* DTK QUIN-55M/P166 (Award BIOS)                           */
extern int	machine_at_dtk486_init(const machine_t *);						/* DTK PKM-0038S E-2                                        */
/* See DTK Quin-32 or DTK PAM-0038S E-2 */									/* DTK PAM-0030P                                            */
/* See DTK Quin-35 */														/* DTK PAM-0035S                                            */
/* See DTK Quin-35 */														/* DTK PAM-0035S (v1.06)                                    */
/* See DTK Quin-35 (v2.03) */												/* DTK PAM-0035S (v2.03)                                    */
/* See DTK Quin-54 */														/* DTK PAM-0054I                                            */
/* See DTK Quin-54 */														/* DTK PAM-0054I (v1.06)                                    */
/* See DTK Quin-54 (v1.11) */												/* DTK PAM-0054I (v1.11)                                    */
/* See DTK Quin-54 (v1.12) */												/* DTK PAM-0054I (v1.12)                                    */
/* See DTK Quin-54 (v1.13) */												/* DTK PAM-0054I (v1.13)                                    */
/* See DTK Quin-54 (v1.22) */												/* DTK PAM-0054I (v1.22)                                    */
/* See DTK Quin-54 (v2.12) */												/* DTK PAM-0054I (v2.12)                                    */
/* See DTK Quin-54 (v2.32) */												/* DTK PAM-0054I (v2.32)                                    */
/* See DTK QUIN-55       (AMIBIOS) */										/* DTK PAM-0055I     (AMIBIOS)                              */
extern int	machine_at_dtk_dcn_4t66m_4t66p_init(const machine_t *);			/* DTK DCN-4T66M                                            */
/* See above */																/* DTK DCN-4T66P                                            */
extern int	machine_at_dtk_dtn_4t100p_init(const machine_t *);				/* DTK DTN-4T100P                                           */

/* Duracom Computer Systems */
extern int	machine_at_duracom_desksaver_486_vesa_init(const machine_t *);	/* Duracom Multimedia DeskSaver 486/33SX                    */
/* See above */																/* Duracom            DeskSaver 486 VESA                    */
extern int	machine_at_duracom_desksaver_pentium_init(const machine_t *);	/* Duracom            DeskSaver Pentium-PCI                 */
extern int	machine_at_duracom_586_66_init(const machine_t *);				/* Duracom                      586/66                      */
extern int	machine_at_duracom_filepro_586_90_init(const machine_t *);		/* Duracom              FilePro 586/90                      */
extern int	machine_at_duracom_travelpro_nbac_init(const machine_t *);		/* Duracom TravelPro       NBM  486/33DX   Monochrome       */
/* See above */																/* Duracom TravelPro       NBC  486/33DX  Passive Color     */
/* See above */																/* Duracom TravelPro       NBAC 486/33DX   Active Color     */
/* See above */																/* Duracom TravelPro       NBM  486/66DX2  Monochrome       */
/* See above */																/* Duracom TravelPro       NBC  486/66DX2 Passive Color     */
/* See above */																/* Duracom TravelPro       NBAC 486/66DX2  Active Color     */
extern int	machine_at_duracom_5110_init(const machine_t *);				/* Duracom 5110D                                            */
/* See above */																/* Duracom 5110                                             */

/* Dyna Micro */
extern int	machine_at_dyna_micro_dm486dx_250_init(const machine_t *);		/* Dyna Micro DMS486DX/250                                  */
extern int	machine_at_dyna_system_466_init(const machine_t *);				/* Dyna System 466                                          */

/* Dynamic Decisions */
extern int	machine_at_dynex_486_init(const machine_t *);					/* Dynex 486                                                */

/* EasyData (GCH): */
extern int	machine_at_easydata_486dx_2_66_init(const machine_t *);			/* EasyData 486DX-2/66                                      */

/* Edge Technology */
/* See Micron Electronics */

/* Eltech Research */
extern int	machine_at_eltech_model_4500_dx2_init(const machine_t *);		/* Eltech Model 4500 DX2                                    */
extern int	machine_at_eltech_model_4200_init(const machine_t *);			/* Eltech Model 4200                                        */
/* See above */																/* Eltech Model 4330                                        */

/* Empac International */
extern int	machine_at_empac_saber_p54_100_init(const machine_t *);			/* Empac Saber P54-100                                      */
/* See above */																/* Empac Talon  HS-100                                      */

/* EPS Technologies */
extern int	machine_at_eps_p60_phantom_init(const machine_t *);				/* EPS             P60 Phantom                              */
extern int	machine_at_eps_p90_explorer_vl_pci_init(const machine_t *);		/* EPS             P90 Explorer (VLB/PCI)                   */
extern int	machine_at_eps_p90_explorer_pci_init(const machine_t *);		/* EPS             P90 Explorer (PCI-only)                  */
/* See above */																/* EPS             P90 Predator                             */
extern int	machine_at_eps_pinnacle_p90_p133_init(const machine_t *);		/* EPS Pinnacle    P90                                      */
/* See above */																/* EPS Pinnacle    P120                                     */
/* See above */																/* EPS Pinnacle    P133                                     */
/* See above */																/* EPS Evolution   P-166                                    */
/* See above */																/* EPS Evolution  LP-133                                    */
/* See above */																/* EPS Evolution XLP-166                                    */

/* Epson */
extern int	machine_at_epson_endeavor_p60_init(const machine_t *);			/* Epson  Endeavor  P60                                     */
extern int	machine_at_epson_actionnote_880cx_init(const machine_t *);		/* Epson ActionNote 880C                                    */
/* See above */																/* Epson ActionNote 880CX                                   */

/* Ergo Computing */
/* See below */																/* Ergo   PowerBrick  50                                    */
extern int	machine_at_ergo_powerbrick_100_init(const machine_t *);			/* Ergo   PowerBrick 100                                    */
extern int	machine_at_ergo_thunderbrick_init(const machine_t *);			/* Ergo ThunderBrick 100                                    */
/* See above */																/* Ergo ThunderBrick 120                                    */
/* See above */																/* Ergo ThunderBrick 133                                    */

/* ESI Automated Office Systems */
extern int	machine_at_esi_challenger_init(const machine_t *);				/* ESI Challenger                                           */

/* Everest Computer Corporation */
extern int	machine_at_everest_column_333_init(const machine_t *);			/* Everest Column 333 Professional                          */

/* Everex Systems */
extern int	machine_at_everex_tempo_m_init(const machine_t *);				/* Everex Tempo M Series                                    */
extern int	machine_at_everex_step_vl_eisa_init(const machine_t *);			/* Everex Step VL EISA DX-33                                */
/* See above */																/* Everex Step VL EISA DX2-50                               */
/* See above */																/* Everex Step VL EISA DX2-66                               */
extern int	machine_at_everex_step_sp_75_100_init(const machine_t *);		/* Everex Step          SP/75                               */
/* See above */																/* Everex Step          SP/100                              */
extern int	machine_at_everex_step_pro_133_init(const machine_t *);			/* Everex Step Pro         133                              */
extern int	machine_at_everex_step_premier_init(const machine_t *);			/* Everex Step Premier     133                              */
/* See above */																/* Everex Step Premier     166                              */

/* FastMicro */
extern int	machine_at_fastdata_386_sx20_init(const machine_t *);			/* FastMicro FastData 386/SX20                              */

/* First Computer Systems (FCS) */
extern int	machine_at_first_486_66_init(const machine_t *);				/* First 486-66                                             */

/* FiveStar Computers */
extern int	machine_at_zodiac_fivestar_386_33_init(const machine_t *);		/* Zodiac FiveStar 386/33                                   */

/* Fortron/Source */
extern int	machine_at_fortron_netset_433i_init(const machine_t *);			/* Fortron NetSet 433I                                      */

/* Fountain Technologies */
/* See Computer Sales Professional, CyberMax, Inteva, MDS, MicroWarehouse, Pionex, or Quantex */
/* See CyberMax 386/40 */													/* Fountain 386SX                                           */
/* See CyberMax 386/40 */													/* Fountain FTNB386WH-40C                                   */
/* See Computer Sales Professional 486DX2-50 */								/* Fountain FTNMT486DX-50C                                  */
/* See Computer Sales Professional 486DX2-50 */								/* Fountain FTNMT486DX2-66C                                 */

/* Future Micro */
extern int	machine_at_future_micro_ga_486vs_init(const machine_t *);		/* Future Micro GA-486VS                                    */
extern int	machine_at_future_micro_intel_premiere_init(const machine_t *);	/* Future Micro Intel Premiere II                           */
extern int	machine_at_future_micro_advanced_zp_init(const machine_t *);	/* Future Micro Intel Advanced/ZP                           */
extern int	machine_at_future_micro_intel_endeavor_init(const machine_t *);	/* Future Micro Intel Endeavor                              */

/* FutureTech */
extern int	machine_at_futuretech_4414_init(const machine_t *);				/* FutureTech   System   4414                               */
/* See above */																/* FutureTech   System   4414A                              */
extern int	machine_at_futuretech_futuremate_462nv_init(const machine_t *);	/* FutureTech FutureMate 462nV                              */
extern int	machine_at_futuretech_futuremate_fm910t_init(const machine_t *);/* FutureTech FutureMate FM910T                             */
extern int	machine_at_futuretech_futuremate_fm366t_init(const machine_t *);/* FutureTech FutureMate FM366T                             */
extern int	machine_at_futuretech_futuremate_fm559d_init(const machine_t *);/* FutureTech FutureMate FM559D                             */

/* Gain Systems */
extern int	machine_at_gain_master_dx2_66_init(const machine_t *);			/* Gain Master DX2/66                                       */

/* Gateway 2000 */
extern int	machine_at_gateway_4dx2_66v_init(const machine_t *);			/* Gateway 2000 4DX2/66V                                    */
extern int	machine_at_gateway_4dx2_66v_glb05_init(const machine_t *);		/* Gateway 2000 4DX2/66V                  (BIOS upgrade)    */
extern int	machine_at_gateway_p5_60_66_af1_init(const machine_t *);		/* Gateway 2000 P5-60                     (1.00.06.AF1)     */
extern int	machine_at_gateway_p5_60_66_init(const machine_t *);			/* Gateway 2000 P5-60                     (1.00.08.AF2)     */
extern int	machine_at_gateway_p5_60_66_af2t_init(const machine_t *);		/* Gateway 2000 P5-60                     (1.00.10.AF2T)    */
/* See Gateway 2000 P5-60  (1.00.08.AF2) */									/* Gateway 2000 P5-60  Family PC                            */
/* See above */																/* Gateway 2000 P5-66                     (1.00.06.AF1)     */
/* See above */																/* Gateway 2000 P5-66                     (1.00.08.AF2)     */
/* See above */																/* Gateway 2000 P5-66                     (1.00.10.AF2T)    */
/* See Gateway 2000 P5-90  (1.00.09.AX1)     */								/* Gateway 2000 P5-75                     (1.00.09.AX1)     */
/* See Gateway 2000 P5-90  (1.00.12.AX1T)    */								/* Gateway 2000 P5-75                     (1.00.12.AX1T)    */
/* See Gateway 2000 P5-90  (1.00.13.14.AX1T) */								/* Gateway 2000 P5-75                     (1.00.13.AX1T)    */
/* See Gateway 2000 P5-100 (1.00.11.BS0T)    */								/* Gateway 2000 P5-75                     (1.00.11.BS0T)    */
/* See Gateway 2000 P5-100 (1.00.11.BS0T)    */								/* Gateway 2000 P5-75  Family PC          (1.00.11.BS0T)    */
/* See Gateway 2000 P5-100 (1.00.11.BS0T)    */								/* Gateway 2000 P5-75  Best Buy           (1.00.11.BS0T)    */
extern int	machine_at_gateway_p5_cn0t_init(const machine_t *);				/* Gateway 2000 P5-75                             (CN0T)    */
extern int	machine_at_gateway_p5_90_ax1_init(const machine_t *);			/* Gateway 2000 P5-90                     (1.00.09.AX1)     */
extern int	machine_at_gateway_p5_90_ax1t_init(const machine_t *);			/* Gateway 2000 P5-90                     (1.00.12.AX1T)    */
extern int	machine_at_gateway_p5_90_ax2t_init(const machine_t *);			/* Gateway 2000 P5-90                     (1.00.13.AX1T)    */
/* See Gateway 2000 P5-90  (1.00.09.AX1) */									/* Gateway 2000 P5-90  Family PC                            */
/* See Gateway 2000 P5-100 (1.00.11.BS0T)    */								/* Gateway 2000 P5-90  Family PC          (1.00.11.BS0T)    */
/* See above */																/* Gateway 2000 P5-90 XL                  (1.00.09.AX1)     */
/* See above */																/* Gateway 2000 P5-90 XL                  (1.00.12.AX1T)    */
/* See above */																/* Gateway 2000 P5-90 XL                  (1.00.13.AX1T)    */
/* See Gateway 2000 P5-100 (1.00.11.BS0T)    */								/* Gateway 2000 P5-90  Best Buy           (1.00.11.BS0T)    */
/* See Gateway 2000 P5-90  (1.00.12.AX1T) */								/* Gateway 2000 P5-100                    (1.00.12.AX1T)    */
/* See Gateway 2000 P5-90  (1.00.13.14.AX1T) */								/* Gateway 2000 P5-100                    (1.00.13.AX1T)    */
extern int	machine_at_gateway_p5_100_133_init(const machine_t *);			/* Gateway 2000 P5-100                    (1.00.11.BS0T)    */
/* See Gateway 2000 P5-75  (CN0T) */										/* Gateway 2000 P5-100 Family PC                  (CN0T)    */
/* See Gateway 2000 P5-90  (1.00.12.AX1T) */								/* Gateway 2000 P5-100XL                  (1.00.12.AX1T)    */
/* See Gateway 2000 P5-90  (1.00.13.14.AX1T) */								/* Gateway 2000 P5-100XL                  (1.00.13.AX1T)    */
extern int	machine_at_gateway_p5_100_xl_init(const machine_t *);			/* Gateway 2000 P5-100XL                  (1.00.10.BR0T)    */
/* See above */																/* Gateway 2000 P5-120                    (1.00.11.BS0T)    */
/* See above */																/* Gateway 2000 P5-120                            (CN0T)    */
/* See above */																/* Gateway 2000 P5-120 Family PC                  (CN0T)    */
/* See Gateway 2000 P5-100XL (1.00.10.BR0T) */								/* Gateway 2000 P5-120XL                  (1.00.10.BR0T)    */
/* See above */																/* Gateway 2000 P5-133 Best Buy           (1.00.11.BS0T)    */
/* See above */																/* Gateway 2000 P5-133                            (CN0T)    */
/* See above */																/* Gateway 2000 P5-133 Family PC                  (CN0T)    */
/* See Gateway 2000 P5-100XL (1.00.10.BR0T) */								/* Gateway 2000 P5-133XL                  (1.00.10.BR0T)    */
/* See above */																/* Gateway 2000 P5-133XL                          (CN0T)    */
/* See Gateway 2000 P5-100XL (1.00.10.BR0T) */								/* Gateway 2000 10th Anniversary PC                         */
/* See Gateway 2000 P5-100XL (1.00.10.BR0T) */								/* Gateway 2000 Holiday XL                                  */
/* See above */																/* Gateway 2000 P5-166                            (CN0T)    */
/* See above */																/* Gateway 2000 P5-166 Family PC                  (CN0T)    */
/* See above */																/* Gateway 2000 P5-166XL                          (CN0T)    */
/* See above */																/* Gateway 2000 P5-200                                      */
/* See above */																/* Gateway 2000 P5-200 Family PC                            */
/* See above */																/* Gateway 2000 P5-200XL                                    */
/* See above */																/* Gateway 2000 Destination D5-120                          */
/* See above */																/* Gateway 2000 Destination D5-133                          */
/* See above */																/* Gateway 2000 Destination D5-166                (CN0T)    */
/* See above */																/* Gateway 2000 Destination D5-200                (CN0T)    */
extern int	machine_at_gw2kvs_init(const machine_t *);						/* Gateway 2000 G6-180                                      */
/* See above */																/* Gateway 2000 G6-200                                      */

/* Gecco */
extern int	machine_at_gecco_4dx_33_init(const machine_t *);				/* Gecco 4DX-33                                             */

/* Golden Star Technology */
extern int	machine_at_gst_486v_init(const machine_t *);					/* GST             486V                                     */
extern int	machine_at_gst_486v4_init(const machine_t *);					/* GST             486V4                                    */
extern int	machine_at_gst_apogee_p133_init(const machine_t *);				/* GST             Apogee P133                              */
extern int	machine_at_gst_aapogee_p133_init(const machine_t *);			/* GST            Aapogee P133 (Intel AMIBIOS)              */
extern int	machine_at_gst_aapogee_p133_award_init(const machine_t *);		/* GST            Aapogee P133 (Award    BIOS)              */
/* See machine_at_gst_aapogee_p133_init */									/* GST/Micro City Aapogee 8000Pt                            */
extern int	machine_at_gst_aapogee_p166_init(const machine_t *);			/* GST            Aapogee P166                              */

/* GoldStar */
extern int	machine_at_gdc212m_init(const machine_t *);						/* GoldStar GDC-212M                                        */
extern int	machine_at_goldstar386_init(const machine_t *);					/* GoldStar 386                                             */
extern int	machine_at_goldstar_gs433_init(const machine_t *);				/* GoldStar GS433                                           */

/* GRiD Systems */
/* See Tandy Sensation! */													/* GRiD MFP/420s                                            */
/* See Tandy Sensation! */													/* GRiD MFP/420                                             */
/* See Tandy Sensation! */													/* GRiD MFP/425s-II                                         */
/* See Tandy Sensation! */													/* GRiD MFP/433s+ L-Series                                  */
/* See Tandy Sensation! */													/* GRiD MFP/433+  L-Series                                  */
/* See Tandy Sensation! */													/* GRiD MFP/450                                             */
/* See Tandy Sensation! */													/* GRiD MFP/450+  L-Series                                  */
/* See Tandy Sensation! */													/* GRiD MFP/466+  L-Series                                  */

/* HD Systems */
extern int	machine_at_hd_victoria_p133_init(const machine_t *);			/* HD Victoria P133                                         */
extern int	machine_at_hd_victoria_p1332_init(const machine_t *);			/* HD Victoria P133 (original BIOS)                         */
extern int	machine_at_hd_victoria_p_120_p_166_init(const machine_t *);		/* HD Victoria P-120                                        */
/* See above */																/* HD Victoria P-166                                        */

/* Hedaka */
extern int  machine_xt_hed919_init(const machine_t *);						/* Hedaka HED-919                                           */

/* Hertz Computer Corporation */
extern int	machine_at_hertz_486_d50x2e_init(const machine_t *);			/* Hertz 486/D50X2e                                         */
extern int	machine_at_hertz_486_d66x2gi_init(const machine_t *);			/* Hertz 486/D66X2Gi                                        */
extern int	machine_at_hertz_486d66x2ge_init(const machine_t *);			/* Hertz 486/D66X2Ge                                        */
/* See above */																/* Hertz 486/D66X2Ge Multimedia                             */
/* See above */																/* Hertz Z-Optima 486/D66X2e                                */
extern int	machine_at_hertz_z_optima_486_notebook_init(const machine_t *);	/* Hertz Z-Optima 486 Notebook PC                           */
/* See below */																/* Hertz        P90e                                        */
extern int	machine_at_hertz_p100e_init(const machine_t *);					/* Hertz        P100e                                       */
/* See above */																/* Hertz Z-Pent P133e                                       */
/* See above */																/* Hertz Z-Pent P166e                                       */

/* Hewitt Rand */
extern int	machine_at_hewitt_rand_hr_486sx_25c_init(const machine_t *);	/* Hewitt Rand HR 486SX-25C                                 */
/* See above */																/* Hewitt Rand HR 486-50C                                   */
extern int	machine_at_hewitt_rand_hr_p5_90_panther_init(const machine_t *);/* Hewitt Rand HR P5-90  Panther                            */
extern int	machine_at_hewitt_rand_hr_p5_75_100_init(const machine_t *);	/* Hewitt Rand HR P5-75  Tower                              */
/* See above */																/* Hewitt Rand HR P5-100                                    */
extern int	machine_at_hewitt_rand_hr_p5_133_tower_init(const machine_t *);	/* Hewitt Rand HR P5-133 Tower                              */

/* Hewlett Packard */
#if defined(DEV_BRANCH) && defined(USE_VECTRA54)
extern int	machine_at_vectra54_init(const machine_t *);					/* HP Vectra VL 5 Series 4                                  */
#endif
/* See below */																/* HP Pavilion 5030                                         */
/* See below */																/* HP Pavilion 5040                                         */
/* See below */																/* HP Pavilion 7010                                         */
/* See below */																/* HP Pavilion 7020                                         */
/* See below */																/* HP Pavilion 7030                                         */
/* See below */																/* HP Pavilion 7050S                                        */
extern int	machine_at_hp_pavilion_5030_7055_init(const machine_t *);		/* HP Pavilion 7055                                         */
/* See below */																/* HP Pavilion 7090                                         */
extern int	machine_at_hp_pavilion_7130p_init(const machine_t *);			/* HP Pavilion 7130p                                        */
extern int	machine_at_pavl7320_init(const machine_t *);					/* HP Pavilion 7320                                         */
/* See above */																/* HP Pavilion 7330z                                        */
extern int	machine_at_brio80xx_init(const machine_t *);					/* HP Brio 80xx                                             */

/* HiQ (HiQuality Systems) */
extern int	machine_at_hiq_ultimate_433i_init(const machine_t *);			/* HiQ Ultimate 433I                                        */
extern int	machine_at_hiq_multimedia_multimagic_init(const machine_t *);	/* HiQ Multimedia Multimagic System                         */
extern int	machine_at_hiq_p66_pentium_init(const machine_t *);				/* HiQ P66 Pentium Graphics Ultra Station                   */
extern int	machine_at_hiq_4dx33_green_pc_system_init(const machine_t *);	/* HiQ 4DX66 Green PC System                                */
extern int	machine_at_hiq_neptune_ii_p66_pci_init(const machine_t *);		/* HiQ Neptune II P66/PCI                                   */
extern int	machine_at_hiq_neptune_ii_p90_pci_init(const machine_t *);		/* HiQ Neptune II P90/PCI                                   */
extern int	machine_at_hiq_apollo_120_133_init(const machine_t *);			/* HiQ Apollo  120                                          */
/* See above */																/* HiQ Apollo  133                                          */
/* See below */																/* HiQ Saturn Station                                       */
extern int	machine_at_hiq_saturn_p100_init(const machine_t *);				/* HiQ Saturn P100                                          */
extern int	machine_at_hiq_apollo_p133_init(const machine_t *);				/* HiQ Apollo P133                                          */
extern int	machine_at_hiq_p133_p166_mars_station_init(const machine_t *);	/* HiQ        P133 Mars Station                             */
/* See above */																/* HiQ        P166 Mars Station                             */

/* Hi-Tech USA */
extern int	machine_at_hi_tech_usa_dx6900a_1_init(const machine_t *);		/* Hi-Tech USA DX6900A-1                                    */
extern int	machine_at_hi_tech_usa_super_power_mpc_init(const machine_t *);	/* Hi-Tech USA Super Power MPC-120                          */

/* HSB Computer Laboratories */
extern int	machine_at_hsb_ms5120pc_series_64_bit_init(const machine_t *);	/* HSB MS5120PC Series 64-Bit PCI Bus MainBoard             */

/* Humphrey Instruments */
extern int	machine_at_humphrey_instruments_wam5737_init(const machine_t *);/* Humphrey Instruments WAM5737                             */

/* Hymco */
extern int	machine_at_hymco_professional_133_init(const machine_t *);		/* Hymco Professional-133                                   */

/* HyperData Technology */
extern int	machine_at_hyperdata_hyperbook_900a_init(const machine_t *);	/* HyperData HyperBook 900A                                 */

/* Hyundai */
extern int	machine_at_super286tr_init(const machine_t *);					/* Hyundai Super-286TR                                      */
extern int	machine_at_hyundai_466d2_init(const machine_t *);				/* Hyundai 466D2                                            */

/* i Corp */
extern int	machine_at_i_corp_blazer_iis_init(const machine_t *);			/* i Corp Blazer IIs                                        */

/* IDS (International Data Systems) */
extern int	machine_at_ids_466i2_init(const machine_t *);					/* IDS 466i2                                                */

/* Image Microsystems */
extern int	machine_at_image_486dx_33_init(const machine_t *);				/* Image        486DX-33                                    */
extern int	machine_at_image_m_line_486dx2_66vl_init(const machine_t *);	/* Image M-Line 486DX2-66VL                                 */
/* See above */																/* Image 486-DX-33 Vesa Local Bus                           */

/* Infotel */
/* See MidWest Micro or Systemax */

/* Inmac */
extern int	machine_at_inmac_insignia_450sl_init(const machine_t *);		/* Inmac Insignia 450SL                                     */
/* See below */																/* Inmac Insignia 433P                                      */
/* See below */																/* Inmac Insignia 450P                                      */
extern int	machine_at_inmac_insignia_466p_init(const machine_t *);			/* Inmac Insignia 466P                                      */

/* Insight */
extern int	machine_at_insight_486i_init(const machine_t *);				/* Insight 486SX-25                                         */
/* See above */																/* Insight 486DX2-66I                                       */
extern int	machine_at_insight_486dx2_66_vl_init(const machine_t *);		/* Insight 486DX2-66 VL-Bus Multimedia                      */
extern int	machine_at_insight_pci_p60_cd_init(const machine_t *);			/* Insight PCI P60  CD                                      */
extern int	machine_at_insight_pci_p60_mm_init(const machine_t *);			/* Insight PCI P60  MM                                      */
/* See above */																/* Insight P60 PCI  TW                                      */
/* See above */																/* Insight PCI P66  MM                                      */
extern int	machine_at_insight_pci_p90_cd_init(const machine_t *);			/* Insight PCI P90  CD                                      */
extern int	machine_at_insight_pci_p90_mm_init(const machine_t *);			/* Insight PCI P90  MM                                      */
/* See above */																/* Insight P90 Special PCI                                  */
extern int	machine_at_insight_pci_p75_mm_init(const machine_t *);			/* Insight PCI P75  MM                                      */
extern int	machine_at_insight_pci_p100_mm_init(const machine_t *);			/* Insight PCI P100 MM                                      */
/* See above */																/* Insight Hemisphere PCI P120 MM                           */
/* See above */																/* Insight PCI P120 MM                                      */

/* Initiative Technology */
extern int	machine_at_initiative_iti_499vl_init(const machine_t *);		/* Initiative ITI 499VL                                     */
/* See above */																/* Initiative ITI DX2-66                                    */

/* Intelec */
extern int	machine_at_intelec_int_486_50_init(const machine_t *);			/* Intelec INT 486-50                                       */

/* Intelesys */
extern int	machine_at_intelesys_star_75_init(const machine_t *);			/* Intelesys Star 75                                        */

/* International Instrumentation */
extern int	machine_at_blue_max_monolith_486up_25s_init(const machine_t *);	/* Blue Max            Monolith 486UP/25S                   */
extern int	machine_at_blue_max_monolith_4250_diul_init(const machine_t *);	/* Blue Max            Monolith 4250 DIUL                   */
/* See above */																/* Blue Max            Monolith 486D2/66UP                  */
extern int	machine_at_blue_max_monolith_init(const machine_t *);			/* Blue Max Multimedia Monolith                             */
extern int	machine_at_blue_max_monolith2_init(const machine_t *);			/* Blue Max            Monolith                             */
extern int	machine_at_blue_max_monolith_75_init(const machine_t *);		/* Blue Max            Monolith Business Partner P5         */
extern int	machine_at_blue_max_mean_green_machine_init(const machine_t *);	/* Blue Max Mean Green Machine                              */
/* See above */																/* Blue Max                     Business Partner DX 4100    */

/* International Upgrade Source */
extern int	machine_at_intel_pci_premier_init(const machine_t *);			/* International Upgrade Source Intel PCI Premier           */

/* Inteva Microsystems */
/* See Quantex QP5/100 M-4 */												/* Inteva 5/133                                             */

/* Itautec */
extern int	machine_at_itautec_infoway_multimidia_init(const machine_t *);	/* Itautec InfoWay Multimidia                               */

/* ITI Technologies */
extern int	machine_at_iti_business_pro_433v_init(const machine_t *);		/* ITI Business Pro 433V                                    */

/* Iverson Computer Corporation */
extern int	machine_at_iverson_icc_386sx_16_init(const machine_t *);		/* Iverson ICC-386SX/16                                     */

/* JDR Microdevices */
extern int	machine_at_jdr_mct_m486vl_init(const machine_t *);				/* JDR MCT-M486VL-33                                        */
/* See above */																/* JDR MCT-M486VL-66                                        */

/* Jet Research (LOCAL RETAILER) */
extern int	machine_at_jet_algo_486dx2_66_init(const machine_t *);			/* Jet Algo 486DX2/66 Local Bus System                      */

/* Juko Electronics */
extern int	machine_xt_jukopc_init(const machine_t *);						/* Juko XT                                                  */

/* Keydata International */
extern int	machine_at_keydata_key486s_25_isa_init(const machine_t *);		/* Keydata KEY486S-25 ISA                                   */
/* See above */																/* Keydata  KEY486-33 ISA                                   */
extern int	machine_at_keydata_key486sx_25_init(const machine_t *);			/* Keydata KEY486SX-25                                      */
/* See above */																/* Keydata KEY486DX-25                                      */
/* See above */																/* Keydata KEY486DX-33                                      */
/* See above */																/* Keydata KEY486DX2-50                                     */
extern int	machine_at_keydata_486sx_25_keystation_init(const machine_t *);	/* Keydata    486SX/25 Keystation                           */

/* Leading Edge */
extern int	machine_at_leading_edge_d4_dx2_50_init(const machine_t *);		/* Leading Edge D4/DX2-50                                   */
extern int	machine_at_leading_edge_fortiva_4000_init(const machine_t *);	/* Leading Edge Fortiva 4000                                */

/* Lightning Computers */
extern int	machine_at_lightning_omniflex_486sx25_init(const machine_t *);	/* Lightning Omniflex 486SX25                               */
/* See above */																/* Lightning Omniflex 486DX25                               */
/* See above */																/* Lightning Omniflex 486DX33                               */
/* See above */																/* Lightning Omniflex 486DX50                               */
/* See above */																/* Lightning Omniflex 486DX250                              */
/* See above */																/* Lightning Omniflex 486DX266                              */
extern int	machine_at_lightning_thunderbox_init(const machine_t *);		/* Lightning ThunderBox                                     */

/* LodeStar Computer */
extern int	machine_at_lodestar_486dlc_33_init(const machine_t *);			/* LodeStar 486DLC-33                                       */

/* Logisys */
extern int	machine_at_logisys_l_windows_486dx_33_init(const machine_t *);	/* Logisys L-Windows 486DX/33                               */

/* Lowland Electronics (LOCAL RETAILER) */
extern int	machine_at_lowland_486dx4_100_init(const machine_t *);			/* Lowland 486DX4-100                                       */

/* Magic Box (LOCAL RETAILER) */
/* See CompuTrend Premio 486 */												/* Magic Box Power VESA 486DX2-66                           */

/* MagiPro Computers (formerly Magix Computers) */
extern int	machine_at_magix_office_p133_p166_init(const machine_t *);		/* Magix   Multimedia Internet                              */
/* See above */																/* Magix     Office  P133                                   */
/* See above */																/* Magix     Office  P166                                   */
/* See above */																/* MagiPro Multimedia Internet                              */
/* See above */																/* MagiPro Multimedia 133MHz                                */
/* See above */																/* MagiPro Multimedia 166MHz                                */
/* See above */																/* MagiPro   Office  P133                                   */

/* Magix Computers */
/* See MagiPro Computers */

/* Matrix Digital Products */
extern int	machine_at_matrix_486_50_dx2_init(const machine_t *);			/* Matrix 486-50 DX2                                        */
extern int	machine_at_matrix_energy_pro_486_init(const machine_t *);		/* Matrix Energy Pro 486                                    */
extern int	machine_at_eisa_test_init(const machine_t *);					/* EISA TEST MACHINE                                        */

/* Maximus Computers */
/* See below */																/* Maximus Magna             Media        P100              */
extern int	machine_at_maximus_magna_graphics_pro_init(const machine_t *);	/* Maximus Magna Graphics ProMedia Pentium 120              */
/* See above */																/* Maximus Magna  Artist  Pro Multimedia                    */
/* See below */																/* Maximus Magna             Media        P100              */
extern int	machine_at_maximus_magna_graphics_pro2_init(const machine_t *);	/* Maximus Magna Graphics ProMedia Pentium 120              */
/* See above */																/* Maximus Magna  Artist  Pro Multimedia                    */
/* See above */																/* Maximus Magna          ProMedia                          */
/* See above */																/* Maximus Magna Graphics ProMedia                          */
extern int	machine_at_maximus_magna_media_133_166_init(const machine_t *);	/* Maximus Magna             Media       P/133              */
/* See above */																/* Maximus Magna             Media       P/166              */
/* See machine_at_maximus_magna_graphics_pro_init */						/* Maximus Magna Graphics                P/166              */
extern int	machine_at_maximus_magna_scsi_media_init(const machine_t *);	/* Maximus Magna   SCSI      Media       P/166              */
extern int	machine_at_maximus_medianote_init(const machine_t *);			/* Maximus MediaNote                                        */
extern int	machine_at_maximus_powermax_init(const machine_t *);			/* Maximus PowerMax                                         */

/* MDS (Marlow Data Systems) */
/* See Quantex QP5/100 M-4 */												/* MDS    75MHz Pentium                                     */
/* See above */																/* MDS    75MHz 850MB HD PCI                                */
/* See above */																/* MDS   120MHz Pentium  PCI 1.2GB                          */
/* See above */																/* MDS 5/100 CD                                             */
/* See above */																/* MDS 5/100 CD MiniTower                                   */

/* Media On */
extern int	machine_at_media_on_mp60_66_init(const machine_t *);			/* Media On MP60  System                                    */
/* See above */																/* Media On MP66  System                                    */
extern int	machine_at_media_on_mp75_90_100_init(const machine_t *);		/* Media On MP75  System                                    */
/* See above */																/* Media On MP90  System                                    */
/* See above */																/* Media On MP100 System                                    */

/* Mega Computer System */
extern int	machine_at_mega_impact_486sx_25p_init(const machine_t *);		/* Mega Impact 486SX/25+                                    */
extern int	machine_at_mega_r486_33_mpc_init(const machine_t *);			/* Mega R486/33-MPC                                         */
extern int	machine_at_mega_impact_v60pci_plus_init(const machine_t *);		/* Mega Impact V-60PCI+                                     */
extern int	machine_at_mega_eco486dx2_66dp_init(const machine_t *);			/* Mega ECO486DX2/66D+                                      */
extern int	machine_at_mega_impact_486dx4_100dp_init(const machine_t *);	/* Mega Impact 486DX4/100D+                                 */
extern int	machine_at_mega_impact_590pci16d_init(const machine_t *);		/* Mega Impact  590PCI16D                                   */
/* See above */																/* Mega Impact 5133PCI16MT                                  */
extern int	machine_at_mega_horizon_mpc57516d_init(const machine_t *);		/* Mega Horizon MPC57516D                                   */
/* See above */																/* Mega Impact 5133PCI16D                                   */
/* See above */																/* Mega Impact 5166PCI16MT                                  */

/* Memorex Telex */
extern int	machine_at_memorex_telex_celerria_lp90_init(const machine_t *);	/* Memorex Telex Celerria LP90                              */
extern int	machine_at_memorex_telex_celerria_mini_init(const machine_t *);	/* Memorex Telex Celerria Mini Tower                        */

/* Micro Express */
extern int	machine_at_microflex_me486_init(const machine_t *);				/* Micro Express ME 486-50/DX2                              */
extern int	machine_at_microflex_me486_vl_init(const machine_t *);			/* Micro Express ME 486-Local Bus                           */
extern int	machine_at_microflex_init(const machine_t *);					/* Micro Express MicroFLEX 386/DX/33                        */
/* See above */																/* Micro Express MicroFLEX 386/DX/40                        */
/* See above */																/* Micro Express MicroFLEX 486/SX/25                        */
/* See above */																/* Micro Express MicroFLEX 486/DX/25                        */
/* See above */																/* Micro Express MicroFLEX 486/DX/33                        */
/* See above */																/* Micro Express MicroFLEX 486/DX2/50                       */
/* See above */																/* Micro Express MicroFLEX 486/DX2/66                       */
extern int	machine_at_microflex_vl_66_multimedia_init(const machine_t *);	/* Micro Express MicroFlex-VL/Multimedia                    */
/* See above */																/* Micro Express MicroFlex-VL/66                            */
extern int	machine_at_microflex_vl_66g_init(const machine_t *);			/* Micro Express MicroFlex-VL/66                            */
/* See above */																/* Micro Express MicroFlex-VL/66G                           */
extern int	machine_at_microflex_vl_pentium_init(const machine_t *);		/* Micro Express MicroFlex-VL/Pentium                       */
/* See above */																/* Micro Express MicroFlex-VL/P60                           */
/* See above */																/* Micro Express MicroFlex-VL/P66                           */
/* See above */																/* Micro Express MicroFlex-VL/66                            */
extern int	machine_at_microflex_vl_pentium_90_init(const machine_t *);		/* Micro Express MicroFLEX-VL/Pentium/90                    */
extern int	machine_at_microflex_vl_80_init(const machine_t *);				/* Micro Express MicroFlex-VL/80                            */
/* See above */																/* Micro Express MicroFlex-VL/D6                            */
extern int	machine_at_microflex_pci_p100_init(const machine_t *);			/* Micro Express MicroFlex PCI/P100                         */
/* See above */																/* Micro Express MicroFlex PCI/P100 Home                    */
/* See above */																/* Micro Express MicroFlex-686/P120+                        */
/* See above */																/* Micro Express MicroFlex-686/P150+                        */
/* See above */																/* Micro Express MicroFlex-686/P166+                        */
extern int	machine_at_micro_express_nb8266_init(const machine_t *);		/* Micro Express NB8266M                                    */
/* See above */																/* Micro Express NB8266                                     */
extern int	machine_at_micro_express_nb9266_init(const machine_t *);		/* Micro Express NB9266                                     */
/* See above */																/* Micro Express NP92DX4                                    */

/* Micro Generation */
extern int	machine_at_micro_generation_mg50dx2_init(const machine_t *);	/* Micro Generation MG50DX2                                 */
/* See above */																/* Micro Generation LB-25SX                                 */

/* Micro Professionals */
extern int	machine_at_micro_professionals_proteva_init(const machine_t *);	/* Micro Professionals      P5/75  Pro Super Multimedia     */
/* See above */																/* Micro Professionals      P5/90  Pro Super Multimedia     */
/* See above */																/* Micro Professionals      P5/100 Pro Super Multimedia     */
/* See above */																/* Micro Professionals      P5/120 Pro Super Multimedia     */
/* See above */																/* Micro Professionals      P5/133 Pro Super Multimedia     */
/* See above */																/* Micro Professionals Proteva 100     Super Multimedia     */

/* Micro Telesis */
extern int	machine_at_micro_telesis_486_33_init(const machine_t *);		/* Micro Telesis 486/33                                     */

/* Micron Electronics */
extern int	machine_at_micron_466vl_magnum_mpc_init(const machine_t *);		/* Micron 466VL Magnum MPC                                  */
/* See above */																/* Micron 466VL Magnum CD                                   */
/* See above */																/* Micron 486VL WinStation                                  */
/* See above */																/* Micron 486DX4 (VLB)                                      */
extern int	machine_at_micron_p90pci_powerstation_init(const machine_t *);	/* Micron P90PCI PowerStation                               */
/* See above */																/* Micron P90 Home MPC                                      */
extern int	machine_at_micron_home_mpc_amibios_init(const machine_t *);		/* Micron Home MPC P166 (Intel AMIBIOS)                     */
extern int	machine_at_micron_home_mpc_init(const machine_t *);				/* Micron Home MPC P166 (Phoenix  BIOS)                     */
/* See Micron Home MPC P166 (Intel AMIBIOS) */								/* Micron Home MPC P200 (Intel AMIBIOS)                     */
/* See Micron Home MPC P166 (Phoenix  BIOS) */								/* Micron Home MPC P200 (Phoenix  BIOS)                     */
/* See Micron Home MPC P166 (Intel AMIBIOS) */								/* Micron ClientPro P100                                    */
/* See above */																/* Micron ClientPro P120                                    */
/* See above */																/* Micron ClientPro P200                                    */

/* MicroSource */
extern int	machine_at_microsource_486vlb_66_init(const machine_t *);		/* MicroSource Tempest 486VLB-66                            */
extern int	machine_at_microsource_premier_pci_init(const machine_t *);		/* MicroSource Tempest Premier/PCI                          */

/* MicroTech Computer Corporation */
extern int	machine_at_microtech_ultima_xvc_66_init(const machine_t *);		/* MicroTech Ultima XVC/66                                  */

/* MicroWarehouse */
/* See CyberMax 386/40 */													/* MicroWarehouse 386/SX 33                                 */
/* See Computer Sales Professional 486DX2-50 */								/* MicroWarehouse 486/SX 25                                 */

/* MidWest Micro (later Systemax) */
extern int	machine_at_midwest_micro_elite_p5_60_init(const machine_t *);	/* MidWest Micro Elite P5-60                                */
extern int	machine_at_midwest_micro_elite_p5_66_init(const machine_t *);	/* MidWest Micro Elite P5-66                                */
extern int	machine_at_midwest_micro_elite_p5_90_init(const machine_t *);	/* MidWest Micro Elite P5-90                                */
/* See below */																/* MidWest Micro Elite P5-90 (1.00.08.AX1)                  */
extern int	machine_at_midwest_micro_home_p5_90_init(const machine_t *);	/* MidWest Micro Elite   Home  PC P5-90                     */
/* See machine_at_midwest_micro_p5_75_init      */							/* MidWest Micro         Home  PC P5-75  PCI                */
/* See machine_at_midwest_micro_p5_100_120_init */							/* MidWest Micro         Home  PC P5-100 PCI                */
/* See above */																/* MidWest Micro         Home  PC P5-120 PCI                */
/* See machine_at_midwest_micro_p5_133_init     */							/* MidWest Micro         Home  PC P5-133 PCI                */
extern int	machine_at_midwest_micro_p5_75_init(const machine_t *);			/* MidWest Micro        Office PC P5-75  PCI                */
extern int	machine_at_midwest_micro_p5_100_120_init(const machine_t *);	/* MidWest Micro        Office PC P5-100 PCI                */
/* See above */																/* MidWest Micro        Office PC P5-120 PCI                */
extern int	machine_at_midwest_micro_p5_133_init(const machine_t *);		/* MidWest Micro        Office PC P5-133 PCI                */
extern int	machine_at_midwest_micro_p590_init(const machine_t *);			/* MidWest Micro P590    Home  PC                           */
extern int	machine_at_midwest_micro_p5_133_166_init(const machine_t *);	/* MidWest Micro P5-133 Office PC                           */
/* See above */																/* MidWest Micro P5-166 Office PC                           */

/* Milkyway Computer Products */
extern int	machine_at_milkyway_myriadbook_466_init(const machine_t *);		/* Milkyway MyriadBook/466                                  */

/* MIS Computer Systems */
extern int	machine_at_mis_m466t_init(const machine_t *);					/* MIS M466T                                                */

/* MiTAC */
extern int	machine_at_american_mitac_486_init(const machine_t *);			/* American Mitac D4033                                     */
/* See above */																/* MiTAC D4125                                              */

/* MITS Systems (Telemart) */
extern int	machine_at_mits_hsy_88_486dx_50_init(const machine_t *);		/* MITS HSY-88-486DX-50                                     */

/* Mitsuba */
extern int	machine_at_mitsuba_pro_upgradable_init(const machine_t *);		/* Mitsuba Professional Upgradable                          */
extern int	machine_at_mitsuba_pro_upgradable_4sx_init(const machine_t *);	/* Mitsuba Pro          Upgradable4SX/25                    */
extern int	machine_at_mitsuba_multi_pro_486dx_33_init(const machine_t *);	/* Mitsuba Multi-Pro            486DX/33                    */
extern int	machine_at_mitsuba_professional_pentium_init(const machine_t *);/* Mitsuba Professional Pentium                             */
extern int	machine_at_mitsuba_mit486_green_pc_init(const machine_t *);		/* Mitsuba MIT486 Green PC                                  */
/* See machine_at_mitsuba_multi_pro_486dx_33_init */						/* Mitsuba VESA-DX4                                         */
extern int	machine_at_mitsuba_fileserver_p_90_init(const machine_t *);		/* Mitsuba Fileserver-P-90                                  */
extern int	machine_at_mitsuba_executive_pentium_pc_init(const machine_t *);/* Mitsuba Executive Pentium-PC                             */
/* See above */																/* Mitsuba Executive    P-100                               */
/* See above */																/* Mitsuba Executive    P-133                               */
/* See above */																/* Mitsuba Premier System 166                               */

/* Motherboard Discount Center */
extern int	machine_at_motherboard_shuttle_init(const machine_t *);			/* Motherboard Discount Center Shuttle 486DX2-80            */

/* MPC Technologies */
extern int	machine_at_mpc_cd_book_init(const machine_t *);					/* MPC CD-Book                                              */

/* MS Engineering */
extern int	machine_at_mse_486eisa_50mhz_init(const machine_t *);			/* MSE 486EISA-50MHz                                        */
/* See below */																/* MSE486DX-33V                                             */
/* See below */																/* MSE486DX2-50V                                            */
extern int	machine_at_mse486dx2_66v_init(const machine_t *);				/* MSE486DX2-66V                                            */
extern int	machine_at_mse_pentium_p_init(const machine_t *);				/* MSE Pentium-P                                            */

/* MultiMicro */
extern int	machine_at_multimicro_mmi_3364t_init(const machine_t *);		/* MultiMicro MMI-3364T                                     */

/* Multiwave Technology */
extern int	machine_at_multiwave_ultra_power_init(const machine_t *);		/* Multiwave Ultra Power                                    */
/* See above */																/* Multiwave SOHO MPEG System                               */

/* Myoda */
extern int	machine_at_myoda_486sx_25b_init(const machine_t *);				/* Myoda 486SX-25b                                          */
/* See Computer Square */													/* Computer Square Patriot PCN1 486DX2/66                   */

/* Naga Systems */
extern int	machine_at_naga_windows_workstation_init(const machine_t *);	/* Naga Windows Workstation                                 */

/* National MicroComputers */
extern int	machine_at_nmc_universal_pro_system_init(const machine_t *);	/* NMC Universal Pro System                                 */
extern int	machine_at_nmc_universal_pro_system_466_init(const machine_t *);/* NMC Universal Pro-System 466                             */
extern int	machine_at_nmc_expert_p66_init(const machine_t *);				/* NMC Expert-System P66                                    */
extern int	machine_at_nmc_expert_pcw_init(const machine_t *);				/* NMC Expert System Plus 120                               */
/* See above */																/* NMC Expert System Plus 133                               */
/* See above */																/* NMC PCW P100                                             */
/* See above */																/* NMC Expert Plus 133                                      */
/* See above */																/* NMC Expert Plus 166                                      */

/* National MicroSystems */
extern int	machine_at_national_micro_flash_486_50_init(const machine_t *);	/* National MicroSystems Flash 486-50                       */
extern int	machine_at_national_micro_486dx2_50_lb_init(const machine_t *);	/* National MicroSystems Flash 486DX2-50 LB                 */
extern int	machine_at_national_micro_486dx_33mpc_init(const machine_t *);	/* National MicroSystems Flash 486-33MPC                    */

/* NCC Computer SYstems */
extern int	machine_at_ncc_impact_v_init(const machine_t *);				/* NCC Impact V                                             */

/* NCR (National Cash Register) */
extern int	machine_at_ncr_3333_init(const machine_t *);					/* NCR System 3000 Model 3333                               */
extern int	machine_at_ncr_3260_init(const machine_t *);					/* NCR 3260                                                 */
extern int	machine_at_ncr_3346_init(const machine_t *);					/* NCR 3346 (AT&T Globalyst 590)                            */
extern int	machine_at_ncr_3346_04_init(const machine_t *);					/* NCR 3346 (AT&T Globalyst 590) (1.00.04.AU0B)             */
extern int	machine_at_ncr_3346_05_init(const machine_t *);					/* NCR 3346 (AT&T Globalyst 590) (1.00.05.AU0B)             */
extern int	machine_at_ncr_3346_09_init(const machine_t *);					/* NCR 3346 (AT&T Globalyst 590) (1.00.09.AU0 )             */
extern int	machine_at_ncr_3356_init(const machine_t *);					/* NCR 3356 (AT&T Globalyst 600)                            */
extern int	machine_at_ncr_3356_beta_init(const machine_t *);				/* NCR 3356 (AT&T Globalyst 600) (BETA/NFR)                 */
extern int	machine_at_ncr_3356_07_init(const machine_t *);					/* NCR 3356 (AT&T Globalyst 600) (1.00.07.BF0B)             */
extern int	machine_at_ncr_3356_08_init(const machine_t *);					/* NCR 3356 (AT&T Globalyst 600) (1.00.08.BF0B)             */
extern int	machine_at_ncr_3249_init(const machine_t *);					/* NCR 3249                                                 */
extern int	machine_at_ncr_3249_06_init(const machine_t *);					/* NCR 3249                      (1.00.06.CH0 )             */
extern int	machine_at_ncr_3349_init(const machine_t *);					/* NCR 3349                                                 */
extern int	machine_at_ncr_3349_06_init(const machine_t *);					/* NCR 3349                      (1.00.06.CN0 )             */
extern int	machine_at_ncr_3259_init(const machine_t *);					/* NCR 3259                                                 */
extern int	machine_at_ncr_3259_09_init(const machine_t *);					/* NCR 3259                      (1.00.09.DL0 )             */
extern int	machine_at_ncr_3269_init(const machine_t *);					/* NCR 3269                                                 */

/* NEC Technologies */
extern int	machine_at_nec_powermate_486i_init(const machine_t *);			/* NEC PowerMate 486SX/33i                                  */
/* See above */																/* NEC PowerMate 486/33i                                    */
/* See above */																/* NEC PowerMate 486/50i                                    */
extern int	machine_at_nec_image_425_433_466_init(const machine_t *);		/* NEC Image 425                                            */
/* See above */																/* NEC Image 433                                            */
/* See above */																/* NEC Image 466                                            */
/* See above */																/* NEC Image 466es                                          */
/* See above */																/* NEC Image 4100es                                         */
/* See NEC PowerMate P60D */												/* NEC Image P60D                                           */
/* See above */																/* NEC Image P60M                                           */
/* See NEC Image 4100es */													/* NEC PowerMate 466D                                       */
/* See above */																/* NEC PowerMate 4100M                                      */
extern int	machine_at_nec_powermate_p60d_init(const machine_t *);			/* NEC PowerMate P60D                                       */
/* See above */																/* NEC PowerMate P60M                                       */
extern int	machine_at_powermate_v_init(const machine_t *);					/* NEC PowerMate V100                                       */
/* See NEC Ready 9520 */													/* NEC PowerMate P133                                       */
extern int	machine_at_nec_powermate_p166_init(const machine_t *);			/* NEC PowerMate P166                                       */
/* See NEC PowerMate P60D */												/* NEC Ready P60D                                           */
/* See NEC PowerMate P60M */												/* NEC Ready P60M                                           */
/* See NEC PowerMate V100 */												/* NEC Ready 7022                                           */
/* See above */																/* NEC Ready 9022                                           */
extern int	machine_at_nec_ready_9520_init(const machine_t *);				/* NEC Ready 9520                                           */
extern int	machine_at_nec_ready_9520_1007_init(const machine_t *);			/* NEC Ready 9520 (1.00.07.CA0K)                            */
/* See machine_at_nec_ready_9520_init */									/* NEC Ready 9552 (Ready 9520 BIOS)                         */

/* NETiS */
extern int	machine_at_netis_isa_425sx_init(const machine_t *);				/* NETiS ISA               425SX                            */
extern int	machine_at_netis_ultra_winstation_init(const machine_t *);		/* NETiS Ultra WinStation N433L                             */
/* See above */																/* NETiS Ultra WinStation N466L                             */
/* See below */																/* NETiS                  N425VL                            */
extern int	machine_at_netis_n4d266vl_init(const machine_t *);				/* NETiS                  N4D266VL                          */
extern int	machine_at_netis_n566vl_init(const machine_t *);				/* NETiS Pentium          N566VL                            */
extern int	machine_at_netis_486_vesa_green_machine_init(const machine_t *);/* NETiS 486 VESA Green Machine                             */
extern int	machine_at_netis_n566p_init(const machine_t *);					/* NETiS                  N566P                             */
/* See above */																/* NETiS                  N566   Best Buy                   */
/* See above */																/* NETiS Pentium          N566   Best Buy                   */
/* See above */																/* NETiS                  N566M                             */
extern int	machine_at_netis_n590p_pci_system_init(const machine_t *);		/* NETiS                  N590P  PCI System                 */
extern int	machine_at_netis_n5120p_powerstation_init(const machine_t *);	/* NETiS                  N5120P PowerStation               */
extern int	machine_at_netis_n5120p_powerstation2_init(const machine_t *);	/* NETiS                  N5120P PowerStation               */
extern int	machine_at_netis_budget_n5100p_init(const machine_t *);			/* NETiS           Budget N5120P                            */
extern int	machine_at_netis_n575_media_init(const machine_t *);			/* NETiS                  N575   Media                      */

/* Northgate Computer Systems */
extern int	machine_at_northgate_486e_init(const machine_t *);				/* Northgate 486e                                           */
extern int	machine_at_northgate_486zxp_init(const machine_t *);			/* Northgate Elegance ZXP                                   */
extern int	machine_at_northgate_486szxp_init(const machine_t *);			/* Northgate SlimLine ZXP                                   */
extern int	machine_at_northgate_superb_init(const machine_t *);			/* Northgate Superb                                         */
extern int	machine_at_northgate_486vl_init(const machine_t *);				/* Northgate 486VL                                          */
extern int	machine_at_northgate_zxp_eisa_vesa_init(const machine_t *);		/* Northgate ZXP EISA VESA                                  */

/* Novacor */
extern int	machine_at_novacor_novas_486sx_20_init(const machine_t *);		/* Novacor Novas 486SX-20                                   */
extern int	machine_at_novacor_novas_486_dx2_50_init(const machine_t *);	/* Novacor Novas OPTimum 486 DX2-50                         */
extern int	machine_at_novacor_novas_init(const machine_t *);				/* Novacor Novas                                            */
extern int	machine_at_novacor_nova_pentium_90_init(const machine_t *);		/* Novacor Nova  Pentium                                    */

/* Occidental Systems */
extern int	machine_at_occidental_init(const machine_t *);					/* Occidental 25MHz 486SX                                   */
/* See above */																/* Occidental 33MHz 486DX                                   */
/* See above */																/* Occidental 25MHz 486DX                                   */
/* See above */																/* Occidental 33MHz 486DX                                   */
/* See above */																/* Occidental 50MHz 486DX2                                  */
/* See above */																/* Occidental 66MHz 486DX2                                  */

/* Olivetti */
extern int	machine_olim24_init(const machine_t *);							/* Olivetti        M24                                      */
extern int	machine_at_olivetti_modulo_m4_82_init(const machine_t *);		/* Olivetti Modulo M4-82                                    */

/* Osicom Technologies */
extern int	machine_at_osicom_i466_mod_420_init(const machine_t *);			/* Osicom i466 MOD 420                                      */

/* Pacific Coast Micro */
extern int	machine_at_pacific_intel_486_vlb_init(const machine_t *);		/* Pacific Coast Micro Intel 486 VLB                        */

/* Packard Bell */
/* See machine_at_pb410a_init */											/* Packard Bell 486DX/33                                    */
/* See machine_at_pb520r_init */											/* Packard Bell Accel 1602D                                 */
/* See machine_at_pb520r_init */											/* Packard Bell Accel 1707D                                 */
extern int	machine_at_pb450_init(const machine_t *);						/* Packard Bell Accel 1728D                                 */
/* See machine_at_pb450_init  */											/* Packard Bell Accel 66 Multimedia                         */
/* See machine_at_pb450_init  */											/* Packard Bell CD TV                                       */
/* See machine_at_pb450_init  */											/* Packard Bell Executive 8707D                             */
/* See machine_at_pb520r_init */											/* Packard Bell Executive 560                               */
/* See machine_at_pb570_init  */											/* Packard Bell Executive 590T                              */
/* See machine_at_pb540_init  */											/* Packard Bell Force 2738 D/4                              */
/* See machine_at_pb540_init  */											/* Packard Bell Force 2742 T/4                              */
/* See machine_at_pb540_init  */											/* Packard Bell Force 443CD                                 */
/* See machine_at_pb570_init  */											/* Packard Bell Force 482CDT                                */
/* See machine_at_pb570_init  */											/* Packard Bell Force 860CD                                 */
/* See machine_at_pb570_init  */											/* Packard Bell Force 872CDT                                */
/* See machine_at_pb640_init  */											/* Packard Bell Force 1998CDT                               */
/* See machine_at_pb640_init  */											/* Packard Bell Force 1999CDT                               */
extern int	machine_at_pb520_init(const machine_t *);						/* Packard Bell Legend 5000                                 */
/* See machine_at_pb450_init  */											/* Packard Bell Legend 10CD                                 */
/* See machine_at_pb450_init  */											/* Packard Bell Legend 18CD                                 */
/* See machine_at_pb450_init  */											/* Packard Bell Legend 20CD                                 */
extern int	machine_at_pb540_init(const machine_t *);						/* Packard Bell Legend 100CD                                */
/* See above */																/* Packard Bell Legend 105CD                                */
/* See above */																/* Packard Bell Legend 110CDT                               */
/* See machine_at_pb450_init  */											/* Packard Bell Legend 140CDT                               */
extern int	machine_at_pb520r_init(const machine_t *);						/* Packard Bell Legend 300CD                                */
/* See machine_at_pb520r_init */											/* Packard Bell Legend 322CDT                               */
/* See machine_at_pb540_init  */											/* Packard Bell Legend 436CDT                               */
extern int	machine_at_pb570_init(const machine_t *);						/* Packard Bell Legend 401CD                                */
/* See above */																/* Packard Bell Legend 402CD                                */
/* See above */																/* Packard Bell Legend 403CD                                */
/* See above */																/* Packard Bell Legend 406CD                                */
/* See above */																/* Packard Bell Legend 408CD                                */
/* See above */																/* Packard Bell Legend 410CDT                               */
/* See above */																/* Packard Bell Legend 418CDT                               */
/* See above */																/* Packard Bell Legend 423CDT                               */
/* See above */																/* Packard Bell Legend 812CD (Intel AMIBIOS)                */
/* See above */																/* Packard Bell Legend 814CD (Intel AMIBIOS)                */
/* See above */																/* Packard Bell Legend 823CDT                               */
/* See above */																/* Packard Bell Legend 824CDT                               */
/* See below */																/* Packard Bell Legend 994CDT                               */
/* See below */																/* Packard Bell Legend 3540                                 */
/* See below */																/* Packard Bell Legend 4610                                 */
/* See below */																/* Packard Bell Legend 5385z                                */
extern int	machine_at_pb410a_init(const machine_t *);						/* Packard Bell Legend 760 Supreme                          */
/* See above */																/* Packard Bell Legend 790 Supreme                          */
/* See machine_at_pb520r_init */											/* Packard Bell Legend 60CD Supreme                         */
/* See machine_at_pb540_init  */											/* Packard Bell Legend 70CD Supreme                         */
/* See below */																/* Packard Bell Legend 106CDT Supreme                       */
/* See below */																/* Packard Bell Legend 108CDT Supreme                       */
/* See below */																/* Packard Bell Legend 117 Supreme                          */
extern int	machine_at_pb640_init(const machine_t *);						/* Packard Bell Designer Tower                              */
/* See machine_at_pb450_init  */											/* Packard Bell 486DX2/66 Multimedia System                 */
/* See machine_at_pb540_init  */											/* Packard Bell Multimedia Pentium PC                       */
/* See machine_at_pb570_init  */											/* Packard Bell Multi-Media Corner 90 (C90)                 */
/* See machine_at_pb640_init  */											/* Packard Bell Multimedia 70106D                           */
/* See above */																/* Packard Bell Multi-Media 70157C                          */
/* See above */																/* Packard Bell Multi-Media 70159D                          */
/* See above */																/* Packard Bell Multimedia D160                             */
/* See above */																/* Packard Bell Microsoft Station                           */
/* See machine_at_pb450_init  */											/* Packard Bell Pack-Mate 28 Plus                           */
/* See machine_at_pb520r_init */											/* Packard Bell Pack-Mate 3960CD                            */
/* See machine_at_pb540_init  */											/* Packard Bell Pack-Mate 3987CD                            */
/* See above */																/* Packard Bell Pack-Mate 4990CD                            */
/* See machine_at_pb520_init  */											/* Packard Bell Pentium Computer                            */
/* See machine_at_pb570_init  */											/* Packard Bell Pentium 100 Designer Tower                  */
/* See machine_at_pb640_init  */											/* Packard Bell Platinum I (Intel AMIBIOS)                  */
/* See machine_at_pb640_init  */											/* Packard Bell Platinum III                                */
/* See above */																/* Packard Bell Platinum X                                  */
/* See above */																/* Packard Bell Platinum XI                                 */
/* See above */																/* Packard Bell Platinum XXI                                */
/* See machine_at_pb450_init  */											/* Packard Bell Pro 66TV Multimedia Computer                */
/* See machine_at_pb450_init  */											/* Packard Bell Spectria 9012                               */
#ifdef EMU_DEVICE_H
extern const device_t	*at_pb640_get_device(void);
#endif
extern int	machine_at_pb680_init(const machine_t *);						/* Packard Bell PB680                                       */

/* PacTron Integration */
extern int	machine_at_packtron_daytonawin_120nx_init(const machine_t *);	/* PacTron DaytonaWin-120NX                                 */
extern int	machine_at_packtron_daytonawin_120nx2_init(const machine_t *);	/* PacTron DaytonaWin-120NX                                 */

/* Panther Systems */
extern int	machine_at_panther_486_33_init(const machine_t *);				/* Panther 486/33                                           */

/* PC Brand */
/* See Tandon */															/* PC Brand Leader Cache 486/DX2-66                         */
/* See Tandon */															/* PC Brand Leader 486/DLC-33                               */

/* PC Craft */
extern int	machine_at_pc_craft_2401_33_init(const machine_t *);			/* PC Craft 2401/33                                         */

/* PC Enterprises (LOCAL RETAILER) */
extern int	machine_at_pc_enterprises_486_vesa_init(const machine_t *);		/* PC Enterprises 486 VESA                                  */

/* PC Express */
extern int	machine_at_pc_express_exp66_100_init(const machine_t *);		/* PC Express EXP66                                         */
/* See above */																/* PC Express EXP100                                        */
extern int	machine_at_pc_express_exp90_init(const machine_t *);			/* PC Express EXP90                                         */
/* See machine_at_pc_express_exp66_100_init */								/* PC Express Family Multimedia System                      */

/* PC Partner */
extern int	machine_at_mb500n_init(const machine_t *);						/* PC Partner MB500N                                        */
extern int	machine_at_mb540n_init(const machine_t *model);					/* PC Partner MB540N                                        */
extern int	machine_at_mb600n_init(const machine_t *);						/* PC Partner MB600N                                        */
extern int	machine_at_apas3_init(const machine_t *);						/* PC Partner APAS3                                         */

/* PC Positive */
/* See Tandon */															/* PC Positive 486                                          */

/* PCI Systems */
extern int	machine_at_pci_486_50c128_init(const machine_t *);				/* PCI 486-50C128                                           */

/* PerComp MicroSystems */
extern int	machine_at_percomp_p75_p90_p100_init(const machine_t *);		/* PerComp P75  Personal                                    */
/* See above */																/* PerComp P90  Personal                                    */
/* See above */																/* PerComp P100 Personal                                    */
/* See above */																/* PerComp P75  Family Media                                */
/* See above */																/* PerComp P90  Family Media                                */
/* See above */																/* PerComp P100 Family Media                                */
/* See above */																/* PerComp P75  MediaPro                                    */
/* See above */																/* PerComp P90  MediaPro                                    */
/* See above */																/* PerComp P100 MediaPro                                    */
extern int	machine_at_percomp_professional_init(const machine_t *);		/* PerComp P120 Executive                                   */
extern int	machine_at_percomp_professional2_init(const machine_t *);		/* PerComp P120 Executive                                   */
/* See above */																/* PerComp P133 Executive                                   */
/* See above */																/* PerComp P100 Professional                                */
/* See above */																/* PerComp P120 Professional                                */
/* See above */																/* PerComp P133 Professional                                */
/* See machine_percomp_p75_p90_p100_init */									/* PerComp P150 Professional                                */
/* See above */																/* PerComp P166 Professional                                */

/* Peregrine */
extern int	machine_at_peregrine_486_33_flyer_init(const machine_t *);		/* Peregrine 486/33 Flyer                                   */

/* Personal Computer Graphics */
extern int	machine_at_pcg_burstar_p90_init(const machine_t *);				/* PCG BurSTar P90                                          */

/* POISK */
extern int	machine_at_poisk2_init(const machine_t *);						/* POISK II 286                                             */

/* Polywell */
extern int	machine_at_polywell_poly_486ev_init(const machine_t *);			/* Polywell Poly 486EV                                      */
/* See above */																/* Polywell Poly 486-66EV                                   */
extern int	machine_at_polywell_poly_590ip_init(const machine_t *);			/* Polywell Poly 586-90VIP                                  */
/* See above */																/* Polywell Poly 590IP                                      */
/* See below */																/* Polywell Poly 586-66V1                                   */
extern int	machine_at_polywell_poly_586_90vlb_init(const machine_t *);		/* Polywell Poly 586-90VLB                                  */
extern int	machine_at_polywell_poly_590ip_init(const machine_t *);			/* Polywell Poly 590IP                                      */
extern int	machine_at_polywell_poly_575ip_init(const machine_t *);			/* Polywell Poly 575IP                                      */
extern int	machine_at_polywell_poly_5120t3_5133t3_init(const machine_t *);	/* Polywell Poly 5100T3                                     */
/* See above */																/* Polywell Poly 5120T3                                     */
/* See above */																/* Polywell Poly 5133T3                                     */
/* See above */																/* Polywell Poly 500P8                                      */
extern int	machine_at_polywell_polystation_init(const machine_t *);		/* Polywell PolyStation 133P                                */
/* See above */																/* Polywell PolyStation 166P                                */
/* See above */																/* Polywell PolyStation 5166P8                              */

/* PowerBox */
extern int	machine_at_powerbox_pbs1_340i_init(const machine_t *);			/* PowerBox PBS1-340i                                       */

/* Precision Systems Group */
extern int	machine_at_precision_pti_66_init(const machine_t *);			/* Precision PTI-66                                         */
extern int	machine_at_precision_pti_90_init(const machine_t *);			/* Precision PTI-90                                         */

/* Premio (formerly CompuTrend) */
extern int	machine_at_computrend_premio_486_init(const machine_t *);		/* CompuTrend Premio              486DX2/66                 */
/* See below */																/* CompuTrend Premio                    P75                 */
/* See below */																/* CompuTrend Premio                    P90                 */
/* See below */																/* CompuTrend Premio                    P100                */
/* See below */																/* CompuTrend Premio                    P120                */
extern int	machine_at_computrend_premio_p133_init(const machine_t *);		/* CompuTrend Premio                    P133                */
/* See above */																/* CompuTrend Premio Triton             P75                 */
/* See above */																/* CompuTrend Premio Triton             P90                 */
/* See above */																/* CompuTrend Premio Triton             P100                */
/* See above */																/* CompuTrend Premio Triton             P120                */
/* See above */																/* CompuTrend Premio Triton             P133                */
/* See above */																/* CompuTrend Premio Rocket PC          P75                 */
/* See above */																/* CompuTrend Premio Rocket PC          P90                 */
/* See above */																/* CompuTrend Premio Rocket PC          P100                */
/* See above */																/* CompuTrend Premio Rocket PC          P120                */
/* See above */																/* CompuTrend Premio Rocket PC          P133                */
/* See above */																/* CompuTrend Premio Express    Station P75                 */
/* See above */																/* CompuTrend Premio Express    Station P90                 */
/* See above */																/* CompuTrend Premio Express    Station P100                */
/* See above */																/* CompuTrend Premio Express    Station P120                */
/* See above */																/* CompuTrend Premio Express    Station P133                */
/* See above */																/* CompuTrend Premio Express    Station P90                 */
/* See above */																/* CompuTrend Premio Express    Station P133                */
/* See above */																/* CompuTrend Premio Vitesse CADstation P100                */
/* See above */																/* CompuTrend Premio Vitesse CADstation P120                */
/* See above */																/* CompuTrend Premio Vitesse CADstation P133                */

/* Professional Computer Systems */
extern int	machine_at_pcs_double_pro_66_init(const machine_t *);			/* PCS Double Pro-66                                        */

/* Professional Technologies */
extern int	machine_at_professional_486_init(const machine_t *);			/* Professional EXEC 486-33                                 */
/* See above */																/* Professional ISA                                         */
/* See above */																/* Professional VESA-1                                      */
/* See above */																/* Professional VESA-2                                      */
/* See above */																/* Professional VESA-3                                      */

/* QSI */
extern int	machine_at_qsi_klonimus_486_init(const machine_t *);			/* QSI Klonimus 486/SX25                                    */
/* See above */																/* QSI Klonimus 486/33                                      */
/* See above */																/* QSI Klonimus 486DX2/66                                   */

/* Quantex */
extern int	machine_at_csp_ftn486_init(const machine_t *);					/* Computer Sales Professional Pro 486DX2/50                */
extern int	machine_at_quantex_q486dx2_66mm_4_init(const machine_t *);		/* Quantex Q486DX2/66MM-4                                   */
extern int	machine_at_quantex_qp5_60_66_init(const machine_t *);			/* Quantex QP5/60     B-1                                   */
/* See above */																/* Quantex QP5/60     B-2                                   */
/* See above */																/* Quantex QP5/60    PM                                     */
/* See above */																/* Quantex QP5/60    PM-1                                   */
/* See above */																/* Quantex QP5/60    PM-2                                   */
/* See above */																/* Quantex QP5/60    PM-3                                   */
/* See above */																/* Quantex QP5/60     W-1                                   */
/* See above */																/* Quantex QP5/60     W-2                                   */
/* See above */																/* Quantex QP5/60    XM                                     */
/* See above */																/* Quantex QP5/60    XM-1                                   */
/* See above */																/* Quantex QP5/66     B-1                                   */
/* See above */                                                             /* Quantex QP5/66     B-2                                   */
/* See above */                                                             /* Quantex QP5/66    PM                                     */
/* See above */                                                             /* Quantex QP5/66    PM-1                                   */
/* See above */                                                             /* Quantex QP5/66    PM-2                                   */
/* See above */                                                             /* Quantex QP5/66    PM-3                                   */
/* See above */                                                             /* Quantex QP5/66     W-1                                   */
/* See above */                                                             /* Quantex QP5/66     W-2                                   */
extern int	machine_at_quantex_qp5_90_init(const machine_t *);				/* Quantex QP5/90     B-1                                   */
/* See above */																/* Quantex QP5/90     B-2                                   */
/* See above */																/* Quantex QP5/90    PM                                     */
/* See machine_at_quantex_qp5_90_w3_init */									/* Quantex QP5/90    PM   (1.00.10.AX1)                     */
/* See machine_at_quantex_qp5_90_init */									/* Quantex QP5/90    PM-1                                   */
/* See machine_at_quantex_qp5_90_w3_init */									/* Quantex QP5/90    PM-1 (1.00.10.AX1)                     */
/* See machine_at_quantex_qp5_90_init */									/* Quantex QP5/90    PM-2                                   */
/* See machine_at_quantex_qp5_90_w3_init */									/* Quantex QP5/90    PM-2 (1.00.10.AX1)                     */
/* See machine_at_quantex_qp5_90_init */									/* Quantex QP5/90    PM-3                                   */
/* See machine_at_quantex_qp5_90_w3_init */									/* Quantex QP5/90    PM-3 (1.00.10.AX1)                     */
/* See machine_at_quantex_qp5_90_init */									/* Quantex QP5/90     W-1                                   */
/* See machine_at_quantex_qp5_90_w3_init */									/* Quantex QP5/90     W-1 (1.00.10.AX1)                     */
/* See machine_at_quantex_qp5_90_init */									/* Quantex QP5/90     W-2                                   */
/* See machine_at_quantex_qp5_90_w3_init */									/* Quantex QP5/90     W-2 (1.00.10.AX1)                     */
/* See machine_at_quantex_qp5_90_ini */										/* Quantex QP5/90     W-3                                   */
extern int	machine_at_quantex_qp5_90_w3_init(const machine_t *);			/* Quantex QP5/90     W-3 (1.00.10.AX1)                     */
/* See above */																/* Quantex QP5/90     XM-1                                  */
/* See above */																/* Quantex QP5/90     XM-3                                  */
/* See above */																/* Quantex QP5/90     XW                                    */
/* See above */																/* Quantex QP5/75     XM-1                                  */
/* See above */																/* Quantex QP5/75     XM-3                                  */
/* See above */																/* Quantex QP5/75     XW                                    */
/* See above */																/* Quantex QP5/100    XM-1                                  */
/* See above */																/* Quantex QP5/100    XM-3                                  */
/* See above */																/* Quantex QP5/100    XW-1                                  */
/* See below */																/* Quantex QP5/75      M-1                                  */
/* See below */																/* Quantex QP5/75      M-2                                  */
/* See below */																/* Quantex QP5/75      M-3                                  */
/* See below */																/* Quantex QP5/75      M-4                                  */
/* See below */																/* Quantex QP5/75     SM                                    */
/* See below */																/* Quantex QP5/90      M-1                                  */
/* See below */																/* Quantex QP5/90      M-2                                  */
/* See below */																/* Quantex QP5/90      M-3                                  */
/* See below */																/* Quantex QP5/90      M-4                                  */
/* See below */																/* Quantex QP5/90     SM                                    */
/* See below */																/* Quantex QP5/100     M-1                                  */
/* See below */																/* Quantex QP5/100     M-2                                  */
/* See below */																/* Quantex QP5/100     M-3                                  */
/* See below */																/* Quantex QP5/100     M-4                                  */
/* See below */																/* Quantex QP5/100    SM                                    */
extern int	machine_at_quantex_qp5_100_sm_1_init(const machine_t *);		/* Quantex QP5/100    SM-1                                  */
/* See above */																/* Quantex QP5/120    SM                                    */
/* See above */																/* Quantex QP5/120    SM-1                                  */
/* See above */																/* Quantex QP5/133    SM                                    */
/* See above */																/* Quantex QP5/133    SM-1                                  */
/* See below */																/* Quantex QP5/100    SM-2 (Intel AMIBIOS)                  */
/* See below */																/* Quantex QP5/100    SM-2 (Award BIOS)                     */
/* See below */																/* Quantex QP5/100    SM-2 (AMIBIOS)                        */
/* See below */																/* Quantex QP5/120    SM-2 (Intel AMIBIOS)                  */
/* See below */																/* Quantex QP5/120    SM-2 (Award BIOS)                     */
/* See below */																/* Quantex QP5/120    SM-2 (AMIBIOS)                        */
extern int	machine_at_quantex_133_166_sm_2_amibios_init(const machine_t *);/* Quantex QP5/133    SM-2 (Intel AMIBIOS)                  */
extern int	machine_at_quantex_133_166_sm_2_award_init(const machine_t *);	/* Quantex QP5/133    SM-2 (Award BIOS)                     */
extern int	machine_at_quantex_133_166_sm_2_hx_init(const machine_t *);		/* Quantex QP5/133    SM-2 (AMIBIOS)                        */
/* See above */																/* Quantex QP5/166    SM-2 (Intel AMIBIOS)                  */
/* See above */																/* Quantex QP5/166    SM-2 (Award BIOS)                     */
 
/* Quill */
extern int	machine_at_quill_q_tech_486_init(const machine_t *);			/* Quill Q-Tech 486SX-25                                    */
/* See above */																/* Quill Q-Tech 486DX-33                                    */
/* See above */																/* Quill Q-Tech 486DX-50                                    */
/* See above */																/* Quill Q-Tech 486DX2-66                                   */
/* See above */																/* Quill Q-Tech 486 4D2/66                                  */
/* See above */																/* Quill Q-Tech PC-4D33-4                                   */

/* Reason Technology */
extern int	machine_at_reason_square_5_lx_tr_iz_120_init(const machine_t *);/* Reason Square 5 LX-TR/IZ-120                             */
extern int	machine_at_reason_square_5_lx_tr_ie_133_init(const machine_t *);/* Reason Square 5 LX-TR/IE-133                             */
extern int	machine_at_reason_square_5_lx_tr_ie_150_init(const machine_t *);/* Reason Square 5 LX-TR/IE-150                             */
/* See above */																/* Reason Square 5 LX-TR/IE-166                             */

/* Robotech */
extern int	machine_at_robotech_cobra_rs_p90_init(const machine_t *);		/* Robotech Cobra RS    p90  Graphics Workstation           */
extern int	machine_at_robotech_cobra_rs_p100_init(const machine_t *);		/* Robotech Cobra RS    p100 Graphics Workstation           */
/* See below */																/* Robotech Cobra XL    P100                                */
/* See below */																/* Robotech Cobra XL    P133                                */
extern int	machine_at_robotech_cobra_xlt_p75_home_init(const machine_t *);	/* Robotech Cobra XLT   P75  Home Office                    */
extern int	machine_at_robotech_cobra_xlt_init(const machine_t *);			/* Robotech Cobra XLT   P100                                */
/* See above */																/* Robotech Cobra XLT   P133                                */
extern int	machine_at_robotech_cobra_xlt_p133_p166_init(const machine_t *);/* Robotech Cobra XLT   P133 (second model)                 */
/* See above */																/* Robotech Cobra XLT   P166                                */
extern int	machine_at_robotech_cobra_xlt_2_init(const machine_t *);		/* Robotech Cobra XLT/2 P133                                */
/* See above */																/* Robotech Cobra XLT/2 P166                                */

/* Royal Computer */
extern int	machine_at_royal_media_master_init(const machine_t *);			/* Royal       Media Master                                 */
/* See above */																/* Royal Ultra Media-15                                     */

/* SAG Electronics */
extern int	machine_at_sag_stf_120_133_init(const machine_t *);				/* SAG STF 120                                              */
extern int	machine_at_sag_stf_120_1332_init(const machine_t *);			/* SAG STF 120                                              */
/* See above */																/* SAG STF 133                                              */
extern int	machine_at_sag_stf_150_166_init(const machine_t *);				/* SAG STF 150                                              */
/* See above */																/* SAG STF 166                                              */

/* SAI Systems Laboratories */
extern int	machine_at_sai_486_25_init(const machine_t *);					/* SAI 486/25                                               */
extern int	machine_at_sai_486_33_init(const machine_t *);					/* SAI 486/33                                               */
extern int	machine_at_sai_386dx_40_init(const machine_t *);				/* SAI 386DX-40                                             */

/* Samsung */
extern int	machine_at_spc4200p_init(const machine_t *);					/* Samsung SPC-4200P                                        */
extern int	machine_at_spc4216p_init(const machine_t *);					/* Samsung SPC-4216P                                        */
extern int	machine_at_deskmaster286_init(const machine_t *);				/* Samsung DeskMaster 286                                   */

/* Schneider */
extern int	machine_europc_init(const machine_t *);							/* Schneider EuroPC                                         */
#ifdef EMU_DEVICE_H
extern const device_t europc_device;
#endif

/* Seanix Technology */
extern int	machine_at_seanix_asi_9000_486_vl_init(const machine_t *);		/* Seanix ASI 9000 486DX266/0BL                             */
/* See above */																/* Seanix ASI 9000 486DX499/16L                             */

/* Sho-Tronics Computer */
extern int	machine_at_sho_tronics_486_init(const machine_t *);				/* Sho-Tronics Professional Starter System                  */
/* See above */																/* Sho-Tronics Power Tech                                   */
/* See above */																/* Sho-Tronics Super CD System                              */

/* Sidus Systems */
extern int	machine_at_sidus_sci966dc256dt_init(const machine_t *);			/* Sidus SCI966DC256DT                                      */
extern int	machine_at_sidus_sci9p590pdt_init(const machine_t *);			/* Sidus SCI9P590PDT                                        */

/* Siemens-Nixdorf */
extern int	machine_at_siemens_init(const machine_t *);						/* Siemens PCD-2L                                           */
//Siemens PCD-2L. N82330 discrete machine. It segfaults in some places

/* Silicon Valley Computer */
extern int	machine_at_silicon_valley_pylon1_586_init(const machine_t *);	/* Silicon Valley Pylon 1 586                               */

/* Simply Better Computers */
/* See machine_at_percomp_p75_p90_p100_init */								/* Simply Better P75  Personal                              */
/* See above */																/* Simply Better P90  Personal                              */
/* See above */																/* Simply Better P100 Personal                              */
/* See above */																/* Simply Better P75  Family Media                          */
/* See above */																/* Simply Better P90  Family Media                          */
/* See above */																/* Simply Better P100 Family Media                          */
/* See above */																/* Simply Better P75  MediaPro                              */
/* See above */																/* Simply Better P90  MediaPro                              */
/* See above */																/* Simply Better P100 MediaPro                              */
/* See machine_at_percomp_professional_init */								/* Simply Better P120 Executive                             */
/* See above */																/* Simply Better P133 Executive                             */
/* See above */																/* Simply Better P100 Professional                          */
/* See above */																/* Simply Better P120 Professional                          */
/* See above */																/* Simply Better P133 Professional                          */

/* Sirius Systems Technology */
extern int	machine_at_sirius_sst_486dx2_66mwc_init(const machine_t *);		/* Sirius SST 486DX2-66MWC                                  */

/* SmartWorks */
extern int	machine_at_smartworks_slimline_66_init(const machine_t *);		/* SmartWorks Slimline 66                                   */

/* SoftWorks Development Corporation */
extern int	machine_at_softworks_citus_mdc_486_init(const machine_t *);		/* SoftWorks Citus MDC 486/25                               */
/* See above */																/* SoftWorks Citus MDC 486DX/33                             */
/* See above */																/* SoftWorks Citus MDC 486DX2/50                            */
/* See above */																/* SoftWorks Citus MDC 486DX2/66                            */

/* SolMicro */
extern int	machine_at_solmicro_intrepid_466_init(const machine_t *);		/* SolMicro Intrepid 466                                    */

/* SONY */
extern int	machine_at_pcv90_init(const machine_t *);						/* Sony VAIO PCV-90                                         */
/* See above */																/* Sony VAIO PCV-120                                        */

/* Spear Technology */
extern int	machine_at_spear_486_isa_convertible_init(const machine_t *);	/* Spear 486 ISA Convertible                                */

/* Standard Computer Corporation */
extern int	machine_at_standard_486sx25_init(const machine_t *);			/* Standard 486SX/25                                        */

/* Stargate Microsystems */
extern int	machine_at_stargate_pentium_75_133_init(const machine_t *);		/* Stargate Pentium     75  System                          */
/* See above */																/* Stargate Pentium     90  System                          */
/* See above */																/* Stargate Pentium    100  System                          */
/* See above */																/* Stargate Pentium    120  System                          */
/* See above */																/* Stargate Pentium 75-133+ Triton MB                       */

/* STD (Standard Systems Supply) */
extern int	machine_at_std_p60_pci_init(const machine_t *);					/* STD P60 PCI                                              */

/* Summit Micro Design */
extern int	machine_at_smd_mount_lassen_shasta_init(const machine_t *);		/* SMD Mount Lassen                                         */
/* See above */																/* SMD Mount Shasta                                         */

/* Swan */
/* See below */																/* Swan     Direct Bus Line                                 */
extern int	machine_at_swan_486_db_init(const machine_t *);					/* Swan 486SX/25DB                                          */
/* See above */																/* Swan 486/33DB                                            */
/* See above */																/* Swan 486DX2-50DB                                         */
extern int	machine_at_swan_486_db2_init(const machine_t *);				/* Swan 486DX2-66DB                                         */
extern int	machine_at_swan_486_direct_bus_init(const machine_t *);			/* Swan 486 Direct Bus                                      */

/* Sys Technology */
extern int	machine_at_sys_performance_p100t_init(const machine_t *);		/* Sys Performance P100T                                    */
extern int	machine_at_sys_performance_p133t_init(const machine_t *);		/* Sys Performance P133T                                    */
extern int	machine_at_sys_performance_p166t_init(const machine_t *);		/* Sys Performance P166T                                    */

/* Systemax */
/* See MidWest Micro */

/* Systems Integration Associates */
extern int	machine_at_sia_486_33_init(const machine_t *);					/* SIA 486/33                                               */

/* Tagram */
/* See below */																/* Tagram Thunderbolt ZR                                    */
extern int	machine_at_tagram_thunderbolt_xl_init(const machine_t *);		/* Tagram Thunderbolt XL                                    */
extern int	machine_at_tagram_thunderbolt_p100_init(const machine_t *);		/* Tagram Thunderbolt P100                                  */
extern int	machine_at_tagram_thunderbolt_p133_init(const machine_t *);		/* Tagram Thunderbolt P133                                  */

/* Tandon */
extern int	machine_at_micronics386_init(const machine_t *);				/* Tandon            386/33                                 */
extern int	machine_at_tandon_486_init(const machine_t *);					/* Tandon   MCS  Pro 486-33                                 */
/* See above */																/* Tandon Option Pro 486 25                                 */
/* See above */																/* Tandon Option Pro 486 33                                 */
/* See above */																/* Tandon Option Pro 486 66                                 */
/* See above */																/* Tandon Option Pro 486 100                                */

/* Tandy */
extern int	tandy1k_eeprom_read(void);
extern int	machine_tandy_init(const machine_t *);
extern int	machine_tandy1000hx_init(const machine_t *);					/* Tandy 1000 HX                                            */
extern int	machine_tandy1000sl2_init(const machine_t *);					/* Tandy 1000 SL/2                                          */
#ifdef EMU_DEVICE_H
extern const device_t	*tandy1k_get_device(void);
extern const device_t	*tandy1k_hx_get_device(void);
#endif
extern int	machine_at_tandy_2500_init(const machine_t *);					/* Tandy 1000 RSX                                           */
/* See above */																/* Tandy 2500 SX/25                                         */
extern int	machine_at_tandy_sensation_init(const machine_t *);				/* Tandy Sensation!                                         */
/* See above */																/* Tandy 3100                                               */
extern int	machine_at_tandy_486_init(const machine_t *);					/* Tandy 2100                                               */
/* See extern int	machine_at_tandy_sensation_init(const machine_t *); */	/* Tandy Multimedia PC 25-1641                              */
/* See extern int	machine_at_tandy_sensation_init(const machine_t *); */	/* Tandy Sensation II                                       */
/* See extern int	machine_at_tandy_sensation_init(const machine_t *); */	/* Tandy Omni II                                            */
/* See extern int	machine_at_tandy_sensation_init(const machine_t *); */	/* Tandy 3200                                               */

/* Tangent */
extern int	machine_at_tangent_model_425s_init(const machine_t *);			/* Tangent Model 425s                                       */
extern int	machine_at_tangent_486_init(const machine_t *);					/* Tangent 486                                              */
/* See above */																/* Tangent Black Box Pro Series                             */
extern int	machine_at_tangent_vl_init(const machine_t *);					/* Tangent VL Cx486S-40                                     */
/* See above */																/* Tangent VL 466                                           */
extern int	machine_at_tangent_p560_init(const machine_t *);				/* Tangent P560                                             */
extern int	machine_at_tangent_mediastar_init(const machine_t *);			/* Tangent MediaStar 590/95                                 */
/* See above */																/* Tangent MediaStar 5133/95                                */

/* Tatung */
extern int	machine_at_tatung_tcs_5100_5900_init(const machine_t *);		/* Tatung TCS-5100                                          */
/* See above */																/* Tatung TCS-5900                                          */

/* TC Computers */
extern int	machine_at_tc_p5_75_media_init(const machine_t *);				/* TC P5-75 Media                                           */

/* Techway */
extern int	machine_at_techway_endeavour_ii_init(const machine_t *);		/* Techway Endeavour II                                     */

/* TechnoMedia Corporation */
extern int	machine_at_technomedia_fic_pt_2000_init(const machine_t *);		/* TechnoMedia FIC PT-2000                                  */

/* TeleVideo Systems */
extern int	machine_at_televideo_tele386e_init(const machine_t *);			/* TeleVideo Tele386e                                       */

/* Tenex Computer Express */
extern int	machine_at_tenex_premier_486dx_33_init(const machine_t *);		/* Tenex Premier 486DX/33                                   */

/* Thoroughbred MicroSystems */
extern int	machine_at_thoroughbred_386_25_init(const machine_t *);			/* Thoroughbred 386/25                                      */

/* TigerDirect */
extern int	machine_at_mvp3_init(const machine_t *);						/* Tiger FIC VA-503+                                        */

/* Top Data */
extern int	machine_at_top_data_p5_pci_init(const machine_t *);				/* Top Data P5-120      PCI                                 */
/* See above */																/* Top Data P5-133      PCI                                 */
/* See above */																/* Top Data P5-100/256C PCI                                 */
/* See above */																/* Top Data P5-120/256C PCI                                 */
/* See above */																/* Top Data P5-133/256C PCI                                 */
extern int	machine_at_top_data_p5_100c_120c_133c_init(const machine_t *);	/* Top Data P5-100C     PCI (Intel Endeavor M/B)            */
extern int	machine_at_top_data_p5_100c_120c_133c2_init(const machine_t *);	/* Top Data P5-100C     PCI (Intel Atlantis M/B)            */
/* See machine_at_top_data_p5_100c_120c_133c  */							/* Top Data P5-120C     PCI (Intel Endeavor M/B)            */
/* See machine_at_top_data_p5_100c_120c_133c2 */							/* Top Data P5-120C     PCI (Intel Atlantis M/B)            */
/* See machine_at_top_data_p5_100c_120c_133c  */							/* Top Data P5-133C     PCI (Intel Endeavor M/B)            */
/* See machine_at_top_data_p5_100c_120c_133c2 */							/* Top Data P5-133C     PCI (Intel Atlantis M/B)            */

/* Toptek (LOCAL RETAILER) */
extern int	machine_at_toptek_top486dx2_66_init(const machine_t *);			/* Toptek Top486DX2/66                                      */

/* Toshiba */
extern int	machine_xt_t1000_init(const machine_t *);						/* Toshiba T1000                                            */
extern int	machine_xt_t1200_init(const machine_t *);						/* Toshiba T1200                                            */
#ifdef EMU_DEVICE_H
extern const device_t	*t1000_get_device(void);
extern const device_t	*t1200_get_device(void);
#endif
extern int	machine_at_t3100e_init(const machine_t *);						/* Toshiba T3100e                                           */
/* See below */																/* Toshiba Equium 5160D                                     */
extern int	machine_at_equium5200_init(const machine_t *);					/* Toshiba Equium 5200D                                     */

/* Total Peripherals */
extern int	machine_at_total_peripherals_386dx_40_init(const machine_t *);	/* Total Peripherals 386DX-40                               */

/* Touche Micro Technologies */
extern int	machine_at_touche_486dx2_50_init(const machine_t *);			/* Touche 486DX2/50                                         */
extern int	machine_at_touche_isa_vlb_init(const machine_t *);				/* Touche ISA VLB                                           */

/* Transource Computers */
extern int	machine_at_transource_verxion_486_init(const machine_t *);		/* Transource Verxion 486                                   */

/* Treasure Chest Computers */
extern int	machine_at_treasure_chest_tcp575_init(const machine_t *);		/* Treasure Chest TCP575                                    */

/* Tri-Star */
extern int	machine_at_tri_star_486_isa_init(const machine_t *);			/* Tri-Star Tri-Win 486SX/25                                */
/* See above */																/* Tri-Star Tri-WIN 486DX/50 ISA                            */
extern int	machine_at_tri_star_tri_cad_workstation_init(const machine_t *);/* Tri-Star Tri-CAD Pro-17 Workstation 120                  */
/* See above */																/* Tri-Star Tri-CAD 133/55 Workstation                      */
extern int	machine_at_tri_star_tri_cad_multimedia_init(const machine_t *);	/* Tri-Star Tri-CAD Multimedia                              */

/* TriGem */
extern int	machine_at_tg286m_init(const machine_t *);						/* TriGem 286M                                              */

/* Twinhead */
extern int	machine_at_twinhead_superset_init(const machine_t *);			/* Twinhead Superset 600/425C                               */
/* See above */																/* Twinhead Superset 600/452C                               */

																			/* Ultra Computers */
extern int	machine_at_ultra_ul486_66_lpc_init(const machine_t *);			/* Ultra UL486/66-LPC                                       */

/* Unisys */
extern int	machine_at_unisys_pw2_advantage_4666_init(const machine_t *);	/* Unisys PW2 Advantage                  4333               */
/* See above */																/* Unisys PW2 Advantage                  4666               */
/* See above */																/* Unisys PW2 Advantage Plus Model       4666               */
/* See above */																/* Unisys PW2 Advantage Partner      ELI 4333               */
/* See above */																/* Unisys                            ELI 46665              */
/* See above */																/* Unisys                            CWD 4001-ZE            */
extern int	machine_at_unisys_pw2_series_svi_init(const machine_t *);		/* Unisys PW2 Series Model           CWP 5906               */
/* See above */																/* Unisys PW2 Series Model           SVI 5907               */
/* See above */																/* Unisys PW2 Series Model           SVI 51007              */
extern int	machine_at_unisys_pw2_advantage_super_init(const machine_t *);	/* Unisys PW2 Advantage Super Series  CWP51336              */

/* United Micro Express */
extern int	machine_at_um_galaxy_486vlb_33mm_init(const machine_t *);		/* United Micro UM Galaxy 486VLB-33MM                       */

/* United Solutions */
extern int	machine_at_usi_green_pc_init(const machine_t *);				/* United Solutions USI Green PC                            */

/* Unitek Technology */
extern int	machine_at_unitek_thunderstreak_init(const machine_t *);		/* Unitek Thunderstreak Pentium 133                         */

/* U.S. Micro */
extern int	machine_at_us_micro_jet_486dx2_init(const machine_t *);			/* U.S. Micro Jet 486DX2-50                                 */
/* See above */																/* U.S. Micro Jet 486DX2-66                                 */

/* USA Flex */
extern int	machine_at_usa_flex_486sx_25_init(const machine_t *);			/* USA Flex                486SX/25         System          */
extern int	machine_at_usa_flex_pentium_init(const machine_t *);			/* USA Flex           Pentium    60MHz      System          */
/* See above */																/* USA Flex Flex PT60 Pentium    Multimedia System          */
extern int	machine_at_usa_flex_pt_75_90_100_init(const machine_t *);		/* USA Flex      PT90                                       */
/* See above */																/* USA Flex      PT90            Power      System          */
/* See above */																/* USA Flex Flex PT75            Multimedia System          */
/* See above */																/* USA Flex      PT-75           Desktop    System          */
/* See above */																/* USA Flex      PT-100          Tower      System          */
/* See above */																/* USA Flex      PT90         MidTower                      */
extern int	machine_at_usa_flex_pt_75_multimedia_init(const machine_t *);	/* USA Flex      PT-75           MultiMedia Classic         */
/* See above */																/* USA Plex      PT-133          Power      System          */
extern int	machine_at_usa_flex_flex_pt_133_init(const machine_t *);		/* USA Flex Flex                 Multimedia System PT-133   */
extern int	machine_at_usa_flex_flex_pt_1332_init(const machine_t *);		/* USA Flex Flex                 Multimedia System PT-133   */
extern int	machine_at_usa_flex_pt100_business_init(const machine_t *);		/* USA Flex      PT100           Business   Workstation     */
/* See above */																/* USA Flex      PT-90           Multimedia System          */
extern int	machine_at_usa_flex_pt_166_ultimate_init(const machine_t *);	/* USA Flex      PT-166 Ultimate Multimedia Tower           */
extern int	machine_at_usa_flex_multimedia_classic_init(const machine_t *);	/* USA Flex                      Multimedia Classic         */

/* Vanvier */
extern int	machine_at_vanvier_gpc7486_init(const machine_t *);				/* Vanvier GPC7486                                          */

/* Vektron International */
extern int	machine_at_vektron_pci_power_station_60_init(const machine_t *);/* Vektron      PCI Professional Multimedia/Pentium 60      */
/* See above */																/* Vektron      PCI Power Station/Pentium 60                */
extern int	machine_at_vektron_p133_init(const machine_t *);				/* Vektron          Power Station      P-133                */
extern int	machine_at_vektron_p1332_init(const machine_t *);				/* Vektron          Power Station      P-133                */
/* See above */																/* Vektron Ultimate Power Station      P-133                */
/* See above */																/* Vektron Multimedia Home                                  */
/* See above */																/* Vektron            Home Office  Pro-P150                 */

/* VTech */
#if defined(DEV_BRANCH) && defined(USE_LASERXT)
extern int	machine_xt_laserxt_init(const machine_t *);						/* VTech Laser Turbo XT                                     */
extern int	machine_xt_lxt3_init(const machine_t *);						/* VTech Laser       XT3                                    */
#endif

/* Wedge Technology */
extern int	machine_at_wedge_deskmate_pro_133_init(const machine_t *);		/* Wedge DeskMate Pro 133                                   */

/* Windows Memory Corporation */
extern int	machine_at_windows_memory_pentium_60_66_init(const machine_t *);/* Windows Memory       Pentium  60/66 PC w/IO              */
extern int	machine_at_windows_memory_premiere_ii_init(const machine_t *);	/* Windows Memory Intel Premiere 90    II w/IO              */
/* See above */																/* Windows Memory Intel Premiere 100   II w/IO              */
/* See above */																/* Windows Memory Intel Premiere       IV w/IO              */

/* Worldwide Technologies */
extern int	machine_at_worldwide_intel_zappa_init(const machine_t *);		/* Worldwide Technologies Intel Zappa P5-75                 */
/* See above */																/* Worldwide Technologies Intel Zappa P5-90                 */
/* See above */																/* Worldwide Technologies Intel Zappa P5-100                */

/* Wyse */
extern int	machine_at_wyse_decision_486si_init(const machine_t *);			/* Wyse Decision 486si                                      */

/* Xi8088 */
extern int	machine_xt_xi8088_init(const machine_t *);						/* Xi8088                                                   */

/* Xi Computer Corporation */
extern int	machine_at_xi_p100_ntower_sp_init(const machine_t *);			/* Xi    P100 NTower SP                                     */
/* See above */																/* Xi         MTower SP166MHz                               */
/* See above */																/* Xi    P133 MTower SP                                     */
/* See above */																/* Xi    P166 MTower SP                                     */
/* See above */																/* Xi    P200 MTower SP                                     */
extern int	machine_at_xi_pro_200mtower_sp_init(const machine_t *);			/* Xi Pro 200 MTower SP                                     */
extern int	machine_at_xi_pro_200mtower_dp_sp_init(const machine_t *);		/* Xi Pro 200 MTower DP/SP (Award BIOS)                     */
extern int	machine_at_xi_pro_200mtower_dp_sp_ami_init(const machine_t *);	/* Xi Pro 200 MTower DP/SP (AMIBIOS)                        */

/* Xinetron */
extern int	machine_at_xinetron_x_lan_486_init(const machine_t *);			/* Xinetron X/Lan 486 (DX/33)                               */
/* See above */																/* Xinetron X/Lan 486 (DX2/66)                              */
/* See below */																/* Xinetron X/LAN Station DX/33                             */
extern int	machine_at_xinetron_x_lan_dx2_66_init(const machine_t *);		/* Xinetron X/LAN Station DX2/66                            */
extern int	machine_at_xinetron_x_lan_xp66_init(const machine_t *);			/* Xinetron X/Lan XP66                                      */

/* WYSE Technology */
extern int	machine_at_wyse_decision_486_50_dx2_init(const machine_t *);	/* Wyse Decision 486/50 DX2                                 */
/* See above */																/* Wyse Decision 486si                                      */

/* Zenith Data Systems */
extern int	machine_xt_zenith_init(const machine_t *);						/* Zenith Data SupersPort                                   */
extern int	machine_at_zenith_z_station_ex_init(const machine_t *);			/* Zenith Z-Station EX                                      */
extern int	machine_at_zenith_z_station_ex_1004_init(const machine_t *);	/* Zenith Z-Station EX      (1.00.04.BF0U)                  */
extern int	machine_at_zenith_z_station_ex_1005_init(const machine_t *);	/* Zenith Z-Station EX      (1.00.05.BF0U)                  */
extern int	machine_at_zenith_z_station_ex_1007_init(const machine_t *);	/* Zenith Z-Station EX      (1.00.07.BF0U)                  */
extern int	machine_at_zenith_z_station_ex_1009_init(const machine_t *);	/* Zenith Z-Station EX      (1.00.09.BF0U)                  */
extern int	machine_at_zenith_z_station_ex_1011_init(const machine_t *);	/* Zenith Z-Station EX      (1.00.11.BF0U)                  */
/* See machine_at_zenith_z_station_ex_init */								/* Zenith Z-Station EX MDII                                 */
/* See machine_at_zenith_z_station_ex_1004_init */							/* Zenith Z-Station EX MDII (1.00.04.BFU0)                  */
/* See machine_at_zenith_z_station_ex_1005_init */							/* Zenith Z-Station EX MDII (1.00.05.BFU0)                  */
/* See machine_at_zenith_z_station_ex_1007_init */							/* Zenith Z-Station EX MDII (1.00.07.BFU0)                  */
/* See machine_at_zenith_z_station_ex_1009_init */							/* Zenith Z-Station EX MDII (1.00.09.BFU0)                  */
/* See machine_at_zenith_z_station_ex_1011_init */							/* Zenith Z-Station EX MDII (1.00.11.BFU0)                  */
extern int	machine_at_zenith_z_station_gt_init(const machine_t *);			/* Zenith Z-Station GT                                      */
extern int	machine_at_zenith_z_station_gt_1001_init(const machine_t *);	/* Zenith Z-Station GT      (1.00.01.CA0U)                  */
extern int	machine_at_zenith_z_station_gt_1002_init(const machine_t *);	/* Zenith Z-Station GT      (1.00.02.CA0U)                  */
extern int	machine_at_zenith_z_station_gt_1007_init(const machine_t *);	/* Zenith Z-Station GT      (1.00.07.CA0U)                  */
extern int	machine_at_zenith_z_station_gt_1009_init(const machine_t *);	/* Zenith Z-Station GT      (1.00.09.CA0U)                  */

/* Zenon Computer Systems */
extern int	machine_at_zenon_z_optimuspentium_60mhz_init(const machine_t *);/* Zenon Z-Titan PCI Pentium 60MHz                          */
extern int	machine_at_zenon_z_titan_pentium_90mhz_init(const machine_t *);	/* Zenon Z-Titan     Pentium 90MHz                          */
extern int	machine_at_zenon_pci_dream_media_4x_init(const machine_t *);	/* Zenon         PCI Dream Media 4X                         */
extern int	machine_at_zenon_dream_media_init(const machine_t *);			/* Zenon             Dream Media P5-120                     */
extern int	machine_at_zenon_dream_media2_init(const machine_t *);			/* Zenon             Dream Media P5-120                     */
/* See above */																/* Zenon             Dream Media P5-133                     */
extern int	machine_at_zenon_dream_media_p_150_166_init(const machine_t *);	/* Zenon             Dream Media  P-150                     */
/* See above */																/* Zenon             Dream Media  P-166                     */

/* ZEOS */
extern int	machine_at_zeos_486_mart_07_init(const machine_t *);			/* ZEOS 486DX2-66 Upgradable (8/ 2/1993)                    */
extern int	machine_at_zeos_486_mart_07s_init(const machine_t *);			/* ZEOS 486DX2-66 Upgradable (8/ 2/1993)(SCSI)              */
extern int	machine_at_zeos_486_mart_10_init(const machine_t *);			/* ZEOS 486DX2-66 Upgradable(11/11/1993)                    */
extern int	machine_at_zeos_486_mart_10s_init(const machine_t *);			/* ZEOS 486DX2-66 Upgradable(11/11/1993)(SCSI)              */
extern int	machine_at_zeos_486_mart_11_init(const machine_t *);			/* ZEOS 486DX2-66 Upgradable(12/31/1993)                    */
extern int	machine_at_zeos_486_mart_11s_init(const machine_t *);			/* ZEOS 486DX2-66 Upgradable(12/31/1993)(SCSI)              */
extern int	machine_at_zeos_486_mart_12b_init(const machine_t *);			/* ZEOS 486DX2-66 Upgradable (3/17/1994)                    */
extern int	machine_at_zeos_486_mart_12bs_init(const machine_t *);			/* ZEOS 486DX2-66 Upgradable (3/17/1994)(SCSI)              */
/* See below */																/* ZEOS Pantera 60                                          */
extern int	machine_at_zeos_pantera_cobra12_init(const machine_t *);		/* ZEOS Pantera 60 (11/30/1994)                             */
extern int	machine_at_zeos_pantera_cobra13_init(const machine_t *);		/* ZEOS Pantera 60 (07/14/1995)                             */
/* See above */																/* ZEOS Pantera 66                                          */
/* See above */																/* ZEOS Pantera 66 (11/30/1994)                             */
/* See above */																/* ZEOS Pantera 66 (07/14/1995)                             */
/* See above */																/* ZEOS Pantera 90                                          */
/* See above */																/* ZEOS Pantera 90 (11/30/1994)                             */
/* See above */																/* ZEOS Pantera 90 (07/14/1995)                             */
extern int	machine_at_zeos_pantera_pentium_init(const machine_t *);		/* ZEOS Pantera Pentium-75                                  */
/* See above */																/* ZEOS Pantera Pentium-90                                  */
/* See above */																/* ZEOS Pantera Pentium-100                                 */
/* See above */																/* ZEOS Pantera Pentium-120                                 */
extern int	machine_at_zeos_pantera_133mhz_init(const machine_t *);			/* ZEOS Pantera 75MHz                                       */
/* See above */																/* ZEOS Pantera 90MHz                                       */
/* See above */																/* ZEOS Pantera 100MHz                                      */
/* See above */																/* ZEOS Pantera 120MHz                                      */
/* See above */																/* ZEOS Pantera 133MHz                                      */

/* Zodiac Technologies */
/* See FiveStar Computers */

/* ZOOMMAX Computers (LOCAL RETAILER) */
extern int	machine_at_zoommax_486_dx2_66_mhz_air_init(const machine_t *);	/* ZOOMMAX 486 DX2-66 MHz (AiR)                             */

#endif	/*EMU_MACHINE_H*/
