# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2023 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BIN_DIR := $(ROOT_DIR)/bin
TOP_DIR := $(ROOT_DIR)

SRC_DIRS = $(ROOT_DIR)/src
INC_DIRS := $(ROOT_DIR)/../include
 
TARGET_EXEC := dhcp4_hal_test
 
ifeq ($(TARGET),)
$(info TARGET NOT SET )
$(info TARGET FORCED TO Linux)
TARGET=linux
CFLAGS = -DBUILD_LINUX
SRC_DIRS += $(ROOT_DIR)/skeletons/src
endif
 
$(info TARGET [$(TARGET)])
 
HAL_LIB_DIR := $(ROOT_DIR)/libs
ifeq ($(TARGET),arm)
HAL ?= dhcp4cApi
 
ifeq ($(HAL),dhcp4cApi)
SRC_DIRS = $(ROOT_DIR)/src/main.c $(ROOT_DIR)/src/test_register.c $(ROOT_DIR)/src/test_l1_dhcp4cApi.c
YLDFLAGS = -Wl,-rpath,$(HAL_LIB_DIR) -L$(HAL_LIB_DIR) -ldhcp4cApi -llogger
CFLAGS = -DDHCP4CAPI
else ifeq ($(HAL),dhcpv4c_api)
SRC_DIRS = $(ROOT_DIR)/src/main.c $(ROOT_DIR)/src/test_register.c $(ROOT_DIR)/src/test_l1_dhcpv4c_api.c
YLDFLAGS = -Wl,-rpath,$(HAL_LIB_DIR) -L$(HAL_LIB_DIR) -lapi_dhcpv4c -lsysevent
CFLAGS = -DDHCPV4C_API
else
$(error Unsupported HAL option for ARM target: $(HAL))
endif
 
$(info HAL [$(HAL)])
endif
  
.PHONY: clean list all
 
# Here is a list of exports from this makefile to the next
 
export YLDFLAGS
export BIN_DIR
export SRC_DIRS
export INC_DIRS
export TARGET
export TOP_DIR
export HAL_LIB_DIR
export CFLAGS
export TARGET_EXEC
 
.PHONY: clean list build
 
build:
	@echo UT [$@]
	make -C ./ut-core
 
list:
	@echo UT [$@]
	make -C ./ut-core list
 
clean:
	@echo UT [$@]
	make -C ./ut-core cleanall
