BUILD_DIR := ./build

all: 
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
		cd $(BUILD_DIR) && cmake .. && make; \
	else \
		cd $(BUILD_DIR) && make; \
	fi
clean:
	@if [ -d $(BUILD_DIR) ]; then \
		cd $(BUILD_DIR) && make clean; \
	fi
	rm -rf $(BUILD_DIR)
