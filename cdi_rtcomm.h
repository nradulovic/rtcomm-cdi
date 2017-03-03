/*
 * cdi_rtcomm.h
 *
 *  Created on: Feb 9, 2017
 *      Author: nenad
 */

#ifndef APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_
#define APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define RTCOMM_HEADER_MAGIC				0xdeadbeef

struct __attribute__((packed)) rtcomm_stats
{
    uint32_t                    complete_err;
    uint32_t                    transfer_err;
    uint32_t                    skipped_err;
};

struct __attribute__((packed)) rtcomm_header_data
{
    uint32_t					data_size;
    uint32_t                    channels;
    uint32_t					frame;
    uint32_t					timestamp_s;
    uint32_t					timestamp_ms;
    uint32_t					magic;
    uint32_t					crc;
    struct rtcomm_stats         stats;
};

/*
 * Data channel
 *
 * Size: 20 bytes
 *
 * Attributes:
 * - elements: how many elements are in the array
 * - addr_mul: address multiplier, usually defined by the element size in bytes
 * - addr_offset: start of array
 * - bit_mul: bit multiplier, usually defined by how many bits are in the element
 * - bit_offset: first bit in element that holds the required data
 * - mask: number of bits in element
 * - content: defined what is the data type:
 *   - 0 - unsigned integer, size of integer depends on mask attribute
 *   - 1 - signed integer, size of integer depends on mask attribute
 *   - 2 - float number, as defined by Cortex-M MCU hardware
 *   - 3 - character, this will be interpreted as string
 */
struct __attribute__((packed)) rtcomm_channel_data
{
    uint16_t                    elements;
    uint16_t                    addr_offset;
    uint8_t                     addr_mul;
    uint8_t                     bit_offset;
    uint8_t                     bit_mul;
    uint8_t                     mask;
    uint8_t                     content;
    char                        name[11];
};

/*
 * To each RTCOMM buffer the structure rtcomm_header is prepended to the data.
 *
 * The size of rtcomm_header is always 2048 bytes
 */
struct __attribute__((packed)) rtcomm_header
{
	union rtcomm_header_extender
	{
		struct rtcomm_header_data   header;
		uint8_t						_h_padding[64];
	}							h;
    union rtcomm_channel_extender
    {
        struct rtcomm_channel_data  channel[99];
        uint8_t                     _c_padding[1984];
    }                           c;
};

uint32_t rtcomm_header_magic(void);

static inline
bool rtcomm_assert_header(void)
{
    struct rtcomm_header * hdr = NULL;

    if (sizeof(hdr->h.header) > sizeof(hdr->h._h_padding)) {
        return (false);
    }

    if (sizeof(hdr->c.channel) > sizeof(hdr->c._c_padding)) {
        return (false);
    }

    return (true);
}

static inline
void rtcomm_header_init(struct rtcomm_header * hdr)
{
    hdr->h.header.channels = 0;
    hdr->h.header.data_size = 0;
}

static inline
void rtcomm_header_pack(struct rtcomm_header * hdr, uint32_t data_size,
        uint32_t channels, uint32_t frame, uint32_t timestamp_s,
        uint32_t timestamp_ms, const struct rtcomm_stats * stats)
{
    hdr->h.header.data_size = data_size;
    hdr->h.header.channels = channels;
    hdr->h.header.frame = frame;
    hdr->h.header.timestamp_s = timestamp_s;
    hdr->h.header.timestamp_ms = timestamp_ms;
    hdr->h.header.magic = RTCOMM_HEADER_MAGIC;
    hdr->h.header.crc = 0;
    hdr->h.header.stats = *stats;
}

static inline
bool rtcomm_header_unpack(struct rtcomm_header * hdr, uint32_t * data_size, uint32_t * channels,
          uint32_t * frame, uint32_t * timestamp_s, uint32_t * timestamp_ms)
{
    if (hdr->h.header.magic != RTCOMM_HEADER_MAGIC) {
        return (false);
    }

    if (hdr->h.header.crc != 0) {
        return (false);
    }
    *data_size = hdr->h.header.data_size;
    *channels = hdr->h.header.channels;
    *frame = hdr->h.header.frame;
    *timestamp_s = hdr->h.header.timestamp_s;
    *timestamp_ms = hdr->h.header.timestamp_ms;

    return (true);
}

static inline
void rtcomm_header_define_channel(struct rtcomm_header * hdr,
          const struct rtcomm_channel_data * channel)
{
    uint32_t index = 0;

    while (channel->name[0] != 0) {
        memcpy(&hdr->c.channel[index], channel, sizeof(*channel));
        index++;
        channel++;
    }
}

static inline
void rtcomm_header_mod_elements(struct rtcomm_header * hdr, uint32_t index, uint32_t elements)
{
    hdr->c.channel[index].elements = (uint16_t)elements;
}

#endif /* APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_ */
