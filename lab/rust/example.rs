
pub fn sum(a: i32, b: i32) -> i32 {
  return a + b;
}

#[test]
fn rusttest_foo_sum1() {
  assert!(sum(3, 4) == 7);
}

#[test]
fn rusttest_foo_sum2() {
  assert!(sum(4, 5) == 9);
}

