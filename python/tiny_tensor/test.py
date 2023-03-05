import unittest

import tiny_tensor


class TestTensor(unittest.TestCase):
    def test_get_size(self) -> None:
        t = tiny_tensor.Tensor([1, 2, 3])
        self.assertEqual(t.get_size(), 3)


if __name__ == "__main__":
    unittest.main()
