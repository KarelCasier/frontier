#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <math/Vector2.hpp>

#include <iostream>

namespace frontier {

template <typename T>
void PrintTo(const Vector2<T>& vec, ::std::ostream* os)
{
    *os << "[" << vec.x() << ", " << vec.y() << "]";
}

} // namespace frontier

using namespace frontier;

TEST(Vector2, Equal)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{5.5, 2.2};

    /// Act

    /// Assert
    ASSERT_EQ(a, b);
}

TEST(Vector2, FloatToIntCast)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};

    /// Act
    auto b = static_cast<Vector2<int>>(a);

    /// Assert
    ASSERT_EQ(b, Vector2<int>(5, 2));
}


/// Scalar arithmetic

TEST(Vector2, MultiplyScalar)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    float b{50.55};

    /// Act
    auto result = a * b;

    /// Assert
    ASSERT_EQ(result, Vector2<float>(278.025, 111.21));
}

TEST(Vector2, DivideScalar)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    float b{50.55};
    float xResult = a.x() / b;
    float yResult = a.y() / b;

    /// Act
    auto result = a / b;

    /// Assert
    ASSERT_EQ(result, Vector2<float>(xResult, yResult));
}

TEST(Vector2, AddScalar)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    float b{50.55};

    /// Act
    auto result = a + b;

    /// Assert
    ASSERT_EQ(result, Vector2<float>(56.05, 52.75));
}

TEST(Vector2, SubtractScalar)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    float b{50.55};

    /// Act
    auto result = a - b;

    /// Assert
    ASSERT_EQ(result, Vector2<float>(-45.05, -48.35));
}

/// Scalar compound assignment arithmetic

TEST(Vector2, MultiplyAssignScalar)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    float b{50.55};

    /// Act
    a *= b;

    /// Assert
    ASSERT_EQ(a, Vector2<float>(278.025, 111.21));
}

TEST(Vector2, DivideAssignScalar)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    float b{50.55};
    float xResult = a.x() / b;
    float yResult = a.y() / b;

    /// Act
    a /= b;

    /// Assert
    ASSERT_EQ(a, Vector2<float>(xResult, yResult));
}

TEST(Vector2, AddAssignScalar)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    float b{50.55};

    /// Act
    a += b;

    /// Assert
    ASSERT_EQ(a, Vector2<float>(56.05, 52.75));
}


TEST(Vector2, SubtractAssignScalar)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    float b{50.55};

    /// Act
    a -= b;

    /// Assert
    ASSERT_EQ(a, Vector2<float>(-45.05, -48.35));
}

/// Vector arithmetic

TEST(Vector2, MultiplyVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{6.6, 3.3};

    /// Act
    auto result = a * b;

    /// Assert
    ASSERT_EQ(result, Vector2<float>(36.3, 7.26));
}

TEST(Vector2, DivideVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{6.6, 3.3};
    float xResult = a.x() / b.x();
    float yResult = a.y() / b.y();

    /// Act
    auto result = a / b;

    /// Assert
    ASSERT_EQ(result, Vector2<float>(xResult, yResult));
}

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

TEST(Vector2, SubtractVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{6.6, 4.3};
    float xResult = a.x() - b.x();
    float yResult = a.y() - b.y();

    /// Act
    auto result = a - b;

    /// Assert
    ASSERT_EQ(result, Vector2<float>(xResult, yResult));
}

/// Vector compound assignment arithmetic

TEST(Vector2, MultiplyEqVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{6.6, 3.3};

    /// Act
    a *= b;

    /// Assert
    ASSERT_EQ(a, Vector2<float>(36.3, 7.26));
}

TEST(Vector2, DivideEqVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{6.6, 3.3};
    float xResult = a.x() / b.x();
    float yResult = a.y() / b.y();

    /// Act
    a /= b;

    /// Assert
    ASSERT_EQ(a, Vector2<float>(xResult, yResult));
}


TEST(Vector2, AddEqVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{6.6, 3.3};

    /// Act
    a += b;

    /// Assert
    ASSERT_EQ(a, Vector2<float>(12.1, 5.5));
}


TEST(Vector2, SubtractEqVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{6.6, 4.3};

    /// Act
    a -= b;

    /// Assert
    ASSERT_EQ(a, Vector2<float>(-1.1, -2.1));
}

/// Vector2 math

TEST(Vector2, LengthVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
	float expectedLength = std::sqrt(5.5 * 5.5 + 2.2 * 2.2);

    /// Act
	auto result = a.length();

    /// Assert
    ASSERT_EQ(result, expectedLength);
}

TEST(Vector2, LengthSquaredVector2f)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
	float expectedLength = (5.5 * 5.5 + 2.2 * 2.2);

    /// Act
	auto result = a.lengthSquared();

    /// Assert
    ASSERT_EQ(result, expectedLength);
}

TEST(Vector2, NormalizeVector2)
{
    /// Arrange
    Vector2<float> a{5.5, 2.2};
    Vector2<float> b{5.5, 2.2};

    /// Act
	a.normalize();

    /// Assert
    ASSERT_EQ(a, b * 1 / std::sqrt(5.5 * 5.5 + 2.2 * 2.2));
}

/// End Tests

int main(int argc, char** argv)
{
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
