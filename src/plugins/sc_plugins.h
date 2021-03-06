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

#ifndef __SWEETCOMB_SYSREPO_PLUGINS__
#define __SWEETCOMB_SYSREPO_PLUGINS__

#include <sysrepo.h>
#include <sysrepo/values.h>
#include <sysrepo/plugins.h>

//functions that sysrepo-plugin need
int sr_plugin_init_cb(sr_session_ctx_t *session, void **private_ctx);
void sr_plugin_cleanup_cb(sr_session_ctx_t *session, void *private_ctx);

#endif //__SWEETCOMB_SYSREPO_PLUGINS__




