/*
 * cdi_rtcomm.h
 *
 *  Created on: Feb 9, 2017
 *      Author: nenad
 */

#ifndef APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_
#define APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_

#include <stdint.h>

#define RTCOMM_HEADER_MAGIC				0xdeadbeef

struct __attribute__((packed)) rtcomm_stats
{
	uint32_t                    complete_err;
	uint32_t                    transfer_err;
	uint32_t                    skipped_err;
};

/*
 * To each RTCOMM buffer the structure rtcomm_header is prepended to the data.
 */
struct __attribute__((packed)) rtcomm_header
{
    uint32_t					data_size;
    uint32_t					frame;
    uint32_t					magic;
    uint32_t					crc;
    struct rtcomm_stats			stats;
};

static inline
void rtcomm_header_init(struct rtcomm_header * hdr)
{
    hdr->data_size = 0;
}

static inline
void rtcomm_header_pack(struct rtcomm_header * hdr, uint32_t data_size,
        uint32_t frame, const struct rtcomm_stats * stats)
{
    hdr->data_size = data_size;
    hdr->frame = frame;
    hdr->magic = RTCOMM_HEADER_MAGIC;
    hdr->crc = 0;
    hdr->stats = *stats;
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

#endif /* APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_ */
