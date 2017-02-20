/**
 * @file
 * openflow.h
 *
 * This file contains the function declarations and structures for the OpenFlow functions
 *
 */

/*
 * This file is part of the Zodiac FX firmware.
 * Copyright (c) 2016 Northbound Networks.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Paul Zanna <paul@northboundnetworks.com>
 *
 */

#ifndef OPENFLOW_H_
#define OPENFLOW_H_

#include "openflow_spec/openflow_spec10.h"
#include "openflow_spec/openflow_spec13.h"
#include "of_helper.h"
#include <lwip/err.h>

struct flows_counter
{
	uint16_t hitCount;
	int bytes;
	int duration;
	uint8_t active;
	int lastmatch;
};

struct table_counter
{
	int lookup_count;
	int matched_count;
	int byte_count;
};

struct flow_tbl_actions
{
	uint8_t action1[16];
	uint8_t action2[16];
	uint8_t action3[16];
	uint8_t action4[16];
};

struct oxm_header13
{
	uint16_t oxm_class;
	uint8_t oxm_field;
	uint8_t oxm_len;
};

/*
*	OpenFlow meter entry structure
*		Meter table is populated with these entries.
*		The structure contains:
*			- meter ID
*			- counters
*			- meter bands
*/
struct meter_entry13
{
	uint32_t	meter_id;
	uint32_t	flow_count;			// Number of flows bound to meter
	uint64_t	packet_in_count;	// Packets processed by meter
	uint64_t	byte_in_count;		// Bytes processed by meter
	uint32_t	duration_sec;		// Time meter has been alive in seconds
	uint16_t	flags;				// Meter configuration flags
	uint16_t	band_count;			// Number of bands in this meter
	uint64_t	last_packet_in;		// Time when meter last processed a packet (milliseconds)
	struct ofp13_meter_band_drop bands[0];	// Meter bands
};

void task_openflow(void);
void nnOF_tablelookup(uint8_t *p_uc_data, uint32_t *ul_size, int port);
void nnOF10_tablelookup(uint8_t *p_uc_data, uint32_t *ul_size, int port);
void nnOF13_tablelookup(uint8_t *p_uc_data, uint32_t *ul_size, int port);
void of10_message(struct ofp_header *ofph, int size, int len);
void of13_message(struct ofp_header *ofph, int size, int len);
void multi_flow_more_reply13(void);
void barrier10_reply(uint32_t xid);
void barrier13_reply(uint32_t xid);
void sendtcp(const void *buffer, u16_t len);
void flowrem_notif10(int flowid, uint8_t reason);
void flowrem_notif13(int flowid, uint8_t reason);
void port_status_message10(uint8_t port);
void port_status_message13(uint8_t port);

#define HTONS(x) ((((x) & 0xff) << 8) | (((x) & 0xff00) >> 8))
#define NTOHS(x) HTONS(x)
#define HTONL(x) ((((x) & 0xff) << 24) | \
(((x) & 0xff00) << 8) | \
(((x) & 0xff0000UL) >> 8) | \
(((x) & 0xff000000UL) >> 24))
#define NTOHL(x) HTONL(x)

#define SHARED_BUFFER_LEN 2048

#define	METER_PARTIAL	8		// Meter structure length, excluding header and bands

#define SUCCESS		0
#define FAILURE		1

#endif /* OPENFLOW_H_ */
