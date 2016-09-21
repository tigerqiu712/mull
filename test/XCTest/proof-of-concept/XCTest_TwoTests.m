#import <XCTest/XCTest.h>

int sum(int a, int b) {
  return a + b;  
}

@interface FooTest : XCTestCase
@end

@implementation FooTest
- (void)testFoo {
  XCTAssert(sum(2, 3) == 5);
}

@end

