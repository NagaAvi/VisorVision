import cv2
import os
import time
import subprocess
from datetime import datetime

# Load Haar cascade
cascade_path = "/home/nagaavi/haarcascade_frontalface_default.xml"
face_cascade = cv2.CascadeClassifier(cascade_path)

if face_cascade.empty():
    print("Error: Could not load Haar cascade. Check the path.")
    exit()

# Directory to save images
image_dir = "/home/nagaavi/captured_images"
os.makedirs(image_dir, exist_ok=True)

# Debugging function
def debug_message(message):
    print(f"[DEBUG] {message}")

# Function to delete old images
def delete_old_images():
    files = sorted(os.listdir(image_dir))  # Sort files by name (older first)
    if len(files) > 5:  # Keep only recent 5 images
        for file in files[:-5]:
            os.remove(os.path.join(image_dir, file))
            debug_message(f"Deleted old image: {file}")

# Main loop for real-time detection
while True:
    # Generate timestamp-based filename
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    image_path = os.path.join(image_dir, f"image_{timestamp}.jpg")

    # Capture image using libcamera-still
    command = f"libcamera-still -o {image_path} --nopreview"
    subprocess.run(command, shell=True)
    debug_message(f"Captured image: {image_path}")

    # Read the captured image
    image = cv2.imread(image_path)
    if image is None:
        debug_message("Failed to read captured image.")
        continue

    # Convert image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Detect faces
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.2, minNeighbors=5, minSize=(30, 30))

    # Display result in CLI
    if len(faces) > 0:
        print("Face Detected!")
    else:
        print("No Face Detected.")

    # Debugging: Show number of faces detected
    debug_message(f"Faces detected: {len(faces)}")

    # Delete older images for memory management
    delete_old_images()

    # Wait for 2 seconds before next capture
    time.sleep(2)
