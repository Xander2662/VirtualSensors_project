import platform
from .base import Sensor

try:
    import psutil
    _HAVE_PSUTIL = True
except Exception:
    print("psutil import failed")
    _HAVE_PSUTIL = False

class CpuTempSensor(Sensor):
    kind = "Temperature"

    def __init__(self, uid: str):
        super().__init__(uid)
        self.min_period = 1.0
        self.available = True  # try best-effort on each OS

    def _read_temp(self):
        if _HAVE_PSUTIL:
            temps = getattr(psutil, 'sensors_temperatures', lambda: {})()
            #print(f"Detected temperature sensors: {temps}")
            for key in ("coretemp", "k10temp", "acpitz"):
                if key in temps and temps[key]:
                    return float(temps[key][0].current)
            for arr in temps.values():
                if arr:
                    return float(arr[0].current)
        if platform.system() == 'Windows':
            try:
                import wmi
                c = wmi.WMI(namespace='root\\wmi')
                sensors = c.MSAcpi_ThermalZoneTemperature()
                if sensors:
                    kelvin = sensors[0].CurrentTemperature / 10.0
                    return float(kelvin - 273.15)
            except Exception:
                #print("WMI import or access failed")
                pass
        return None

    def read(self):
        t = self._read_temp()
        if t is None:
            return {}
        return {"temp": round(t, 1)}
