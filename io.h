/*
 * acqunity_commands.h
 *
 *  Created on: Jan 19, 2015
 *      Author: nenad
 */

#ifndef APPLICATION_INCLUDE_ACQUNITY_COMMANDS_H_
#define APPLICATION_INCLUDE_ACQUNITY_COMMANDS_H_

#include <stdint.h>

#include "base/bitop.h"


/*
 *  MSB                         LSB
 * +---+---+---+---+---+---+---+---+
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * +---+---+---+---+---+---+---+---+
 *  |   |   |   |   |   |   |   |
 *  |   |   |   |   |   |   |   +---- CMD
 *  |   |   |   |   |   |   +-------- PAR 0
 *  |   |   |   |   |   +------------ PAR 1
 *  |   |   |   |   +---------------- PAR 2
 *  |   |   |   +-------------------- PAR 3
 *  |   |   +------------------------ PAR 4
 *  |   +---------------------------- PAR 5
 *  +-------------------------------- PAR 6
 */

#define ACQUNITY_ID						0x26
#define ACQUNITY_BUFF_SIZE              2048
#define ACQUNITY_AUX_CHANNELS           4
#define ACQUNITY_ACQ_CHANNELS           3

#define ACQ_ADC_SIGNED_MAX				8388607
#define ACQ_ADC_SIGNED_MIN				-8388608
#define ACQ_ADC_UNSIGNED_MAX			16777215u
#define ACQ_ADC_UNSIGNED_MIN			0u
#define ACQ_ADC_FS                      (ACQ_ADC_UNSIGNED_MAX + 1u)

#define ACQ_CHANNEL_X              		0
#define ACQ_CHANNEL_Y              		1
#define ACQ_CHANNEL_Z              		2

#define ADS_REG_STATUS                  0x00
#define ADS_REG_MUX                     0x01
#define ADS_REG_ADCON                   0x02
#define ADS_REG_DRATE                   0x03
#define ADS_REG_IO                      0x04
#define ADS_REG_OFC0                    0x05
#define ADS_REG_OFC1                    0x06
#define ADS_REG_OFC2                    0x07
#define ADS_REG_FSC0                    0x08
#define ADS_REG_FSC1                    0x09
#define ADS_REG_FSC2                    0x0a

#define ADS_STATUS_ORDER_LSB            (0x1u << 3)
#define ADS_STATUS_ACAL_ENABLED         (0x1u << 2)
#define ADS_STATUS_BUFEN_ENABLED        (0x1u << 1)

#define ADS_MUX(pos, neg)               ((uint8_t)((uint8_t)((pos & 0xfu) << 4u) | (uint8_t)(neg & 0xfu)))

#define ADS_ADCON_CLKOUT_FCLKIN         (0x1u << 5)
#define ADS_ADCON_CLKOUT_FCLKIN_DIV_2   (0x2u << 5)
#define ADS_ADCON_CLKOUT_FLCKIN_DIV_4   (0x3u << 5)
#define ADS_ADCON_SDCS_05UA             (0x1u << 3)
#define ADS_ADCON_SDCS_2UA              (0x2u << 3)
#define ADS_ADCON_SDCS_10UA             (0x3u << 3)
#define ADS_ADCON_PGA_2                 (0x1u << 0)
#define ADS_ADCON_PGA_4                 (0x2u << 0)
#define ADS_ADCON_PGA_8                 (0x3u << 0)
#define ADS_ADCON_PGA_16                (0x4u << 0)
#define ADS_ADCON_PGA_32                (0x5u << 0)
#define ADS_ADCON_PGA_64                (0x6u << 0)

#define ADS_DRATE_30KSPS                0xf0
#define ADS_DRATE_15KSPS                0xe0
#define ADS_DRATE_7500SPS               0xd0
#define ADS_DRATE_3750SPS               0xc0
#define ADS_DRATE_2000SPS               0xb0
#define ADS_DRATE_1000SPS               0xa1
#define ADS_DRATE_500SPS                0x92
#define ADS_DRATE_100SPS                0x82
#define ADS_DRATE_60SPS                 0x72
#define ADS_DRATE_50SPS                 0x63
#define ADS_DRATE_30SPS                 0x53
#define ADS_DRATE_25SPS                 0x43
#define ADS_DRATE_15SPS                 0x33
#define ADS_DRATE_10SPS                 0x23
#define ADS_DRATE_5SPS                  0x13
#define ADS_DRATE_2_5SPS                0x03

#define ADS_IO_DIR3                     0x80
#define ADS_IO_DIR2                     0x40
#define ADS_IO_DIR1                     0x20
#define ADS_IO_DIR0                     0x10

#define ADS_CMD_WAKEUP                  0x00
#define ADS_CMD_RDATA                   0x01
#define ADS_CMD_RDATAC                  0x03
#define ADS_CMD_SDATAC                  0x0f
#define ADS_CMD_RREG                    0x10
#define ADS_CMD_WREG                    0x50
#define ADS_CMD_SELFCAL                 0xf0
#define ADS_CMD_SELFOCAL                0xf1
#define ADS_CMD_SELFGCAL                0xf2
#define ADS_CMD_SYSOCAL                 0xf3
#define ADS_CMD_SYSGCAL                 0xf4
#define ADS_CMD_SYNC                    0xfc
#define ADS_CMD_STANDBY                 0xfd
#define ADS_CMD_RESET                   0xfe

#define ADS_CLOCK_SLAVE                 0x1u

#define ACQ_CHANNEL_X_MASK              (0x1u << 0)
#define ACQ_CHANNEL_Y_MASK              (0x1u << 1)
#define ACQ_CHANNEL_Z_MASK              (0x1u << 2)

/*--  ACQUNITY command: CMD_SET_SYSTEM_CFG  ----------------------------------*/

#define CMD_SET_SYSTEM_CFG				0x01
#define CMD_SET_SYSTEM_STOP             0x02
#define ACQ_CFG_SIZE_TO_ENUM(size)      ((size + 15u) / 16u)

/* Trigger signal is output on a pin
 * There are two available modes depending on the sample rate speed:
 *  - if sample speed is low (less than 15kSPS) then trigger rising edge is
 *  	generated just at the beginning of the sample read. After calculated
 *  	time a falling edge is generated through a hardware timer.
 *  - if sample speed is high (15-30 kSPS) then the rising edge is generated at
 *  	start of reading and the falling edge is generated at end of reading of
 *  	all bytes from ADCs.
 */
#define TRIG_MODE_OUT          			0

/* This trigger means that after each trigger a sample is taken.
 */
#define TRIG_MODE_IN_CONTINUOUS   		1

/* This trigger triggers only once and then it will continue on its own.
 */
#define TRIG_MODE_IN_SINGLE_SHOT      	2

#define ACQ_MODE_CONTINUOUS				0
#define ACQ_MODE_REQUEST				1


struct PORT_C_PACKED acqunity_in
{
    uint8_t                     acq_channel_mask;
    uint8_t                     acq_size;
    uint8_t                     acq_status;
    uint8_t                     acq_mux;
    uint8_t                     acq_adcon;
    uint8_t                     acq_drate;
    uint8_t                     acq_gpio_io;
    uint8_t                     acq_trig;
    uint8_t                     aux_channel_no;
    uint8_t                     aux_mux[4];
    uint8_t                     aux_gpio_io;
    int32_t                     range_hi[4];
    int32_t                     range_lo[4];
    uint32_t                    attack_time;
    uint32_t                    pullback_time;
};


enum process_data_mode  // nacin prikaza prikupljenih podataka
{
    SERVICE_DATA,
    USER_DATA,
};


struct PORT_C_PACKED acqunity_out
{
    uint32_t                    aux_val[4];
    uint8_t                     status[4];
};


struct PORT_C_PACKED acq_sample
{
	union acq_sample_data
	{
		int32_t					idata;
		float					fdata;
	}							_channel[3];
    uint32_t                    _metadata;
};


/*--  ACQUNITY command: CMD_GET_DEV_MEM  -------------------------------------*/
/*
 * No parameters
 */
#define CMD_GET_DEV_MEM                 0xf0

/*
 * METADATA
 *
 *  +---+---+--------------------------+
 *  | G | T |        TIMESTAMP         |
 *  +---+---+--------------------------+
 *   | | | | |                        |
 *   | | | | |                        +---- 0
 *   | | | | +----------------------------- 25
 *   | | | +------------------------------- 26
 *   | | +--------------------------------- 28
 *   | +----------------------------------- 29
 *   +------------------------------------- 31
 *
 *   G - gain [31:29] - 3 bits
 *   T - type [28:26] - 3 bits
 *    - SAMPLE_TYPE_INT
 *    - SAMPLE_TYPE_FLOAT
 *   TIMESTAMP - timestamp [25:0] - 26 bits
 */

#define SAMPLE_GAIN_Pos					(29u)
#define SAMPLE_GAIN_Mask				(0x7u << SAMPLE_GAIN_Pos)
#define SAMPLE_TYPE_Pos					(26)
#define SAMPLE_TYPE_Mask				(0x7u << SAMPLE_TYPE_Pos)
#define SAMPLE_TIMESTAMP_Pos			(0)
#define SAMPLE_TIMESTAMP_Mask			(0x3ffffffu << SAMPLE_TIMESTAMP_Pos)

#define SAMPLE_TYPE_INT					(0x0)
#define SAMPLE_TYPE_FLOAT				(0x1)

#define io_raw_adc_to_int(raw_data)		n_ext_i24((int32_t)(raw_data))



PORT_C_INLINE
void sample_init(struct acq_sample * sample, uint32_t raw_data, uint32_t channel)
{
	sample->_channel[channel].idata = io_raw_adc_to_int(raw_data);
}



PORT_C_INLINE
void sample_cpy_metadata(struct acq_sample * dst, const struct acq_sample * src)
{
	dst->_metadata = src->_metadata;
}



PORT_C_INLINE
void sample_set_int(struct acq_sample * sample, int32_t value, uint32_t channel)
{
	sample->_channel[channel].idata = value;
}



PORT_C_INLINE
int32_t sample_get_int(const struct acq_sample * sample, uint32_t channel)
{
	return (sample->_channel[channel].idata);
}



PORT_C_INLINE
void sample_set_float(struct acq_sample * sample, float value, uint32_t channel)
{
	sample->_channel[channel].fdata = value;
}



PORT_C_INLINE
float sample_get_float(const struct acq_sample * sample, uint32_t channel)
{
	return (sample->_channel[channel].fdata);
}



PORT_C_INLINE
void sample_set_gain(struct acq_sample * sample, uint32_t gain)
{
	gain <<= SAMPLE_GAIN_Pos;

	sample->_metadata &= ~SAMPLE_GAIN_Mask;
	sample->_metadata |= gain;
}



PORT_C_INLINE
uint32_t sample_get_gain(const struct acq_sample * sample)
{
	return (sample->_metadata >> SAMPLE_GAIN_Pos);
}



/**@brief		Set the sample type
 * @param 		sample - Pointer to acq_sample structure
 * @param 		type
 * 				- SAMPLE_TYPE_INT
 * 				- SAMPLE_TYPE_FLOAT
 */
PORT_C_INLINE
void sample_set_type(struct acq_sample * sample, uint32_t type)
{
	type <<= SAMPLE_TYPE_Pos;
	type &= SAMPLE_TYPE_Mask;

	sample->_metadata &= ~SAMPLE_TYPE_Mask;
	sample->_metadata |= type;
}



/**@brief		Get the sample type
 * @param 		sample - Pointer to acq_sample structure
 * @return
 *  @retval		SAMPLE_TYPE_INT
 *  @retval		SAMPLE_TYPE_FLOAT
 */
PORT_C_INLINE
uint32_t sample_get_type(const struct acq_sample * sample)
{
	return ((sample->_metadata & SAMPLE_TYPE_Mask) >> SAMPLE_TYPE_Pos);
}



PORT_C_INLINE
void sample_set_timestamp(struct acq_sample * sample, uint32_t timestamp)
{
	timestamp &= SAMPLE_TIMESTAMP_Mask;

	sample->_metadata &= ~SAMPLE_TIMESTAMP_Mask;
	sample->_metadata |= timestamp;
}



PORT_C_INLINE
uint32_t sample_get_timestamp(const struct acq_sample * sample)
{
	return (sample->_metadata & SAMPLE_TIMESTAMP_Mask);
}

#endif /* APPLICATION_INCLUDE_ACQUNITY_COMMANDS_H_ */
