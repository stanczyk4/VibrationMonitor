import asyncio # pip install asyncio
from bleak import BleakScanner # pip install bleak

async def run():
    while True:
        print("Scanning for Vibration Monitor...")
        devices = await BleakScanner.discover()
        for d in devices:
            if d.name == "Vibration Monitor":
                print(f"Device found: {d.name} ({d.address}). RSSI: {d.rssi}dB. MetaData: {d.metadata}")
            # print(d)

if __name__ == '__main__':

    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)

    try:
        loop.run_until_complete(run())
    except KeyboardInterrupt:
        pass
