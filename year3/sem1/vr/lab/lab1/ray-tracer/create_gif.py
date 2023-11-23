import glob
from PIL import Image

def make_gif(frame_folder):
    # Load individual frames
    frames = [Image.open(image) for image in sorted(glob.glob(f"{frame_folder}/*.png"))]

    # Get the size of the frames (assuming all frames have the same size)
    frame_size = frames[0].size

    # Create a black background image of the same size as the frames
    background = Image.new('RGB', frame_size, (0, 0, 0))

    # Create an output list to store the frames with black backgrounds
    frames_with_background = []

    # Overlay each frame on the black background
    for frame in frames:
        # Create a copy of the black background
        frame_with_background = background.copy()
        # Paste the frame onto the black background
        frame_with_background.paste(frame, (0, 0))
        frames_with_background.append(frame_with_background)

    # Save the frames with black backgrounds as an animated GIF
    output_file = 'animation_with_black_background.gif'
    frames_with_background[0].save(
        output_file,
        save_all=True,
        append_images=frames_with_background[1:],
        duration=100,  # in milliseconds
        loop=0
    )

if __name__ == "__main__":
    make_gif("frames")
