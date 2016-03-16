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
#define BOARD_PECANPICO7A
#define BOARD_NAME                  "Pecan Pico 7a"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                25999500U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   282U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F429xx



/*
 * Program code configuration
 */

// Serial debugging
#define DEBUG_UART_TX               (GPIOA, 0U)
#define DEBUG_UART_RX               (GPIOA, 1U)

// GPS
#define GPS_UART_TX                 (GPIOA, 2U)
#define GPS_UART_RX                 (GPIOA, 3U)
#define GPS_OFF                     (GPIOE, 7U)
#define GPS_TIMEPULSE               (GPIOE, 10U)
#define GPS_RESET                   (GPIOE, 12U)

// Main I2C
#define I2C_SCL                     (GPIOB, 10U)
#define I2C_SDA                     (GPIOB, 11U)

// Radio SPI
#define SPI_SCK                     (GPIOB, 13U)
#define SPI_MISO                    (GPIOB, 14U)
#define SPI_MOSI                    (GPIOB, 15U)

// Debug LEDs
#define LED_RED                     (GPIOC, 15U)
#define LED_YELLOW                  (GPIOC, 13U)
#define LED_GREEN                   (GPIOE, 3U)

// Camera pins
#define CAM_XCLK                    (GPIOA, 8U)
#define CAM_PCLK                    (GPIOA, 6U)
#define CAM_HREF                    (GPIOA, 4U)
#define CAM_VSYNC                   (GPIOB, 7U)
#define CAM_D2                      (GPIOC, 6U)
#define CAM_D3                      (GPIOC, 7U)
#define CAM_D4                      (GPIOC, 8U)
#define CAM_D5                      (GPIOC, 9U)
#define CAM_D6                      (GPIOE, 4U)
#define CAM_D7                      (GPIOB, 6U)
#define CAM_D8                      (GPIOE, 5U)
#define CAM_D9                      (GPIOE, 6U)
#define CAM_SCL                     (GPIOB, 8U)
#define CAM_SDA                     (GPIOB, 9U)
#define CAM_OFF                     (GPIOE, 0U)

// 2m radio pins
#define RADIO1_CS                   (GPIOA, 11U)
#define RADIO1_SDN                  (GPIOA, 12U)
#define RADIO1_GPIO0                (GPIOA, 10U)
#define RADIO1_GPIO1                (GPIOA, 9U)
#define RADIO1_PWR_REF              (GPIOA, 7U)
#define RADIO1_PWR_SENSE            (GPIOB, 1U)

// 70cm radio pins
#define RADIO2_CS                   (GPIOB, 0U)
#define RADIO2_SDN                  (GPIOB, 12U)
#define RADIO2_GPIO0                (GPIOE, 13U)
#define RADIO2_GPIO1                (GPIOE, 14U)

// SD card SPI
#define SD_CS                       (GPIOA, 15U)
#define SD_SCK                      (GPIOC, 10U)
#define SD_MISO                     (GPIOC, 11U)
#define SD_MOSI                     (GPIOC, 12U)

// ADC
#define ADC_VSOLAR                  (GPIOC, 4U)
#define ADC_VBAT_DIFF               (GPIOC, 5U)

// MPU9250 Interrupt
#define MPU_INT                     (GPIOE, 15U)


// Hardware definitions (which cant be changed easily)
#define OSC_FREQ				STM32_HSECLK	/* Oscillator frequency */
#define CAM_AVAIL				TRUE			/* Camera available */
#define GPS_AVAIL				TRUE			/* uBlox MAX7/8 GNSS receiver available */
#define SD_AVAIL				FALSE			/* microSD card available */
#define RADIO1_AVAIL			TRUE			/* Radio 1 available */
#define RADIO2_AVAIL			TRUE			/* Radio 2 available */
#define BME280_AVAIL			TRUE			/* BME280 air pressure sensor available */
#define MPU9250_AVAIL			FALSE			/* MPU9250 9 axis sensor available */
#define PAC1720_AVAIL			TRUE			/* PAC1720 current sensor available */

#define RADIO1_MIN_FREQ			1				/* Min. Frequency range of Radio 1 */
#define RADIO1_MAX_FREQ			2				/* Min. Frequency range of Radio 1 */
#define RADIO1_MAX_PWR			13				/* Max. power of Radio 1 in dBm */
#define RADIO2_MIN_FREQ			144000000		/* Min. Frequency range of Radio 2 */
#define RADIO2_MAX_FREQ			450000000		/* Min. Frequency range of Radio 2 */
#define RADIO2_MAX_PWR			13				/* Max. power of Radio 2 in dBm */



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
#define GPIOC_LED_YELLOW            13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_LED_RED               15U

#define GPIOE_CAM_OFF               0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_LED_GREEN             3U
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
#define LINE_LED_YELLOW             PAL_LINE(GPIOC, 13U)
#define LINE_OSC32_IN               PAL_LINE(GPIOC, 14U)
#define LINE_LED_RED                PAL_LINE(GPIOC, 15U)

#define LINE_CAM_OFF                PAL_LINE(GPIOE, 0U)
#define LINE_PIN1                   PAL_LINE(GPIOE, 1U)
#define LINE_PIN2                   PAL_LINE(GPIOE, 2U)
#define LINE_LED_GREEN              PAL_LINE(GPIOE, 3U)
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
 * PC13 - LED_YELLOW                (output pushpull maximum)
 * PC14 - OSC32_IN                  (input floating)
 * PC15 - LED_RED                   (output pushpull maximum)
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
                                     PIN_MODE_OUTPUT(GPIOC_LED_YELLOW) |    \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_OUTPUT(GPIOC_LED_RED))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC_VSOLAR) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC_VBAT_DIFF)|\
                                     PIN_OTYPE_PUSHPULL(GPIOC_CAM_D2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_CAM_D3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_CAM_D4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_CAM_D5) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_SCK) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_MOSI) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_MISO) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED_YELLOW) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED_RED))
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
                                     PIN_OSPEED_VERYLOW(GPIOC_LED_YELLOW) | \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_IN) |      \
                                     PIN_OSPEED_VERYLOW(GPIOC_LED_RED))
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
                                     PIN_PUPDR_PULLUP(GPIOC_LED_YELLOW) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_PULLUP(GPIOC_LED_RED))
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
                                     PIN_ODR_HIGH(GPIOC_LED_YELLOW) |       \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_LED_RED))
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
                                     PIN_AFIO_AF(GPIOC_LED_YELLOW, 0) |     \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0) |       \
                                     PIN_AFIO_AF(GPIOC_LED_RED, 0))

/*
 * GPIOE setup:
 *
 * PE0  - CAM_OFF                   (output pushpull maximum)
 * PE1  - PIN1                      (input pullup)
 * PE2  - PIN2                      (input pullup)
 * PE3  - LED_GREEN                 (input pullup)
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
                                     PIN_MODE_INPUT(GPIOE_LED_GREEN) |      \
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
                                     PIN_OTYPE_PUSHPULL(GPIOE_LED_GREEN) |  \
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
                                     PIN_OSPEED_VERYLOW(GPIOE_LED_GREEN) |  \
                                     PIN_OSPEED_HIGH(GPIOE_CAM_D6) |        \
                                     PIN_OSPEED_HIGH(GPIOE_CAM_D8) |        \
                                     PIN_OSPEED_HIGH(GPIOE_CAM_D9) |        \
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
                                     PIN_PUPDR_PULLUP(GPIOE_LED_GREEN) |    \
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
                                     PIN_ODR_HIGH(GPIOE_LED_GREEN) |        \
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
                                     PIN_AFIO_AF(GPIOE_LED_GREEN, 0) |      \
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
