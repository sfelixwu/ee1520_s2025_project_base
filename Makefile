# Makefile for NCKU ee1520 Spring 2025
# instructor, Shyhtsun Felix Wu (sfelixwu@gs.ncku.edu.tw)
#

CC = g++ -std=c++14

# the followings might need to be modified for different platforms
CFLAGS = -g -I/usr/include/jsoncpp

# CFLAGS = -g -D_EE1520_DEBUG_ -I/usr/include/jsoncpp
# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

LDFLAGS = 	-L/opt/homebrew/lib					\
		-ljsoncpp -lmicrohttpd -ljsonrpccpp-common		\
		-ljsonrpccpp-server -lcurl -ljsonrpccpp-client 

CORE_INCS =	Core.h Person.h Post.h Comment.h Reaction.h		\
		Action.h Link.h JvTime.h Tag.h Thing.h			\
		Record.h GPS.h Labeled_GPS.h Commutable.h Team.h	\
		Holdable.h Locatable.h Message.h OKey.h			\
		Timed_Location.h ee1520_Common.h ee1520_Exception.h	\
		Personal_Timed_GPS_Record.h Locatable_Thing.h		\
		Traceable_Person.h					\
		Transaction.h Coupon.h Credential.h Target.h Relation.h	\
		Fridge.h Grocery.h Item.h Space.h Storage.h Revision.h	\
		Product.h Recommendation.h IP.h

CORE_OBJS =	Core.o Person.o Post.o Comment.o Reaction.o		\
	 	Action.o Link.o JvTime.o Tag.o Thing.o OKey.o		\
		Record.o GPS.o Labeled_GPS.o Commutable.o Team.o	\
		Holdable.o Locatable.o ee1520_JSON.o Message.o		\
		Timed_Location.o ee1520_Exception.o			\
		Personal_Timed_GPS_Record.o Locatable_Thing.o		\
		Traceable_Person.o					\
		Transaction.o Coupon.o Credential.o Target.o Relation.o	\
		Fridge.o Grocery.o Item.o Space.o Storage.o Revision.o	\
		Product.o Recommendation.o IP.o

# rules to build

all: 	ysd_grocery 		\
	ee1520server ee1520update ee1520search ee1520parse ee1520team ee1520casting

#	ee1520control ee1520NCKUEE ee1520NCKUHospital ee1520NCKUChangRongStation
#
#

ee1520BUSclient.h:	ee1520_bus.json
	jsonrpcstub ee1520_bus.json --cpp-server=ee1520BUSServer --cpp-client=ee1520BUSClient

ee1520BUSserver.h:	ee1520_bus.json
	jsonrpcstub ee1520_bus.json --cpp-server=ee1520BUSServer --cpp-client=ee1520BUSClient

ee1520control.o:	ee1520control.cpp ee1520BUSclient.h ee1520BUSserver.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) ee1520control.cpp

ee1520control:		$(CORE_OBJS) ee1520control.o
	$(CC) -o ee1520control $(CORE_OBJS) ee1520control.o $(LDFLAGS)


ee1520client.h:		ee1520_s2025.json
	jsonrpcstub ee1520_s2025.json --cpp-server=ee1520Server --cpp-client=ee1520Client

ee1520server.h:		ee1520_s2025.json
	jsonrpcstub ee1520_s2025.json --cpp-server=ee1520Server --cpp-client=ee1520Client

ysd_grocery.o:		ysd_grocery.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ysd_grocery.cpp

ee1520update.o:		ee1520update.cpp ee1520client.h ee1520server.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) ee1520update.cpp

ee1520search.o:		ee1520search.cpp ee1520client.h ee1520server.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) ee1520search.cpp

ee1520server.o:		ee1520server.cpp ee1520client.h ee1520server.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) ee1520server.cpp

ee1520team.o:		ee1520team.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ee1520team.cpp

ee1520casting.o:	ee1520casting.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ee1520casting.cpp

ee1520parse.o:		ee1520parse.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ee1520parse.cpp

ee1520_JSON.o:		ee1520_JSON.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ee1520_JSON.cpp

ee1520_Exception.o:	ee1520_Exception.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ee1520_Exception.cpp

Core.o:			Core.cpp Core.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Core.cpp

OKey.o:			OKey.cpp OKey.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) OKey.cpp

Message.o:		Message.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Message.cpp

Commutable.o:		Commutable.cpp Commutable.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Commutable.cpp

Transaction.o:		Transaction.cpp Transaction.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Transaction.cpp

Target.o:		Target.cpp Target.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Target.cpp

Relation.o:		Relation.cpp Relation.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Relation.cpp

Fridge.o:		Fridge.cpp Fridge.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Fridge.cpp

Grocery.o:		Grocery.cpp Grocery.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Grocery.cpp

Item.o:		Item.cpp Item.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Item.cpp

Space.o:		Space.cpp Space.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Space.cpp

Storage.o:		Storage.cpp Storage.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Storage.cpp

Revision.o:		Revision.cpp Revision.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Revision.cpp

Product.o:		Product.cpp Product.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Product.cpp

IP.o:		IP.cpp IP.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) IP.cpp

Recommendation.o:	Recommendation.cpp Recommendation.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Recommendation.cpp


Coupon.o:		Coupon.cpp Coupon.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Coupon.cpp

Credential.o:		Credential.cpp Credential.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Credential.cpp

Personal_Timed_GPS_Record.o:	Personal_Timed_GPS_Record.cpp ee1520client.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Personal_Timed_GPS_Record.cpp

Timed_Location.o:	Timed_Location.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Timed_Location.cpp

Record.o:		Record.cpp Record.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Record.cpp

Tag.o:			Tag.cpp Tag.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Tag.cpp

Team.o:			Team.cpp Team.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Team.cpp

Thing.o:		Thing.cpp Thing.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Thing.cpp

Locatable_Thing.o:	Locatable_Thing.cpp Locatable_Thing.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Locatable_Thing.cpp

Locatable.o:		Locatable.cpp Locatable.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Locatable.cpp

Holdable.o:		Holdable.cpp Holdable.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Holdable.cpp

GPS.o:			GPS.cpp GPS.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) GPS.cpp

Labeled_GPS.o:		Labeled_GPS.cpp Labeled_GPS.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Labeled_GPS.cpp

Person.o:		Person.cpp Person.h Core.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Person.cpp

Traceable_Person.o:	Traceable_Person.cpp Traceable_Person.h Core.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Traceable_Person.cpp

Post.o:			Post.cpp Post.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Post.cpp

Comment.o:		Comment.cpp Comment.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Comment.cpp

Reaction.o:		Reaction.cpp Reaction.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Reaction.cpp

JvTime.o:		JvTime.cpp JvTime.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) JvTime.cpp

Link.o:			Link.cpp Link.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Link.cpp

Action.o:		Action.cpp Action.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Action.cpp

ee1520casting:		$(CORE_OBJS) ee1520casting.o
	$(CC) $(CORE_OBJS) ee1520casting.o $(LDFLAGS)

# Linking the following three stuffs ==> into one single executable
# $(CORE_OBJS)
# ee1520casting.o
# $(LDFLAGS)

# $(CC)              -o ee1520casting $(CORE_OBJS) ee1520casting.o $(LDFLAGS)

ee1520update:		$(CORE_OBJS) ee1520update.o
	$(CC) -o ee1520update $(CORE_OBJS) ee1520update.o $(LDFLAGS)

ee1520search:		$(CORE_OBJS) ee1520search.o
	$(CC) -o ee1520search $(CORE_OBJS) ee1520search.o $(LDFLAGS)

ee1520server:		$(CORE_OBJS) ee1520server.o
	$(CC) -o ee1520server $(CORE_OBJS) ee1520server.o $(LDFLAGS)

ee1520team:		$(CORE_OBJS) ee1520team.o
	$(CC) -o ee1520team $(CORE_OBJS) ee1520team.o $(LDFLAGS)

ee1520parse:		$(CORE_OBJS) ee1520parse.o
	$(CC) -o ee1520parse $(CORE_OBJS) ee1520parse.o $(LDFLAGS)

ysd_grocery:		$(CORE_OBJS) ysd_grocery.o
	$(CC) -o ysd_grocery $(CORE_OBJS) ysd_grocery.o $(LDFLAGS)

clean:
	rm -f	*.o *~ core ee1520server ee1520update ee1520search	\
	      	ee1520server.h ee1520client.h ee1520team ee1520parse	\
		ee1520casting

