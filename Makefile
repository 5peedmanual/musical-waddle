#################################
#	PROGRAM NAME		#
#################################
CLIENT_PROGRAM_NAME	:= client
SERVER_PROGRAM_NAME	:= server
#################################



#################################
#	  BUILD DIR		#
#################################
MAKE_DIR		:= /home/buiop/Programming/musical-waddle/
SOURCE_DIR 		:= src/


BUILD_DIR 		:= $(MAKE_DIR)build/
LIBS_DIR		:= $(MAKE_DIR)build/libs/



#################################
#################################
#	  COMPILER		#
#################################
# You dont know C flag extra
EXTRA_FLAGS	:= -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-align \
            		-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            		-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            		-Wconversion -Wstrict-prototypes
#EXTRA_FLAGS	+= -pedantic
DEBUG_FLAG	:= -g


# Compiler to use
CC 			:= gcc
# Flags for the compiler
CFLAGS 		:= $(DEBUG_FLAG) -std=gnu99
#CFLAGS		+= $(EXTRA_FLAGS)




#################################
#	 C PRE-PROCESSOR	#
#################################
# What flags should be passed to the C pre-processor
# In other words, where should we look for files to include
# This doenst include compiler specific directories
CPPFLAGS	:= -I. \
		-I$(INCLUDE_DIR)

## CLIENT INCLUDES FOR SEARCH
INCLUDE_DIR		:= $(MAKE_DIR)include/

CLIENT_INC_SRCH_PATH 	:=
CLIENT_INC_SRCH_PATH 	+= -I$(INCLUDE_DIR)networking
CLIENT_INC_SRCH_PATH 	+= -I$(INCLUDE_DIR)error_handling
CLIENT_INC_SRCH_PATH 	+= -I$(INCLUDE_DIR)client


SERVER_INC_SRCH_PATH	:= 
SERVER_INC_SRCH_PATH	+= -I$(INCLUDE_DIR)networking
SERVER_INC_SRCH_PATH	+= -I$(INCLUDE_DIR)error_handling
SERVER_INC_SRCH_PATH	+= -I$(INCLUDE_DIR)server


#################################



#################################
#	     LINKER		#
#################################
# Where to look for libraries to link
LDFLAGS			:= -L. \
			-L$(LIBS_DIR)


## CLIENT LDLIBS
CLIENT_LIBS		:= -linterface -lutils -lclientnetworking -lerror
			

## SERVER LDLIBS
SERVER_LIBS		:= -lreceive_cmds -lsys_ctl -lsys_info -lservernetworking -lerror



#################################





#################################
#	COMMON .c FILES		#
#################################
ERROR_SRC 		:= $(SOURCE_DIR)error_handling
NETWORKING_SRC 		:= $(SOURCE_DIR)networking
#################################


#################################
#	CLIENT .c FILES		#
#################################
CLIENT_SRC 		:= $(SOURCE_DIR)client/
CLIENT_INTERFACE_SRC 	:= $(CLIENT_SRC)interface
CLIENT_UTILS_SRC 	:= $(CLIENT_SRC)utils
#################################


#################################
#	SERVER .c FILES		#
#################################
SERVER_SRC		:= $(SOURCE_DIR)server
SERVER_RCV_CMDS_SRC	:= $(SOURCE_DIR)server/receive_cmds
SERVER_SYS_CTL_SRC	:= $(SOURCE_DIR)server/sys_ctl
SERVER_SYS_INFO_SRC	:= $(SOURCE_DIR)server/sys_info
#################################




export MAKE_DIR CC CFLAGS
export MAKE_DIR BUILD_DIR INCLUDE_DIR LIBS_DIR
export LDFLAGS 
export CLIENT_PROGRAM_NAME CLIENT_LIBS CLIENT_INC_SRCH_PATH
export SERVER_PROGRAM_NAME SERVER_LIBS SERVER_INC_SRCH_PATH

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
	$(MAKE) -C $(NETWORKING_SRC) -f client_networking.mk --no-print-directory
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
