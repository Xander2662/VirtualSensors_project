from sensors import load_sensors
s = load_sensors()
for i in range(5):
    for x in s: print(x.uid, x.read())