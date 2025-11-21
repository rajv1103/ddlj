import matplotlib.pyplot as plt

trace = "out.tr"
src1_drop = 0
src2_drop = 0

with open(trace) as f:
    for line in f:
        fields = line.split()
        if len(fields) < 6:
            continue

        if fields[0] == "d":
            src = fields[2]
            if src == "0":
                src1_drop += 1
            elif src == "1":
                src2_drop += 1

print("Src0 Drops:", src1_drop)
print("Src1 Drops:", src2_drop)

plt.bar(["Src0", "Src1"], [src1_drop, src2_drop])
plt.title("Congestion Comparison")
plt.ylabel("Drops")
plt.show()
