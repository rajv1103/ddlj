import matplotlib.pyplot as plt

def fn(file):
    with open(file, 'r') as f:
        counts = {}

        for line in f:
            if line.startswith('d'):   # dropped packet
                arr = line.split()
                src = arr[2]          # source node
                dest = arr[3]         # destination node
                pair = (src, dest)
                counts[pair] = counts.get(pair, 0) + 1

        print("Total drop is:", sum(counts.values()))

        # Print drops for each link n0-n1, n1-n2, n2-n3, n3-n4
        for i in range(4):
            print(f"Packet dropped b/w n{i} & n{i+1} is : {counts.get((str(i), str(i+1)), 0)}")

        # X-axis labels (bandwidth levels)
        x = ["1mb", "2mb", "3mb", "4mb"]

        # Extract drop counts safely for plotting
        y = [counts.get((str(i), str(i+1)), 0) for i in range(4)]

        plt.plot(x, y, marker='o')
        plt.xlabel("Bandwidth")
        plt.ylabel("Packet dropped")
        plt.title("Packet Drops on Each Link")
        plt.grid(True)
        plt.show()

# Run function
fn('file.tr')
