#include "ArrayMatchers.h"
#include "Array.h"
#include <stdio.h>

ElaraMatcherReturn have_array_count(size_t expected_count) {
    return matcher_create(^ElaraTestResult(void *received) {
        if (received == NULL) {
            return ElaraTestResultError;
        }
        if (array_count((Array *)received) == expected_count) {
            return ElaraTestResultPass;
        }
        return ElaraTestResultFail;
    },
    ^char *(void *received, char *to) {
        size_t message_length = 1024;
        char *message = calloc(message_length, 1);
        if (received == NULL) {
            snprintf(message, message_length, "Expected NULL %s be an Array", to);
        } else {
            size_t received_count = array_count((Array *)received);
            snprintf(message, message_length, "Expected Array (count %zu) %s have %zu element%s", received_count, to, expected_count, expected_count == 1 ? "" : "s");
        }
        return message;
    });
}
