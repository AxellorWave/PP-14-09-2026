CXX = g++
CXXFLAGS = -std=c++17 -pthread

OUT_DIR = out

.PHONY: all run test clean rebuild

all: $(OUT_DIR)/counter $(OUT_DIR)/tester

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/counter: main.cpp clicker.hpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) main.cpp -o $@

$(OUT_DIR)/tester: tester.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) tester.cpp -o $@

THREADS ?= 4
run: $(OUT_DIR)/counter
	$(OUT_DIR)/counter $(THREADS)

test: $(OUT_DIR)/counter $(OUT_DIR)/tester
	cd $(OUT_DIR) && ./tester

clean:
	rm -rf $(OUT_DIR) results.csv

rebuild: clean all
