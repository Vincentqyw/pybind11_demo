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

    # Create an options object
    opts = binding_demo.options()
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
