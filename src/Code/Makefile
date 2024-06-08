CC = C:\\mingw64\\bin\\g++.exe
CFLAGS = -Wall -std=c++17 -g

EXEC = BidToBuy

OBJS = AuctionHouse.o Bid.o Buyer.o Clothing.o Electronics.o Home.o main.o petSupplies.o Product.o  Seller.o Shoes.o User.o Utilities.o Message.o

.PHONY: all clean		# found this online idk if it helps, .o files are not being deleted.

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXEC) AuctionHouse.o Bid.o Buyer.o Clothing.o Electronics.o Home.o main.o petSupplies.o Product.o Seller.o Shoes.o User.o Utilities.o Message.o

AuctionHouse.o: AuctionHouse.cpp
	$(CC) $(CFLAGS) -c  AuctionHouse.cpp

Bid.o: Bid.cpp
	$(CC) $(CFLAGS) -c Bid.cpp

Buyer.o: Buyer.cpp
	$(CC) $(CFLAGS) -c Buyer.cpp

Clothing.o: Clothing.cpp
	$(CC) $(CFLAGS) -c Clothing.cpp

Electronics.o: Electronics.cpp
	$(CC) $(CFLAGS) -c Electronics.cpp

Home.o: Home.cpp
	$(CC) $(CFLAGS) -c Home.cpp

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

petSupplies.o: petSupplies.cpp
	$(CC) $(CFLAGS) -c petSupplies.cpp

Product.o: Product.cpp
	$(CC) $(CFLAGS) -c  Product.cpp

Seller.o: Seller.cpp
	$(CC) $(CFLAGS) -c Seller.cpp

Shoes.o: Shoes.cpp
	$(CC) $(CFLAGS) -c Shoes.cpp

User.o: User.cpp
	$(CC) $(CFLAGS) -c User.cpp

Utilities.o: Utilities.cpp 
	$(CC) $(CFLAGS)  -c Utilities.cpp

Message.o: Message.cpp 
	$(CC) $(CFLAGS)  -c Message.cpp

clean:
	rm -f *.o $(EXEC)