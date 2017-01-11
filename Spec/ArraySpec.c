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
            if (subject != NULL) {
                array_dealloc(subject, NULL);
                subject = NULL;
            }
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
            });

            it("allows the user to retrieve stored objects", ^{
                expect(array_get(subject, 0)).to(equal(one));

                int two = 2;
                array_append(subject, &two);
                expect(array_get(subject, 1)).to(equal(two));
                expect(subject).to(have_array_count(2));
            });

            it("can store any number of objects", ^{
                for (size_t i = 2; i < 2000; i++) {
                    array_append(subject, &i);
                }

                expect(subject).to(have_array_count(1999));
                expect(array_get(subject, 0)).to(equal(one));
            });

            it("works if you try to add NULL", ^{
                array_append(subject, NULL);

                expect(subject).to(have_array_count(2));
            });

            it("returns NULL if you try to ask for an index that's not stored", ^{
                expect(array_get(subject, 65535)).to(be_null());
            });
        });
    });
}
