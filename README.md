# Reverse-Traceroute

Traceroute is a widely used Internet diagnostic tool. It measures the sequence of routers
from the source to destination. Operators use it to investigate routing failures and performance
problems. Researchers use it as the basis for Internet maps ,path prediction ,geolocation ,ISP
performance analysis,and anomaly detection.

However, traceroute has a fundamental limitation it doesn’t provide information taken
by the processed packets in reaching back to the source. Our goal is to address this basic
restriction of traceroute by building a tool to provide the same basic information as traceroute
but the path from destination back to the source. Unlike traceroute, our reverse traceroute tool
does require control of the destination. Our tool does not require new functionality from routers
or other network components.Our system builds a reverse path incrementally, Using the Client
server socket programming. There were three main measurement techniques to build the path
backwards.

First, we feel that Internet routing is generally destination-based, allowing us to group
together the path as one hop at a time.

Second, we add the IP time-stamp and record route options to the packet to identify the
path taken by the processed packets.

Third, we use limited source spoofing, i.e., shifting to another vantage points.

Discussion about the first two measurements. We need to configure the packets the way
we want in order to reach our goal, there is a tool called scapy(a python framework) or there
can also be some other tools to meet the requirement. But the intermediate routers between
the source and the destination drop all the options that we set at the time of configuring the
packets. Therefore using the record route option which is one of the most reliable method
cannot be implemented We usually rely on routers to be friendly to our techniques, yet most
of these intermediate routers are not as friendly as we think. As we ultimately want our tool
widely used operationally, we have attempted to pursue our approach in a way that it doesn’t
require the intermediate routers support. Since the system that we build is not a distributed
system, we need not make use of various vantage points to collectively gather the intermediate
router information. The system we build is a standalone system.
