from pathlib import Path

import binding_demo
import cv2

TEST_ROOT = Path(__file__).parent


def test_main():
    """
    Tests the binding with a demo image.
    """
    # Load the test images
    img1_path = str(TEST_ROOT / "03903474_1471484089.jpg")
    img2_path = str(TEST_ROOT / "93341989_396310999.jpg")

    img1 = cv2.imread(img1_path)
    img2 = cv2.imread(img2_path)

    # Create an Options object
    opts = binding_demo.Options()
    opts.image = img1
    opts.filename = "111"
    opts.params = [0.1, 0.2, 0.3]

    # Create an image processor
    processor = binding_demo.ImageProcessor("config", img2_path)

    # Process the image
    processed_image = processor.process(opts)

    # Save the processed image
    status = cv2.imwrite("output.jpg", processed_image)
    assert status

    # Check that the processed image is the same as the test image
    diff = (img2 - processed_image).sum()
    assert diff == 0

    # Check that the forward function works
    forward_output = processor.forward(opts)

    buffer_a = [1, 2, 3]
    buffer_b = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    buffer_c = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    assert forward_output.vbuffer_a == buffer_a
    assert forward_output.vvbuffer_b == buffer_b
    assert forward_output.vbuffer_c == buffer_c
