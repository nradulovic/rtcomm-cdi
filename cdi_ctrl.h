/*
 * cdi_ctrl.h
 *
 *  Created on: May 30, 2017
 *      Author: nenad
 */

#ifndef APPLICATION_INCLUDE_CDI_CDI_CTRL_H_
#define APPLICATION_INCLUDE_CDI_CDI_CTRL_H_

#include <stdint.h>
#include <stdbool.h>

#define CTRL_HEADER_MAGIC				0xdeadbeee

struct __attribute__((packed)) ctrl_header
{
    uint32_t					data_size;
    uint32_t					magic;
    uint32_t					crc;
};

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
    if (hdr->magic != RTCOMM_HEADER_MAGIC) {
        return (false);
    }

    if (hdr->crc != 0) {
        return (false);
    }
    *data_size = hdr->data_size;

    return (true);
}

#endif /* APPLICATION_INCLUDE_CDI_CDI_CTRL_H_ */
