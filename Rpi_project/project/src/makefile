SRCS= main.c car_positioning.c fee_calculate.c enter_exit_manage.c long_term_parking_list.c parking_history.c save_load.c display_parking_lot.c parking_status.c
OBJS= $(SRCS:.c=.o)
INCPATH= ../include
LIBPATH= ../lib
CFLAGS=-I $(INCPATH) -c

main: $(OBJS)
	$(CC) -o ../$@ -L$(LIBPATH) $(OBJS) -larray
.c.o: $(SRCS)
	$(CC) $(CFLAGS) $*.c

clean:
	rm $(OBJS) ../main
