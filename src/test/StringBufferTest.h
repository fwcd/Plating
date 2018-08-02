#ifndef PLATING_STRING_BUFFER_TEST_H
#define PLATING_STRING_BUFFER_TEST_H

#include "plating/StringBuffer.h"
#include "plating/TestUtils.h"

void testStringBuffer(void) {
	StringBuffer* buf = StringBufferNew();
	assertStringBufferEq("", buf);
	assertTrue(StringBufferIsEmpty(buf), "String buffer not empty");
	
	StringBufferPush(buf, 'a');
	StringBufferPush(buf, 'b');
	StringBufferPush(buf, 'c');
	assertStringBufferEq("abc", buf);
	
	StringBufferAppend(buf, "def");
	assertStringBufferEq("abcdef", buf);
	
	StringBufferSetChar(buf, 1, 'q');
	assertStringBufferEq("aqcdef", buf);
	
	StringBufferPop(buf);
	assertStringBufferEq("aqcde", buf);
	
	assertTrue(StringBufferStartsWith(buf, "aqc"), "String buffer does not, but should start with 'aqc'");
	assertTrue(StringBufferStartsWith(buf, "aqcde"), "String buffer does not, but should start with its own contents");
	assertFalse(StringBufferStartsWith(buf, "aqcdef"), "String buffer does, but should not start with 'aqcdef'");
	assertTrue(StringBufferEndsWith(buf, "cde"), "String buffer does not, but should end with 'cde'");
	assertTrue(StringBufferEndsWith(buf, "aqcde"), "String buffer does not, but should end with its own contents");
	assertFalse(StringBufferEndsWith(buf, ".aqcde"), "String buffer does, but should not end with '.aqcde'");
	
	StringBufferClear(buf);
	assertIntEq(0, buf->length);
	assertStringBufferEq("", buf);
	
	for (int i=0; i<50; i++) {
		StringBufferPush(buf, 'x');
	}
	assertIntEq(50, buf->length);
	
	StringBufferReplace(buf, "A new string that is longer than its initial size");
	assertStringBufferEq("A new string that is longer than its initial size", buf);
	
	StringBufferDelete(buf);
	assertLeaks(0);
	
	StringBuffer* buf2 = StringBufferFrom("Just a simple string");
	StringBuffer* buf3 = StringBufferFrom("123");
	assertStringBufferEq("Just a simple string", buf2);
	
	StringBufferAppendBuf(buf2, buf3);
	assertStringBufferEq("Just a simple string123", buf2);
	
	StringBufferDelete(buf2);
	StringBufferDelete(buf3);
	assertLeaks(0);
	
	pass("StringBuffer");
}

#endif // PLATING_STRING_BUFFER_TEST_H
