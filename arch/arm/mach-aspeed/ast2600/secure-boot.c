// SPDX-License-Identifier: GPL-2.0-or-later
// (C) Copyright IBM Corp. 2022

#include <common.h>
#include <asm-generic/gpio.h>
#include <dm.h>

static int aspeed_get_chained_secboot_state(void)
{
	struct gpio_desc desc;
	struct udevice *dev;
	int secboot;
	int rc;

	rc = uclass_get_device_by_driver(UCLASS_GPIO,
					 DM_GET_DRIVER(gpio_aspeed),
					 &dev);
	if (rc < 0) {
		debug("Warning: GPIO initialization failure: %d\n", rc);
		return rc;
	}

	rc = gpio_request_by_line_name(dev, "bmc-secure-boot", &desc,
				       GPIOD_IS_IN);
	if (rc < 0) {
		debug("Failed to acquire secure-boot GPIO: %d\n", rc);
		return rc;
	}

	secboot = dm_gpio_get_value(&desc);
	if (secboot < 0)
		debug("Failed to read secure-boot GPIO value: %d\n", rc);

	rc = dm_gpio_free(dev, &desc);
	if (rc < 0)
		debug("Failed to free secure-boot GPIO: %d\n", rc);

	return secboot;
}

int board_fit_image_require_verified(void)
{
	int secboot;

	secboot = aspeed_get_chained_secboot_state();

	/*
	 * If secure-boot is enabled then require signature verification.
	 * Otherwise, if we fail to read the GPIO, enforce FIT signature
	 * verification
	 */
	return secboot >= 0 ? secboot : 1;
}
