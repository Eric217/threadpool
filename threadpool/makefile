
# $＠，目标文件名集合 @ = at = aim at
# $<，依赖文件中的第1个文件 < 指向最左侧，第一个
# $^，所有依赖文件的集合，自动去重。^很像从上往下罩的动作，集合
# $?，所有比目标文件 mtime 新的依赖文件集合 

ROOT 	= 	$(HOME)/Desktop/threadpool

SRC_DIR = 	$(ROOT)
BIN_DIR = 	$(ROOT)/build/binary
OBJ_DIR = 	$(ROOT)/build/object
 
CC 		=	@gcc-8
LD 		= 	@ld
LIB 	=  

CFLAGS 	= 	$(LIB) \
			-c \
			-fno-builtin \
			-Wall \
			-W -Wstrict-prototypes -Wmissing-prototypes  

LDFLAGS = 	-lSystem \
		  	-syslibroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk \
		    \
		  	-arch x86_64 \
	  	  	-macosx_version_min 10.14.0 \
		  	\
		  	-demangle \
		  	-no_compact_unwind \
		  	-dynamic \
		  	-weak_reference_mismatches non-weak
		 	# (may use) -L/usr/local/lib   
			# (gcc-8) -lgcc_ext.10.5  -lgcc  
			# (gcc-mac) -lto_library -l/Applications/Xcode9.4.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/libLTO.dylib \
			# -l/Applications/Xcode9.4.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/9.1.0/lib/darwin/libclang_rt.osx.a   
   

OBJS = $(OBJ_DIR)/pool.o $(OBJ_DIR)/debug.o $(OBJ_DIR)/condition.o 

# c代码编译 
$(OBJ_DIR)/debug.o: $(SRC_DIR)/debug.c 
	$(CC) $(CFLAGS) $< -o $@ 

$(OBJ_DIR)/pool.o: $(SRC_DIR)/pool.c 
	$(CC) $(CFLAGS) $< -o $@ 
$(OBJ_DIR)/condition.o: $(SRC_DIR)/condition.c 
	$(CC) $(CFLAGS) $< -o $@ 

# 链接所有目标文件 
$(BIN_DIR)/main.bin: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@


.PHONY : mk_dir clean all all-r

mk_dir:
	@if [[ ! -d $(OBJ_DIR) ]];then mkdir -p $(OBJ_DIR);fi
	@if [[ ! -d $(BIN_DIR) ]];then mkdir -p $(BIN_DIR);fi

clean:
	@cd $(OBJ_DIR) && rm -f ./*  
	@cd $(BIN_DIR) && rm -f ./*

build: $(BIN_DIR)/main.bin 

all-r: mk_dir clean build   

all: mk_dir build  
