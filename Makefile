.SUFFIXES:

TARGET		:=	wiiu-launcher
BUILD		:=	build
SOURCES		:=	source source/common source/gui source/menu
RESOURCES	:=	resources

CFLAGS		:=	-g -O2 -Wall -mhard-float -meabi
CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions -std=c++17
LDFLAGS		:=	-g $(CFLAGS) -Wl,-Map,$(notdir $@).map

LIBS		:=	-lwhb -lwut -lfat

include $(DEVKITPRO)/wut/wut_rules

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))

export OFILES	:=	$(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

.PHONY: all clean

all: $(TARGET).wuhb

$(TARGET).rpx: $(OFILES)

$(TARGET).wuhb: $(TARGET).rpx manifest.json
	@wuhbtool $(TARGET).rpx $(TARGET).wuhb --content=$(RESOURCES)

clean:
	@rm -fr $(BUILD) $(TARGET).rpx $(TARGET).wuhb
