import matplotlib.pyplot as plt

trace = "out.tr"
tcp_drop = 0
udp_drop = 0

with open(trace) as f:
    for line in f:
        fields = line.split()
        if len(fields) < 5:
            continue

        if fields[0] == "d":
            ptype = fields[4]
            if "tcp" in ptype:
                tcp_drop += 1
            elif "cbr" in ptype or "udp" in ptype:
                udp_drop += 1

print("TCP Drop:", tcp_drop)
print("UDP Drop:", udp_drop)

plt.bar(["TCP", "UDP"], [tcp_drop, udp_drop])
plt.title("Packet Drop (TCP vs UDP)")
plt.ylabel("Count")
plt.show()
