// Note #1: running at 480MHz, there are exactly 480 cycles in 1us
// Note #2: according to ARM specs, NOP may be optimized out to 0 cycles. so we use MOV instead

void sleep_us_cm7(int numMicroSeconds)
{
	asm("WAIT_1_US:\n\t"
		"MOV     R0, R0\n\t"     // clock cycle 1
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 10
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 20
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 30
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 40
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 50
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 60
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 70
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 80
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 90
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 100
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 110
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 120
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 130
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 140
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 150
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 160
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 170
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 180
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 190
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 200
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 210
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 220
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 230
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 240
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 250
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 260
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 270
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 280
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 290
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 300
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 310
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 320
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 330
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 340
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 350
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 360
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 370
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 380
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 390
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 400
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 410
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 420
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 430
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 440
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 450
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 460
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 470
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"
		"MOV     R0, R0\n\t"      // clock cycle 478
		"SUBS    %[value], %[value], #1\n\t"      // clock cycle 479
		"BGT     WAIT_1_US\n\t"       // clock cycle 480
		"BX      LR"
		 : [value] "+r" (numMicroSeconds));      // return
}
