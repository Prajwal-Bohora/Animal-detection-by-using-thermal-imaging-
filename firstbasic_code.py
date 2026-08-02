import serial
import numpy as np
import cv2

# ==========================
# SERIAL SETTINGS
# ==========================
PORT = "COM3"          # Change if needed
BAUD = 115200

try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
    print(f"Connected to {PORT}")
except Exception as e:
    print("Could not open serial port.")
    print(e)
    exit()

print("Press ESC to quit.")

while True:

    try:
        line = ser.readline().decode(errors="ignore").strip()

        if not line:
            continue

        values = line.split(",")

        if len(values) != 64:
            continue

        temps = np.array(values, dtype=np.float32)

        frame = temps.reshape((8, 8))

        # Rotate if needed
        frame = np.rot90(frame, 1)

        # Normalize temperatures
        minimum = frame.min()
        maximum = frame.max()

        if maximum - minimum < 0.1:
            continue

        normalized = (frame - minimum) / (maximum - minimum)
        normalized = (normalized * 255).astype(np.uint8)

        # Upscale to 512x512
        image = cv2.resize(
            normalized,
            (512, 512),
            interpolation=cv2.INTER_CUBIC
        )

        # Smooth image
        image = cv2.GaussianBlur(image, (11, 11), 0)

        # Apply thermal color map
        image = cv2.applyColorMap(image, cv2.COLORMAP_INFERNO)

        # Display max temperature
        cv2.putText(
            image,
            f"Max Temp: {maximum:.1f} C",
            (15, 30),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,
            (255, 255, 255),
            2
        )

        cv2.imshow("AMG8833 Live Thermal Camera", image)

        key = cv2.waitKey(1)

        if key == 27:   # ESC key
            break

    except KeyboardInterrupt:
        break

    except Exception as e:
        print(e)

ser.close()
cv2.destroyAllWindows()