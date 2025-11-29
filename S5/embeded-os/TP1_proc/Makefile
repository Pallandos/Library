.PHONY: all clean

# variables!
SRC_FOLDER = src
BIN_FOLDER = bin

$(BIN_FOLDER):
	mkdir -p $(BIN_FOLDER)

# ======== TP1 ========

sysinfo: src/sysinfo.c $(BIN_FOLDER)
	gcc -o $(BIN_FOLDER)/sysinfo $(SRC_FOLDER)/sysinfo.c

trace: src/trace.c $(BIN_FOLDER)
	gcc -o $(BIN_FOLDER)/trace $(SRC_FOLDER)/trace.c

reverse: src/reverse.c $(BIN_FOLDER)
	gcc -o $(BIN_FOLDER)/reverse $(SRC_FOLDER)/reverse.c

tp1: sysinfo trace reverse

# =====================

# ======== TP2 ========

get_priority: $(SRC_FOLDER)/tp2/get_priority.c $(BIN_FOLDER)
	gcc -o $(BIN_FOLDER)/tp2_get_priority $(SRC_FOLDER)/tp2/get_priority.c $(SRC_FOLDER)/lib/parse_info.c

set_priority: $(SRC_FOLDER)/tp2/set_priority.c $(BIN_FOLDER)
	gcc -o $(BIN_FOLDER)/set_priority $(SRC_FOLDER)/tp2/set_priority.c 

set_scheduler: $(SRC_FOLDER)/tp2/set_policy.c $(BIN_FOLDER)
	gcc -o $(BIN_FOLDER)/set_policy $(SRC_FOLDER)/tp2/set_policy.c $(SRC_FOLDER)/lib/parse_info.c

gigue: $(SRC_FOLDER)/tp2/gigue.c $(BIN_FOLDER)
	gcc -o $(BIN_FOLDER)/gigue $(SRC_FOLDER)/tp2/gigue.c

tp2: get_priority set_priority set_scheduler gigue

# =====================

default: all

all: sysinfo trace reverse

clean:
	rm -f $(BIN_FOLDER)/*