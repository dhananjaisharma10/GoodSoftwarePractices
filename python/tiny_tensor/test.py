import unittest

import tiny_tensor

# TODO: Not sure how to determine which method from CPP code is called when
# doing, say, __mul__ and __imul__. Same for addition, subtraction, division.
# Had to use print statements to determine which CPP method was called.


class TestTensor(unittest.TestCase):
    """Tests for `tiny_tensor.Tensor`"""

    def test_size(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        exp_size = [3]
        # Act
        size = t.size()
        # Assert
        self.assertIsInstance(size, list)
        self.assertListEqual(size, exp_size)

    def test_data(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        exp_data = [1, 2, 3]
        # Act
        data = t.data()
        # Assert
        self.assertIsInstance(data, list)
        self.assertListEqual(data, exp_data)

    def test__getitem__(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        # Act & Assert
        self.assertEqual(t[0], 1.0)
        self.assertEqual(t[1], 2.0)
        self.assertEqual(t[2], 3.0)
        with self.assertRaises(IndexError):
            _ = t[3]

    def test__eq__(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2])
        # Act & Assert
        self.assertEqual(t, tiny_tensor.Tensor([1, 2]))
        self.assertNotEqual(
            t,
            tiny_tensor.Tensor(
                [
                    1,
                ]
            ),
        )
        self.assertNotEqual(
            t,
            tiny_tensor.Tensor(
                [
                    2,
                ]
            ),
        )
        self.assertNotEqual(t, tiny_tensor.Tensor([2, 1]))
        self.assertNotEqual(t, tiny_tensor.Tensor([]))

    def test__truediv__(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        scalar = 5.0
        exp_t = tiny_tensor.Tensor([0.2, 0.4, 0.6])
        # Act
        div_t = t / scalar
        # Assert
        self.assertIsInstance(div_t, tiny_tensor.Tensor)
        self.assertEqual(div_t, exp_t)
        float

    def test__idiv__(self) -> None:
        # TODO: This function still calls the scalarDiv method from CPP. We
        # want it to call selfScalarDiv. Find the right dunder method for it.
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        scalar = 5.0
        exp_t = tiny_tensor.Tensor([0.2, 0.4, 0.6])
        # Act
        t /= scalar
        # Assert
        self.assertIsInstance(t, tiny_tensor.Tensor)
        self.assertEqual(t, exp_t)

    def test__mul__(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        scalar = 5
        exp_t = tiny_tensor.Tensor([5, 10, 15])
        # Act
        mul_t = t * scalar
        # Assert
        self.assertIsInstance(mul_t, tiny_tensor.Tensor)
        self.assertEqual(mul_t, exp_t)

    def test__imul__(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        scalar = 5
        exp_t = tiny_tensor.Tensor([5, 10, 15])
        # Act
        t *= scalar
        # Assert
        self.assertIsInstance(t, tiny_tensor.Tensor)
        self.assertEqual(t, exp_t)

    def test__add__(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        scalar = 5
        exp_t = tiny_tensor.Tensor([6, 7, 8])
        # Act
        add_t = t + scalar
        # Assert
        self.assertIsInstance(add_t, tiny_tensor.Tensor)
        self.assertEqual(add_t, exp_t)

    def test__iadd__(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        scalar = 5
        exp_t = tiny_tensor.Tensor([6, 7, 8])
        # Act
        t += scalar
        # Assert
        self.assertIsInstance(t, tiny_tensor.Tensor)
        self.assertEqual(t, exp_t)

    def test__sub__(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        scalar = 5
        exp_t = tiny_tensor.Tensor([-4, -3, -2])
        # Act
        sub_t = t - scalar
        # Assert
        self.assertIsInstance(sub_t, tiny_tensor.Tensor)
        self.assertEqual(sub_t, exp_t)

    def test__isub__(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        scalar = 5
        exp_t = tiny_tensor.Tensor([-4, -3, -2])
        # Act
        t -= scalar
        # Assert
        self.assertIsInstance(t, tiny_tensor.Tensor)
        self.assertEqual(t, exp_t)

    def test_tensor_add(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        other_t = tiny_tensor.Tensor([4, 5, 6])
        exp_t = tiny_tensor.Tensor([5, 7, 9])
        # Act
        add_t = t.tensor_add(other_t)
        # Assert
        self.assertIsInstance(add_t, tiny_tensor.Tensor)
        self.assertEqual(add_t, exp_t)

    def test_tensor_mul(self) -> None:
        # Arrange
        t = tiny_tensor.Tensor([1, 2, 3])
        other_t = tiny_tensor.Tensor([4, 5, 6])
        exp_t = tiny_tensor.Tensor([4, 10, 18])
        # Act
        add_t = t.tensor_mul(other_t)
        # Assert
        self.assertIsInstance(add_t, tiny_tensor.Tensor)
        self.assertEqual(add_t, exp_t)


if __name__ == "__main__":
    unittest.main()
