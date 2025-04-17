import serial
import time
import random

# Inicializace sériového portu
ser = serial.Serial(
    port='COM3',
    baudrate=9600,
    timeout=0.1
)

if not ser.is_open:
    print("COM3 port is not open, opening...")
    ser.open()

def generate_messages():
    messages = [
        f"?id=3&Distance={random.randint(50, 200)}",
        f"?id=4&Temperature={random.randint(20, 35)}"
        f"&acm_x={random.randint(-20, 20)}"
        f"&acm_y={random.randint(-20, 20)}"
        f"&acm_z={random.randint(-20, 20)}"
        f"&gyr_x={random.randint(0, 100)}"
        f"&gyr_y={random.randint(0, 100)}"
        f"&gyr_z={round(random.uniform(0, 1), 2)}",
        f"?id=5&Temperature={random.randint(20, 35)}&Pressure={random.randint(950, 1050)}",
        f"?id=7&XCoordination={random.randint(0, 100)}&YCoordination={random.randint(0, 100)}&Button={random.randint(0, 1)}",
        f"?id=8&Temperature={round(random.uniform(20, 30), 1)}&Humidity={random.randint(30, 90)}",
        f"?id=9&milliTesla Meter={round(random.uniform(10.0, 15.0), 2)}&Magnet Detector={random.randint(0, 1)}",
        f"?id=10&Lux Meter={random.randint(50, 200)}"
    ]
    return messages

try:
    while True:
        msg = " ".join(generate_messages())
        ser.write(msg.encode("utf-8"))
        print(f"Message sended to bus: {msg}")
        time.sleep(2)

except KeyboardInterrupt:
    print("Comm closing...")

finally:
    ser.close()
