run: cleandata folds model test clean

parsing: parsing.cpp
	g++ -o $@ $^

createtenfolds: createtenfolds.cpp
	g++ -o $@ $^

testing: testing.cpp
	g++ -o $@ $^

training: training.cpp
	g++ -o $@ $^

cleaning: cleaning.cpp
	g++ -o $@ $^

cleandata: cleaning
	./cleaning < Review.txt > dataaftercleaning.txt

model: training
	./training

folds: createtenfolds
	./createtenfolds < dataaftercleaning.txt

test: testing
	./testing

clean:
	rm -f createtenfolds parsing training testing cleaning
