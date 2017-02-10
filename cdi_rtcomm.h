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

#define RTCOMM_HEADER_SIZE				sizeof(struct rtcomm_header)

/*
 * To each RTCOMM buffer the structure rtcomm_header is prepended to the data.
 *
 * The size of rtcomm_header is always 128 bytes
 */
struct rtcomm_header
{
	union rtcomm_header_extender
	{
		struct rtcomm_header_data __attribute__((packed))
		{
			uint32_t					magic;
			uint32_t					frame;
			uint32_t					data_size;
			uint32_t					data_crc;
			uint32_t					timestamp_s;
			uint32_t					timestamp_ms;
		}							header;
		uint8_t						_padding[128];
	}							u;
	uint8_t						data[];
};

#endif /* APPLICATION_INCLUDE_CDI_CDI_RTCOMM_H_ */
