/*
 *  teslameter_3mhx-fw - 2017
 *
 *  cdi_ctrl.h
 *
 *  Created on: May 30, 2017
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
 * @brief       Cross-Domain-Interface (CDI) control
 *********************************************************************//** @{ */

#ifndef APPLICATION_INCLUDE_CDI_CDI_CTRL_H_
#define APPLICATION_INCLUDE_CDI_CDI_CTRL_H_

/*=========================================================  INCLUDE FILES  ==*/

#include <stdbool.h>
#include <stdint.h>

/*===============================================================  MACRO's  ==*/

#define CTRL_HEADER_MAGIC               0xdeadbeee

/*------------------------------------------------------  C++ extern begin  --*/
#ifdef __cplusplus
extern "C" {
#endif
/*============================================================  DATA TYPES  ==*/

struct __attribute__((packed)) ctrl_header
{
    uint32_t                    data_size;
    uint32_t                    magic;
    uint32_t                    crc;
};

/*======================================================  GLOBAL VARIABLES  ==*/
/*===================================================  FUNCTION PROTOTYPES  ==*/

static inline
void ctrl_header_init(struct ctrl_header * hdr)
{
    hdr->data_size = 0;
}

static inline
void ctrl_header_pack(struct ctrl_header * hdr, uint32_t data_size)
{
    hdr->data_size = data_size;
    hdr->magic = CTRL_HEADER_MAGIC;
    hdr->crc = 0;
}

static inline
bool ctrl_header_unpack(struct ctrl_header * hdr, uint32_t * data_size)
{
    if (hdr->magic != CTRL_HEADER_MAGIC) {
        return (false);
    }

    if (hdr->crc != 0) {
        return (false);
    }
    *data_size = hdr->data_size;

    return (true);
}

/*--------------------------------------------------------  C++ extern end  --*/
#ifdef __cplusplus
}
#endif

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//** @} *//*********************************************
 * END of cdi_ctrl.h
 ******************************************************************************/
#endif /* APPLICATION_INCLUDE_CDI_CDI_CTRL_H_ */
