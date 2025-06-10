from PIL import Image
import sys


def convert_argb_to_rgb(input_path, output_path, background_color=(255, 255, 255)):
    img = Image.open(input_path).convert("RGBA")  # Ensure it has alpha
    background = Image.new("RGB", img.size, background_color)
    background.paste(img, mask=img.split()[3])  # Use alpha channel as mask
    background.save(output_path)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input_image> <output_image>")
        sys.exit(1)

    convert_argb_to_rgb(sys.argv[1], sys.argv[2])
