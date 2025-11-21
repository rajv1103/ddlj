import matplotlib.pyplot as plt

trace = "out.tr"
sent = 0
received = 0

with open(trace) as f:
    for line in f:
        fields = line.split()
        if len(fields) < 1:
            continue

        if fields[0] == "+":
            sent += 1
        if fields[0] == "r":
            received += 1

loss = sent - received
delivery = (received / sent) * 100

print("Packets Sent:", sent)
print("Packets Received:", received)
print("Lost:", loss)
print("Delivery Ratio:", delivery)

plt.bar(["Sent", "Received", "Lost"], [sent, received, loss])
plt.title("Packet Transmission Performance")
plt.ylabel("Packets")
plt.show()
