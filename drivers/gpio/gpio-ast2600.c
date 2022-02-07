// SPDX-License-Identifier: GPL-2.0-or-later
/* Copyright IBM Corp. 2022 */

#include <common.h>
#include <dm.h>
#include <linux/bitfield.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/sizes.h>
#include <linux/errno.h>
#include <asm/gpio.h>

#define AST2600_GPIO			0x2ac
#define   AST2600_GPIO_DATA		GENMASK(31, 20)
#define     AST2600_GPIO_DATA_DIR_IN	0
#define     AST2600_GPIO_DATA_DIR_OUT	1
#define   AST2600_GPIO_TYPE		GENMASK(19, 16)
#define     AST2600_GPIO_TYPE_DATA	0
#define     AST2600_GPIO_TYPE_DIR	1
#define   AST2600_GPIO_COMMAND		BIT(12)
#define     AST2600_GPIO_WRITE		0
#define     AST2600_GPIO_READ		1
#define   AST2600_GPIO_NUMBER		GENMASK(7, 0)
#define AST2600_GPIO_MAX		0xcf

struct ast2600_gpio_priv {
	void __iomem *base;
	void __iomem *reg;
};

static int ast2600_gpio_writel(const struct udevice *dev, unsigned int offset, u32 type, u32 data)
{
	struct ast2600_gpio_priv *priv = dev_get_priv(dev);
	u32 cmd = 0;

	cmd |= FIELD_PREP(AST2600_GPIO_DATA, data);
	cmd |= FIELD_PREP(AST2600_GPIO_TYPE, type);
	cmd |= FIELD_PREP(AST2600_GPIO_COMMAND, AST2600_GPIO_WRITE);
	cmd |= FIELD_PREP(AST2600_GPIO_NUMBER, offset);
	writel(cmd, priv->reg);

	return 0;
}

static int ast2600_gpio_readl(const struct udevice *dev, unsigned int offset, u32 type)
{
	struct ast2600_gpio_priv *priv = dev_get_priv(dev);
	u32 cmd = 0;
	u32 data;

	cmd |= FIELD_PREP(AST2600_GPIO_TYPE, type);
	cmd |= FIELD_PREP(AST2600_GPIO_COMMAND, AST2600_GPIO_READ);
	cmd |= FIELD_PREP(AST2600_GPIO_NUMBER, offset);
	writel(cmd, priv->reg);

	data = readl(priv->reg);
	return FIELD_GET(AST2600_GPIO_DATA, data);
}

static int ast2600_gpio_direction_set(struct udevice *dev, unsigned int offset, int direction)
{
	return ast2600_gpio_writel(dev, offset, AST2600_GPIO_TYPE_DIR, direction);
}

static int ast2600_gpio_direction_input(struct udevice *dev, unsigned int offset)
{
	return ast2600_gpio_direction_set(dev, offset, AST2600_GPIO_DATA_DIR_IN);
}

static int ast2600_gpio_direction_output(struct udevice *dev, unsigned int offset, int value)
{
	ast2600_gpio_writel(dev, offset, AST2600_GPIO_TYPE_DATA, value);
	return ast2600_gpio_direction_set(dev, offset, AST2600_GPIO_DATA_DIR_OUT);
}

static int ast2600_gpio_get_value(struct udevice *dev, unsigned int offset)
{
	return ast2600_gpio_readl(dev, offset, AST2600_GPIO_TYPE_DATA);
}

static int ast2600_gpio_set_value(struct udevice *dev, unsigned int offset, int value)
{
	return ast2600_gpio_writel(dev, offset, AST2600_GPIO_TYPE_DATA, value);
}

static int ast2600_gpio_get_function(struct udevice *dev, unsigned int offset)
{
	return ast2600_gpio_readl(dev, offset, AST2600_GPIO_TYPE_DIR) ? GPIOF_OUTPUT : GPIOF_INPUT;
}

static const struct dm_gpio_ops ast2600_gpio_ops = {
	.direction_input	= ast2600_gpio_direction_input,
	.direction_output	= ast2600_gpio_direction_output,
	.get_value		= ast2600_gpio_get_value,
	.set_value		= ast2600_gpio_set_value,
	.get_function		= ast2600_gpio_get_function,
};

static int ast2600_gpio_probe(struct udevice *dev)
{
	struct ast2600_gpio_priv *priv = dev_get_priv(dev);
	struct gpio_dev_priv *uc_priv = dev_get_uclass_priv(dev);
	fdt_addr_t addr;

	uc_priv->gpio_count = fdtdec_get_uint(gd->fdt_blob, dev_of_offset(dev),
					      "ngpios", 0);

	if (uc_priv->gpio_count > AST2600_GPIO_MAX)
		return -EINVAL;

	addr = dev_read_addr(dev);
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	priv->base = devm_ioremap(dev, addr, SZ_4K);
	if (!priv->base)
		return -ENOMEM;

	priv->reg = priv->base + AST2600_GPIO;

	return 0;
}

static const struct udevice_id ast2600_gpio_match[] = {
	{ .compatible = "aspeed,ast2600-gpio" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(ast2600_gpio) = {
	.name		= "gpio-ast2600",
	.id		= UCLASS_GPIO,
	.of_match	= ast2600_gpio_match,
	.probe		= ast2600_gpio_probe,
	.priv_auto	= sizeof(struct ast2600_gpio_priv),
	.ops		= &ast2600_gpio_ops,
};
