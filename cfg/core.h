// hardware
#define CFG_CORES 1
#define CFG_FLASH 14
#define CFG_TICKUS 1000
#define CFG_MAXTASK 8


// core-bin activation
#define CFG_BIN_TERM 1  // command-line
#define CFG_BIN_MEM 1   // memory manager
#define CFG_BIN_FILE 1  // file manager
#define CFG_BIN_TASK 1  // task manager
#define CFG_BIN_VAR 1   // variable manager

// core-bin config

// term: command-line app
#define CFG_BIN_TERM_MAXCHAR 32
#define CFG_BAUDRATE 9600


// mem: memory manager app
#define CFG_BIN_MEM_MSGAT 123   // message when uses too ram in kb
