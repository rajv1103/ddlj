import matplotlib.pyplot as plt

trace = "out.tr"
total_drop = 0

with open(trace) as f:
    for line in f:
        fields = line.split()
        if len(fields) > 0 and fields[0] == "d":
            total_drop += 1

print("Total Packets Dropped:", total_drop)

plt.bar(["Dropped"], [total_drop])
plt.title("Total Packets Dropped")
plt.ylabel("Count")
plt.show()
