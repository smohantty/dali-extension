#
# Copyright (c) 2018 Samsung Electronics Co., Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Build the Dali web engine chromium plugin

extension_src_dir = ../../../dali-extension

include ../../../dali-extension/web-engine-chromium/file.list

lib_LTLIBRARIES =

lib_LTLIBRARIES += libdali-web-engine-chromium-plugin.la

# Todo Web engine lite plugin separation
libdali_web_engine_chromium_plugin_la_SOURCES = \
                     $(web_engine_chromium_plugin_src_files)

libdali_web_engine_chromium_plugin_la_DEPENDENCIES =

libdali_web_engine_chromium_plugin_la_CXXFLAGS = \
                      $(DALI_CFLAGS) \
                      $(WEB_ENGINE_CHROMIUM_CFLAGS) \
                      $(ELEMENTARY_CFLAGS) \
                      -I../../../dali-extension/web-engine-chromium \
                      -Werror -Wall

libdali_web_engine_chromium_plugin_la_LIBADD = \
                      $(DLOG_LIBS) \
                      $(DALI_LIBS) \
                      $(WEB_ENGINE_CHROMIUM_LIBS)

libdali_web_engine_chromium_plugin_la_LDFLAGS = \
                      -rdynamic
