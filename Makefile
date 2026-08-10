.SUFFIXES:

TARGET		:=	wiiu-launcher
BUILD		:=	build
SOURCES		:=	source source/common source/gui source/menu
RESOURCES	:=	resources

# Forces the compiler engine to skip local path queries completely
CC          :=  powerpc-eabi-gcc
CXX         :=  powerpc-eabi-g++

CFLAGS		:=	-g -O2 -Wall -mhard-float -meabi -mspe -mabi=spe
CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions -std=c++17
LDFLAGS		:=	-g $(CFLAGS) -Wl,-Map,$(notdir $@).map

LIBS		:=	-lwhb -lwut -lfat

# Forces a standard inline layout check instead of pulling folder configuration dependencies
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean

all: $(TARGET).rpx

$(TARGET).rpx: $(OFILES)
	$(CXX) $(LDFLAGS) $^ $(LIBS) -o $@

clean:
	rm -fr $(BUILD) $(TARGET).rpx
