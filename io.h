/*
 * acqunity_commands.h
 *
 *  Created on: Jan 19, 2015
 *      Author: nenad
 */

#ifndef CDI_IO_H_
#define CDI_IO_H_

#include <stdint.h>

#include "cdi_rtcomm.h"

#define IO_ID							0x26
#define IO_BUFF_SIZE              		3000
#define IO_AUX_CHANNELS           		2
#define IO_PROBE_CHANNELS           	3

#define IO_ADC_SIGNED_MAX				8388607
#define IO_ADC_SIGNED_MIN				-8388608
#define IO_ADC_UNSIGNED_MAX				16777215u
#define IO_ADC_UNSIGNED_MIN				0u
#define IO_ADC_FS                       (IO_ADC_UNSIGNED_MAX + 1u)

#define IO_CHANNEL_X              		0
#define IO_CHANNEL_Y              		1
#define IO_CHANNEL_Z              		2

#define IO_CHANNEL_X_MASK               (0x1u << 0)
#define IO_CHANNEL_Y_MASK               (0x1u << 1)
#define IO_CHANNEL_Z_MASK               (0x1u << 2)
#define IO_CHANNEL_XYZ_MASK				\
	(IO_CHANNEL_X_MASK | IO_CHANNEL_Y_MASK | IO_CHANNEL_Z_MASK)

/* IO_TRIG_MODE_OUT
 * Trigger signal is output on a pin
 * There are two available modes depending on the sample rate speed:
 *  - if sample speed is low (less than 15kSPS) then trigger rising edge is
 *  	generated just at the beginning of the sample read. After calculated
 *  	time a falling edge is generated through a hardware timer.
 *  - if sample speed is high (15-30 kSPS) then the rising edge is generated at
 *  	start of reading and the falling edge is generated at end of reading of
 *  	all bytes from ADCs.
 *
 * IO_TRIG_MODE_IN_CONTINUOUS
 * This trigger means that after each trigger a sample is taken.
 *
 * IO_TRIG_MODE_IN_SINGLE_SHOT
 * This trigger triggers only once and then it will continue on its own.
 */
#define IO_TRIG_MODE_OUT          		0
#define IO_TRIG_MODE_IN_CONTINUOUS   	1
#define IO_TRIG_MODE_IN_SINGLE_SHOT    	2

/* IO_ADC_MODE_CONTINUOUS
 * ADC is sampling automatically at specified speed.
 *
 * IO_ADC_MODE_REQUEST
 * ADC is sampling only when requested by MCU.
 */
#define IO_ADC_MODE_CONTINUOUS			0
#define IO_ADC_MODE_REQUEST				1

struct __attribute__((packed)) io_buffer
{
    struct rtcomm_header        header;
    int32_t           			sample[IO_BUFF_SIZE][IO_PROBE_CHANNELS];
    uint8_t						gain[IO_BUFF_SIZE][IO_PROBE_CHANNELS];
    uint32_t                    aux[IO_AUX_CHANNELS];
};

#endif /* CDI_IO_H_ */
