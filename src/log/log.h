#pragma once
#include <stdio.h>

#define LOG_ALIGN "30"
#define ERRORF(fmt, ...) fprintf(stderr, "E | %-" LOG_ALIGN "s: %-" LOG_ALIGN "s | " fmt "\n", __FILE__, __func__, ##__VA_ARGS__)
#ifndef NDEBUG
#define DEBUGF(fmt, ...) fprintf(stderr, "D | %-" LOG_ALIGN "s: %-" LOG_ALIGN "s | " fmt "\n", __FILE__, __func__, ##__VA_ARGS__)
#else
#define DEBUGF(fmt, ...)
#endif
