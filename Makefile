run: cleandata folds model bmodel test btest clean

parsing: parsing.cpp
	g++ -o $@ $^

createtenfolds: createtenfolds.cpp
	g++ -o $@ $^

testing: testing.cpp
	g++ -o $@ $^

btesting: btesting.cpp
	g++ -o $@ $^

btraining: btraining.cpp
	g++ -o $@ $^

training: training.cpp
	g++ -o $@ $^

cleaning: cleaning.cpp
	g++ -o $@ $^

cleandata: cleaning
	./cleaning < Review.txt > dataaftercleaning.txt

model: training
	./training 

bmodel: btraining
	./btraining 

test: testing
	./testing

btest: btesting
	./btesting

folds: createtenfolds
	./createtenfolds < dataaftercleaning.txt

clean:
	rm -f createtenfolds parsing training testing btraining btesting cleaning
