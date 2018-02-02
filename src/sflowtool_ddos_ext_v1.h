/*
 * File name: sflowtool_ddos_ext_v1.h
 *
 * Copyright(C) 2007-2014, A10 Networks Inc. All rights reserved.
 * Software for all A10 products contain trade secrets and confidential
 * information of A10 Networks and its subsidiaries and may not be
 * disclosed, copied, reproduced or distributed to anyone outside of
 * A10 Networks without prior written consent of A10 Networks, Inc.
 */
/*
 * File name: sflow_ddos_ext_v1.h
 *
 * Copyright(C) 2007-2014, A10 Networks Inc. All rights reserved.
 * Software for all A10 products contain trade secrets and confidential
 * information of A10 Networks and its subsidiaries and may not be
 * disclosed, copied, reproduced or distributed to anyone outside of
 * A10 Networks without prior written consent of A10 Networks, Inc.
 */

#ifndef _SFLOW_DDOS_EXT_V1_H_
#define _SFLOW_DDOS_EXT_V1_H_

#include <sys/types.h>
#include "sto_types.h"
/*
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
*/
#define DDOS_TOTAL_L4_TYPE_SIZE 4
#define DDOS_TOTAL_APP_TYPE_SIZE 7

#define A10_SFLOW 1

struct sflow_ddos_packet_counters_v1 {
    u64 ingress_bytes;
    u64 egress_bytes;
    u64 packets_dropped_by_countermeasures;
    u64 total_ingress_packets;
    u64 total_egress_packets;
} __attribute__((packed));

struct sflow_ddos_l4_counters_v1 {
    u32 protocol[256];
} __attribute__((packed));

struct sflow_ddos_tcp_basic_counter_dir_v1 {
    u32 syn;
    u32 syn_ack;
    u32 fin;
    u32 rst;
    u32 psh;
    u32 ack;
    u32 urg;
    u32 ece;
    u32 cwr;
    u32 ns;
    u32 reserved_flag9;
    u32 reserved_flag10;
    u32 reserved_flag11;
    u32 no_flags;

    u32 option_mss;
    u32 option_wscale;
    u32 option_sack;
    u32 option_ts;
    u32 option_other;
} __attribute__((packed));

struct sflow_ddos_tcp_basic_counters_v1 {
    struct sflow_ddos_tcp_basic_counter_dir_v1 rcvd;
    struct sflow_ddos_tcp_basic_counter_dir_v1 sent;
} __attribute__((packed));

struct sflow_ddos_tcp_stateful_handshake_counters_v1 {
    u16 avg_syn_ack_delay_ms;
    u16 max_syn_ack_delay_ms;
    u16 avg_ack_delay_ms;
    u16 max_ack_delay_ms;
} __attribute__((packed));

struct sflow_ddos_tcp_stateful_close_counters_v1 {
    u64 client_fin;
    u64 client_rst;
    u64 server_fin;
    u64 server_rst;
    u64 idle;
    u64 other;
} __attribute__((packed));

struct sflow_ddos_tcp_stateful_counters_v1 {
    u64 conn_open;
    u64 conn_est;

    struct sflow_ddos_tcp_stateful_close_counters_v1 open_closed;
    struct sflow_ddos_tcp_stateful_close_counters_v1 est_closed;

    struct sflow_ddos_tcp_stateful_handshake_counters_v1 handshake;

    u32 syn_retransmit;
    u32 psh_retransmit;
    u32 ack_retransmit;
    u32 fin_retransmit;
    u32 total_retransmit;

    u32 syn_ofo;
    u32 psh_ofo;
    u32 ack_ofo;
    u32 fin_ofo;
    u32 total_ofo;
} __attribute__((packed));

struct sflow_ddos_http_counters_v1 {
    u32 method_option_count;
    u32 method_get_count;
    u32 method_head_count;
    u32 method_post_count;
    u32 method_put_count;
    u32 method_delete_count;
    u32 method_trace_count;
    u32 method_connect_count;
    u32 method_other_count;
    u32 status_1XX_count;
    u32 status_2XX_count;
    u32 status_3XX_count;
    u32 status_4XX_count;
    u32 status_5XX_count;
    u32 status_other_count;

    /* time to first byte */
    u16 avg_response_time_ms;
    u16 max_response_time_ms;

    u16 avg_health_check_time_ms;
    u16 max_health_check_time_ms;
} __attribute__((packed));

struct sflow_ddos_l4_global_counters_v1 {
    u64 intcp;
    u64 tcp_est;
    u64 tcp_outrst;
    u64 tcp_synreceived;

    u64 tcp_syncookiessent;
    u64 tcp_syncookiessentfailed;
    u64 tcp_syncookiescheckfailed;
    u64 tcp_syn_rate;

    u64 tcp_exceed_drop;
    u64 src_tcp_exceed_drop;
    u64 tcp_exceed_drop_crate_src;
    u64 tcp_exceed_drop_prate_src;

    u64 tcp_exceed_drop_climit_src;
    u64 tcp_exceed_drop_black_src;
    u64 tcp_exceed_drop_crate_dst;
    u64 tcp_exceed_drop_prate_dst;

    u64 tcp_exceed_drop_climit_dst;
    u64 tcp_exceed_drop_black_dst;
    u64 tcp_exceed_drop_crate_src_dst;
    u64 tcp_exceed_drop_prate_src_dst;

    u64 tcp_exceed_drop_climit_src_dst;
    u64 tcp_reset_client;
    u64 tcp_reset_server;
    u64 inudp;

    u64 udp_exceed_drop;
    u64 src_udp_exceed_drop;
    u64 udp_exceed_drop_crate_src;
    u64 udp_exceed_drop_prate_src;

    u64 udp_exceed_drop_climit_src;
    u64 udp_exceed_drop_black_src;
    u64 udp_exceed_drop_crate_dst;
    u64 udp_exceed_drop_prate_dst;

    u64 udp_exceed_drop_climit_dst;
    u64 udp_exceed_drop_black_dst;
    u64 udp_exceed_drop_crate_src_dst;
    u64 udp_exceed_drop_prate_src_dst;

    u64 udp_exceed_drop_climit_src_dst;
    u64 instateless;
    u64 ip_outnoroute;
    u64 other_exceed_drop;

    u64 src_other_exceed_drop;
    u64 l2_dsr;
    u64 dst_learn;
    u64 src_learn;

    u64 src_hit;
    u64 dst_hit;
    u64 inicmp;

    u64 icmp_exceed_drop;
    u64 src_icmp_exceed_drop;

    u64 icmp_exceed_drop_prate_dst;
    u64 dns_malform_drop;
    u64 dns_qry_any_drop;
    u64 sync_src_wl_sent;

    u64 sync_src_dst_wl_sent;
    u64 sync_dst_wl_sent;
    u64 sync_src_wl_rcv;
    u64 sync_src_dst_wl_rcv;

    u64 sync_dst_wl_rcv;
    u64 sync_wl_no_dst_drop;
    u64 ip_rcvd;
    u64 ipv6_rcvd;

    u64 ip_sent;
    u64 ipv6_sent;

    u64 inother;

    u64 ip_tunnel_rcvd;
    u64 ipv6_tunnel_rcvd;

    u64 ip_tunnel_encap;
    u64 ip_tunnel_decap;


    u64 ip_tunnel_fail_encap_rcvd;
    u64 ip_tunnel_rate;

    u64 gre_tunnel_encap;
    u64 gre_tunnel_fail_encap_rcvd;
    u64 gre_tunnel_decap;
    u64 gre_tunnel_rate;
    u64 gre_tunnel_encap_key;
    u64 gre_tunnel_decap_key;
    u64 gre_tunnel_decap_drop_no_key;
    u64 gre_v6_tunnel_rcvd;
    u64 gre_v6_tunnel_fail_encap_rcvd;
    u64 gre_v6_tunnel_decap;
    u64 gre_v6_tunnel_rate;

    u64 dst_port_deny;
    u64 dst_port_undef_drop;

    u64 dst_port_bl;
    u64 dst_port_pkt_rate_exceed;
    u64 dst_port_conn_limm_exceed;
    u64 dst_port_conn_rate_exceed;

    u64 dst_sport_bl;
    u64 dst_sport_pkt_rate_exceed;
    u64 dst_sport_conn_limm_exceed;
    u64 dst_sport_conn_rate_exceed;

    u64 tcp_ack_no_syn;
    u64 tcp_out_of_order;
    u64 tcp_zero_window;
    u64 tcp_retransmit;

    u64 tcp_action_on_ack_drop;
    u64 tcp_action_on_ack_matched;
    u64 tcp_action_on_ack_timeout;
    u64 tcp_action_on_ack_reset;

    u64 src_entry_aged;
    u64 dst_entry_aged;
    u64 zero_wind_fail_bl;
    u64 out_of_seq_fail_bl;

    u64 tcp_retransmit_fail_bl;
    u64 tcp_action_on_ack_passed;
    u64 syn_authn_skipped;
    u64 syn_cookie_fail_bl;

    u64 udp_learn;
    u64 icmp_learn;
    u64 udp_pass;
    u64 dns_auth_pass;

    u64 src_dst_other_frag_exceed_drop;
    u64 src_other_frag_exceed_drop;
    u64 dst_other_frag_exceed_drop;

    u64 over_conn_limit_tcp_syn_auth;
    u64 over_conn_limit_tcp_port_syn_auth;
    u64 max_rexmit_syn_drop;
    u64 max_rexmit_syn_bl;
    u64 wellknown_port_drop;
    u64 ntp_monlist_req_drop;
    u64 ntp_monlist_resp_drop;
    u64 udp_payload_too_big_drop;
    u64 udp_payload_too_small_drop;
    u64 tcp_bl_drop_user_config;
    u64 udp_bl_drop_user_config;
    u64 icmp_bl_drop_user_config;
    u64 other_bl_drop_user_config;

    u64 over_conn_limit_tcp_syn_cookie;
    u64 over_conn_limit_tcp_port_syn_cookie;
    u64 dst_ipproto_pkt_rate_exceed;
    u64 tcp_action_on_ack_failed;
    u64 udp_exceed_drop_conn_prate_dst;
    u64 tcp_exceed_drop_conn_prate_dst;
    u64 dns_tcp_auth_pass;
} __attribute__((__packed__));

struct sflow_ddos_http_ext_counters_v1 {
    u64 ofo_timer_expired;
    u64 partial_hdr;
    u64 ofo;
    u64 retrans_fin;
    u64 retrans_rst;
    u64 retrans_push;
    u64 retrans;
    u64 chunk_bad;
    u64 chunk_sz_512;
    u64 chunk_sz_1k;
    u64 chunk_sz_2k;
    u64 chunk_sz_4k;
    u64 chunk_sz_gt_4k;
    u64 neg_rsp_remain;
    u64 too_many_headers;
    u64 header_name_too_long;
    u64 http11;
    u64 http10;
    u64 get;
    u64 head;
    u64 put;
    u64 post;
    u64 trace;
    u64 options;
    u64 connect;
    u64 del;
    u64 unknown;
    u64 line_too_long;
    u64 req_content_len;
    u64 rsp_chunk;
    u64 parsereq_fail;
    u64 request;
    u64 neg_req_remain;
    u64 client_rst;
    u64 req_retrans;
    u64 req_ofo;
    u64 invalid_header;
    u64 ddos_policy_violation;
    u64 lower_than_mss_exceed;
    u64 dst_req_rate_exceed;
    u64 src_req_rate_exceed;
    u64 req_processed;
    u64 new_syn;
    u64 policy_drop;
    u64 error_condition;
    u64 ofo_queue_exceed;
    u64 alloc_fail;
    u64 alloc_hdr_fail;
    u64 invalid_hdr_name;
    u64 invalid_hdr_val;
    u64 challenge_ud_fail;
    u64 challenge_js_fail;
    u64 challenge_fail;
    u64 challenge_js_sent;
    u64 challenge_ud_sent;
    u64 malform_bad_chunk;
    u64 malform_content_len_too_long;
    u64 malform_too_many_headers;
    u64 malform_header_name_too_long;
    u64 malform_line_too_long;
    u64 malform_req_line_too_long;
    u64 window_small;
    u64 window_small_drop;
    u64 use_hdr_ip_as_source;
    u64 agent_filter_match;
    u64 agent_filter_blacklist;
    u64 referer_filter_match;
    u64 referer_filter_blacklist;
    u64 http_idle_timeout;
    /* New SYM counters */
    u64 hps_rsp_10;
    u64 hps_rsp_11;

    u64 hps_req_sz_1k;
    u64 hps_req_sz_2k;
    u64 hps_req_sz_4k;
    u64 hps_req_sz_8k;
    u64 hps_req_sz_16k;
    u64 hps_req_sz_32k;
    u64 hps_req_sz_64k;
    u64 hps_req_sz_256k;
    u64 hps_req_sz_256k_plus;

    u64 hps_rsp_sz_1k;
    u64 hps_rsp_sz_2k;
    u64 hps_rsp_sz_4k;
    u64 hps_rsp_sz_8k;
    u64 hps_rsp_sz_16k;
    u64 hps_rsp_sz_32k;
    u64 hps_rsp_sz_64k;
    u64 hps_rsp_sz_256k;
    u64 hps_rsp_sz_256k_plus;

    u64 hps_rsp_status_1xx;
    u64 hps_rsp_status_2xx;
    u64 hps_rsp_status_3xx;
    u64 hps_rsp_status_4xx;
    u64 hps_rsp_status_5xx;
    u64 hps_rsp_status_504_AX;
    u64 hps_rsp_status_6xx;
    u64 hps_rsp_status_unknown;
    u64 header_processing_time_0;
    u64 header_processing_time_1;
    u64 header_processing_time_2;
    u64 header_processing_time_3;
    u64 header_processing_incomplete;
    u64 hps_server_rst;

    u64 filter_hdr_match;
    u64 filter_hdr_not_match;
    u64 filter_hdr_action_blacklist;
    u64 filter_hdr_action_drop;
    u64 filter_hdr_action_default_pass;
    u64 dst_post_rate_exceed;
    u64 src_post_rate_exceed;
    u64 dst_resp_rate_exceed;
    u64 filter_hdr_action_whitelist;
    u64 src_filter_hdr_match;
    u64 src_filter_hdr_not_match;
    u64 src_filter_hdr_action_blacklist;
    u64 src_filter_hdr_action_drop;
    u64 src_filter_hdr_action_default_pass;
    u64 src_filter_hdr_action_whitelist;
    u64 src_dst_filter_hdr_match;
    u64 src_dst_filter_hdr_not_match;
    u64 src_dst_filter_hdr_action_blacklist;
    u64 src_dst_filter_hdr_action_drop;
    u64 src_dst_filter_hdr_action_default_pass;
    u64 src_dst_filter_hdr_action_whitelist;

} __attribute__((packed));

struct sflow_ddos_http_ip_ext_counters_v1 {

    u64 ofo_timer_expired;
    u64 partial_hdr;
    u64 ofo;
    u64 retrans_fin;
    u64 retrans_rst;
    u64 retrans_push;
    u64 retrans;
    u64 chunk_bad;
    u64 chunk_sz_512;
    u64 chunk_sz_1k;
    u64 chunk_sz_2k;
    u64 chunk_sz_4k;
    u64 chunk_sz_gt_4k;
    u64 neg_rsp_remain;
    u64 too_many_headers;
    u64 header_name_too_long;
    u64 http11;
    u64 http10;
    u64 get;
    u64 head;
    u64 put;
    u64 post;
    u64 trace;
    u64 options;
    u64 connect;
    u64 del;
    u64 unknown;
    u64 line_too_long;
    u64 req_content_len;
    u64 rsp_chunk;
    u64 parsereq_fail;
    u64 request;
    u64 neg_req_remain;
    u64 client_rst;
    u64 req_retrans;
    u64 req_ofo;
    u64 invalid_header;
    u64 ddos_policy_violation;
    u64 lower_than_mss_exceed;
    u64 dst_req_rate_exceed;
    u64 src_req_rate_exceed;
    u64 req_processed;
    u64 new_syn;
    u64 policy_drop;
    u64 error_condition;
    u64 ofo_queue_exceed;
    u64 alloc_fail;
    u64 get_line_fail;
    u64 alloc_hdr_fail;
    u64 invalid_hdr_name;
    u64 invalid_hdr_val;
    u64 challenge_ud_fail;
    u64 challenge_js_fail;
    u64 challenge_fail;
    u64 challenge_js_sent;
    u64 challenge_ud_sent;
    u64 malform_bad_chunk;
    u64 malform_content_len_too_long;
    u64 malform_too_many_headers;
    u64 malform_header_name_too_long;
    u64 malform_line_too_long;
    u64 malform_req_line_too_long;
    u64 window_small;
    u64 window_small_drop;
    u64 use_hdr_ip_as_source;
    u64 agent_filter_match;
    u64 agent_filter_blacklist;
    u64 referer_filter_match;
    u64 referer_filter_blacklist;
    u64 http_idle_timeout;
    u64 header_processing_time_0;
    u64 header_processing_time_1;
    u64 header_processing_time_2;
    u64 header_processing_time_3;
    u64 header_processing_incomplete;
    u64 req_sz_1k;
    u64 req_sz_2k;
    u64 req_sz_4k;
    u64 req_sz_8k;
    u64 req_sz_16k;
    u64 req_sz_32k;
    u64 req_sz_64k;
    u64 req_sz_256k;
    u64 req_sz_gt_256k;
    u64 filter_hdr_match;
    u64 filter_hdr_not_match;
    u64 filter_hdr_action_blacklist;
    u64 filter_hdr_action_drop;
    u64 filter_hdr_action_default_pass;
    u64 resp_code_1xx;
    u64 resp_code_2xx;
    u64 resp_code_3xx;
    u64 resp_code_4xx;
    u64 resp_code_5xx;
    u64 resp_code_other;
    u64 dst_post_rate_exceed;
    u64 src_post_rate_exceed;
    u64 dst_resp_rate_exceed;
    u64 filter_hdr_action_whitelist;
    u64 filter1_hdr_match;
    u64 filter2_hdr_match;
    u64 filter3_hdr_match;
    u64 filter4_hdr_match;
    u64 filter5_hdr_match;
    u64 filter_hdr_none_match;

    u64 src_partial_hdr;
    u64 src_parsereq_fail;
    u64 src_neg_req_remain;
    u64 src_ddos_policy_violation;
    u64 src_lower_than_mss_exceed;
    u64 src_policy_drop;
    u64 src_malform_bad_chunk;
    u64 src_challenge_ud_fail;
    u64 src_challenge_js_fail;
    u64 src_challenge_fail;
    u64 src_window_small_drop;
    u64 src_filter_hdr_action_drop;
    u64 src_challenge_ud_sent;
    u64 src_challenge_js_sent;
};

struct sflow_ddos_ssl_l4_ip_ext_counters_v1 {

    u64 ssll4_policy_reset;
    u64 ssll4_policy_drop;
    u64 ssll4_drop_packet;
    u64 ssll4_er_condition;
    u64 ssll4_processed;
    u64 ssll4_new_syn;
    u64 ssll4_is_ssl3;
    u64 ssll4_is_tls1_1;
    u64 ssll4_is_tls1_2;
    u64 ssll4_is_tls1_3;
    u64 ssll4_is_renegotiation;
    u64 ssll4_renegotiation_exceed;
    u64 ssll4_is_dst_req_rate_exceed;
    u64 ssll4_is_src_req_rate_exceed;
    u64 ssll4_do_auth_handshake;
    u64 ssll4_reset_for_handshake;
    u64 ssll4_handshake_timeout;
    u64 ssll4_auth_handshake_ok;
    u64 ssll4_auth_handshake_bl;

    u64 src_ssll4_policy_drop;
    u64 src_ssll4_drop_packet;
    u64 src_ssll4_renegotiation_exceed;
    u64 src_ssll4_auth_handshake_bl;
    u64 src_ssll4_policy_reset;
};

struct sflow_ddos_icmp_ip_ext_counters_v1 {

    u64 icmp_type_deny_drop;
    u64 icmpv4_rfc_undef_drop;
    u64 icmpv6_rfc_undef_drop;
    u64 icmp_rate_exceed0;
    u64 icmp_rate_exceed1;
    u64 icmp_rate_exceed2;
    u64 icmp_wildcard_deny_drop;

};

struct sflow_ddos_udp_ip_ext_counters_v1 {

    u64 filter1_match;
    u64 filter2_match;
    u64 filter3_match;
    u64 filter4_match;
    u64 filter5_match;
    u64 filter_none_match;

};

struct sflow_ddos_tcp_ip_ext_counters_v1 {

    u64 filter1_match;
    u64 filter2_match;
    u64 filter3_match;
    u64 filter4_match;
    u64 filter5_match;
    u64 filter_none_match;

};

struct sflow_ddos_other_ip_ext_counters_v1 {

    u64 filter1_match;
    u64 filter2_match;
    u64 filter3_match;
    u64 filter4_match;
    u64 filter5_match;
    u64 filter_none_match;

};

/* Should be the same as struct ddos_anomaly_stats. We have diff structs to maintian compatibility between diff sflow versions. */
struct  sflow_ddos_fpga_anomaly_drop_counters_v1 {

    u64 land_attack_drop;
    u64 empty_frag_drop;
    u64 micro_frag_drop;
    u64 ipv4_opt_drop;
    u64 ip_frag_drop;
    u64 bad_ip_hdr_len_drop;
    u64 bad_ip_flags_drop;
    u64 bad_ip_ttl_drop;
    u64 no_ip_payload_drop;
    u64 oversize_ip_pl_drop;
    u64 bad_ip_pl_len_drop;
    u64 bad_ip_frag_off_drop;
    u64 bad_ip_csum_drop;
    u64 icmp_pod_drop;
    u64 tcp_bad_urg_off_drop;
    u64 tcp_short_hdr_drop;
    u64 tcp_bad_ip_len_drop;
    u64 tcp_null_flags_drop;
    u64 tcp_null_scan_drop;
    u64 tcp_syn_and_fin_drop;
    u64 tcp_xmas_flags_drop;
    u64 tcp_xmas_scan_drop;
    u64 tcp_syn_frag_drop;
    u64 tcp_frag_header_drop;
    u64 tcp_bad_csum_drop;
    u64 udp_short_hdr_drop;
    u64 udp_bad_leng_drop;
    u64 udp_kb_frag_drop;
    u64 udp_port_lb_drop;
    u64 udp_bad_csum_drop;
    u64 runt_ip_hdr_drop;
    u64 runt_tcpudp_hdr_drop;
    u64 tun_mismatch_drop;
    u64 tcp_opt_err;

} __attribute__((packed));

/* SSL-L4 Stats: */
struct sflow_ddos_ssl_l4_stats_v1 {
    u64 ssll4_policy_reset;
    u64 ssll4_policy_drop;
    u64 ssll4_drop_packet;
    u64 ssll4_er_condition;
    u64 ssll4_processed;
    u64 ssll4_new_syn;
    u64 ssll4_is_ssl3;
    u64 ssll4_is_tls1_1;
    u64 ssll4_is_tls1_2;
    u64 ssll4_is_tls1_3;
    u64 ssll4_is_renegotiation;
    u64 ssll4_renegotiation_exceed;
    u64 ssll4_is_dst_req_rate_exceed;
    u64 ssll4_is_src_req_rate_exceed;
    u64 ssll4_do_auth_handshake;
    u64 ssll4_reset_for_handshake;
    u64 ssll4_handshake_timeout;
    u64 ssll4_auth_handshake_ok;
    u64 ssll4_auth_handshake_bl;
} __attribute__((packed));

/* L4 TCP Stats: */
struct sflow_ddos_l4_tcp_stats_v1 {
    u64 tcp_sess_create;
    u64 intcp;
    u64 tcp_syn_rcvd;
    u64 tcp_invalid_syn_rcvd;
    u64 tcp_syn_ack_rcvd;
    u64 tcp_ack_rcvd;
    u64 tcp_fin_rcvd;
    u64 tcp_rst_rcvd;
    u64 tcp_outrst;
    u64 tcp_reset_client;
    u64 tcp_reset_server;
    u64 tcp_syn_rate;
    u64 tcp_total_drop;
    u64 tcp_drop_dst;
    u64 tcp_exceed_drop_any_dst;
    u64 tcp_exceed_drop_prate_dst;
    u64 tcp_exceed_drop_crate_dst;
    u64 tcp_exceed_drop_climit_dst;
    u64 tcp_drop_black_dst;
    u64 tcp_drop_src;
    u64 tcp_exceed_drop_any_src;
    u64 tcp_exceed_drop_prate_src;
    u64 tcp_exceed_drop_crate_src;
    u64 tcp_exceed_drop_climit_src;
    u64 tcp_drop_black_src;
    u64 tcp_drop_black_user_cfg_src;
    u64 tcp_drop_src_dst;
    u64 tcp_exceed_drop_any_src_dst;
    u64 tcp_exceed_drop_prate_src_dst;
    u64 tcp_exceed_drop_crate_src_dst;
    u64 tcp_exceed_drop_climit_src_dst;
    u64 tcp_drop_black_src_dst;
    u64 tcp_drop_black_user_cfg_src_dst;
    u64 tcp_port_zero_drop;
    u64 tcp_syncookie_sent;
    u64 tcp_syncookie_sent_fail;
    u64 tcp_syncookie_check_fail;
    u64 tcp_syncookie_hw_missing;
    u64 tcp_syncookie_fail_bl;
    u64 tcp_syncookie_pass;
    u64 syn_auth_pass;
    u64 syn_auth_skip;
    u64 over_conn_limit_tcp_syn_auth;
    u64 over_conn_limit_tcp_syn_cookie;
    u64 over_conn_limit_tcp_port_syn_auth;
    u64 over_conn_limit_tcp_port_syn_cookie;
    u64 tcp_action_on_ack_start;
    u64 tcp_action_on_ack_matched;
    u64 tcp_action_on_ack_passed;
    u64 tcp_action_on_ack_failed;
    u64 tcp_action_on_ack_timeout;
    u64 tcp_action_on_ack_reset;
    u64 tcp_ack_no_syn;
    u64 tcp_out_of_order;
    u64 tcp_zero_window;
    u64 tcp_retransmit;
    u64 tcp_rexmit_syn_limit_drop;
    u64 tcp_zero_wind_bl;
    u64 tcp_out_of_seq_bl;
    u64 tcp_retransmit_bl;
    u64 tcp_rexmit_syn_limit_bl;
    u64 tcp_exceed_drop_conn_prate;
    u64 tcp_action_on_ack_gap_drop;
    u64 tcp_action_on_ack_gap_pass;
    u64 tcp_new_conn_ack_retry_gap_start;
    u64 tcp_new_conn_ack_retry_gap_passed;
    u64 tcp_new_conn_ack_retry_gap_failed;
    u64 tcp_new_conn_ack_retry_gap_timeout;
    u64 tcp_new_conn_ack_retry_gap_reset;
    u64 tcp_new_conn_ack_retry_gap_drop;
    u64 tcp_action_on_syn_start;
    u64 tcp_action_on_syn_passed;
    u64 tcp_action_on_syn_failed;
    u64 tcp_action_on_syn_timeout;
    u64 tcp_action_on_syn_reset;
    u64 tcp_action_on_syn_gap_drop;
    u64 tcp_action_on_syn_gap_pass;
    u64 tcp_unauth_rst_drop;
    u64 tcp_filter_match;
    u64 tcp_filter_not_match;
    u64 tcp_filter_action_blacklist;
    u64 tcp_filter_action_drop;
    u64 tcp_filter_action_default_pass;
    u64 tcp_over_limit_syn_auth_src;
    u64 tcp_over_limit_syn_auth_src_dst;
    u64 tcp_over_limit_syn_cookie_src;
    u64 tcp_over_limit_syn_cookie_src_dst;
    u64 tcp_exceed_drop_brate_dst;
    u64 tcp_exceed_drop_brate_src;
    u64 tcp_exceed_drop_brate_src_dst;
    u64 tcp_concurrent;
    u64 tcp_filter_action_whitelist;
    u64 src_tcp_filter_match;
    u64 src_tcp_filter_not_match;
    u64 src_tcp_filter_action_blacklist;
    u64 src_tcp_filter_action_drop;
    u64 src_tcp_filter_action_default_pass;
    u64 src_tcp_filter_action_whitelist;
    u64 src_dst_tcp_filter_match;
    u64 src_dst_tcp_filter_not_match;
    u64 src_dst_tcp_filter_action_blacklist;
    u64 src_dst_tcp_filter_action_drop;
    u64 src_dst_tcp_filter_action_default_pass;
    u64 src_dst_tcp_filter_action_whitelist;
} __attribute__((packed));

/* L4 UDP Stats: */
struct sflow_ddos_l4_udp_stats_v1 {
    u64 udp_sess_create;
    u64 inudp;
    u64 instateless;
    u64 udp_total_drop;
    u64 udp_drop_dst;
    u64 udp_exceed_drop_any_dst;
    u64 udp_exceed_drop_prate_dst;
    u64 udp_exceed_drop_crate_dst;
    u64 udp_exceed_drop_climit_dst;
    u64 udp_drop_black_dst;
    u64 udp_drop_src;
    u64 udp_exceed_drop_any_src;
    u64 udp_exceed_drop_prate_src;
    u64 udp_exceed_drop_crate_src;
    u64 udp_exceed_drop_climit_src;
    u64 udp_drop_black_src;
    u64 udp_drop_black_user_cfg_src;
    u64 udp_drop_src_dst;
    u64 udp_exceed_drop_any_src_dst;
    u64 udp_exceed_drop_prate_src_dst;
    u64 udp_exceed_drop_crate_src_dst;
    u64 udp_exceed_drop_climit_src_dst;
    u64 udp_drop_black_src_dst;
    u64 udp_drop_black_user_cfg_src_dst;
    u64 udp_port_zero_drop;
    u64 udp_wellknown_src_port_drop;
    u64 udp_exceed_drop_conn_prate;
    u64 udp_retry_start;
    u64 udp_retry_pass;
    u64 udp_retry_fail;
    u64 udp_retry_timeout;
    u64 udp_payload_too_big_drop;
    u64 udp_payload_too_small_drop;
    u64 ntp_monlist_req_drop;
    u64 ntp_monlist_resp_drop;
    u64 udp_filter_match;
    u64 udp_filter_not_match;
    u64 udp_filter_action_blacklist;
    u64 udp_filter_action_drop;
    u64 udp_filter_action_default_pass;
    u64 udp_filter_action_whitelist;

    u64 UNUSED1;

    u64 udp_auth_pass;
    u64 udp_over_limit_auth_dst;
    u64 udp_over_limit_auth_dst_port;
    u64 udp_over_limit_auth_src;
    u64 udp_over_limit_auth_src_dst;
    u64 udp_exceed_drop_brate_dst;
    u64 udp_exceed_drop_brate_src;
    u64 udp_exceed_drop_brate_src_dst;
    u64 src_udp_filter_match;
    u64 src_udp_filter_not_match;
    u64 src_udp_filter_action_blacklist;
    u64 src_udp_filter_action_drop;
    u64 src_udp_filter_action_default_pass;
    u64 src_udp_filter_action_whitelist;
    u64 src_dst_udp_filter_match;
    u64 src_dst_udp_filter_not_match;
    u64 src_dst_udp_filter_action_blacklist;
    u64 src_dst_udp_filter_action_drop;
    u64 src_dst_udp_filter_action_default_pass;
    u64 src_dst_udp_filter_action_whitelist;
} __attribute__((packed));

/* L4 ICMP Stats: */
/* make sure the sflowtool update as these structures */
struct sflow_ddos_l4_icmp_stats_v1 {
    u64 inicmp;
    u64 icmp_echo_rcvd;
    u64 icmp_other_rcvd;
    u64 icmp_total_drop;
    u64 icmp_drop_dst;
    u64 icmp_exceed_drop_any_dst;
    u64 icmp_exceed_drop_prate_dst;
    u64 icmp_drop_black_dst;
    u64 icmp_drop_src;
    u64 icmp_exceed_drop_any_src;
    u64 icmp_exceed_drop_prate_src;
    u64 icmp_drop_black_src;
    u64 icmp_drop_black_user_cfg_src;
    u64 icmp_drop_src_dst;
    u64 icmp_exceed_drop_any_src_dst;
    u64 icmp_exceed_drop_prate_src_dst;
    u64 icmp_drop_black_src_dst;
    u64 icmp_drop_black_user_cfg_src_dst;
    u64 icmp_type_deny_drop;
    u64 icmp_v4_rfc_undef_drop;
    u64 icmp_v6_rfc_undef_drop;
    u64 icmp_wildcard_deny_drop;
    u64 icmp_rate_exceed0;
    u64 icmp_rate_exceed1;
    u64 icmp_rate_exceed2;
    u64 icmp_exceed_drop_brate_dst;
    u64 icmp_exceed_drop_brate_src;
    u64 icmp_exceed_drop_brate_src_dst;
} __attribute__((packed));

struct sflow_ddos_dns_stats_v1 {

    u64 force_tcp_auth;
    u64 dns_auth_udp;
    u64 dns_malform_drop;
    u64 dns_qry_any_drop;
    u64 dst_rate_limit0;
    u64 dst_rate_limit1;
    u64 dst_rate_limit2;
    u64 dst_rate_limit3;
    u64 dst_rate_limit4;
    u64 src_rate_limit0;
    u64 src_rate_limit1;
    u64 src_rate_limit2;
    u64 src_rate_limit3;
    u64 src_rate_limit4;
    u64 dns_auth_udp_pass;

    //u64 dns_nx_exceed;

    u64 dns_nx_bl;
    u64 dns_nx_drop;
    u64 dns_fqdn_stage2_exceed;
    u64 dns_is_nx;
    u64 dns_fqdn_label_len_exceed;

    u64 UNUSED1;
    u64 UNUSED2;
    u64 UNUSED3;
    u64 UNUSED4;
    u64 UNUSED5;
    u64 UNUSED6;

    u64 dns_pkt_processed;
    u64 dns_query_type_a;
    u64 dns_query_type_aaaa;
    u64 dns_query_type_ns;
    u64 dns_query_type_cname;
    u64 dns_query_type_any;
    u64 dns_query_type_srv;
    u64 dns_query_type_mx;
    u64 dns_query_type_soa;
    u64 dns_query_type_opt;
    u64 dns_tcp_auth_pass;
    u64 dns_auth_udp_fail;
    u64 dns_auth_udp_timeout;

};

/* L4 Others Stats: */
struct sflow_ddos_l4_other_stats_v1 {
    u64 inother;
    u64 infrag;
    u64 other_total_drop;
    u64 other_drop_dst;
    u64 frag_drop;
    u64 other_exceed_drop_any_dst;
    u64 other_exceed_drop_prate_dst;
    u64 other_exceed_drop_fprate_dst;
    u64 other_frag_exceed_drop_dst;
    u64 other_drop_black_dst;
    u64 other_drop_src;
    u64 other_exceed_drop_any_src;
    u64 other_exceed_drop_prate_src;
    u64 other_exceed_drop_fprate_src;
    u64 other_frag_exceed_drop_src;
    u64 other_drop_black_src;
    u64 other_drop_black_user_cfg_src;
    u64 other_drop_src_dst;
    u64 other_exceed_drop_any_src_dst;
    u64 other_exceed_drop_prate_src_dst;
    u64 other_exceed_drop_fprate_src_dst;
    u64 other_frag_exceed_drop_src_dst;
    u64 other_drop_black_src_dst;
    u64 other_drop_black_user_cfg_src_dst;
    u64 other_exceed_drop_brate_dst;
    u64 other_exceed_drop_brate_src;
    u64 other_exceed_drop_brate_src_dst;
    u64 other_filter_match;
    u64 other_filter_not_match;
    u64 other_filter_action_blacklist;
    u64 other_filter_action_drop;
    u64 other_filter_action_default_pass;
    u64 other_filter_action_whitelist;
    u64 src_other_filter_match;
    u64 src_other_filter_not_match;
    u64 src_other_filter_action_blacklist;
    u64 src_other_filter_action_drop;
    u64 src_other_filter_action_default_pass;
    u64 src_other_filter_action_whitelist;
    u64 src_dst_other_filter_match;
    u64 src_dst_other_filter_not_match;
    u64 src_dst_other_filter_action_blacklist;
    u64 src_dst_other_filter_action_drop;
    u64 src_dst_other_filter_action_default_pass;
    u64 src_dst_other_filter_action_whitelist;
} __attribute__((packed));

/* DDOS Switch Stats: */
struct sflow_ddos_switch_stats_v1 {
    u64 ip_rcvd;
    u64 ip_sent;
    u64 ipv6_rcvd;
    u64 ipv6_sent;
    u64 instateless;
    u64 out_no_route;
    u64 not_for_ddos;
    u64 mpls_rcvd;
    u64 mpls_drop;
    u64 mpls_malformed;
} __attribute__((packed));

/* DDOS Sessions stats: */
struct sflow_ddos_sess_stats_v1 {
    /* need more counters */
    u64 v4_sess_create;
    u64 v6_sess_create;
    u64 tcp_sess_create;
    u64 tcp_conn_est_w_syn;
    u64 tcp_conn_est_w_ack;
    u64 tcp_conn_est;
    u64 tcp_conn_close_w_rst;
    u64 tcp_conn_close_w_fin;
    u64 tcp_conn_close_w_idle;
    u64 tcp_conn_close_w_half_open;
    u64 tcp_conn_close;
    u64 udp_sess_create;
    u64 udp_conn_est;
    u64 udp_conn_close;
} __attribute__((packed));

/* DDOS Sync Stats: */
struct sflow_ddos_sync_stats_v1 {

    u64 sync_dst_wl_rcv;
    u64 sync_dst_wl_sent;
    u64 sync_src_wl_rcv;
    u64 sync_src_wl_sent;
    u64 sync_src_dst_wl_rcv;
    u64 sync_src_dst_wl_sent;
    u64 sync_src_dst_wl_no_dst_drop;
    u64 sync_hello_rcv;
    u64 sync_hello_sent;

    u64 sync_sent_fail;
    u64 sync_sent_no_peer;
    u64 sync_rcv_fail;

    u64 sync_dst_tcp_wl_sent;
    u64 sync_dst_udp_wl_sent;
    u64 sync_dst_icmp_wl_sent;
    u64 sync_dst_other_wl_sent;
    u64 sync_dst_tcp_bl_sent;
    u64 sync_dst_udp_bl_sent;
    u64 sync_dst_icmp_bl_sent;
    u64 sync_dst_other_bl_sent;
    u64 sync_src_tcp_wl_sent;
    u64 sync_src_udp_wl_sent;
    u64 sync_src_icmp_wl_sent;
    u64 sync_src_other_wl_sent;
    u64 sync_src_tcp_bl_sent;
    u64 sync_src_udp_bl_sent;
    u64 sync_src_icmp_bl_sent;
    u64 sync_src_other_bl_sent;
    u64 sync_src_dst_tcp_wl_sent;
    u64 sync_src_dst_udp_wl_sent;
    u64 sync_src_dst_icmp_wl_sent;
    u64 sync_src_dst_other_wl_sent;
    u64 sync_src_dst_tcp_bl_sent;
    u64 sync_src_dst_udp_bl_sent;
    u64 sync_src_dst_icmp_bl_sent;
    u64 sync_src_dst_other_bl_sent;
    u64 sync_dst_tcp_wl_rcvd;
    u64 sync_dst_udp_wl_rcvd;
    u64 sync_dst_icmp_wl_rcvd;
    u64 sync_dst_other_wl_rcvd;
    u64 sync_dst_tcp_bl_rcvd;
    u64 sync_dst_udp_bl_rcvd;
    u64 sync_dst_icmp_bl_rcvd;
    u64 sync_dst_other_bl_rcvd;
    u64 sync_src_tcp_wl_rcvd;
    u64 sync_src_udp_wl_rcvd;
    u64 sync_src_icmp_wl_rcvd;
    u64 sync_src_other_wl_rcvd;
    u64 sync_src_tcp_bl_rcvd;
    u64 sync_src_udp_bl_rcvd;
    u64 sync_src_icmp_bl_rcvd;
    u64 sync_src_other_bl_rcvd;
    u64 sync_src_dst_tcp_wl_rcvd;
    u64 sync_src_dst_udp_wl_rcvd;
    u64 sync_src_dst_icmp_wl_rcvd;
    u64 sync_src_dst_other_wl_rcvd;
    u64 sync_src_dst_tcp_bl_rcvd;
    u64 sync_src_dst_udp_bl_rcvd;
    u64 sync_src_dst_icmp_bl_rcvd;
    u64 sync_src_dst_other_bl_rcvd;

} __attribute__((packed));

/* DDOS Tunnel Stats: */
struct sflow_ddos_tunnel_stats_v1 {
    u64 ip_tunnel_rcvd;
    u64 ip_tunnel_rate;
    u64 ip_tunnel_encap;
    u64 ip_tunnel_encap_fail;
    u64 ip_tunnel_decap;
    u64 ip_tunnel_decap_fail;
    u64 ipv6_tunnel_rcvd;
    u64 ipv6_tunnel_rate;
    u64 ipv6_tunnel_encap;
    u64 ipv6_tunnel_encap_fail;
    u64 ipv6_tunnel_decap;
    u64 ipv6_tunnel_decap_fail;
    u64 gre_tunnel_rcvd;
    u64 gre_tunnel_rate;
    u64 gre_tunnel_encap;
    u64 gre_tunnel_encap_fail;
    u64 gre_tunnel_decap;
    u64 gre_tunnel_decap_fail;
    u64 gre_tunnel_encap_key;
    u64 gre_tunnel_decap_key;
    u64 gre_tunnel_decap_drop_no_key;
    u64 gre_v6_tunnel_rcvd;
    u64 gre_v6_tunnel_rate;
    u64 gre_v6_tunnel_encap;
    u64 gre_v6_tunnel_encap_fail;
    u64 gre_v6_tunnel_decap;
    u64 gre_v6_tunnel_decap_fail;
    u64 gre_v6_tunnel_encap_key;
    u64 gre_v6_tunnel_decap_key;
    u64 gre_v6_tunnel_decap_drop_no_key;
} __attribute__((packed));

/* DDOS Table stats: */
struct sflow_ddos_table_stats_v1 {
    u64 dst_entry_learn;
    u64 dst_entry_hit;
    u64 dst_entry_miss;
    u64 dst_entry_aged;
    u64 src_entry_learn;
    u64 src_entry_hit;
    u64 src_entry_miss;
    u64 src_entry_aged;
    u64 src_dst_entry_learn;
    u64 src_dst_entry_hit;
    u64 src_dst_entry_miss;
    u64 src_dst_entry_aged;
    u64 src_wl_tcp;
    u64 src_wl_udp;
    u64 src_wl_icmp;
    u64 src_wl_other;
    u64 src_bl_tcp;
    u64 src_bl_udp;
    u64 src_bl_icmp;
    u64 src_bl_other;
    u64 src_dst_wl_tcp;
    u64 src_dst_wl_udp;
    u64 src_dst_wl_icmp;
    u64 src_dst_wl_other;
    u64 src_dst_bl_tcp;
    u64 src_dst_bl_udp;
    u64 src_dst_bl_icmp;
    u64 src_dst_bl_other;
    u64 dst_over_limit_on;
    u64 dst_port_over_limit_on;
    u64 src_over_limit_on;
    u64 src_dst_over_limit_on;
    u64 dst_over_limit_off;
    u64 dst_port_over_limit_off;
    u64 src_over_limit_off;
    u64 src_dst_over_limit_off;
} __attribute__((packed));

/* DDOS Brief View Stats: */

struct sflow_ddos_brief_stats_v1 { /* #show ddos statistics */

    u64 ip_rcvd;
    u64 ip_sent;
    u64 ipv6_rcvd;
    u64 ipv6_sent;
    u64 out_no_route;
    u64 not_for_ddos;
    u64 instateless;
    u64 intcp;
    u64 inudp;
    u64 inicmp;
    u64 inother;

    u64 v4_sess_create;
    u64 v6_sess_create;
    u64 tcp_sess_create;
    u64 udp_sess_create;
    u64 sess_aged_out;

    u64 tcp_total_drop;
    u64 tcp_dst_drop;
    u64 tcp_src_drop;
    u64 tcp_src_dst_drop;
    u64 tcp_drop_black_dst;
    u64 tcp_drop_black_src;
    u64 tcp_drop_black_src_dst;
    u64 tcp_exceed_drop_any_dst;
    u64 tcp_exceed_drop_any_src;
    u64 tcp_exceed_drop_any_src_dst;

    u64 udp_total_drop;
    u64 udp_dst_drop;
    u64 udp_src_drop;
    u64 udp_src_dst_drop;
    u64 udp_drop_black_dst;
    u64 udp_drop_black_src;
    u64 udp_drop_black_src_dst;
    u64 udp_exceed_drop_any_dst;
    u64 udp_exceed_drop_any_src;
    u64 udp_exceed_drop_any_src_dst;

    u64 icmp_total_drop;
    u64 icmp_dst_drop;
    u64 icmp_src_drop;
    u64 icmp_src_dst_drop;
    u64 icmp_drop_black_dst;
    u64 icmp_drop_black_src;
    u64 icmp_drop_black_src_dst;
    u64 icmp_exceed_drop_any_dst;
    u64 icmp_exceed_drop_any_src;
    u64 icmp_exceed_drop_any_src_dst;

    u64 other_total_drop;
    u64 other_dst_drop;
    u64 other_src_drop;
    u64 other_src_dst_drop;
    u64 other_drop_black_dst;
    u64 other_drop_black_src;
    u64 other_drop_black_src_dst;
    u64 other_exceed_drop_any_dst;
    u64 other_exceed_drop_src;
    u64 other_exceed_drop_src_dst;
    u64 infrag;
    u64 frag_drop;

    u64 http_drop_total;
    u64 http_drop_dst;
    u64 http_drop_src;
    u64 http_drop_src_dst;

    u64 dns_udp_drop_total;
    u64 dns_udp_drop_dst;
    u64 dns_udp_drop_src;
    u64 dns_udp_drop_src_dst;

    u64 dns_tcp_drop_total;
    u64 dns_tcp_drop_dst;
    u64 dns_tcp_drop_src;
    u64 dns_tcp_drop_src_dst;

    u64 ssl_l4_drop_total;
    u64 ssl_l4_drop_dst;
    u64 ssl_l4_drop_src;
    u64 ssl_l4_drop_src_dst;

    u64 dst_port_undef_drop;
    u64 dst_port_exceed_drop_any;
    u64 dst_ipproto_bl;
    u64 dst_port_bl;

    u64 dst_sport_bl;
    u64 dst_sport_exceed_drop_any;

    u64 dst_ipproto_rcvd;
    u64 dst_ipproto_drop;
    u64 dst_ipproto_exceed_drop_any;
    u64 src_ip_bypass;

    u64 mpls_rcvd;
    u64 mpls_drop;
    u64 mpls_malformed;
    u64 dst_scanning_detected;

    u64 dst_ingress_bytes;
    u64 dst_egress_bytes;
    u64 dst_ingress_packets;
    u64 dst_egress_packets;
    u64 dst_ip_bypass;

    u64 dst_blackhole_inject;
    u64 dst_blackhole_withdraw;

    u64 dst_fwd_pkt_sent;
    u64 dst_rev_pkt_sent;
    u64 dst_fwd_byte_sent;
    u64 dst_rev_byte_sent;

} __attribute__((packed));

struct sflow_ddos_long_stats_v1 { /* #show ddos statistics long */

    u64 tcp_syncookie_sent;
    u64 tcp_syncookie_pass;
    u64 tcp_syncookie_sent_fail;
    u64 tcp_syncookie_check_fail;
    u64 tcp_syncookie_fail_bl;
    u64 tcp_outrst;
    u64 tcp_syn_received;
    u64 tcp_syn_rate;
    u64 tcp_exceed_drop_prate_dst;
    u64 tcp_exceed_drop_crate_dst;
    u64 tcp_exceed_drop_climit_dst;
    u64 tcp_exceed_drop_prate_src;
    u64 tcp_exceed_drop_crate_src;
    u64 tcp_exceed_drop_climit_src;
    u64 tcp_exceed_drop_prate_src_dst;
    u64 tcp_exceed_drop_crate_src_dst;
    u64 tcp_exceed_drop_climit_src_dst;
    u64 udp_exceed_drop_prate_dst;
    u64 udp_exceed_drop_crate_dst;
    u64 udp_exceed_drop_climit_dst;
    u64 udp_exceed_drop_prate_src;
    u64 udp_exceed_drop_crate_src;
    u64 udp_exceed_drop_climit_src;
    u64 udp_exceed_drop_prate_src_dst;
    u64 udp_exceed_drop_crate_src_dst;
    u64 udp_exceed_drop_climit_src_dst;
    u64 udp_exceed_drop_conn_prate;
    u64 dns_malform_drop;
    u64 dns_qry_any_drop;
    u64 tcp_reset_client;
    u64 tcp_reset_server;
    u64 dst_entry_learn;
    u64 dst_entry_hit;
    u64 src_entry_learn;
    u64 src_entry_hit;
    u64 sync_src_wl_sent;
    u64 sync_src_dst_wl_sent;
    u64 sync_dst_wl_sent;
    u64 sync_src_wl_rcv;
    u64 sync_src_dst_wl_rcv;
    u64 sync_dst_wl_rcv;
    u64 dst_port_pkt_rate_exceed;
    u64 dst_port_conn_limm_exceed;
    u64 dst_port_conn_rate_exceed;
    u64 dst_sport_pkt_rate_exceed;
    u64 dst_sport_conn_limm_exceed;
    u64 dst_sport_conn_rate_exceed;
    u64 dst_ipproto_pkt_rate_exceed;
    u64 tcp_ack_no_syn;
    u64 tcp_ofo;
    u64 tcp_zero_window;
    u64 tcp_retransmit;
    u64 tcp_action_on_ack_start;
    u64 tcp_action_on_ack_matched;
    u64 tcp_action_on_ack_passed;
    u64 tcp_action_on_ack_failed;
    u64 tcp_action_on_ack_timeout;
    u64 tcp_action_on_ack_reset;
    u64 src_entry_aged;
    u64 dst_entry_aged;
    u64 tcp_zero_wind_bl;
    u64 tcp_ofo_bl;
    u64 tcp_retransmit_bl;
    u64 syn_auth_skip;
    u64 udp_retry_pass;
    u64 dns_auth_udp_pass;
    u64 dst_port_udp_wellknown_port_drop;
    u64 ntp_monlist_req_drop;
    u64 ntp_monlist_resp_drop;
    u64 udp_payload_too_big_drop;
    u64 udp_payload_too_small_drop;
    u64 other_frag_exceed_drop_dst;
    u64 other_frag_exceed_drop_src;
    u64 other_frag_exceed_drop_src_dst;
    u64 tcp_rexmit_syn_limit_drop;
    u64 tcp_rexmit_syn_limit_bl;
    u64 over_conn_limit_tcp_syn_auth;
    u64 over_conn_limit_tcp_syn_cookie;
    u64 over_conn_limit_tcp_port_syn_auth;
    u64 over_conn_limit_tcp_port_syn_cookie;
    u64 tcp_exceed_drop_conn_prate;
    u64 syn_auth_pass;
    u64 udp_retry_start;
    u64 udp_retry_fail;
    u64 udp_retry_timeout;
    u64 ip_tunnel_rcvd;
    u64 ipv6_tunnel_rcvd;
    u64 gre_tunnel_rcvd;
    u64 gre_v6_tunnel_rcvd;
    u64 dst_entry_miss;
    u64 src_entry_miss;
    u64 src_dst_entry_hit;
    u64 src_dst_entry_miss;
    u64 src_dst_entry_aged;
    u64 icmp_exceed_drop_prate_dst;
    u64 sync_wl_no_dst_drop;
    u64 src_dst_entry_learn;
    u64 dns_tcp_auth_pass;
    u64 dst_port_kbit_rate_exceed;
    u64 dst_sport_kbit_rate_exceed;

} __attribute__((packed));

/* T2 Stats:- */

struct sflow_ddos_dns_ip_ext_counters_v1 {

    u64 force_tcp_auth;
    u64 udp_auth;
    u64 dst_rate_limit0;
    u64 dst_rate_limit1;
    u64 dst_rate_limit2;
    u64 dst_rate_limit3;
    u64 dst_rate_limit4;
    u64 dst_is_nx;
    u64 dst_fqdn_stage2_rate_exceed;
    u64 dst_nx_bl;
    u64 dst_nx_drop;
    u64 dns_req_sent;
    u64 dns_req_size_exceed;
    u64 dns_req_retrans;
    u64 dns_tcp_req_incomplete;
    u64 dns_fqdn_label_len_exceed;

    u64 UNUSED1;
    u64 UNUSED2;
    u64 UNUSED3;
    u64 UNUSED4;
    u64 UNUSED5;
    u64 UNUSED6;

    u64 dns_query_type_a;
    u64 dns_query_type_aaaa;
    u64 dns_query_type_ns;
    u64 dns_query_type_cname;
    u64 dns_query_type_any;
    u64 dns_query_type_srv;
    u64 dns_query_type_mx;
    u64 dns_query_type_soa;
    u64 dns_query_type_opt;
    u64 dns_udp_auth_fail;
    u64 dns_malform_drop;
    u64 src_rate_limit0;
    u64 src_rate_limit1;
    u64 src_rate_limit2;
    u64 src_rate_limit3;
    u64 src_rate_limit4;

    u64 src_dns_fqdn_label_len_exceed;
    u64 src_dns_udp_auth_fail;
    u64 src_force_tcp_auth;
    u64 src_dns_malform_drop;

} __attribute__((packed));

struct sflow_ddos_ip_counter_l4_t2_v1 {

    u64 dst_frag_pkt_rate_exceed;
    u64 dst_icmp_pkt_rate_exceed;
    u64 dst_other_pkt_rate_exceed;
    u64 dst_tcp_src_drop;
    u64 dst_udp_src_drop;
    u64 dst_icmp_src_drop;
    u64 dst_other_src_drop;
    u64 dst_tcp_pkt_rcvd;
    u64 dst_tcp_conn_limit_exceed;
    u64 dst_tcp_any_exceed;
    u64 dst_tcp_pkt;
    u64 dst_tcp_pkt_rate_exceed;
    u64 dst_tcp_syn;
    u64 dst_tcp_syn_drop;
    u64 dst_tcp_conn_rate_exceed;
    u64 dst_frag_src_rate_drop;
    u64 dst_udp_conn_limit_exceed;
    u64 dst_udp_pkt;
    u64 dst_udp_pkt_rate_exceed;
    u64 dst_tcp_auth;
    u64 dst_udp_conn_rate_exceed;
    u64 dst_tcp_drop;
    u64 dst_udp_drop;
    u64 dst_icmp_drop;
    u64 dst_frag_drop;
    u64 dst_other_drop;
    u64 dst_pkt_sent;
    u64 dst_udp_pkt_sent;
    u64 dst_tcp_pkt_sent;
    u64 dst_icmp_pkt_sent;
    u64 dst_other_pkt_sent;
    u64 dst_icmp_pkt;
    u64 dst_other_pkt;
    u64 dst_tcp_src_rate_drop;
    u64 dst_udp_src_rate_drop;
    u64 dst_icmp_src_rate_drop;
    u64 dst_other_src_rate_drop;
    u64 dst_port_pkt_rate_exceed;
    u64 dst_port_conn_limit_exceed;
    u64 dst_port_conn_rate_exceed;
    u64 dst_udp_any_exceed;
    u64 dst_udp_filter_match;
    u64 dst_udp_filter_not_match;
    u64 dst_udp_filter_action_blacklist;
    u64 dst_udp_filter_action_drop;
    u64 dst_udp_filter_action_default_pass;
    u64 dst_tcp_filter_match;
    u64 dst_tcp_filter_not_match;
    u64 dst_tcp_filter_action_blacklist;
    u64 dst_tcp_filter_action_drop;
    u64 dst_tcp_filter_action_default_pass;
    u64 dst_udp_filter_action_whitelist;
    u64 dst_udp_pkt_rcvd;
    u64 dst_icmp_pkt_rcvd;
    u64 dst_other_pkt_rcvd;
    u64 tcp_syn_cookie_fail;
    u64 tcp_syn_rcvd;
    u64 tcp_syn_ack_rcvd;
    u64 tcp_ack_rcvd;
    u64 tcp_fin_rcvd;
    u64 tcp_rst_rcvd;
    u64 ingress_bytes;
    u64 egress_bytes;
    u64 ingress_packets;
    u64 egress_packets;
    u64 tcp_fwd_recv;
    u64 udp_fwd_recv;
    u64 icmp_fwd_recv;
    u64 dst_over_limit_on;
    u64 dst_over_limit_off;
    u64 dst_port_over_limit_on;
    u64 dst_port_over_limit_off;
    u64 dst_over_limit_action;
    u64 dst_port_over_limit_action;
    u64 scanning_detected_drop;
    u64 scanning_detected_blacklist;
    u64 dst_udp_kibit_rate_drop;
    u64 dst_tcp_kibit_rate_drop;
    u64 dst_icmp_kibit_rate_drop;
    u64 dst_other_kibit_rate_drop;
    u64 dst_port_undef_drop;
    u64 dst_port_bl;
    u64 dst_src_port_bl;
    u64 dst_tcp_session_created;
    u64 dst_udp_session_created;
    u64 dst_tcp_filter_action_whitelist;
    u64 dst_other_filter_match;
    u64 dst_other_filter_not_match;
    u64 dst_other_filter_action_blacklist;
    u64 dst_other_filter_action_drop;
    u64 dst_other_filter_action_default_pass;
    u64 dst_other_filter_action_whitelist;
    u64 dst_blackhole_inject;
    u64 dst_blackhole_withdraw;
    u64 dst_out_no_route;
    u64 dst_port_kbit_rate_exceed;
    u64 dst_tcp_out_of_seq_excd;
    u64 dst_tcp_retransmit_excd;
    u64 dst_tcp_zero_window_excd;
    u64 dst_tcp_conn_prate_excd;
    u64 dst_tcp_action_on_ack_init;
    u64 dst_tcp_action_on_ack_gap_drop;
    u64 dst_tcp_action_on_ack_fail;
    u64 dst_tcp_action_on_ack_pass;
    u64 dst_tcp_action_on_syn_init;
    u64 dst_tcp_action_on_syn_gap_drop;
    u64 dst_tcp_action_on_syn_fail;
    u64 dst_tcp_action_on_syn_pass;
    u64 dst_udp_min_payload;
    u64 dst_udp_max_payload;
    u64 dst_udp_conn_prate_excd;
    u64 dst_udp_ntp_monlist_req;
    u64 dst_udp_ntp_monlist_resp;
    u64 dst_udp_wellknown_sport_drop;
    u64 dst_udp_retry_init;
    u64 dst_udp_retry_pass;
    u64 dst_icmp_any_exceed;
    u64 dst_other_any_exceed;
    u64 dst_drop_frag_pkt;

    u64 src_udp_min_payload;
    u64 src_udp_max_payload;
    u64 src_udp_ntp_monlist_req;
    u64 src_udp_ntp_monlist_resp;
    u64 src_tcp_action_on_ack_gap_drop;
    u64 src_tcp_action_on_syn_gap_drop;
    u64 tcp_new_conn_ack_retry_gap_drop;
    u64 src_tcp_new_conn_ack_retry_gap_drop;
    u64 src_tcp_filter_action_blacklist;
//    u64 src_dst_tcp_filter_action_blacklist;
    u64 src_tcp_filter_action_drop;
//    u64 src_dst_tcp_filter_action_drop;
    u64 src_tcp_out_of_seq_excd;
    u64 src_tcp_retransmit_excd;
    u64 src_tcp_zero_window_excd;
    u64 src_tcp_conn_prate_excd;
    u64 src_udp_filter_action_blacklist;
    u64 src_dst_udp_filter_action_blacklist;
    u64 src_udp_filter_action_drop;
    u64 src_dst_udp_filter_action_drop;
    u64 src_udp_conn_prate_excd;
    u64 src_other_filter_action_blacklist;
    u64 src_dst_other_filter_action_blacklist;
    u64 src_other_filter_action_drop;
    u64 src_dst_other_filter_action_drop;
    u64 dst_port_src_over_limit_action;

    u64 src_tcp_action_on_ack_fail;
    u64 src_tcp_action_on_syn_fail;
    u64 src_udp_wellknown_sport_drop;
    u64 src_tcp_syn_cookie_fail;
    u64 src_tcp_action_on_ack_init;
    u64 src_tcp_action_on_syn_init;
    u64 src_udp_retry_init;
    u64 tcp_rst_cookie_fail;
    u64 tcp_unauth_drop;
    u64 src_tcp_rst_cookie_fail;
    u64 src_tcp_unauth_drop;
    
    u64 dst_l4_tcp_blacklist_drop;
    u64 dst_l4_udp_blacklist_drop;
    u64 dst_l4_icmp_blacklist_drop;
    u64 dst_l4_other_blacklist_drop;

    u64 src_dst_l4_tcp_blacklist_drop;
    u64 src_dst_l4_udp_blacklist_drop;
    u64 src_dst_l4_icmp_blacklist_drop;
    u64 src_dst_l4_other_blacklist_drop;
    u64 src_tcp_auth;

    u64 dst_fwd_pkt_sent;
    u64 dst_rev_pkt_sent;

} __attribute__((packed));

struct sflow_ddos_ip_counter_l4_ext_t2_v1 {
    u64 dst_fwd_bytes_sent;
    u64 dst_rev_bytes_sent;
    u64 tcp_l4_syn_cookie_fail;
    u64 tcp_l4_rst_cookie_fail;
    u64 tcp_l4_unauth_drop;
    u64 dst_l4_tcp_auth;

    u64 src_frag_pkt_rate_exceed;
    u64 src_frag_drop;
    u64 dst_frag_timeout_drop;
    u64 dst_tcp_invalid_syn;
} __attribute__((packed));


struct sflow_ddos_limit_result_stat_v1 {
    /* 0 Byte */
    u32 curr_conn;
    u32 conn_limit;
    u32 curr_conn_rate;
    u32 conn_rate_limit;
    u32 curr_pkt_rate;
    u32 pkt_rate_limit;
    u32 curr_syn_cookie;
    u32 syn_cookie_thr;
    u64 bl_drop_ct;
    u64 conn_rate_exceed_ct;
    u64 pkt_rate_exceed_ct;
    u64 conn_limit_exceed_ct;
} __attribute__((packed));

struct sflow_ddos_limit_app_stat_v1 {
    u32 app;
    u32 state;
    u32 exceed_byte;
    u32 lockup_period;
    u32 app_rate1;
    u32 config_app_rate1;
    u32 app_rate2;
    u32 config_app_rate2;
    u32 app_rate3;
    u32 config_app_rate3;
    u32 app_rate4;
    u32 config_app_rate4;
    u32 app_rate5;
    u32 config_app_rate5;
    u32 app_rate6;
    u32 config_app_rate6;
    u32 app_rate7;
    u32 config_app_rate7;
    u32 app_rate8;
    u32 config_app_rate8;
} __attribute__((packed));

struct sflow_ddos_limit_proto_stat_v1 {
    u32 protocol;
    u32 state;
    u32 exceed_byte;
    u32 lockup_period;
    struct sflow_ddos_limit_result_stat_v1 stat;
} __attribute__((packed));

struct sflow_ddos_ip_counter_common_v1 {
    u32 table_type;   /* 0:DDOS_DST, 1:DDOS_SRC, 2:DDOS_SRC_DST */
    u32 ip_type;      /* 1:ipv4 address, 2:ipv6 address*/
    u32 static_entry;
    union {
        u32                 ip_addr;
        struct in6_addr     ip6_addr;
    };
    union {
        u32                 dst_ip_addr;
        struct in6_addr     dst_ip6_addr;
    };
    u16 subnet_mask;
    u16 age;
} __attribute__((packed));

struct sflow_ddos_ip_counter_l4_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_ip_counter_l4_t2_v1 l4;
} __attribute__((packed));

struct sflow_ddos_ip_counter_l4_ext_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_ip_counter_l4_ext_t2_v1 l4_ext;
} __attribute__((packed));


struct sflow_ddos_ip_counter_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    u32 proto_num;    /* number of protocols */
    union {
        struct {
            struct sflow_ddos_limit_proto_stat_v1 udp;
            struct sflow_ddos_limit_proto_stat_v1 tcp;
            struct sflow_ddos_limit_proto_stat_v1 icmp;
            struct sflow_ddos_limit_proto_stat_v1 other;
        } __attribute__((packed));
        struct sflow_ddos_limit_proto_stat_v1 stat[DDOS_TOTAL_L4_TYPE_SIZE];
    } __attribute__((packed));
    u32 app_num;    /* number of app */
    struct sflow_ddos_limit_app_stat_v1 app_stat[DDOS_TOTAL_APP_TYPE_SIZE - DDOS_TOTAL_L4_TYPE_SIZE];
} __attribute__((packed));

struct sflow_ddos_ip_counter_port_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    u32 port;
    u32 app_type;
    u32 port_exceed_check;
    u32 lockup_period;
    struct sflow_ddos_limit_result_stat_v1 port_stat;
};

struct sflow_ddos_ip_counter_dns_t2_v1 {
    u16 port;
    u16 app_type;     /* The app type for this sflow record */
    struct sflow_ddos_dns_ip_ext_counters_v1 stats;
} __attribute__((packed));

/*
struct sflow_ddos_ip_counter_dns_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_ip_counter_dns_t2_v1 dns;
} __attribute__((packed));
*/

struct sflow_ddos_ip_counter_dns_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_ip_counter_dns_t2_v1 dns;
} __attribute__((packed));

struct sflow_ddos_ip_counter_icmp_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_icmp_ip_ext_counters_v1 icmp;
} __attribute__((packed));

struct sflow_ddos_ip_counter_http_t2_v1 {
    u16 port;
    u16 app_type;     /* The app type for this sflow record */
    struct sflow_ddos_http_ip_ext_counters_v1 stats;
} __attribute__((packed));

struct sflow_ddos_ip_counter_http_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_ip_counter_http_t2_v1 http;
} __attribute__((packed));

struct sflow_ddos_ip_counter_ssl_l4_t2_v1 {
    u16 port;
    u16 app_type;     /* The app type for this sflow record */
    struct sflow_ddos_ssl_l4_ip_ext_counters_v1 stats;
} __attribute__((packed));

struct sflow_ddos_ip_counter_ssl_l4_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_ip_counter_ssl_l4_t2_v1 ssl_l4;
} __attribute__((packed));

struct sflow_ddos_ip_counter_udp_t2_v1 {
    u16 port;
    u16 app_type;     /* The app type for this sflow record */
    struct sflow_ddos_udp_ip_ext_counters_v1 stats;
} __attribute__((packed));

struct sflow_ddos_ip_counter_udp_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_ip_counter_udp_t2_v1 udp;
} __attribute__((packed));

struct sflow_ddos_ip_counter_tcp_t2_v1 {
    u16 port;
    u16 app_type;     /* The app type for this sflow record */
    struct sflow_ddos_tcp_ip_ext_counters_v1 stats;
} __attribute__((packed));

struct sflow_ddos_ip_counter_tcp_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_ip_counter_tcp_t2_v1 tcp;
} __attribute__((packed));

struct sflow_ddos_ip_counter_other_t2_v1 {
    u16 port;
    u16 app_type;     /* The app type for this sflow record */
    struct sflow_ddos_other_ip_ext_counters_v1 stats;
} __attribute__((packed));

struct sflow_ddos_ip_counter_other_v1 {
    struct sflow_ddos_ip_counter_common_v1 common;
    struct sflow_ddos_ip_counter_other_t2_v1 other;
} __attribute__((packed));

/**
 * Note: x100 means it's a float value times 100, so divide the given value by 100 to get the real value
 * e.g. for 1.45 we will send 145 as the value
 * This is to avoid issues with floating point
 */
struct sflow_ddos_ind_value_v1 {
    u32 mean_x100;
    u32 variance_x100;
    u32 min_x100;
    u32 nonzero_min_x100;
    u32 max_x100;
} __attribute__((packed));

struct sflow_ddos_dst_udp_indicators_v1 {
    u32 seq_num;
    u16 num_data_points;
    u16 elapsed_sec;
    struct sflow_ddos_ind_value_v1 in_pkt_rate; // DDET_IND_PKT_RATE_UDP
    struct sflow_ddos_ind_value_v1 small_payload_rate; // DDET_IND_SMALL_PAYLOAD_RATE_UDP
    struct sflow_ddos_ind_value_v1 in_byte_over_out_byte; // DDET_IND_INB_PER_OUTB_UDP
    struct sflow_ddos_ind_value_v1 concurrent_conns; // DDET_IND_CONCURRENT_CONNS_UDP
    struct sflow_ddos_ind_value_v1 pkt_drop_rate;   // DDET_IND_PKT_DROP_RATE_UDP
    struct sflow_ddos_ind_value_v1 pkt_drop_recv_ratio;     //  DDET_IND_PKT_DROP_RATIO_UDP
} __attribute__((packed));

struct sflow_ddos_dst_tcp_indicators_v1 {
    u32 seq_num;
    u16 num_data_points;
    u16 elapsed_sec;
    struct sflow_ddos_ind_value_v1 in_pkt_rate;                // DDET_IND_PKT_RATE_TCP
    struct sflow_ddos_ind_value_v1 in_syn_rate;                // DDET_IND_SYN_RATE
    struct sflow_ddos_ind_value_v1 in_fin_rate;                // DDET_IND_FIN_RATE
    struct sflow_ddos_ind_value_v1 in_rst_rate;                // DDET_IND_RST_RATE
    struct sflow_ddos_ind_value_v1 small_window_ack_rate;      // DDET_IND_SMALL_WINDOW_ACK_RATE
    struct sflow_ddos_ind_value_v1 empty_ack_rate;             // DDET_IND_EMPTY_ACK_RATE
    struct sflow_ddos_ind_value_v1 small_payload_rate;         // DDET_IND_SMALL_PAYLOAD_RATE_TCP
    struct sflow_ddos_ind_value_v1 in_byte_over_out_byte; // DDET_IND_INB_PER_OUTB_TCP
    struct sflow_ddos_ind_value_v1 syn_over_fin;          // DDET_IND_SYN_PER_FIN_RATE
    struct sflow_ddos_ind_value_v1 conn_miss_rate;             // DDET_IND_SESSION_MISS_RATE
    struct sflow_ddos_ind_value_v1 concurrent_conns;           // DDET_IND_CONCURRENT_CONNS
    struct sflow_ddos_ind_value_v1 pkt_drop_rate;   // DDET_IND_PKT_DROP_RATE_TCP
    struct sflow_ddos_ind_value_v1 pkt_drop_recv_ratio;     //  DDET_IND_PKT_DROP_RATIO_TCP
} __attribute__((packed));

struct sflow_ddos_dst_icmp_indicators_v1 {
    u32 seq_num;
    u16 num_data_points;
    u16 elapsed_sec;
    struct sflow_ddos_ind_value_v1 in_pkt_rate;                // DDET_IND_PKT_RATE_ICMP
    struct sflow_ddos_ind_value_v1 in_byte_over_out_byte; // DDET_IND_INB_PER_OUTB_ICMP
    struct sflow_ddos_ind_value_v1 pkt_drop_rate;   // DDET_IND_PKT_DROP_RATE_ICMP
    struct sflow_ddos_ind_value_v1 pkt_drop_recv_ratio;     //  DDET_IND_PKT_DROP_RATIO_ICMP
} __attribute__((packed));

struct sflow_ddos_dst_other_indicators_v1 {
    u32 seq_num;
    u16 num_data_points;
    u16 elapsed_sec;
    struct sflow_ddos_ind_value_v1 in_pkt_rate;                // DDET_IND_PKT_RATE_OTHER
    struct sflow_ddos_ind_value_v1 in_frag_rate;               // DDET_IND_FRAG_RATE
    struct sflow_ddos_ind_value_v1 in_byte_over_out_byte; // DDET_IND_INB_PER_OUTB_OTHER
    struct sflow_ddos_ind_value_v1 pkt_drop_rate;   // DDET_IND_PKT_DROP_RATE_OTHER
    struct sflow_ddos_ind_value_v1 pkt_drop_recv_ratio;     //  DDET_IND_PKT_DROP_RATIO_OTHER
} __attribute__((packed));

struct sflow_ddos_dst_indicators_v1 {
    struct sflow_ddos_dst_tcp_indicators_v1 tcp;
    struct sflow_ddos_dst_udp_indicators_v1 udp;
    struct sflow_ddos_dst_icmp_indicators_v1 icmp;
    struct sflow_ddos_dst_other_indicators_v1 other;
} __attribute__((packed));

typedef enum {
    SFLOW_DDOS_ENTRY_MAP_PORT_TYPE_DST = 0,
    SFLOW_DDOS_ENTRY_MAP_PORT_TYPE_SRC = 1,
} SFLOW_DDOS_ENTRY_MAP_PORT_TYPE;

/* Only add at end */
typedef enum {
    SFL_DDOS_OBJ_MAP_PORT_NONE = 0,
    SFL_DDOS_OBJ_MAP_PORT_UDP,
    SFL_DDOS_OBJ_MAP_PORT_TCP,
    SFL_DDOS_OBJ_MAP_PORT_ICMP,
    SFL_DDOS_OBJ_MAP_PORT_OTHER,
    SFL_DDOS_OBJ_MAP_PORT_HTTP,
    SFL_DDOS_OBJ_MAP_PORT_DNS_TCP,
    SFL_DDOS_OBJ_MAP_PORT_DNS_UDP,
    SFL_DDOS_OBJ_MAP_PORT_SSL,
} sflow_ddos_obj_map_port_type_t;

struct sflow_ddos_entry_map_v1 {
    u8  is_src; /* needs to be here for backwards compat since we didn't do ntohs */
    u8  port_type;
    u16 port;
    u8  entry_name[64];
} __attribute__((packed));

typedef enum {
    // global ddos brief stats
    STAT_OBJ_ID_DEVICE_DDOS_BRIEF = 416,
    
    // general stats for zone from mitigator
    STAT_OBJ_ID_ZONE = 2312,
    STAT_OBJ_ID_PORT_TCP = 2313,
    STAT_OBJ_ID_PORT_UDP = 2314,
    STAT_OBJ_ID_PORT_DNSTCP = 2315,
    STAT_OBJ_ID_PORT_DNSUDP = 2316,
    STAT_OBJ_ID_PORT_SSLL4 = 2317,
    STAT_OBJ_ID_PORT_HTTP = 2318,
    STAT_OBJ_ID_IPPROTO_OTHER = 2319,
    STAT_OBJ_ID_IPPROTO_ICMP = 2320,

    // indicator stats from mitigator or detector:
    STAT_OBJ_ID_ZONE_SRV_IND = 2401,
    STAT_OBJ_ID_ZONE_IPPROTO_NUM_IND = 2408,
    STAT_OBJ_ID_ZONE_IPPROTO_NAME_IND = 2409,
    STAT_OBJ_ID_ZONE_SRV_OTHER_IND = 2410,
    STAT_OBJ_ID_ZONE_SRV_PRANGE_IND = 2411,
 
    // general stats for dest entry from mitigator
    STAT_OBJ_ID_DST_ENTRY = 2301,
    STAT_OBJ_ID_DST_PORT_SSLL4 = 2302,
    STAT_OBJ_ID_DST_PORT_DNSTCP = 2303,
    STAT_OBJ_ID_DST_PORT_DNSUDP = 2304,
    STAT_OBJ_ID_DST_PORT_HTTP = 2305,
    STAT_OBJ_ID_DST_PORT_ICMP = 2307,
    STAT_OBJ_ID_DST_PORT_UDP = 2308,
    STAT_OBJ_ID_DST_PORT_TCP = 2309,
    STAT_OBJ_ID_DST_PORT_OTHER = 2310
} sflow_tps_stat_obj_id;

#define MAX_CH_SLOTS 2  // max chassis slots

#define slot_to_index(s) ((s > 0) ? (s-1) : 0)

typedef struct stat_device_ddos_brief {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 total_pkts_rcvd;
  u64 total_pkts_drop;
  u64 total_pkts_pass;
  u64 total_bytes_rcvd;
  u64 total_bytes_drop;
  u64 total_bytes_pass;
} stat_device_ddos_brief_t;

typedef struct stat_zone {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd_inb;
  u64 pkts_drop_inb;
  u64 pkts_pass_inb;
  u64 bytes_rcvd_inb;
  u64 bytes_drop_inb;
  u64 bytes_pass_inb;
} stat_zone_t;

typedef struct cm_stat_http {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 http_port_glid_drop;
  u64 http_blacklist_drop;
  u64 http_tcp_auth_drop;
  u64 http_src_based_glid_drop;
  u64 http_tcp_service_drop;
  u64 http_auth_drop;
  u64 http_service_drop;
  u64 syn_auth_pass;
} cm_stat_http_t;

typedef struct cm_stat_ssll4 {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 ssll4_port_glid_drop;
  u64 ssll4_blacklist_drop;
  u64 ssll4_tcp_auth_drop;
  u64 ssll4_src_based_glid_drop;
  u64 ssll4_tcp_service_drop;
  u64 ssll4_auth_drop;
  u64 ssll4_service_drop;
  u64 syn_auth_pass;
} cm_stat_ssll4_t;

typedef struct cm_stat_dnstcp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 dnstcp_port_glid_drop;
  u64 dnstcp_blacklist_drop;
  u64 dnstcp_src_based_glid_drop;
  u64 dnstcp_service_drop;
} cm_stat_dnstcp_t;

typedef struct cm_stat_dnsudp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 dnsudp_port_glid_drop;
  u64 dnsudp_blacklist_drop;
  u64 dnsudp_src_based_glid_drop;
  u64 dnsudp_auth_drop;
  u64 dnsudp_service_drop;
  u64 udp_auth_pass;
} cm_stat_dnsudp_t;

typedef struct cm_stat_tcp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 tcp_port_glid_drop;
  u64 tcp_blacklist_drop;
  u64 tcp_auth_drop;
  u64 tcp_src_based_glid_drop;
  u64 tcp_service_drop;
  u64 syn_auth_pass;
} cm_stat_tcp_t;

typedef struct cm_stat_udp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 udp_port_glid_drop;
  u64 udp_blacklist_drop;
  u64 udp_auth_drop;
  u64 udp_src_based_glid_drop;
  u64 udp_service_drop;
} cm_stat_udp_t;

typedef struct cm_stat_ipproto_icmp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 ipproto_icmp_port_glid_drop;
  u64 ipproto_icmp_blacklist_drop;
  u64 ipproto_icmp_src_based_glid_drop;
  u64 ipproto_icmp_service_drop;
} cm_stat_ipproto_icmp_t;

typedef struct cm_stat_ipproto_other {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 ipproto_other_port_glid_drop;
  u64 ipproto_other_blacklist_drop;
  u64 ipproto_other_src_based_glid_drop;
  u64 ipproto_other_service_drop;
} cm_stat_ipproto_other_t;

typedef struct cm_stat_dst_entry {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 dst_l4_drop;
  u64 src_l4_drop;
  u64 src_based_policy_drop;
  u64 dst_tcp_dropped;
  u64 dst_udp_dropped;
  u64 dst_icmp_dropped;
  u64 dst_other_dropped;
  u64 dst_src_tcp_dropped;
  u64 dst_src_udp_dropped;
  u64 dst_src_other_dropped;   
  u64 syn_auth;
  u64 dst_port_cm_dropped;
  u64 port_wildcards_dropped;
  u64 src_auth_dropped;
  u64 port_tcp_udp_dropped;
  u64 src_rates_dropped;
  u64 ip_proto_dropped;
  u64 port_cm_dropped;
  u64 dst_frag_dropped;
  u64 tcp_inb_pkt_rcvd;
  u64 udp_inb_pkt_rcvd;
  u64 icmp_inb_pkt_rcvd;
  u64 tcp_total_pkt_rcvd;
  u64 udp_total_pkt_rcvd;
  u64 icmp_total_pkt_rcvd;
  u64 other_total_pkt_rcvd;
  u64 tcp_total_pkt_pass;
  u64 tcp_total_pkt_drop;
  u64 udp_total_pkt_pass;
  u64 udp_total_pkt_drop;
  u64 icmp_total_pkt_pass;
  u64 icmp_total_pkt_drop;
  u64 other_total_pkt_pass;
  u64 other_total_pkt_drop;
  u64 tcp_session;
  u64 udp_session;
  u64 tcp_total_syn_rcvd;
  u64 tcp_total_fin_rcvd;
} cm_stat_dst_entry_t;

typedef struct cm_stat_dst_tcp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 port_tcp_dropped;
  u64 tcp_dropped;
  u64 src_tcp_dropped;
} cm_stat_dst_tcp_t;

typedef struct cm_stat_dst_udp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 port_udp_dropped;
  u64 udp_dropped;
  u64 src_udp_dropped;
} cm_stat_dst_udp_t;

typedef struct cm_stat_dst_icmp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 icmp_dropped;
  u64 icmp_template_dropped;
} cm_stat_dst_icmp_t;

typedef struct cm_stat_dst_other {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 ip_proto_dropped;
  u64 other_dropped;
  u64 src_other_dropped;
} cm_stat_dst_other_t;

typedef struct cm_stat_dst_dnstcp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 port_dns_tcp_dropped;
  u64 dns_tcp_dropped;
  u64 app_cm_dropped;
  u64 src_dns_dropped;
} cm_stat_dst_dnstcp_t;

typedef struct cm_stat_dst_dnsudp {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 port_dns_udp_dropped;
  u64 dns_udp_dropped;
  u64 force_tcp;
  u64 app_cm_dropped;
  u64 src_dns_dropped;
} cm_stat_dst_dnsudp_t;

typedef struct cm_stat_dst_http {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 port_http_dropped;
  u64 http_dropped;
  u64 http_policy_violation;
  u64 http_challenge;
  u64 app_cm_dropped;
  u64 src_http_dropped;
} cm_stat_dst_http_t;

typedef struct cm_stat_dst_ssll4 {
  long timestamp;
  u32 last_key[MAX_CH_SLOTS];
  u32 slots;
  u64 pkts_rcvd;
  u64 pkts_drop;
  u64 pkts_pass;
  u64 bytes_rcvd;
  u64 bytes_drop;
  u64 bytes_pass;
  u64 port_ssl_dropped;
  u64 ssl_dropped;
  u64 app_cm_dropped;
  u64 src_ssl_dropped;
} cm_stat_dst_ssll4_t;
#endif /* _SFLOW_DDOS_EXT_V1_H_ */
