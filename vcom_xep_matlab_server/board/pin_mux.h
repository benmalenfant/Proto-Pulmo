/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/* GPIO_B1_15 (coord B14), FACRESET_BUTTON */
#define BOARD_INITPINS_FACRESET_BUTTON_GPIO                                GPIO7   /*!< GPIO device name: GPIO7 */
#define BOARD_INITPINS_FACRESET_BUTTON_PORT                                GPIO7   /*!< PORT device name: GPIO7 */
#define BOARD_INITPINS_FACRESET_BUTTON_PIN                                   31U   /*!< GPIO7 pin index: 31 */

/* GPIO_AD_B0_00 (coord M14), SLEEPAIR_BUTTON */
#define BOARD_INITPINS_SLEEPAIR_BUTTON_GPIO                                GPIO6   /*!< GPIO device name: GPIO6 */
#define BOARD_INITPINS_SLEEPAIR_BUTTON_PORT                                GPIO6   /*!< PORT device name: GPIO6 */
#define BOARD_INITPINS_SLEEPAIR_BUTTON_PIN                                    0U   /*!< GPIO6 pin index: 0 */

/* GPIO_B1_13 (coord D14), WDOG */
#define BOARD_INITPINS_WDOG_GPIO                                           GPIO2   /*!< GPIO device name: GPIO2 */
#define BOARD_INITPINS_WDOG_PORT                                           GPIO2   /*!< PORT device name: GPIO2 */
#define BOARD_INITPINS_WDOG_PIN                                              29U   /*!< GPIO2 pin index: 29 */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/* GPIO_EMC_10 (coord G1), ADDR01 */
#define BOARD_INIT_SDRAM_ADDR01_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR01_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR01_CHANNEL                                       1U   /*!< SEMC ADDR channel: 01 */

/* GPIO_EMC_11 (coord G3), ADDR02 */
#define BOARD_INIT_SDRAM_ADDR02_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR02_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR02_CHANNEL                                       2U   /*!< SEMC ADDR channel: 02 */

/* GPIO_EMC_12 (coord H1), ADDR03 */
#define BOARD_INIT_SDRAM_ADDR03_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR03_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR03_CHANNEL                                       3U   /*!< SEMC ADDR channel: 03 */

/* GPIO_EMC_13 (coord A6), ADDR04 */
#define BOARD_INIT_SDRAM_ADDR04_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR04_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR04_CHANNEL                                       4U   /*!< SEMC ADDR channel: 04 */

/* GPIO_EMC_14 (coord B6), ADDR05 */
#define BOARD_INIT_SDRAM_ADDR05_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR05_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR05_CHANNEL                                       5U   /*!< SEMC ADDR channel: 05 */

/* GPIO_EMC_15 (coord B1), ADDR06 */
#define BOARD_INIT_SDRAM_ADDR06_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR06_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR06_CHANNEL                                       6U   /*!< SEMC ADDR channel: 06 */

/* GPIO_EMC_16 (coord A5), ADDR07 */
#define BOARD_INIT_SDRAM_ADDR07_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR07_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR07_CHANNEL                                       7U   /*!< SEMC ADDR channel: 07 */

/* GPIO_EMC_17 (coord A4), ADDR08 */
#define BOARD_INIT_SDRAM_ADDR08_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR08_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR08_CHANNEL                                       8U   /*!< SEMC ADDR channel: 08 */

/* GPIO_EMC_18 (coord B2), ADDR09 */
#define BOARD_INIT_SDRAM_ADDR09_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR09_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR09_CHANNEL                                       9U   /*!< SEMC ADDR channel: 09 */

/* GPIO_EMC_23 (coord G2), ADDR10 */
#define BOARD_INIT_SDRAM_ADDR10_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR10_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR10_CHANNEL                                      10U   /*!< SEMC ADDR channel: 10 */

/* GPIO_EMC_19 (coord B4), ADDR11 */
#define BOARD_INIT_SDRAM_ADDR11_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR11_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR11_CHANNEL                                      11U   /*!< SEMC ADDR channel: 11 */

/* GPIO_EMC_21 (coord C1), BA0 */
#define BOARD_INIT_SDRAM_BA0_PERIPHERAL                                     SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_BA0_SIGNAL                                           BA   /*!< SEMC signal: BA */
#define BOARD_INIT_SDRAM_BA0_CHANNEL                                          0U   /*!< SEMC BA channel: 0 */

/* GPIO_EMC_22 (coord F1), BA1 */
#define BOARD_INIT_SDRAM_BA1_PERIPHERAL                                     SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_BA1_SIGNAL                                           BA   /*!< SEMC signal: BA */
#define BOARD_INIT_SDRAM_BA1_CHANNEL                                          1U   /*!< SEMC BA channel: 1 */

/* GPIO_EMC_24 (coord D3), CAS */
#define BOARD_INIT_SDRAM_CAS_PERIPHERAL                                     SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_CAS_SIGNAL                                     semc_cas   /*!< SEMC signal: semc_cas */

/* GPIO_EMC_27 (coord A2), CKE */
#define BOARD_INIT_SDRAM_CKE_PERIPHERAL                                     SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_CKE_SIGNAL                                     semc_cke   /*!< SEMC signal: semc_cke */

/* GPIO_EMC_26 (coord B3), CLK */
#define BOARD_INIT_SDRAM_CLK_PERIPHERAL                                     SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_CLK_SIGNAL                                     semc_clk   /*!< SEMC signal: semc_clk */

/* GPIO_EMC_25 (coord D2), RAS */
#define BOARD_INIT_SDRAM_RAS_PERIPHERAL                                     SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_RAS_SIGNAL                                     semc_ras   /*!< SEMC signal: semc_ras */

/* GPIO_EMC_28 (coord D1), WE */
#define BOARD_INIT_SDRAM_WE_PERIPHERAL                                      SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_WE_SIGNAL                                       semc_we   /*!< SEMC signal: semc_we */

/* GPIO_EMC_29 (coord E1), CS */
#define BOARD_INIT_SDRAM_CS_PERIPHERAL                                      SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_CS_SIGNAL                                            CS   /*!< SEMC signal: CS */
#define BOARD_INIT_SDRAM_CS_CHANNEL                                           0U   /*!< SEMC CS channel: 0 */

/* GPIO_EMC_37 (coord E4), DATA15 */
#define BOARD_INIT_SDRAM_DATA15_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA15_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA15_CHANNEL                                      15U   /*!< SEMC DATA channel: 15 */

/* GPIO_EMC_36 (coord C3), DATA14 */
#define BOARD_INIT_SDRAM_DATA14_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA14_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA14_CHANNEL                                      14U   /*!< SEMC DATA channel: 14 */

/* GPIO_EMC_35 (coord E5), DATA13 */
#define BOARD_INIT_SDRAM_DATA13_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA13_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA13_CHANNEL                                      13U   /*!< SEMC DATA channel: 13 */

/* GPIO_EMC_34 (coord D4), DATA12 */
#define BOARD_INIT_SDRAM_DATA12_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA12_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA12_CHANNEL                                      12U   /*!< SEMC DATA channel: 12 */

/* GPIO_EMC_00 (coord E3), DATA00 */
#define BOARD_INIT_SDRAM_DATA00_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA00_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA00_CHANNEL                                       0U   /*!< SEMC DATA channel: 00 */

/* GPIO_EMC_01 (coord F3), DATA01 */
#define BOARD_INIT_SDRAM_DATA01_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA01_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA01_CHANNEL                                       1U   /*!< SEMC DATA channel: 01 */

/* GPIO_EMC_03 (coord G4), DATA03 */
#define BOARD_INIT_SDRAM_DATA03_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA03_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA03_CHANNEL                                       3U   /*!< SEMC DATA channel: 03 */

/* GPIO_EMC_02 (coord F4), DATA02 */
#define BOARD_INIT_SDRAM_DATA02_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA02_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA02_CHANNEL                                       2U   /*!< SEMC DATA channel: 02 */

/* GPIO_EMC_04 (coord F2), DATA04 */
#define BOARD_INIT_SDRAM_DATA04_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA04_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA04_CHANNEL                                       4U   /*!< SEMC DATA channel: 04 */

/* GPIO_EMC_05 (coord G5), DATA05 */
#define BOARD_INIT_SDRAM_DATA05_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA05_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA05_CHANNEL                                       5U   /*!< SEMC DATA channel: 05 */

/* GPIO_EMC_06 (coord H5), DATA06 */
#define BOARD_INIT_SDRAM_DATA06_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA06_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA06_CHANNEL                                       6U   /*!< SEMC DATA channel: 06 */

/* GPIO_EMC_07 (coord H4), DATA07 */
#define BOARD_INIT_SDRAM_DATA07_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA07_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA07_CHANNEL                                       7U   /*!< SEMC DATA channel: 07 */

/* GPIO_EMC_30 (coord C6), DATA08 */
#define BOARD_INIT_SDRAM_DATA08_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA08_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA08_CHANNEL                                       8U   /*!< SEMC DATA channel: 08 */

/* GPIO_EMC_31 (coord C5), DATA09 */
#define BOARD_INIT_SDRAM_DATA09_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA09_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA09_CHANNEL                                       9U   /*!< SEMC DATA channel: 09 */

/* GPIO_EMC_32 (coord D5), DATA10 */
#define BOARD_INIT_SDRAM_DATA10_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA10_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA10_CHANNEL                                      10U   /*!< SEMC DATA channel: 10 */

/* GPIO_EMC_33 (coord C4), DATA11 */
#define BOARD_INIT_SDRAM_DATA11_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DATA11_SIGNAL                                      DATA   /*!< SEMC signal: DATA */
#define BOARD_INIT_SDRAM_DATA11_CHANNEL                                      11U   /*!< SEMC DATA channel: 11 */

/* GPIO_EMC_08 (coord H3), DM0 */
#define BOARD_INIT_SDRAM_DM0_PERIPHERAL                                     SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DM0_SIGNAL                                           DM   /*!< SEMC signal: DM */
#define BOARD_INIT_SDRAM_DM0_CHANNEL                                          0U   /*!< SEMC DM channel: 0 */

/* GPIO_EMC_38 (coord D6), DM1 */
#define BOARD_INIT_SDRAM_DM1_PERIPHERAL                                     SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DM1_SIGNAL                                           DM   /*!< SEMC signal: DM */
#define BOARD_INIT_SDRAM_DM1_CHANNEL                                          1U   /*!< SEMC DM channel: 1 */

/* GPIO_EMC_09 (coord C2), ADDR00 */
#define BOARD_INIT_SDRAM_ADDR00_PERIPHERAL                                  SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_ADDR00_SIGNAL                                      ADDR   /*!< SEMC signal: ADDR */
#define BOARD_INIT_SDRAM_ADDR00_CHANNEL                                       0U   /*!< SEMC ADDR channel: 00 */

/* GPIO_EMC_39 (coord B7), DQS */
#define BOARD_INIT_SDRAM_DQS_PERIPHERAL                                     SEMC   /*!< Device name: SEMC */
#define BOARD_INIT_SDRAM_DQS_SIGNAL                                     semc_dqs   /*!< SEMC signal: semc_dqs */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_SDRAM(void);

/* GPIO_SD_B1_08 (coord P3), IO0 */
#define BOARD_INIT_FLASH_IO0_PERIPHERAL                                  FLEXSPI   /*!< Device name: FLEXSPI */
#define BOARD_INIT_FLASH_IO0_SIGNAL                              FLEXSPI_A_DATA0   /*!< FLEXSPI signal: FLEXSPI_A_DATA0 */

/* GPIO_SD_B1_09 (coord N4), IO1 */
#define BOARD_INIT_FLASH_IO1_PERIPHERAL                                  FLEXSPI   /*!< Device name: FLEXSPI */
#define BOARD_INIT_FLASH_IO1_SIGNAL                              FLEXSPI_A_DATA1   /*!< FLEXSPI signal: FLEXSPI_A_DATA1 */

/* GPIO_SD_B1_10 (coord P4), IO2 */
#define BOARD_INIT_FLASH_IO2_PERIPHERAL                                  FLEXSPI   /*!< Device name: FLEXSPI */
#define BOARD_INIT_FLASH_IO2_SIGNAL                              FLEXSPI_A_DATA2   /*!< FLEXSPI signal: FLEXSPI_A_DATA2 */

/* GPIO_SD_B1_11 (coord P5), IO3 */
#define BOARD_INIT_FLASH_IO3_PERIPHERAL                                  FLEXSPI   /*!< Device name: FLEXSPI */
#define BOARD_INIT_FLASH_IO3_SIGNAL                              FLEXSPI_A_DATA3   /*!< FLEXSPI signal: FLEXSPI_A_DATA3 */

/* GPIO_SD_B1_05 (coord N3), DQS */
#define BOARD_INIT_FLASH_DQS_PERIPHERAL                                  FLEXSPI   /*!< Device name: FLEXSPI */
#define BOARD_INIT_FLASH_DQS_SIGNAL                                FLEXSPI_A_DQS   /*!< FLEXSPI signal: FLEXSPI_A_DQS */

/* GPIO_SD_B1_07 (coord L4), CLK */
#define BOARD_INIT_FLASH_CLK_PERIPHERAL                                  FLEXSPI   /*!< Device name: FLEXSPI */
#define BOARD_INIT_FLASH_CLK_SIGNAL                               FLEXSPI_A_SCLK   /*!< FLEXSPI signal: FLEXSPI_A_SCLK */

/* GPIO_SD_B1_06 (coord L3), CS */
#define BOARD_INIT_FLASH_CS_PERIPHERAL                                   FLEXSPI   /*!< Device name: FLEXSPI */
#define BOARD_INIT_FLASH_CS_SIGNAL                               FLEXSPI_A_SS0_B   /*!< FLEXSPI signal: FLEXSPI_A_SS0_B */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_Flash(void);

/* GPIO_SD_B0_04 (coord H2), DAT2 */
#define BOARD_INIT_SD_DAT2_PERIPHERAL                                     USDHC1   /*!< Device name: USDHC1 */
#define BOARD_INIT_SD_DAT2_SIGNAL                                     usdhc_data   /*!< USDHC1 signal: usdhc_data */
#define BOARD_INIT_SD_DAT2_CHANNEL                                            2U   /*!< USDHC1 usdhc_data channel: 2 */

/* GPIO_SD_B0_05 (coord J2), DAT3 */
#define BOARD_INIT_SD_DAT3_PERIPHERAL                                     USDHC1   /*!< Device name: USDHC1 */
#define BOARD_INIT_SD_DAT3_SIGNAL                                     usdhc_data   /*!< USDHC1 signal: usdhc_data */
#define BOARD_INIT_SD_DAT3_CHANNEL                                            3U   /*!< USDHC1 usdhc_data channel: 3 */

/* GPIO_SD_B0_03 (coord K1), DAT1 */
#define BOARD_INIT_SD_DAT1_PERIPHERAL                                     USDHC1   /*!< Device name: USDHC1 */
#define BOARD_INIT_SD_DAT1_SIGNAL                                     usdhc_data   /*!< USDHC1 signal: usdhc_data */
#define BOARD_INIT_SD_DAT1_CHANNEL                                            1U   /*!< USDHC1 usdhc_data channel: 1 */

/* GPIO_SD_B0_02 (coord J1), DAT0 */
#define BOARD_INIT_SD_DAT0_PERIPHERAL                                     USDHC1   /*!< Device name: USDHC1 */
#define BOARD_INIT_SD_DAT0_SIGNAL                                     usdhc_data   /*!< USDHC1 signal: usdhc_data */
#define BOARD_INIT_SD_DAT0_CHANNEL                                            0U   /*!< USDHC1 usdhc_data channel: 0 */

/* GPIO_SD_B0_01 (coord J3), CLK */
#define BOARD_INIT_SD_CLK_PERIPHERAL                                      USDHC1   /*!< Device name: USDHC1 */
#define BOARD_INIT_SD_CLK_SIGNAL                                       usdhc_clk   /*!< USDHC1 signal: usdhc_clk */

/* GPIO_SD_B0_00 (coord J4), CMD */
#define BOARD_INIT_SD_CMD_PERIPHERAL                                      USDHC1   /*!< Device name: USDHC1 */
#define BOARD_INIT_SD_CMD_SIGNAL                                       usdhc_cmd   /*!< USDHC1 signal: usdhc_cmd */

/* GPIO_B1_12 (coord D13), CD */
#define BOARD_INIT_SD_CD_GPIO                                              GPIO2   /*!< GPIO device name: GPIO2 */
#define BOARD_INIT_SD_CD_PORT                                              GPIO2   /*!< PORT device name: GPIO2 */
#define BOARD_INIT_SD_CD_PIN                                                 28U   /*!< GPIO2 pin index: 28 */

/* GPIO_AD_B1_10 (coord L13), SD_PWR_EN */
#define BOARD_INIT_SD_SD_PWR_EN_GPIO                                       GPIO1   /*!< GPIO device name: GPIO1 */
#define BOARD_INIT_SD_SD_PWR_EN_PORT                                       GPIO1   /*!< PORT device name: GPIO1 */
#define BOARD_INIT_SD_SD_PWR_EN_PIN                                          26U   /*!< GPIO1 pin index: 26 */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_SD(void);

/* GPIO_AD_B0_14 (coord H14), BT_UART_CTS */
#define BOARD_INIT_WICED_BT_UART_CTS_PERIPHERAL                          LPUART1   /*!< Device name: LPUART1 */
#define BOARD_INIT_WICED_BT_UART_CTS_SIGNAL                                CTS_B   /*!< LPUART1 signal: CTS_B */

/* GPIO_AD_B0_15 (coord L10), BT_UART_RTS */
#define BOARD_INIT_WICED_BT_UART_RTS_PERIPHERAL                          LPUART1   /*!< Device name: LPUART1 */
#define BOARD_INIT_WICED_BT_UART_RTS_SIGNAL                                RTS_B   /*!< LPUART1 signal: RTS_B */

/* GPIO_AD_B0_13 (coord L14), BT_UART_TXD */
#define BOARD_INIT_WICED_BT_UART_TXD_PERIPHERAL                          LPUART1   /*!< Device name: LPUART1 */
#define BOARD_INIT_WICED_BT_UART_TXD_SIGNAL                                   RX   /*!< LPUART1 signal: RX */

/* GPIO_AD_B0_12 (coord K14), BT_UART_RXD */
#define BOARD_INIT_WICED_BT_UART_RXD_PERIPHERAL                          LPUART1   /*!< Device name: LPUART1 */
#define BOARD_INIT_WICED_BT_UART_RXD_SIGNAL                                   TX   /*!< LPUART1 signal: TX */

/* GPIO_B1_09 (coord A13), WL_REG_ON */
#define BOARD_INIT_WICED_WL_REG_ON_GPIO                                    GPIO2   /*!< GPIO device name: GPIO2 */
#define BOARD_INIT_WICED_WL_REG_ON_PORT                                    GPIO2   /*!< PORT device name: GPIO2 */
#define BOARD_INIT_WICED_WL_REG_ON_PIN                                       25U   /*!< GPIO2 pin index: 25 */

/* GPIO_B1_10 (coord B13), BT_REG_ON */
#define BOARD_INIT_WICED_BT_REG_ON_GPIO                                    GPIO2   /*!< GPIO device name: GPIO2 */
#define BOARD_INIT_WICED_BT_REG_ON_PORT                                    GPIO2   /*!< PORT device name: GPIO2 */
#define BOARD_INIT_WICED_BT_REG_ON_PIN                                       26U   /*!< GPIO2 pin index: 26 */

/* GPIO_B1_07 (coord B12), BT_HOSTWAKE */
#define BOARD_INIT_WICED_BT_HOSTWAKE_GPIO                                  GPIO2   /*!< GPIO device name: GPIO2 */
#define BOARD_INIT_WICED_BT_HOSTWAKE_PORT                                  GPIO2   /*!< PORT device name: GPIO2 */
#define BOARD_INIT_WICED_BT_HOSTWAKE_PIN                                     23U   /*!< GPIO2 pin index: 23 */

/* GPIO_B1_11 (coord C13), WIFI_GPIO2 */
#define BOARD_INIT_WICED_WIFI_GPIO2_GPIO                                   GPIO2   /*!< GPIO device name: GPIO2 */
#define BOARD_INIT_WICED_WIFI_GPIO2_PORT                                   GPIO2   /*!< PORT device name: GPIO2 */
#define BOARD_INIT_WICED_WIFI_GPIO2_PIN                                      27U   /*!< GPIO2 pin index: 27 */

/* GPIO_B1_14 (coord C14), WIFI_GPIO3 */
#define BOARD_INIT_WICED_WIFI_GPIO3_GPIO                                   GPIO2   /*!< GPIO device name: GPIO2 */
#define BOARD_INIT_WICED_WIFI_GPIO3_PORT                                   GPIO2   /*!< PORT device name: GPIO2 */
#define BOARD_INIT_WICED_WIFI_GPIO3_PIN                                      30U   /*!< GPIO2 pin index: 30 */

/* GPIO_AD_B1_15 (coord J14), BT_WAKE */
#define BOARD_INIT_WICED_BT_WAKE_GPIO                                      GPIO1   /*!< GPIO device name: GPIO1 */
#define BOARD_INIT_WICED_BT_WAKE_PORT                                      GPIO1   /*!< PORT device name: GPIO1 */
#define BOARD_INIT_WICED_BT_WAKE_PIN                                         31U   /*!< GPIO1 pin index: 31 */

/* GPIO_AD_B1_09 (coord M13), WIFI_SDIO_CLK */
#define BOARD_INIT_WICED_WIFI_SDIO_CLK_PERIPHERAL                         USDHC2   /*!< Device name: USDHC2 */
#define BOARD_INIT_WICED_WIFI_SDIO_CLK_SIGNAL                          usdhc_clk   /*!< USDHC2 signal: usdhc_clk */

/* GPIO_AD_B1_08 (coord H13), WIFI_SDIO_CMD */
#define BOARD_INIT_WICED_WIFI_SDIO_CMD_PERIPHERAL                         USDHC2   /*!< Device name: USDHC2 */
#define BOARD_INIT_WICED_WIFI_SDIO_CMD_SIGNAL                          usdhc_cmd   /*!< USDHC2 signal: usdhc_cmd */

/* GPIO_AD_B1_04 (coord L12), WIDI_SDIO_D0 */
#define BOARD_INIT_WICED_WIDI_SDIO_D0_PERIPHERAL                          USDHC2   /*!< Device name: USDHC2 */
#define BOARD_INIT_WICED_WIDI_SDIO_D0_SIGNAL                          usdhc_data   /*!< USDHC2 signal: usdhc_data */
#define BOARD_INIT_WICED_WIDI_SDIO_D0_CHANNEL                                 0U   /*!< USDHC2 usdhc_data channel: 0 */

/* GPIO_AD_B1_05 (coord K12), WIDI_SDIO_D1 */
#define BOARD_INIT_WICED_WIDI_SDIO_D1_PERIPHERAL                          USDHC2   /*!< Device name: USDHC2 */
#define BOARD_INIT_WICED_WIDI_SDIO_D1_SIGNAL                          usdhc_data   /*!< USDHC2 signal: usdhc_data */
#define BOARD_INIT_WICED_WIDI_SDIO_D1_CHANNEL                                 1U   /*!< USDHC2 usdhc_data channel: 1 */

/* GPIO_AD_B1_06 (coord J12), WIDI_SDIO_D2 */
#define BOARD_INIT_WICED_WIDI_SDIO_D2_PERIPHERAL                          USDHC2   /*!< Device name: USDHC2 */
#define BOARD_INIT_WICED_WIDI_SDIO_D2_SIGNAL                          usdhc_data   /*!< USDHC2 signal: usdhc_data */
#define BOARD_INIT_WICED_WIDI_SDIO_D2_CHANNEL                                 2U   /*!< USDHC2 usdhc_data channel: 2 */

/* GPIO_AD_B1_07 (coord K10), WIDI_SDIO_D3 */
#define BOARD_INIT_WICED_WIDI_SDIO_D3_PERIPHERAL                          USDHC2   /*!< Device name: USDHC2 */
#define BOARD_INIT_WICED_WIDI_SDIO_D3_SIGNAL                          usdhc_data   /*!< USDHC2 signal: usdhc_data */
#define BOARD_INIT_WICED_WIDI_SDIO_D3_CHANNEL                                 3U   /*!< USDHC2 usdhc_data channel: 3 */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_Wiced(void);

/* USB_OTG1_DN (coord M8), DM */
#define BOARD_INIT_USB_DM_PERIPHERAL                                        USB1   /*!< Device name: USB1 */
#define BOARD_INIT_USB_DM_SIGNAL                                     usb_otg1_dn   /*!< USB1 signal: usb_otg1_dn */

/* USB_OTG1_DP (coord L8), DP */
#define BOARD_INIT_USB_DP_PERIPHERAL                                        USB1   /*!< Device name: USB1 */
#define BOARD_INIT_USB_DP_SIGNAL                                     usb_otg1_dp   /*!< USB1 signal: usb_otg1_dp */

/* GPIO_AD_B0_01 (coord H10), ID */
#define BOARD_INIT_USB_ID_PERIPHERAL                                        USB1   /*!< Device name: USB1 */
#define BOARD_INIT_USB_ID_SIGNAL                                     usb_otg1_id   /*!< USB1 signal: usb_otg1_id */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_USB(void);

/* GPIO_AD_B0_02 (coord M11), RED */
#define BOARD_INIT_LED_RED_GPIO                                            GPIO6   /*!< GPIO device name: GPIO6 */
#define BOARD_INIT_LED_RED_PORT                                            GPIO6   /*!< PORT device name: GPIO6 */
#define BOARD_INIT_LED_RED_PIN                                                2U   /*!< GPIO6 pin index: 2 */

/* GPIO_AD_B0_03 (coord G11), GREEN */
#define BOARD_INIT_LED_GREEN_GPIO                                          GPIO6   /*!< GPIO device name: GPIO6 */
#define BOARD_INIT_LED_GREEN_PORT                                          GPIO6   /*!< PORT device name: GPIO6 */
#define BOARD_INIT_LED_GREEN_PIN                                              3U   /*!< GPIO6 pin index: 3 */

/* GPIO_B0_11 (coord A10), PWMG */
#define BOARD_INIT_LED_PWMG_PERIPHERAL                                      PWM2   /*!< Device name: PWM2 */
#define BOARD_INIT_LED_PWMG_SIGNAL                                             B   /*!< PWM2 signal: B */
#define BOARD_INIT_LED_PWMG_CHANNEL                                           2U   /*!< PWM2 B channel: 2 */

/* GPIO_B0_09 (coord C9), PWMB */
#define BOARD_INIT_LED_PWMB_PERIPHERAL                                      PWM2   /*!< Device name: PWM2 */
#define BOARD_INIT_LED_PWMB_SIGNAL                                             B   /*!< PWM2 signal: B */
#define BOARD_INIT_LED_PWMB_CHANNEL                                           1U   /*!< PWM2 B channel: 1 */

/* GPIO_B0_07 (coord A9), PWMR */
#define BOARD_INIT_LED_PWMR_PERIPHERAL                                      PWM2   /*!< Device name: PWM2 */
#define BOARD_INIT_LED_PWMR_SIGNAL                                             B   /*!< PWM2 signal: B */
#define BOARD_INIT_LED_PWMR_CHANNEL                                           0U   /*!< PWM2 B channel: 0 */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_LED(void);

/* GPIO_AD_B0_11 (coord G10), TRST */
#define BOARD_INIT_JTAG_TRST_PERIPHERAL                                     JTAG   /*!< Device name: JTAG */
#define BOARD_INIT_JTAG_TRST_SIGNAL                                        TRSTB   /*!< JTAG signal: TRSTB */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_JTAG(void);

/* GPIO_B0_01 (coord E7), SPI_MISO */
#define BOARD_INIT_X4_SPI_MISO_PERIPHERAL                                 LPSPI4   /*!< Device name: LPSPI4 */
#define BOARD_INIT_X4_SPI_MISO_SIGNAL                                        SDI   /*!< LPSPI4 signal: SDI */

/* GPIO_B0_03 (coord D8), SPI_SCLK */
#define BOARD_INIT_X4_SPI_SCLK_PERIPHERAL                                 LPSPI4   /*!< Device name: LPSPI4 */
#define BOARD_INIT_X4_SPI_SCLK_SIGNAL                                        SCK   /*!< LPSPI4 signal: SCK */

/* GPIO_B0_00 (coord D7), SPI_CS */
#define BOARD_INIT_X4_SPI_CS_PERIPHERAL                                   LPSPI4   /*!< Device name: LPSPI4 */
#define BOARD_INIT_X4_SPI_CS_SIGNAL                                         PCS0   /*!< LPSPI4 signal: PCS0 */

/* GPIO_B0_02 (coord E8), SPI_MOSI */
#define BOARD_INIT_X4_SPI_MOSI_PERIPHERAL                                 LPSPI4   /*!< Device name: LPSPI4 */
#define BOARD_INIT_X4_SPI_MOSI_SIGNAL                                        SDO   /*!< LPSPI4 signal: SDO */

/* GPIO_B0_06 (coord A8), EN */
#define BOARD_INIT_X4_EN_GPIO                                              GPIO7   /*!< GPIO device name: GPIO7 */
#define BOARD_INIT_X4_EN_PORT                                              GPIO7   /*!< PORT device name: GPIO7 */
#define BOARD_INIT_X4_EN_PIN                                                  6U   /*!< GPIO7 pin index: 6 */

/* GPIO_B0_04 (coord C8), GPIO1 */
#define BOARD_INIT_X4_GPIO1_GPIO                                           GPIO2   /*!< GPIO device name: GPIO2 */
#define BOARD_INIT_X4_GPIO1_PORT                                           GPIO2   /*!< PORT device name: GPIO2 */
#define BOARD_INIT_X4_GPIO1_PIN                                               4U   /*!< GPIO2 pin index: 4 */

/* GPIO_B0_05 (coord B8), GPIO2 */
#define BOARD_INIT_X4_GPIO2_GPIO                                           GPIO2   /*!< GPIO device name: GPIO2 */
#define BOARD_INIT_X4_GPIO2_PORT                                           GPIO2   /*!< PORT device name: GPIO2 */
#define BOARD_INIT_X4_GPIO2_PIN                                               5U   /*!< GPIO2 pin index: 5 */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_X4(void);

/* GPIO_AD_B1_00 (coord J11), SCL */
#define BOARD_INIT_I2C_SCL_PERIPHERAL                                     LPI2C1   /*!< Device name: LPI2C1 */
#define BOARD_INIT_I2C_SCL_SIGNAL                                            SCL   /*!< LPI2C1 signal: SCL */

/* GPIO_AD_B1_01 (coord K11), SDA */
#define BOARD_INIT_I2C_SDA_PERIPHERAL                                     LPI2C1   /*!< Device name: LPI2C1 */
#define BOARD_INIT_I2C_SDA_SIGNAL                                            SDA   /*!< LPI2C1 signal: SDA */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_I2C(void);

/* GPIO_AD_B1_02 (coord L11), UART2_TX */
#define BOARD_INIT_UART_UART2_TX_PERIPHERAL                              LPUART2   /*!< Device name: LPUART2 */
#define BOARD_INIT_UART_UART2_TX_SIGNAL                                       TX   /*!< LPUART2 signal: TX */

/* GPIO_AD_B1_03 (coord M12), UART2_RX */
#define BOARD_INIT_UART_UART2_RX_PERIPHERAL                              LPUART2   /*!< Device name: LPUART2 */
#define BOARD_INIT_UART_UART2_RX_SIGNAL                                       RX   /*!< LPUART2 signal: RX */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_UART(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
