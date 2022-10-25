FILE_NAME=shr
TEST_FILE=test\test.b
start:
	g++ $(FILE_NAME).cpp -o $(FILE_NAME)
	./$(FILE_NAME) --file $(TEST_FILE) --find 61
