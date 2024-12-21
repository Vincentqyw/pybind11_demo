import cv2
import binding_demo

image = cv2.imread("03903474_1471484089.jpg")
image2 = cv2.imread("93341989_396310999.jpg")


o = binding_demo.options()

o.image = image
o.filename = "111"
o.params = [0.1, 0.2, 0.3]


processor = binding_demo.ImageProcessor("config")

processed_image = processor.process(o)

cv2.imwrite("output.jpg", processed_image)

diff = (image2 - processed_image).sum()
breakpoint()
