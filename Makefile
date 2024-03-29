CC      =gcc
CFLAGS  =-O3 -Wall
LDFLAGS =-lpng -lz -lm
MPFLAGS =-fopenmp
SRCDIR1 =mfb_src
SRCDIR2 =com_src
OBJDIR =obj
TARGET1 =example1.out
TRGSRC1 =example1.c
TARGET2 =example2.out
TRGSRC2 =example2.c
TARGET3 =example3.out
TRGSRC3 =example3.c

SRCS1=$(wildcard $(SRCDIR1)/*.c)
OBJS1=$(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(notdir $(SRCS1)) ))
HEAD1=$(wildcard $(SRCDIR1)/*.h)
SRCS2=$(wildcard $(SRCDIR2)/*.c)
OBJS2=$(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(notdir $(SRCS2)) ))
HEAD2=$(wildcard $(SRCDIR2)/*.h)

TRGOBJ1=$(OBJS1) $(OBJS2) $(patsubst %.c,%.o,$(TRGSRC1))
TRGOBJ2=$(OBJS1) $(OBJS2) $(patsubst %.c,%.o,$(TRGSRC2))
TRGOBJ3=$(OBJS1) $(OBJS2) $(patsubst %.c,%.o,$(TRGSRC3))

all : directories $(TARGET1) $(TARGET2) $(TARGET3)

directories:
	@mkdir -p $(OBJDIR)

$(TARGET1) : $(TRGOBJ1)  
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

$(TARGET2) : $(TRGOBJ2)  
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MPFLAGS)

$(TARGET3) : $(TRGOBJ3)  
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MPFLAGS)

$(OBJDIR)/%.o : $(SRCDIR1)/%.c
	$(CC) $(CFLAGS) -I $(SRCDIR2) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR2)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.c.o :
	$(CC) $(CFLAGS) $(MPFLAGS) -I $(SRCDIR1) -I $(SRCDIR2) -c $<

clean:
	@rm -rf $(TARGET1) $(TARGET2) $(TARGET3) $(OBJDIR) *.o

$(OBJS1) : $(HEAD1)
$(OBJS1) $(OBJS2) : $(HEAD2)
