# mqtt_public_broker.py
import paho.mqtt.client as mqtt

BROKER = "broker.hivemq.com"
PORT = 1883
TOPIC = "public/topic/test"

def on_message(client, userdata, msg):
    print(f"[SUBSCRIBER] {msg.topic}: {msg.payload.decode()}")

def publisher():
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    client.connect(BROKER, PORT)
    while True:
        msg = input("Enter message (or 'exit'): ")
        if msg == "exit":
            break
        client.publish(TOPIC, msg)
    client.disconnect()

def subscriber():
    client = mqtt.Client()
    client.on_message = on_message
    client.connect(BROKER, PORT)
    client.subscribe(TOPIC)
    print("Listening on public broker... Ctrl+C to stop.")
    client.loop_forever()

def menu():
    print("\n1. Publisher\n2. Subscriber")
    ch = input("Select: ")
    if ch == "1":
        publisher()
    else:
        subscriber()

if __name__ == "__main__":
    menu()
