import cv2
import binding_demo
from pathlib import Path

TEST_ROOT = Path(__file__).parent


def test_main():
    img1_path = str(TEST_ROOT / "03903474_1471484089.jpg")
    img2_path = str(TEST_ROOT / "93341989_396310999.jpg")

    img1 = cv2.imread(img1_path)
    img2 = cv2.imread(img2_path)
    opts = binding_demo.options()
    opts.image = img1
    opts.filename = "111"
    opts.params = [0.1, 0.2, 0.3]

    processor = binding_demo.ImageProcessor("config", img2_path)

    processed_image = processor.process(opts)

    status = cv2.imwrite("output.jpg", processed_image)
    assert status == True

    diff = (img2 - processed_image).sum()
    assert diff == 0
