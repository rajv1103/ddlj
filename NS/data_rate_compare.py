import matplotlib.pyplot as plt

trace = "out.tr"
tcp_bytes = 0
udp_bytes = 0
sim_time = 10

with open(trace) as f:
    for line in f:
        fields = line.split()
        if len(fields) < 6:
            continue

        if fields[0] == "r":
            p = fields[4]
            size = int(fields[5])

            if "tcp" in p:
                tcp_bytes += size
            elif "cbr" in p:
                udp_bytes += size

tcp_rate = (tcp_bytes * 8) / (sim_time * 1e6)
udp_rate = (udp_bytes * 8) / (sim_time * 1e6)

print("TCP Data Rate:", tcp_rate, "Mbps")
print("UDP Data Rate:", udp_rate, "Mbps")

plt.bar(["TCP", "UDP"], [tcp_rate, udp_rate])
plt.title("TCP vs UDP Data Rate")
plt.ylabel("Mbps")
plt.show()
