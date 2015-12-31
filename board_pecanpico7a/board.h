/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for STMicroelectronics STM32F429I-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_PECANPICO7
#define BOARD_NAME                  "Pecan Pico 7"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                26000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   250U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F429xx

/*

 * IO pins assignments.
 */
#define GPIOA_UART_TX               0U
#define GPIOA_UART_RX               1U
#define GPIOA_UART_GPS_TX           2U
#define GPIOA_UART_GPS_RX           3U
#define GPIOA_CAM_HREF              4U
#define GPIOA_PIN5                  5U
#define GPIOA_CAM_PCLK              6U
#define GPIOA_RADIO1_PWR_REF        7U
#define GPIOA_CAM_XCLK              8U
#define GPIOA_RADIO1_GPIO1          9U
#define GPIOA_RADIO1_GPIO0          10U
#define GPIOA_RADIO1_CS             11U
#define GPIOA_RADIO1_SDN            12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_SD_CS                 15U

#define GPIOB_RADIO2_CS             0U
#define GPIOB_RADIO1_PWR_SENSE      1U
#define GPIOB_BOOT1                 2U
#define GPIOB_SWO                   3U
#define GPIOB_PIN4                  4U
#define GPIOB_PIN5                  5U
#define GPIOB_CAM_D7                6U
#define GPIOB_CAM_VSYNC             7U
#define GPIOB_CAM_SCL               8U
#define GPIOB_CAM_SDA               9U
#define GPIOB_I2C_SCL               10U
#define GPIOB_I2C_SDA               11U
#define GPIOB_RADIO2_SDN            12U
#define GPIOB_SPI_SCK               13U
#define GPIOB_SPI_MISO              14U
#define GPIOB_SPI_MOSI              15U

#define GPIOC_PIN0                  0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_PIN3                  3U
#define GPIOC_ADC_VSOLAR            4U
#define GPIOC_ADC_VBAT_DIFF         5U
#define GPIOC_CAM_D2                6U
#define GPIOC_CAM_D3                7U
#define GPIOC_CAM_D4                8U
#define GPIOC_CAM_D5                9U
#define GPIOC_SD_SCK                10U
#define GPIOC_SD_MISO               11U
#define GPIOC_SD_MOSI               12U
#define GPIOC_LED2                  13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_LED1                  15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_CAM_OFF               0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_LED3                  3U
#define GPIOE_CAM_D6                4U
#define GPIOE_CAM_D8                5U
#define GPIOE_CAM_D9                6U
#define GPIOE_GPS_OFF               7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_GPS_TIMEPULSE         10U
#define GPIOE_PIN11                 11U
#define GPIOE_GPS_RESET             12U
#define GPIOE_RADIO2_GPIO0          13U
#define GPIOE_RADIO2_GPIO1          14U
#define GPIOE_MPU_INT               15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_PIN0                  0U
#define GPIOH_PIN1                  1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_UART_TX                PAL_LINE(GPIOA, 0U)
#define LINE_UART_RX                PAL_LINE(GPIOA, 1U)
#define LINE_UART_GPS_TX            PAL_LINE(GPIOA, 2U)
#define LINE_UART_GPS_RX            PAL_LINE(GPIOA, 3U)
#define LINE_CAM_HREF               PAL_LINE(GPIOA, 4U)
#define LINE_CAM_PCLK               PAL_LINE(GPIOA, 6U)
#define LINE_RADIO1_PWR_REF         PAL_LINE(GPIOA, 7U)
#define LINE_CAM_XCLK               PAL_LINE(GPIOA, 8U)
#define LINE_RADIO1_GPIO1           PAL_LINE(GPIOA, 9U)
#define LINE_RADIO1_GPIO0           PAL_LINE(GPIOA, 10U)
#define LINE_RADIO1_CS              PAL_LINE(GPIOA, 11U)
#define LINE_RADIO1_SDN             PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_SD_CS                  PAL_LINE(GPIOA, 15U)

#define LINE_RADIO2_CS              PAL_LINE(GPIOB, 0U)
#define LINE_RADIO1_PWR_SENSE       PAL_LINE(GPIOB, 1U)
#define LINE_BOOT1                  PAL_LINE(GPIOB, 2U)
#define LINE_CAM_D7                 PAL_LINE(GPIOB, 6U)
#define LINE_CAM_VSYNC              PAL_LINE(GPIOB, 7U)
#define LINE_CAM_SCL                PAL_LINE(GPIOB, 8U)
#define LINE_CAM_SDA                PAL_LINE(GPIOB, 9U)
#define LINE_I2C_SCL                PAL_LINE(GPIOB, 10U)
#define LINE_I2C_SDA                PAL_LINE(GPIOB, 11U)
#define LINE_RADIO2_SDN             PAL_LINE(GPIOB, 12U)
#define LINE_SPI_SCK                PAL_LINE(GPIOB, 13U)
#define LINE_SPI_MISO               PAL_LINE(GPIOB, 14U)
#define LINE_SPI_MOSI               PAL_LINE(GPIOB, 15U)

#define LINE_ADC_VSOLAR             PAL_LINE(GPIOC, 4U)
#define LINE_ADC_VBAT_DIFF          PAL_LINE(GPIOC, 5U)
#define LINE_CAM_D2                 PAL_LINE(GPIOC, 6U)
#define LINE_CAM_D3                 PAL_LINE(GPIOC, 7U)
#define LINE_CAM_D4                 PAL_LINE(GPIOC, 8U)
#define LINE_CAM_D5                 PAL_LINE(GPIOC, 9U)
#define LINE_SD_SCK                 PAL_LINE(GPIOC, 10U)
#define LINE_SD_MISO                PAL_LINE(GPIOC, 11U)
#define LINE_SD_MOSI                PAL_LINE(GPIOC, 12U)
#define LINE_LED2                   PAL_LINE(GPIOC, 13U)
#define LINE_OSC32_IN               PAL_LINE(GPIOC, 14U)
#define LINE_LED1                   PAL_LINE(GPIOC, 15U)

#define LINE_CAM_OFF                PAL_LINE(GPIOE, 0U)
#define LINE_PIN1                   PAL_LINE(GPIOE, 1U)
#define LINE_PIN2                   PAL_LINE(GPIOE, 2U)
#define LINE_LED3                   PAL_LINE(GPIOE, 3U)
#define LINE_CAM_D6                 PAL_LINE(GPIOE, 4U)
#define LINE_CAM_D8                 PAL_LINE(GPIOE, 5U)
#define LINE_CAM_D9                 PAL_LINE(GPIOE, 6U)
#define LINE_GPS_OFF                PAL_LINE(GPIOE, 7U)
#define LINE_PIN8                   PAL_LINE(GPIOE, 8U)
#define LINE_PIN9                   PAL_LINE(GPIOE, 9U)
#define LINE_GPS_TIMEPULSE          PAL_LINE(GPIOE, 10U)
#define LINE_PIN11                  PAL_LINE(GPIOE, 11U)
#define LINE_GPS_RESET              PAL_LINE(GPIOE, 12U)
#define LINE_RADIO2_GPIO0           PAL_LINE(GPIOE, 13U)
#define LINE_RADIO2_GPIO1           PAL_LINE(GPIOE, 14U)
#define LINE_MPU_INT                PAL_LINE(GPIOE, 15U)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - UART_TX                   (alternate 8)
 * PA1  - UART_RX                   (alternate 8)
 * PA2  - UART_GPS_TX               (alternate 7)
 * PA3  - UART_GPS_RX               (alternate 7)
 * PA4  - CAM_HREF                  (alternate 13)
 * PA5  - PIN5                      (input pullup)
 * PA6  - CAM_PCLK                  (alternate 13)
 * PA7  - RADIO1_PWR_REF            (input floating)
 * PA8  - CAM_XCLK                  (alternate 0)
 * PA9  - RADIO1_GPIO1              (output pushpull maximum)
 * PA10 - RADIO1_GPIO0              (output pushpull maximum)
 * PA11 - RADIO1_CS                 (output pushpull maximum)
 * PA12 - RADIO1_SDN                (output pushpull maximum)
 * PA13 - SWDIO                     (alternate 0)
 * PA14 - SWCLK                     (alternate 0)
 * PA15 - SD_CS                     (output pushpull maximum)
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ALTERNATE(GPIOA_UART_TX) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_UART_RX) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_UART_GPS_TX) |\
                                     PIN_MODE_ALTERNATE(GPIOA_UART_GPS_RX) |\
                                     PIN_MODE_ALTERNATE(GPIOA_CAM_HREF) |   \
                                     PIN_MODE_INPUT(GPIOA_PIN5) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_CAM_PCLK) |   \
                                     PIN_MODE_INPUT(GPIOA_RADIO1_PWR_REF) | \
                                     PIN_MODE_ALTERNATE(GPIOA_CAM_XCLK) |   \
                                     PIN_MODE_OUTPUT(GPIOA_RADIO1_GPIO1) |  \
                                     PIN_MODE_OUTPUT(GPIOA_RADIO1_GPIO0) |  \
                                     PIN_MODE_OUTPUT(GPIOA_RADIO1_CS) |     \
                                     PIN_MODE_OUTPUT(GPIOA_RADIO1_SDN) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_OUTPUT(GPIOA_SD_CS))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_UART_TX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART_RX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART_GPS_TX) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART_GPS_RX) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_CAM_HREF) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_CAM_PCLK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RADIO1_PWR_REF)|\
                                     PIN_OTYPE_PUSHPULL(GPIOA_CAM_XCLK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RADIO1_GPIO1)|\
                                     PIN_OTYPE_PUSHPULL(GPIOA_RADIO1_GPIO0)|\
                                     PIN_OTYPE_PUSHPULL(GPIOA_RADIO1_CS) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RADIO1_SDN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SD_CS))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_UART_TX) |       \
                                     PIN_OSPEED_HIGH(GPIOA_UART_RX) |       \
                                     PIN_OSPEED_HIGH(GPIOA_UART_GPS_TX) |   \
                                     PIN_OSPEED_HIGH(GPIOA_UART_GPS_RX) |   \
                                     PIN_OSPEED_HIGH(GPIOA_CAM_HREF) |      \
                                     PIN_OSPEED_VERYLOW(GPIOA_PIN5) |       \
                                     PIN_OSPEED_HIGH(GPIOA_CAM_PCLK) |      \
                                     PIN_OSPEED_VERYLOW(GPIOA_RADIO1_PWR_REF)|\
                                     PIN_OSPEED_HIGH(GPIOA_CAM_XCLK) |      \
                                     PIN_OSPEED_LOW(GPIOA_RADIO1_GPIO1) |   \
                                     PIN_OSPEED_LOW(GPIOA_RADIO1_GPIO0) |   \
                                     PIN_OSPEED_HIGH(GPIOA_RADIO1_CS) |     \
                                     PIN_OSPEED_VERYLOW(GPIOA_RADIO1_SDN) | \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SD_CS))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLUP(GPIOA_UART_TX) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_UART_RX) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_UART_GPS_TX) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_UART_GPS_RX) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_CAM_HREF) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_CAM_PCLK) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_RADIO1_PWR_REF)|\
                                     PIN_PUPDR_PULLUP(GPIOA_CAM_XCLK) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_RADIO1_GPIO1) | \
                                     PIN_PUPDR_PULLUP(GPIOA_RADIO1_GPIO0) | \
                                     PIN_PUPDR_PULLUP(GPIOA_RADIO1_CS) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_RADIO1_SDN) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_SD_CS))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_UART_TX) |          \
                                     PIN_ODR_HIGH(GPIOA_UART_RX) |          \
                                     PIN_ODR_HIGH(GPIOA_UART_GPS_TX) |      \
                                     PIN_ODR_HIGH(GPIOA_UART_GPS_RX) |      \
                                     PIN_ODR_HIGH(GPIOA_CAM_HREF) |         \
                                     PIN_ODR_HIGH(GPIOA_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOA_CAM_PCLK) |         \
                                     PIN_ODR_HIGH(GPIOA_RADIO1_PWR_REF) |   \
                                     PIN_ODR_HIGH(GPIOA_CAM_XCLK) |         \
                                     PIN_ODR_HIGH(GPIOA_RADIO1_GPIO1) |     \
                                     PIN_ODR_HIGH(GPIOA_RADIO1_GPIO0) |     \
                                     PIN_ODR_HIGH(GPIOA_RADIO1_CS) |        \
                                     PIN_ODR_HIGH(GPIOA_RADIO1_SDN) |       \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_SD_CS))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_UART_TX, 8) |        \
                                     PIN_AFIO_AF(GPIOA_UART_RX, 8) |        \
                                     PIN_AFIO_AF(GPIOA_UART_GPS_TX, 7) |    \
                                     PIN_AFIO_AF(GPIOA_UART_GPS_RX, 7) |    \
                                     PIN_AFIO_AF(GPIOA_CAM_HREF, 13) |      \
                                     PIN_AFIO_AF(GPIOA_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOA_CAM_PCLK, 13) |      \
                                     PIN_AFIO_AF(GPIOA_RADIO1_PWR_REF, 0))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_CAM_XCLK, 0) |       \
                                     PIN_AFIO_AF(GPIOA_RADIO1_GPIO1, 0) |   \
                                     PIN_AFIO_AF(GPIOA_RADIO1_GPIO0, 0) |   \
                                     PIN_AFIO_AF(GPIOA_RADIO1_CS, 0) |      \
                                     PIN_AFIO_AF(GPIOA_RADIO1_SDN, 0) |     \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0) |          \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0) |          \
                                     PIN_AFIO_AF(GPIOA_SD_CS, 0))

/*
 * GPIOB setup:
 *
 * PB0  - RADIO2_CS                 (output pushpull maximum)
 * PB1  - RADIO1_PWR_SENSE          (input floating)
 * PB2  - BOOT1                     (input pullup)
 * PB3  - SWO                       (alternate 0)
 * PB4  - PIN4                      (input pullup)
 * PB5  - PIN5                      (input pullup)
 * PB6  - CAM_D7                    (alternate 13)
 * PB7  - CAM_VSYNC                 (alternate 13)
 * PB8  - CAM_SCL                   (alternate 4)
 * PB9  - CAM_SDA                   (alternate 4)
 * PB1  - I2C_SCL                   (alternate 4)
 * PB11 - I2C_SDA                   (alternate 4)
 * PB12 - RADIO2_SDN                (output pushpull maximum)
 * PB13 - SPI_SCK                   (alternate 5)
 * PB14 - SPI_MISO                  (alternate 5)
 * PB15 - SPI_MOSI                  (alternate 5)
 */
#define VAL_GPIOB_MODER             (PIN_MODE_OUTPUT(GPIOB_RADIO2_CS) |     \
                                     PIN_MODE_INPUT(GPIOB_RADIO1_PWR_SENSE)|\
                                     PIN_MODE_INPUT(GPIOB_BOOT1) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN5) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_CAM_D7) |     \
                                     PIN_MODE_ALTERNATE(GPIOB_CAM_VSYNC) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_CAM_SCL) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_CAM_SDA) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C_SCL) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C_SDA) |    \
                                     PIN_MODE_OUTPUT(GPIOB_RADIO2_SDN) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_SPI_SCK) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_SPI_MISO) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_SPI_MOSI))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_RADIO2_CS) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RADIO1_PWR_SENSE)|\
                                     PIN_OTYPE_PUSHPULL(GPIOB_BOOT1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAM_D7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAM_VSYNC) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_CAM_SCL) |   \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_CAM_SDA) |   \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C_SCL) |   \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C_SDA) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RADIO2_SDN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SPI_SCK) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SPI_MISO) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SPI_MOSI))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_RADIO2_CS) |     \
                                     PIN_OSPEED_VERYLOW(GPIOB_RADIO1_PWR_SENSE)|\
                                     PIN_OSPEED_HIGH(GPIOB_BOOT1) |         \
                                     PIN_OSPEED_HIGH(GPIOB_SWO) |           \
                                     PIN_OSPEED_VERYLOW(GPIOB_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_PIN5) |       \
                                     PIN_OSPEED_HIGH(GPIOB_CAM_D7) |        \
                                     PIN_OSPEED_HIGH(GPIOB_CAM_VSYNC) |     \
                                     PIN_OSPEED_HIGH(GPIOB_CAM_SCL) |       \
                                     PIN_OSPEED_HIGH(GPIOB_CAM_SDA) |       \
                                     PIN_OSPEED_HIGH(GPIOB_I2C_SCL) |       \
                                     PIN_OSPEED_HIGH(GPIOB_I2C_SDA) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_RADIO2_SDN) | \
                                     PIN_OSPEED_HIGH(GPIOB_SPI_SCK) |       \
                                     PIN_OSPEED_HIGH(GPIOB_SPI_MISO) |      \
                                     PIN_OSPEED_HIGH(GPIOB_SPI_MOSI))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_RADIO2_CS) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_RADIO1_PWR_SENSE)|\
                                     PIN_PUPDR_PULLUP(GPIOB_BOOT1) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_SWO) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_CAM_D7) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_CAM_VSYNC) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_CAM_SCL) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_CAM_SDA) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C_SCL) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C_SDA) |    \
                                     PIN_PUPDR_PULLUP(GPIOB_RADIO2_SDN) |   \
                                     PIN_PUPDR_PULLUP(GPIOB_SPI_SCK) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_SPI_MISO) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_SPI_MOSI))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_RADIO2_CS) |        \
                                     PIN_ODR_HIGH(GPIOB_RADIO1_PWR_SENSE) | \
                                     PIN_ODR_HIGH(GPIOB_BOOT1) |            \
                                     PIN_ODR_HIGH(GPIOB_SWO) |              \
                                     PIN_ODR_HIGH(GPIOB_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOB_CAM_D7) |           \
                                     PIN_ODR_HIGH(GPIOB_CAM_VSYNC) |        \
                                     PIN_ODR_HIGH(GPIOB_CAM_SCL) |          \
                                     PIN_ODR_HIGH(GPIOB_CAM_SDA) |          \
                                     PIN_ODR_HIGH(GPIOB_I2C_SCL) |          \
                                     PIN_ODR_HIGH(GPIOB_I2C_SDA) |          \
                                     PIN_ODR_HIGH(GPIOB_RADIO2_SDN) |       \
                                     PIN_ODR_HIGH(GPIOB_SPI_SCK) |          \
                                     PIN_ODR_HIGH(GPIOB_SPI_MISO) |         \
                                     PIN_ODR_HIGH(GPIOB_SPI_MOSI))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_RADIO2_CS, 0) |      \
                                     PIN_AFIO_AF(GPIOB_RADIO1_PWR_SENSE, 0)|\
                                     PIN_AFIO_AF(GPIOB_BOOT1, 0) |          \
                                     PIN_AFIO_AF(GPIOB_SWO, 0) |            \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOB_CAM_D7, 13) |        \
                                     PIN_AFIO_AF(GPIOB_CAM_VSYNC, 13))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_CAM_SCL, 4) |        \
                                     PIN_AFIO_AF(GPIOB_CAM_SDA, 4) |        \
                                     PIN_AFIO_AF(GPIOB_I2C_SCL, 4) |        \
                                     PIN_AFIO_AF(GPIOB_I2C_SDA, 4) |        \
                                     PIN_AFIO_AF(GPIOB_RADIO2_SDN, 0) |     \
                                     PIN_AFIO_AF(GPIOB_SPI_SCK, 5) |        \
                                     PIN_AFIO_AF(GPIOB_SPI_MISO, 5) |       \
                                     PIN_AFIO_AF(GPIOB_SPI_MOSI, 5))

/*
 * GPIOC setup:
 *
 * PC0  - PIN0                      (input pullup)
 * PC1  - PIN1                      (input pullup)
 * PC2  - PIN2                      (input pullup)
 * PC3  - PIN3                      (input pullup)
 * PC4  - ADC_VSOLAR                (input pullup)
 * PC5  - ADC_VBAT_DIFF             (input floating)
 * PC6  - CAM_D2                    (alternate 13)
 * PC7  - CAM_D3                    (alternate 13)
 * PC8  - CAM_D4                    (alternate 13)
 * PC9  - CAM_D5                    (alternate 13)
 * PC10 - SD_SCK                    (alternate 6)
 * PC11 - SD_MISO                   (alternate 6)
 * PC12 - SD_MOSI                   (alternate 6)
 * PC13 - LED2                      (output pushpull maximum)
 * PC14 - OSC32_IN                  (input floating)
 * PC15 - LED1                      (output pushpull maximum)
 */
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOC_ADC_VSOLAR) |     \
                                     PIN_MODE_INPUT(GPIOC_ADC_VBAT_DIFF) |  \
                                     PIN_MODE_ALTERNATE(GPIOC_CAM_D2) |     \
                                     PIN_MODE_ALTERNATE(GPIOC_CAM_D3) |     \
                                     PIN_MODE_ALTERNATE(GPIOC_CAM_D4) |     \
                                     PIN_MODE_ALTERNATE(GPIOC_CAM_D5) |     \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_SCK) |     \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_MOSI) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_MISO) |    \
                                     PIN_MODE_OUTPUT(GPIOC_LED2) |          \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_OUTPUT(GPIOC_LED1))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC_VSOLAR) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC_VBAT_DIFF)|\
                                     PIN_OTYPE_PUSHPULL(GPIOC_CAM_D2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_CAM_D3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_CAM_D4) |     \
                                     PIN_OTYPE_OPENDRAIN(GPIOC_CAM_D5) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_SCK) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_MOSI) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_MISO) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED1))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOC_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOC_ADC_VSOLAR) | \
                                     PIN_OSPEED_VERYLOW(GPIOC_ADC_VBAT_DIFF)|\
                                     PIN_OSPEED_HIGH(GPIOC_CAM_D2) |        \
                                     PIN_OSPEED_HIGH(GPIOC_CAM_D3) |        \
                                     PIN_OSPEED_HIGH(GPIOC_CAM_D4) |        \
                                     PIN_OSPEED_HIGH(GPIOC_CAM_D5) |        \
                                     PIN_OSPEED_HIGH(GPIOC_SD_SCK) |        \
                                     PIN_OSPEED_HIGH(GPIOC_SD_MOSI) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SD_MISO) |       \
                                     PIN_OSPEED_VERYLOW(GPIOC_LED2) |       \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_IN) |      \
                                     PIN_OSPEED_VERYLOW(GPIOC_LED1))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC_VSOLAR) | \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC_VBAT_DIFF)|\
                                     PIN_PUPDR_PULLUP(GPIOC_CAM_D2) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_CAM_D3) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_CAM_D4) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_CAM_D5) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_SD_SCK) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_SD_MOSI) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_SD_MISO) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_LED2) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_PULLUP(GPIOC_LED1))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOC_ADC_VSOLAR) |       \
                                     PIN_ODR_HIGH(GPIOC_ADC_VBAT_DIFF) |    \
                                     PIN_ODR_HIGH(GPIOC_CAM_D2) |           \
                                     PIN_ODR_HIGH(GPIOC_CAM_D3) |           \
                                     PIN_ODR_HIGH(GPIOC_CAM_D4) |           \
                                     PIN_ODR_HIGH(GPIOC_CAM_D5) |           \
                                     PIN_ODR_HIGH(GPIOC_SD_SCK) |           \
                                     PIN_ODR_HIGH(GPIOC_SD_MOSI) |          \
                                     PIN_ODR_HIGH(GPIOC_SD_MISO) |          \
                                     PIN_ODR_HIGH(GPIOC_LED2) |             \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_LED1))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOC_ADC_VSOLAR, 0) |     \
                                     PIN_AFIO_AF(GPIOC_ADC_VBAT_DIFF, 0) |  \
                                     PIN_AFIO_AF(GPIOC_CAM_D2, 13) |        \
                                     PIN_AFIO_AF(GPIOC_CAM_D3, 13))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_CAM_D4, 13) |        \
                                     PIN_AFIO_AF(GPIOC_CAM_D5, 13) |        \
                                     PIN_AFIO_AF(GPIOC_SD_SCK, 6) |         \
                                     PIN_AFIO_AF(GPIOC_SD_MOSI, 6) |        \
                                     PIN_AFIO_AF(GPIOC_SD_MISO, 6) |        \
                                     PIN_AFIO_AF(GPIOC_LED2, 0) |           \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0) |       \
                                     PIN_AFIO_AF(GPIOC_LED1, 0))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                      (input pullup)
 * PD1  - PIN1                      (input pullup)
 * PD2  - PIN2                      (input pullup)
 * PD3  - PIN3                      (input pullup)
 * PD4  - PIN4                      (input pullup)
 * PD5  - PIN5                      (input pullup)
 * PD6  - PIN6                      (input pullup)
 * PD7  - PIN7                      (input pullup)
 * PD8  - PIN8                      (input pullup)
 * PD9  - PIN9                      (input pullup)
 * PD10 - PIN10                     (input pullup)
 * PD11 - PIN11                     (input pullup)
 * PD12 - PIN12                     (input pullup)
 * PD13 - PIN13                     (input pullup)
 * PD14 - PIN14                     (input pullup)
 * PD15 - PIN15                     (input pullup)
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOD_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN14))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN14))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN14))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN7, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0))

/*
 * GPIOE setup:
 *
 * PE0  - CAM_OFF                   (output pushpull maximum)
 * PE1  - PIN1                      (input pullup)
 * PE2  - PIN2                      (input pullup)
 * PE3  - LED3                      (input pullup)
 * PE4  - CAM_D6                    (alternate 13)
 * PE5  - CAM_D8                    (alternate 13)
 * PE6  - CAM_D9                    (alternate 13)
 * PE7  - GPS_OFF                   (output pushpull maximum)
 * PE8  - PIN8                      (input pullup)
 * PE9  - PIN9                      (input pullup)
 * PE10 - GPS_TIMEPULSE             (input pullup)
 * PE11 - PIN11                     (input pullup)
 * PE12 - GPS_RESET                 (output pushpull maximum)
 * PE13 - RADIO2_GPIO0              (output pushpull maximum)
 * PE14 - RADIO2_GPIO1              (output pushpull maximum)
 * PE15 - MPU_INT                   (input pullup)
 */
#define VAL_GPIOE_MODER             (PIN_MODE_OUTPUT(GPIOE_CAM_OFF) |       \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOE_LED3) |           \
                                     PIN_MODE_ALTERNATE(GPIOE_CAM_D6) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_CAM_D8) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_CAM_D9) |     \
                                     PIN_MODE_OUTPUT(GPIOE_GPS_OFF) |       \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_GPS_TIMEPULSE) |  \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_OUTPUT(GPIOE_GPS_RESET) |     \
                                     PIN_MODE_OUTPUT(GPIOE_RADIO2_GPIO0) |  \
                                     PIN_MODE_OUTPUT(GPIOE_RADIO2_GPIO1) |  \
                                     PIN_MODE_INPUT(GPIOE_MPU_INT))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_CAM_OFF) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_LED3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_CAM_D6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_CAM_D8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_CAM_D9) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_GPS_OFF) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_GPS_TIMEPULSE)|\
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_GPS_RESET) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_RADIO2_GPIO0)|\
                                     PIN_OTYPE_PUSHPULL(GPIOE_RADIO2_GPIO1)|\
                                     PIN_OTYPE_PUSHPULL(GPIOE_MPU_INT))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOE_CAM_OFF) |    \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_LED3) |       \
                                     PIN_OSPEED_HIGH(GPIOE_CAM_D6) |    \
                                     PIN_OSPEED_HIGH(GPIOE_CAM_D8) |    \
                                     PIN_OSPEED_HIGH(GPIOE_CAM_D9) |    \
                                     PIN_OSPEED_VERYLOW(GPIOE_GPS_OFF) |    \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_GPS_TIMEPULSE)|\
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOE_GPS_RESET) |  \
                                     PIN_OSPEED_LOW(GPIOE_RADIO2_GPIO0) |   \
                                     PIN_OSPEED_LOW(GPIOE_RADIO2_GPIO1) |   \
                                     PIN_OSPEED_VERYLOW(GPIOE_MPU_INT))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLUP(GPIOE_CAM_OFF) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_LED3) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_CAM_D6) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_CAM_D8) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_CAM_D9) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_GPS_OFF) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_GPS_TIMEPULSE) |\
                                     PIN_PUPDR_PULLUP(GPIOE_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_GPS_RESET) |    \
                                     PIN_PUPDR_PULLUP(GPIOE_RADIO2_GPIO0) | \
                                     PIN_PUPDR_PULLUP(GPIOE_RADIO2_GPIO1) | \
                                     PIN_PUPDR_PULLUP(GPIOE_MPU_INT))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_CAM_OFF) |          \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOE_LED3) |             \
                                     PIN_ODR_HIGH(GPIOE_CAM_D6) |           \
                                     PIN_ODR_HIGH(GPIOE_CAM_D8) |           \
                                     PIN_ODR_HIGH(GPIOE_CAM_D9) |           \
                                     PIN_ODR_HIGH(GPIOE_GPS_OFF) |          \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_GPS_TIMEPULSE) |    \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_GPS_RESET) |        \
                                     PIN_ODR_HIGH(GPIOE_RADIO2_GPIO0) |     \
                                     PIN_ODR_HIGH(GPIOE_RADIO2_GPIO1) |     \
                                     PIN_ODR_HIGH(GPIOE_MPU_INT))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_CAM_OFF, 0) |        \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOE_LED3, 0) |           \
                                     PIN_AFIO_AF(GPIOE_CAM_D6, 13) |        \
                                     PIN_AFIO_AF(GPIOE_CAM_D8, 13) |        \
                                     PIN_AFIO_AF(GPIOE_CAM_D9, 13) |        \
                                     PIN_AFIO_AF(GPIOE_GPS_OFF, 0))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOE_GPS_TIMEPULSE, 0) |  \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOE_GPS_RESET, 0) |      \
                                     PIN_AFIO_AF(GPIOE_RADIO2_GPIO0, 0) |   \
                                     PIN_AFIO_AF(GPIOE_RADIO2_GPIO1, 0) |   \
                                     PIN_AFIO_AF(GPIOE_MPU_INT, 0))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                      (input pullup)
 * PF1  - PIN1                      (input pullup)
 * PF2  - PIN2                      (input pullup)
 * PF3  - PIN3                      (input pullup)
 * PF4  - PIN4                      (input pullup)
 * PF5  - PIN5                      (input pullup)
 * PF6  - PIN6                      (input pullup)
 * PF7  - PIN7                      (input pullup)
 * PF8  - PIN8                      (input pullup)
 * PF9  - PIN9                      (input pullup)
 * PF10 - PIN10                     (input pullup)
 * PF11 - PIN11                     (input pullup)
 * PF12 - PIN12                     (input pullup)
 * PF13 - PIN13                     (input pullup)
 * PF14 - PIN14                     (input pullup)
 * PF15 - PIN15                     (input pullup)
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOF_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN14))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_PULLUP(GPIOF_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN14))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN7, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0))

/*
 * GPIOG setup:
 *
 * PG0  - PIN0                      (input pullup)
 * PG1  - PIN1                      (input pullup)
 * PG2  - PIN2                      (input pullup)
 * PG3  - PIN3                      (input pullup)
 * PG4  - PIN4                      (input pullup)
 * PG5  - PIN5                      (input pullup)
 * PG6  - PIN6                      (input pullup)
 * PG7  - PIN7                      (input pullup)
 * PG8  - PIN8                      (input pullup)
 * PG9  - PIN9                      (input pullup)
 * PG10 - PIN10                     (input pullup)
 * PG11 - PIN11                     (input pullup)
 * PG12 - PIN12                     (input pullup)
 * PG13 - PIN13                     (input pullup)
 * PG14 - PIN14                     (input pullup)
 * PG15 - PIN15                     (input pullup)
 */
#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(GPIOG_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN14))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN14))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOG_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN14))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_PULLUP(GPIOG_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN14))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN14))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN7, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOG_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOG_PIN14, 0))

/*
 * GPIOH setup:
 *
 * PH0  - PIN0                      (input pullup)
 * PH1  - PIN1                      (input pullup)
 * PH2  - PIN2                      (input pullup)
 * PH3  - PIN3                      (input pullup)
 * PH4  - PIN4                      (input pullup)
 * PH5  - PIN5                      (input pullup)
 * PH6  - PIN6                      (input pullup)
 * PH7  - PIN7                      (input pullup)
 * PH8  - PIN8                      (input pullup)
 * PH9  - PIN9                      (input pullup)
 * PH10 - PIN10                     (input pullup)
 * PH11 - PIN11                     (input pullup)
 * PH12 - PIN12                     (input pullup)
 * PH13 - PIN13                     (input pullup)
 * PH14 - PIN14                     (input pullup)
 * PH15 - PIN15                     (input pullup)
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOH_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN14))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_PULLUP(GPIOH_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN14))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN7, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input pullup)
 * PI1  - PIN1                      (input pullup)
 * PI2  - PIN2                      (input pullup)
 * PI3  - PIN3                      (input pullup)
 * PI4  - PIN4                      (input pullup)
 * PI5  - PIN5                      (input pullup)
 * PI6  - PIN6                      (input pullup)
 * PI7  - PIN7                      (input pullup)
 * PI8  - PIN8                      (input pullup)
 * PI9  - PIN9                      (input pullup)
 * PI10 - PIN10                     (input pullup)
 * PI11 - PIN11                     (input pullup)
 * PI12 - PIN12                     (input pullup)
 * PI13 - PIN13                     (input pullup)
 * PI14 - PIN14                     (input pullup)
 * PI15 - PIN15                     (input pullup)
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOI_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN14))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLUP(GPIOI_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN14))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN7, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
