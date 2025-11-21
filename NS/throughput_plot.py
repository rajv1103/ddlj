import matplotlib.pyplot as plt

trace = "out.tr"
recv_bytes = 0

sim_time = 10  # simulation time

with open(trace) as f:
    for line in f:
        fields = line.split()
        if len(fields) < 6:
            continue

        if fields[0] == "r":  # received
            recv_bytes += int(fields[5])

throughput = (recv_bytes * 8) / (sim_time * 1e6)  # Mbps

print("Throughput (Mbps):", throughput)

plt.bar(["Throughput"], [throughput])
plt.title("Network Throughput")
plt.ylabel("Mbps")
plt.show()
