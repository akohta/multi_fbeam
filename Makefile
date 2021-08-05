CC      =gcc
CFLAGS  =-O3 -Wall
LDFLAGS =-lm
SRCDIR  =mfb_src
OBJDIR  =mfb_src
TARGET1 =example1.out
TRGSRC1 =example1.c
TARGET2 =example2.out
TRGSRC2 =example2.c
TARGET3 =fpw_verification.out
TRGSRC3 =fpw_verification.c

SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(notdir $(SRCS)) ))
HEAD=$(wildcard $(SRCDIR)/*.h)

TRGOBJ1=$(OBJS) $(patsubst %.c,%.o,$(TRGSRC1))
TRGOBJ2=$(OBJS) $(patsubst %.c,%.o,$(TRGSRC2))
TRGOBJ3=$(OBJS) $(patsubst %.c,%.o,$(TRGSRC3))

all : $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1) : $(TRGOBJ1)  
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET2) : $(TRGOBJ2)  
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET3) : $(TRGOBJ3)  
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(SRCDIR) -c $< -o $@

.c.o :
	$(CC) $(CFLAGS) -c $<
        
clean:
	@rm -rf $(TARGET1) $(TARGET2) $(TARGET3) $(OBJDIR)/*.o *.o
        
$(OBJS) : $(HEAD)

