import paho.mqtt.client as mqtt

BROKER = "localhost"
PORT = 1883
TOPIC = "test/local"

def on_message(client, userdata, msg):
    print(f"[SUBSCRIBER] Topic: {msg.topic} | Message: {msg.payload.decode()}")

def publisher():
    client = mqtt.Client()
    client.connect(BROKER, PORT)
    while True:
        msg = input("Enter message (or 'exit'): ")
        if msg.lower() == "exit":
            break
        client.publish(TOPIC, msg)
    client.disconnect()

def subscriber():
    client = mqtt.Client()
    client.on_message = on_message
    client.connect(BROKER, PORT)
    client.subscribe(TOPIC)
    print("Listening for messages... Ctrl+C to stop.")
    client.loop_forever()

def menu():
    print("\n1. Publisher\n2. Subscriber")
    ch = input("Select option: ")
    if ch == "1":
        publisher()
    else:
        subscriber()

if __name__ == "__main__":
    menu()
