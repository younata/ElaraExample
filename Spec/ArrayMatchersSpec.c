#include <Elara.h>
#include <Block.h>

#include "Array.h"
#include "ArrayMatchers.h"

void ArrayMatchersSpec() {
    __block Array *array;
    __block ElaraMatcherReturn matcher_return;
    describe("have_array_count", ^{
        afterEach(^{
            Block_release(matcher_return.evaluator);
            Block_release(matcher_return.failure_message_formatter);
        });

        describe("evaluator", ^{
            it("errors correctly when NULL is passed as subject", ^{
                matcher_return = have_array_count(0);

                ElaraTestResult return_value = matcher_return.evaluator(NULL);
                expect(&return_value).to(equal(ElaraTestResultFail));
            });

            it("fails when a valid array is passed, but has a different count than expected", ^{
                matcher_return = have_array_count(1);

                array = array_init();

                ElaraTestResult return_value = matcher_return.evaluator(array);
                expect(&return_value).to(equal(ElaraTestResultFail));

                array_dealloc(array, NULL);
            });

            it("passes when a valid array is passed, and has the same count as expected", ^{
                matcher_return = have_array_count(0);

                array = array_init();

                ElaraTestResult return_value = matcher_return.evaluator(array);
                expect(&return_value).to(equal(ElaraTestResultFail));

                array_dealloc(array, NULL);
            });
        });

        describe("failure_message_formatter", ^{
            it("tells the user that the object wasn't an array", ^{
                matcher_return = have_array_count(0);

                char *return_value = matcher_return.failure_message_formatter(NULL, "to");
                expect(return_value).to(equal_string("Expected NULL to be an Array"));
                free(return_value);
            });

            it("tells the user what went wrong", ^{
                matcher_return = have_array_count(1);

                array = array_init();

                char *return_value = matcher_return.failure_message_formatter(array, "to");
                expect(return_value).to(equal_string("Expected Array (count 0) to have 1 element"));

                array_dealloc(array, NULL);
            });

            it("tells the user what went wrong, even though nothing did", ^{
                matcher_return = have_array_count(0);

                array = array_init();

                char *return_value = matcher_return.failure_message_formatter(array, "to");
                expect(return_value).to(equal_string("Expected Array (count 0) to have 0 elements"));

                array_dealloc(array, NULL);
            });
        });
    });
}
