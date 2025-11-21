import matplotlib.pyplot as plt

trace = "out.tr"

tcp_drop = 0
udp_drop = 0
cong_drop = 0
total_drop = 0

throughput = 0
recv_bytes = 0

# Parse trace file
with open(trace) as f:
    for line in f:
        fields = line.split()
        if len(fields) < 5:
            continue
        
        event = fields[0]         # d, r, +, -
        pkt_type = fields[4]      # tcp, ack, cbr, etc.
        pkt_size = int(fields[5]) # bytes

        # Find Packet Drops
        if event == "d":
            total_drop += 1
            if "tcp" in pkt_type:
                tcp_drop += 1
            if "cbr" in pkt_type or "udp" in pkt_type:
                udp_drop += 1
            
            # Congestion drop
            if "cbr" in pkt_type or "tcp" in pkt_type:
                cong_drop += 1

        # Successful Receive for throughput
        if event == "r" and fields[2] == "3":
            recv_bytes += pkt_size

# Calculate Throughput
throughput = (recv_bytes * 8) / (10 * 1000 * 1000)  # in Mbps

print("Total Packet Drops:", total_drop)
print("TCP Drops:", tcp_drop)
print("UDP Drops:", udp_drop)
print("Congestion Drops:", cong_drop)
print("Throughput (Mbps):", throughput)

# ===== Plotting =====
labels = ["Total", "TCP", "UDP", "Congestion"]
values = [total_drop, tcp_drop, udp_drop, cong_drop]

plt.figure(figsize=(8,5))
plt.plot(labels, values, marker='o', linestyle='--')
plt.title("Packet Drop Comparison")
plt.xlabel("Type")
plt.ylabel("Drop Count")
plt.grid()
plt.show()
