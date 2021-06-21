#define _LINUX_IN_H
#define _GNU_SOURCE
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/igmp.h>
#include <sys/types.h>
#include <linux/types.h>
#include <linux/mroute.h>

#define IGMP_V3_MEMBERSHIP_REPORT 0x22

#define INADDR_ALLIGMPV3_GROUP ((in_addr_t) 0xe0000016)

static inline unsigned short ip_data_len(const struct ip *ip)
{
    return ntohs(ip->ip_len) - (ip->ip_hl << 2);
}

static inline void ip_set_len(struct ip *ip, unsigned short len)
{
    ip->ip_len = htons(len);
}

/* following code is taken from FreeBSD netinet/igmp.h, which is licensed under
   the following license */

/*-
 * Copyright (c) 1988 Stephen Deering.
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Stephen Deering of Stanford University.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)igmp.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: releng/11.2/sys/netinet/igmp.h 331722 2018-03-29 02:50:57Z eadler $
 */

/*
 * IGMP v3 query format.
 */
struct igmpv3 {
    u_char          igmp_type;  /* version & type of IGMP message  */
    u_char          igmp_code;  /* subtype for routing msgs        */
    u_short         igmp_cksum; /* IP-style checksum               */
    struct in_addr  igmp_group; /* group address being reported    */
                                /*  (zero for queries)             */
    u_char          igmp_misc;  /* reserved/suppress/robustness    */
    u_char          igmp_qqi;   /* querier's query interval        */
    u_short         igmp_numsrc;    /* number of sources               */
    /*struct in_addr	igmp_sources[1];*/ /* source addresses */
};

#define IGMP_V3_QUERY_MINLEN    12

struct igmp_grouprec {
    u_char          ig_type;    /* record type */
    u_char          ig_datalen; /* length of auxiliary data */
    u_short         ig_numsrc;  /* number of sources */
    struct in_addr  ig_group;   /* group address being reported */
    /*struct in_addr  ig_sources[];*/ /* source addresses */
};

#define IGMP_GRPREC_HDRLEN  8

/*
 * IGMPv3 host membership report header.
 */
struct igmp_report {
    u_char          ir_type;    /* IGMP_v3_HOST_MEMBERSHIP_REPORT */
    u_char          ir_rsv1;    /* must be zero */
    u_short         ir_cksum;   /* checksum */
    u_short         ir_rsv2;    /* must be zero */
    u_short         ir_numgrps; /* number of group records */
    /*struct	igmp_grouprec   ir_groups[];*/ /* group records */
};

#define IGMP_V3_REPORT_MINLEN   8
#define IGMP_V3_REPORT_MAXRECS  65535

/*
 * IGMPv3 report modes.
 */
#define IGMP_DO_NOTHING             0   /* don't send a record */
#define IGMP_MODE_IS_INCLUDE        1   /* MODE_IN */
#define IGMP_MODE_IS_EXCLUDE        2   /* MODE_EX */
#define IGMP_CHANGE_TO_INCLUDE_MODE 3   /* TO_IN */
#define IGMP_CHANGE_TO_EXCLUDE_MODE 4   /* TO_EX */
#define IGMP_ALLOW_NEW_SOURCES      5   /* ALLOW_NEW */
#define IGMP_BLOCK_OLD_SOURCES      6   /* BLOCK_OLD */

/*
 * IGMPv3 query types.
 */
#define IGMP_V3_GENERAL_QUERY       1
#define IGMP_V3_GROUP_QUERY         2
#define IGMP_V3_GROUP_SOURCE_QUERY  3