import matplotlib.pyplot as plt

trace = "out.tr"
cong_drop = 0

with open(trace) as f:
    for line in f:
        fields = line.split()
        if len(fields) < 5:
            continue

        if fields[0] == "d":  # drop
            # considering TCP + UDP traffic as congestion drop
            if "tcp" in fields[4] or "cbr" in fields[4]:
                cong_drop += 1

print("Congestion Drops:", cong_drop)

plt.bar(["Congestion"], [cong_drop])
plt.title("Packets Dropped due to Congestion")
plt.ylabel("Count")
plt.show()
