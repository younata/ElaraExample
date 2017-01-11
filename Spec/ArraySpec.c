#include <Elara.h>

#include "Array.h"
#include "ArrayMatchers.h"

void ArraySpec() {
    describe("Array", ^{
        __block Array *subject;

        beforeEach(^{
            subject = array_init();
        });

        afterEach(^{
            array_dealloc(subject);
            subject = NULL;
        });

        it("creates a non-null array", ^{
            expect(subject).toNot(be_null());
        });

        it("has an initial count of 0", ^{
            expect(subject).to(have_array_count(0));
        });

        describe("Adding objects", ^{
            __block int one = 1;
            beforeEach(^{
                array_append(subject, &one);
            });

            it("increments the count each time an object is added", ^{
                expect(subject).to(have_array_count(1));

                for (size_t i = 2; i < 1000; i++) {
                    array_append(subject, &i);
                    expect(subject).to(have_array_count(i));
                }
            });
        });
    });
}
