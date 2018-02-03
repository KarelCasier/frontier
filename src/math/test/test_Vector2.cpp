#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <math/Vector2.hpp>

using namespace frontier;

TEST(Vector2, AddVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{6.6, 3.3};

    /// Act
    auto result = a + b;

    /// Assert
    ASSERT_EQ(result, Vector2<float>(12.1, 5.5));
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

