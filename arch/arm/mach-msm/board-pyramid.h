/* Copyright (C) 2010-2011 HTC Corporation.
 * Copyright (c) 2013 Sebastian Sobczyk <sebastiansobczyk@wp.pl>
 *
 * Copyright (c) 2014 Sultanxda <sultanxda@gmail.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ARCH_ARM_MACH_MSM_BOARD_PYRAMID_H
#define __ARCH_ARM_MACH_MSM_BOARD_PYRAMID_H

#include <mach/board.h>
#include <mach/msm_memtypes.h>

/*** Memory map ***/
#define MSM_SMI_SIZE         0x4000000
#define MSM_ION_SF_SIZE      0x29A0000
#define MSM_ION_MM_FW_SIZE   0x200000
#define MSM_ION_MM_SIZE      0x3400000
#define MSM_ION_WB_SIZE      0x2FD000
#define MSM_ION_CAMERA_SIZE  0x2000000
#define MSM_ION_AUDIO_SIZE   0x4CF000

#define MSM_ION_HEAP_NUM     7

#define MSM_SMI_BASE         0x38000000
#define MSM_ION_MM_FW_BASE   0x38000000
#define MSM_ION_MM_BASE      0x38200000
#define MSM_FB_BASE          0x3B600000
#define MSM_ION_SF_BASE      0x40400000
#define MSM_ION_WB_BASE      0x46400000
#define MSM_ION_AUDIO_BASE   0x6DB00000
#define MSM_ION_CAMERA_BASE  0x6E000000

#define PHY_BASE_ADDR1       0x48000000
#define SIZE_ADDR1           0x25B00000
/*** END Memory map ***/

#define MSM_RAM_CONSOLE_BASE	MSM_HTC_RAM_CONSOLE_PHYS
#define MSM_RAM_CONSOLE_SIZE	MSM_HTC_RAM_CONSOLE_SIZE

#define PYRAMID_GPIO_KEY_POWER          (125)

#define PYRAMID_GPIO_MBAT_IN            (61)
#define PYRAMID_GPIO_CHG_INT		(126)

#define PYRAMID_GPIO_WIFI_IRQ              (46)
#define PYRAMID_GPIO_WIFI_SHUTDOWN_N       (96)

#define PYRAMID_SENSOR_I2C_SDA		(72)
#define PYRAMID_SENSOR_I2C_SCL		(73)
#define PYRAMID_GYRO_INT               (127)
#define PYRAMID_ECOMPASS_INT           (128)
#define PYRAMID_GSENSOR_INT           (129)

#define PYRAMID_GENERAL_I2C_SDA		(59)
#define PYRAMID_GENERAL_I2C_SCL		(60)

#define PYRAMID_FLASH_EN             (29)
#define PYRAMID_TORCH_EN             (30)

#define PYRAMID_GPIO_AUD_HP_DET        (31)

#define PYRAMID_SPI_DO                 (33)
#define PYRAMID_SPI_DI                 (34)
#define PYRAMID_SPI_CS                 (35)
#define PYRAMID_SPI_CLK                (36)

#define PYRAMID_TP_I2C_SDA           (51)
#define PYRAMID_TP_I2C_SCL           (52)
#define PYRAMID_TP_ATT_N             (65)
#define PYRAMID_TP_ATT_N_XB       (50)

#define GPIO_LCD_TE	(28)

#define GPIO_LCM_RST_N			(66)
#define GPIO_LCM_ID			(50)

#define PYRAMID_AUD_CODEC_RST        (67)

#define PYRAMID_GPIO_BT_HOST_WAKE      (45)
#define PYRAMID_GPIO_BT_UART1_TX       (53)
#define PYRAMID_GPIO_BT_UART1_RX       (54)
#define PYRAMID_GPIO_BT_UART1_CTS      (55)
#define PYRAMID_GPIO_BT_UART1_RTS      (56)
#define PYRAMID_GPIO_BT_SHUTDOWN_N     (100)
#define PYRAMID_GPIO_BT_CHIP_WAKE      (130)
#define PYRAMID_GPIO_BT_RESET_N        (142)

#define PYRAMID_GPIO_USB_ID        (63)
#define PYRAMID_GPIO_MHL_RESET        (70)
#define PYRAMID_GPIO_MHL_INT        (71)
#define PYRAMID_GPIO_MHL_USB_SWITCH        (99)

#define PYRAMID_CAM_CAM1_ID           (10)
#define PYRAMID_CAM_I2C_SDA           (47)
#define PYRAMID_CAM_I2C_SCL           (48)

#define PYRAMID_GPIO_CAM_MCLK     	 (32)
#define PYRAMID_GPIO_CAM_VCM_PD      (58)
#define PYRAMID_GPIO_CAM1_RSTz       (137)
#define PYRAMID_GPIO_CAM2_RSTz       (138)
#define PYRAMID_GPIO_CAM2_PWDN       (140)
#define PYRAMID_GPIO_MCLK_SWITCH     (141)

#define PMGPIO(x) (x-1)
#define PYRAMID_VOL_UP             PMGPIO(16)
#define PYRAMID_VOL_DN             PMGPIO(17)
#define PYRAMID_AUD_HP_EN          PMGPIO(18)
#define PYRAMID_HAP_ENABLE         PMGPIO(19)
#define PYRAMID_AUD_QTR_RESET      PMGPIO(21)
#define PYRAMID_TP_RST             PMGPIO(23)
#define PYRAMID_GREEN_LED          PMGPIO(24)
#define PYRAMID_AMBER_LED          PMGPIO(25)
#define PYRAMID_AUD_MIC_SEL        PMGPIO(26)
#define PYRAMID_CHG_STAT           PMGPIO(33)
#define PYRAMID_SDC3_DET           PMGPIO(34)
#define PYRAMID_PLS_INT            PMGPIO(35)
#define PYRAMID_AUD_REMO_PRES      PMGPIO(37)
#define PYRAMID_WIFI_BT_SLEEP_CLK  PMGPIO(38)

extern int panel_type;

int __init pyramid_init_mmc(void);
void __init pyramid_audio_init(void);
int __init pyramid_init_keypad(void);
int __init pyramid_wifi_init(void);

void pyramid_init_fb(void);
void pyramid_allocate_fb_region(void);
void __init pyramid_mdp_writeback(struct memtype_reserve* reserve_table);

#endif 
