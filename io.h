/*
 *  teslameter_3mhx-fw - 2017
 *
 *  io.h (former acqunity_commands.h)
 *
 *  Created on: Jan 19, 2015
 * ----------------------------------------------------------------------------
 *  This file is part of teslameter_3mhx-fw.
 *
 *  teslameter_3mhx-fw is free software: you can redistribute it and/or modify
 *  it under the terms of the Lesser GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  teslameter_3mhx-fw is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with teslameter_3mhx-fw.  If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------- *//**
 * @file
 * @author      Nenad Radulovic
 * @brief       Main file header
 *********************************************************************//** @{ */

#ifndef CDI_IO_H_
#define CDI_IO_H_

/*=========================================================  INCLUDE FILES  ==*/

#include <stdint.h>

#include "cdi_rtcomm.h"
#include "cdi_ctrl.h"

/*===============================================================  MACRO's  ==*/

#define IO_ID							0x26
#define IO_BUFF_SIZE              		3000
#define IO_AUX_CHANNELS           		2
#define IO_PROBE_CHANNELS           	3

#define IO_CHANNEL_X              		0
#define IO_CHANNEL_Y              		1
#define IO_CHANNEL_Z              		2

/* IO_WORKMODE_NORMAL
 * Trigger signal is output on a pin
 * There are two available modes depending on the sample rate speed:
 *  - if sample speed is low (less than 15kSPS) then trigger rising edge is
 *  	generated just at the beginning of the sample read. After calculated
 *  	time a falling edge is generated through a hardware timer.
 *  - if sample speed is high (15-30 kSPS) then the rising edge is generated at
 *  	start of reading and the falling edge is generated at end of reading of
 *  	all bytes from ADCs.
 *
 * IO_WORKMODE_TRIG_CONTINUOUS
 * This trigger means that after each trigger a sample is taken.
 *
 * IO_WORKMODE_TRIG_SINGLE_SHOT
 * This trigger triggers only once and then it will continue on its own.
 */
#define IO_WORKMODE_NORMAL				0
#define IO_WORKMODE_TRIG_CONTINUOUS		1
#define IO_WORKMODE_TRIG_SINGLE_SHOT	2

#define IO_EN_AUTORANGE_DISABLED		0
#define IO_EN_AUTORANGE_ENABLED			1

/*------------------------------------------------------  C++ extern begin  --*/
#ifdef __cplusplus
extern "C" {
#endif
/*============================================================  DATA TYPES  ==*/

struct __attribute__((packed)) io_ctrl_config
{
	struct __attribute__((packed)) ctrl_header
								header;
	uint8_t						en_x;
	uint8_t						en_y;
	uint8_t						en_z;
	uint8_t						en_aux1;
	uint8_t						en_aux2;
	uint8_t						en_probe_buffer;
	uint8_t						en_aux_buffer;
	uint8_t						probe_pga;
	uint8_t						aux1_mux_hi;
	uint8_t						aux1_mux_lo;
	uint8_t						aux2_mux_hi;
	uint8_t						aux2_mux_lo;
	uint8_t						tcgain;
	uint8_t						tgain1hi;
	uint8_t						vgain1hi;
	uint8_t						tgain2hi;
	uint8_t						tgain2lo;
	uint8_t						vgain2hi;
	uint8_t						vgain2lo;
	uint8_t						tgain3hi;
	uint8_t						tgain3lo;
	uint8_t						vgain3hi;
	uint8_t						vgain3lo;
	uint8_t						tgain4lo;
	uint8_t						vgain4lo;
	uint8_t						probe_mux_hi;
	uint8_t						probe_mux_lo;
};

struct __attribute__((packed)) ctrl_param_data
{
    uint8_t						en_autorange;
    uint8_t						vspeed;
    uint8_t						workmode;
    uint8_t						probe_gain;
};

struct __attribute__((packed)) io_ctrl_param
{
	struct __attribute__((packed)) ctrl_header
								header;
	struct __attribute__((packed)) ctrl_param_data
	                            data;
};

struct __attribute__((packed)) io_buffer
{
    struct __attribute__((packed)) rtcomm_header
    							header;
    struct __attribute__((packed)) ctrl_param_data
    							param;
    struct __attribute__((packed)) io_stats_info
	{
    	uint32_t					total_errors;
    	uint32_t					runtime_check_failed;
    	uint32_t					ctrl_comm_err;
    	uint32_t					ctrl_data_err;
    	uint32_t					ads_err;
    	uint32_t					no_resource_err;
    	uint32_t					rtcomm_skipped_err;
    	uint32_t					rtcomm_transfer_err;
    	uint32_t					rtcomm_complete_err;
	}							stats;
    int32_t           			sample[IO_BUFF_SIZE][IO_PROBE_CHANNELS];
    uint8_t						gain[IO_BUFF_SIZE][IO_PROBE_CHANNELS];
    int32_t                     aux[IO_AUX_CHANNELS];
    struct __attribute__((packed)) rtcomm_footer
    							footer;
};

/*======================================================  GLOBAL VARIABLES  ==*/
/*===================================================  FUNCTION PROTOTYPES  ==*/
/*--------------------------------------------------------  C++ extern end  --*/
#ifdef __cplusplus
}
#endif

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/

/* NOTE:
 * This declaration is not used anywhere in the code. It is only here to force
 * the compiler to check if io_buffer size is divisible by 4. This requirement
 * exists because we are sending the buffer using hardware DMA which may have
 * limitations regarding data addressing.
 *
 * If the following line of code fails to compile, then the io_buffer has wrong
 * number of bytes.
 */
extern int _assert_buffer_size[(sizeof(struct __attribute__((packed)) io_buffer) & 0x3) ? -1 : 1];

/** @endcond *//** @} *//** @} *//*********************************************
 * END of io.h
 ******************************************************************************/
#endif /* CDI_IO_H_ */
