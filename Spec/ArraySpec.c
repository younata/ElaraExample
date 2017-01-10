#include <Elara.h>

#include "Array.h"

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
    });
}
