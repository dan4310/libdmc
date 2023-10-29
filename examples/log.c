#include "../log.h"

int main(void) {
    log_error("Hello, Error!");
    log_warn("Hello, Warn!");
    log_info("Hello, Info!");
    log_debug("Hello, Debug!");
    return 0;
}
