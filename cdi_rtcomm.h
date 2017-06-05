/*
 *  teslameter_3mhx-fw - 2017
 *
 *  cdi_rtcomm.h
 *
 *  Created on: Feb 9, 2017
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
 * @brief       Cross-Domain-Interface (CDI) Real-Time communication
 *********************************************************************//** @{ */

#ifndef APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_
#define APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_

/*=========================================================  INCLUDE FILES  ==*/

#include <stdint.h>
#include <stdbool.h>

/*===============================================================  MACRO's  ==*/

#define RTCOMM_HEADER_MAGIC				0xdeadbeef
#define RTCOMM_FOOTER_MAGIC				0xdeadbeed

/*------------------------------------------------------  C++ extern begin  --*/
#ifdef __cplusplus
extern "C" {
#endif
/*============================================================  DATA TYPES  ==*/

/*
 * To each RTCOMM buffer the structure rtcomm_header is prepended to the data.
 */
struct __attribute__((packed)) rtcomm_header
{
    uint32_t					data_size;
    uint32_t					frame;
    uint32_t					magic;
    uint32_t					crc;
};

struct __attribute__((packed)) rtcomm_footer
{
	uint32_t					magic;
	uint32_t					crc;
};

/*======================================================  GLOBAL VARIABLES  ==*/
/*===================================================  FUNCTION PROTOTYPES  ==*/

static inline
void rtcomm_header_init(struct rtcomm_header * hdr)
{
    hdr->data_size = 0;
}

static inline
void rtcomm_footer_pack(struct rtcomm_footer * ftr,
		const struct rtcomm_header * hdr)
{
	ftr->magic = RTCOMM_FOOTER_MAGIC;
	ftr->crc = ~hdr->crc;
}

static inline
void rtcomm_header_pack(struct rtcomm_header * hdr, uint32_t data_size,
        uint32_t frame)
{
    hdr->data_size = data_size;
    hdr->frame = frame;
    hdr->magic = RTCOMM_HEADER_MAGIC;
    hdr->crc = 0;
}

static inline
bool rtcomm_header_unpack(struct rtcomm_header * hdr, uint32_t * data_size,
		uint32_t * frame)
{
    if (hdr->magic != RTCOMM_HEADER_MAGIC) {
        return (false);
    }

    if (hdr->crc != 0) {
        return (false);
    }
    *data_size = hdr->data_size;
    *frame = hdr->frame;

    return (true);
}

static inline
bool rtcomm_footer_unpack(struct rtcomm_footer * ftr,
		const struct rtcomm_header * hdr)
{
	if (ftr->magic != RTCOMM_FOOTER_MAGIC) {
		return (false);
	}

	if (hdr->crc != ~ftr->crc) {
		return (false);
	}

	return (true);
}

/*--------------------------------------------------------  C++ extern end  --*/
#ifdef __cplusplus
}
#endif

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//** @} *//*********************************************
 * END of cdi_rtcomm.h
 ******************************************************************************/
#endif /* APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_ */
