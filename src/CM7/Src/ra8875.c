#include "ra8875.h"

#include <stdlib.h>
#include <stdint.h>

struct ra8875_state {
	GPIO_TypeDef      *RST_PORT;
	uint16_t           RST_PIN;
	GPIO_TypeDef      *INT_PORT;
	uint16_t           INT_PIN;
	SPI_HandleTypeDef *spi_port;
};

typedef enum ra8875_registers {
	REG_STSR = 0x00,    // Status Register (STSR)
	REG_PWRR = 0x01,    // Power and Display Control Register (PWRR)
	REG_PCSR = 0x04,    // Pixel Clock Setting Register (PCSR)
	REG_SROC = 0x05,    // Serial Flash/ROM Configuration Register (SROC)
	REG_SFCLR = 0x06,   // Serial Flash/ROM CLK Setting Register(SFCLR)
	REG_SYSR = 0x10,    // System Configuration Register (SYSR)
	REG_GPI = 0x12,     // GPI
	REG_GPO = 0x13,     // GPO
	REG_HDWR = 0x14,    // LCD Horizontal Display Width Register (HDWR)
	REG_HNDFTR = 0x15,  // Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)
	REG_HNDR = 0x16,    // LCD Horizontal Non-Display Period Register (HNDR)
	REG_HSTR = 0x17,    // HSYNC Start Position Register (HSTR)
	REG_HPWR = 0x18,    // HSYNC Pulse Width Register (HPWR)
	REG_VDHR0 = 0x19,   // LCD Vertical Display Height Register (VDHR0)
	REG_VDHR1 = 0x1A,   // LCD Vertical Display Height Register0 (VDHR1)
	REG_VNDR0 = 0x1B,   // LCD Vertical Non-Display Period Register (VNDR0)
	REG_VNDR1 = 0x1C,   // LCD Vertical Non-Display Period Register (VNDR1)
	REG_VSTR0 = 0x1D,   // VSYNC Start Position Register (VSTR0)
	REG_VSTR1 = 0x1E,   // VSYNC Start Position Register (VSTR1)
	REG_VPWR = 0x1F,    // VSYNC Pulse Width Register (VPWR)
	REG_DPCR = 0x20,    // Display Configuration Register (DPCR)
	REG_FNCR0 = 0x21,   // Font Control Register 0 (FNCR0)
	REG_FNCR1 = 0x22,   // Font Control Register1 (FNCR1)
	REG_CGSR = 0x23,    // CGRAM Select Register (CGSR)
	REG_HOFS0 = 0x24,   // Horizontal Scroll Offset Register 0 (HOFS0)
	REG_HOFS1 = 0x25,   // Horizontal Scroll Offset Register 1 (HOFS1)
	REG_VOFS0 = 0x26,   // Vertical Scroll Offset Register 0 (VOFS0)
	REG_VOFS1 = 0x27,   // Vertical Scroll Offset Register 1 (VOFS1)
	REG_FLDR = 0x29,    // Font Line Distance Setting Register (FLDR)
	REG_F_CURXL = 0x2A, // Font Write Cursor Horizontal Position Register 0 (F_CURXL)
	REG_F_CURXH = 0x2B, // Font Write Cursor Horizontal Position Register 1 (F_CURXH)
	REG_F_CURYL = 0x2C, // Font Write Cursor Vertical Position Register 0 (F_CURYL)
	REG_F_CURYH = 0x2D, // Font Write Cursor Vertical Position Register 1 (F_CURYH)
	REG_FWTS = 0x2E,    // Font Write Type Setting Register
	REG_SFROM = 0x2F,   // Serial Font ROM Setting
	REG_HSAW0 = 0x30,   // Horizontal Start Point 0 of Active Window (HSAW0)
	REG_HSAW1 = 0x31,   // Horizontal Start Point 1 of Active Window (HSAW1)
	REG_VSAW0 = 0x32,   // Vertical Start Point 0 of Active Window (VSAW0)
	REG_VSAW1 = 0x33,   // Vertical Start Point 1 of Active Window (VSAW1)
	REG_HEAW0 = 0x34,   // Horizontal End Point 0 of Active Window (HEAW0)
	REG_HEAW1 = 0x35,   // Horizontal End Point 1 of Active Window (HEAW1)
	REG_VEAW0 = 0x36,   // Vertical End Point of Active Window 0 (VEAW0)
	REG_VEAW1 = 0x37,   // Vertical End Point of Active Window 1 (VEAW1)
	REG_HSSW0 = 0x38,   // Horizontal Start Point 0 of Scroll Window (HSSW0)
	REG_HSSW1 = 0x39,   // Horizontal Start Point 1 of Scroll Window (HSSW1)
	REG_VSSW0 = 0x3A,   // Vertical Start Point 0 of Scroll Window (VSSW0)
	REG_VSSW1 = 0x3B,   // Vertical Start Point 1 of Scroll Window (VSSW1)
	REG_HESW0 = 0x3C,   // Horizontal End Point 0 of Scroll Window (HESW0)
	REG_HESW1 = 0x3D,   // Horizontal End Point 1 of Scroll Window (HESW1)
	REG_VESW0 = 0x3E,   // Vertical End Point 0 of Scroll Window (VESW0)
	REG_VESW1 = 0x3F,   // Vertical End Point 1 of Scroll Window (VESW1)
	REG_MWCR0 = 0x40,   // Memory Write Control Register 0 (MWCR0)
	REG_MWCR1 = 0x41,   // Memory Write Control Register1 (MWCR1)
	REG_BTCR = 0x44,    // Blink Time Control Register (BTCR)
	REG_MRCD = 0x45,    // Memory Read Cursor Direction (MRCD)
	REG_CURH0 = 0x46,   // Memory Write Cursor Horizontal Position Register 0 (CURH0)
	REG_CURH1 = 0x47,   // Memory Write Cursor Horizontal Position Register 1 (CURH1)
	REG_CURV0 = 0x48,   // Memory Write Cursor Vertical Position Register 0 (CURV0)
	REG_CURV1 = 0x49,   // Memory Write Cursor Vertical Position Register 1 (CURV1)
	REG_RCURH0 = 0x4A,  // Memory Read Cursor Horizontal Position Register 0 (RCURH0)
	REG_RCURH01 = 0x4B, // Memory Read Cursor Horizontal Position Register 1 (RCURH01)
	REG_RCURV0 = 0x4C,  // Memory Read Cursor Vertical Position Register 0 (RCURV0)
	REG_RCURV1 = 0x4D,  // Memory Read Cursor Vertical Position Register 1 (RCURV1)
	REG_CURHS = 0x4E,   // Font Write Cursor and Memory Write Cursor Horizontal Size Register (CURHS)
	REG_CURVS = 0x4F,   // Font Write Cursor Vertical Size Register (CURVS)
	REG_BECR0 = 0x50,   // BTE Function Control Register 0 (BECR0)
	REG_BECR1 = 0x51,   // BTE Function Control Register1 (BECR1)
	REG_LTPR0 = 0x52,   // Layer Transparency Register0 (LTPR0)
	REG_LTPR1 = 0x53,   // Layer Transparency Register1 (LTPR1)
	REG_HSBE0 = 0x54,   // Horizontal Source Point 0 of BTE (HSBE0)
	REG_HSBE1 = 0x55,   // Horizontal Source Point 1 of BTE (HSBE1)
	REG_VSBE0 = 0x56,   // Vertical Source Point 0 of BTE (VSBE0)
	REG_VSBE1 = 0x57,   // Vertical Source Point 1 of BTE (VSBE1)
	REG_HDBE0 = 0x58,   // Horizontal Destination Point 0 of BTE (HDBE0)
	REG_HDBE1 = 0x59,   // Horizontal Destination Point 1 of BTE (HDBE1)
	REG_VDBE0 = 0x5A,   // Vertical Destination Point 0 of BTE (VDBE0)
	REG_VDBE1 = 0x5B,   // Vertical Destination Point 1 of BTE (VDBE1)
	REG_BEWR0 = 0x5C,   // BTE Width Register 0 (BEWR0)
	REG_BEWR1 = 0x5D,   // BTE Width Register 1 (BEWR1)
	REG_BEHR0 = 0x5E,   // BTE Height Register 0 (BEHR0)
	REG_BEHR1 = 0x5F,   // BTE Height Register 1 (BEHR1)
	REG_BGCR0 = 0x60,   // Background Color Register 0 (BGCR0)
	REG_BGCR1 = 0x61,   // Background Color Register 1 (BGCR1)
	REG_BGCR2 = 0x62,   // Background Color Register 2 (BGCR2)
	REG_FGCR0 = 0x63,   // Foreground Color Register 0 (FGCR0)
	REG_FGCR1 = 0x64,   // Foreground Color Register 1 (FGCR1)
	REG_FGCR2 = 0x65,   // Foreground Color Register 2 (FGCR2)
	REG_PTNO = 0x66,    // Pattern Set No for BTE (PTNO)
	REG_BGTR0 = 0x67,   // Background Color Register for Transparent 0 (BGTR0)
	REG_BGTR1 = 0x68,   // Background Color Register for Transparent 1 (BGTR1)
	REG_BGTR2 = 0x69,   // Background Color Register for Transparent 2 (BGTR2)
	REG_TPCR0 = 0x70,   // Touch Panel Control Register 0 (TPCR0)
	REG_TPCR1 = 0x71,   // Touch Panel Control Register 1 (TPCR1)
	REG_TPXH = 0x72,    // Touch Panel X High Byte Data Register (TPXH)
	REG_TPYH = 0x73,    // Touch Panel Y High Byte Data Register (TPYH)
	REG_TPXYL = 0x74,   // Touch Panel X/Y Low Byte Data Register (TPXYL)
	REG_GCHP0 = 0x80,   // Graphic Cursor Horizontal Position Register 0 (GCHP0)
	REG_GCHP1 = 0x81,   // Graphic Cursor Horizontal Position Register 1 (GCHP1)
	REG_GCVP0 = 0x82,   // Graphic Cursor Vertical Position Register 0 (GCVP0)
	REG_GCVP1 = 0x83,   // Graphic Cursor Vertical Position Register 1 (GCVP1)
	REG_GCC0 = 0x84,    // Graphic Cursor Color 0 (GCC0)
	REG_GCC1 = 0x85,    // Graphic Cursor Color 1 (GCC1)
	REG_PLLC1 = 0x88,   // PLL Control Register 1 (PLLC1)
	REG_PLLC2 = 0x89,   // PLL Control Register 2 (PLLC2)
	REG_P1CR = 0x8A,    // PWM1 Control Register (P1CR)
	REG_P1DCR = 0x8B,   // PWM1 Duty Cycle Register (P1DCR)
	REG_P2CR = 0x8C,    // PWM2 Control Register (P2CR)
	REG_P2DCR = 0x8D,   // PWM2 Control Register (P2DCR)
	REG_MCLR = 0x8E,    // Memory Clear Control Register (MCLR)
	REG_DCR = 0x90,     // Draw Line/Circle/Square Control Register (DCR)
	REG_DLHSR0 = 0x91,  // Draw Line/Square Horizontal Start Address Register0 (DLHSR0)
	REG_DLHSR1 = 0x92,  // Draw Line/Square Horizontal Start Address Register1 (DLHSR1)
	REG_DLVSR0 = 0x93,  // Draw Line/Square Vertical Start Address Register0 (DLVSR0)
	REG_DLVSR1 = 0x94,  // Draw Line/Square Vertical Start Address Register1 (DLVSR1)
	REG_DLHER0 = 0x95,  // Draw Line/Square Horizontal End Address Register0 (DLHER0)
	REG_DLHER1 = 0x96,  // Draw Line/Square Horizontal End Address Register1 (DLHER1)
	REG_DLVER0 = 0x97,  // Draw Line/Square Vertical End Address Register0 (DLVER0)
	REG_DLVER1 = 0x98,  // Draw Line/Square Vertical End Address Register1 (DLVER1)
	REG_DCHR0 = 0x99,   // Draw Circle Center Horizontal Address Register0 (DCHR0)
	REG_DCHR1 = 0x9A,   // Draw Circle Center Horizontal Address Register1 (DCHR1)
	REG_DCVR0 = 0x9B,   // Draw Circle Center Vertical Address Register0 (DCVR0)
	REG_DCVR1 = 0x9C,   // Draw Circle Center Vertical Address Register1 (DCVR1)
	REG_DCRR = 0x9D,    // Draw Circle Radius Register (DCRR)
	REG_DEECCS = 0xA0,  // Draw Ellipse/Ellipse Curve/Circle Square Control Register
	REG_ELL_A0 = 0xA1,  // Draw Ellipse/Circle Square Long axis Setting Register (ELL_A0)
	REG_ELL_A1 = 0xA2,  // Draw Ellipse/Circle Square Long axis Setting Register (ELL_A1)
	REG_ELL_B0 = 0xA3,  // Draw Ellipse/Circle Square Short axis Setting Register (ELL_B0)
	REG_ELL_B1 = 0xA4,  // Draw Ellipse/Circle Square Short axis Setting Register (ELL_B1)
	REG_DEHR0 = 0xA5,   // Draw Ellipse/Circle Square Center Horizontal Address Register0 (DEHR0)
	REG_DEHR1 = 0xA6,   // Draw Ellipse/Circle Square Center Horizontal Address Register1 (DEHR1)
	REG_DEVR0 = 0xA7,   // Draw Ellipse/Circle Square Center Vertical Address Register0 (DEVR0)
	REG_DEVR1 = 0xA8,   // Draw Ellipse/Circle Square Center Vertical Address Register1 (DEVR1)
	REG_DTPH0 = 0xA9,   // Draw Triangle Point 2 Horizontal Address Register0 (DTPH0)
	REG_DTPH1 = 0xAA,   // Draw Triangle Point 2 Horizontal Address Register1 (DTPH1)
	REG_DTPV0 = 0xAB,   // Draw Triangle Point 2 Vertical Address Register0 (DTPV0)
	REG_DTPV1 = 0xAC,   // Draw Triangle Point 2 Vertical Address Register1 (DTPV1)
	REG_SSAR0 = 0xB0,   // Source Starting Address REG0 (SSAR0)
	REG_SSAR1 = 0xB1,   // Source Starting Address REG 1 (SSAR1)
	REG_SSAR2 = 0xB2,   // Source Starting Address REG 2 (SSAR2)
	REG_DTNR0 = 0xB4,   // Block Width REG 0(BWR0) / DMA Transfer Number REG 0 (DTNR0)
	REG_BWR1 = 0xB5,    // Block Width REG 1 (BWR1)
	REG_DTNR1 = 0xB6,   // Block Height REG 0(BHR0) /DMA Transfer Number REG 1 (DTNR1)
	REG_BHR1 = 0xB7,    // Block Height REG 1 (BHR1)
	REG_SPWR0 = 0xB8,   // Source Picture Width REG 0(SPWR0) / DMA Transfer Number REG 2(DTNR2)
	REG_SPWR1 = 0xB9,   // Source Picture Width REG 1 (SPWR1)
	REG_DMACR = 0xBF,   // DMA Configuration REG (DMACR)
	REG_GPIOX = 0xC7,   // Extra General Purpose IO Register (GPIOX)
	REG_INTC1 = 0xF0,   // Interrupt Control Register1 (INTC1)
	REG_INTC2 = 0xF1,   // Interrupt Control Register2 (INTC2)
} ra8875_registers;

#define check_result(hr) { if (hr != RA8875_OK) { goto exit_function; } }

ra8875_result ra8875_cmd_write(struct ra8875_state *state, uint8_t command);
ra8875_result ra8875_data_write(struct ra8875_state *state, uint8_t data);
ra8875_result ra8875_set_register(struct ra8875_state *state, uint8_t register, uint8_t data);
ra8875_result ra8875_reset(struct ra8875_state *state);
ra8875_result ra8875_init_pll(struct ra8875_state *state);
ra8875_result ra8875_init_lcd(struct ra8875_state *state);

ra8875_result ra8875_initialize(struct ra8875_state **state_pointer, SPI_HandleTypeDef *spi_port, GPIO_TypeDef *RST_PORT, uint16_t RST_PIN, GPIO_TypeDef *INT_PORT, uint16_t INT_PIN)
{
	if (state_pointer == NULL) return RA8875_INVALID_POINTER;
	if (*state_pointer != NULL) return RA8875_INVALID_POINTER;
	*state_pointer = calloc(1, sizeof(struct ra8875_state));
	struct ra8875_state *state = *state_pointer;
	state->RST_PORT = RST_PORT;
	state->RST_PIN = RST_PIN;
	state->INT_PORT = INT_PORT;
	state->INT_PIN = INT_PIN;

	ra8875_result rv = RA8875_OK;
	check_result(ra8875_reset(state));
	check_result(ra8875_init_pll(state));
	check_result(ra8875_init_lcd(state));

exit_function:
	if (rv != RA8875_OK) ra8875_destroy(state_pointer);

	return rv;
}

ra8875_result ra8875_destroy(struct ra8875_state **state_pointer)
{
	if (state_pointer == NULL) return RA8875_INVALID_POINTER;
	if (*state_pointer == NULL) return RA8875_INVALID_POINTER;
	free(*state_pointer);
	*state_pointer = NULL;
	return RA8875_OK;
}

ra8875_result ra8875_init_lcd(struct ra8875_state *state)
{
	ra8875_result rv = RA8875_OK;

	//check_result(ra8875_set_register(state, REG_SYSR, 0x00)); // 256 colors
	check_result(ra8875_set_register(state, REG_SYSR, 0x0C)); // 65k colors

	// PDAT is fetched at PCLK falling edge
	// PCLK period = 2 times of System Clock period.
	check_result(ra8875_set_register(state, REG_PCSR, 0x81));
	// TODO Delay1ms(1);

	check_result(ra8875_set_register(state, REG_HDWR, 0x63));

	//Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)
	//Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]
	check_result(ra8875_set_register(state, REG_HNDFTR, 0x00));
	//HNDR//Horizontal Non-Display Period Bit[4:0]
	//Horizontal Non-Display Period (pixels) = (HNDR + 1)*8
	check_result(ra8875_set_register(state, REG_HNDR, 0x03));
	//HSTR//HSYNC Start Position[4:0]
	//HSYNC Start Position(PCLK) = (HSTR + 1)*8
	check_result(ra8875_set_register(state, REG_HSTR, 0x03));
	//HPWR//HSYNC Polarity ,The period width of HSYNC.
	//HSYNC Width [4:0] HSYNC Pulse width(PCLK) = (HPWR + 1)*8
	check_result(ra8875_set_register(state, REG_HPWR, 0x0B));

	//Vertical set
	//VDHR0 //Vertical Display Height Bit [7:0]
	//Vertical pixels = VDHR + 1
	check_result(ra8875_set_register(state, REG_VDHR0, 0xdf));
	//VDHR1 //Vertical Display Height Bit [8]
	//Vertical pixels = VDHR + 1
	check_result(ra8875_set_register(state, REG_VDHR1, 0x01));
	//VNDR0 //Vertical Non-Display Period Bit [7:0]
	//Vertical Non-Display area = (VNDR + 1)
	check_result(ra8875_set_register(state, REG_VNDR0, 0x20));
	//VNDR1 //Vertical Non-Display Period Bit [8]
	//Vertical Non-Display area = (VNDR + 1)
	check_result(ra8875_set_register(state, REG_VNDR1, 0x00));
	//VSTR0 //VSYNC Start Position[7:0]
	//VSYNC Start Position(PCLK) = (VSTR + 1)
	check_result(ra8875_set_register(state, REG_VSTR0, 0x16));
	//VSTR1 //VSYNC Start Position[8]
	//VSYNC Start Position(PCLK) = (VSTR + 1)
	check_result(ra8875_set_register(state, REG_VSTR1, 0x00));
	//VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0]
	//VSYNC Pulse Width(PCLK) = (VPWR + 1)
	check_result(ra8875_set_register(state, REG_VPWR, 0x01));

	//Active window set
	//setting active window X
	//Horizontal Start Point 0 of Active Window (HSAW0)
	//Horizontal Start Point of Active Window [7:0]
	check_result(ra8875_set_register(state, REG_HSAW0, 0x00));
	//Horizontal Start Point 1 of Active Window (HSAW1)
	//Horizontal Start Point of Active Window [9:8]
	check_result(ra8875_set_register(state, REG_HSAW1, 0x00));
	//Horizontal End Point 0 of Active Window (HEAW0)
	//Horizontal End Point of Active Window [7:0]
	check_result(ra8875_set_register(state, REG_HEAW0, 0x1F));
	//Horizontal End Point 1 of Active Window (HEAW1)
	//Horizontal End Point of Active Window [9:8]
	check_result(ra8875_set_register(state, REG_HEAW1, 0x03));

	//setting active window Y
	//Vertical Start Point 0 of Active Window (VSAW0)
	//Vertical Start Point of Active Window [7:0]
	check_result(ra8875_set_register(state, REG_VSAW0, 0x00));
	//Vertical Start Point 1 of Active Window (VSAW1)
	//Vertical Start Point of Active Window [8]
	check_result(ra8875_set_register(state, REG_VSAW1, 0x00));
	//Vertical End Point of Active Window 0 (VEAW0)
	//Vertical End Point of Active Window [7:0]
	check_result(ra8875_set_register(state, REG_VEAW0, 0xdf));
	//Vertical End Point of Active Window 1 (VEAW1)
	//Vertical End Point of Active Window [8]
	check_result(ra8875_set_register(state, REG_VEAW1, 0x01));

	//Clear screen
	check_result(ra8875_set_register(state, REG_MCLR, 0x80));

	Delay1ms(100);

exit_function:
	return rv;
}

ra8875_result ra8875_init_pll(struct ra8875_state *state)
{
	ra8875_result rv = RA8875_OK;

	check_result(ra8875_set_register(state, REG_PLLC1, 0x0b));
	// TODO Delay1ms(1);
	check_result(ra8875_set_register(state, REG_PLLC2, 0x02));
	// TODO Delay1ms(1);
exit_function:
	return rv;
}

ra8875_result ra8875_reset(struct ra8875_state *state)
{
    state->RST_PORT->BSRR = (uint32_t)state->RST_PIN << 16;
    // TODO Delay1ms(1);
	state->RST_PORT->BSRR = state->RST_PIN;
	// TODO Delay1ms(10);
	return RA8875_OK;
}

ra8875_result ra8875_set_register(struct ra8875_state *state, uint8_t reg, uint8_t data)
{
	ra8875_result rv = RA8875_OK;
	check_result(ra8875_cmd_write(state, reg));
	check_result(ra8875_data_write(state, data));
exit_function:
	return rv;
}

ra8875_result ra8875_cmd_write(struct ra8875_state *state, uint8_t command)
{
	return (HAL_SPI_Transmit(state->spi_port, &command, 1, 500) == HAL_OK) ? RA8875_OK : RA8875_SPI_ERROR;
}

ra8875_result ra8875_data_write(struct ra8875_state *state, uint8_t data)
{
	return (HAL_SPI_Transmit(state->spi_port, &data, 1, 500) == HAL_OK) ? RA8875_OK : RA8875_SPI_ERROR;
}
