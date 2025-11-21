# ==============================
#   NS2 Simulation Script
#   5 Nodes: n0 n1 n2 n3 n4
# ==============================

# Create simulator
set ns [new Simulator]

# Trace and NAM files
set trfile [open out.tr w]
$ns trace-all $trfile

set namfile [open out.nam w]
$ns namtrace-all $namfile

# Create 5 nodes
for {set i 0} {$i < 5} {incr i} {
    set n($i) [$ns node]
}

# Links between nodes
$ns duplex-link $n(0) $n(2) 2Mb 10ms DropTail
$ns duplex-link $n(1) $n(2) 2Mb 10ms DropTail
$ns duplex-link $n(2) $n(3) 1Mb 20ms DropTail
$ns duplex-link $n(3) $n(4) 1Mb 10ms DropTail

# ------------------------
#  TCP FLOW (n0 -> n4)
# ------------------------
set tcp0 [new Agent/TCP]
$ns attach-agent $n(0) $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n(4) $sink0

$ns connect $tcp0 $sink0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ns at 0.5 "$ftp0 start"
$ns at 8.0 "$ftp0 stop"

# ------------------------
#  UDP FLOW (n1 -> n3)
# ------------------------
set udp1 [new Agent/UDP]
$ns attach-agent $n(1) $udp1

set null1 [new Agent/Null]
$ns attach-agent $n(3) $null1

$ns connect $udp1 $null1

set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 1000
$cbr1 set rate_ 1Mb
$cbr1 attach-agent $udp1

$ns at 1.0 "$cbr1 start"
$ns at 7.0 "$cbr1 stop"

# Finish procedure
proc finish {} {
    global ns trfile namfile

    $ns flush-trace
    close $trfile
    close $namfile

    exec nam out.nam &
    exit 0
}

# Run Simulation
$ns at 10.0 "finish"
$ns run
