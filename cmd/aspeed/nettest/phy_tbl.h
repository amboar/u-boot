/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) ASPEED Technology Inc.
 */
void recov_phy_marvell(MAC_ENGINE *eng);
void phy_marvell(MAC_ENGINE *eng);
void recov_phy_marvell0(MAC_ENGINE *eng);
void phy_marvell0(MAC_ENGINE *eng);
void recov_phy_marvell1(MAC_ENGINE *eng);
void phy_marvell1(MAC_ENGINE *eng);
void recov_phy_marvell2(MAC_ENGINE *eng);
void phy_marvell2(MAC_ENGINE *eng);
void phy_marvell3(MAC_ENGINE *eng);
void phy_broadcom(MAC_ENGINE *eng);
void recov_phy_broadcom0(MAC_ENGINE *eng);
void phy_broadcom0(MAC_ENGINE *eng);
void phy_realtek(MAC_ENGINE *eng);
void phy_realtek0(MAC_ENGINE *eng);
void recov_phy_realtek1(MAC_ENGINE *eng);
void phy_realtek1(MAC_ENGINE *eng);
void recov_phy_realtek2(MAC_ENGINE *eng);
void recov_phy_realtek3(MAC_ENGINE *eng);
void phy_realtek3(MAC_ENGINE *eng);
void phy_realtek4(MAC_ENGINE *eng);
void phy_realtek2(MAC_ENGINE *eng);
void recov_phy_realtek5(MAC_ENGINE *eng);
void phy_realtek5(MAC_ENGINE *eng);
void phy_realtek6(MAC_ENGINE *eng);
void phy_smsc(MAC_ENGINE *eng);
void phy_micrel(MAC_ENGINE *eng);
void phy_micrel0(MAC_ENGINE *eng);
void phy_micrel1(MAC_ENGINE *eng);
void phy_micrel2(MAC_ENGINE *eng);
void recov_phy_vitesse(MAC_ENGINE *eng);
void phy_vitesse(MAC_ENGINE *eng);
void recov_phy_atheros(MAC_ENGINE *eng);
void phy_atheros(MAC_ENGINE *eng);
void phy_default(MAC_ENGINE *eng);

struct phy_desc {
	uint16_t id1;
	uint16_t id2;
	uint16_t id2_mask;
	uint8_t name[64];
	PHY_ENGINE cfg;
};

#define PHY_LOOKUP_N 34
static const struct phy_desc phy_lookup_tbl[PHY_LOOKUP_N] = {
	{ .id1 = 0x001c,
	  .id2 = 0xc916,
	  .id2_mask = 0xffff,
	  .name = "RTL8211F",
	  .cfg.fp_set = phy_realtek5,
	  .cfg.fp_clr = recov_phy_realtek5 },
	{ .id1 = 0x001c,
	  .id2 = 0xc859,
	  .id2_mask = 0xffff,
	  .name = "RTL8211FD-VX",
	  .cfg.fp_set = phy_realtek5,
	  .cfg.fp_clr = recov_phy_realtek5 },
	{ .id1 = 0x001c,
	  .id2 = 0xc915,
	  .id2_mask = 0xffff,
	  .name = "RTL8211E",
	  .cfg.fp_set = phy_realtek2,
	  .cfg.fp_clr = recov_phy_realtek2 },
	{ .id1 = 0x001c,
	  .id2 = 0xc914,
	  .id2_mask = 0xffff,
	  .name = "RTL8211D",
	  .cfg.fp_set = phy_realtek1,
	  .cfg.fp_clr = recov_phy_realtek1 },
	{ .id1 = 0x001c,
	  .id2 = 0xc912,
	  .id2_mask = 0xffff,
	  .name = "RTL8211C",
	  .cfg.fp_set = phy_realtek3,
	  .cfg.fp_clr = recov_phy_realtek3 },
	{ .id1 = 0x001c,
	  .id2 = 0xc930,
	  .id2_mask = 0xffff,
	  .name = "RTL8363S",
	  .cfg.fp_set = phy_realtek6,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x001c,
	  .id2 = 0xc816,
	  .id2_mask = 0xffff,
	  .name = "RTL8201F",
	  .cfg.fp_set = phy_realtek4,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x001c,
	  .id2 = 0xc815,
	  .id2_mask = 0xfff0,
	  .name = "RTL8201E",
	  .cfg.fp_set = phy_realtek0,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x0000,
	  .id2 = 0x8201,
	  .id2_mask = PHYID3_Mask,
	  .name = "RTL8201N",
	  .cfg.fp_set = phy_realtek,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x0143,
	  .id2 = 0xbcb2,
	  .id2_mask = 0xfff0,
	  .name = "BCM5482",
	  .cfg.fp_set = phy_broadcom0,
	  .cfg.fp_clr = recov_phy_broadcom0 },
	{ .id1 = 0x0143,
	  .id2 = 0xbca0,
	  .id2_mask = 0xfff0,
	  .name = "BCM5481",
	  .cfg.fp_set = phy_broadcom0,
	  .cfg.fp_clr = recov_phy_broadcom0 },
	{ .id1 = 0x0362,
	  .id2 = 0x5e6a,
	  .id2_mask = 0xfff0,
	  .name = "BCM54612",
	  .cfg.fp_set = phy_broadcom0,
	  .cfg.fp_clr = recov_phy_broadcom0 },
	{ .id1 = 0x0362,
	  .id2 = 0x5d10,
	  .id2_mask = 0xfff0,
	  .name = "BCM54616S",
	  .cfg.fp_set = phy_broadcom0,
	  .cfg.fp_clr = recov_phy_broadcom0 },
	{ .id1 = 0x0020,
	  .id2 = 0x60b0,
	  .id2_mask = 0xfff0,
	  .name = "BCM5464SR",
	  .cfg.fp_set = phy_broadcom0,
	  .cfg.fp_clr = recov_phy_broadcom0 },
	{ .id1 = 0x0020,
	  .id2 = 0x60c1,
	  .id2_mask = 0xfff0,
	  .name = "BCM5461S",
	  .cfg.fp_set = phy_broadcom0,
	  .cfg.fp_clr = recov_phy_broadcom0 },
	{ .id1 = 0x600d,
	  .id2 = 0x84a2,
	  .id2_mask = 0xfff0,
	  .name = "BCM5421x",
	  .cfg.fp_set = phy_broadcom0,
	  .cfg.fp_clr = recov_phy_broadcom0 },
	{ .id1 = 0x0143,
	  .id2 = 0xbd63,
	  .id2_mask = 0xfff0,
	  .name = "BCM54610C",
	  .cfg.fp_set = phy_broadcom0,
	  .cfg.fp_clr = recov_phy_broadcom0 },
	{ .id1 = 0x0040,
	  .id2 = 0x61e0,
	  .id2_mask = PHYID3_Mask,
	  .name = "BCM5221",
	  .cfg.fp_set = phy_broadcom,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x0141,
	  .id2 = 0x0e22,
	  .id2_mask = 0xfff0,
	  .name = "88E3019",
	  .cfg.fp_set = phy_marvell3,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x0141,
	  .id2 = 0x0dd0,
	  .id2_mask = 0xfff0,
	  .name = "88E15 10/12/14/18",
	  .cfg.fp_set = phy_marvell2,
	  .cfg.fp_clr = recov_phy_marvell2 },
	{ .id1 = 0xff00,
	  .id2 = 0x1761,
	  .id2_mask = 0xffff,
	  .name = "88E6176(IntLoop)",
	  .cfg.fp_set = phy_marvell1,
	  .cfg.fp_clr = recov_phy_marvell1 },
	{ .id1 = 0xff00,
	  .id2 = 0x1152,
	  .id2_mask = 0xffff,
	  .name = "88E6320(IntLoop)",
	  .cfg.fp_set = phy_marvell1,
	  .cfg.fp_clr = recov_phy_marvell1 },
	{ .id1 = 0x0141,
	  .id2 = 0x0e90,
	  .id2_mask = 0xfff0,
	  .name = "88E1310",
	  .cfg.fp_set = phy_marvell0,
	  .cfg.fp_clr = recov_phy_marvell0 },
	{ .id1 = 0x0141,
	  .id2 = 0x0cc0,
	  .id2_mask = PHYID3_Mask,
	  .name = "88E1111",
	  .cfg.fp_set = phy_marvell,
	  .cfg.fp_clr = recov_phy_marvell },
	{ .id1 = 0x0022,
	  .id2 = 0x1555,
	  .id2_mask = 0xfff0,
	  .name = "KSZ8031/KSZ8051",
	  .cfg.fp_set = phy_micrel0,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x0022,
	  .id2 = 0x1622,
	  .id2_mask = 0xfff0,
	  .name = "KSZ9031",
	  .cfg.fp_set = phy_micrel1,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x0022,
	  .id2 = 0x1562,
	  .id2_mask = 0xfff0,
	  .name = "KSZ8081",
	  .cfg.fp_set = phy_micrel2,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x0022,
	  .id2 = 0x1512,
	  .id2_mask = 0xfff0,
	  .name = "KSZ8041",
	  .cfg.fp_set = phy_micrel,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x004d,
	  .id2 = 0xd072,
	  .id2_mask = 0xfff0,
	  .name = "AR8035",
	  .cfg.fp_set = phy_atheros,
	  .cfg.fp_clr = recov_phy_atheros },
	{ .id1 = 0x0007,
	  .id2 = 0xc0c4,
	  .id2_mask = PHYID3_Mask,
	  .name = "LAN8700",
	  .cfg.fp_set = phy_smsc,
	  .cfg.fp_clr = NULL },
	{ .id1 = 0x000f,
	  .id2 = 0xc4b1,
	  .id2_mask = 0xfff0,
	  .name = "VSC8211",
	  .cfg.fp_set = phy_vitesse,
	  .cfg.fp_clr = recov_phy_vitesse },
	{ .id1 = 0x0007,
	  .id2 = 0x0421,
	  .id2_mask = 0xfff0,
	  .name = "VSC8601",
	  .cfg.fp_set = phy_vitesse,
	  .cfg.fp_clr = recov_phy_vitesse },
	{ .id1 = 0x0007,
	  .id2 = 0x0431,
	  .id2_mask = 0xfff0,
	  .name = "VSC8641",
	  .cfg.fp_set = phy_vitesse,
	  .cfg.fp_clr = recov_phy_vitesse },
	{ .id1 = 0x0000,
	  .id2 = 0x0000,
	  .id2_mask = 0x0000,
	  .name = "default",
	  .cfg.fp_set = phy_default,
	  .cfg.fp_clr = NULL },
};