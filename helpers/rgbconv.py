from PIL import Image
import sys


def convert_argb_to_rgb(image_path):
    img = Image.open(image_path)
    img = img.convert("RGB")  # Convert to RGB
    img.save(sys.argv[2])  # Save as RGB PNG


convert_argb_to_rgb(sys.argv[1])
