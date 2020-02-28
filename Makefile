
#################################
#	FROM LINUX KERNEL	#
#################################
#				#
# VERSION = 0			#
# #PATCH_LEVEL			#
# #SUBLEVEL			#
# # NAME =			#
#################################

# # Do not use make's built-in rules and variables
# (this increases performance and avoids hard-to-debug behaviour)
MAKEFLAGS += -rR


#################################
#	PROGRAM NAME		#
#################################
CLIENT_PROGRAM_NAME	:= client
SERVER_PROGRAM_NAME	:= server
#################################

#################################
#	  COMPILER		#
#################################
WARNINGS 		:= -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-align \
            		-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            		-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            		-Wconversion -Wstrict-prototypes
#WARNINGS		+= -pedantic
CFLAGS 			:= -g -std=gnu99 $(WARNINGS)
CC 			:= gcc
#################################


#################################
#	  BUILD DIR		#
#################################
MAKE_DIR 		:= $(PWD)
SOURCE 			:= src/


BUILD_CLI_DIR 		:= $(MAKE_DIR)/build/client/
BUILD_SER_DIR 		:= $(MAKE_DIR)/build/server/
BUILD_ERR_DIR 		:= $(MAKE_DIR)/build/error/
BUILD_NET_DIR 		:= $(MAKE_DIR)/build/networking/
#################################


#################################
#	COMMON .c FILES		#
#################################
ERROR_SRC 		:= $(SOURCE)error_handling
NETWORKING_SRC 		:= $(SOURCE)networking
#################################


#################################
#	CLIENT .c FILES		#
#################################
CLIENT_SRC 		:= $(SOURCE)client/
CLIENT_INTERFACE_SRC 	:= $(CLIENT_SRC)interface
CLIENT_UTILS_SRC 	:= $(CLIENT_SRC)utils
#################################


# TODO: ADD the includes of each .c file
## CLIENT INCLUDES FOR SEARCH
CLIENT_INC_SRCH_PATH :=
CLIENT_INC_SRCH_PATH += -I$(CLIENT_SRC)
CLIENT_INC_SRCH_PATH += -I$(CLIENT_INTERFACE_SRC)
CLIENT_INC_SRCH_PATH += -I$(CLIENT_UTILS_SRC)
CLIENT_INC_SRCH_PATH += -I$(NETWORKING_SRC)

##

CLIENT_LIB_SRCH_PATH :=
CLIENT_LIB_SRCH_PATH += -L $(BUILD_CLI_DIR)libs

## CLIENT LIBS
CLIENT_LIBS_DIR	:= $(BUILD_CLI_DIR)libs/

CLIENT_LIBS 		:= $(BUILD_ERR_DIR)errorlib.a \
			$(BUILD_NET_DIR)lclientnetworking.a \
			$(CLIENT_LIBS_DIR)lutils.a \
			$(CLIENT_LIBS_DIR)linterface.a 

			

## SERVER LIBS DIRECTORY
SERVER_LIBS_DIR 	:=$(BUILD_SER_DIR)libs/

SERVER_LIBS 		:= $(BUILD_NET_DIR)lservernetworking.a \
			$(SERVER_LIBS_DIR)lreceive_cmds.a \
			$(SERVER_LIBS_DIR)lsys_info.a \
			$(SERVER_LIBS_DIR)lsys_ctl.a \
			$(BUILD_ERR_DIR)errorlib.a 



## ALL SERVER LIBS
# for server.mk
#SERVER_LIBS	:=	$(MAKE_DIR)$(BUILD_ERR_DIR)errorlib.a \
			$(MAKE_DIR)$(BUILD_NET_DIR)lservernetworking.a \
			$(SERVER_LIBS_DIR)lreceive_cmds.a \
			$(SERVER_LIBS_DIR)lsys_ctl.a \
			$(SERVER_LIBS_DIR)lsys_info.a


#################################
#	SERVER .c FILES		#
#################################
SERVER_SRC		:= $(SOURCE)server
SERVER_RCV_CMDS_SRC	:= $(SOURCE)server/receive_cmds
SERVER_SYS_CTL_SRC	:= $(SOURCE)server/sys_ctl
SERVER_SYS_INFO_SRC	:= $(SOURCE)server/sys_info
#################################


export MAKE_DIR CC CFLAGS
export CLIENT_LIBS CLIENT_PROGRAM_NAME
export SERVER_LIBS SERVER_PROGRAM_NAME

# Link command:
all: $(CLIENT_PROGRAM_NAME) $(SERVER_PROGRAM_NAME)


#################################
#	    TARGETS		#
#################################
# make -C ./dir1
# make -C ./dir2

# This actually spawns/forks a new child process for every make call.
client: 	
	$(info compiling $(CLIENT_PROGRAM_NAME) ...)
	@$(MAKE) -C $(ERROR_SRC) -f error.mk --no-print-directory
	@$(MAKE) -C $(NETWORKING_SRC) -f client_networking.mk --no-print-directory
	@$(MAKE) -C $(CLIENT_UTILS_SRC) -f utils.mk --no-print-directory
	@$(MAKE) -C $(CLIENT_INTERFACE_SRC) -f interface.mk --no-print-directory
	@$(MAKE) -C $(CLIENT_SRC) -f client.mk --no-print-directory


server:
	$(info compiling $(SERVER_PROGRAM_NAME) ...)
	@$(MAKE) -C $(ERROR_SRC) -f error.mk --no-print-directory
	@$(MAKE) -C $(NETWORKING_SRC) -f server_networking.mk --no-print-directory
	@$(MAKE) -C $(SERVER_RCV_CMDS_SRC) -f receive_cmds.mk --no-print-directory
	@$(MAKE) -C $(SERVER_SYS_CTL_SRC) -f sys_ctl.mk --no-print-directory
	@$(MAKE) -C $(SERVER_SYS_INFO_SRC) -f sys_info.mk --no-print-directory
	@$(MAKE) -C $(SERVER_SRC) -f server.mk --no-print-directory
################################


# creates a build/ directory for the binaries
create:
	mkdir -p build/client/libs
	mkdir -p build/server/libs
	mkdir -p build/error
	mkdir -p build/networking


# A phony target is one that is not really the name of a file;
# rather it is just a name for a recipe to be executed when you make an
# explicit request. There are two reasons to use a phony target: to avoid a
# conflict with a file of the same name, and to improve performance.
# removes the executables and removes build/ directory

.PHONY: clean cleandir cleanelfs

clean:
	-rm -r build/




cleanelfs:
	-rm $(CLIENT_SRC)$(CLIENT_PROGRAM_NAME)
	-rm $(SERVER_SRC)$(SERVER_PROGRAM_NAME)
