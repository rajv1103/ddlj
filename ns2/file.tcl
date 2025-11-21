# Adjusted NS2 script to force packet drops on each link
# Increased traffic rate, reduced queue sizes, reduced bandwidth to ensure drops.

# Create Simulator
set ns [new Simulator]

# Open trace file
set tracefile [open "/home/iiitkota/Desktop/test/ns2/file.tr" w]
$ns trace-all $tracefile

# Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

# Duplex links with reduced bandwidth and uniform delay
# Lower bandwidth forces congestion and packet drops on all links
$ns duplex-link $n0 $n1 0.2Mb 5ms DropTail
$ns duplex-link $n1 $n2 0.15Mb 5ms DropTail
$ns duplex-link $n2 $n3 0.1Mb 5ms DropTail
$ns duplex-link $n3 $n4 0.12Mb 5ms DropTail

# Reduce queue limits so drops occur more frequently
$ns queue-limit $n0 $n1 2
$ns queue-limit $n1 $n2 2
$ns queue-limit $n2 $n3 2
$ns queue-limit $n3 $n4 2

# Create UDP agent and Null agent
set udp0 [new Agent/UDP]
set null0 [new Agent/Null]
$ns attach-agent $n2 $udp0
$ns attach-agent $n0 $udp0
$ns attach-agent $n1 $udp0
$ns attach-agent $n4 $null0

# Create CBR traffic
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set interval_ 0.001   ;# High sending rate -> congestion
$cbr attach-agent $udp0

# Connect agents
$ns connect $udp0 $null0

# Schedule events
$ns at 0.2 "$cbr start"
$ns at 1.2 "$cbr stop"
$ns at 1.5 "finish"

# Finish procedure
proc finish {} {
    global ns tracefile
    $ns flush-trace
    close $tracefile
    exit 0
}

# Run simulation
$ns run
