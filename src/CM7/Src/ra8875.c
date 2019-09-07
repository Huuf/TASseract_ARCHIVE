#include "ra8875.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "usbd_cdc_if.h"
#include "stm32h7xx_hal.h"

struct ra8875_state {
	GPIO_TypeDef      *RST_PORT;
	uint16_t           RST_PIN;
	GPIO_TypeDef      *INT_PORT;
	uint16_t           INT_PIN;
	GPIO_TypeDef      *CS_PORT;
	uint16_t           CS_PIN;
	SPI_HandleTypeDef *spi_port;
};

typedef enum ra8875_registers {
	RA8875_REG_STSR = 0x00,    // Status Register (STSR)
	RA8875_REG_PWRR = 0x01,    // Power and Display Control Register (PWRR)
	RA8875_REG_MRWC = 0x02,    // Memory Read/Write Command (MRWC)
	RA8875_REG_PCSR = 0x04,    // Pixel Clock Setting Register (PCSR)
	RA8875_REG_SROC = 0x05,    // Serial Flash/ROM Configuration Register (SROC)
	RA8875_REG_SFCLR = 0x06,   // Serial Flash/ROM CLK Setting Register(SFCLR)
	RA8875_REG_SYSR = 0x10,    // System Configuration Register (SYSR)
	RA8875_REG_GPI = 0x12,     // GPI
	RA8875_REG_GPO = 0x13,     // GPO
	RA8875_REG_HDWR = 0x14,    // LCD Horizontal Display Width Register (HDWR)
	RA8875_REG_HNDFTR = 0x15,  // Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)
	RA8875_REG_HNDR = 0x16,    // LCD Horizontal Non-Display Period Register (HNDR)
	RA8875_REG_HSTR = 0x17,    // HSYNC Start Position Register (HSTR)
	RA8875_REG_HPWR = 0x18,    // HSYNC Pulse Width Register (HPWR)
	RA8875_REG_VDHR0 = 0x19,   // LCD Vertical Display Height Register (VDHR0)
	RA8875_REG_VDHR1 = 0x1A,   // LCD Vertical Display Height Register0 (VDHR1)
	RA8875_REG_VNDR0 = 0x1B,   // LCD Vertical Non-Display Period Register (VNDR0)
	RA8875_REG_VNDR1 = 0x1C,   // LCD Vertical Non-Display Period Register (VNDR1)
	RA8875_REG_VSTR0 = 0x1D,   // VSYNC Start Position Register (VSTR0)
	RA8875_REG_VSTR1 = 0x1E,   // VSYNC Start Position Register (VSTR1)
	RA8875_REG_VPWR = 0x1F,    // VSYNC Pulse Width Register (VPWR)
	RA8875_REG_DPCR = 0x20,    // Display Configuration Register (DPCR)
	RA8875_REG_FNCR0 = 0x21,   // Font Control Register 0 (FNCR0)
	RA8875_REG_FNCR1 = 0x22,   // Font Control Register1 (FNCR1)
	RA8875_REG_CGSR = 0x23,    // CGRAM Select Register (CGSR)
	RA8875_REG_HOFS0 = 0x24,   // Horizontal Scroll Offset Register 0 (HOFS0)
	RA8875_REG_HOFS1 = 0x25,   // Horizontal Scroll Offset Register 1 (HOFS1)
	RA8875_REG_VOFS0 = 0x26,   // Vertical Scroll Offset Register 0 (VOFS0)
	RA8875_REG_VOFS1 = 0x27,   // Vertical Scroll Offset Register 1 (VOFS1)
	RA8875_REG_FLDR = 0x29,    // Font Line Distance Setting Register (FLDR)
	RA8875_REG_F_CURXL = 0x2A, // Font Write Cursor Horizontal Position Register 0 (F_CURXL)
	RA8875_REG_F_CURXH = 0x2B, // Font Write Cursor Horizontal Position Register 1 (F_CURXH)
	RA8875_REG_F_CURYL = 0x2C, // Font Write Cursor Vertical Position Register 0 (F_CURYL)
	RA8875_REG_F_CURYH = 0x2D, // Font Write Cursor Vertical Position Register 1 (F_CURYH)
	RA8875_REG_FWTS = 0x2E,    // Font Write Type Setting Register
	RA8875_REG_SFROM = 0x2F,   // Serial Font ROM Setting
	RA8875_REG_HSAW0 = 0x30,   // Horizontal Start Point 0 of Active Window (HSAW0)
	RA8875_REG_HSAW1 = 0x31,   // Horizontal Start Point 1 of Active Window (HSAW1)
	RA8875_REG_VSAW0 = 0x32,   // Vertical Start Point 0 of Active Window (VSAW0)
	RA8875_REG_VSAW1 = 0x33,   // Vertical Start Point 1 of Active Window (VSAW1)
	RA8875_REG_HEAW0 = 0x34,   // Horizontal End Point 0 of Active Window (HEAW0)
	RA8875_REG_HEAW1 = 0x35,   // Horizontal End Point 1 of Active Window (HEAW1)
	RA8875_REG_VEAW0 = 0x36,   // Vertical End Point of Active Window 0 (VEAW0)
	RA8875_REG_VEAW1 = 0x37,   // Vertical End Point of Active Window 1 (VEAW1)
	RA8875_REG_HSSW0 = 0x38,   // Horizontal Start Point 0 of Scroll Window (HSSW0)
	RA8875_REG_HSSW1 = 0x39,   // Horizontal Start Point 1 of Scroll Window (HSSW1)
	RA8875_REG_VSSW0 = 0x3A,   // Vertical Start Point 0 of Scroll Window (VSSW0)
	RA8875_REG_VSSW1 = 0x3B,   // Vertical Start Point 1 of Scroll Window (VSSW1)
	RA8875_REG_HESW0 = 0x3C,   // Horizontal End Point 0 of Scroll Window (HESW0)
	RA8875_REG_HESW1 = 0x3D,   // Horizontal End Point 1 of Scroll Window (HESW1)
	RA8875_REG_VESW0 = 0x3E,   // Vertical End Point 0 of Scroll Window (VESW0)
	RA8875_REG_VESW1 = 0x3F,   // Vertical End Point 1 of Scroll Window (VESW1)
	RA8875_REG_MWCR0 = 0x40,   // Memory Write Control Register 0 (MWCR0)
	RA8875_REG_MWCR1 = 0x41,   // Memory Write Control Register1 (MWCR1)
	RA8875_REG_BTCR = 0x44,    // Blink Time Control Register (BTCR)
	RA8875_REG_MRCD = 0x45,    // Memory Read Cursor Direction (MRCD)
	RA8875_REG_CURH0 = 0x46,   // Memory Write Cursor Horizontal Position Register 0 (CURH0)
	RA8875_REG_CURH1 = 0x47,   // Memory Write Cursor Horizontal Position Register 1 (CURH1)
	RA8875_REG_CURV0 = 0x48,   // Memory Write Cursor Vertical Position Register 0 (CURV0)
	RA8875_REG_CURV1 = 0x49,   // Memory Write Cursor Vertical Position Register 1 (CURV1)
	RA8875_REG_RCURH0 = 0x4A,  // Memory Read Cursor Horizontal Position Register 0 (RCURH0)
	RA8875_REG_RCURH01 = 0x4B, // Memory Read Cursor Horizontal Position Register 1 (RCURH01)
	RA8875_REG_RCURV0 = 0x4C,  // Memory Read Cursor Vertical Position Register 0 (RCURV0)
	RA8875_REG_RCURV1 = 0x4D,  // Memory Read Cursor Vertical Position Register 1 (RCURV1)
	RA8875_REG_CURHS = 0x4E,   // Font Write Cursor and Memory Write Cursor Horizontal Size Register (CURHS)
	RA8875_REG_CURVS = 0x4F,   // Font Write Cursor Vertical Size Register (CURVS)
	RA8875_REG_BECR0 = 0x50,   // BTE Function Control Register 0 (BECR0)
	RA8875_REG_BECR1 = 0x51,   // BTE Function Control Register1 (BECR1)
	RA8875_REG_LTPR0 = 0x52,   // Layer Transparency Register0 (LTPR0)
	RA8875_REG_LTPR1 = 0x53,   // Layer Transparency Register1 (LTPR1)
	RA8875_REG_HSBE0 = 0x54,   // Horizontal Source Point 0 of BTE (HSBE0)
	RA8875_REG_HSBE1 = 0x55,   // Horizontal Source Point 1 of BTE (HSBE1)
	RA8875_REG_VSBE0 = 0x56,   // Vertical Source Point 0 of BTE (VSBE0)
	RA8875_REG_VSBE1 = 0x57,   // Vertical Source Point 1 of BTE (VSBE1)
	RA8875_REG_HDBE0 = 0x58,   // Horizontal Destination Point 0 of BTE (HDBE0)
	RA8875_REG_HDBE1 = 0x59,   // Horizontal Destination Point 1 of BTE (HDBE1)
	RA8875_REG_VDBE0 = 0x5A,   // Vertical Destination Point 0 of BTE (VDBE0)
	RA8875_REG_VDBE1 = 0x5B,   // Vertical Destination Point 1 of BTE (VDBE1)
	RA8875_REG_BEWR0 = 0x5C,   // BTE Width Register 0 (BEWR0)
	RA8875_REG_BEWR1 = 0x5D,   // BTE Width Register 1 (BEWR1)
	RA8875_REG_BEHR0 = 0x5E,   // BTE Height Register 0 (BEHR0)
	RA8875_REG_BEHR1 = 0x5F,   // BTE Height Register 1 (BEHR1)
	RA8875_REG_BGCR0 = 0x60,   // Background Color Register 0 (BGCR0)
	RA8875_REG_BGCR1 = 0x61,   // Background Color Register 1 (BGCR1)
	RA8875_REG_BGCR2 = 0x62,   // Background Color Register 2 (BGCR2)
	RA8875_REG_FGCR0 = 0x63,   // Foreground Color Register 0 (FGCR0)
	RA8875_REG_FGCR1 = 0x64,   // Foreground Color Register 1 (FGCR1)
	RA8875_REG_FGCR2 = 0x65,   // Foreground Color Register 2 (FGCR2)
	RA8875_REG_PTNO = 0x66,    // Pattern Set No for BTE (PTNO)
	RA8875_REG_BGTR0 = 0x67,   // Background Color Register for Transparent 0 (BGTR0)
	RA8875_REG_BGTR1 = 0x68,   // Background Color Register for Transparent 1 (BGTR1)
	RA8875_REG_BGTR2 = 0x69,   // Background Color Register for Transparent 2 (BGTR2)
	RA8875_REG_TPCR0 = 0x70,   // Touch Panel Control Register 0 (TPCR0)
	RA8875_REG_TPCR1 = 0x71,   // Touch Panel Control Register 1 (TPCR1)
	RA8875_REG_TPXH = 0x72,    // Touch Panel X High Byte Data Register (TPXH)
	RA8875_REG_TPYH = 0x73,    // Touch Panel Y High Byte Data Register (TPYH)
	RA8875_REG_TPXYL = 0x74,   // Touch Panel X/Y Low Byte Data Register (TPXYL)
	RA8875_REG_GCHP0 = 0x80,   // Graphic Cursor Horizontal Position Register 0 (GCHP0)
	RA8875_REG_GCHP1 = 0x81,   // Graphic Cursor Horizontal Position Register 1 (GCHP1)
	RA8875_REG_GCVP0 = 0x82,   // Graphic Cursor Vertical Position Register 0 (GCVP0)
	RA8875_REG_GCVP1 = 0x83,   // Graphic Cursor Vertical Position Register 1 (GCVP1)
	RA8875_REG_GCC0 = 0x84,    // Graphic Cursor Color 0 (GCC0)
	RA8875_REG_GCC1 = 0x85,    // Graphic Cursor Color 1 (GCC1)
	RA8875_REG_PLLC1 = 0x88,   // PLL Control Register 1 (PLLC1)
	RA8875_REG_PLLC2 = 0x89,   // PLL Control Register 2 (PLLC2)
	RA8875_REG_P1CR = 0x8A,    // PWM1 Control Register (P1CR)
	RA8875_REG_P1DCR = 0x8B,   // PWM1 Duty Cycle Register (P1DCR)
	RA8875_REG_P2CR = 0x8C,    // PWM2 Control Register (P2CR)
	RA8875_REG_P2DCR = 0x8D,   // PWM2 Control Register (P2DCR)
	RA8875_REG_MCLR = 0x8E,    // Memory Clear Control Register (MCLR)
	RA8875_REG_DCR = 0x90,     // Draw Line/Circle/Square Control Register (DCR)
	RA8875_REG_DLHSR0 = 0x91,  // Draw Line/Square Horizontal Start Address Register0 (DLHSR0)
	RA8875_REG_DLHSR1 = 0x92,  // Draw Line/Square Horizontal Start Address Register1 (DLHSR1)
	RA8875_REG_DLVSR0 = 0x93,  // Draw Line/Square Vertical Start Address Register0 (DLVSR0)
	RA8875_REG_DLVSR1 = 0x94,  // Draw Line/Square Vertical Start Address Register1 (DLVSR1)
	RA8875_REG_DLHER0 = 0x95,  // Draw Line/Square Horizontal End Address Register0 (DLHER0)
	RA8875_REG_DLHER1 = 0x96,  // Draw Line/Square Horizontal End Address Register1 (DLHER1)
	RA8875_REG_DLVER0 = 0x97,  // Draw Line/Square Vertical End Address Register0 (DLVER0)
	RA8875_REG_DLVER1 = 0x98,  // Draw Line/Square Vertical End Address Register1 (DLVER1)
	RA8875_REG_DCHR0 = 0x99,   // Draw Circle Center Horizontal Address Register0 (DCHR0)
	RA8875_REG_DCHR1 = 0x9A,   // Draw Circle Center Horizontal Address Register1 (DCHR1)
	RA8875_REG_DCVR0 = 0x9B,   // Draw Circle Center Vertical Address Register0 (DCVR0)
	RA8875_REG_DCVR1 = 0x9C,   // Draw Circle Center Vertical Address Register1 (DCVR1)
	RA8875_REG_DCRR = 0x9D,    // Draw Circle Radius Register (DCRR)
	RA8875_REG_DEECCS = 0xA0,  // Draw Ellipse/Ellipse Curve/Circle Square Control Register
	RA8875_REG_ELL_A0 = 0xA1,  // Draw Ellipse/Circle Square Long axis Setting Register (ELL_A0)
	RA8875_REG_ELL_A1 = 0xA2,  // Draw Ellipse/Circle Square Long axis Setting Register (ELL_A1)
	RA8875_REG_ELL_B0 = 0xA3,  // Draw Ellipse/Circle Square Short axis Setting Register (ELL_B0)
	RA8875_REG_ELL_B1 = 0xA4,  // Draw Ellipse/Circle Square Short axis Setting Register (ELL_B1)
	RA8875_REG_DEHR0 = 0xA5,   // Draw Ellipse/Circle Square Center Horizontal Address Register0 (DEHR0)
	RA8875_REG_DEHR1 = 0xA6,   // Draw Ellipse/Circle Square Center Horizontal Address Register1 (DEHR1)
	RA8875_REG_DEVR0 = 0xA7,   // Draw Ellipse/Circle Square Center Vertical Address Register0 (DEVR0)
	RA8875_REG_DEVR1 = 0xA8,   // Draw Ellipse/Circle Square Center Vertical Address Register1 (DEVR1)
	RA8875_REG_DTPH0 = 0xA9,   // Draw Triangle Point 2 Horizontal Address Register0 (DTPH0)
	RA8875_REG_DTPH1 = 0xAA,   // Draw Triangle Point 2 Horizontal Address Register1 (DTPH1)
	RA8875_REG_DTPV0 = 0xAB,   // Draw Triangle Point 2 Vertical Address Register0 (DTPV0)
	RA8875_REG_DTPV1 = 0xAC,   // Draw Triangle Point 2 Vertical Address Register1 (DTPV1)
	RA8875_REG_SSAR0 = 0xB0,   // Source Starting Address REG0 (SSAR0)
	RA8875_REG_SSAR1 = 0xB1,   // Source Starting Address REG 1 (SSAR1)
	RA8875_REG_SSAR2 = 0xB2,   // Source Starting Address REG 2 (SSAR2)
	RA8875_REG_DTNR0 = 0xB4,   // Block Width REG 0(BWR0) / DMA Transfer Number REG 0 (DTNR0)
	RA8875_REG_BWR1 = 0xB5,    // Block Width REG 1 (BWR1)
	RA8875_REG_DTNR1 = 0xB6,   // Block Height REG 0(BHR0) /DMA Transfer Number REG 1 (DTNR1)
	RA8875_REG_BHR1 = 0xB7,    // Block Height REG 1 (BHR1)
	RA8875_REG_SPWR0 = 0xB8,   // Source Picture Width REG 0(SPWR0) / DMA Transfer Number REG 2(DTNR2)
	RA8875_REG_SPWR1 = 0xB9,   // Source Picture Width REG 1 (SPWR1)
	RA8875_REG_DMACR = 0xBF,   // DMA Configuration REG (DMACR)
	RA8875_REG_GPIOX = 0xC7,   // Extra General Purpose IO Register (GPIOX)
	RA8875_REG_INTC1 = 0xF0,   // Interrupt Control Register1 (INTC1)
	RA8875_REG_INTC2 = 0xF1,   // Interrupt Control Register2 (INTC2)
} ra8875_registers;

#define check_result(hr) { if (hr != RA8875_OK) { goto exit_function; } }

ra8875_result ra8875_cmd_write(struct ra8875_state *state, uint8_t command);
ra8875_result ra8875_data_write(struct ra8875_state *state, uint8_t data);
ra8875_result ra8875_set_register(struct ra8875_state *state, uint8_t register, uint8_t data);
ra8875_result ra8875_reset(struct ra8875_state *state);
ra8875_result ra8875_init_pll(struct ra8875_state *state);
ra8875_result ra8875_init_lcd(struct ra8875_state *state);
ra8875_result ra8875_read_register(struct ra8875_state *state, uint8_t reg, uint8_t *value);
void ra8875_wait_for_register_flag(struct ra8875_state *state, uint8_t reg, uint8_t flag);

ra8875_result ra8875_initialize(struct ra8875_state **state_pointer, SPI_HandleTypeDef *spi_port, GPIO_TypeDef *RST_PORT, uint16_t RST_PIN,
	GPIO_TypeDef *INT_PORT, uint16_t INT_PIN, GPIO_TypeDef *CS_PORT, uint16_t CS_PIN)
{
	if (state_pointer == NULL) return RA8875_INVALID_POINTER;
	if (*state_pointer != NULL) return RA8875_INVALID_POINTER;
	*state_pointer = calloc(1, sizeof(struct ra8875_state));
	struct ra8875_state *state = *state_pointer;
	state->spi_port = spi_port;
	state->RST_PORT = RST_PORT;
	state->RST_PIN = RST_PIN;
	state->INT_PORT = INT_PORT;
	state->INT_PIN = INT_PIN;
	state->CS_PORT = CS_PORT;
	state->CS_PIN = CS_PIN;

	ra8875_result rv = RA8875_OK;
	check_result(ra8875_reset(state));
	uint8_t val = 0;
	ra8875_read_register(state, RA8875_REG_STSR, &val);

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

ra8875_result ra8875_turn_on_display(struct ra8875_state *ra8875, bool on)
{
	return ra8875_set_register(ra8875, RA8875_REG_PWRR, on ? 0x80 : 0x00);
}

ra8875_result ra8875_gpiox(struct ra8875_state *ra8875, bool state)
{
	return ra8875_set_register(ra8875, RA8875_REG_GPIOX, state ? 0x01 : 0x00);
}

ra8875_result ra8875_pwm1_setup(struct ra8875_state *ra8875, bool on, uint8_t divider)
{
	return ra8875_set_register(ra8875, RA8875_REG_P1CR, (on ? 0x80 : 0x00) | divider);
}

ra8875_result ra8875_pwm1_duty_cycle(struct ra8875_state *ra8875, uint8_t cycle)
{
	return ra8875_set_register(ra8875, RA8875_REG_P1DCR, cycle);
}

void ra8875_set_graphics_mode(struct ra8875_state *ra8875)
{
	uint8_t cur_value = 0;
	if (ra8875_read_register(ra8875, RA8875_REG_MWCR0, &cur_value) != RA8875_OK) return;
	ra8875_set_register(ra8875, RA8875_REG_MWCR0, cur_value & ~0x80);
}

void ra8875_draw_rectangle(struct ra8875_state *ra8875, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, bool outline)
{
	int16_t x2 = x + w - 1;
	int16_t y2 = y + h - 1;

	ra8875_set_register(ra8875, RA8875_REG_DLHSR0, (x & 0xFF));
	ra8875_set_register(ra8875, RA8875_REG_DLHSR1, (x >> 8) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_DLVSR0, (y & 0xFF));
	ra8875_set_register(ra8875, RA8875_REG_DLVSR1, (y >> 8) & 0xFF);

	ra8875_set_register(ra8875, RA8875_REG_DLHER0, (x2 & 0xFF));
	ra8875_set_register(ra8875, RA8875_REG_DLHER1, (x2 >> 8) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_DLVER0, (y2 & 0xFF));
	ra8875_set_register(ra8875, RA8875_REG_DLVER1, (y2 >> 8) & 0xFF);

	ra8875_set_register(ra8875, RA8875_REG_FGCR0, ((color & 0xf800) >> 11) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_FGCR1, ((color & 0x07e0) >> 5) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_FGCR2, ((color & 0x001f) & 0xff));

	ra8875_set_register(ra8875, RA8875_REG_DCR, outline ? 0x90 : 0xB0);

	ra8875_wait_for_register_flag(ra8875, RA8875_REG_DCR, 0x80);
}

void ra8875_draw_line(struct ra8875_state *ra8875, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	ra8875_set_register(ra8875, RA8875_REG_DLHSR0, (x1 & 0xFF));
	ra8875_set_register(ra8875, RA8875_REG_DLHSR1, (x1 >> 8) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_DLVSR0, (y1 & 0xFF));
	ra8875_set_register(ra8875, RA8875_REG_DLVSR1, (y1 >> 8) & 0xFF);

	ra8875_set_register(ra8875, RA8875_REG_DLHER0, (x2 & 0xFF));
	ra8875_set_register(ra8875, RA8875_REG_DLHER1, (x2 >> 8) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_DLVER0, (y2 & 0xFF));
	ra8875_set_register(ra8875, RA8875_REG_DLVER1, (y2 >> 8) & 0xFF);

	ra8875_set_register(ra8875, RA8875_REG_FGCR0, ((color & 0xf800) >> 11) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_FGCR1, ((color & 0x07e0) >> 5) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_FGCR2, ((color & 0x001f) & 0xff));


	ra8875_set_register(ra8875, RA8875_REG_DCR, 0x80);

	ra8875_wait_for_register_flag(ra8875, RA8875_REG_DCR, 0x80);
}

void ra8875_debug_draw(struct ra8875_state *ra8875, uint16_t x, uint16_t y, const char* buffer)
{
	ra8875_set_text_mode(ra8875);
	ra8875_set_text_cursor(ra8875, x, y);
	ra8875_set_text_color(ra8875, 0xFFFF, 0x0000);
	ra8875_text_write(ra8875, buffer);
}

void ra8875_set_text_mode(struct ra8875_state *ra8875)
{
	uint8_t cur_value = 0;
	if (ra8875_read_register(ra8875, RA8875_REG_MWCR0, &cur_value) != RA8875_OK) return;

	ra8875_set_register(ra8875, RA8875_REG_MWCR0, cur_value | 0x80);

	if (ra8875_read_register(ra8875, RA8875_REG_FNCR0, &cur_value) != RA8875_OK) return;
	ra8875_set_register(ra8875, RA8875_REG_FNCR0, cur_value & ~(0x80 | 0x10));
}

void ra8875_set_text_cursor(struct ra8875_state *ra8875, uint16_t x, uint16_t y)
{
	ra8875_set_register(ra8875, RA8875_REG_F_CURXL, x & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_F_CURXH, (x >> 8) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_F_CURYL, y & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_F_CURYH, (y >> 8) & 0xFF);
}

void ra8875_set_text_color(struct ra8875_state *ra8875, uint16_t foreground, uint16_t background)
{
	ra8875_set_register(ra8875, RA8875_REG_FGCR0, ((foreground & 0xf800) >> 11) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_FGCR1, ((foreground & 0x07e0) >> 5) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_FGCR2, ((foreground & 0x001f) & 0xff));

	ra8875_set_register(ra8875, RA8875_REG_BGCR0, ((background & 0xf800) >> 11) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_BGCR1, ((background & 0x07e0) >> 5) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_BGCR2, ((background & 0x001f) & 0xff));

	uint8_t cur_value = 0;
	if (ra8875_read_register(ra8875, RA8875_REG_FNCR1, &cur_value) != RA8875_OK) return;
	ra8875_set_register(ra8875, RA8875_REG_FNCR1, cur_value & ~0x40);
}

void ra8875_set_text_transparent(struct ra8875_state *ra8875, uint16_t foreground)
{
	ra8875_set_register(ra8875, RA8875_REG_FGCR0, ((foreground & 0xf800) >> 11) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_FGCR1, ((foreground & 0x07e0) >> 5) & 0xFF);
	ra8875_set_register(ra8875, RA8875_REG_FGCR2, ((foreground & 0x001f) & 0xff));

	uint8_t cur_value = 0;
	if (ra8875_read_register(ra8875, RA8875_REG_FNCR1, &cur_value) != RA8875_OK) return;
	ra8875_set_register(ra8875, RA8875_REG_FNCR1, cur_value | 0x40);
}

void ra8875_set_text_enlarge(struct ra8875_state *ra8875, uint8_t scale)
{
	if (scale > 3) scale = 3;
	uint8_t cur_value = 0;
	if (ra8875_read_register(ra8875, RA8875_REG_FNCR1, &cur_value) != RA8875_OK) return;
	ra8875_set_register(ra8875, RA8875_REG_FNCR1, (cur_value & ~0x0F) | (scale << 2) | (scale));
}

void ra8875_text_write(struct ra8875_state *ra8875, const char* buffer)
{
	size_t len = strlen(buffer);
	ra8875_cmd_write(ra8875, RA8875_REG_MRWC);
	for (size_t i = 0; i < len; i++) {
		ra8875_data_write(ra8875, buffer[i]);
	}
}

void ra8875_enable_touch(struct ra8875_state *ra8875)
{
	ra8875_set_register(ra8875, RA8875_REG_TPCR0, 0x80 | 0x30 | 0x08 | 0x04);
	ra8875_set_register(ra8875, RA8875_REG_TPCR1, 0x04);
	uint8_t interrupt_cur;
	ra8875_read_register(ra8875, RA8875_REG_INTC1, &interrupt_cur);
	ra8875_set_register(ra8875, RA8875_REG_INTC1, interrupt_cur | 0x04);

}

void ra8875_disable_touch(struct ra8875_state *ra8875)
{
	ra8875_set_register(ra8875, RA8875_REG_TPCR0, 0x00);
	uint8_t interrupt_cur;
	ra8875_read_register(ra8875, RA8875_REG_INTC1, &interrupt_cur);
	ra8875_set_register(ra8875, RA8875_REG_INTC1, interrupt_cur & ~0x04);
}

bool ra8875_read_touch(struct ra8875_state *ra8875, uint16_t *x, uint16_t *y)
{
	uint8_t touched;
	if (ra8875_read_register(ra8875, RA8875_REG_INTC2, &touched) != RA8875_OK) return false;
	if (touched & 0x04) {
		uint8_t temp_x, temp_y, temp_xy;
		if (ra8875_read_register(ra8875, RA8875_REG_TPXH, &temp_x) != RA8875_OK) return false;
		if (ra8875_read_register(ra8875, RA8875_REG_TPYH, &temp_y) != RA8875_OK) return false;
		if (ra8875_read_register(ra8875, RA8875_REG_TPXYL, &temp_xy) != RA8875_OK) return false;
		*x = (temp_x << 2) | (temp_xy & 0x03);
		*y = (temp_y << 2) | ((temp_xy >> 2) & 0x03);
	}
	return false;
}

ra8875_result ra8875_init_lcd(struct ra8875_state *state)
{
	ra8875_result rv = RA8875_OK;

	//check_result(ra8875_set_register(state, RA8875_REG_SYSR, 0x00)); // 256 colors
	check_result(ra8875_set_register(state, RA8875_REG_SYSR, 0x0C)); // 65k colors

	// PDAT is fetched at PCLK falling edge
	// PCLK period = 2 times of System Clock period.
	check_result(ra8875_set_register(state, RA8875_REG_PCSR, 0x81));
	HAL_Delay(1);

	check_result(ra8875_set_register(state, RA8875_REG_HDWR, 0x63));

	//Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)
	//Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]
	check_result(ra8875_set_register(state, RA8875_REG_HNDFTR, 0x00));
	//HNDR//Horizontal Non-Display Period Bit[4:0]
	//Horizontal Non-Display Period (pixels) = (HNDR + 1)*8
	check_result(ra8875_set_register(state, RA8875_REG_HNDR, 0x03));
	//HSTR//HSYNC Start Position[4:0]
	//HSYNC Start Position(PCLK) = (HSTR + 1)*8
	check_result(ra8875_set_register(state, RA8875_REG_HSTR, 0x03));
	//HPWR//HSYNC Polarity ,The period width of HSYNC.
	//HSYNC Width [4:0] HSYNC Pulse width(PCLK) = (HPWR + 1)*8
	check_result(ra8875_set_register(state, RA8875_REG_HPWR, 0x0B));

	//Vertical set
	//VDHR0 //Vertical Display Height Bit [7:0]
	//Vertical pixels = VDHR + 1
	check_result(ra8875_set_register(state, RA8875_REG_VDHR0, 0xdf));
	//VDHR1 //Vertical Display Height Bit [8]
	//Vertical pixels = VDHR + 1
	check_result(ra8875_set_register(state, RA8875_REG_VDHR1, 0x01));
	//VNDR0 //Vertical Non-Display Period Bit [7:0]
	//Vertical Non-Display area = (VNDR + 1)
	check_result(ra8875_set_register(state, RA8875_REG_VNDR0, 0x1F));
	//VNDR1 //Vertical Non-Display Period Bit [8]
	//Vertical Non-Display area = (VNDR + 1)
	check_result(ra8875_set_register(state, RA8875_REG_VNDR1, 0x00));
	//VSTR0 //VSYNC Start Position[7:0]
	//VSYNC Start Position(PCLK) = (VSTR + 1)
	check_result(ra8875_set_register(state, RA8875_REG_VSTR0, 0x16));
	//VSTR1 //VSYNC Start Position[8]
	//VSYNC Start Position(PCLK) = (VSTR + 1)
	check_result(ra8875_set_register(state, RA8875_REG_VSTR1, 0x00));
	//VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0]
	//VSYNC Pulse Width(PCLK) = (VPWR + 1)
	check_result(ra8875_set_register(state, RA8875_REG_VPWR, 0x01));

	//Active window set
	//setting active window X
	//Horizontal Start Point 0 of Active Window (HSAW0)
	//Horizontal Start Point of Active Window [7:0]
	check_result(ra8875_set_register(state, RA8875_REG_HSAW0, 0x00));
	//Horizontal Start Point 1 of Active Window (HSAW1)
	//Horizontal Start Point of Active Window [9:8]
	check_result(ra8875_set_register(state, RA8875_REG_HSAW1, 0x00));
	//Horizontal End Point 0 of Active Window (HEAW0)
	//Horizontal End Point of Active Window [7:0]
	check_result(ra8875_set_register(state, RA8875_REG_HEAW0, 0x1F));
	//Horizontal End Point 1 of Active Window (HEAW1)
	//Horizontal End Point of Active Window [9:8]
	check_result(ra8875_set_register(state, RA8875_REG_HEAW1, 0x03));

	//setting active window Y
	//Vertical Start Point 0 of Active Window (VSAW0)
	//Vertical Start Point of Active Window [7:0]
	check_result(ra8875_set_register(state, RA8875_REG_VSAW0, 0x00));
	//Vertical Start Point 1 of Active Window (VSAW1)
	//Vertical Start Point of Active Window [8]
	check_result(ra8875_set_register(state, RA8875_REG_VSAW1, 0x00));
	//Vertical End Point of Active Window 0 (VEAW0)
	//Vertical End Point of Active Window [7:0]
	check_result(ra8875_set_register(state, RA8875_REG_VEAW0, 0xdf));
	//Vertical End Point of Active Window 1 (VEAW1)
	//Vertical End Point of Active Window [8]
	check_result(ra8875_set_register(state, RA8875_REG_VEAW1, 0x01));

	//Clear screen
	check_result(ra8875_set_register(state, RA8875_REG_MCLR, 0x80));

	HAL_Delay(500);

exit_function:
	return rv;
}

ra8875_result ra8875_init_pll(struct ra8875_state *state)
{
	ra8875_result rv = RA8875_OK;

	check_result(ra8875_set_register(state, RA8875_REG_PLLC1, 0x0b));
	HAL_Delay(1);
	check_result(ra8875_set_register(state, RA8875_REG_PLLC2, 0x02));
	HAL_Delay(1);
exit_function:
	return rv;
}

ra8875_result ra8875_reset(struct ra8875_state *state)
{
    state->RST_PORT->BSRR = (uint32_t)state->RST_PIN << 16;
    HAL_Delay(100);
	state->RST_PORT->BSRR = state->RST_PIN;
	HAL_Delay(100);
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
	state->CS_PORT->BSRR = state->CS_PIN << 16;
	uint8_t full_command[2] = {0x80, command};
	HAL_SPI_Transmit(state->spi_port, full_command, 2, 500);
	while (HAL_SPI_GetState(state->spi_port) != HAL_SPI_STATE_READY);
	state->CS_PORT->BSRR = state->CS_PIN;
	//HAL_Delay(1);
	return RA8875_OK;
}

ra8875_result ra8875_data_write(struct ra8875_state *state, uint8_t data)
{
	state->CS_PORT->BSRR = state->CS_PIN << 16;
	uint8_t full_data[2] = {0x00, data};
	HAL_SPI_Transmit(state->spi_port, full_data, 2, 500);
	while (HAL_SPI_GetState(state->spi_port) != HAL_SPI_STATE_READY);
	state->CS_PORT->BSRR = state->CS_PIN;
	//HAL_Delay(1);
	return RA8875_OK;
}


ra8875_result ra8875_read_register(struct ra8875_state *state, uint8_t reg, uint8_t *value)
{
	ra8875_cmd_write(state, reg);
	state->CS_PORT->BSRR = state->CS_PIN << 16;
	uint8_t read_reg = 0x40;
	HAL_SPI_Transmit(state->spi_port, &read_reg, 1, 500);
	while (HAL_SPI_GetState(state->spi_port) != HAL_SPI_STATE_READY);
	read_reg = 0x00;
	ra8875_result res = (HAL_OK == HAL_SPI_TransmitReceive(state->spi_port, &read_reg, value, 1, 500)) ? RA8875_OK : RA8875_SPI_ERROR;
	while (HAL_SPI_GetState(state->spi_port) != HAL_SPI_STATE_READY);
	state->CS_PORT->BSRR = state->CS_PIN;
	//HAL_Delay(1);
	return res;
}

void ra8875_wait_for_register_flag(struct ra8875_state *state, uint8_t reg, uint8_t flag)
{
	uint8_t temp = 0;
	while (1) {
		ra8875_read_register(state, reg, &temp);
		if (!(temp & flag))
			return;
	}
}
