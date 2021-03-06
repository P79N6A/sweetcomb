/*
 * Copyright (c) 2018 HUACHENTEL and/or its affiliates.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __SWEETCOMB_VPP_OPERATION__
#define __SWEETCOMB_VPP_OPERATION__
#include <vapi/vapi.h>
#include <vapi/vpe.api.vapi.h>
DEFINE_VAPI_MSG_IDS_VPE_API_JSON;

#include <sysrepo.h>
#include <sysrepo/values.h>
#include <sysrepo/plugins.h>   //for SC_LOG_DBG

#define VPP_INTFC_NAME_LEN 64
#define VPP_TAP_NAME_LEN VPP_INTFC_NAME_LEN
#define VPP_IP4_ADDRESS_LEN 4
#define VPP_IP6_ADDRESS_LEN 16
#define VPP_IP4_ADDRESS_STRING_LEN 16
#define VPP_IP6_ADDRESS_STRING_LEN 46
#define VPP_MAC_ADDRESS_LEN 8
#define VPP_TAG_LEN VPP_INTFC_NAME_LEN
#define VPP_IKEV2_PROFILE_NAME_LEN VPP_INTFC_NAME_LEN
#define VPP_IKEV2_PSK_LEN VPP_INTFC_NAME_LEN
#define VPP_IKEV2_ID_LEN 32

#ifndef SC_THIS_FUNC
#ifdef __FUNCTION__
#define SC_THIS_FUNC __FUNCTION__
#else
#define SC_THIS_FUNC __func__
#endif
#endif

#ifndef SC_NOLOG
#define SC_LOG_DBG SRP_LOG_DBG
#define SC_LOG_ERR SRP_LOG_ERR
#define SC_LOG_DBG_MSG SRP_LOG_DBG_MSG
#define SC_LOG_ERR_MSG SRP_LOG_ERR_MSG
#else
#define SC_LOG_DBG //printf
#define SC_LOG_DBG //SRP_LOG_DBG
#define SC_LOG_ERR //SRP_LOG_ERR
#define SC_LOG_DBG_MSG //SRP_LOG_DBG_MSG
#define SC_LOG_ERR_MSG //SRP_LOG_ERR_MSG
#endif

#define SC_INVOKE_BEGIN SC_LOG_DBG("inovke %s bein.",SC_THIS_FUNC);
#define SC_INVOKE_END   SC_LOG_DBG("inovke %s end,with return OK.",SC_THIS_FUNC);
#define SC_INVOKE_ENDX(...)  SC_LOG_DBG("inovke %s end,with %s.",SC_THIS_FUNC, ##__VA_ARGS__)

/**
 * when use tihs must fist DEFINE_VAPI_MSG_IDS_VXLAN_API_JSON
 */
#define SC_VPP_VAPI_RECV \
do { \
	size_t size; \
	int recv_vapimsgid = -1; \
	rv = vapi_recv (g_vapi_ctx_instance, (void *) &resp, &size, 0, 0); \
	recv_vapimsgid = vapi_lookup_vapi_msg_id_t(g_vapi_ctx_instance, ntohs(resp->header._vl_msg_id) ); \
	if(recv_vapimsgid <= vapi_msg_id_get_next_index_reply \
		|| recv_vapimsgid >= vapi_get_message_count ()) { \
	  SC_LOG_DBG("***recv error msgid[%d] not in [0-%d) ,try again!***\n", \
					  recv_vapimsgid, vapi_get_message_count ()); \
	} else { \
	  SC_LOG_DBG("recv msgid [%d]\n", recv_vapimsgid); \
	  break; \
	} \
  } while(1);

#define SC_REGISTER_RPC_EVT_HANDLER(rpc_evt_handle) \
do { \
	sr_error_t rc = rpc_evt_handle(session, &subscription); \
	if (SR_ERR_OK != rc) \
	{ \
		SC_LOG_ERR("load plugin failed: %s", sr_strerror(rc)); \
		sr_unsubscribe(session, subscription); \
		SC_INVOKE_ENDX(sr_strerror(rc)); \
		return rc; \
	} \
} while(0);

///////////////////////////
//VPP接口
int sc_connect_vpp();
int sc_disconnect_vpp();
int sc_end_with(const char* str, const char* end);
extern vapi_ctx_t g_vapi_ctx_instance;
#endif //__SWEETCOMB_VPP_OPERATION__




